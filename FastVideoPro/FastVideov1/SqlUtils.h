#ifndef SQLUTILS_H
#define SQLUTILS_H
#include <ostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>
#include <QSqlQuery>
#include <QSqlError>
#include "macro_params.h"
#include <tuple>

#include <QDebug>
#include <type_traits>
#include <utility>
#include <QString>
#include "../../VideoServer/log.h"

using std::make_pair;
using std::make_tuple;
using std::ostream;
using std::pair;

#define SQL_UTIL_TIME_FORMAT "yyyy-MM-dd HH:mm:ss:zzz"

template <typename F, typename S, typename T>
ostream& printValues(ostream& os, const F& printF,  const S& s, const T& t)
{
    printF(os, t);
    return os;
}
template <typename F, typename S, typename T>
ostream& printValues(ostream& os, const F& printF,  const S& s, const std::pair<const char*, T>& t)
{
    printF(os, t);
    return os;
}

template <typename F, typename S, typename T, typename... Rest>
ostream& printValues(ostream& os, const F& printF, const S& s, const T& t, Rest... rest)
{
    printValues(os, printF, s, t);
    os << s;
    printValues(os, printF, s, rest...);
    return os;
}




template<typename F, typename S, typename... Types>
ostream& printValues(ostream& os, const F& printF, const S& s, const std::tuple<Types...>&  t)
{
    TuplePrinter<decltype(t), sizeof...(Types)>::printValues(os, printF, s, t);
    return os;
}

template<typename ColumnType>
ostream& coutCreateColumnSqlType(ostream& os, const ColumnType& Column)
{
    os << "VARCHAR";
    return os;
}

ostream& coutCreateColumnSqlType(ostream& os, const int& Column);
ostream& coutCreateColumnSqlType(ostream& os, const double& Column);
ostream& coutCreateColumnSqlType(ostream& os, const float& Column);

template<typename ColumnType>
ostream& printCreateColumnSql(ostream& os, const pair<const char*, ColumnType>& Column)
{
    os << Column.first << " ";
    coutCreateColumnSqlType(os, Column.second);

    return os;
}





template <typename ColumnType, typename... RestColumns>
ostream& printCreateColumnSql(ostream& os, const pair<const char*, ColumnType>& Column, RestColumns... restcols)
{
    printCreateColumnSql(os, Column);
    os<<",";
    printCreateColumnSql(os, restcols...);
    return os;
}


ostream& coutCondtionValue(ostream& os, const char* Condition);
ostream& coutCondtionValue(ostream& os, const std::string& Condition);
ostream& coutCondtionValue(ostream& os, const QString& Condition);
template<typename T>
ostream& coutCondtionValue(ostream& os, const T& Condition)
{
    os << Condition;
    return os;
}


template<typename ColumnType>
ostream& printWhereCondtionSql(ostream& os, const pair<const char*, ColumnType>& Condition)
{
    os << Condition.first << " = ";
    coutCondtionValue(os, Condition.second);
    return os;
}

template <typename ColumnType, typename... RestConditions>
ostream& printWhereCondtionSql(ostream& os, const pair<const char*, ColumnType>& Condition, RestConditions... rest)
{
    printWhereCondtionSql(os, Condition);
    os<<" AND ";
    printWhereCondtionSql(os, rest...);
    return os;

}

template<typename ColumnType>
ostream& printWhereCondtionSql(ostream& os, const std::tuple<const char*, const char*, ColumnType>& Condition)
{
    os << std::get<0>(Condition) << " "<< std::get<1>(Condition)<<" ";
    coutCondtionValue(os, std::get<2>(Condition));
    return os;
}

template <typename ColumnType, typename... RestConditions>
ostream& printWhereCondtionSql(ostream& os, const std::tuple<const char*, const char*, ColumnType>& Condition, RestConditions... rest)
{
    printWhereCondtionSql(os, Condition);
    os<<" AND ";
    printWhereCondtionSql(os, rest...);
    return os;
}

template< class Tuple, std::size_t N>
struct TuplePrinter {
    template<typename F, typename S>
    static void printValues(ostream& os, const F& printF, const S& s, const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::printValues(os, printF, s, t);
        ::printValues(os, printF, s, std::get<N - 1>(t));
    }
    static void printCreateColumn(ostream& os, const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::printCreateColumn(os, t);
        os << ",";
        printCreateColumnSql(os, std::get<N - 1>(t));
    }

    static void printCondition(ostream& os, const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::printCondition(os, t);
        os << " AND ";
        printWhereCondtionSql(os, std::get<N - 1>(t));
    }

};

template<class Tuple>
struct TuplePrinter<Tuple, 1>{
    template<typename F, typename S>
    static void printValues(ostream& os, const F& printF, const S& s, const Tuple& t)
    {
        ::printValues(os, printF, s, std::get<0>(t));
    }

    static void printCreateColumn(ostream& os, const Tuple& t)
    {
        printCreateColumnSql(os, std::get<0>(t));
    }

    static void printCondition(ostream& os, const Tuple& t)
    {
        printWhereCondtionSql(os, std::get<0>(t));
    }
};

template<size_t N>
struct Apply {
    template<typename F, typename T, typename... A>
    static inline auto apply(F && f, T && t, A &&... a)
        -> decltype(Apply<N-1>::apply(
            ::std::forward<F>(f), ::std::forward<T>(t),
            ::std::get<N-1>(::std::forward<T>(t)),
            ::std::forward<A>(a)...
            )
       )
    {
        return Apply<N-1>::apply(::std::forward<F>(f),
                ::std::forward<T>(t),
                ::std::get<N-1>(::std::forward<T>(t)),
                ::std::forward<A>(a)...
                );
    }
};

template<>
struct Apply<0> {
    template<typename F, typename T, typename... A>
    static inline auto apply(F && f, T &&, A &&... a)
        -> decltype(::std::forward<F>(f)(::std::forward<A>(a)...))
    {
        return ::std::forward<F>(f)(::std::forward<A>(a)...);
    }
};

template<typename F, typename T>
inline auto apply(F && f, T && t)
    -> decltype(Apply< ::std::tuple_size<typename ::std::decay<T>::type>::value >
                ::apply(::std::forward<F>(f), ::std::forward<T>(t)))
{
    return Apply< ::std::tuple_size< typename ::std::decay<T>::type>::value>
            ::apply(::std::forward<F>(f), ::std::forward<T>(t));
}


template <typename... Columns>
ostream& printCreateTableSql(ostream& os, const char* sTableName,  Columns... cols)
{
    os << "CREATE TABLE IF NOT EXISTS "<< sTableName << "(";
    printCreateColumnSql(os, cols...);
    os << ")";
    return os;
}

template <typename... Args>
ostream& printCreateTableSql(ostream& os, const char* sTableName,  const std::tuple<Args...>& t)
{
    os << "CREATE TABLE IF NOT EXISTS "<< sTableName << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::printCreateColumn(os, t);
    os << ");";
    return os;
}

template <typename... ColumnName>
ostream& printSelectSql(ostream& os, const char* sTableName,  ColumnName... cols)
{
    os << "SELECT ";
    printValues(os, [&](ostream& os, const QString& name){
            os << name.toLocal8Bit().data();
        }, ",", cols...);

    os << " FROM " << sTableName;
    return os;
}


//template <typename... Conditions>
//ostream& printWhereSql(ostream& os, std::tuple<Conditions...> cndtns)
//{
//    os << " WHERE ";
//    TuplePrinter<decltype(cndtns), sizeof...(Conditions)>::printCondition(os, cndtns);
//    return os;
//}

template <typename... Conditions>
ostream& printWhereSql(ostream& os, Conditions... cndtns)
{
    os << " WHERE ";
    printWhereCondtionSql(os, cndtns...);
    return os;
}

template<typename ColumnName>
ostream& printPrepearUpdateColSql(ostream& os, const ColumnName& name)
{
    printValues(os, [&](ostream& os, const ColumnName& name){
            os << name << " = :" << name;
        }, ",", name);

    return os;
}
template <typename ColumnName>
ostream& printPrepearUpdateSetSql(ostream& os, const char* sTableName,  const ColumnName& cols)
{
    os << "UPDATE " << sTableName << " SET ";
    printValues(os, [&](ostream& os, const QString& name){
            os << name << " = :" << name.toLocal8Bit().data();
        }, ",", cols);
    return os;
}
template <typename... ColumnName>
ostream& printPrepearUpdateSetSql(ostream& os, const char* sTableName,  ColumnName... cols)
{
    os << "UPDATE " << sTableName << " SET ";
    printValues(os, [&](ostream& os, const QString& name){
            os << name << " = :" << name.toLocal8Bit().data();
        }, ",", cols...);
    return os;
}

template <typename... ColumnName>
ostream& printPrepearWhereSql(ostream& os, ColumnName... cols)
{
    os << " WHERE ";
    printValues(os, [&](ostream& os, const QString& name){
            os << name << " = :" << name.toLocal8Bit().data();
        }, ",", cols...);
    return os;
}

template <typename... ColumnName>
ostream& printPrepearInsertSql(ostream& os, const char* sTableName, ColumnName... cols)
{
    os << "INSERT INTO " << sTableName << " (";
    printValues(os, [&](ostream& os, const QString& name){
            os << name.toLocal8Bit().data();
        }, ",", cols...);
    os << ") VALUES (";
    printValues(os, [&](ostream& os, const QString& name){
            os << ":" << name.toLocal8Bit().data();
        }, ",", cols...);
    os << ")";
    return os;
}

template <typename... ColumnName>
ostream& printPrepearDeleteSql(ostream& os, const char* sTableName,  ColumnName... cols)
{
    os << "DELETE FROM " << sTableName << " ";
    printPrepearWhereSql(os, cols...);
    return os;
}

ostream& printPrepearWhereSql(ostream& os, const std::vector<std::string>& vcColumns);
ostream& printPrepearDeleteSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcPrimaryColumns);
ostream& printPrepearUpdateSetSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcColumns);
ostream& printPrepearInsertSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcColumns);

#ifndef ID_COLUMN
#define ID_COLUMN "mLNId"
#define ID_NULL  -1
#endif

#define TIME_FORMAT_DB "yyyy-MM-dd HH:mm:ss:zzz"

template <class Override>
class SqlTable
{
public:
    static const char* sTableName;
protected:

    static bool sInit;
    static QString sPreparedUpdate;
    static QString sPreparedInsert;
    static QString sPreparedDelete;
    static QString sPreparedWhere;
    int mLNId;
public:
    int getLNId()
    {
        return mLNId;
    }

    template<typename... Conditions>
    static std::vector< std::shared_ptr<Override> > query(Conditions... cndtns)
    {
        std::vector< std::shared_ptr<Override> > results;
        std::stringstream sqlStream;
        sqlStream << "SELECT * FROM "<< sTableName;
        printWhereSql(sqlStream, cndtns...);
        QSqlQuery q;
        if (exec(q, sqlStream.str().c_str()))
        {

            while (q.next())
            {
                std::shared_ptr<Override> r = std::make_shared<Override>();
                r->loadData(q);
                results.push_back(r);
            }
        }

        return results;
    }

    template<typename... Conditions>
    static std::vector< std::shared_ptr<Override> > query(std::tuple<Conditions...> cndtns)
    {
        std::stringstream sqlStream;
        sqlStream << "SELECT * FROM "<< sTableName;
        printWhereSql(sqlStream, cndtns);

        return query(sqlStream);
    }

    static std::vector< std::shared_ptr<Override> > query(std::stringstream& sqlStream)
    {
        std::vector< std::shared_ptr<Override> > results;
        QSqlQuery q;
        if (exec(q, sqlStream.str().c_str()))
        {

            while (q.next())
            {
                std::shared_ptr<Override> r = std::make_shared<Override>();
                r->loadData(q);
                results.push_back(r);
            }
        }

        return results;
    }

    static std::shared_ptr<Override> get(int id)
    {
        std::vector< std::shared_ptr<Override> > mResults = query(std::make_pair("mLNId", id));
        if (mResults.size() > 0)
        {
            return mResults[0];
        }

        return std::shared_ptr<Override>();
    }

    static bool exec(QSqlQuery& q, const std::string& sql = "")
    {
        bool ok = false;
        if (sql.empty())
        {
            ok = q.exec();
        }
        else
        {

            ok = q.exec(QString::fromLocal8Bit(sql.c_str()));
        }
        if (!ok)
        {
//            Log::instance().AddLog(QString("exec sql failed:%1;%2").arg(q.lastQuery()).arg(q.lastError().text()));
            qDebug() << "exec sql failed:" << q.lastQuery() << ":" << q.lastError().text();
            q.clear();
        }

        return ok;
    }

    template<class Tuple>
    static void init(const std::vector<std::string>& vcColumnName, const Tuple& columns)
    {
        if (sInit)
        {
            return;
        }

        sInit = true;
        std::vector<std::string> primaryColumns{ID_COLUMN};
        sInit = true;
        std::stringstream strstream;
        printCreateTableSql(strstream, sTableName, columns);
        createTable(strstream);

        strstream.str("");
        printPrepearUpdateSetSql(strstream, sTableName, vcColumnName);
        printPrepearWhereSql(strstream, primaryColumns);
        sPreparedUpdate = strstream.str().c_str();
        sPreparedUpdate += ";";
 //       qDebug()<<sPreparedUpdate;
        strstream.str("");
        printPrepearInsertSql(strstream, sTableName, vcColumnName);
        sPreparedInsert = strstream.str().c_str();
        sPreparedInsert += ";";
//        qDebug()<<sPreparedInsert;
        strstream.str("");
        printPrepearDeleteSql(strstream, sTableName, primaryColumns);
        sPreparedDelete = strstream.str().c_str();
        sPreparedDelete += ";";
//        qDebug()<<sPreparedDelete;
    }

    static bool createTable(std::stringstream& sqlStream)
    {
        QString createSql(sqlStream.str().c_str());
        createSql.replace("(", "("ID_COLUMN" INTEGER primary key AutoIncrement,");
        QSqlQuery query;
//        qDebug()<<"createTable "<<" "<< sTableName<<" "<<createSql;
        return exec(query, createSql.toStdString());
    }

    SqlTable() : mLNId(ID_NULL)
    {

    }

    void loadData(int &member, const QSqlQuery &QueryResult, const char* column)
    {
        member = QueryResult.value(column).toInt();
    }
    void loadData(double &member, QSqlQuery &QueryResult, const char* column)
    {
        member = QueryResult.value(column).toDouble();
    }

    void loadData(std::string &member, QSqlQuery &QueryResult, const char* column)
    {
        member = QueryResult.value(column).toString().toLocal8Bit().data();
    }

    void loadData(QString &member, QSqlQuery &QueryResult, const char* column)
    {
        member = QueryResult.value(column).toString();
    }
    void loadData(double &member, QSqlQuery &QueryResult, int index)
    {
        member = QueryResult.value(index).toDouble();
    }
    void loadData(int &member, const QSqlQuery &QueryResult, int index)
    {
        member = QueryResult.value(index).toInt();
    }
    void loadData(std::string &member, QSqlQuery &QueryResult, int index)
    {
        member = QueryResult.value(index).toString().toLocal8Bit().data();
    }

    void loadData(QString &member, QSqlQuery &QueryResult, int index)
    {
        member = QueryResult.value(index).toString();
    }
    bool isSaved()
    {
        return mLNId != ID_NULL;
    }

    virtual bool insert()
    {
        QSqlQuery query;
        query.clear();
        query.prepare(sPreparedInsert);
        bindValues(query);
        if (exec(query))
        {
            if (exec(query, std::string("SELECT MAX(mLNId) id FROM ") + sTableName))
            {
                if (query.next())
                {
                    mLNId = query.value(0).toInt();
                    return true;
                }
            }
        }

        return false;
    }

    virtual bool update()
    {
        if (mLNId == ID_NULL)
        {
            return false;
        }
        QSqlQuery query;
        query.clear();
        query.prepare(sPreparedUpdate);
        query.bindValue(":"ID_COLUMN, mLNId);
        bindValues(query);
        return exec(query);
    }

    virtual bool save()
    {
        if (isSaved())
        {
            return this->update();
        }
        else
        {
            return this->insert();
        }
    }

    virtual bool erase()
    {
        if (isSaved())
        {
            QSqlQuery query;
            query.prepare(sPreparedDelete);
            query.bindValue(":"ID_COLUMN, mLNId);
            return exec(query);
        }

        return true;
    }

    virtual void loadData(QSqlQuery &QueryResult) = 0;
    virtual void bindValues(QSqlQuery& query) = 0;
protected:
    virtual void loaded(){

    }
};

template<class Override>
const char* SqlTable<Override>::sTableName = typeid(Override).name() + 6;
template<class Override>
QString SqlTable<Override>::sPreparedUpdate;
template<class Override>
QString SqlTable<Override>::sPreparedInsert;
template<class Override>
QString SqlTable<Override>::sPreparedDelete;
template<class Override>
bool SqlTable<Override>::sInit = false;

#endif // SQLUTILS_H

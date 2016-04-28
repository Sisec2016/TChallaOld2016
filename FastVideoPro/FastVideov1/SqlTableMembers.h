#ifndef SQLTABLEMEMBERS_H
#define SQLTABLEMEMBERS_H

#define SERIAL_MEMMBER_HEAD() \
public: \
    static void createTable(); \
    void loadData(QSqlQuery &QueryResult); \
    void bindValues(QSqlQuery& query); \



#define SERIAL_MEMMBER_3(SERIAL_CLASS, M1, M2, M3) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3)   \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
}  \




#define SERIAL_MEMMBER_4(SERIAL_CLASS, M1, M2, M3, M4) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
}  \


#define SERIAL_MEMMBER_5(SERIAL_CLASS, M1, M2, M3, M4, M5) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
}  \



#define SERIAL_MEMMBER_6(SERIAL_CLASS, M1, M2, M3, M4, M5, M6) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
  \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
}  \


#define SERIAL_MEMMBER_7(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, #M1);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, #M2);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, #M3);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, #M4);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, #M5);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, #M6);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, #M7);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
}  \




#define SERIAL_MEMMBER_8(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, "mLNId");  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, #M1);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, #M2);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, #M3);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, #M4);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, #M5);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, #M6);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, #M7);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, #M8);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
}  \


#define SERIAL_MEMMBER_9(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
}  \



#define SERIAL_MEMMBER_10(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10};  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
}  \


#define SERIAL_MEMMBER_11(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
}  \

#define SERIAL_MEMMBER_12(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
}  \

#define SERIAL_MEMMBER_13(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12),  \
                               std::make_pair(#M13, v.M13)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, #M13, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M13, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
    query.bindValue(":"#M13, M13);  \
}  \


#define SERIAL_MEMMBER_14(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12),  \
                               std::make_pair(#M13, v.M13),  \
                               std::make_pair(#M14, v.M14)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, #M13, #M14, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M13, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M14, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
    query.bindValue(":"#M13, M13);  \
    query.bindValue(":"#M14, M14);  \
}  \

#define SERIAL_MEMMBER_15(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12),  \
                               std::make_pair(#M13, v.M13),  \
                               std::make_pair(#M14, v.M14),  \
                               std::make_pair(#M15, v.M15)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, #M13, #M14, #M15, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M13, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M14, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M15, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
    query.bindValue(":"#M13, M13);  \
    query.bindValue(":"#M14, M14);  \
    query.bindValue(":"#M15, M15);  \
}  \


#define SERIAL_MEMMBER_16(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12,  M13, M14, M15, M16) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12),  \
                               std::make_pair(#M13, v.M13),  \
                               std::make_pair(#M14, v.M14),  \
                               std::make_pair(#M15, v.M15),  \
                               std::make_pair(#M16, v.M16)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, #M13, #M14, \
                            #M15, #M16, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M13, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M14, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M15, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M16, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
    query.bindValue(":"#M13, M13);  \
    query.bindValue(":"#M14, M14);  \
    query.bindValue(":"#M15, M15);  \
    query.bindValue(":"#M16, M16);  \
}  \

#define SERIAL_MEMMBER_17(SERIAL_CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12,  M13, M14, M15, M16, M17) \
void SERIAL_CLASS::createTable()  \
{ \
    if (sInit) \
    { \
        return; \
    } \
    SERIAL_CLASS v; \
    auto columns = std::make_tuple(  \
                               std::make_pair(#M1, v.M1),  \
                               std::make_pair(#M2, v.M2),  \
                               std::make_pair(#M3, v.M3),  \
                               std::make_pair(#M4, v.M4),  \
                               std::make_pair(#M5, v.M5),  \
                               std::make_pair(#M6, v.M6),  \
                               std::make_pair(#M7, v.M7),  \
                               std::make_pair(#M8, v.M8),  \
                               std::make_pair(#M9, v.M9),  \
                               std::make_pair(#M10, v.M10),  \
                               std::make_pair(#M11, v.M11),  \
                               std::make_pair(#M12, v.M12),  \
                               std::make_pair(#M13, v.M13),  \
                               std::make_pair(#M14, v.M14),  \
                               std::make_pair(#M15, v.M15),  \
                               std::make_pair(#M16, v.M16),  \
                               std::make_pair(#M17, v.M17)  \
                            );  \
    std::vector<std::string> vcColumns{#M1, #M2, #M3, #M4, #M5,  \
                                       #M6, #M7, #M8, #M9, #M10, #M11, #M12, #M13, #M14, \
                            #M15, #M16, #M17, };  \
    SqlTable<SERIAL_CLASS>::init(vcColumns, columns);  \
}  \
  \
void SERIAL_CLASS::loadData(QSqlQuery &QueryResult)  \
{  \
    int i = 0;  \
    SqlTable<SERIAL_CLASS>::loadData(mLNId, QueryResult, i++);  \
  \
    SqlTable<SERIAL_CLASS>::loadData(M1, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M2, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M3, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M4, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M5, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M6, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M7, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M8, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M9, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M10, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M11, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M12, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M13, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M14, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M15, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M16, QueryResult, i++);  \
    SqlTable<SERIAL_CLASS>::loadData(M17, QueryResult, i++);  \
    \
    loaded();  \
}  \
  \
  \
void SERIAL_CLASS::bindValues(QSqlQuery& query)  \
{  \
    query.bindValue(":"#M1, M1);  \
    query.bindValue(":"#M2, M2);  \
    query.bindValue(":"#M3, M3);  \
    query.bindValue(":"#M4, M4);  \
    query.bindValue(":"#M5, M5);  \
    query.bindValue(":"#M6, M6);  \
    query.bindValue(":"#M7, M7);  \
    query.bindValue(":"#M8, M8);  \
    query.bindValue(":"#M9, M9);  \
    query.bindValue(":"#M10, M10);  \
    query.bindValue(":"#M11, M11);  \
    query.bindValue(":"#M12, M12);  \
    query.bindValue(":"#M13, M13);  \
    query.bindValue(":"#M14, M14);  \
    query.bindValue(":"#M15, M15);  \
    query.bindValue(":"#M16, M16);  \
    query.bindValue(":"#M17, M17);  \
}  \

#endif // SQLTABLEMEMBERS_H

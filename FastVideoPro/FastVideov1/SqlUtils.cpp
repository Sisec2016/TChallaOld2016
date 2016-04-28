#include "SqlUtils.h"

ostream& coutCreateColumnSqlType(ostream& os, const int& Column)
{
    os << "INTEGER";
    return os;
}

ostream& coutCreateColumnSqlType(ostream& os, const double& Column)
{
    os << "DECIMAL (20, 10)";
    return os;
}

ostream& coutCreateColumnSqlType(ostream& os, const float& Column)
{
    os << "DECIMAL (20, 10)";
    return os;
}

ostream& coutCondtionValue(ostream& os, const char* Condition)
{
    os << "'" << Condition << "'";
    return os;
}

ostream& coutCondtionValue(ostream& os, const std::string& Condition)
{
    os << "'" << Condition << "'";
    return os;
}
ostream& coutCondtionValue(ostream& os, const QString& Condition)
{
    os << "'" << Condition.toLocal8Bit().data() << "'";
    return os;
}
ostream& printPrepearWhereSql(ostream& os, const std::vector<std::string>& vcColumns)
{
    os << " WHERE 1=1";
    for (int i = 0; i < vcColumns.size(); i++)
    {
        os << " AND ";
        os << vcColumns[i] << " = :" << vcColumns[i];
    }

    return os;
}

ostream& printPrepearDeleteSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcPrimaryColumns)
{
    os << "DELETE FROM " << sTableName << " ";
    printPrepearWhereSql(os, vcPrimaryColumns);
    return os;
}


ostream& printPrepearUpdateSetSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcColumns)
{
    os << "UPDATE " << sTableName << " SET ";
    for (int i = 0; i < vcColumns.size(); i++)
    {
        os << vcColumns[i] << " = :" << vcColumns[i];
        if (i != vcColumns.size() - 1)
        {
            os << ",";
        }
    }

    return os;
}

ostream& printPrepearInsertSql(ostream& os, const char* sTableName, const std::vector<std::string>& vcColumns)
{
    os << "INSERT INTO " << sTableName << " (";
    for (int i = 0; i < vcColumns.size(); i++)
    {
        os << vcColumns[i];
        if (i != vcColumns.size() - 1)
        {
            os << ",";
        }
    }
    os << ") VALUES (";
    for (int i = 0; i < vcColumns.size(); i++)
    {
        os << ":" << vcColumns[i];
        if (i != vcColumns.size() - 1)
        {
            os << ",";
        }
    }
    os << ")";
    return os;
}

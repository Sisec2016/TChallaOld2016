#pragma once

interface ISelect
{
	virtual ISelect* NewSelect() = 0;
	virtual void DelSelect(ISelect *) = 0;
	virtual void Clear(void) = 0;
	virtual void SetDB(const char* sDB) = 0;
	virtual ISelect* Colone() = 0;
	//select
	virtual void SetDistinct() = 0;
	virtual void SetTop(ULONG nTopNum, bool IsPercent = false, bool bTie = false) = 0;
	virtual void AddReturnColumn(const char* sColName, const char* sByName = "", const char* sNullReplace = "") = 0;
	virtual void SelectInto(const char* sNewTable) = 0;
public://from
	enum tp_Join
	{
		INNER,
		FULL,
		LEFT,
		RIGHT
	};
	virtual void AddSelcetSources(ISelect *pSelect, const char* sByName) = 0;
	virtual void AddTableSource(const char* sTable, const char* sByName = "") = 0;
	virtual void AddTableJoin(const char* sTable, const char* sByName = "", tp_Join tp = INNER) = 0;
	virtual void AddSelectJoin(ISelect *pSelect, const char* sByName, tp_Join tp = INNER) = 0;
	virtual void AddJoinCondition(const char* sJoin, const char* sColName, 
		const char* sValue, const char* sCompare = "=") = 0;
public://where
    void AddConditon(const char* sColName, int nValue, const char* sCompare = "=")
    {
        AddConditon(sColName, (long)nValue, sCompare);
    }
	virtual void AddConditon(const char* sColName, long nValue, const char* sCompare = "=") = 0;
    virtual void AddConditon(const char* sColName, unsigned __int64 nValue, const char* sCompare = "=")
    {
        AddConditon(sColName, (LONGLONG)nValue, sCompare);
    }
	virtual void AddConditon(const char* sColName, LONGLONG nValue, const char* sCompare = "=") = 0;
	virtual void AddConditon(const char* sColName, double dValue, const char* sCompare = "=") = 0;
    void AddConditon(const char* sColName, const std::string& s, const char* sCompare = "=")
    {
        AddConditon(sColName, s.c_str(), sCompare);
    }
	virtual void AddConditon(const char* sColName, const char* sValue, const char* sCompare = "=") = 0;
	virtual void AddConditonSql(const char* sColName, const char* sSqlValue, const char* sCompare = "=") = 0;
public://group by
	enum tp_GroupType
	{
		NORMAL,
		ALL,
		CUBE,
		ROLLUP
	};
	virtual void SetGroupType(tp_GroupType tp) = 0;
	virtual void AddGroup(const char* sGroupExpression) = 0;
    void AddHavingConditon(const char* sColName, int nValue, const char* sCompare = "=")
    {
        AddHavingConditon(sColName, (long)nValue, sCompare);
    }
	virtual void AddHavingConditon(const char* sColName, long nValue, const char* sCompare = "=") = 0;
    virtual void AddHavingConditon(const char* sColName, unsigned __int64 nValue, const char* sCompare = "=")
    {
        AddHavingConditon(sColName, (LONGLONG)nValue, sCompare);
    }
	virtual void AddHavingConditon(const char* sColName, LONGLONG nValue, const char* sCompare = "=") = 0;
	virtual void AddHavingConditon(const char* sColName, double dValue, const char* sCompare = "=") = 0;
	virtual void AddHavingConditon(const char* sColName, const char* sValue, const char* sCompare = "=") = 0;
    void AddHavingConditonSql(const char* sColName, const std::string& s, const char* sCompare = "=")
    {
        AddHavingConditonSql(sColName, s.c_str(), sCompare);
    }
	virtual void AddHavingConditonSql(const char* sColName, const char* sSqlValue, const char* sCompare = "=") = 0;
public://order by
	virtual void AddOrderColumn(const char* sOrderExpession, bool bAsc = true) = 0;
public://Union
	virtual void AddUnion(ISelect *pSelect) = 0;
protected:
	virtual ~ISelect()
	{
	}
	friend class CDBAgent;
	ISelect(CodeConvert *pCC) : m_pCC(pCC)
	{

	}
protected:
	CodeConvert *m_pCC;
};
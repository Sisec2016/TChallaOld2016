#pragma once
#include "codeConvert.h"
#include <string>
struct IDMLParam 
{
	IDMLParam(CodeConvert *pCC) : m_pCC(pCC)
	{

	}
	virtual ~IDMLParam()
	{

	}
	virtual void Clear(void) = 0;
	virtual void SetDB(const char* sDBName) = 0;
    virtual void SetTableName(const char* sName) = 0;
	virtual const char* GetTableName() = 0;
    void AddColumnData(const char* sColName, const std::string& s)
    {
        AddColumnData(sColName, s.c_str());
    }
 	virtual void AddColumnData(const char* sColName, const char* sValue) = 0;
    void AddColumnData(const char* sColName, int nValue)
    {
        AddColumnData(sColName, (long)nValue);
    }
	virtual void AddColumnData(const char* sColName, long nValue) = 0;
	virtual void AddColumnData(const char* sColName, unsigned __int64 nValue)
    {
        AddColumnData(sColName, (LONGLONG)nValue);
    }
	virtual void AddColumnData(const char* sColName, LONGLONG nValue) = 0;
	virtual void AddColumnData(const char* sColName, double dValue) = 0;
    void AddConditon(const char* sColName, const std::string& s, const char* sCompare = "=")
    {
        AddConditon(sColName, s.c_str(), sCompare);
    }
	virtual void AddConditon(const char* sColName, const char* sValue, const char* sCompare = "=") = 0;
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
public:
	void SetDBW(const WCHAR* sDBName)
	{
		SetDB(m_pCC->ToAnsi(sDBName));
	}
	void SetTableNameW(const WCHAR* sName)
	{
		SetTableName(m_pCC->ToAnsi(sName));
	}
	void AddColumnDataW(const WCHAR* sColName, const WCHAR* sValue)
	{
		AddColumnData(m_pCC->ToAnsi(sColName), m_pCC->ToAnsi(sValue));
	}
	void AddColumnDataW(const WCHAR* sColName, long nValue)
	{
		AddColumnData(m_pCC->ToAnsi(sColName), nValue);
	}
    void AddColumnDataW(const WCHAR* sColName, LONGLONG nValue)
    {
        AddColumnData(m_pCC->ToAnsi(sColName), nValue);
    }
	void AddColumnDataW(const WCHAR* sColName, double dValue)
	{
		AddColumnData(m_pCC->ToAnsi(sColName), dValue);
	}
	void AddConditonW(const WCHAR* sColName, long nValue, const WCHAR* sCompare)
	{
		AddConditon(m_pCC->ToAnsi(sColName), nValue, m_pCC->ToAnsi(sCompare));
	}
    void AddConditonW(const WCHAR* sColName, LONGLONG nValue, const WCHAR* sCompare)
    {
        AddConditon(m_pCC->ToAnsi(sColName), nValue, m_pCC->ToAnsi(sCompare));
    }
	void AddConditonW(const WCHAR* sColName, double dValue, const WCHAR* sCompare)
	{
		AddConditon(m_pCC->ToAnsi(sColName), dValue, m_pCC->ToAnsi(sCompare));
	}
	void AddConditonW(const WCHAR* sColName, const WCHAR* sValue, const WCHAR* sCompare)
	{
		AddConditon(m_pCC->ToAnsi(sColName), m_pCC->ToAnsi(sValue), m_pCC->ToAnsi(sCompare));
	}
protected:
	CodeConvert *m_pCC;
};
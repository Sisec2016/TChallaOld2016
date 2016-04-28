// DMLParam.h: interface for the CDMLParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMLPARAM_H__F998CD95_EF2A_44C9_B22B_755B9815701C__INCLUDED_)
#define AFX_DMLPARAM_H__F998CD95_EF2A_44C9_B22B_755B9815701C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IDMLParam.h"
#include <set>
#include <map>
#include <vector>
#include <string>
#include "codeConvert.h"
#include "Struct.h"
using namespace std;
typedef string tp_Column;
typedef string tp_Value;
typedef string tp_Param;

class CDMLParam  : public IDMLParam
{
public:
	CDMLParam(CodeConvert *pCC);
	virtual ~CDMLParam();
public:
	virtual void Clear(void)
	{
		//m_sDB.erase(m_sDB.begin(), m_sDB.end());
		m_sTbName.erase(m_sTbName.begin(), m_sTbName.end());
		m_sOrder.erase(m_sOrder.begin(), m_sOrder.end());
		m_mpData.erase(m_mpData.begin(), m_mpData.end());
		m_mpCondition.erase(m_mpCondition.begin(), m_mpCondition.end());
		SafeDelete(returnColumns);
		m_mpOrder.erase(m_mpOrder.begin(), m_mpOrder.end());
	}
	virtual void SetDB(const char* sDBName)
	{
		if (HaveSpecialChar(m_sDB))
		{
			return;
		}
		m_sDB = sDBName;
		
	}
	virtual void SetTableName(const char* sName)
	{
		if (HaveSpecialChar(m_sDB))
		{
			return;
		}
		m_sTbName = sName;
	}
	virtual const char* GetTableName()
	{
		return m_sTbName.c_str();
	}
	virtual void AddColumnData(const char* sColName, const char* sValue)
	{
		if (HaveSpecialChar(sColName))
		{
			return;
		}
		string s(sValue);
		ReplaceSpecialChar(s);
		m_mpData[sColName] = "'";
		m_mpData[sColName] += s;
		m_mpData[sColName] += "'";
	}
    virtual void AddColumnData(const char* sColName, long nValue)
    {
        if (HaveSpecialChar(sColName))
        {
            return;
        }
        m_mpData[sColName] = m_pCC->ConvertToString(nValue);
    }
    virtual void AddColumnData(const char* sColName, LONGLONG nValue)
    {
        if (HaveSpecialChar(sColName))
        {
            return;
        }
        m_mpData[sColName] = m_pCC->ConvertToString(nValue);
    }
	virtual void AddColumnData(const char* sColName, double dValue)
	{
		if (HaveSpecialChar(sColName))
		{
			return;
		}
		m_mpData[sColName] = m_pCC->ConvertToString(dValue);
	}

	virtual void AddConditon(const char* sColName, long nValue, const char* sCompare = "=")
	{
		if (NULL == sColName || sCompare == NULL)
		{
			return;
		}
		if (HaveSpecialChar(sColName) || HaveSpecialChar(sCompare))
		{
			return;
		}
		sConditon& cond = m_mpCondition[sColName];
		cond.m_sComp = sCompare;
		m_mpCondition[sColName].m_sValue = m_pCC->ConvertToString(nValue);
	}
    virtual void AddConditon(const char* sColName, LONGLONG nValue, const char* sCompare = "=")
    {
        if (NULL == sColName || sCompare == NULL)
        {
            return;
        }
        if (HaveSpecialChar(sColName) || HaveSpecialChar(sCompare))
        {
            return;
        }
        sConditon& cond = m_mpCondition[sColName];
        cond.m_sComp = sCompare;
        m_mpCondition[sColName].m_sValue = m_pCC->ConvertToString(nValue);
    }
	virtual void AddConditon(const char* sColName, double dValue, const char* sCompare = "=")
	{
		if (NULL == sColName || sCompare == NULL)
		{
			return;
		}
		if (HaveSpecialChar(sColName) || HaveSpecialChar(sCompare))
		{
			return;
		}
		sConditon& cond = m_mpCondition[sColName];
		cond.m_sComp = sCompare;
		m_mpCondition[sColName].m_sValue = m_pCC->ConvertToString(dValue);
	}
	virtual void AddConditon(const char* sColName, const char* sValue, const char* sCompare = "=")
	{
		if (NULL == sColName || sValue == NULL || sCompare == NULL)
		{
			return;
		}
		if (HaveSpecialChar(sColName) || HaveSpecialChar(sCompare))
		{
			return;
		}
		sConditon& cond = m_mpCondition[sColName];
		cond.m_sComp = sCompare;
		string s(sValue);
		ReplaceSpecialChar(s);
		m_mpCondition[sColName].m_sValue = "'";
		m_mpCondition[sColName].m_sValue += s;
		m_mpCondition[sColName].m_sValue += "'";
	}
public:
	const string& GetDB(void) const
	{
		return m_sDB;
	}
	const string& GetName(void) const
	{
		return m_sTbName;
	}
	const map<tp_Column, tp_Value>& GetData(void) const
	{
		return m_mpData;
	}
	const map<tp_Column, sConditon>&GetCondition(void) const
	{
		return m_mpCondition;
	}
protected:
	string  m_sDB;
	string  m_sTbName;
	string  m_sOrder;
	map<tp_Column, tp_Value> m_mpData;
	map<tp_Column, sConditon> m_mpCondition;
	ReturnColumns_t returnColumns;
	map<tp_Column, bool> m_mpOrder;
private:
	string m_sTemp;
	
};

#endif // !defined(AFX_DMLPARAM_H__F998CD95_EF2A_44C9_B22B_755B9815701C__INCLUDED_)

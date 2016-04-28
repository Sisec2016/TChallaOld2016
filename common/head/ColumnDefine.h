// ColumnDefine.h: interface for the CColumnDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNDEFINE_H__F51A00DF_5185_4D2C_8F1E_5757583744FE__INCLUDED_)
#define AFX_COLUMNDEFINE_H__F51A00DF_5185_4D2C_8F1E_5757583744FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IColumnDefine.h"
#include <string>
using namespace std;

class CColumnDefine : public IColumnDefine 
{
public:
	CColumnDefine(const string &sName, tp_data_type type, long nLength = 0, bool bNull = true, bool bUnique = false);
	virtual ~CColumnDefine();
	void Set(bool bNull, bool bUnique = false, const char* sDefault = "")
	{
		m_bNULL =  bNull;
		m_bUnique = bUnique;
		if (NULL != sDefault)
		{
			m_sDefult = sDefault;
		}
		
	} 
	void SetCollate(const char* sCollate)
	{
		if (NULL != sCollate)
		{
			m_sCollate = sCollate;
		}
	}
	void SetLittleNum(long nNum)
	{
		m_nLittle = nNum;
	}
	void SetAutoIncrease(long nBegin = 1, long nNum = 1)
	{
		m_bIdetity = true;//主键列
		m_nBegin = nBegin;
		m_nNum = nNum;
	}
public:
	const string& Name(void) const
	{
		return m_sName;
	}
	const string& Collate(void) const
	{
		return m_sCollate;
	}
	tp_data_type DataType(void) const
	{
		return m_type;
	}
	bool CanNull(void) const
	{
		return m_bNULL;
	}
	bool IsUnique(void) const
	{
		return m_bUnique;
	}
	long Length(void) const
	{
		return m_nLength;
	}
	long LittleLen(void) const
	{
		return m_nLittle;
	}
	bool Idetity(void) const
	{
		return m_bIdetity;
	}
	long Begin(void) const
	{
		return m_nBegin;
	}
	long Num(void) const
	{
		return m_nNum;
	}
	const string& Defult(void) const
	{
		return m_sDefult;
	}
protected:
	string m_sName;
	string m_sCollate; //排序规则
	string m_sDefult; //默认值
	bool m_bNULL;
	bool m_bUnique;
	tp_data_type m_type;
	long m_nLength;
	long m_nLittle;//小数点后几位

	bool m_bIdetity;//主键列
	long m_nBegin;
	long m_nNum;

	
};

#endif // !defined(AFX_COLUMNDEFINE_H__F51A00DF_5185_4D2C_8F1E_5757583744FE__INCLUDED_)

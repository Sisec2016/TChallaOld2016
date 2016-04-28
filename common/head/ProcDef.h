// ProcDef.h: interface for the CProcDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCDEF_H__737C73D5_FAD7_4648_838B_8BBE2B40287E__INCLUDED_)
#define AFX_PROCDEF_H__737C73D5_FAD7_4648_838B_8BBE2B40287E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include "ColumnDefine.h"
enum tp_ParamDirction
{
	PD_IN = 0,
	PD_OUT,
	PD_INOUT,
	PD_RETURN,
	PD_RETURNCOLUMN
};
class CProcDef  
{
public:
	class sParam
	{
	public:
		void SetType(tp_data_type type)
		{
			m_type = type;
		}
		tp_data_type GetType(void) const
		{
			return m_type;
		}
		void SetDirection(tp_ParamDirction dr)
		{
			m_direction = dr;
		}
		tp_ParamDirction GetDiretion(void) const
		{
			return m_direction;
		}
		void SetName(const string& sName)
		{
			m_sName = sName;
		}
		const string& GetName(void) const
		{
			return m_sName;
		}
		
		void SetValue(const string& sValue)
		{
			m_sValue = sValue;
		}
		const string& GetValue(void) const
		{
			return m_sValue;
		}
		void SetLen(int nLen)
		{
			m_nLen = nLen;
		}
		const int GetLen(void) const
		{
			return m_nLen;
		}
	protected:
		tp_data_type m_type;
		tp_ParamDirction m_direction;
		string m_sName;
		string m_sValue;
		int m_nLen;
	};
public:
	CProcDef()
	{

	}
	virtual ~CProcDef()
	{
		ClearParams();
	}
	void SetName(const string& sName)
	{
		m_sName = sName;
	}
	const string& GetName(void)
	{
		return m_sName;
	}
	void SetDB(const string& sDB)
	{
		m_sDB = sDB;
	}
	const string& GetDB(void) const
	{
		return m_sDB;
	}
	void AddParam(const char* sParamName, const char* sParamValue,
		tp_data_type DataType, int Leng, tp_ParamDirction derection);
	void ClearParams(void);
	const vector<sParam*>& GetParams(void) const;
protected:
	string m_sName;
	string m_sDB;
	vector<sParam*> m_vcParams;
};

#endif // !defined(AFX_PROCDEF_H__737C73D5_FAD7_4648_838B_8BBE2B40287E__INCLUDED_)

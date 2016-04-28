
/*
1.非线程安全

*/
#pragma once
#ifdef DBAGENT_EXPORTS
#define DBAGENT_API __declspec(dllexport)
#else
#define DBAGENT_API __declspec(dllimport)
#include "Coom.h"
#endif
#pragma warning (disable:4786)
#include "IColumnDefine.h"
#include "IDDLParam.h"
#include "IDMLParam.h"
#include "ISelect.h"
#include "ProcDef.h"
#include <string>
#include <vector>
#include <map>
#include "codeConvert.h"
using namespace std;
typedef __int64 LONGLONG; 
// This class is exported from the DBAgent.dll
typedef void* t_RESULT_TAG;
class CDBAgent {
public:
	enum tp_DBAGENT
	{
		ODBC,
		CUSTOM
	};
	enum tp_DBTYPE
	{
		SQL_SERVER = 0,
		ORACLE,
		SYBASE,
		MYSQL,
		XML,
		SQLITE
	};
public:
	virtual ~CDBAgent(void);
	void Destroy(void)
	{
		delete this;
	}
	static CDBAgent* Ctreate(tp_DBAGENT dbagent, tp_DBTYPE dbtype);
public:
	//如果是ADO，ODBC，默认用的是DSN连接方式
	virtual bool CoonByDSNW(const WCHAR* sDSN, const WCHAR* sUser, const WCHAR* sPassWord){
		return CoonByDSN(m_codeConvert.ToAnsi(sDSN), m_codeConvert.ToAnsi(sUser), m_codeConvert.ToAnsi(sPassWord));
	}
	virtual bool CoonByDSN(const char* sDSN, const char* sUser, const char* sPassWord)
	{
		return false;
	}
	virtual bool CoonW(const WCHAR* sServername, const WCHAR* sDbname, const WCHAR* sUser, const WCHAR* sPassWord){
		return Coon(m_codeConvert.ToAnsi(sServername), m_codeConvert.ToAnsi(sDbname), m_codeConvert.ToAnsi(sUser), m_codeConvert.ToAnsi(sPassWord));
	}
	virtual bool Coon(const char* sServername, const char* sDbname, const char* sUser, const char* sPassWord) = 0;	
	virtual bool DisConnect(void) = 0;
	virtual bool IsCoon(void) = 0;
	virtual void SetDefaultDBW(const WCHAR* sDefultDB)
	{
		SetDefaultDB(m_codeConvert.ToAnsi(sDefultDB));
	}
	virtual void SetDefaultDB(const char* sDefultDB)
	{
		m_sDefaultDB = sDefultDB;
	}
public://特殊查询
	virtual bool IsHaveTable(const char* sTable, bool& bHave) = 0;
	virtual bool IsHaveProc(const char* sProc, bool& bHave) = 0;
public://DDL
	IDDLParam*  DDL(void)
	{
		return m_pDDLParam;
	}
	void setDDL(IDDLParam* p)
	{
		if (nullptr != p)
		{
			m_pDDLParam = p;
		}
	}
	IDDLParam* newDDL();
	virtual bool CreateTable(void) = 0;
	virtual bool DelTable(void) = 0;
	virtual bool ReNameTable(const char* sNewName) = 0;
	virtual bool ReNameTableW(const WCHAR* sNewName)
	{
		return ReNameTable(m_codeConvert.ToAnsi(sNewName));
	}
	virtual bool AddPrimaryKey(void) = 0;
	virtual bool DelPrimaryKey(void) = 0;
	virtual bool AddForeignKey(void) = 0;
	virtual bool DelForeignKey(void) = 0;
	virtual bool AddColumn(void) = 0;
	virtual bool DelColumn(void) = 0;
	virtual bool ReNameColumn(const char* sNewColName) = 0;
	virtual bool ReNameColumnW(const WCHAR* sNewColName)
	{
		return ReNameColumn(m_codeConvert.ToAnsi(sNewColName));
	}

	virtual bool ModifyColumn(void) = 0;
	virtual bool CreateIndex(void) = 0;
	virtual bool DelIndex(void) = 0;
public://DML
	IDMLParam*  DML(void)
	{
		return m_pDMLParam;
	}
	void setDML(IDMLParam* p)
	{
		if (nullptr != p)
		{
			m_pDMLParam = p;
		}
	}
	IDMLParam* newDML();
	virtual bool AddData(IDMLParam* p = nullptr) = 0;
	virtual bool DelData(IDMLParam* p = nullptr) = 0;
	virtual bool ModifyData(IDMLParam* p = nullptr) = 0;
public:
	virtual void Destroy(t_RESULT_TAG& r) = 0;
public://数据查询
	ISelect* SLT(void)
	{
		return m_pSelect;
	}
	virtual t_RESULT_TAG Find(ISelect *pSet = NULL) = 0;
	virtual void GetFindSql(string& sSql, ISelect *pSet = NULL){sSql.erase(sSql.begin(), sSql.end());}

public://存储过程
	virtual t_RESULT_TAG CreateProcedue(const char* sName, const char* sDB = NULL)
	{
		m_procDef.ClearParams();
		m_procDef.SetName(sName);
		if (NULL != sDB)
		{
			m_procDef.SetDB(sDB);
		}
		else
		{
			m_procDef.SetDB(m_sDefaultDB);
		}
		return nullptr;
	}
	virtual t_RESULT_TAG CreateProcedueW(const WCHAR* sName, const WCHAR* sDB = NULL)
	{
		return CreateProcedue(m_codeConvert.ToAnsi(sName), m_codeConvert.ToAnsi(sDB));
	}
	virtual void AddParamValue(t_RESULT_TAG p, const char* sParamName, const char* sParamValue,
		tp_data_type DataType, int Leng = 0, tp_ParamDirction derection = PD_IN)
	{
		m_procDef.AddParam(sParamName, sParamValue, DataType, Leng, derection);
	}
	virtual void AddParamValueW(t_RESULT_TAG p,const WCHAR* sParamName, const WCHAR* sParamValue,
		tp_data_type DataType, int Leng = 0, tp_ParamDirction derection = PD_IN)
	{
		AddParamValue(p, m_codeConvert.ToAnsi(sParamName), m_codeConvert.ToAnsi(sParamValue),
			DataType, Leng, derection);
	}
	virtual bool ExcutePrcedure()
	{
		return false;
	}
	virtual long GetOuputLongW(const WCHAR* sParamName, t_RESULT_TAG r)
	{
		return 0;
	}
	virtual long GetOuputLong(const char* sParamName, t_RESULT_TAG r)
	{
		return 0;
	}
	virtual const WCHAR* GetOuputStringW(const WCHAR* sParamName, t_RESULT_TAG r)
	{
		return L"";
	}
	virtual const char* GetOuputString(const char* sParamName, t_RESULT_TAG r)
	{
		return "";
	}
	virtual double GetOuputDoubleW(const WCHAR* sParamName, t_RESULT_TAG r)
	{
		return 0;
	}
	virtual double GetOuputDouble(const char* sParamName, t_RESULT_TAG r)
	{
		return 0;
	}
public:
	const WCHAR* GetLastErroMsgW(void)
	{
		return m_codeConvert.ToUncd(m_sLastError.c_str());
	}
	const char* GetLastErroMsg(void)
	{
		return m_sLastError.c_str();
	}
public://数据浏览
	virtual bool LoadNextRow(t_RESULT_TAG r) = 0;
	virtual const char* GetString(const char *sColName, t_RESULT_TAG r) = 0;
	virtual const WCHAR* GetStringW(const WCHAR *sColName, t_RESULT_TAG r)
	{
		return m_codeConvert.ToUncd(GetString(m_codeConvert.ToAnsi(sColName), r));
	}
	virtual long GetLong(const char *sColName, t_RESULT_TAG r) = 0;
	virtual long GetLongW(const WCHAR *sColName, t_RESULT_TAG r)
	{
		return GetLong(m_codeConvert.ToAnsi(sColName), r);
	}
    virtual LONGLONG GetLongLong(const char *sColName, t_RESULT_TAG r) = 0;
    virtual LONGLONG GetLongLongW(const WCHAR *sColName, t_RESULT_TAG r)
    {
        return GetLongLong(m_codeConvert.ToAnsi(sColName), r);
    }
	virtual double GetDouble(const char *sColName, t_RESULT_TAG r) = 0;
	virtual double GetDoubleW(const WCHAR *sColName, t_RESULT_TAG r)
	{
		return GetDouble(m_codeConvert.ToAnsi(sColName), r);
	}
	virtual const DECIMAL& GetDecimal(const char *sColName, t_RESULT_TAG r)
	{
		return m_dcmlTemp;
	}
	virtual const DECIMAL& GetDecimalW(const WCHAR *sColName, t_RESULT_TAG r)
	{
		return GetDecimal(m_codeConvert.ToAnsi(sColName), r);
	}
protected:
	string m_sLastError;
    IDDLParam *m_pDDLParam;
	IDMLParam *m_pDMLParam;
	ISelect *m_pSelect;
	CProcDef m_procDef;
protected:
	string m_sSql;
public:
	virtual bool Execute(const char *sSql, bool bClearParam = true) = 0;
	virtual bool ExecuteW(const WCHAR* sSql, bool bClearParam = true)
	{
		return Execute(m_codeConvert.ToAnsi(sSql), bClearParam);
	}
	virtual t_RESULT_TAG Select(const char *sSql, bool bClearParam = true) = 0;
	virtual t_RESULT_TAG SelectW(const WCHAR* sSql, bool bClearParam = true)
	{
		return Select(m_codeConvert.ToAnsi(sSql), bClearParam);
	}
protected:
	CDBAgent(void);
protected:
	CodeConvert m_codeConvert;
	DECIMAL m_dcmlTemp;
	string m_sDefaultDB;
};

extern "C" DBAGENT_API CDBAgent* GetDBAgent(CDBAgent::tp_DBAGENT dbagent, CDBAgent::tp_DBTYPE dbtype);


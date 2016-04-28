#pragma once
#include "TableDefine.h"
#include "DMLParam.h"
#include "SelectParam.h"
#include "DBAgent.h"
class ISQL
{ 
public:
	virtual ~ISQL()
	{
	}
	virtual const string& IsHaveTable(const char* sTable, const char* sDataBase = NULL) = 0;
	virtual const string& IsHaveProc(const char* sProc, const char* sDataBase = NULL) = 0;
public://DDL
	virtual const string& CreateTable(const CTableDefine *pDDL) = 0;
	virtual const string& DelTable(const CTableDefine *pDDL) = 0;
	virtual const string& ReNameTable(const CTableDefine *pDDL, const string& sNewName) = 0;
	virtual const string& AddPrimaryKey(const CTableDefine *pDDL) = 0;
	virtual const string& DelPrimaryKey(const CTableDefine *pDDL) = 0;
	virtual const string& AddForeignKey(const CTableDefine *pDDL) = 0;
	virtual const string& DelForeignKey(const CTableDefine *pDDL) = 0;
	virtual const string& AddColumn(const CTableDefine *pDDL) = 0;
	virtual const string& DelColumn(const CTableDefine *pDDL) = 0;
	virtual const string& ReNameColumn(const CTableDefine *pDDL, const string& sNewColName) = 0;
	virtual const string& ModifyColumn(const CTableDefine *pDDL) = 0;
	virtual const string& CreateIndex(const tp_index* pIndex, const string& sIndex, const string& sTableName) = 0;
	virtual const string& DelIndex(const CTableDefine *pDDL) = 0;
public://DML
	virtual const string& AddData(const CDMLParam *pDDL) = 0;
	virtual const string& DelData(const CDMLParam *pDDL) = 0;
	virtual const string& ModifyData(const CDMLParam *pDDL) = 0;
public://Êý¾Ý²éÑ¯
	virtual const string& Find(const CSelectParam *pSelect) = 0;
public:
	virtual const string& ExcutePrcedure(const char* sName, const vector<string>& vcParams,
		map<string, string>& vcReturnValues) = 0;
protected:
	string m_sSql;
	const string& MapToString(const map<string, string>& mpStr, const string& sOutSeparator = ",", 
		const string& sInSeparator = " ");
	const string& MapToString(const map<tp_Column, sConditon>& mpCondtion, const string& sOutSeparator = " and ");
private:
	string m_sMap;
};
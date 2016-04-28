#pragma once
#include "IColumnDefine.h"
#include "codeConvert.h"
struct IDDLParam 
{
	virtual ~IDDLParam()
	{
	}
	virtual void Clear(void) = 0;
	virtual void SetDB(const char* sDBName) = 0;
	void SetDBW(const WCHAR* sDBName)
	{
		SetDB(m_pCodeConvert->ToAnsi(sDBName));
	}
	virtual void SetTableName(const char* sName) = 0;
	const char* GetTableName(const char* sName);
	void SetTableNameW(const WCHAR* sName)
	{
		SetTableName(m_pCodeConvert->ToAnsi(sName));
	}
	virtual IColumnDefine* AddColumn(const char* sColName, tp_data_type dt, long nDataLength = 0) = 0;
	IColumnDefine* AddColumnW(const WCHAR* sColName, tp_data_type dt, long nDataLength = 0)
	{
		return AddColumn(m_pCodeConvert->ToAnsi(sColName), dt, nDataLength);
	}
	virtual void AddKeyCol(const char* sColName) = 0;
	void AddKeyColW(const WCHAR* sColName)
	{
		AddKeyCol(m_pCodeConvert->ToAnsi(sColName));
	}
	virtual void AddForeignKey(const char* sColName, const char* sRefTable, const char* sRefCol) = 0;
	void AddForeignKeyW(const WCHAR* sColName, const WCHAR* sRefTable, const WCHAR* sRefCol)
	{
		AddForeignKey(m_pCodeConvert->ToAnsi(sColName), m_pCodeConvert->ToAnsi(sRefTable), m_pCodeConvert->ToAnsi(sRefCol));
	}
	virtual void AddIndex(const char* sName, bool m_bUnique, bool m_bCluster) = 0;
	void AddIndexW(const WCHAR* sName, bool m_bUnique, bool m_bCluster)
	{
		AddIndex(m_pCodeConvert->ToAnsi(sName), m_bUnique, m_bCluster);
	}
	virtual void AddIndexCol(const char* sIndexName, const char* sCol, bool bDESC = false) = 0;
	void AddIndexColW(const WCHAR* sIndexName, const WCHAR* sCol, bool bDESC = false)
	{
		AddIndexCol(m_pCodeConvert->ToAnsi(sIndexName), m_pCodeConvert->ToAnsi(sCol), bDESC);
	}
	IDDLParam(CodeConvert *pCodeConvert) : m_pCodeConvert(pCodeConvert)
	{

	}
protected:
	CodeConvert *m_pCodeConvert;
};
#pragma once
#include "IColumnDefine.h"
struct IExcuteParam 
{
	virtual void Clear(void) = 0;
	virtual void SetDB(const char* sDBName) = 0;
	virtual void SetTableName(const char* sName) = 0;
	virtual IColumnDefine* AddColumn(const char* sColName, tp_data_type dt, long nDataLength = 0) = 0;
	virtual bool AddKeyCol(const char* sColName) = 0;
	virtual bool AddForeignKey(const char* sColName, const char* sRefTable, const char* sRefCol) = 0;
};
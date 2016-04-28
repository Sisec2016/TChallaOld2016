#ifndef _LOGSEARCH_H_
#define _LOGSEARCH_H_

#include <list>
#include "FileDisk.h"
#include "LogHeader.h"

#include "Poco/Types.h"

namespace Poco 
{

typedef struct
{
	CFileDisk *pLog;
	UInt32 uiLogSz;
}T_LogFilePtr;

class CLogSearch
{
public:
	CLogSearch();
	virtual ~CLogSearch();

public:
	Int32 StartSearchLog(UInt32 startTime, UInt32 endTime, Int16 type);
	void  StopSearchLog();
	Int32 GetSearchLogNum();
	Int32 LoadPuLog(Int32 iNum, LogInfo* pLog);
private:
	CLogSearch(const CLogSearch&);
	void  SearchListClear();

	Int32 ReadSFirIndex(CFileDisk *pFir, T_FirIndex *pFirIndex, Int32 iPos, UInt32 iNum=1);
	Int32 ReadSSecIndex(CFileDisk *pSec,T_SecIndex *pSecIndex, Int32 iPos,UInt32 iNum=1);
	Int32 ReadSLogFile(CFileDisk *pLog, LogInfo* ptLog, Int32 iPos,UInt32 iNum=1);
	Int32 BinarySearch(T_SecIndex * ptSec, UInt32 uiSize, UInt32 uiStart, UInt32 uiEnd, UInt32 uiTime, UInt32 flag);
	Int32 BinarySearchDetail(T_SecIndex * ptSec,UInt32 size,UInt32 start,UInt32 end, UInt32 uiTime,UInt32 flag);
	Int32 IsBetween(UInt32 uiStart, UInt32 uiEnd, UInt32 val);
	void  SearchLogDetail(T_LogFilePtr &tLogFile, T_FirIndex* ptFir, UInt32 uiStartTime, UInt32 uiEndTime, Int16 type);

	Int32 SearchSuitLog(Int32 startTime, Int32 endTime, Int16 type);
	Int32 GetFirIndexNum(CFileDisk *pFir);
private:
	FastMutex m_mutex_search; //主要目的对检索list加锁
	bool m_iSearchRun;		 //判断Search是否已经在Running

	T_LogFilePtr m_pLogPtr;

	typedef  struct _T_SLogIndex
	{
		UInt32 uiLogPos;
		UInt32 uiLogTime;
		CFileDisk *pLog;
	}T_SLogIndex;
	
	typedef std::list<T_SLogIndex> CLOGLISTINDEX;
	CLOGLISTINDEX m_LogIndex;

	T_SecIndex *m_ptSec; // 第二级索引，避免频繁分配堆空间
};

}

#endif


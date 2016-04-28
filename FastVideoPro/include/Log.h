#ifndef _LOG_H_
#define _LOG_H_

#include "FileDisk.h" 
#include "Poco/Types.h"
#include "LogHeader.h"


#define  LOGCONTINUM				(5000)	//一次不分段最大的数目

namespace Poco 
{

class CLog
{
public:
	CLog();
	virtual ~CLog();

public:	
	Int32 Init(const char * pLogName);
	Int32 WriteData(LogInfo* ptLog);
	void  CloseLogFiles();
    
    bool IsRecycle();
	
private:
    CLog(const CLog&);
	Int32 CheckOpenLogFiles(char *pFileName);
	Int32 ReadFirLogIndex(T_FirIndex *pFirIndex,Int32 iPos,UInt32 iNum=1);
	Int32 ReadSecLogIndex(T_SecIndex *pSecIndex, Int32 iPos, UInt32 iNum=1);
	
	Int32 WriteFirIndex(UInt32 iPos,T_FirIndex *pFirIndex, UInt32 iNum=1);
	Int32 WriteLogContent(LogInfo* ptLog, T_SecIndex &tSecIndex);
	void  ParaInit();
	
private:
	
	//记录日志索引和日志文件的当前信息
	UInt32 m_uiCurFirPos;		//第一索引当前位置，记录的是正在写的位置
	UInt32 m_uiFirNum;			//第 一 索 引 数 目
	UInt32 m_uiCurSecNum;		//当 前 数 目
	UInt32 m_uiLogMaxNum;		//可 以 存 储 的 最 大 数 目

	Int32 m_LogStartPos; 		// 记 录 日 志 内 容 开 始 位 置
	Int32 m_SecStartPos; 		// 记 录 第 二 索 引 开 始 位 置

	UInt32 m_iCycle;			//判 断 当 前 是 否 循 环

	T_FirIndex m_tFirIndex;		//记 录 1 个 结 构
	T_FirIndex m_tFirNext;		//记 录 1 个 结 构	
	T_SecIndex m_tSecIndex;
		
	char m_iLogFileName[30];		//日志记录文件名
	
	Int32 m_iLogContiNum;				//不分段连续的数目
	
	CFileDisk* m_pLog;				//日志文件FileDisk

	FastMutex m_mutex_write;

protected:
	UInt32 m_LogFileSz;		//本 log 文 件 大 小
};


}

#endif


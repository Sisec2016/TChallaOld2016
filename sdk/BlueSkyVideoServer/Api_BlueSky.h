#ifndef _Api_BlueSky_H
#define _Api_BlueSky_H
// namespace BlueSky
// {
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include "dvxSdk.h"
// #pragma comment(lib, "dvxSdk.lib")
// }
// using BlueSky::DvxHandle;
// using BlueSky::DumpHandle;
// using BlueSky::ArchEventOpts;
// using BlueSky::FetchResult;
// using BlueSky::RecordDumpOpenPara;
// using BlueSky::ArcItem;
// using BlueSky::DVX_SEARCH_KEY_CHANNEL;
// using BlueSky::DVX_OK;
// using BlueSky::DVX_INDEXTYPE_DVX7_IPC;
// using BlueSky::DVX_NOTIFY_LPARAM_DUMP_END;
// using BlueSky::DVX_NOFIFY_LPARAM_DUMP_DISCONN;
// using BlueSky::RecordPlayOpenPara;
// using BlueSky::PlayHandle;

typedef int (*pdvxSdkInit)();
typedef int (*pdvxSdkDeInit)();
typedef int (*pdvxCreate)( const char* ip, unsigned short nCmdPort, unsigned short nDataPort, const char* szUserName, const char* szPasswd, DvxHandle* pDvr );
typedef int (*pdvxDestory)( DvxHandle hDvx );
typedef int (*pdvxAVExistChannelsGet)(DvxHandle hDvx, NvrGetExistChannels* pOutPara);
typedef int (*pdvxEventOpenATM)(DvxHandle hDvx, ArchEventATMOpts* opts, unsigned int* total, int msTimeout);
typedef int (*pdvxEventClose)(DvxHandle hDvx);
typedef int (*pdvxEventFetch)(DvxHandle hDvx, int rowId, int rowCount, FetchResult* pFetchList);
typedef int (*pdvxRecordDumpOpen)( DvxHandle hDvx, RecordDumpOpenPara* pPara, const char* szFName, HWND hNotifyWnd, unsigned int msgId, DumpHandle* phDump , bool bContinue);
typedef int (*pdvxRecordDumpStart)( DumpHandle hDump );
typedef int (*pdvxRecordDumpStop)( DumpHandle hDump );
typedef int (*pdvxRecordDumpClose)( DumpHandle &hDump );
typedef int (*pdvxRecordDumpGetFileSize)( DumpHandle hDump, __int64 *nSize );
typedef int (*pdvxRecordDumpPos)( DumpHandle hDump, __int64 *nSize );
typedef int (*pdvxRecordOpen)( DvxHandle hDvx, RecordPlayOpenPara* pPara, HWND hPlayWnd,HWND hNotifyWnd, unsigned int msgId, PlayHandle* hPlay );
typedef int (*pdvxRecordPlay)( PlayHandle hPlay );
typedef int (*pdvxRecordPause)( PlayHandle hPlay );
typedef int (*pdvxRecordStop)( PlayHandle hPlay );
typedef int (*pdvxRecordClose)( PlayHandle &hPlay );
typedef int (*pdvxRecordSeek)( PlayHandle hPlay, __int64 ms );
typedef int (*pdvxRecordGetCurrentTime)(PlayHandle hPlay, __int64* ms);
typedef int (*pdvxRecordGetTime)(PlayHandle hPlay, __int64* msBegin, __int64* msEnd);
class Api_BlueSky
{
public:
	Api_BlueSky();
	virtual ~Api_BlueSky();
	static Api_BlueSky& Api();
    int Init();
    int Uninit();
    int Login(const char* ip, unsigned short nCmdPort, unsigned short nDataPort,
        const char* szUserName, const char* szPasswd, DvxHandle* pDvr);
    int Logout(DvxHandle hDvx);
    int GetChannel(DvxHandle hDvx, NvrGetExistChannels* pOutPara);
    int EventOpen(DvxHandle hDvx, ArchEventATMOpts* opts, unsigned int* total, int msTimeout);
    int EventClose(DvxHandle hDvx);
    int EventFetch(DvxHandle hDvx, int rowId, int rowCount, FetchResult* pFetchList);
    int DownloadByFile(DvxHandle hDvx, RecordDumpOpenPara* pPara, const char* szFName,
            HWND hNotifyWnd, unsigned int msgId, DumpHandle* phDump, bool bContinue);
    int DownloadStart(DumpHandle hDump);
    int DownloadStop(DumpHandle hDump);
    int DownloadClose(DumpHandle &hDump);
    int DownloadFileSize(DumpHandle hDump, __int64 *nSize);
    int DownloadPos(DumpHandle hDump, __int64 *nSize);
    int PlayBackOpen(DvxHandle hDvx, RecordPlayOpenPara* pPara, HWND hPlayWnd, HWND hNotifyWnd,
         unsigned int msgId, PlayHandle* hPlay);
    int PlayBackStart(PlayHandle hPlay);
    int PlayBackPause(PlayHandle hPlay);
    int PlayBackStop(PlayHandle hPlay);
    int PlayBackClose(PlayHandle &hPlay);
    int PlayBackSetPos(PlayHandle hPlay, __int64 ms);
    int PlayBackGetPos(PlayHandle hPlay, __int64* ms);
    int RecordGetTime(PlayHandle hPlay, __int64* msBegin, __int64* msEnd);
    void addLog(const char* sLog, int nLine);
protected:
	pdvxSdkInit m_pInit;
	pdvxSdkDeInit m_pUninit;
	pdvxCreate m_pLogin;
	pdvxDestory m_pLogout;
	pdvxAVExistChannelsGet m_pGetChannel;
	pdvxEventOpenATM m_pEventOpen;
	pdvxEventClose m_pEventClose;
	pdvxEventFetch m_pEventFetch;
	pdvxRecordDumpOpen m_pDownloadByFile;
	pdvxRecordDumpStart m_pDownloadStart;
	pdvxRecordDumpStop m_pDownloadStop;
	pdvxRecordDumpClose m_pDownloadClose;
	pdvxRecordDumpGetFileSize m_pDownloadFileSize;
	pdvxRecordDumpPos m_pDownloadPos;
	pdvxRecordOpen m_pPlayBackOpen;
	pdvxRecordPlay m_pPlayBackStart;
	pdvxRecordPause m_pPlayBackPause;
	pdvxRecordStop m_pPlayBackStop;
	pdvxRecordClose m_pPlayBackClose;
	pdvxRecordSeek m_pPlayBackSetPos;
	pdvxRecordGetCurrentTime m_pPlayBackGetPos;
    pdvxRecordGetTime m_pRecordGetTime;
private:
	HMODULE m_hMod;
};
#endif
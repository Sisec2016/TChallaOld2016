#include "Api_BlueSky.h"
#include "Poco/SingletonHolder.h"
#include <assert.h>
#include <string>
#include "IVideoServer.h"
#include "../../VideoServer/log.h"

using namespace std;
#ifdef NDEBUG
#undef NDEBUG
#define RESET_NDEBUG
#endif // NDEBUG

static string GetExePath()
{
	char szPath[MAX_PATH];
	ZeroMemory(szPath, sizeof(szPath));
	HMODULE hIns = GetModuleHandle(NULL);
	assert(hIns);
	GetModuleFileNameA(hIns, szPath, MAX_PATH);
	string strPath = szPath;
	int iIndex = strPath.rfind('\\');
	if (iIndex != string::npos)
	{
		strPath = strPath.substr(0, iIndex+1);
	}
	return strPath;
}




Api_BlueSky::Api_BlueSky()
{
//	char szCurDir[MAX_PATH];
//	ZeroMemory(szCurDir, sizeof(szCurDir));
//	GetCurrentDirectoryA(MAX_PATH, szCurDir);
//	string strPath = GetExePath();
//	strPath += "BlueSky";
//	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
//	assert(bRet);
	m_hMod = LoadLibraryA(".\\dvxSdk.dll");
	if (m_hMod == NULL)
	{
//		bRet = SetCurrentDirectoryA(szCurDir);
//		assert(bRet);
		assert(m_hMod);
		return;
	}
//	bRet = SetCurrentDirectoryA(szCurDir);
//	assert(bRet);

	m_pInit = (pdvxSdkInit)GetProcAddress(m_hMod, "dvxSdkInit");
	assert(m_pInit);
	m_pUninit = (pdvxSdkDeInit)GetProcAddress(m_hMod, "dvxSdkDeInit");
	assert(m_pUninit);
	m_pLogin = (pdvxCreate)GetProcAddress(m_hMod, "dvxCreate");
	assert(m_pLogin);
	m_pLogout = (pdvxDestory)GetProcAddress(m_hMod, "dvxDestory");
	assert(m_pLogout);
	m_pGetChannel = (pdvxAVExistChannelsGet)GetProcAddress(m_hMod, "dvxAVExistChannelsGet");
	assert(m_pGetChannel);
	m_pEventOpen = (pdvxEventOpenATM)GetProcAddress(m_hMod, "dvxEventOpenATM");
	assert(m_pEventOpen);
	m_pEventClose = (pdvxEventClose)GetProcAddress(m_hMod, "dvxEventClose");
	assert(m_pEventClose);
	m_pEventFetch = (pdvxEventFetch)GetProcAddress(m_hMod, "dvxEventFetch");
	assert(m_pEventFetch);
	m_pDownloadByFile = (pdvxRecordDumpOpen)GetProcAddress(m_hMod, "dvxRecordDumpOpen");
	assert(m_pDownloadByFile);
	m_pDownloadStart = (pdvxRecordDumpStart)GetProcAddress(m_hMod, "dvxRecordDumpStart");
	assert(m_pDownloadStart);
	m_pDownloadStop = (pdvxRecordDumpStop)GetProcAddress(m_hMod, "dvxRecordDumpStop");
	assert(m_pDownloadStop);
	m_pDownloadClose = (pdvxRecordDumpClose)GetProcAddress(m_hMod, "dvxRecordDumpClose");
	assert(m_pDownloadClose);
	m_pDownloadFileSize = (pdvxRecordDumpGetFileSize)GetProcAddress(m_hMod, "dvxRecordDumpGetFileSize");
	assert(m_pDownloadFileSize);
	m_pDownloadPos = (pdvxRecordDumpPos)GetProcAddress(m_hMod, "dvxRecordDumpPos");
	assert(m_pDownloadPos);
	m_pPlayBackOpen = (pdvxRecordOpen)GetProcAddress(m_hMod, "dvxRecordOpen");
	assert(m_pPlayBackOpen);
	m_pPlayBackStart = (pdvxRecordPlay)GetProcAddress(m_hMod, "dvxRecordPlay");
	assert(m_pPlayBackStart);
	m_pPlayBackPause = (pdvxRecordPause)GetProcAddress(m_hMod, "dvxRecordPause");
	assert(m_pPlayBackPause);
	m_pPlayBackStop = (pdvxRecordStop)GetProcAddress(m_hMod, "dvxRecordStop");
	assert(m_pPlayBackStop);
	m_pPlayBackClose = (pdvxRecordClose)GetProcAddress(m_hMod, "dvxRecordClose");
	assert(m_pPlayBackClose);
	m_pPlayBackSetPos = (pdvxRecordSeek)GetProcAddress(m_hMod, "dvxRecordSeek");
	assert(m_pPlayBackSetPos);
	m_pPlayBackGetPos = (pdvxRecordGetCurrentTime)GetProcAddress(m_hMod, "dvxRecordGetCurrentTime");
	assert(m_pPlayBackGetPos);
    m_pRecordGetTime = (pdvxRecordGetTime)GetProcAddress(m_hMod, "dvxRecordGetTime");
    assert(m_pRecordGetTime);
} 

Api_BlueSky::~Api_BlueSky()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}
void Api_BlueSky::addLog(const char* sLog, int nLine)
{
    Log::instance().AddLog(QString("%1:%2:%3:%4").arg(__FILE__).arg(__FUNCTION__)
        .arg(nLine).arg(sLog));
}
Api_BlueSky& Api_BlueSky::Api()
{
    static Api_BlueSky *p = nullptr;
    if (nullptr == p)
    {
        p = new Api_BlueSky();
    }

    return *p;
}



int Api_BlueSky::Init(){
    SHE_BEGING
        return this->m_pInit();
    SHE_END_RETURN(-1)
}
int Api_BlueSky::Uninit(){
    SHE_BEGING
        return this->m_pUninit();
    SHE_END_RETURN(-1)
}
int Api_BlueSky::Login(const char* ip, unsigned short nCmdPort, unsigned short nDataPort,
    const char* szUserName, const char* szPasswd, DvxHandle* pDvr){
    SHE_BEGING
        return this->m_pLogin(ip, nCmdPort, nDataPort, szUserName, szPasswd, pDvr);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::Logout(DvxHandle hDvx){
    SHE_BEGING
        return this->m_pLogout(hDvx);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::GetChannel(DvxHandle hDvx, NvrGetExistChannels* pOutPara){
    SHE_BEGING
        return this->m_pGetChannel(hDvx, pOutPara);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::EventOpen(DvxHandle hDvx, ArchEventATMOpts* opts, unsigned int* total, int msTimeout){
    SHE_BEGING
        return this->m_pEventOpen(hDvx, opts, total, msTimeout);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::EventClose(DvxHandle hDvx){
    SHE_BEGING
        return this->m_pEventClose(hDvx);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::EventFetch(DvxHandle hDvx, int rowId, int rowCount, FetchResult* pFetchList){
    SHE_BEGING
        return this->m_pEventFetch(hDvx, rowId, rowCount, pFetchList);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadByFile(DvxHandle hDvx, RecordDumpOpenPara* pPara, const char* szFName,
    HWND hNotifyWnd, unsigned int msgId, DumpHandle* phDump, bool bContinue){
    SHE_BEGING
        return this->m_pDownloadByFile(hDvx, pPara, szFName, hNotifyWnd, msgId, phDump, bContinue);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadStart(DumpHandle hDump){
    SHE_BEGING
        return this->m_pDownloadStart(hDump);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadStop(DumpHandle hDump){
    SHE_BEGING
        return this->m_pDownloadStop(hDump);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadClose(DumpHandle &hDump){
    SHE_BEGING
        return this->m_pDownloadClose(hDump);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadFileSize(DumpHandle hDump, __int64 *nSize){
    SHE_BEGING
        return this->m_pDownloadFileSize(hDump, nSize);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::DownloadPos(DumpHandle hDump, __int64 *nSize){
    SHE_BEGING
        return this->m_pDownloadPos(hDump, nSize);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackOpen(DvxHandle hDvx, RecordPlayOpenPara* pPara, HWND hPlayWnd, HWND hNotifyWnd,
    unsigned int msgId, PlayHandle* hPlay){
    SHE_BEGING
        return this->m_pPlayBackOpen(hDvx, pPara, hPlayWnd, hNotifyWnd, msgId, hPlay);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackStart(PlayHandle hPlay){
    SHE_BEGING
        return this->m_pPlayBackStart(hPlay);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackPause(PlayHandle hPlay){
    SHE_BEGING
        return this->m_pPlayBackPause(hPlay);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackStop(PlayHandle hPlay){
    SHE_BEGING
        return this->m_pPlayBackStop(hPlay);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackClose(PlayHandle &hPlay){
    SHE_BEGING
        return this->m_pPlayBackClose(hPlay);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackSetPos(PlayHandle hPlay, __int64 ms){
    SHE_BEGING
        return this->m_pPlayBackSetPos(hPlay, ms);
    SHE_END_RETURN(-1)
}
int Api_BlueSky::PlayBackGetPos(PlayHandle hPlay, __int64* ms){
    SHE_BEGING
        return this->m_pPlayBackGetPos(hPlay, ms);
    SHE_END_RETURN(-1)
}

int Api_BlueSky::RecordGetTime(PlayHandle hPlay, __int64* msBegin, __int64* msEnd)
{
    SHE_BEGING
        return this->m_pRecordGetTime(hPlay, msBegin, msEnd);
    SHE_END_RETURN(-1)
}

#ifdef RESET_NDEBUG
#define NDEBUG
#endif
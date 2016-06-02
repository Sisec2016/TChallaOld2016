#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <qdatetime.h>
#include <memory>
#include <string>
#include <map>
using std::map;
using std::string;
#include <mutex>
#include <memory>
#include "HISISDK.h"


extern HINSTANCE m_hINSTANCE;
typedef BOOL(WINAPI *PJiuAn_DVR_Init) ();
typedef BOOL(WINAPI *PJiuAn_DVR_Cleanup) ();
typedef LONG(WINAPI *PJiuAn_DVR_Login) (char *sDVRIP, WORD wDVRPort, WORD wHttpPort, char *sUserName, char *sPassword, PHISI_DEVCEINFO lpDeviceInfo);
typedef BOOL(WINAPI *PJiuAn_DVR_Logout) (LONG lUserID);
typedef BOOL(WINAPI *PJiuAn_DVR_GetDVRConfig) (LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
typedef LONG(WINAPI *PJiuAn_DVR_FindFile) (LONG lUserID, LONG lChannel, DWORD dwFileType, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime);
typedef LONG(WINAPI *PJiuAn_DVR_FindNextFile)(LONG lFindHandle, PHISI_DVR_FIND_DATA lpFindData);
typedef BOOL(WINAPI *PJiuAn_DVR_FindClose)(LONG lFindHandle);
typedef LONG(WINAPI *PHISI_DVR_PlayBackByTime) (LONG lUserID, LONG lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, HWND hWnd);
typedef BOOL(WINAPI *PJiuAn_DVR_PlayBackControl) (LONG lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *LPOutValue);
typedef BOOL(WINAPI *PJiuAn_DVR_StopPlayBack) (LONG lPlayHandle);
typedef LONG(WINAPI *PJiuAn_DVR_PlayBackByName)(LONG lUserID, char *sPlayBackFileName, HWND hWnd);
typedef int  (WINAPI *PJiuAn_DVR_GetFileByTime)(int lUserID, int lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, char *sSavedFileName);
typedef LONG(WINAPI *PJiuAn_DVR_GetFileByName)(LONG lUserID, char *sDVRFileName, char *sSavedFileName);
typedef BOOL(WINAPI *PJiuAn_DVR_StopGetFile)(int lFileHandle);
typedef DWORD(WINAPI *PJiuAn_DVR_GetLastError) ();

extern PJiuAn_DVR_Init pJiuAn_DVR_Init;
extern PJiuAn_DVR_Cleanup pJiuAn_DVR_Cleanup;
extern PJiuAn_DVR_Login pJiuAn_DVR_Login;
extern PJiuAn_DVR_GetDVRConfig pJiuAn_DVR_GetDVRConfig;
extern PJiuAn_DVR_Logout pJiuAn_DVR_Logout;
extern PJiuAn_DVR_FindFile pJiuAn_DVR_FindFile;
extern PJiuAn_DVR_FindNextFile pJiuAn_DVR_FindNextFile;
extern PJiuAn_DVR_FindClose pJiuAn_DVR_FindClose;
extern PJiuAn_DVR_GetFileByTime pJiuAn_DVR_GetFileByTime;
extern PJiuAn_DVR_GetFileByName pJiuAn_DVR_GetFileByName;
extern PJiuAn_DVR_StopGetFile pJiuAn_DVR_StopGetFile;
extern PJiuAn_DVR_PlayBackByName pJiuAn_DVR_PlayBackByName;
extern PHISI_DVR_PlayBackByTime pJiuAn_DVR_PlayBackByTime;
extern PJiuAn_DVR_StopPlayBack pJiuAn_DVR_StopPlayBack;
extern PJiuAn_DVR_PlayBackControl pJiuAn_DVR_PlayBackControl;
extern PJiuAn_DVR_GetLastError pJiuAn_DVR_GetLastError;

class CFactory : public IVideoServerFactory
{
public:
    CFactory();
    ~CFactory();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "¾Å°²¹âµç";
    }

    virtual int defaultPort()
    {
        return 80;
    }
    virtual const char* defaultUser()
    {
        return "admin";
    }

    virtual const char* defaultPasswords()
    {
        return "";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_JIUAN;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
      // externs.push_back("h264");
		externs.push_back("mp4");
     //   externs.push_back("dav");
    }

    virtual IVideoServer* create();
private:

    //PJiuAn_DVR_GetLastError pJiuAn_DVR_GetLastError;
};
typedef struct
{
    __time64_t iTotalSize;
    __time64_t iCurSize;
    int iPercent;
}stPos_DownPlay;
class JiuAn_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
    static std::vector<JiuAn_videoserver*> sServers;
public:
    JiuAn_videoserver();
    ~JiuAn_videoserver();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user,
        const char* password, std::map<__int32, std::string>& channels);
    virtual bool logout();
    virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
        __time64_t timeEnd);
    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    bool SetPlayBack(__int64 playbackHandle, __int32 pos);
    virtual bool StopPlayBack(__int64 playbackHandle, __int32 mPause);
    bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
    bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
	void InitRF(__int32 channel, HISI_DVR_FIND_DATA& findInfo, RecordFile& rf);
	void InitTime(HISI_DVR_TIME& struStartTime, HISI_DVR_TIME& struStopTime, __time64_t timeStart, __time64_t timeEnd);
private:
    const RecordFile* m_playFile;
    __time64_t mStartPlayTime;
protected:

    HISI_DEVCEINFO m_deviceInfo;
	
    std::recursive_mutex m_mtxPos;
    std::map<long long, INT64> m_mapDownloadTotalSize;
    std::map<long long, INT64> m_mapDownloadPos;
};


#endif // HIKAN_VIDEOSERVER_H

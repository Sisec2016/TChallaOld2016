#include "JiuAn_videoserver.h"
#include <QObject>
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <time.h>
#include <QStringList>
#include <QThread>
#include <io.h>
#include <tchar.h>
#include <boost/thread/lock_guard.hpp>
#include "excpt.h"
#include "../../VideoServer/log.h"



HINSTANCE m_hINSTANCE;

PJiuAn_DVR_Init pJiuAn_DVR_Init = NULL;
PJiuAn_DVR_Cleanup pJiuAn_DVR_Cleanup = NULL;
PJiuAn_DVR_Login pJiuAn_DVR_Login = NULL;
PJiuAn_DVR_Logout pJiuAn_DVR_Logout = NULL;
PJiuAn_DVR_GetDVRConfig pJiuAn_DVR_GetDVRConfig = NULL;
PJiuAn_DVR_GetFileByTime pJiuAn_DVR_GetFileByTime = NULL;
PJiuAn_DVR_FindFile pJiuAn_DVR_FindFile = NULL;
PJiuAn_DVR_FindNextFile pJiuAn_DVR_FindNextFile = NULL;
PJiuAn_DVR_FindClose pJiuAn_DVR_FindClose = NULL;
PJiuAn_DVR_GetFileByName pJiuAn_DVR_GetFileByName = NULL;
PJiuAn_DVR_StopGetFile pJiuAn_DVR_StopGetFile = NULL;
PJiuAn_DVR_PlayBackByName pJiuAn_DVR_PlayBackByName = NULL;
PJiuAn_DVR_StopPlayBack pJiuAn_DVR_StopPlayBack = NULL;
PJiuAn_DVR_PlayBackControl pJiuAn_DVR_PlayBackControl = NULL;
PJiuAn_DVR_GetLastError pJiuAn_DVR_GetLastError = NULL;
extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{
    Log::instance().initFileName("JiuAn_videoserver");
    return new CFactory();
}

/*
* 构造函数初始化
*
*/
CFactory::CFactory()
{
    init();
}
/*
* 构造函数
*
*/
CFactory::~CFactory()
{
    clean();
}


bool DVR_init()
{
    __try{

        return pJiuAn_DVR_Init();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_init:初始化sdk出错", error);
        std::cout << "SDK-Hisi.DVR_init:初始化sdk出错";
        return false;
    }
}

/*
*  初始化SDK
*/
bool CFactory::init()
{
    if (!m_init)
    {
        if (m_hINSTANCE == NULL)
        {
            m_hINSTANCE = LoadLibraryA(LPCSTR("HISISDK.dll"));
        }
        if (m_hINSTANCE == NULL)
        {
            m_sLastError = "无法加载动态链接库";
            Log::instance().AddLog(m_sLastError);
            return false;
        }

        pJiuAn_DVR_Cleanup = (PJiuAn_DVR_Cleanup)GetProcAddress(m_hINSTANCE, "HISI_DVR_Cleanup");
        if (NULL == pJiuAn_DVR_Cleanup)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_Cleanup";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_Init = (PJiuAn_DVR_Init)GetProcAddress(m_hINSTANCE, "HISI_DVR_Init");
        if (NULL == pJiuAn_DVR_Init)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_Init";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_Login = (PJiuAn_DVR_Login)GetProcAddress(m_hINSTANCE, "HISI_DVR_Login");
        if (NULL == pJiuAn_DVR_Login)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_Login";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_Logout = (PJiuAn_DVR_Logout)GetProcAddress(m_hINSTANCE, "HISI_DVR_Logout");
        if (NULL == pJiuAn_DVR_Logout)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_Logout";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_GetDVRConfig = (PJiuAn_DVR_GetDVRConfig)GetProcAddress(m_hINSTANCE, "HISI_DVR_GetDVRConfig");
        if (NULL == pJiuAn_DVR_GetDVRConfig)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_GetDVRConfig";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_GetFileByTime = (PJiuAn_DVR_GetFileByTime)GetProcAddress(m_hINSTANCE, "HISI_DVR_GetFileByTime");
        if (NULL == pJiuAn_DVR_GetFileByTime)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_GetFileByTime";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_FindFile = (PJiuAn_DVR_FindFile)GetProcAddress(m_hINSTANCE, "HISI_DVR_FindFile");
        if (NULL == pJiuAn_DVR_FindFile)
        {
            m_sLastError = "无法加载动态链接库::HISI_DVR_FindFile";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_FindNextFile = (PJiuAn_DVR_FindNextFile)GetProcAddress(m_hINSTANCE, "HISI_DVR_FindNextFile");
        if (NULL == pJiuAn_DVR_FindNextFile)
        {
            m_sLastError = "无法加载动态链接库::HISI_DVR_FindNextFile";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_FindClose = (PJiuAn_DVR_FindClose)GetProcAddress(m_hINSTANCE, "HISI_DVR_FindClose");
        if (NULL == pJiuAn_DVR_FindClose)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_FindClose";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_GetFileByName = (PJiuAn_DVR_GetFileByName)GetProcAddress(m_hINSTANCE, "HISI_DVR_GetFileByName");
        if (NULL == pJiuAn_DVR_GetFileByName)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_GetFileByName";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_StopGetFile = (PJiuAn_DVR_StopGetFile)GetProcAddress(m_hINSTANCE, "HISI_DVR_StopGetFile");
        if (NULL == pJiuAn_DVR_StopGetFile)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_StopGetFile";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_PlayBackByName = (PJiuAn_DVR_PlayBackByName)GetProcAddress(m_hINSTANCE, "HISI_DVR_PlayBackByName");
        if (NULL == pJiuAn_DVR_PlayBackByName)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_PlayBackByName";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_StopPlayBack = (PJiuAn_DVR_StopPlayBack)GetProcAddress(m_hINSTANCE, "HISI_DVR_StopPlayBack");
        if (NULL == pJiuAn_DVR_StopPlayBack)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_StopPlayBack";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_PlayBackControl = (PJiuAn_DVR_PlayBackControl)GetProcAddress(m_hINSTANCE, "HISI_DVR_PlayBackControl");
        if (NULL == pJiuAn_DVR_PlayBackControl)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_PlayBackControl";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }
        pJiuAn_DVR_GetLastError = (PJiuAn_DVR_GetLastError)GetProcAddress(m_hINSTANCE, "HISI_DVR_GetLastError");
        if (NULL == pJiuAn_DVR_GetLastError)
        {
            m_sLastError = "无法加载动态链接库::pJiuAn_DVR_GetLastError";
            Log::instance().AddLog(m_sLastError);
            FreeLibrary(m_hINSTANCE);
            return false;
        }




        m_init = DVR_init();
        if (!m_init)
        {
            m_sLastError = "初始化失败";
            Log::instance().AddLog(m_sLastError);
        }
    }

    return m_init;
}

bool DVR_clean()
{
    __try{

        return pJiuAn_DVR_Cleanup();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_clean:卸载sdk出错", error);
        std::cout << "SDK-Hisi.DVR_clean:卸载sdk出错";
        return false;
    }
}
/*
* 释放SDK
*/
void CFactory::clean()
{
    DVR_clean();
    FreeLibrary(m_hINSTANCE);
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new JiuAn_videoserver();
}


std::vector<JiuAn_videoserver*> JiuAn_videoserver::sServers;
std::recursive_mutex JiuAn_videoserver::sMtServers;

/*
* 析构函数
*/
JiuAn_videoserver::JiuAn_videoserver()
{
}
/*
* 析构函数
*/
JiuAn_videoserver::~JiuAn_videoserver()
{
    logout();
}

DWORD DVR_GetLastError()
{
    __try{

        return pJiuAn_DVR_GetLastError();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_GetLastError:获取错误代码出错", error);
        return -1;
    }
}

std::string GetLastErrorString()
{
    DWORD dwErr = DVR_GetLastError();

    switch (dwErr)
    {
    case HISI_DVR_NOERROR: return "没有错误";
    case HISI_DVR_PASSWORD_ERROR: return "用户名密码错误";
    case HISI_DVR_NETWORK_FAIL_CONNECT: return "连接服务器失败";
    case HISI_COMM_EXCEPTION: return "通用异常消息";
    case HISI_COMM_ALARM: return "通用报警消息";
    case HISI_ALARM_WIRELESS: return "无线模块报警消息";
    case HISI_ALARM_UPS: return "UPS报警消息";
    case HISI_EXCEPTION_EXCHANGE: return "用户交互时异常";
    case HISI_EXCEPTION_AUDIOEXCHANGE: return "语音对讲异常";
    case HISI_EXCEPTION_ALARM: return "报警异常";
    case HISI_EXCEPTION_PREVIEW: return "网络预览异常";
    case HISI_EXCEPTION_ORDERCALL: return "调用顺序错误";
    case HISI_EXCEPTION_RECONNECT: return "预览时重连";
    case HISI_EXCEPTION_ALARMRECONNECT: return "报警时重连";
    case HISI_EXCEPTION_NOTINIT: return "未调用初始化";
    case HISI_EXCEPTION_GETVIDEOPORT: return "获取视频端口失败";
    case HISI_EXCEPTION_GETHTTPPORT: return "获取HTTP服务器端口失败";
    case HISI_EXCEPTION_PLAYBACK: return "回放异常";
    case HISI_EXCEPTION_NOPLAYHANDLE: return "无播放器句柄";
    case HISI_EXCEPTION_EXMAXCHANNEL: return "超过最大通道号";
    case HISI_EXCEPTION_NETERROR: return "网络异常";
    case HISI_EXCEPTION_ORDER: return "函数调用顺序错误";
    case HISI_EXCEPTION_MAXPLAY: return "达到最大播放数";
    case HISI_EXCEPTION_EXMAXVALUE: return "超出最大值";
    case HISI_EXCEPTION_INVALIDHANDLE: return "无效的句柄";
    default: return "未知错误";
    }

    return "";
}


IVideoServer* JiuAn_videoserver::clone()
{
    JiuAn_videoserver *svr = new JiuAn_videoserver();
    return svr;
}

LONG DVR_Login(char *sDVRIP, WORD wDVRPort, WORD wHttpPort, char *sUserName, char *sPassword, PHISI_DEVCEINFO lpDeviceInfo)
{
    __try{

        return pJiuAn_DVR_Login(sDVRIP, wDVRPort, wHttpPort, sUserName, sPassword, lpDeviceInfo);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("DVR_Login:DVR_Login");
        return -1;
    }
}

bool GetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned)
{
    __try{

        return pJiuAn_DVR_GetDVRConfig(lUserID, dwCommand, lChannel, lpOutBuffer, dwOutBufferSize, lpBytesReturned);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}

bool JiuAn_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels)
{
    channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));
    char cPort[16] = { 0 };
    sprintf_s(cPort, "%d", port);
    Log::instance().AddLog(string(IP) + " " + string(user) + " " + string(password) + " " + cPort);
    m_lLoginHandle = DVR_Login((char*)IP, port, port,
        (char*)user, (char*)password,
        &m_deviceInfo);
    if (m_lLoginHandle == -1)
    {
        m_sLastError = GetLastErrorString();
        Log::instance().AddLog(string("[1]login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

    //以下为查询通过数代码,m_deviceInfo中的通道数无效
    DWORD nRcvBytes = 0;
    PHISI_DEVINFO devInfo;
    memset(&devInfo, 0, sizeof(PHISI_DEVINFO));
    BOOL bRes = GetDVRConfig(m_lLoginHandle, HISI_DVR_GET_DEVICECFG, -1, &devInfo, sizeof(PHISI_DEVINFO), &nRcvBytes);
    if (bRes == FALSE)
    {
        m_sLastError = GetLastErrorString();
        Log::instance().AddLog(string("[2]login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

    char strNum[16] = { 0 };
    sprintf_s(strNum, "ChanNum:%d", devInfo.camcnt);
    Log::instance().AddLog(string(strNum));
    char szName[32];
    for (int i = 1; i <= devInfo.camcnt; i++)
    {
        ZeroMemory(szName, 32);
        sprintf(szName, "通道%d", i);
        channels[i] = std::string(szName);
    }


    return true;
}

bool DVR_Logout(LONG lUserID)
{
    __try{

        return pJiuAn_DVR_Logout(lUserID);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_Logout:登出出错 ", error);
        std::cout << "SDK-Hisi.DVR_Logout:登出出错";
        return false;
    }
}

bool JiuAn_videoserver::logout()
{
    if (m_lLoginHandle >= 0 && !DVR_Logout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}


LONG DVR_FindFile(LONG lUserID, LONG lChannel, DWORD dwFileType, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime)
{
    __try{

        return pJiuAn_DVR_FindFile(lUserID, lChannel, dwFileType, lpStartTime, lpStopTime);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("DVR_FindFile EXCEPTION_EXECUTE_HANDLER");
        return -1;
    }
}
LONG DVR_FindNextFile(LONG lFindHandle, PHISI_DVR_FIND_DATA lpFindData)
{
    __try{

        return pJiuAn_DVR_FindNextFile(lFindHandle, lpFindData);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("DVR_FindNextFile EXCEPTION_EXECUTE_HANDLER");
        return -1;
    }
}
bool DVR_FindClose(LONG lFindHandle)
{
    __try{

        return pJiuAn_DVR_FindClose(lFindHandle);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("DVR_FindClose EXCEPTION_EXECUTE_HANDLER");
        return false;
    }
}
LONG DVR_GetFileByName(LONG lUserID, char *sDVRFileName, char *sSavedFileName)
{
    __try{

        return pJiuAn_DVR_GetFileByName(lUserID, sDVRFileName, sSavedFileName);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_GetFileByName:下载文件出错 ", error);
        return -1;
    }
}
LONG DVR_GetFileByTime(LONG lUserID, int channel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, char *sSavedFileName)
{
    __try{

        return pJiuAn_DVR_GetFileByTime(lUserID, channel, lpStartTime, lpStopTime, sSavedFileName);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_GetFileByName:下载文件出错 ", error);
        std::cout << "SDK-Hisi.DVR_GetFileByName:下载文件出错";
        return -1;
    }
}
bool JiuAn_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
    __time64_t timeEnd)
{
	if (m_lLoginHandle <= 0) return false;
	if (timeStart >= timeEnd) return false;

    files.clear();
	HISI_DVR_TIME struStartTime, struStopTime;
	HISI_DVR_TIME struStartTimeTemp, struEveryDayTime;
	InitTime(struStartTime, struStopTime, timeStart, timeEnd);	
	
	struStartTimeTemp = struStartTime;
	struEveryDayTime = struStopTime;

	if (struStopTime.dwDay > struStartTime.dwDay)
	{
		struEveryDayTime.dwDay = struStartTime.dwDay;
		struEveryDayTime.dwHour = 23;
		struEveryDayTime.dwMinute = 59;
		struEveryDayTime.dwSecond = 59;
	}

    __int32 nChannelId = 0;
	for (; struStartTime.dwDay <= struStopTime.dwDay; struStartTime.dwDay += 1, struEveryDayTime.dwDay += 1){
		if (struEveryDayTime.dwDay == struStopTime.dwDay)
		{
			struEveryDayTime = struStopTime;
		}
		if (struStartTimeTemp.dwDay != struStartTime.dwDay)
		{
			struStartTime.dwHour = 0;
			struStartTime.dwMinute = 0;
			struStartTime.dwSecond = 0;
		}
		for (int ch = 0; ch < channelVec.size(); ch++)
		{
			nChannelId = channelVec[ch];

			LONG lfind = DVR_FindFile(m_lLoginHandle, nChannelId, rt_all, &struStartTime, &struEveryDayTime);			
			if (lfind == 0) {
                m_sLastError = GetLastErrorString();
                Log::instance().AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
                continue;
            }
		
			HISI_DVR_FIND_DATA findInfo;
            do 
            {
                ZeroMemory(&findInfo, sizeof(findInfo));
                LONG re = DVR_FindNextFile(lfind, &findInfo);
                if (re == HISI_DVR_ISFINDING) {
                    ::Sleep(20);
                    continue;
                }

                if (re != HISI_DVR_FILE_SUCCESS){
                    Log::instance().AddLog(QString("re != HISI_DVR_ISFINDING re: %1").arg(re));
                    break;
                }

                RecordFile rf;
                InitRF(nChannelId, findInfo, rf);

                if (findInfo.dwFileSize == 0)
                {
                    LONG hdl = DVR_GetFileByTime(m_lLoginHandle, rf.channel, &findInfo.struStartTime, &findInfo.struStopTime, (char*)"C:/test.h263");

                    hdl < 0 ? rf.size = 0 : rf.size = (rf.endTime - rf.beginTime) * 18083;
                    pJiuAn_DVR_StopGetFile(hdl);
                }
                else{
                    rf.size = findInfo.dwFileSize;
                }

                if (rf.size > 0)
                {
                    rf.setPrivateData(&findInfo, sizeof(HISI_DVR_FIND_DATA));
                    files.push_back(rf);
                }
                
            } while (true);
		}
	}
	

    Log::instance().AddLog(string("GetRecordFileList done"));
    return true;
}


void JiuAn_videoserver::InitRF(__int32 channel, HISI_DVR_FIND_DATA& findInfo, RecordFile& rf)
{
	struct tm Tm;
	Tm.tm_year = findInfo.struStartTime.dwYear - 1900;
	Tm.tm_mon = findInfo.struStartTime.dwMonth - 1;
	Tm.tm_mday = findInfo.struStartTime.dwDay;
	Tm.tm_hour = findInfo.struStartTime.dwHour;
	Tm.tm_min = findInfo.struStartTime.dwMinute;
	Tm.tm_sec = findInfo.struStartTime.dwSecond;
	rf.beginTime = _mktime64(&Tm);

	Tm.tm_year = findInfo.struStopTime.dwYear - 1900;
	Tm.tm_mon = findInfo.struStopTime.dwMonth - 1;
	Tm.tm_mday = findInfo.struStopTime.dwDay;
	Tm.tm_hour = findInfo.struStopTime.dwHour;
	Tm.tm_min = findInfo.struStopTime.dwMinute;
	Tm.tm_sec = findInfo.struStopTime.dwSecond;
	rf.endTime = _mktime64(&Tm);

	rf.channel = channel;
	rf.name = findInfo.sFileName;
}

void JiuAn_videoserver::InitTime(HISI_DVR_TIME& struStartTime, HISI_DVR_TIME& struStopTime, __time64_t timeStart, __time64_t timeEnd)
{
	struct tm Tm;

	_localtime64_s(&Tm, (const time_t*)&timeStart);
	struStartTime.dwYear = Tm.tm_year + 1900;
	struStartTime.dwMonth = Tm.tm_mon + 1;
	struStartTime.dwDay = Tm.tm_mday;
	struStartTime.dwHour = Tm.tm_hour;
	struStartTime.dwMinute = Tm.tm_min;
	struStartTime.dwSecond = Tm.tm_sec;

	_localtime64_s(&Tm, (const time_t*)&timeEnd);
	struStopTime.dwYear = Tm.tm_year + 1900;
	struStopTime.dwMonth = Tm.tm_mon + 1;
	struStopTime.dwDay = Tm.tm_mday;
	struStopTime.dwHour = Tm.tm_hour;
	struStopTime.dwMinute = Tm.tm_min;
	struStopTime.dwSecond = Tm.tm_sec;
}

bool JiuAn_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        Log::instance().AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

    HISI_DVR_FIND_DATA* pData = (HISI_DVR_FIND_DATA *)file.getPrivateData();
    //hdl = DVR_GetFileByName(m_lLoginHandle, pData->sFileName, (char*)saveFileName);
    hdl = DVR_GetFileByTime(m_lLoginHandle, file.channel, &pData->struStartTime, &pData->struStopTime, (char*)saveFileName);

    if (hdl < 0)
    {
        m_sLastError = GetLastErrorString();
        Log::instance().AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(m_mtxPos);
    m_mapDownloadTotalSize[hdl] = file.size;
    return true;
}


bool DVR_StopGetFile(LONG lFileHandle)
{
    __try{

        return pJiuAn_DVR_StopGetFile(lFileHandle);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}

bool JiuAn_videoserver::stopDownload(download_handle_t h)
{
    Log::instance().AddLog(string("stopDownload 开始停止下载"));
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        Log::instance().AddLog(string("stopDownload 请先登录"));
        return false;
    }

    if (FALSE == DVR_StopGetFile(h))
    {
        m_sLastError = GetLastErrorString();
        Log::instance().AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(m_mtxPos);
    m_mapDownloadTotalSize.erase(h);
    m_mapDownloadPos.erase(h);
    return true;
}

LONG DVR_PlayBackByName(LONG lUserID, char *sPlayBackFileName, HWND hWnd)
{
    __try{

        return pJiuAn_DVR_PlayBackByName(lUserID, sPlayBackFileName, hWnd);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_PlayBackByName:播放文件出错 ", error);
        std::cout << "SDK-Hisi.DVR_PlayBackByName:播放文件出错";
        return -1;
    }
}
bool DVR_StopPlayBack(LONG lPlayHandle)
{
    __try{

        return pJiuAn_DVR_StopPlayBack(lPlayHandle);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}

bool  JiuAn_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }



    playbackHandle = DVR_PlayBackByName(m_lLoginHandle, (char *)(file.name.c_str()), hwnd);
    if (playbackHandle == 0)
    {
        DVR_StopPlayBack(playbackHandle);
    }

    return playbackHandle != 0;
}


bool JiuAn_videoserver::SetPlayBack(qint64 playbackHandle, qint32 pos)
{
    m_sLastError = "不支持!";
    return false;
}

bool DVR_PlayBackControl(LONG lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *LPOutValue)
{
    __try{

        return pJiuAn_DVR_PlayBackControl(lPlayHandle, dwControlCode, dwInValue, LPOutValue);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::add("SDK-Hisi.DVR_PlayBackControl:获取播放或下载进度出错 ", error);
        std::cout << "SDK-Hisi.DVR_PlayBackControl:获取播放或下载进度出错";
        return false;
    }
}
/*
* 获得播放进度
*/
bool JiuAn_videoserver::getPlayBackPos(qint64 playbackHandle, qint32* pos)
{
    DWORD dwFilePos;
    DVR_PlayBackControl(playbackHandle, HISI_DVR_PLAYGETPOS, 0, &dwFilePos);
    *pos = dwFilePos;
    return true;
}

/*
* 停止视频预览
*/
bool JiuAn_videoserver::StopPlayBack(qint64 playbackHandle, qint32 mPause)
{
    std::lock_guard<std::recursive_mutex> lock(sMtServers);
    if (!DVR_StopPlayBack(playbackHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}

/*
* 获得下载进度
*/
bool JiuAn_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        Log::instance().AddLog(string("getDownloadPos 请先登录"));
        return false;
    }

    DWORD pos = 0;
    bool bRet = DVR_PlayBackControl(h, HISI_DVR_PLAYGETPOS, 0, &pos);
    if (!bRet)
    {
        m_sLastError = GetLastErrorString();
        Log::instance().AddLog(string("getDownloadPos 获取进度失败") + m_sLastError);
        *failed = false;
        return false;
    }
    
    std::lock_guard<std::recursive_mutex> lock(m_mtxPos);
    if (m_mapDownloadPos.find(h) == m_mapDownloadPos.end())
    {
        m_mapDownloadPos[h] = 0;
    }
    auto itr = m_mapDownloadTotalSize.find(h);
    if (itr != m_mapDownloadTotalSize.end())
    {
        *totalSize = itr->second;
        *currentSize = *totalSize * (pos) / 100;
        if (*currentSize - m_mapDownloadPos[h] < 1024){
            if (*totalSize - m_mapDownloadPos[h] > 1024 * 600)
            {
                m_mapDownloadPos[h] += 1024 * 500;
            }
            else{
                m_mapDownloadPos[h] += 1024;
            }
            
            *currentSize = m_mapDownloadPos[h];
        }
        else{
            m_mapDownloadPos[h] = *currentSize;
        }
        *failed = false;
        return true;
    }

    m_sLastError = "找不到该下载文件";
    Log::instance().AddLog(string("getDownloadPos 找不到该下载文件"));
    *failed = false;
    return false;
}




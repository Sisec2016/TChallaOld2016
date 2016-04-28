#include "tdy_videoserver.h"
#include "../../VideoServer/log.h"

#include <iostream>

#include <time.h>
#include <io.h>


Log g_log("TianDiWeiYe_videoserver");

HWND g_hwnd = NULL;
int g_iPlayID = -1;
int g_gloadPlayLen = 0;

HANDLE g_hEventLogon = CreateEventA(NULL, FALSE, FALSE, NULL);
HANDLE g_hEventSearch = CreateEventA(NULL, FALSE, FALSE, NULL);
HANDLE g_hEventDown = CreateEventA(NULL, FALSE, FALSE, NULL);

void __stdcall DownloadNotify(unsigned long _ulID, unsigned char* _ucData, int _iLen, int _iFlag, void* _lpUserData)
{
//	int iPlayID = -1;
	char strPlayID[16] = { 0 };

	if (_iFlag == 1)//处理文件头
	{
/*		g_log.AddLog(string("[1]DownloadNotify!"));*/
		g_iPlayID = TC_CreatePlayerFromVoD(g_hwnd, _ucData, _iLen);//创建VOD播放器
// 		sprintf_s(strPlayID, "iPlayID:%d", g_iPlayID);
// 		g_log.AddLog(string("[2]DownloadNotify!") + strPlayID);

		if (g_iPlayID >= 0)
		{
			TC_Play(g_iPlayID);//播放
			g_gloadPlayLen = g_gloadPlayLen + _iLen;
		}
		else
		{
			printf("CreatePlayerFromVoD failed!\n");
		}
	}
	else//处理数据
	{
// 		sprintf_s(strPlayID, "iPlayID:%d", g_iPlayID);
// 		g_log.AddLog(string("[3]DownloadNotify!") + strPlayID);
		TC_PutStreamToPlayer(g_iPlayID, _ucData, _iLen);
		g_gloadPlayLen = g_gloadPlayLen + _iLen;
		//CheckStatus();
	}
}


std::map<int, HANDLE> g_mapLinkidEvent;

Mutex g_mtxLinkidEvent;
int g_iLogonID = -1;
void Notify_Main(int _iLogonID, int  _iWparam, int  _iLParam, int _iUserData)
{
	int iMsgType = LOWORD(_iWparam);

	char temStr[32] = { 0 };
	sprintf(temStr, "iMsgType:%d, _iUserData:%d", iMsgType, _iUserData);
	g_log.AddLog("Notify_Main:" + string(temStr));

	switch (iMsgType)
	{
		case WCM_LOGON_NOTIFY:
		{
			printf("WCM_LOGON_NOTIFY\n");
			if (_iLParam == LOGON_SUCCESS)
			{
				//SetEvent(g_hEventLogon);
				Mutex::ScopedLock lock(g_mtxLinkidEvent);
				std::map<int, HANDLE>::iterator itr = g_mapLinkidEvent.find(_iLogonID);
				if (itr != g_mapLinkidEvent.end())
				{
					HANDLE h = itr->second;
					SetEvent(h);
				}
			}
			else
			{

			}
			break;
		}
		case WCM_QUERYFILE_FINISHED:
		{
                NVS_IPAndID *pNvs = (NVS_IPAndID *)_iLParam;
                if (pNvs)
                {
                    int iLogonID = *pNvs->m_piLogonID;
                    if (iLogonID == g_iLogonID)
                    {
                        SetEvent(g_hEventSearch);
                    }
                    
                }
			
			break;
		}
		case WCM_DWONLOAD_FINISHED:
		{
			printf("WCM_DWONLOAD_FINISHED\n");
			SetEvent(g_hEventDown);
			break;
		}
		case WCM_DWONLOAD_FAULT:
		{
			printf("WCM_DWONLOAD_FAULT\n");
			break;
		}
		case WCM_DOWNLOAD_INTERRUPT:
		{
			printf("WCM_DOWNLOAD_INTERRUPT\n");
			break;
		}
		default:
		    break;
	}
}


extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{
	return new CTDYFactory();
}

std::string GetLastErrorString()
{
	return "NO ERROR";
}



CTDYFactory::CTDYFactory()
{
	g_log.AddLog(string("CTDYFactory::CTDYFactory()!"));
    init();
}

CTDYFactory::~CTDYFactory()
{
    clean();
}

bool CTDYFactory::init()
{

    if (!m_init)
    {
		LoadNVSSDK();
		LoadPlaySdk();
		g_log.AddLog(string("CTDYFactory::init()"));
        NetClient_SetNotifyFunction_V4(Notify_Main, NULL, NULL, NULL, NULL);//设置回调函数
        TC_CreateSystem(0);//创建播放系统
		int ret = NetClient_Startup_V4(3000, 6000, 0);
		if (ret == 0)
		{
			m_init = true;
		}
		g_log.AddLog(string("CTDYFactory::init() NetClient_Startup_V4! after"));
// 		NetClient_SetNotifyFunction_V4(Notify_Main, NULL, NULL, NULL, NULL);//设置回调函数
// 		TC_CreateSystem(0);//创建播放系统
    }

    return m_init;
}


void CTDYFactory::clean()
{
	TC_DeleteSystem();//删除播放器系统

	FreePlaySdk();

	NetClient_Cleanup();

	FreeNVSSDK();
	m_init = false;
}




IVideoServer* CTDYFactory::create()
{
    if (!init())
    {
		g_log.AddLog(string("IVideoServer* CTDYFactory::create() return nullptr"));
        return nullptr;
    }
	g_log.AddLog(string("IVideoServer* CTDYFactory::create()"));
    return new tdy_videoserver();
}


// std::vector<tdy_videoserver*> tdy_videoserver::sServers;
// std::recursive_mutex tdy_videoserver::sMtServers;

/*
 * 析构函数
 */
tdy_videoserver::tdy_videoserver()
{
// 	std::lock_guard<std::recursive_mutex> lock(tdy_videoserver::sMtServers);
//     sServers.push_back(this);
	m_iLogonID = -1;

}

tdy_videoserver::~tdy_videoserver()
{
    logout();
// 	std::lock_guard<std::recursive_mutex> lock(tdy_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

IVideoServer* tdy_videoserver::clone()
{
	return nullptr;
	tdy_videoserver *svr = new tdy_videoserver();
    return svr;
}

bool tdy_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    if (m_iLogonID >= 0)
    {
        return true;
    }
	char iLogonID[32] = { 0 };
	sprintf(iLogonID, "%d", m_iLogonID);
	char addThis[32] = { 0 };
	sprintf(addThis, "%d", this);
	g_log.AddLog(string("[1]tdy_videoserver::login!") + iLogonID + ", this:" + addThis + " " + IP);

    int newLogin = NetClient_Logon(NULL, (char *)IP, (char *)user, (char *)password, NULL, port);
    if (newLogin < 0)
    {
        return false;
    }
    else{
        logout();
        m_iLogonID = newLogin;
    }
	m_lLoginHandle = m_iLogonID;
	char temStr[32] = { 0 };
	sprintf(temStr, "%d", m_iLogonID);
	
	
	{
		Mutex::ScopedLock lock(g_mtxLinkidEvent);
		std::map<int, HANDLE>::iterator itr = g_mapLinkidEvent.find(m_iLogonID);
		if (itr == g_mapLinkidEvent.end())
		{
            HANDLE hConnectEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
            g_mapLinkidEvent.insert(std::make_pair(m_iLogonID, hConnectEvent));
		}
		
	}

    DWORD dwRet = WaitForSingleObject(g_mapLinkidEvent[m_iLogonID], 5 * 1000);
	char temRet[32] = { 0 };
	sprintf(temRet, "%d", dwRet);
	g_log.AddLog(string("tdy_videoserver::login OK!m_iLogonID = ") + string(temStr) + string("-") + string(temRet));
	int iChinnalNum = 0;
	int usrNum = 0;
	if (dwRet == WAIT_OBJECT_0)
	{
		g_log.AddLog(string("tdy_videoserver::login OK!"));
		int ret = -1;
		ret = NetClient_GetChannelNum(m_iLogonID, &iChinnalNum);
		//int a = NetClient_GetMaxConUser(m_iLogonID, usrNum);
		if (ret != 0)
		{
			g_log.AddLog(string("tdy_videoserver::NetClient_GetChannelNum error!"));
		}
		else
		{
			char cusrNum[32] = { 0 };
			sprintf_s(cusrNum, "%d", usrNum);
			g_log.AddLog(string("tdy_videoserver::NetClient_GetChannelNum OK!") + "cusrNum:" + cusrNum);
			channels.clear();
			char szName[32 + 2];
			for (int i = 0; i < iChinnalNum; i++)
			{
				ZeroMemory(szName, sizeof(szName));
				sprintf(szName, "通道%d", i+1);
				string strName = szName;
				channels.insert(std::make_pair(i, strName));
			}
			/*m_lLoginHandle += 1;*/
		}
	}
	else
	{
		DWORD dwRet = GetLastError();
		char temRet[32] = { 0 };
		sprintf(temRet, "%d", dwRet);
		g_log.AddLog(string("tdy_videoserver::login Failed!") + temRet);
		return false;
	}


    return true;
}

bool tdy_videoserver::logout()
{
	char addThis[32] = { 0 };
	sprintf(addThis, "%d", this);

	if (m_iLogonID >= 0)
    {
		NetClient_Logoff(m_iLogonID);//注销用户
        Mutex::ScopedLock lock(g_mtxLinkidEvent);
        std::map<int, HANDLE>::iterator itr = g_mapLinkidEvent.find(m_iLogonID);
        if (itr != g_mapLinkidEvent.end())
        {
            HANDLE h = itr->second;
            CloseHandle(h);
            g_mapLinkidEvent.erase(itr);
        }
	}
	g_log.AddLog(string("[2]IVideoServer* CTDYFactory::logout() this") + addThis);
	m_iLogonID = -1;
	m_lLoginHandle = m_iLogonID;
    return true;
}

bool tdy_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart, __time64_t timeEnd)
{
	char iLogonID[32] = { 0 };
	sprintf(iLogonID, "%d", m_iLogonID);
	char addThis[32] = { 0 };
	sprintf(addThis, "%d", this);
	g_log.AddLog(string("[1]tdy_videoserver::GetRecordFileList!") + iLogonID + ", this:" + addThis);

	if (m_iLogonID < 0)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    if (timeStart >= timeEnd)
    {
        m_sLastError = "时间范围不对!";

        return false;
    }

	char cTemp[256] = { 0 };
    NVS_FILE_QUERY_EX fileQuery;
	memset(&fileQuery, 0, sizeof(fileQuery));

/*	fileQuery.iChannel = nChannelId;*/
    fileQuery.fileQuery.iType = 0xFF;
    fileQuery.fileQuery.iFiletype = 0;                  //0: All 1: AVstream 2: picture
    fileQuery.fileQuery.iPageNo = 0;
    fileQuery.fileQuery.iPageSize = 20;

	tm STime;
	tm ETime;
	tm *pSTime = &STime;
	tm *pETime = &ETime;

	_localtime64_s(&STime, (const time_t*)&timeStart);
    fileQuery.fileQuery.struStartTime.iYear = STime.tm_year + 1900;
    fileQuery.fileQuery.struStartTime.iMonth = STime.tm_mon + 1;
    fileQuery.fileQuery.struStartTime.iDay = STime.tm_mday;
    fileQuery.fileQuery.struStartTime.iHour = STime.tm_hour;
    fileQuery.fileQuery.struStartTime.iMinute = STime.tm_min;
    fileQuery.fileQuery.struStartTime.iSecond = STime.tm_sec;

	char starTime[32] = { 0 };
    sprintf(starTime, "%d-%d-%d %d:%d:%d", fileQuery.fileQuery.struStartTime.iYear, fileQuery.fileQuery.struStartTime.iMonth, fileQuery.fileQuery.struStartTime.iDay, fileQuery.fileQuery.struStartTime.iHour,
        fileQuery.fileQuery.struStartTime.iMinute, fileQuery.fileQuery.struStartTime.iSecond);
	g_log.AddLog(string("GetRecordFileList, starTime:") + string(starTime));

	_localtime64_s(&ETime, (const time_t*)&timeEnd);
    fileQuery.fileQuery.struStopTime.iYear = ETime.tm_year + 1900;
    fileQuery.fileQuery.struStopTime.iMonth = ETime.tm_mon + 1;
    fileQuery.fileQuery.struStopTime.iDay = ETime.tm_mday;
    fileQuery.fileQuery.struStopTime.iHour = ETime.tm_hour;
    fileQuery.fileQuery.struStopTime.iMinute = ETime.tm_min;
    fileQuery.fileQuery.struStopTime.iSecond = ETime.tm_sec;

	char stopTime[32] = { 0 };
    sprintf(stopTime, "%d-%d-%d %d:%d:%d", fileQuery.fileQuery.struStopTime.iYear, fileQuery.fileQuery.struStopTime.iMonth, fileQuery.fileQuery.struStopTime.iDay, fileQuery.fileQuery.struStopTime.iHour,
        fileQuery.fileQuery.struStopTime.iMinute, fileQuery.fileQuery.struStopTime.iSecond);
	g_log.AddLog(string("GetRecordFileList, stopTime:") + string(stopTime));
    g_iLogonID = m_iLogonID;
    fileQuery.iTrigger = 0;
    fileQuery.iTriggerType = 0x7FFFFFFF;
	for (int ch = 0; ch < channelVec.size(); ch++)
	{
        fileQuery.fileQuery.iChannel = channelVec[ch];
        fileQuery.fileQuery.iPageNo = 0;
		while (1)
		{
            int iRet = NetClient_NetFileQueryEx(m_iLogonID, (PNVS_FILE_QUERY)&fileQuery, sizeof(fileQuery));//录像查询
			if (0 <= iRet)
			{
				g_log.AddLog(string("NetClient_NetFileQuery success!"));
			}
			else
			{
				g_log.AddLog(string("NetClient_NetFileQuery failed!"));
				break;
			}

			DWORD dwRet = WaitForSingleObject(g_hEventSearch, 20 * 1000);
			if (dwRet == WAIT_OBJECT_0)
			{
				int iTotalCount = 0;
				int iCurrentCount = 0;
				int ret = NetClient_NetFileGetFileCount(m_iLogonID, &iTotalCount, &iCurrentCount);//查询文件条数
				if (0 == iRet)
				{
					//g_log.AddLog(string("NetClient_NetFileGetFileCount success!"));
				}
				else
				{
					g_log.AddLog(string("NetClient_NetFileGetFileCount failed!"));
					break;
				}

				if (iCurrentCount == 0)
				{
					g_log.AddLog(string("NetClient_NetFileGetFileCount iCurrentCount == 0!"));
					break;
				}

				char temm_iLogonID[32] = { 0 };
				sprintf(temm_iLogonID, "%d", m_iLogonID);

				char temRet[32] = { 0 };
				sprintf(temRet, "%d", ret);

				char temiTotalCount[32] = { 0 };
				sprintf(temiTotalCount, "%d", iTotalCount);
				char temiCurrentCount[32] = { 0 };
				sprintf(temiCurrentCount, "%d", iCurrentCount);
				g_log.AddLog(string("GetRecordFileList, iTotalCount:") + string(temiTotalCount) + ",iCurrentCount:" + string(temiCurrentCount) + " " + temRet + ",temm_iLogonID:" + temm_iLogonID);

				NVS_FILE_DATA fileInfo = { 0 };
				RecordFile rf;
				for (int i = 0; i < iCurrentCount; ++i)
				{
					int iRet = NetClient_NetFileGetQueryfile(m_iLogonID, i, &fileInfo);//获取文件信息
					if (0 == iRet)
					{
						//g_log.AddLog(string("NetClient_NetFileGetQueryfile success!") + fileInfo.cFileName);
						//char fileinfo[1024] = { 0 };
						//sprintf_s(fileinfo, "file(%d):name(%s),type(%d),chan(%d),size(%d)\n", i, fileInfo.cFileName, fileInfo.iType, fileInfo.iChannel, fileInfo.iFileSize);
						struct tm Tm;
						Tm.tm_year = fileInfo.struStartTime.iYear - 1900;
						Tm.tm_mon = fileInfo.struStartTime.iMonth - 1;
						Tm.tm_mday = fileInfo.struStartTime.iDay;
						Tm.tm_hour = fileInfo.struStartTime.iHour;
						Tm.tm_min = fileInfo.struStartTime.iMinute;
						Tm.tm_sec = fileInfo.struStartTime.iSecond;
						rf.beginTime = _mktime64(&Tm);

						Tm.tm_year = fileInfo.struStoptime.iYear - 1900;
						Tm.tm_mon = fileInfo.struStoptime.iMonth - 1;
						Tm.tm_mday = fileInfo.struStoptime.iDay;
						Tm.tm_hour = fileInfo.struStoptime.iHour;
						Tm.tm_min = fileInfo.struStoptime.iMinute;
						Tm.tm_sec = fileInfo.struStoptime.iSecond;
						rf.endTime = _mktime64(&Tm);

						rf.channel = fileInfo.iChannel;
						rf.name = fileInfo.cFileName;
						rf.size = fileInfo.iFileSize;

						//g_log.AddLog(string(fileinfo));
						rf.setPrivateData(&fileInfo, sizeof(NVS_FILE_DATA));
						files.push_back(rf);
					}
					else
					{
						g_log.AddLog(QString("NetClient_NetFileGetQueryfile failed ret:%1").arg(ret));
						break;
					}
				}

                fileQuery.fileQuery.iPageNo++;
			}
			else
			{
                g_log.AddLog(string("NetClient_NetFileGetQueryfile failed!"));
				break;
			}
		}
	}
    g_log.AddLog(QString("GetRecordFileList finish:%1").arg(files.size()));

//here:
    return true;
}

bool tdy_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
	char iLogonID[32] = { 0 };
	sprintf(iLogonID, "%d", m_iLogonID);
	char addThis[32] = { 0 };
	sprintf(addThis, "size:%d, this:%d", file.size, this);
	g_log.AddLog(string("[1]tdy_videoserver::downLoadByRecordFile!") + iLogonID  + addThis);
	//return false;
	if (m_iLogonID < 0)
	{
		m_sLastError = "请先登录!";
        g_log.AddLog(string("m_iLogonID < 0!"));
		return false;
	}
	NVS_FILE_DATA* pData = (NVS_FILE_DATA *)file.getPrivateData();
    unsigned int uConnID = pData->iChannel;
    DOWNLOAD_FILE tdf = { sizeof(DOWNLOAD_FILE) };
    strcpy_s(tdf.m_cRemoteFilename, strlen(pData->cFileName) + 1, pData->cFileName);
    strcpy_s(tdf.m_cLocalFilename, strlen(saveFileName) + 1, (char*)saveFileName);
    tdf.m_iPosition = -1;
    tdf.m_iSpeed = 32;
    tdf.m_iReqMode = 1;

    int iRet = NetClient_NetFileDownload(&uConnID, m_iLogonID, DOWNLOAD_CMD_FILE, &tdf, sizeof(DOWNLOAD_FILE));
	//NetClient_SetNetFileDownloadFileCallBack(uConnID, (RECV_DOWNLOADDATA_NOTIFY)DownloadNotify, NULL);//设置回调
	char temiRet[32] = { 0 };
	sprintf(temiRet, "iRet:%d,uConnID:%d,m_iLogonID:%d,", iRet, uConnID, m_iLogonID);
	if (iRet >= 0)
	{
		g_log.AddLog(string("NetFileDownloadFile success!") + temiRet +",filename:" + file.name + "," + saveFileName);
	}
	else
	{
		DWORD dwRet = GetLastError();
		char temRet[32] = { 0 };
		sprintf(temRet, " lasterror:%d", dwRet);
		g_log.AddLog(string("NetFileDownloadFile failed!") + temiRet + temRet + ",filename:" + file.name + "," + saveFileName);
		return false;
	}

    DOWNLOAD_CONTROL tdc = { sizeof(DOWNLOAD_CONTROL) };
    tdc.m_iPosition = -1;
    tdc.m_iSpeed = 16;
    tdc.m_iReqMode = 1;
    NetClient_NetFileDownload((unsigned int*)&uConnID, m_iLogonID, DOWNLOAD_CMD_CONTROL, &tdc, sizeof(DOWNLOAD_CONTROL));
	
	hdl = (download_handle_t)uConnID;
	g_log.AddLog(string("NetFileDownloadFile operate over!"));
	return true;
}

bool  tdy_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
	if (m_iLogonID < 0)
	{
		m_sLastError = "请先登录!";
		return false;
	}
	g_hwnd = hwnd;
	g_log.AddLog(string("[1]PlayBackByRecordFile!"));

	unsigned long uConnID = -1;
	int iRet = NetClient_NetFileDownloadFile(&uConnID, m_iLogonID, (char *)file.name.c_str(), NULL, 0, 0, 1);
	g_log.AddLog(string("[3]PlayBackByRecordFile!"));
	if (iRet >= 0)
	{
		g_log.AddLog(string("[4]PlayBackByRecordFile!"));
		NetClient_SetNetFileDownloadFileCallBack(uConnID, (RECV_DOWNLOADDATA_NOTIFY)DownloadNotify, this);//设置回调
		g_log.AddLog(string("[5]PlayBackByRecordFile!"));
		g_gloadPlayLen = 0;
	}
	else
	{
		printf("NetFileDownloadFile failed!\n");
		return false;
	}

	DownLoadInfo tDownLoadInfo = { 0 };
	tDownLoadInfo.filesize = file.size;

	{
		Mutex::ScopedLock lock(m_downloadMutex);
		m_DownLoadStream.insert(std::make_pair(uConnID, tDownLoadInfo));
	}
	playbackHandle = (download_handle_t)uConnID;

	return true;
}

bool tdy_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	return false;
}

bool tdy_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
	{
		Mutex::ScopedLock lock(m_downloadMutex);
		m_DownLoadStream.erase(playbackHandle);
	}
	int ret = NetClient_NetFileStopDownloadFile((unsigned long)playbackHandle);
	if (0 != ret)
	{
		m_sLastError = GetLastError();
		return false;
	}

	TC_Stop(g_iPlayID);//停止播放
	TC_DeletePlayer(g_iPlayID);//删除播放器实例

	g_log.AddLog(string("stop the play"));


	return true;
}



bool tdy_videoserver::stopDownload(download_handle_t h)
{
	{
		Mutex::ScopedLock lock(m_downloadMutex);
		m_DownLoadStream.erase(h);
	}
	int ret = NetClient_NetFileStopDownloadFile((unsigned long)h);
	if (0 != ret)
    {
		m_sLastError = GetLastError();
        return false;
    }

	return true;
}

bool tdy_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	int iPos = 0;
	int downLoadSize = 0;
	{
		Mutex::ScopedLock lock(this->m_downloadMutex);
		std::map<unsigned int, DownLoadInfo>::iterator itr = m_DownLoadStream.find((unsigned int)(playbackHandle));
		if (itr != this->m_DownLoadStream.end())
		{
			int ret = NetClient_NetFileGetDownloadPos((unsigned int)playbackHandle, &iPos, &downLoadSize);
			char per[256] = { 0 };
			sprintf_s(per, "getPlayBackPos:[1]iPos:%d, downLoadSize:%d",  iPos, downLoadSize);
			g_log.AddLog(string(per));
			if (ret != 0)
			{
				GetLastError();
			}
			else
			{
				*pos = iPos;
			}

// 			*pos = (g_gloadPlayLen * 100 / (itr->second.filesize));
// 			char str[256] = { 0 };
// 			sprintf_s(str, "g_gloadPlayLen:%d, filesize:%d, pos:%d", g_gloadPlayLen, itr->second.filesize, *pos);
// 			g_log.AddLog(string(str));
		}
	}

	return true;
}


/*bool tdy_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	int iPos = 0;
	int downLoadSize = 0;
	g_log.AddLog(string("getDownloadPos!"));
	{
		Mutex::ScopedLock lock(this->m_downloadMutex);
		std::map<unsigned int, DownLoadInfo>::iterator itr = m_DownLoadStream.find((unsigned int)(h));
		if (itr != this->m_DownLoadStream.end())
		{
			int ret = NetClient_NetFileGetDownloadPos((unsigned long)h, &iPos, &downLoadSize);
			char per[256] = { 0 };
			sprintf_s(per, "[1]iPos:%d, downLoadSize:%d", iPos, downLoadSize);
			g_log.AddLog(string(per));

			sprintf_s(per, "[2]downLoadSize:%d, iPos:%d", downLoadSize, iPos);
			g_log.AddLog(string(per));

			if (ret != 0)
			{
				GetLastError();
				*failed = false;
			}
			else
			{
				*totalSize = itr->second.filesize;
				*currentSize = downLoadSize;
			}

// 			if (iPos >= 98)
// 			{
// 				*currentSize = *totalSize;
// 			}

			if (iPos == 0 && downLoadSize == 0)
			{
				*currentSize = *totalSize;
			}
		}
		else
		{
			*failed = false;
		}
	}

	return true;
}*/

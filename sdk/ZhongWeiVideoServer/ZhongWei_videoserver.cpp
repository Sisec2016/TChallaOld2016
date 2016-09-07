#include "ZhongWei_videoserver.h"
#include <iostream>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QString>
#include <time.h>
#include <io.h>
#include <WinUser.h>
#include "../../VideoServer/log.h"
Log g_log("ZhongWei_videoserver");

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryZhongWei();
}

static std::string GetLastErrorString()
{
    return "未知错误";
}

CFactoryZhongWei::CFactoryZhongWei()
{
    init();
}

CFactoryZhongWei::~CFactoryZhongWei()
{
    clean();
}


// HANDLE g_hConnectEvent = CreateEventA(NULL, FALSE, FALSE, NULL);

string g_strRecFilename = "Video.mp4";

bool g_bPlaybackFinished = false;
bool g_bDecoding = false;
__int64 g_iTotalSize = 0;
__int64 g_fileRealSize = 0;
HWND g_hWnd = NULL;
float g_iBitRate = (397 * 1024 / 160);//文件大小/文件时间长度秒
int g_iPos = 0;
int g_iTimeLen = 1600;



std::map<int, ZhongWei_videoserver*> ZhongWei_videoserver::sLinkeVideoserver;
std::recursive_mutex ZhongWei_videoserver::sMutexLinkVideservrs;

void ZhongWei_videoserver::dealConnected(ZhongWei::JCLink_t nLinkID, const QString& sError){
    std::lock_guard<std::recursive_mutex> lck(sMutexLinkVideservrs);
    if (sLinkeVideoserver.find(nLinkID) == sLinkeVideoserver.end() || sLinkeVideoserver[nLinkID] == NULL)
    {
        g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        return;
    }
    sLinkeVideoserver[nLinkID]->onConnected(sError);
    if (!sError.isEmpty())
    {
        g_log.AddLog(sError);
        std::lock_guard<std::recursive_mutex> lock(sMutexLinkVideservrs);
        sLinkeVideoserver.erase(nLinkID);
    }
   
}
void ZhongWei_videoserver::dealDisConnected(ZhongWei::JCLink_t nLinkID, const QString& sError){
    std::lock_guard<std::recursive_mutex> lck(sMutexLinkVideservrs);
    if (sLinkeVideoserver.find(nLinkID) == sLinkeVideoserver.end() || sLinkeVideoserver[nLinkID] == NULL)
    {
        g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        return;
    }
    sLinkeVideoserver[nLinkID]->onDisConnected(sError);
    g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
    std::lock_guard<std::recursive_mutex> lock(sMutexLinkVideservrs);
    sLinkeVideoserver.erase(nLinkID);
}
void ZhongWei_videoserver::dealDownloadData(ZhongWei::JCLink_t nLinkID, char* data, int len){
    std::lock_guard<std::recursive_mutex> lck(sMutexLinkVideservrs);
    if (sLinkeVideoserver.find(nLinkID) == sLinkeVideoserver.end() || sLinkeVideoserver[nLinkID] == NULL)
    {
        g_log.AddLog(QString("dealDownloadData NULL"));
        return;
    }
    sLinkeVideoserver[nLinkID]->onDownloadData(data, len);
}
void ZhongWei_videoserver::dealFinishDownload(ZhongWei::JCLink_t nLinkID, const QString& sError){
    std::lock_guard<std::recursive_mutex> lck(sMutexLinkVideservrs);
    if (sLinkeVideoserver.find(nLinkID) == sLinkeVideoserver.end() || sLinkeVideoserver[nLinkID] == NULL)
    {
        g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        return;
    }
    g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
    sLinkeVideoserver[nLinkID]->onFinishDownload(sError);
   // sLinkeVideoserver.erase(nLinkID);
}



void ZhongWei_videoserver::dealFindFiles(ZhongWei::JCLink_t nLinkID, ZhongWei::PJCRecFileInfo pInfos, int nCount){
    std::lock_guard<std::recursive_mutex> lck(sMutexLinkVideservrs);
    if (sLinkeVideoserver.find(nLinkID) == sLinkeVideoserver.end() || sLinkeVideoserver[nLinkID] == NULL)
    {
        g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        return;
    }
    sLinkeVideoserver[nLinkID]->onFindFiles(pInfos, nCount);
}


void funJCEventCallback(ZhongWei::JCLink_t nLinkID, ZhongWei::JCEventType etType, DWORD_PTR pData1, DWORD_PTR pData2, LPVOID pUserData)
{
    g_log.AddLog(QString("link %1 type %2").arg(nLinkID).arg(etType));
	switch(etType)
	{
	case ZhongWei::JCET_DownloadData://录像下载数据
		{
            ZhongWei_videoserver::dealDownloadData(nLinkID, (char*)pData1, pData2);

		}
		break;

	case ZhongWei::JCET_DownloadStop://录像下载停止
        ZhongWei_videoserver::dealFinishDownload(nLinkID, QStringLiteral("录像下载停止"));
        break;
	case ZhongWei::JCET_DownloadError://远程下载失败
        ZhongWei_videoserver::dealFinishDownload(nLinkID, QStringLiteral("远程下载失败"));
        break;
	case ZhongWei::JCET_DownloadTimeout://远程下载超时
        ZhongWei_videoserver::dealFinishDownload(nLinkID, QStringLiteral("远程下载超时"));
        break;
    case ZhongWei::JCET_DownloadEnd://录像下载完成
        ZhongWei_videoserver::dealFinishDownload(nLinkID, "");
        break;
	case ZhongWei::JCET_RemotePlayBegin:		//远程回放开始
	{
													//SetEvent(g_hEventSearch);
    }
        break;
	case ZhongWei::JCET_RemotePlayEnd:		//远程回放结束
		{
			g_bPlaybackFinished = true;
		}
		break;
	case ZhongWei::JCET_StreamReset:		//码流重置信号(码流配置改变,须关闭并重新开启解码、录像等)
		{
			g_log.AddLog(string("JCET_StreamReset 码流重置信号"));
			Api_ZhongWei::Api().m_pEnableDecoder(nLinkID, false);
			if (g_bDecoding)
			{
				Api_ZhongWei::Api().m_pEnableDecoder(nLinkID, true);
				RECT rc;
				GetClientRect(g_hWnd, &rc);
				POINT pt;
				pt.x = rc.left;
				pt.y = rc.top;
				ClientToScreen(g_hWnd, &pt);
				RECT rcTmp;
				rcTmp.left = pt.x;
				rcTmp.top = pt.y;
				rcTmp.right = rcTmp.left + (rc.right - rc.left);
				rcTmp.bottom = rcTmp.top + (rc.bottom - rc.top);
				rc = rcTmp;
				Api_ZhongWei::Api().m_pSetVPreview(nLinkID, g_hWnd, &rc);
			}
		}
		break;
	case ZhongWei::JCET_GetFileListOK://获取远程录像成功
        ZhongWei_videoserver::dealFindFiles(nLinkID, (ZhongWei::PJCRecFileInfo)pData1, (int)pData2);
		break;
	case ZhongWei::JCET_GetFileListError://获取远程录像失败
		{
		}
		break;
	case ZhongWei::JCET_ConnectOK://连接成功
		{
            
            ZhongWei_videoserver::dealConnected(nLinkID, "");
		}
		break;

	case ZhongWei::JCET_UserAccessError: //用户验证失败
        ZhongWei_videoserver::dealConnected(nLinkID, QStringLiteral("用户验证失败"));
		break;

	case ZhongWei::JCET_NoChannel://主控通道未开启
        ZhongWei_videoserver::dealConnected(nLinkID, QStringLiteral("主控通道未开启"));
		break;

	case ZhongWei::JCET_ConTypeError://连接类型错误
        ZhongWei_videoserver::dealConnected(nLinkID, QStringLiteral("连接类型错误"));
		break;

	case ZhongWei::JCET_ConCountLimit://超过主控连接最大数
        ZhongWei_videoserver::dealConnected(nLinkID, QStringLiteral("超过主控连接最大数"));
		break;

	case ZhongWei::JCET_ConTimeout://连接超时
        ZhongWei_videoserver::dealConnected(nLinkID, QStringLiteral("连接超时"));
		break;

	case ZhongWei::JCET_DisconOK://断开连接成功
        ZhongWei_videoserver::dealDisConnected(nLinkID, "");
		break;

	case ZhongWei::JCET_ConAbout://
        ZhongWei_videoserver::dealDisConnected(nLinkID, QStringLiteral("连接异常断开"));
		break;

	case ZhongWei::JCET_ServiceStop://主控断开连接
        ZhongWei_videoserver::dealDisConnected(nLinkID, QStringLiteral("主控断开连接"));
		break;

	default:
		break;
	}
}

void funJCDataCallback(ZhongWei::JCLink_t nLinkID, ZhongWei::PJCStreamFrame pFrame, LPVOID pUserData)
{
	char acBuffer[32];
	sprintf(acBuffer, "Type:%d\n", pFrame->sType);
	OutputDebugStringA(acBuffer);
}

void funJCRawDataCallback(ZhongWei::JCLink_t nLinkID, ZhongWei::PJCRawFrame pFrame, LPVOID pUserData)
{
}

void funLanSearchCallback(ZhongWei::PJCLanDeviceInfo pDevice)
{
	//JCLanDeviceInfo
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "funLanSearchCallback 通道个数 :%d ", pDevice->nChannelNum);
	g_log.AddLog(string(szLog));
}

bool CFactoryZhongWei::init()
{
    if (!m_init)
    {
        m_init = Api_ZhongWei::Api().m_pInit(-1);
        if (!m_init)
        {
           m_sLastError = "初始化SDK失败";
		   g_log.AddLog(string("初始化SDK失败"));
           return false;
        }
		g_log.AddLog(string("初始化SDK成功"));
		Api_ZhongWei::Api().m_pSetCallback(funJCEventCallback, funJCDataCallback, funJCRawDataCallback, funLanSearchCallback);
    }

    return m_init;
}


void CFactoryZhongWei::clean()
{
    Api_ZhongWei::Api().m_pUninit();
}



IVideoServer* CFactoryZhongWei::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new ZhongWei_videoserver();
}



// std::vector<ZhongWei_videoserver*> ZhongWei_videoserver::sServers;
// std::recursive_mutex ZhongWei_videoserver::sMtServers;

/*
 * 析构函数
 */
ZhongWei_videoserver::ZhongWei_videoserver()
{
    mhConnectEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    m_hEventSearch = CreateEventA(NULL, FALSE, FALSE, NULL);
    m_bDownloadFinished = false;
    mCurLink = 0;
    m_pRecFile = NULL;
    mDownloadTotalSize = 0;
    mDownloadSize = 0;
}

ZhongWei_videoserver::~ZhongWei_videoserver()
{
    logout();
//     CloseHandle(mhConnectEvent);
//     CloseHandle(m_hEventSearch);
}

IVideoServer* ZhongWei_videoserver::clone()
{
	return NULL;
}
void ZhongWei_videoserver::onConnected(const QString& sError){
    msConnectError = sError;
    SetEvent(mhConnectEvent);
}

void ZhongWei_videoserver::onDisConnected(const QString& sError){
    m_sLastError = sError.toLocal8Bit().data();
}

void ZhongWei_videoserver::onDownloadData(char* data, int len){
    std::lock_guard<std::recursive_mutex> lck(m_recFileMutex);
    if (m_pRecFile != NULL)
    {

        int r = fwrite(data, len, 1, m_pRecFile);
        g_log.AddLog(QString("onDownloadData:%1-----%2").arg(len).arg(r));
        mDownloadSize += len;
    }
    
}

void ZhongWei_videoserver::onFinishDownload(const QString& sError){
    msDownloadError = sError;
    if (sError.isEmpty())
    {
        //mDownloadSize = mDownloadTotalSize;
    }
    m_bDownloadFinished = true;
    mLastDownloadSize = 0;
}

void ZhongWei_videoserver::onFindFiles(ZhongWei::PJCRecFileInfo pInfos, int nCount){

    m_RecFileInfoList.clear();
    for (int i = 0; i < nCount; ++i)
    {
        m_RecFileInfoList.push_back(pInfos[i]);
    }

    SetEvent(m_hEventSearch);
}

bool ZhongWei_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
//    logout();
    std::lock_guard<std::recursive_mutex> lock(m_linksMutex);

    m_strIP = IP;
    m_iPort = port;
    m_strUser = user;
    m_strPsw = password;

    int channel = 1;
    channels.clear();
    if (m_mpLinks.size() > 0)
    {
        for (auto it = m_mpLinks.begin(); it != m_mpLinks.end(); it++)
        {
            channels[it->first];
        }
    }
    else{
        while (this->connectChannel(channel)){
            channels[channel];
            channel++;
        }
    }

    
    return channels.size() > 0;
}


bool ZhongWei_videoserver::logout()
{
    g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
    std::lock_guard<std::recursive_mutex> lock(m_linksMutex);
    for (auto it = m_mpLinks.begin(); it != m_mpLinks.end(); it++)
    {
        this->disconnectChannel(it->first);
    }
    m_mpLinks.clear();
    return true;
}



#define MAX_SEARCH_COUNT 1000
bool ZhongWei_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    if (!this->hasLogin())
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("GetRecordFileList 请先登录"));
		return false;
	}

    if (timeStart >= timeEnd)
    {
		m_sLastError = "时间范围不对!";
		g_log.AddLog(string("GetRecordFileList 时间范围不对"));

        return false;
    }

	files.clear();
    
	auto  itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
		int nChannelId = *itr;
        if (m_mpLinks.find(nChannelId) == m_mpLinks.end())
        {
            continue;
        }

        int iLinkID = m_mpLinks[nChannelId];

        QDateTime dtTimeStart(QDateTime::fromTime_t(timeStart));
        QDateTime dtTimeEnd(QDateTime::fromTime_t(timeEnd));
        QTime tmS;
        QTime tmE;
        QDate dtE;
        RecordFile f;
        for (QDate start(dtTimeStart.date()); start <= dtTimeEnd.date(); start = start.addDays(1))
        {
            if (start == dtTimeStart.date())
            {
                tmS = dtTimeStart.time();
            }
            else{
                tmS = QTime(0, 0);
            }

            if (start >= dtTimeEnd.date())
            {
                tmE = dtTimeEnd.time();
            }
            else{
                tmE = QTime(23, 59);
            }

            ZhongWei::JCDateBlock jcdb;
            jcdb.nEndYear = jcdb.nBeginYear = start.year();
            jcdb.nEndMonth = jcdb.nBeginMonth = start.month();
            jcdb.nEndDay = jcdb.nBeginDay = start.day();
            m_RecFileInfoList.clear();

            if (!Api_ZhongWei::Api().m_pSearchFileByTime(iLinkID, &jcdb))
            {
                m_sLastError = GetLastErrorString();
                g_log.AddLog(string("GetRecordFileList 获取录像失败"));
                continue;
            }

            DWORD dwRet = WaitForSingleObject(m_hEventSearch, 5 * 1000);
            if (dwRet != WAIT_OBJECT_0){
                g_log.AddLog(string("GetRecordFileList 获取录像超时!"));
                continue;
            }

            std::vector<ZhongWei::JCRecFileInfo>::iterator itr = m_RecFileInfoList.begin();
            for (; itr != m_RecFileInfoList.end(); itr++)
            {
                ZhongWei::JCRecFileInfo& item = *itr;
                f.channel = nChannelId;
                f.size = g_iBitRate * g_iTimeLen;
                f.name = item.szFilename;
                QTime tBegin(QTime::fromString(item.szBeginTime, "hhmmss"));
                if (tBegin > tmE)
                {
                    continue;
                }

                QTime tEnd(tBegin.addSecs(10 * 60));
                if (tEnd < tmS)
                {
                    continue;
                }
                f.beginTime = QDateTime(start, tBegin).toTime_t();
                f.endTime = QDateTime(start, tEnd).toTime_t();
                sprintf(item.szPathName, "%d", iLinkID);
                f.setPrivateData(&item, sizeof(ZhongWei::JCRecFileInfo));
                if (files.size() > 0)
                {
                    files.rbegin()->endTime = f.beginTime;
                }
                files.push_back(f);
            }
        }
	}

    std::sort(files.begin(), files.end(), [](const RecordFile& a, const RecordFile& b){
        return a.beginTime < b.beginTime;
    });
	return true;
}



bool ZhongWei_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{

    std::lock_guard<std::recursive_mutex> lck(m_recFileMutex);
    if (m_pRecFile)
    {
        char szLog[1024];
        ZeroMemory(szLog, 1024);
        sprintf(szLog, "downLoadByRecordFile this:%p 不支持多线程下载回放", this);
        g_log.AddLog(string(szLog));
        return false;
    }

	

//     this->disconnectChannel(file.channel);
//     ::Sleep(1000);
//     if (!this->connectChannel(file.channel))
//     {
//         g_log.AddLog("download connectChannel failed!");
//         return false;
//     }

    m_bDownloadFinished = false;
    m_pRecFile = fopen(saveFileName, "wb");
    if (m_pRecFile == NULL)
    {
        char szLog[1024];
        ZeroMemory(szLog, 1024);
        sprintf(szLog, "downLoadByRecordFile 打开文件失败 文件名：%s", g_strRecFilename.c_str());
        g_log.AddLog(string(szLog));
        m_sLastError = szLog;
        return false;
    }

    int iLinkID = m_mpLinks[file.channel];

    ZhongWei::JCRecFileInfo* pData = (ZhongWei::JCRecFileInfo *)file.getPrivateData();
    //if (atoi(pData->szPathName) != iLinkID)
//     {
//         std::vector<RecordFile> files;
//         std::vector<int> vcChannels;
//         vcChannels.push_back(file.channel);
//         if (!this->GetRecordFileList(files, vcChannels, file.beginTime, file.endTime) || files.size() < 0)
//         {
//             g_log.AddLog(string("downLoadByRecordFile GetRecordFileList failed:") + m_sLastError);
//             return false;
//         }
//         RecordFile& f = *((RecordFile*)&file);
//         f = files[0];
//     }
//     ZhongWei::JCRecFileInfo *pData = (ZhongWei::JCRecFileInfo *)file.getPrivateData();
	bool bRet = Api_ZhongWei::Api().m_pDownloadByFile(iLinkID, pData->nRecFileID);
	if (!bRet)
	{
		m_sLastError = GetLastErrorString();
        g_log.AddLog(string("downLoadByRecordFile 下载文件失败") + m_sLastError);
		if (m_pRecFile != NULL)
		{
			fclose(m_pRecFile);
			m_pRecFile = NULL;
		}
		return false;
	}

    mDownloadTotalSize = file.size;
    mDownloadSize = 0;
    hdl = iLinkID + 1;
	return true;
}


bool  ZhongWei_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
  
    int iLinkID = m_mpLinks[file.channel];
	g_bPlaybackFinished = false;
	g_bDecoding = true;
	g_hWnd = hwnd;
	g_iPos = 0;
	
	bool bRet = false;
	if (Api_ZhongWei::Api().m_pEnableDecoder)
	{
        bRet = Api_ZhongWei::Api().m_pEnableDecoder(iLinkID, true);
		if (!bRet)
		{
			m_sLastError = "初始化解码器失败";
		    g_log.AddLog(string("PlayBackByRecordFile 初始化解码器失败"));
			return false;
		}
	}
	else
	{
		g_log.AddLog(string("PlayBackByRecordFile dll中无此接口：m_pEnableDecoder"));
		return false;
	}

	RECT rc;
	GetClientRect(hwnd, &rc);
	POINT pt;
	pt.x = rc.left;
	pt.y = rc.top;
	ClientToScreen(hwnd, &pt);
	RECT rcTmp;
	rcTmp.left = pt.x;
	rcTmp.top = pt.y;
	rcTmp.right = rcTmp.left + (rc.right - rc.left);
	rcTmp.bottom = rcTmp.top + (rc.bottom - rc.top);
	rc = rcTmp;

	char szLog[1024];
	ZeroMemory(szLog, 1024);
	g_log.AddLog(string(szLog));
	if (Api_ZhongWei::Api().m_pSetVPreview)
	{
        bRet = Api_ZhongWei::Api().m_pSetVPreview(iLinkID, hwnd, &rc);
		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("PlayBackByRecordFile 设置播放窗口句柄失败"));
			return false;
		}
	}
	else
	{
		g_log.AddLog(string("PlayBackByRecordFile dll中无此接口：m_pSetVPreview"));
		return false;
	}

	if (Api_ZhongWei::Api().m_pPlayBackByFile)
	{
		ZhongWei::JCRecFileInfo* pData = (ZhongWei::JCRecFileInfo *)file.getPrivateData();
        bRet = Api_ZhongWei::Api().m_pPlayBackByFile(iLinkID, /*atoi(file.name.c_str())*/pData->nRecFileID);
		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 录像播放失败"));
			return false;
		}
	}
	else
	{
		g_log.AddLog(string("PlayBackByRecordFile dll中无此接口：m_pPlayBackByFile"));
		return false;
	}

    playbackHandle = iLinkID + 1;
	return true;
}

bool ZhongWei_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
	g_log.AddLog(string("SetPlayBack 不支持"));
	return false;
}

bool ZhongWei_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
{
	if (mPause == 1)
	{
		g_log.AddLog(string("StopPlayBack 开始暂停播放"));
		bool bRet = Api_ZhongWei::Api().m_pPlayBackControl(playbackHandle - 1, ZhongWei::JCRPC_Pause);
		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 暂停播放失败"));
			return false;
		}
	}
	else
	{
		char szLog[1024];
		ZeroMemory(szLog, 1024);
		sprintf(szLog, "StopPlayBack 开始停止播放 playbackHandle:%d", playbackHandle);
		g_log.AddLog(string(szLog));

		g_bDecoding = false;
		bool bRet = Api_ZhongWei::Api().m_pEnableDecoder(playbackHandle - 1, false);
		if (!bRet)
		{
			m_sLastError = "反初始化解码器失败";
			g_log.AddLog(string("PlayBackByRecordFile 反初始化解码器失败"));
			return false;
		}
		bRet = Api_ZhongWei::Api().m_pSetVPreview(playbackHandle - 1, NULL, NULL);
		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("PlayBackByRecordFile 解除设置播放窗口句柄失败"));
			return false;
		}
		bRet = Api_ZhongWei::Api().m_pPlayBackByFile(playbackHandle - 1, -1);
		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败"));
			return false;
		}
	}
    return true;
}

bool ZhongWei_videoserver::stopDownload(download_handle_t h)
{
    std::lock_guard<std::recursive_mutex> lck(m_recFileMutex);
	g_log.AddLog(string("stopDownload ------"));
	bool bRet = Api_ZhongWei::Api().m_pDownloadByFile(h - 1, -1);
	if (!m_pRecFile)
	{
		g_log.AddLog(string("stopDownload *******"));
		m_bDownLoading = false;
		return true;
	}
    if (m_pRecFile != NULL)
    {
        fclose(m_pRecFile);
        m_pRecFile = NULL;
    }
	if (!bRet)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败"));
		return false;
	}

    //dealFinishDownload(h - 1, QStringLiteral("手工停止下载"));


    return true;
}

bool ZhongWei_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	if (g_bPlaybackFinished)
	{
		StopPlayBack(playbackHandle, 0);

		*pos = 100;
	}
	return true;
}


bool ZhongWei_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{

	if (m_bDownloadFinished)
	{
        if (mLastDownloadSize != mDownloadSize)
        {
            mLastDownloadSize = ++mDownloadSize;
            *failed = false;
            *totalSize = mDownloadTotalSize;
            *currentSize = mDownloadTotalSize;
            return true;
        }
        
        *failed = false;
        *totalSize = mDownloadTotalSize;
        *currentSize = mDownloadTotalSize;

		char szLog[1024];
		ZeroMemory(szLog, 1024);
		sprintf(szLog, "getDownloadPos 文件总大小:%d", g_iTotalSize);
		g_log.AddLog(string(szLog));
        *failed = !msDownloadError.isEmpty();
        m_sLastError = msDownloadError.toLocal8Bit().data();
        stopDownload(h);
        g_iPos = 0;
		return true;
	}
    

    *totalSize = mDownloadTotalSize;
    *currentSize = mDownloadSize;
    if (mDownloadSize / mDownloadTotalSize >= 94)
    {
        *currentSize = (mDownloadTotalSize * 94) / 100;
        *currentSize += g_iPos++;
    }
    else
    {
        g_iPos = 0;
    }

	*failed = false;
	return true;
}

bool ZhongWei_videoserver::connectChannel(int channel){
    int iLinkID = Api_ZhongWei::Api().m_pLogin((char*)m_strIP.c_str(), m_iPort, channel,
        (char*)m_strUser.c_str(), (char*)m_strPsw.c_str(), FALSE, NULL);
    if (iLinkID == JCSDK_INVALID_LINKVALUE)
    {
        m_sLastError = "通道连接失败!";
        g_log.AddLog(string("connectChannel 通道连接失败"));
        return false;
    }

    {
        std::lock_guard<std::recursive_mutex> lock(sMutexLinkVideservrs);
        sLinkeVideoserver[iLinkID] = this;
    }

    DWORD dwRet = WaitForSingleObject(mhConnectEvent, 5 * 1000);
    if (dwRet != WAIT_OBJECT_0)
    {
        g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        std::lock_guard<std::recursive_mutex> lock(sMutexLinkVideservrs);
        sLinkeVideoserver.erase(iLinkID);
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(m_linksMutex);
    m_mpLinks[channel] = iLinkID;
    return msConnectError.isEmpty();
}

bool ZhongWei_videoserver::hasLogin(){
    std::lock_guard<std::recursive_mutex> lock(m_linksMutex);
    return m_mpLinks.size() > 0;
}

bool ZhongWei_videoserver::disconnectChannel(int channel){
    std::lock_guard<std::recursive_mutex> lock(m_linksMutex);
    if (m_mpLinks.find(channel) != m_mpLinks.end())
    {
        if (NULL != m_mpLinks[channel])
        {
            Api_ZhongWei::Api().m_pLogout(m_mpLinks[channel]);
            std::lock_guard<std::recursive_mutex> lock(sMutexLinkVideservrs);
            g_log.AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
            sLinkeVideoserver.erase(m_mpLinks[channel]);
            m_mpLinks[channel] = NULL;
        }

    }

    return true;
}

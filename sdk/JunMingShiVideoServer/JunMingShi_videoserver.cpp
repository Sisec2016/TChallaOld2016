#include "JunMingShi_videoserver.h"
#include <iostream>
#include <sys/timeb.h>

#include <time.h>
#include <io.h>
#include <assert.h>
#include "../../VideoServer/log.h"
#include <algorithm>
Log g_log("JunMingShi_videoserver");
// #include <ATLSTR.H>

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryJunMingShi();
}

static std::string GetLastErrorString()
{
	return "未知错误";
}

CFactoryJunMingShi::CFactoryJunMingShi()
{
    init();
}

CFactoryJunMingShi::~CFactoryJunMingShi()
{
    clean();
}

bool CFactoryJunMingShi::init()
{
    if (!m_init)
    {
        int iRet = Api_JunMingShi::Api().m_pInit();
		if (iRet < 0)
		{
			m_init = false;
		}
		else
			m_init = true;
        //NET_DVR_SetConnectTime(1000, 30);
        //NET_DVR_SetReconnect(3000);
        //NET_DVR_SetDVRMessage()
        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
			return false;
        }

		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryJunMingShi::clean()
{
    Api_JunMingShi::Api().m_pUninit();
}

IVideoServer* CFactoryJunMingShi::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new JunMingShi_videoserver();
}


// std::vector<JunMingShi_videoserver*> JunMingShi_videoserver::sServers;
// std::recursive_mutex JunMingShi_videoserver::sMtServers;

/*
 * 析构函数
 */
JunMingShi_videoserver::JunMingShi_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(JunMingShi_videoserver::sMtServers);
//     sServers.push_back(this);
}

JunMingShi_videoserver::~JunMingShi_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(JunMingShi_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}


static void CALLBACK down_PROGRESS_callback(JunMingShi::NETDVR_progressParam_t progress, unsigned int dwContent)
{
	//g_log.AddLog(string("down_PROGRESS_callback"));
// 	PlayCBContext *pContext = (PlayCBContext *)dwContent;
// 	if (!pContext)
// 	{
// 		return;
// 	}
	JunMingShi_videoserver *pThis = (JunMingShi_videoserver *)dwContent;
	if (!pThis)
	{
		return;
	}
	{
		Mutex::ScopedLock lock(pThis->m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDown.find(INT_MAX);
		if (itr != pThis->m_mapPosDown.end())
		{
			itr->second.iCurSize = progress.curr_pos;
			itr->second.iTotalSize = progress.total_size;
			itr->second.iPercent = ((float)itr->second.iCurSize/(float)itr->second.iTotalSize)*100;
		}
	}
}

static void CALLBACK play_PROGRESS_callback(JunMingShi::NETDVR_progressParam_t progress, unsigned int dwContent)
{
	PlayCBContext *pContext = (PlayCBContext *)dwContent;
	if (!pContext)
	{
		return;
	}
	JunMingShi_videoserver *pThis = (JunMingShi_videoserver *)pContext->iThis;
	long long llHandle = 0;
	{
		Mutex::ScopedLock lock(pThis->m_mtx);
		map<unsigned int, long long>::iterator itr = pThis->m_mapWndHandle.find((unsigned int)pContext);
		if (itr == pThis->m_mapWndHandle.end())
		{
			return;
		}
		llHandle = itr->second;
	}
	{
		Mutex::ScopedLock lock(pThis->m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosPlay.find(llHandle);
		if (itr != pThis->m_mapPosPlay.end())
		{
			itr->second.iCurSize = progress.curr_pos;
			itr->second.iTotalSize = progress.total_size;
			itr->second.iPercent = ((float)itr->second.iCurSize/(float)itr->second.iTotalSize)*100;
		}
	}
}

void CALLBACK get_encframe(JunMingShi::pFrameHeadr pFrmHdr, unsigned int dwContextEnc)
{
	PlayCBContext* pContext = (PlayCBContext*)dwContextEnc;
	if (pContext == NULL)
	{
		return;
	}
	JunMingShi_videoserver * pThis = (JunMingShi_videoserver *)pContext->iThis;
	if (pThis == NULL)
	{
		return;
	}
	// 	TLPlay_SetPlayMode(pThis->m_hPlay, TL_PLAY_POOL_STREAM);
	// 	TLPlay_OpenStream(pThis->m_hPlay, 1024*1024*1);
	// 	TLPlay_Play(pThis->m_hPlay, pThis->GetDlgItem(IDC_PLAYWND1)->GetSafeHwnd());
	BYTE *framebuf = NULL;
	framebuf = (BYTE *)malloc(2048 * 1024);
	if (NULL == framebuf)
	{
		return;
	}
	memset(framebuf, 0, sizeof(framebuf));
	JunMingShi::PLAYFRAMEHDR hdr={0};
	hdr.m_byMediaType = pFrmHdr->mediaType;
	hdr.m_dwDataSize = pFrmHdr->dataSize;
	hdr.m_byFrameRate =pFrmHdr->frameRate;
	hdr.m_dwFrameID = pFrmHdr->frameID;
	hdr.m_dwTimeStamp = pFrmHdr->timeStamp;
	hdr.m_tVideoParam.m_bKeyFrame = pFrmHdr->videoParam.keyFrame;
	hdr.m_tVideoParam.m_wVideoWidth = pFrmHdr->videoParam.videoWidth;
	hdr.m_tVideoParam.m_wVideoHeight = pFrmHdr->videoParam.videoHeight;

	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "get_encframe dataLen:%d ", pFrmHdr->dataSize);
	g_log.AddLog(string(szLog));

	memcpy(framebuf, &hdr,sizeof(JunMingShi::PLAYFRAMEHDR));
	memcpy(framebuf+sizeof(JunMingShi::PLAYFRAMEHDR), pFrmHdr->pData,pFrmHdr->dataSize);
	if (hdr.m_byMediaType==98)
	{
		BOOL bret = Api_JunMingShi::Api().m_pPlayInputV(pContext->lPlayPort, 
			framebuf, pFrmHdr->dataSize+sizeof(JunMingShi::PLAYFRAMEHDR));
		//TRACE("ret %d\n", bret);
	}
	else
	{
		BOOL bret = Api_JunMingShi::Api().m_pPlayInputA(pContext->lPlayPort, 
			framebuf, pFrmHdr->dataSize+sizeof(JunMingShi::PLAYFRAMEHDR));
	}
	free(framebuf);
	framebuf = NULL;
}

IVideoServer* JunMingShi_videoserver::clone()
{
//     JunMingShi_videoserver *svr = new JunMingShi_videoserver();
// 	memcpy(svr, this, sizeof(JunMingShi_videoserver));
//     return svr;
	return NULL;
}

bool JunMingShi_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    if (0 < m_lLoginHandle && !logout())
    {
        return false;
    }
    //memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	char szLog[512];
	ZeroMemory(szLog, 512);
	sprintf(szLog, "login ip:%s port:%d user:%s psw:%s", IP, port, user, password);
	g_log.AddLog(string(szLog));
	int iRet = 0;
	iRet = Api_JunMingShi::Api().m_pCreateDvr((int *)&m_lLoginHandle, inet_addr(IP), port);
	if (iRet != 0)
	{
		m_lLoginHandle = 0;
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
		return false;
	}
	JunMingShi::NETDVR_loginInfo_t loginInfo;
	ZeroMemory(&loginInfo, sizeof(loginInfo));
	strcpy(loginInfo.username, user);
	strcpy(loginInfo.loginpass, password);
    iRet = Api_JunMingShi::Api().m_pLogin(m_lLoginHandle, &loginInfo);
    if (iRet != 0)
    {
		Api_JunMingShi::Api().m_pDestroyDvr(m_lLoginHandle);
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 01 登录失败，错误原因：") + m_sLastError);
        return false;
    }

// 	iRet = Api_JunMingShi::Api().m_pSetCb(m_lLoginHandle, down_PROGRESS_callback, 0);
// 	if (iRet != 0)
// 	{
// 		Api_JunMingShi::Api().m_pDestroyDvr(m_lLoginHandle);
// 		Api_JunMingShi::Api().m_pLogout(m_lLoginHandle);
// 		m_sLastError = "设置下载进度回调函数失败";
// 		g_log.AddLog(string("login 设置下载进度回调函数失败，错误原因：") + m_sLastError);
// 		return false;
// 	}

	JunMingShi::NETDVR_DeviceInfo_t deviceInfo;
	Api_JunMingShi::Api().m_pGetDeviceInfo(m_lLoginHandle, &deviceInfo);

	channels.clear();
	char szName[32+2];
	for (int i = 1; i <= deviceInfo.maxChnNum; i++)
	{
		ZeroMemory(szName, sizeof(szName));
		sprintf(szName, "通道%d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}
	ZeroMemory(szLog, 512);
	sprintf(szLog, "login 通道个数:%d", deviceInfo.maxChnNum);
	g_log.AddLog(string(szLog));

    return true;
}

bool JunMingShi_videoserver::logout()
{
	if (m_lLoginHandle <= 0)
	{
		m_sLastError = GetLastErrorString();
		return false;
	}
	int iRet = 0;
	iRet = Api_JunMingShi::Api().m_pLogout(m_lLoginHandle);
	if (iRet < 0)
	{
		m_sLastError = GetLastErrorString();
		return false;
	}
	iRet = Api_JunMingShi::Api().m_pDestroyDvr(m_lLoginHandle);
    if (iRet < 0)
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}

#define MAX_SEARCH_COUNT 1000
bool JunMingShi_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    if (m_lLoginHandle <= 0)
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
	//m_mapArcItem.clear();
    struct timeb tb;
    ftime(&tb);
    //timeStart -= tb.timezone * 60;
    //timeEnd -= tb.timezone * 60;
    JunMingShi::NETDVR_fileSearchCondition_t searchCond;

    searchCond.type = JunMingShi::NETDVR_REC_INDEX_ALL;

	auto itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
		int nChannelId = *itr;
        searchCond.chn = nChannelId;
		searchCond.startID = 1;
		searchCond.max_return = 24;
        searchCond.start_time = timeStart;
        searchCond.end_time = timeEnd;
        do 
        {
            JunMingShi::NETDVR_recFileSearchResult_t searchRest = { NULL };

            int iRet = Api_JunMingShi::Api().m_pSearchFileByTime(m_lLoginHandle, &searchCond, &searchRest);
            if (iRet != 0)
            {
                m_sLastError = GetLastErrorString();
                g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
                break;
            }
            if (searchRest.sum <= 0)
            {
                g_log.AddLog(string("GetRecordFileList 查询录像成功，录像个数为0"));
                break;
            }
            char szLog[512];
            ZeroMemory(szLog, 512);
            sprintf(szLog, "GetRecordFileList 查询录像成功，录像个数为:%d", searchRest.sum);
            g_log.AddLog(string(szLog));
            JunMingShi::NETDVR_recFileInfo_t *pFileInfo = searchRest.precInfo;
            char szName[128];
            g_log.AddLog(QString("searchRest.sum:%1, searchCond.max_return:%2, startID:%3,"
                "endID:%4").arg(searchRest.sum).arg(searchCond.max_return).arg(searchRest.startID).arg(searchRest.endID));
            for (int i = searchRest.startID; i <= searchRest.endID && pFileInfo != NULL; i++)
            {
                RecordFile info;
                info.channel = nChannelId/*pFileInfo->channel_no*/;
                info.size = pFileInfo->size;
                string strName = pFileInfo->filename;
                strName.erase(strName.length() - 4, 4);
                int iIndex = strName.rfind('/');
                if (iIndex != string::npos)
                {
                    strName.erase(0, iIndex + 1);
                }

                ZeroMemory(szName, sizeof(szName));
                sprintf(szName, "channel%d_%s", nChannelId, strName.c_str());

                info.name = szName;
                info.beginTime = pFileInfo->start_time;
                info.endTime = pFileInfo->end_time;
                if (searchCond.start_time < info.endTime)
                {
                    //    searchCond.start_time = info.endTime;
                }
                info.setPrivateData(pFileInfo, sizeof(JunMingShi::NETDVR_recFileInfo_t));
                files.push_back(info);

                pFileInfo = pFileInfo->pnext;
            }

            
            g_log.AddLog(QString("searchRest.sum:%1, searchCond.max_return:%2, startID:%3,"
                "endID:%4").arg(searchRest.sum).arg(searchCond.max_return).arg(searchRest.startID).arg(searchRest.endID));
            if (searchRest.sum < searchCond.max_return)
            {
                Api_JunMingShi::Api().m_pSearchFileByTimeClean(&searchRest);
                break;
            }
            else{
                
                searchCond.startID = searchRest.endID + 1;
                Api_JunMingShi::Api().m_pSearchFileByTimeClean(&searchRest);
            }

           
            
        } while (true);
        
	}
    std::sort(files.begin(), files.end(), [](const RecordFile& a, const RecordFile& b){
        return a.beginTime < b.beginTime;
    });
	return true;
}

void CALLBACK callbackDLProgress(struct JunMingShi::NETDVR_progressParam_t progress, unsigned int dwContent)
{
	if (progress.curr_pos >= progress.total_size)
	{
		//AfxMessageBox("Download finished !\n");
		g_log.AddLog(string("Download finished !"));
	}
}

HANDLE g_hEventDownErr = CreateEventA(NULL, FALSE, FALSE, NULL);
void CALLBACK callbackDLError(unsigned short err_code, unsigned int dwContent)
{
	if (err_code != 0)
	{
		char szErr[MAX_PATH];
		ZeroMemory(szErr, sizeof(szErr));
		sprintf(szErr, "Download err_code  = %d", err_code);
		//szErr.Format("Download err_code  = %d", err_code);
		//AfxMessageBox(szErr);
		g_log.AddLog(string(szErr));
		return;
	}
	SetEvent(g_hEventDownErr);
}

void replace(string &str, char x, char y)
{
	int i = str.find(x);
	while (i != string::npos)
	{
		//g_log.AddLog(str);
		str.at(i) = y;
		
		if (i >= str.length()-1)
		{
			break;
		}
		i = str.find(x, i + 1);
	}
}

bool JunMingShi_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
	}
	if (m_mapDownload.size() > 0)
	{
		m_sLastError = "不支持多线程下载";
		g_log.AddLog(string("downLoadByRecordFile 不支持多线程下载"));
		return false;
	}

// 	JunMingShi::NETDVR_recFileInfo_t info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, JunMingShi::NETDVR_recFileInfo_t>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}

	string strPath = saveFileName;
	int iIndex = strPath.rfind('/');
	if (iIndex == string::npos)
	{
		m_sLastError = "该文件不存在";
		g_log.AddLog(string("downLoadByRecordFile 01 该文件不存在"));
		return false;
	}
	string strDir = strPath.substr(0, iIndex);
	string strSaveName = strPath.substr(iIndex + 1, strPath.length() - iIndex - 1);
	//strDir = "F:\\测试磁盘导出中文路径问题";
	//ATL::CStringA strDirTmp(strDir.c_str());
	replace(strDir, '/', '\\');
	g_log.AddLog(string("downLoadByRecordFile 保存路径:") + strDir + string(" 保存文件名:") + strSaveName);
	int iRet = Api_JunMingShi::Api().m_pSetDownPosCallback(m_lLoginHandle, down_PROGRESS_callback, (unsigned int)this);
	iRet = Api_JunMingShi::Api().m_pSetDownErrCallback(m_lLoginHandle, callbackDLError, 0);

	JunMingShi::NETDVR_recFileInfo_t* pData = (JunMingShi::NETDVR_recFileInfo_t *)file.getPrivateData();
	iRet = Api_JunMingShi::Api().m_pDownloadByFile(m_lLoginHandle, (char *)strDir.c_str(), (char *)strSaveName.c_str(), pData);
	if (iRet != 0)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
		return false;
	}
// 	DWORD dwRet = WaitForSingleObject(g_hEventDownErr, 1000);
// 	if (dwRet == WAIT_TIMEOUT)
// 	{
// 		m_sLastError = GetLastErrorString();
// 		g_log.AddLog(string("downLoadByRecordFile 01 下载录像失败，错误原因：") + m_sLastError);
// 		return false;
// 	}
	hdl = INT_MAX;

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownload.insert(std::make_pair(INT_MAX, file));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDown.insert(std::make_pair(INT_MAX, pos));
	}

	return true;
}

//没有传入句柄
bool  JunMingShi_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
		return false;
	}

// 	JunMingShi::NETDVR_recFileInfo_t info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, JunMingShi::NETDVR_recFileInfo_t>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("PlayBackByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}

	long lPlayPort = 0;
	bool bRet = Api_JunMingShi::Api().m_pPlayGetPort(&lPlayPort);
	if (!bRet)
	{
		m_sLastError = "获取播放句柄失败";
		g_log.AddLog(string("PlayBackByRecordFile 获取播放句柄失败，错误原因：") + m_sLastError);
		return false;
	}
	g_log.AddLog(string("PlayBackByRecordFile 获取播放句柄成功"));
	bRet = Api_JunMingShi::Api().m_pPlaySetMode(lPlayPort, JunMingShi::TL_PLAY_REALTIME_STREAM);
	if (!bRet)
	{
		m_sLastError = "设置播放模式失败";
		g_log.AddLog(string("PlayBackByRecordFile 设置播放模式失败，错误原因：") + m_sLastError);
		return false;
	}
	g_log.AddLog(string("PlayBackByRecordFile 设置播放模式成功"));
	bRet = Api_JunMingShi::Api().m_pPlayOpenStream(lPlayPort, 2*1024*1024);
	if (!bRet)
	{
		m_sLastError = "打开播放流失败";
		g_log.AddLog(string("PlayBackByRecordFile 打开播放流失败，错误原因：") + m_sLastError);
		return false;
	}
	g_log.AddLog(string("PlayBackByRecordFile 打开播放流成功"));
// 	bRet = Api_JunMingShi::Api().m_pPlaySetDelay(lPlayPort, 0, 0);
// 	if (!bRet)
// 	{
// 		m_sLastError = "设置延时失败";
// 		g_log.AddLog(string("PlayBackByRecordFile 设置延时失败，错误原因：") + m_sLastError);
// 		return false;
// 	}
// 	g_log.AddLog(string("PlayBackByRecordFile 设置延时成功"));
	bRet = Api_JunMingShi::Api().m_pPlayPlay(lPlayPort, hwnd);
	if (!bRet)
	{
		m_sLastError = "开始播放失败";
		g_log.AddLog(string("PlayBackByRecordFile 开始播放失败，错误原因：") + m_sLastError);
		return false;
	}
	g_log.AddLog(string("PlayBackByRecordFile 开始播放成功"));

	PlayCBContext *pContext = new PlayCBContext;
	pContext->iWnd = (unsigned int)hwnd;
	pContext->iThis = (unsigned int)this;
	pContext->lPlayPort = lPlayPort;

	JunMingShi::PlayBackClientInfo_t pbci_t={0};
	pbci_t.sendmode = 0;
	pbci_t.pEncFrameCBFunc = get_encframe;
	pbci_t.dwEncFrameContent = (unsigned int)pContext;
	pbci_t.pDecFrameCBFunc = NULL;
	pbci_t.dwDecFrameContent = 0;
	pbci_t.pPlayOverCBFunc = NULL;
	pbci_t.dwPlayOverContent = 0;
	pbci_t.pProgressCBFunc = play_PROGRESS_callback;
	pbci_t.dwProgressContent = (unsigned int)pContext;

	JunMingShi::NETDVR_recFileInfo_t* pData = (JunMingShi::NETDVR_recFileInfo_t *)file.getPrivateData();
	int iRet = Api_JunMingShi::Api().m_pPlayBackByFile(m_lLoginHandle, pData, &pbci_t, (int *)&playbackHandle);
	if (iRet != 0)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
		return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapPlay.insert(std::make_pair(playbackHandle, file));
		m_mapWndHandle.insert(std::make_pair((unsigned int)pContext, playbackHandle));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosPlay.insert(std::make_pair(playbackHandle, pos));
	}

	return true;
}

bool JunMingShi_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
	RecordFile recFile;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapPlay.find(playbackHandle);
		if (itr == m_mapPlay.end())
		{
			m_sLastError = "回放句柄无效";
			g_log.AddLog(string("SetPlayBack 回放句柄无效"));
			return false;
		}

		recFile = itr->second;
	}

	unsigned int totaltime = recFile.endTime - recFile.beginTime; //sec
	unsigned int newpos =(totaltime*pos/100)*1000;

	int iRet = Api_JunMingShi::Api().m_pSeekPlayBack(m_lLoginHandle, newpos);
	if (iRet < 0)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("SetPlayBack 拖动播放失败，错误原因：") + m_sLastError);
		return false;
	}
	return true;
}

bool JunMingShi_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
{
	PlayCBContext *pContext = NULL;
	map<unsigned int, long long>::iterator itr;
	{
		Mutex::ScopedLock lock(m_mtx);
		itr = m_mapWndHandle.begin();
		for ( ; itr != m_mapWndHandle.end(); itr++)
		{
			if (itr->second == playbackHandle)
			{
				pContext = (PlayCBContext *)itr->first;
				break;
			}
		}
		if (itr == m_mapWndHandle.end())
		{
			m_sLastError = "回放句柄无效";
			g_log.AddLog(string("StopPlayBack 回放句柄无效"));
			return false;
		}
	}

	if (mPause == 1)
	{
		g_log.AddLog(string("StopPlayBack 开始暂停播放"));
		int iRet = Api_JunMingShi::Api().m_pPausePlayBack(playbackHandle);
		if (iRet != 0)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 暂停播放失败，错误原因:") + m_sLastError);
			return false;
		}
	}
	else
	{
		g_log.AddLog(string("StopPlayBack 开始停止播放"));
		int iRet = Api_JunMingShi::Api().m_pStopPlayBack(playbackHandle);
		if (iRet != 0)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因:") + m_sLastError);
			return false;
		}

		bool bRet = Api_JunMingShi::Api().m_pPlayStop(pContext->lPlayPort);
		if (!bRet)
		{
			m_sLastError = "停止播放失败";
			g_log.AddLog(string("StopPlayBack 01 停止播放失败，错误原因:") + m_sLastError);
			return false;
		}
		bRet = Api_JunMingShi::Api().m_pPlayClose(pContext->lPlayPort);
		if (!bRet)
		{
			m_sLastError = "关闭播放失败";
			g_log.AddLog(string("StopPlayBack 02 停止播放失败，错误原因:") + m_sLastError);
			return false;
		}
		bRet = Api_JunMingShi::Api().m_pPlayFreePort(pContext->lPlayPort);
		if (!bRet)
		{
			m_sLastError = "释放播放句柄失败";
			g_log.AddLog(string("StopPlayBack 03 停止播放失败，错误原因:") + m_sLastError);
			return false;
		}
		delete pContext;

		{
			Mutex::ScopedLock lock(m_mtx);
			Mutex::ScopedLock lock2(m_mtxPos);
			m_mapPlay.erase(playbackHandle);
			m_mapWndHandle.erase(itr);
			m_mapPosPlay.erase(playbackHandle);
		}
	}


    return true;
}

bool JunMingShi_videoserver::stopDownload(download_handle_t h)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
        return false;
    }
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapDownload.find(h);
		if (itr == m_mapDownload.end())
		{
			m_sLastError = "下载句柄无效";
			g_log.AddLog(string("stopDownload 下载句柄无效"));
			return false;
		}
		m_mapDownload.erase(h);
	}
	{
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDown.erase(h);
	}

	int iRet = Api_JunMingShi::Api().m_pStopDownload(m_lLoginHandle);
    if (iRet != 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因:") + m_sLastError);
        return false;
    }

    return true;
}

bool JunMingShi_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getPlayBackPos 请先登录"));
		return false;
	}

	Mutex::ScopedLock lock(m_mtxPos);
	map<long long, stPos_DownPlay>::iterator itr = m_mapPosPlay.find(playbackHandle);
	if (itr != m_mapPosPlay.end())
	{
		*pos = itr->second.iPercent;
		return true;
	}
	m_sLastError = "找不到该回放";
	g_log.AddLog(string("getPlayBackPos 找不到该回放"));
	return false;
}

bool JunMingShi_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}

	Mutex::ScopedLock lock(m_mtxPos);
	map<long long, stPos_DownPlay>::iterator itr = m_mapPosDown.find(h);
	if (itr != m_mapPosDown.end())
	{
		*totalSize = itr->second.iTotalSize;
		*currentSize = itr->second.iCurSize;

		*failed = false;
		return true;
	}
	m_sLastError = "找不到该下载";
	g_log.AddLog(string("getDownloadPos 找不到该下载"));
	*failed = true;
	return false;
}
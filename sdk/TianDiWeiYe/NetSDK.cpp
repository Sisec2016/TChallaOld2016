#include "NetSDK.h"

HINSTANCE g_hNVSSDK = NULL;
HINSTANCE g_hPlaySdk = NULL;


pfNetClient_Startup_V4 NetClient_Startup_V4 = NULL;
pfNetClient_Logon NetClient_Logon = NULL;
pfNetClient_Logoff NetClient_Logoff = NULL;
pfNetClient_GetChannelNum  NetClient_GetChannelNum = NULL;
pfNetClient_StartRecv NetClient_StartRecv = NULL;
pfNetClient_StartPlay NetClient_StartPlay = NULL;
pfNetClient_StopPlay NetClient_StopPlay = NULL;
pfNetClient_SetNotifyFunction_V4 NetClient_SetNotifyFunction_V4 = NULL;
pfNetClient_Cleanup NetClient_Cleanup = NULL;
pfNetClient_NetFileQuery NetClient_NetFileQuery = NULL;
pfNetClient_NetFileQueryEx NetClient_NetFileQueryEx = NULL;
pfNetClient_NetFileGetFileCount NetClient_NetFileGetFileCount = NULL; 
pfNetClient_NetFileGetQueryfile NetClient_NetFileGetQueryfile = NULL;
pfNetClient_NetFileDownloadFile NetClient_NetFileDownloadFile = NULL;
IMPLEMENT_FUNCTION(NetClient_NetFileDownload);
pfNetClient_SetNetFileDownloadFileCallBack NetClient_SetNetFileDownloadFileCallBack = NULL;
pfNetClient_VCASetConfig NetClient_VCASetConfig = NULL;
pfNetClient_VCAGetConfig NetClient_VCAGetConfig = NULL;
pfNetClient_VCARestartEx NetClient_VCARestartEx = NULL;
pfTC_CreateSystem TC_CreateSystem = NULL;
pfTC_DeleteSystem TC_DeleteSystem  = NULL;
pfTC_RegisterCommonEventCallBack_V4 TC_RegisterCommonEventCallBack_V4 = NULL;
pfTC_CreatePlayerFromFile TC_CreatePlayerFromFile = NULL;
pfTC_DeletePlayer TC_DeletePlayer = NULL;
pfTC_Play TC_Play = NULL;
pfTC_Stop TC_Stop = NULL;
pfTC_CreatePlayerFromVoD TC_CreatePlayerFromVoD = NULL;
pfTC_PutStreamToPlayer TC_PutStreamToPlayer = NULL;
pfTC_GetStreamPlayBufferState TC_GetStreamPlayBufferState = NULL;
pfNetClient_NetFileDownloadByTimeSpanEx NetClient_NetFileDownloadByTimeSpanEx = NULL;

pfNetClient_NetFileStopDownloadFile NetClient_NetFileStopDownloadFile = NULL;
pfNetClient_NetFileGetDownloadPos NetClient_NetFileGetDownloadPos = NULL;
pfNetClient_GetMaxConUser NetClient_GetMaxConUser = NULL;

pfNetClient_GetDigitalChannelConfig NetClient_GetDigitalChannelConfig = NULL;
pfNetClient_SetDigitalChannelConfig NetClient_SetDigitalChannelConfig = NULL;
pfNetClient_GetChannelProperty NetClient_GetChannelProperty = NULL;
pfNetClient_TalkStart NetClient_TalkStart = NULL;
pfNetClient_TalkEnd	NetClient_TalkEnd = NULL;
pfNetClient_InterTalkStart NetClient_InterTalkStart = NULL;
pfNetClient_InterTalkEnd NetClient_InterTalkEnd = NULL;
pfNetClient_AudioStart NetClient_AudioStart = NULL;
pfNetClient_LogonEx NetClient_LogonEx = NULL; 
pfNetClient_GetDeviceType NetClient_GetDeviceType = NULL;
pfNetClient_ComSend NetClient_ComSend = NULL;
pfNetClient_NetLogQuery NetClient_NetLogQuery = NULL;
pfNetClient_NetLogGetLogCount NetClient_NetLogGetLogCount = NULL;
pfNetClient_NetLogGetLogfile NetClient_NetLogGetLogfile = NULL;
pNetClient_GetVideoPara NetClient_GetVideoPara = NULL;
pNetClient_SetVideoPara NetClient_SetVideoPara = NULL;
pNetClient_SetDevConfig NetClient_SetDevConfig = NULL;
pNetClient_GetDevConfig NetClient_GetDevConfig = NULL;
pNetClient_SetMotionDecLinkOutport	NetClient_SetMotionDecLinkOutport = NULL;
pNetClient_SetMotionDetectSchedule	NetClient_SetMotionDetectSchedule = NULL;
pNetClient_SetThreshold NetClient_SetThreshold = NULL;
pNetClient_SetMotionDetection NetClient_SetMotionDetection = NULL;
pNetClient_GetMotionDecLinkOutport NetClient_GetMotionDecLinkOutport = NULL;
pNetClient_GetMotionDetectSchedule NetClient_GetMotionDetectSchedule = NULL;
pNetClient_GetThreshold NetClient_GetThreshold = NULL;

int LoadNVSSDK()
{
	if (g_hNVSSDK)
		return	-2;
	else
	{
		g_hNVSSDK = LoadLibraryA(".\\NVSSDK.dll");
		if(!g_hNVSSDK) 
			return -1;
	}

	NetClient_Startup_V4 = (pfNetClient_Startup_V4)GetProcAddress(g_hNVSSDK, "NetClient_Startup_V4");
	NetClient_Logon = (pfNetClient_Logon)GetProcAddress(g_hNVSSDK, "NetClient_Logon");
	NetClient_Logoff = (pfNetClient_Logoff)GetProcAddress(g_hNVSSDK, "NetClient_Logoff");
	NetClient_GetChannelNum = (pfNetClient_GetChannelNum)GetProcAddress(g_hNVSSDK, "NetClient_GetChannelNum");
	NetClient_StartPlay = (pfNetClient_StartPlay)GetProcAddress(g_hNVSSDK, "NetClient_StartPlay");
	NetClient_StartRecv = (pfNetClient_StartRecv)GetProcAddress(g_hNVSSDK, "NetClient_StartRecv");
	NetClient_StopPlay = (pfNetClient_StopPlay)GetProcAddress(g_hNVSSDK, "NetClient_StopPlay");
	NetClient_SetNotifyFunction_V4 = (pfNetClient_SetNotifyFunction_V4)GetProcAddress(g_hNVSSDK, "NetClient_SetNotifyFunction_V4");
	NetClient_Cleanup = (pfNetClient_Cleanup)GetProcAddress(g_hNVSSDK, "NetClient_Cleanup");
	NetClient_NetFileQuery = (pfNetClient_NetFileQuery)GetProcAddress(g_hNVSSDK, "NetClient_NetFileQuery");
    NetClient_NetFileQueryEx = (pfNetClient_NetFileQueryEx)GetProcAddress(g_hNVSSDK, "NetClient_NetFileQueryEx");
	NetClient_NetFileGetFileCount = (pfNetClient_NetFileGetFileCount)GetProcAddress(g_hNVSSDK, "NetClient_NetFileGetFileCount");
	NetClient_NetFileGetQueryfile = (pfNetClient_NetFileGetQueryfile)GetProcAddress(g_hNVSSDK, "NetClient_NetFileGetQueryfile");
	NetClient_NetFileDownloadFile = (pfNetClient_NetFileDownloadFile)GetProcAddress(g_hNVSSDK, "NetClient_NetFileDownloadFile");
    EXPORT_FUNCTION(g_hNVSSDK, NetClient_NetFileDownload);
	NetClient_SetNetFileDownloadFileCallBack = (pfNetClient_SetNetFileDownloadFileCallBack)GetProcAddress(g_hNVSSDK, "NetClient_SetNetFileDownloadFileCallBack");
	NetClient_VCASetConfig = (pfNetClient_VCASetConfig)GetProcAddress(g_hNVSSDK,"NetClient_VCASetConfig");
	NetClient_VCAGetConfig = (pfNetClient_VCAGetConfig)GetProcAddress(g_hNVSSDK,"NetClient_VCAGetConfig");
	NetClient_VCARestartEx = (pfNetClient_VCARestartEx)GetProcAddress(g_hNVSSDK,"NetClient_VCARestartEx");
	NetClient_NetFileDownloadByTimeSpanEx = (pfNetClient_NetFileDownloadByTimeSpanEx)GetProcAddress(g_hNVSSDK,"NetClient_NetFileDownloadByTimeSpanEx");

	NetClient_NetFileStopDownloadFile = (pfNetClient_NetFileStopDownloadFile)GetProcAddress(g_hNVSSDK, "NetClient_NetFileStopDownloadFile");
	NetClient_NetFileGetDownloadPos = (pfNetClient_NetFileGetDownloadPos)GetProcAddress(g_hNVSSDK, "NetClient_NetFileGetDownloadPos");
	NetClient_GetMaxConUser = (pfNetClient_GetMaxConUser)GetProcAddress(g_hNVSSDK, "NetClient_GetMaxConUser");

	NetClient_GetDigitalChannelConfig = (pfNetClient_GetDigitalChannelConfig)GetProcAddress(g_hNVSSDK,"NetClient_GetDigitalChannelConfig");
	NetClient_SetDigitalChannelConfig = (pfNetClient_SetDigitalChannelConfig)GetProcAddress(g_hNVSSDK,"NetClient_SetDigitalChannelConfig");
	NetClient_GetChannelProperty = (pfNetClient_GetChannelProperty)GetProcAddress(g_hNVSSDK,"NetClient_GetChannelProperty");
	NetClient_TalkStart = (pfNetClient_TalkStart)GetProcAddress(g_hNVSSDK,"NetClient_TalkStart");
	NetClient_TalkEnd = (pfNetClient_TalkEnd)GetProcAddress(g_hNVSSDK,"NetClient_TalkEnd");
	NetClient_InterTalkStart = (pfNetClient_InterTalkStart)GetProcAddress(g_hNVSSDK,"NetClient_InterTalkStart");
	NetClient_InterTalkEnd = (pfNetClient_InterTalkEnd)GetProcAddress(g_hNVSSDK,"NetClient_InterTalkEnd");
	NetClient_AudioStart = (pfNetClient_AudioStart)GetProcAddress(g_hNVSSDK,"NetClient_AudioStart");
    NetClient_LogonEx = (pfNetClient_LogonEx)GetProcAddress(g_hNVSSDK,"NetClient_LogonEx");
	NetClient_ComSend = (pfNetClient_ComSend)GetProcAddress(g_hNVSSDK,"NetClient_ComSend");
	NetClient_GetDeviceType = (pfNetClient_GetDeviceType)GetProcAddress(g_hNVSSDK,"NetClient_GetDeviceType");
    NetClient_NetLogQuery = (pfNetClient_NetLogQuery)GetProcAddress(g_hNVSSDK, "NetClient_NetLogQuery");
	NetClient_NetLogGetLogCount = (pfNetClient_NetLogGetLogCount)GetProcAddress(g_hNVSSDK, "NetClient_NetLogGetLogCount");
	NetClient_NetLogGetLogfile = (pfNetClient_NetLogGetLogfile)GetProcAddress(g_hNVSSDK, "NetClient_NetLogGetLogfile");
    NetClient_GetVideoPara = (pNetClient_GetVideoPara)GetProcAddress(g_hNVSSDK, "NetClient_GetVideoPara");
	NetClient_SetVideoPara = (pNetClient_SetVideoPara)GetProcAddress(g_hNVSSDK, "NetClient_SetVideoPara");
	NetClient_SetDevConfig = (pNetClient_SetDevConfig)GetProcAddress(g_hNVSSDK, "NetClient_SetDevConfig");
	NetClient_GetDevConfig = (pNetClient_GetDevConfig)GetProcAddress(g_hNVSSDK, "NetClient_GetDevConfig");
    NetClient_SetMotionDetection = (pNetClient_SetMotionDetection)GetProcAddress(g_hNVSSDK, "NetClient_SetMotionDetection");	
	NetClient_SetThreshold = (pNetClient_SetThreshold)GetProcAddress(g_hNVSSDK, "NetClient_SetThreshold");	
	NetClient_SetMotionDetectSchedule = (pNetClient_SetMotionDetectSchedule)GetProcAddress(g_hNVSSDK, "NetClient_SetMotionDetectSchedule");
	NetClient_SetMotionDecLinkOutport = (pNetClient_SetMotionDecLinkOutport)GetProcAddress(g_hNVSSDK, "NetClient_SetMotionDecLinkOutport");	
	NetClient_GetThreshold = (pNetClient_GetThreshold)GetProcAddress(g_hNVSSDK, "NetClient_GetThreshold");
	NetClient_GetMotionDecLinkOutport = (pNetClient_GetMotionDecLinkOutport)GetProcAddress(g_hNVSSDK, "NetClient_GetMotionDecLinkOutport");	
	NetClient_GetMotionDetectSchedule = (pNetClient_GetMotionDetectSchedule)GetProcAddress(g_hNVSSDK, "NetClient_GetMotionDetectSchedule");

	return 0;
}

void FreeNVSSDK()
{
	if(g_hNVSSDK)
	{
		::FreeLibrary(g_hNVSSDK);
		g_hNVSSDK = NULL;
	}
}

int LoadPlaySdk()
{
	if (g_hPlaySdk)
		return	-2;
	else
	{
		g_hPlaySdk = LoadLibraryA(".\\PlaySdkM4.dll");
		if(!g_hPlaySdk) 
			return -1;
	}

	TC_CreateSystem = (pfTC_CreateSystem)GetProcAddress(g_hPlaySdk, "TC_CreateSystem");
	TC_DeleteSystem = (pfTC_DeleteSystem)GetProcAddress(g_hPlaySdk, "TC_DeleteSystem");
	TC_RegisterCommonEventCallBack_V4 = (pfTC_RegisterCommonEventCallBack_V4)GetProcAddress(g_hPlaySdk, "TC_RegisterCommonEventCallBack_V4");
	TC_CreatePlayerFromFile = (pfTC_CreatePlayerFromFile)GetProcAddress(g_hPlaySdk, "TC_CreatePlayerFromFile");
	TC_DeletePlayer = (pfTC_DeletePlayer)GetProcAddress(g_hPlaySdk, "TC_DeletePlayer");
	TC_Play = (pfTC_Play)GetProcAddress(g_hPlaySdk, "TC_Play");
	TC_Stop = (pfTC_Stop)GetProcAddress(g_hPlaySdk, "TC_Stop");
	TC_CreatePlayerFromVoD = (pfTC_CreatePlayerFromVoD)GetProcAddress(g_hPlaySdk,"TC_CreatePlayerFromVoD");
	TC_PutStreamToPlayer = (pfTC_PutStreamToPlayer)GetProcAddress(g_hPlaySdk,"TC_PutStreamToPlayer");
	TC_GetStreamPlayBufferState = (pfTC_GetStreamPlayBufferState)GetProcAddress(g_hPlaySdk,"TC_GetStreamPlayBufferState");

	return 0;
}

void FreePlaySdk()
{
	if(g_hPlaySdk)
	{
		::FreeLibrary(g_hPlaySdk);
		g_hPlaySdk = NULL;
	}
}

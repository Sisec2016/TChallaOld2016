#ifndef NETSDK_H
#define NETSDK_H

#include "NetClientTypes.h"

#define USER_ERROR  0x10000000
#define ERROR_ALREADY_INTERTALK			(USER_ERROR+0x32)		//正在进行双向对讲

#define TYPEDEF_FUNCTION(funcName)  typedef int (__stdcall* pf##funcName)
#define DECLARE_FUNCTION(funcName)	extern pf##funcName funcName
#define TYPEDEF_FUNCTION2(funcName)  typedef int (__cdecl* pf##funcName)
#define IMPLEMENT_FUNCTION(funcName)  pf##funcName funcName = NULL
//#define EXPORT_FUNCTION(hDll, funcName)	if(NULL == (funcName = (pf##funcName)::GetProcAddress(hDll, #funcName))) {return DLL_FUN_EXPORT_FAILED;}
#define EXPORT_FUNCTION(hDll, funcName)	funcName = (pf##funcName)::GetProcAddress(hDll, #funcName);
#define  TYPEDEF_FUNCTION_RET(retType, funcName) typedef retType (__stdcall* pf##funcName)

//NVSSDK初始化
typedef int (__stdcall *pfNetClient_Startup_V4)(int _iServerPort, int _iClientPort, int _iWnd);
extern pfNetClient_Startup_V4	NetClient_Startup_V4;
typedef int (__stdcall *pfNetClient_Cleanup)();
extern pfNetClient_Cleanup  NetClient_Cleanup;
typedef int (__stdcall *pfNetClient_SetNotifyFunction_V4)(MAIN_NOTIFY_V4 _MainNotify, ALARM_NOTIFY_V4 _AlarmNotify, PARACHANGE_NOTIFY_V4  _ParaNotify, COMRECV_NOTIFY_V4 _ComNotify, PROXY_NOTIFY _ProxyNotify);
extern pfNetClient_SetNotifyFunction_V4  NetClient_SetNotifyFunction_V4;

//登录
typedef int (__stdcall *pfNetClient_Logon)(char* _cProxy, char* _cIP, char* _cUserName, char* _cPassword, char* _pcProID, int _iPort);
extern pfNetClient_Logon	NetClient_Logon;
typedef int (__stdcall *pfNetClient_Logoff)(int _iLogonID);
extern pfNetClient_Logoff	NetClient_Logoff;
typedef int (__stdcall *pfNetClient_GetChannelNum)(int _iLogonID, int* _iChannelNum);
extern pfNetClient_GetChannelNum NetClient_GetChannelNum;

//视频预览
typedef int (__stdcall *pfNetClient_StartRecv)(unsigned int *_ulConID, CLIENTINFO* _cltInfo, RECVDATA_NOTIFY _cbkDataArrive);
extern pfNetClient_StartRecv  NetClient_StartRecv;
typedef int (__stdcall *pfNetClient_StartPlay)(unsigned int _ulID, HWND _hWnd, RECT _rcShow, unsigned int _iDecflag);
extern pfNetClient_StartPlay  NetClient_StartPlay;
typedef int (__stdcall *pfNetClient_StopPlay)(unsigned int _ulID);
extern pfNetClient_StopPlay  NetClient_StopPlay;
typedef int (__stdcall *pfNetClient_AudioStart)(unsigned long _ulConID);
extern	pfNetClient_AudioStart NetClient_AudioStart;

//文件下载
typedef int (__stdcall* pfNetClient_NetFileQuery)(int _iLogonID, PNVS_FILE_QUERY _fileQuery);
extern pfNetClient_NetFileQuery NetClient_NetFileQuery;
typedef int(__stdcall* pfNetClient_NetFileQueryEx)(int _iLogonID, PNVS_FILE_QUERY _pFileQuery, int _iSize);
extern pfNetClient_NetFileQueryEx NetClient_NetFileQueryEx;
typedef int (__stdcall *pfNetClient_NetFileGetFileCount)(int _iLogonID, int *_iTotalCount, int *_iCurrentCount);
extern pfNetClient_NetFileGetFileCount NetClient_NetFileGetFileCount; 
typedef int (__stdcall *pfNetClient_NetFileGetQueryfile)(int _iLogonID, int _iFileIndex, PNVS_FILE_DATA _fileInfo);
extern pfNetClient_NetFileGetQueryfile NetClient_NetFileGetQueryfile;
typedef int (__stdcall *pfNetClient_NetFileDownloadFile)(unsigned long *_ulConID,int _iLogonID, char* _cRemoteFilename, char* _cLocalFilename, int _iFlag /*= 0*/, int _iPosition /*= -1*/, int _Speed /*= 1*/);
extern pfNetClient_NetFileDownloadFile NetClient_NetFileDownloadFile;

TYPEDEF_FUNCTION(NetClient_NetFileDownload)(unsigned int *_ulConID, int _iLogonID, int _iCmd, void* _lpBuf, int _iBufSize);
DECLARE_FUNCTION(NetClient_NetFileDownload);

typedef int (__stdcall *pfNetClient_SetNetFileDownloadFileCallBack)(unsigned long _ulConID, RECV_DOWNLOADDATA_NOTIFY _cbkDataNotify, void* _lpUserData);
extern	pfNetClient_SetNetFileDownloadFileCallBack NetClient_SetNetFileDownloadFileCallBack;
typedef int (__stdcall *pfNetClient_NetFileDownloadByTimeSpanEx)( unsigned int* _ulConID, int _iLogonID, char* _pcLocalFile, int _iChannelNO, NVS_FILE_TIME *_pTimeBegin, NVS_FILE_TIME *_pTimeEnd, int _iFlag/* = 0*/, int _iPosition/* = -1*/,int _iSpeed/* = 1*/);
extern pfNetClient_NetFileDownloadByTimeSpanEx NetClient_NetFileDownloadByTimeSpanEx;

/****************************************************************************************************************************************/
typedef int(__stdcall *pfNetClient_NetFileStopDownloadFile)(unsigned int _ulConID);
extern pfNetClient_NetFileStopDownloadFile NetClient_NetFileStopDownloadFile;

typedef int(__stdcall *pfNetClient_NetFileGetDownloadPos)(unsigned int _ulConID, int* _iPos, int* _iDLSize);
extern pfNetClient_NetFileGetDownloadPos NetClient_NetFileGetDownloadPos;

typedef int(__stdcall *pfNetClient_GetMaxConUser)(int _iLogonID, int _iMaxConUser);
extern pfNetClient_GetMaxConUser NetClient_GetMaxConUser;
/****************************************************************************************************************************************/

//智能分析
typedef int (__stdcall *pfNetClient_VCASetConfig)(int _iLogonID, int _iVCACmdID, int _iChannel, void* _lpCmdBuf, int _iCmdBufLen);
extern pfNetClient_VCASetConfig NetClient_VCASetConfig;
typedef int (__stdcall *pfNetClient_VCAGetConfig)(int _iLogonID, int _iVCACmdID, int _iChannel, void* _lpCmdBuf, int _iCmdBufLen);
extern pfNetClient_VCAGetConfig NetClient_VCAGetConfig;

typedef int (__stdcall *pfNetClient_VCARestartEx)(int _iLogonID, int _iChannelNO);
extern pfNetClient_VCARestartEx NetClient_VCARestartEx;

//数字通道
typedef int (__stdcall *pfNetClient_GetDigitalChannelConfig)(int _iLogonID, int _iChannel, int _iCmd, void* _lpCmdBuf, int _iBufSize);
extern pfNetClient_GetDigitalChannelConfig NetClient_GetDigitalChannelConfig;
typedef int (__stdcall *pfNetClient_SetDigitalChannelConfig)(int _iLogonID, int _iChannel, int _iCmd, void* _lpCmdBuf, int _iBufSize);
extern pfNetClient_SetDigitalChannelConfig NetClient_SetDigitalChannelConfig;
typedef int (__stdcall *pfNetClient_GetChannelProperty)(int _iLogonID, int _iChannel, int _iCmd, void* _lpBuf, int _iBufSize);
extern pfNetClient_GetChannelProperty NetClient_GetChannelProperty;

//对讲
typedef int (__stdcall *pfNetClient_TalkStart)(int _iLogonID, int _bUser);
extern	pfNetClient_TalkStart NetClient_TalkStart;
typedef int (__stdcall *pfNetClient_TalkEnd)(int _iLogonID);
extern	pfNetClient_TalkEnd	NetClient_TalkEnd;
typedef	int (__stdcall *pfNetClient_InterTalkStart)(unsigned int * _uiConnID, int _iLogonID, int _iUserData);
extern	pfNetClient_InterTalkStart NetClient_InterTalkStart;
typedef	int (__stdcall *pfNetClient_InterTalkEnd)(unsigned int _uiConnID, bool _blStopTalk);
extern	pfNetClient_InterTalkEnd NetClient_InterTalkEnd;

//PTZ坐标
typedef int (__stdcall *pfNetClient_LogonEx)(char* _cProxy,char* _cIP,char* _cUserName,char* _cPassword,char* _pcProID,int _iPort,char* _pcCharSet);
extern pfNetClient_LogonEx	 NetClient_LogonEx; 
typedef int (__stdcall *pfNetClient_GetDeviceType)(int _iLogonID,int _iChannelNum,int* _iComPort,int* _iDevAddress,char* _cDeviceType);
extern pfNetClient_GetDeviceType NetClient_GetDeviceType;
typedef int (__stdcall *pfNetClient_ComSend)(int _iLogonID,unsigned char* _ucBuf,int _iLength,int _iComNo);
extern pfNetClient_ComSend	 NetClient_ComSend;

//日志管理
typedef int (__stdcall *pfNetClient_NetLogQuery)( int _iLogonID, PNVS_LOG_QUERY _logQuery);
extern pfNetClient_NetLogQuery  NetClient_NetLogQuery;
typedef int (__stdcall *pfNetClient_NetLogGetLogCount)(int _iLogonID, int *_iTotalCount, int *_iCurrentCount);
extern pfNetClient_NetLogGetLogCount  NetClient_NetLogGetLogCount;
typedef int (__stdcall *pfNetClient_NetLogGetLogfile)(int _iLogonID, int _iLogIndex, PNVS_LOG_DATA _pLogInfo);
extern pfNetClient_NetLogGetLogfile  NetClient_NetLogGetLogfile;

//参数配置
typedef int (__stdcall *pNetClient_GetVideoPara)(int _iLogonID, int _iChannelNum, STR_VideoParam* _strVidoParam);
extern pNetClient_GetVideoPara  NetClient_GetVideoPara;
typedef int (__stdcall *pNetClient_SetVideoPara)(int _iLogonID, int _iChannelNum, STR_VideoParam* _strVidoParam);
extern pNetClient_SetVideoPara NetClient_SetVideoPara;
typedef int (__stdcall *pNetClient_SetDevConfig)(int _iLogonID, int _iCommand, int _iChannel, void *_lpInBuffer, int _iInBufferSize);
extern pNetClient_SetDevConfig NetClient_SetDevConfig;
typedef int (__stdcall *pNetClient_GetDevConfig)(int _iLogonID, int _iCommand, int _iChannel, void *_lpOutBuffer, int _iOutBufferSize, int *_lpBytesReturned);
extern pNetClient_GetDevConfig NetClient_GetDevConfig;

//报警模块
//设置联动输出端口
typedef int (__stdcall *pNetClient_SetMotionDecLinkOutport)(int _iLogonID, int _iChannelNum, int _iOutportArray );
extern pNetClient_SetMotionDecLinkOutport NetClient_SetMotionDecLinkOutport ;
//获得联动输出端口
typedef int (__stdcall *pNetClient_GetMotionDecLinkOutport)(int _iLogonID, int _iChannelNum, int* _iOutportArray );
extern pNetClient_GetMotionDecLinkOutport NetClient_GetMotionDecLinkOutport ;
//设置移动报警布防时间段
typedef int (__stdcall *pNetClient_SetMotionDetectSchedule)(  int _iLogonID, int _iChannelNum, int _iWeekday, PNVS_SCHEDTIME _strScheduleParam[MAX_TIMESEGMENT] );
extern pNetClient_SetMotionDetectSchedule NetClient_SetMotionDetectSchedule ;
//获得移动报警布防时间段
typedef int (__stdcall *pNetClient_GetMotionDetectSchedule)(  int _iLogonID, int _iChannelNum, int _iWeekday, PNVS_SCHEDTIME _strScheduleParam[MAX_TIMESEGMENT] );
extern pNetClient_GetMotionDetectSchedule NetClient_GetMotionDetectSchedule ;
//设置移动报警灵敏度
typedef int (__stdcall *pNetClient_SetThreshold)(int _iLogonID, int _iChannelNum, int iThreshold );
extern pNetClient_SetThreshold NetClient_SetThreshold ;
//获得移动抱紧灵敏度
typedef int (__stdcall *pNetClient_GetThreshold)(int _iLogonID, int _iChannelNum, int* iThreshold );
extern pNetClient_GetThreshold NetClient_GetThreshold ;
//使能移动报警
typedef int (__stdcall *pNetClient_SetMotionDetection)(int _iLogonID, int _iChannelNum, int _iEnabled );
extern pNetClient_SetMotionDetection NetClient_SetMotionDetection ;

///////////////////////////回放库//////////////////////////////////////
/************************************************************************
*	TC_PutStreamToPlayer返回值说明                                                                     
************************************************************************/
#define		RET_BUFFER_FULL					(-11)		//	缓冲区满，数据没有放入缓冲区
#define		RET_BUFFER_WILL_BE_FULL			(-18)		//	即将满，降低送入数据的频率
#define		RET_BUFFER_WILL_BE_EMPTY		(-19)		//	即将空，提高送入数据的频率
#define     RET_BUFFER_IS_OK                (-20)       //  正常可以放数据

/*回放器库消息的LPARAM参数取值列表*/
#define  LPARAM_FILE_PLAY_END			0	//	播放完毕
#define  LPARAM_FILE_SEARCH_END			1	//  寻找到文件末尾
#define  LPARAM_NEED_DECRYPT_KEY		2	//	需要解密密码
#define  LPARAM_DECRYPT_KEY_FAILED		3	//	解密密码错误
#define  LPARAM_DECRYPT_SUCCESS			4	//	解密成功
#define  LPARAM_STREAM_SEARCH_END		5   //  流缓冲区中没有数据了
#define  LPARAM_VOD_STREAM_END			6   //  VOD文件流播放完毕

typedef int (__cdecl  *pfTC_CreateSystem)(HWND _hWnd);    
extern pfTC_CreateSystem  TC_CreateSystem;//创建播放系统

typedef int (__cdecl *pfTC_DeleteSystem)();   
extern pfTC_DeleteSystem TC_DeleteSystem;//删除播放器系统

typedef int (__cdecl* pfCBCommonEventNotifyEx)(int _iPlayerID, int _iEventMessage, void* _lpUserData);
typedef int (__cdecl *pfTC_RegisterCommonEventCallBack_V4)(int _iID, pfCBCommonEventNotifyEx _pf, void* _lpUserData);
extern pfTC_RegisterCommonEventCallBack_V4 TC_RegisterCommonEventCallBack_V4;//注册回调

typedef int (__cdecl *pfTC_CreatePlayerFromFile)(HWND _hWnd, char* _pcFileName, int _iDownloadBufSz, int _iFileTrueSz, 
											  int* _piNowSz, int _iLastFrmNo, int* piCompleteFlag);
extern pfTC_CreatePlayerFromFile TC_CreatePlayerFromFile;//创建播放器实例

typedef int (*pfTC_CreatePlayerFromVoD)(HWND _hWnd, unsigned char* _pucVideoHeadBuf, int _iHeadSize);
extern pfTC_CreatePlayerFromVoD TC_CreatePlayerFromVoD;

typedef int ( *pfTC_PutStreamToPlayer )(int ID,unsigned char *_ucData,int _iSize);
extern pfTC_PutStreamToPlayer TC_PutStreamToPlayer;

typedef int (*pfTC_GetStreamPlayBufferState)( int _iID, int * _piStreamBufferState );
extern pfTC_GetStreamPlayBufferState TC_GetStreamPlayBufferState;

typedef int (__cdecl *pfTC_DeletePlayer)(int _iID);   
extern pfTC_DeletePlayer TC_DeletePlayer;//删除播放器实例

typedef int (__cdecl *pfTC_Play)(int _iID);    
extern pfTC_Play TC_Play;//播放
typedef int (__cdecl *pfTC_Stop)(int _iID);    
extern pfTC_Stop TC_Stop;//停止播放

int LoadNVSSDK();
void FreeNVSSDK();

int LoadPlaySdk();
void FreePlaySdk();

#endif

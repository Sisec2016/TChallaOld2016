#ifndef HSX_NETWORK_CLIENT_H
#define HSX_NETWORK_CLIENT_H

#ifdef WIN32
#include <windows.h>

#if defined(NETCLIENT_EXPORT)
#define DVR_NET_API extern "C" __declspec(dllexport) 
#else
#define DVR_NET_API extern "C" __declspec(dllimport) 
#endif

#else // ifndef win32
#define DVR_NET_API extern "C"

#ifndef DWORD
#define DWORD unsigned int
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef HWND
#define HWND unsigned
#endif

#ifndef HDC
#define HDC unsigned
#endif

#ifndef HANDLE
#define HANDLE unsigned
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef __stdcall
#define __stdcall 
#endif

#ifndef CALLBACK 
#define CALLBACK
#endif

#endif // end of (ifdef win32)

////////////////////////////////////////////////////////////////////////////////
// 宏定义
////////////////////////////////////////////////////////////////////////////////

// 输入参数
#define IN
// 输出参数
#define OUT
// 输入输出参数
#define INOUT


// 设备句柄
#define HDEVICE         HANDLE
// 查询句柄
#define HQUERY          HANDLE
// 升级句柄 
#define HUPGRADE        HANDLE
// 下载句柄
#define HDOWNLOAD		HANDLE
// 实时流句柄
#define HLIVE           HANDLE
// 历史文件句柄
#define HPLAYBACK       HANDLE
// 语音对讲句柄
#define HVOICE			HANDLE
// 设备发现句柄
#define HDISCOVERY		HANDLE


// 设备名称长度
#define MAX_DEVICE_NAME_LEN     (32)
// 设备地址最大长度
#define	MAX_DEV_ADDR_LEN		(256)
// 最大用户名长度
#define MAX_USERNAME_LEN		(32)
// 最大密码长度
#define MAX_PASSWORD_LEN		(32)
// ip地址长度
#define IP_ADDR_LEN             (16)
// mac地址长度
#define MAC_ADDR_LEN            (18)
// 最大配置信息长度
#define MAX_CFG_INFO_LEN        (20 * 1024)
// 最大文件名长度（含文件路径长度）
#define MAX_FILE_NAME_LEN       (256)	
// 版本信息长度
#define MAX_VERSION_INFO_LEN	(32)

// 每台设备的最大通道数
#define MAX_CHANNLE_PER_DEVICE	(32)  

////////////////////////////////////////////////////////////////////////////////
// 枚举定义
////////////////////////////////////////////////////////////////////////////////

// 接口返回码定义
typedef enum eNetClientRetCode
{
	eRetSuccess = 0,						// 成功
	eRetFailed,								// 失败
	eRetFailVersion,						// 版本不匹配
	eRetFailBoardType,						// 板型不匹配，无法升级

	eRetFailSdkNotInit,						// 客户端sdk未初始化
	eRetFailUnsupported,                    // 不支持的操作
	eRetFailHasStarted,						// 已经启动
	eRetFailNotStart,						// 未启动

	eRetFailInvalidParameter,				// 参数无效
	eRetFailInvalidHandle,					// 句柄值无效
	eRetFailInvalidFile,					// 文件无效
	eRetFailNoResource,						// 资源不足

	eRetFailUserName,						// 用户名错误
	eRetFailUserPwd,						// 用户密码错误
	eRetFailIpNotAllowed,					// 不允许的ip地址
	eRetFailTooManyLoginedUser,				// 登录用户过多

	eRetFailNetworkError,					// 网络错误
	eRetFailCmdTimeout,						// 命令超时
	eRetFailReplyError,						// 设备端回复错误
	eRetFailDisconnect,						// 连接断开
	
	eRetFailDecodeShow,						// 解码显示失败
	eRetFailAudioCapture,					// 音频捕获失败
	eRetFailVoicePlay,						// 语音播放失败
	eRetFailNotFind,						// 未找到

	eRetFailNoRight = 1000,					// 没有权限
	eRetFailChannelDisabled,				// 通道被禁用
	eRetFailSameIPLoginLimit,				// 同一ip地址登陆次数过多

}eNetClientRetCode;


// 设备日志查询方式 
typedef enum eLogQueryMode
{
	eLogQueryModeBegin,
	eLogQueryModeByTime			= 0x01,
	eLogQueryModeByType			= 0x02,
	eLogQueryModeByTimeAndType	= 0x04,
	eLogQueryModeAll			= 0xFFFFFFFF,
}eLogQueryMode;

// 日志查询主类型
typedef enum eLogQueryMainType
{
	eLogMainBegin, 
	eLogMainOperation	= 0x01,
	eLogMainException	= 0x02,
	eLogMainAlarm		= 0x04,
	eLogMainAll			= 0xFFFFFFFF
}eLogQueryMainType;

// 日志查询子类型
typedef enum eLogQuerySubType
{
	eLogOptBegin				= 100,
	eLogOptPowerOn,						// 开机
	eLogOptLogout,						// 注销
	eLogOptLogin,						// 登录
	eLogOptFormatDisk,					// 格式化硬盘
	eLogOptClearAlarm,					// 清除报警
	eLogOptBackup,						// 备份文件
	eLogOptUpdate,						// 升级
	eLogOptCommandConfig,				// 一般配置
	eLogOptResolutionConfig,			// 分辨率调节
	eLogOptStandardConfig,				// 视频制式调节
	eLogOptPollingConfig,				// 设置轮巡
	eLogOptScreenConfig,				// 屏幕调节
	eLogOptAudioMute,					// 设置静音
	eLogOptAudioVolumn,					// 音量调节
	eLogOptFactoryConfig,				// 恢复默认配置
	eLogOptUserInfoConfig,				// 用户信息配置
	eLogOptSystemTimeConfig,			// 系统时间设置
	eLogOptAudioOutConfig,				// 打开声音
	eLogOptStartRecord,					// 启动录像
	eLogOptStopRecord,					// 停止录像
	eLogOptCameraNameConfig,			// 修改摄像机名称
	eLogOptRecordConfig,				// 修改录像参数
	eLogOptColorConfig,					// 颜色设置
	eLogOptMotionConfig,				// 设置移动侦测
	eLogOptMosaicConfig,				// 设置马赛克
	eLogOptVideoLostConfig,				// 视频丢失配置
	eLogOptPTZConfig,					// 云台配置
	eLogOptAlarmConfig,					// 报警配置
	eLogOptNetworkConfig,				// 网络配置
	eLogOptDiskConfig,					// 硬盘配置
	eLogOptMacConfig,                   // 物理地址(MAC)设置
	eLogOptNtpConfig,					// NTP配置
	eLogOptPwdReset,					// 密码复位
	eLogOptCoverConfig,					// 遮挡检测配置
	eLogOptEnd,

	eLogAlarmBegin				= 200,
	eLogAlarmMotionStart,				// 移动侦测报警开始
	eLogAlarmMotionStop,				// 移动侦测报警结束
	eLogAlarmVideoLost,					// 视频丢失
	eLogAlarmVideoOk,					// 视频恢复	
	eLogAlarmAlarmInTriggered,			// 触发报警输入
	eLogAlarmAlarmOutTriggered,			// 触发报警输出
	eLogAlarmCoverStart,				// 遮挡事件开始
	eLogAlarmCoverStop,					// 遮挡事件结束
	eLogAlarmEnd,

	eLogExceptionBegin			= 300,
	eLogExceptionHDFull,				// 硬盘满
	eLogExceptionHDError,				// 硬盘错误
	eLogExceptionNetBroken,				// 网络异常
	eLogExceptionNoHDD,					// 无硬盘
	eLogExceptionHDFS,					// 硬盘的文件系统异常
	eLogExceptionHDWritting,			// 写硬盘异常
	eLogExceptionHDAllError,			// 所有硬盘都出错
	eLogExceptionHDFSOverflow,			// 硬盘资源泄漏
	eLogExceptionEnd,

	eLogSubAll					= 0xFFFFFFFF

}eLogQuerySubType;


// 回放控制码 
typedef enum ePlaybackCtrlCode
{
	ePlaybackPause		= 1,			// 暂停播放
	ePlaybackResume,					// 恢复播放 
	ePlaybackFast,						// 快放
	ePlaybackSlow,						// 慢放 
	ePlaybackNormalSpeed,				// 正常速度
	ePlaybackSingle,					// 单帧放
	ePlaybackOpenSound,					// 打开声音
	ePlaybackCloseSound,				// 关闭声音
	ePlaybackSetVolumn,					// 调节音量
	ePlaybackSeek,						// 回放跳转	
	ePlaybackGetCurPlayTime,			// 获取当前播放时间
	ePlaybackKeepImgAspectRatio,		// 设置是否按图像比例播放，而不随窗口进行拉伸
	ePlaybackCaptureBmp,				// 抓图
	ePlaybackSetVSync,					// 设置是否开启垂直同步
}ePlaybackCtrlCode;

// 实时流控制码
typedef enum eLiveStreamCtrlCode
{
	eLiveForceIFrame = 1,			// 强制I帧
	eLiveSetVolumn,					// 设置音量
	eLiveOpenSound,					// 打开声音，不影响回调数据
	eLiveCloseSound,				// 停止声音，不影响回调数据
	eLiveNotShowImage,				// 不解码显示图像
	eLiveResumeShowImage,			// 恢复解码显示，可通过参数指定显示窗口
	eLiveKeepImgAspectRatio,		// 设置是否按图像比例播放，而不随窗口进行拉伸
	eLiveCaptureBmp,				// 抓图
	eLiveSetVSync,					// 设置是否开启垂直同步
	eLiveSetConnectMode,			// 设置预览连接方式（主码流/子码流/自动选择）
}eLiveCtrlCode;

// 事件主类型
typedef enum eEventMainType
{
	eEventTypeAlarm			= 0x101,	// 报警事件
	eEventTypeVLost			= 0x201,	// 视频丢失事件
	eEventTypeMotion		= 0x301,	// 移动侦测事件
	eEventTypeHDD			= 0x701,	// 硬盘事件
	eEventTypeSystem		= 0x1001,	// 系统事件
	eEventNetDisconnect		= 0x10001,	// 连接断开
	eEventNetReconnect		= 0x11001,	// 重连成功
}eEventMainType;

// 报警事件子类型
typedef enum eEventSubTypeAlarm
{
	eEventSubAlarmInvalid = -1,
	eEventSubAlarmDisappear = 0,
	eEventSubAlarmArise,	
}eEventSubTypeAlarm;

// 移动侦测事件子类型
typedef enum eEventSubTypeMotion
{
	eEventSubMotionInvalid = -1,
	eEventSubMotionDisappear = 0,
	eEventSubMotionArise,
}eEventSubTypeMotion;

// 视频丢失事件子类型
typedef enum eEventSubTypeVLost
{
	eEventSubVLostInvalid = -1,
	eEventSubVLostDisappear = 0,
	eEventSubVLostArise,
}eEventSubTypeVLost;

// 硬盘事件子类型
typedef enum eEventSubTypeHDD
{
	eEventSubHDDInvalid = -1,
	eEventSubHDDNormal = 0,	
	eEventSubHDDFormatting,
	eEventSubHDDNeedFormat,
	eEventSubHDDFS_RO,
	eEventSubHDDEnd,
};

// 系统事件子类型
typedef enum eEventSubTypeSystem
{
	eEventSubSystemInvalid = -1,
	eEventSubSystemStandardChange = 0,		// 视频制式改变 （预留）
	eEventSubSystemChannelModeChange,		// 通道模式改变
};


// 设备控制码
typedef enum eDeviceCtrlCode
{
	eDevReboot = 1,           // 重启
	eDevResumeDefaultCfg,     // 恢复默认配置
	eDevDiskFormat,           // 硬盘格式化
	eDevReserved = 100,		  // 预留
	
}eDeviceCtrlCode;

// 录像类型
typedef enum
{
	RECORD_TYPE_NONE	 = 0,						// 非法录像类型,或无录像
	RECORD_TYPE_TIME	 = 0x01 << 0,				// 时间录像
	RECORD_TYPE_MOTION	 = 0x01 << 1,				// 移动监测录像
	RECORD_TYPE_ALARM	 = 0x01 << 2,				// 报警输入录像
	RECORD_TYPE_MANUAL	 = 0x01 << 3,				// 手动录像
	RECORD_TYPE_COVER	 = 0x01 << 4,				// 遮挡录像
	RECORD_TYPE_EVENT	 = 6,						// 事件录像（包括移动侦测录像、报警录像和遮挡录像）
	RECORD_TYPE_ALL		 = 0xFFFFFFFF,
}record_type_e;


// ptz控制码
typedef enum
{
	PTZ_ACTION_BEGIN,
	PTZ_DIRECTION,				// 方向控制
	PTZ_ZOOM,					// 缩放
	PTZ_FOCUS,					// 焦点
	PTZ_IRIS,					// 焦距
	PTZ_PRESET,					// 预置点
	PTZ_TRACK,					// 轨迹
	PTZ_CRUISE,					// 巡航
	PTZ_ACTION_END,
}ptz_action_e;

// 方向控制
typedef enum
{
	PTZ_DIRCTION_UP,
	PTZ_DIRCTION_DOWN,
	PTZ_DIRCTION_LEFT,
	PTZ_DIRCTION_RIGHT,
	PTZ_DIRCTION_LEFT_UP,
	PTZ_DIRCTION_LEFT_DOWN,
	PTZ_DIRCTION_RIGHT_UP,
	PTZ_DIRCTION_RIGHT_DOWN,
	PTZ_DIRCTION_STOP,
}ptz_dirction_ctl_e;

// zoom
typedef enum
{
	PTZ_ZOOM_WIDE,
	PTZ_ZOOM_TELE,
	PTZ_ZOOM_STOP,
}ptz_zoom_ctl_e;

// focus
typedef enum
{
	PTZ_FOCUS_NEAR,
	PTZ_FOCUS_FAR,
	PTZ_FOCUS_STOP,
}ptz_focus_ctl_e;

// iris
typedef enum
{
	PTZ_IRIS_OPEN,
	PTZ_IRIS_CLOSE,
	PTZ_IRIS_STOP,
}ptz_iris_ctl_e;

// preset
typedef enum
{
	PTZ_PRESET_SET,
	PTZ_PRESET_CLR,
	PTZ_PRESET_GOTO,
}ptz_preset_ctl_e;

// track
typedef enum
{
	PTZ_TRACK_START_SET,
	PTZ_TRACK_STOP_SET,
	PTZ_TRACK_RUN,
}ptz_track_ctl_e;

// cruise
typedef enum
{
	PTZ_CRUISE_STOP,			// 停止巡航
	PTZ_CRUISE_START,			// 开始巡航
}ptz_cruise_ctl_e;

// 设备发现协议类型
typedef enum eDiscoveryType
{
	eDiscoveryProtoPrivate	= 0x01,		// 私有协议设备发现
	eDiscoveryProtoOnivf	= 0x02,		// onvif设备发现
	eDiscoveryProtoAll		= eDiscoveryProtoPrivate | eDiscoveryProtoOnivf,
}eDiscoveryType;

// 发现到的设备类型
typedef enum egk_device_type
{
	eDevTypeUnknown,			// 未知的设备类型
	eDevTypeDVR,				// DVR设备
	eDevTypeIPC,				// IPC设备
	eDevTypeHVR,				// HVR设备
	eDevTypeNVR,				// NVR设备
}gk_device_type;

////////////////////////////////////////////////////////////////////////////////
// 结构体定义
////////////////////////////////////////////////////////////////////////////////

// 时间结构
typedef struct tagTimeInfo
{
	WORD wYear;									// 年
	WORD wMonth;								// 月
	WORD wDay;									// 日
	WORD wHour;									// 时
	WORD wMinute;								// 分 
	WORD wSecond;								// 秒
}TimeInfo, *LPTimeInfo;

// 实时流连接信息
typedef struct tagLiveConnect
{
	DWORD dwChannel;							// 对应设备通道
	HWND hPlayWnd;								// 视频显示窗口, NULL表示仅接收并回调预览数据，不需要解码显示图像
	DWORD dwConnectMode;						// 连接方式， 0--主码流 1--子码流 2-自动选择
}LiveConnect, *LPLiveConnect;

// 日志的返回结果 
typedef struct tagLogQueryResult
{
    TimeInfo cLogTime;							// 时间
    eLogQueryMainType eMainType;				// 主类型
    eLogQuerySubType eSubType;					// 次类型
    char acUser[MAX_USERNAME_LEN];				// 操作员
    DWORD dwRemoteHostAddr;						// 远程主机地址，为0时表示本地操作的日志，否则表示远程操作的日志
    int nChannel;								// 通道号
}LogQueryResult, *LPLogQueryResult;

// 录像文件查找 
typedef struct tagRecFileQueryResult
{
	char acFileName[MAX_FILE_NAME_LEN];			// 录像文件名
    record_type_e dwFileType;					// 录像文件的类型，和查找时保持一致 
	DWORD dwFileSize;							// 录像文件的大小
	TimeInfo cBeginTime;						// 文件的开始时间
	TimeInfo cEndTime;							// 文件的结束时间
}RecFileQueryResult, *LPRecFileQueryResult;

// ptz控制信息
typedef struct tagPtzControlInfo
{
	ptz_action_e action;
	long 	control_data1;
	long 	control_data2;
}PtzControlInfo;

// 设备事件
typedef struct server_event_s
{
	int channel;								// 产生事件的通道号
	int event_main;								// 事件主类型，参见eEventMainType的定义
	int event_sub;								// 事件子类型，参见各子类型的定义，如eEventSubTypeAlarm
	int data1;					
	int data2;
}server_event_t;


// 设备发现信息
typedef struct tagDiscoveryInfo
{
	char uuid[128];
	char ip_address[128];
	int port;
	char device_type;				// 设备类型(参考定义gk_device_type)
	char ipc_type;					// IPC类型(参考hsx_cfgdefine.h中的定义eIPCType)
	char wifi_ipaddr[32];			// wifi无线ip地址
}DiscoveryInfo;


// 通道属性资源信息
typedef struct tagChannelAttrResInfo
{
	int video_standard;				// 视频制式（参考hsx_cfgdefine.h中关于video_stand_e枚举类型的定义）
	DWORD ch_enable_mask;			// 通道启用掩码
	int resolution[32];				// 各通道的分辨率（参考hsx_cfgdefine.h中关于enc_size_e枚举类型的定义）
}ChannelAttrResInfo;

// 录像画质资源信息
typedef struct tagRecQualityResInfo
{
	int video_standard;				// 视频制式（参考hsx_cfgdefine.h中关于video_stand_e枚举类型的定义）
	DWORD ch_enable_mask;			// 通道启用掩码
	int resolution[32];				// 各通道的分辨率（参考hsx_cfgdefine.h中关于enc_size_e枚举类型的定义）
	int framerate[32];				// 各通道的帧率（1-30）
	int event_resolution[32];		// 各通道事件录像的分辨率
	int event_framerate[32];		// 各通道事件录像的帧率
}RecQualityResInfo;

// 位置比例信息
typedef struct tagPosRatioInfo
{
	DWORD numerator;				// 分子
	DWORD denominator;				// 分母
}PosRatioInfo;

// 通道位置信息
typedef struct tagChPosInfo
{
	int ch;							// 通道号, 从0开始
	PosRatioInfo x;					
	PosRatioInfo y;
	PosRatioInfo w;
	PosRatioInfo h;
}ChPosInfo;

// 设备分屏配置
typedef struct tagDeviceScreenDisplay
{
	int nScreenChCnt;							
	ChPosInfo ChPos[MAX_CHANNLE_PER_DEVICE];
}DeviceScreenDisplay;

////////////////////////////////////////////////////////////////////////////////
// 回调函数定义
////////////////////////////////////////////////////////////////////////////////


// 设备事件回调
typedef int (CALLBACK *CB_DeviceEvent)(IN HDEVICE hDev, server_event_t *pEvent, DWORD dwUserData);

// 实时流数据回调
typedef int (CALLBACK *CB_StreamData)(HLIVE hStream, BYTE *pDataBuf, DWORD dwDataLen, DWORD dwUserData);

// 实时图像绘制回调
typedef void (CALLBACK* CB_DrawFun)(HLIVE hStream, HDC hDC, DWORD dwUserData);

// 设备发现回调
typedef int(CALLBACK* CB_Discovery)(HDISCOVERY hDiscovery, DiscoveryInfo *pDiscoveryInfo, int nIsNewDevice, DWORD dwUserData);

#ifndef WIN32
// rgb帧数据回调
typedef void (CALLBACK *CB_RGBVideoFrame)(BYTE *pFrame, int nWidth, int nHeight, int nLineBytes, DWORD dwUserData);
#endif

////////////////////////////////////////////////////////////////////////////////
// 接口定义
////////////////////////////////////////////////////////////////////////////////

#ifndef WIN32
#pragma GCC visibility push(default)
#endif

// 初始化
DVR_NET_API int __stdcall Network_ClientInit();

// 反初始化
DVR_NET_API int __stdcall Network_ClientUnInit();

// 获取当前SDK的版本信息
DVR_NET_API int __stdcall Network_ClientGetVersion(BYTE *pVersionInfo, int nInfoLen);



// 登录设备
DVR_NET_API int __stdcall Network_ClientLogin(OUT HDEVICE *pDev, char *pSeverAddr, DWORD dwCmdPort, char *pUserName, char *pPassword);

// 登出设备
DVR_NET_API int __stdcall Network_ClientLogout(HDEVICE hDev);

// 设备控制
DVR_NET_API int __stdcall Network_ClientDeviceControl(IN HDEVICE hDev, eDeviceCtrlCode eCtrlCode, DWORD dwParam);

// 设置事件回调
DVR_NET_API int __stdcall Network_ClientSetEventCB(HDEVICE hDev, CB_DeviceEvent cbfEvent, DWORD dwUserData);

// 分辨率改变时，需要更新视频，否则图像无法显示
DVR_NET_API int __stdcall Network_ClientRefreshVideo(IN HDEVICE hDev);


// 启动实时流
DVR_NET_API int __stdcall Network_ClientStartLive(HLIVE *pStream, IN HDEVICE hDev, LiveConnect *pClientInfo, CB_StreamData cDatacbf = NULL, DWORD dwUserData = 0);

// 停止实时流
DVR_NET_API int __stdcall Network_ClientStopLive(HLIVE hStream);

// 实时流控制
DVR_NET_API int __stdcall Network_ClientLiveControl(HLIVE hStream, eLiveCtrlCode eCode, void *pParam);

// 设置实时流图像叠加绘制回调
DVR_NET_API int __stdcall Network_ClientSetLiveDrawCB(HLIVE hStream, IN HWND hWnd, IN CB_DrawFun cbfDraw, DWORD dwUserData);

// 设置实时流数据回调, bMustCBMainStream，该参数只在设备支持多码流的情况下有效: true--必须回调主码流；false--直接回调预览数据
// bNeedSound, 回调是否需要声音
DVR_NET_API int __stdcall Network_ClientSetLiveDataCB(HLIVE hStream, CB_StreamData cDatacbf, DWORD dwUserData, bool bMustCBMainStream = false, bool bNeedSound = true);

// 预览连接方式为子码流/自动选择时，设置随显示窗口的大小自适应选择码流；预览连接方式为主码流时，调用该接口无效
DVR_NET_API int __stdcall Network_ClientSubcodeAdapt(HLIVE hStream, int nWndWidth, int nWndHeight);



// 获取一个月中有录像的有哪些天
DVR_NET_API int __stdcall Network_ClientGetMonthRecDate(HDEVICE hDev, DWORD dwYear, DWORD dwMonth, DWORD &dwRecDateMask);

// 获取某一天有录像的时间
// 以分钟为单位返回录像时间，所以dwBufLen必须>=(24 * 60)
DVR_NET_API int __stdcall Network_ClientGetDayRecTime(HDEVICE hDev, TimeInfo *pRecDate, BYTE *pRecTimeBuf, DWORD dwBufLen, DWORD dwChannel);

// 启动回放
DVR_NET_API int __stdcall Network_ClientStartPlayback(OUT HPLAYBACK *pPlayback, HANDLE hDev, DWORD dwChannel, DWORD dwFileType, TimeInfo *pBeginTime, TimeInfo *pEndTime, HWND hWnd);

//  停止回放
DVR_NET_API int __stdcall Network_ClientStopPlayback(IN HPLAYBACK hPlayback);

// 回放控制
DVR_NET_API int __stdcall Network_ClientPlaybackControl(IN HPLAYBACK hPlayback, ePlaybackCtrlCode dwControlCode, void *pParam);



// 启动下载
DVR_NET_API int __stdcall Network_ClientStartDownload(OUT HDOWNLOAD *pDownload, HANDLE hDev, char *pDevFileName, char *pSavedFileName, TimeInfo *pBeginTime = NULL, TimeInfo *pEndTime = NULL);

// 停止下载
DVR_NET_API int __stdcall Network_ClientStopDownload(HDOWNLOAD hDownload);

// 获取下载状态
DVR_NET_API int __stdcall Network_ClientGetDownloadStatus(IN HDOWNLOAD hDownload, DWORD &dwProgress);


// PTZ控制
DVR_NET_API int __stdcall Network_ClientPTZControl(HDEVICE hDev, DWORD dwChannle, PtzControlInfo *pControlInfo);

// 透明通道传输数据, nDataLen <= 2048(字节)
DVR_NET_API int __stdcall Network_ClientTransparentSend(HDEVICE hDev, DWORD dwBuadRate, BYTE *pDataBuf, int nDataLen);

// 获取设备配置
// 注意：在缓冲区长度允许的范围内(参见MAX_CFG_INFO_LEN)，可同时设置或获取多个相同的配置
// 比如要获取dvr_channel_cfg，如果通道掩码为二进制的0101,则m_acCfg中得数据为dvr_channel_cfg1, dvr_channel_cfg3
DVR_NET_API int __stdcall Network_ClientGetDeviceConfig(HDEVICE hDev, DWORD dwCommand, DWORD dwChannelMask, BYTE *pCfgBuf, DWORD dwBufLen);

// 设置设备配置
DVR_NET_API int __stdcall Network_ClientSetDeviceConfig(HDEVICE hDev, DWORD dwCommand, DWORD dwChannelMask, BYTE *pCfgBuf, DWORD dwCfgLen);



// 启动升级
DVR_NET_API int __stdcall Network_ClientStartUpgrade(OUT HUPGRADE *pUpgrade, IN HANDLE hDev, const char *pFileName);

// 停止升级
DVR_NET_API int __stdcall Network_ClientStopUpgrade(HUPGRADE hUpgrade);

// 获取升级状态
DVR_NET_API int __stdcall Network_ClientGetUpgradeStatus(IN HUPGRADE hUpgrade, OUT DWORD &dwProgress);



// 启动日志查询
DVR_NET_API int __stdcall Network_ClientStartLogQuery(OUT HQUERY *pLog, HANDLE hDev, eLogQueryMode eQueryMode, DWORD dwChannel, eLogQueryMainType eMainType, eLogQuerySubType eSubType, TimeInfo *pQueryTime);

// 获取日志查询结果 dwLogCnt >= 0 && dwLogCnt <= 100
DVR_NET_API int __stdcall Network_ClientGetLogQueryResult(IN HQUERY hLog, INOUT DWORD &dwLogCnt, OUT BYTE *pLogBuf, IN DWORD dwBufLen);

// 停止日志查询
DVR_NET_API int __stdcall Network_ClientStopLogQuery(HQUERY hLog);



// 启动文件查询
DVR_NET_API int __stdcall Network_ClientStartFileQuery(OUT HQUERY *pFileQuery, HANDLE hDev, DWORD dwChannel, DWORD dwFileType, TimeInfo *pBeginTime, TimeInfo *pEndTime);

// 获取文件查询结果 dwFileCnt >= 0 && dwFileCnt <= 50
DVR_NET_API int __stdcall Network_ClientGetFileQueryResult(IN HQUERY hFileQuery, INOUT DWORD &dwFileCnt, OUT BYTE *pFileBuf, IN DWORD dwBufLen);

// 停止文件查询
DVR_NET_API int __stdcall Network_ClientStopFileQuery(HQUERY hFileQuery);



// 启动语音对讲
DVR_NET_API int __stdcall Network_ClientStartVoice(OUT HVOICE *pVoice, IN HANDLE hDev, IN HWND hWnd = NULL);

// 停止语音对讲
DVR_NET_API int __stdcall Network_ClientStopVoice(IN HVOICE hVoice);

// 设置语音对讲音量 bHighOrLow: true--提高音量 false--降低音量
DVR_NET_API int __stdcall Network_ClientSetVoiceVolumn(IN HVOICE hVoice, bool bHighOrLow);



// 启动设备发现, nInterval--发送探测包的周期，单位：ms (nInterval >= 1000)
DVR_NET_API int __stdcall Network_ClientStartDiscovery(OUT HDISCOVERY *pDiscovery, int nInterval, CB_Discovery cbfDiscovery, DWORD dwUserData, eDiscoveryType eType = eDiscoveryProtoAll);

// 停止设备发现
DVR_NET_API int __stdcall Network_ClientStopDiscovery(IN HDISCOVERY hDiscovery);

// 刷新设备发现
DVR_NET_API int __stdcall Network_ClientRefreshDiscovery(IN HDISCOVERY hDiscovery);



// 检查总体通道属性配置所需性能是否超过系统的最大性能
// *pExceedCIFCnt为0表示当前配置可以满足，否则大于0表示当前配置所需性能无法满足，超出部分为*pExceedCIFCnt（单位：CIF, 帧每秒）
DVR_NET_API int __stdcall Network_ClientCheckChAttrResLimit(OUT int *pExceedCIFCnt, HANDLE hDev, IN ChannelAttrResInfo *pResInfo);

// 检查总体录像画质配置所需性能是否超过系统的最大性能
// *pExceedCIFCnt为0表示当前配置可以满足，否则大于0表示当前配置所需性能无法满足，超出部分为*pExceedCIFCnt（单位：CIF, 帧每秒）
DVR_NET_API int __stdcall Network_ClientCheckRecQualityResLimit(OUT int *pExceedCIFCnt, HANDLE hDev, IN RecQualityResInfo *pResInfo);



#ifndef WIN32
// set live rgb callback
DVR_NET_API int __stdcall Network_ClientSetLiveRgbCB(HLIVE hStream, CB_RGBVideoFrame cbf, DWORD dwUserData);

// set playback rgb callback
DVR_NET_API int __stdcall Network_ClientSetPlaybackRgbCB(HPLAYBACK hPlayback, CB_RGBVideoFrame cbf, DWORD dwUserData);
#endif


// 设置设备端分屏模式
DVR_NET_API int __stdcall Network_ClientSetDeviceScreenDisplay(IN HDEVICE hDevice, DeviceScreenDisplay *pScreenDisplay);


#ifndef WIN32
#pragma GCC visibility pop
#endif

#endif // end of HSX_NETWORK_CLIENT_H

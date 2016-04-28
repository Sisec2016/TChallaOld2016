#ifndef _HISI_SDK_H_
#define _HISI_SDK_H_

#define SERIALNO_LEN  32                   //serial number length
#define HISI_DVR_NOERROR  0                //没有错误
#define HISI_DVR_NETWORK_FAIL_CONNECT  1   //连接服务器失败
#define HISI_DVR_PASSWORD_ERROR  2         //用户名或者密码错误,登录失败

#define  HISI_COMM_EXCEPTION 0x11         //通用异常消息
#define  HISI_COMM_ALARM 0x12             //通用报警消息
#define  HISI_ALARM_WIRELESS 0x13         //无线模块报警消息
#define  HISI_ALARM_UPS 0x14              //UPS报警消息
#define  HISI_ALARM_RECONNECT 0x15
#define  HISI_ALARM_RECONNECTED 0x16

#define  HISI_EXCEPTION_EXCHANGE   0x8000           //用户交互时异常
#define  HISI_EXCEPTION_AUDIOEXCHANGE   0x8001      //语音对讲异常
#define  HISI_EXCEPTION_ALARM   0x8002              //报警异常
#define  HISI_EXCEPTION_PREVIEW   0x8003            //网络预览异常
#define  HISI_EXCEPTION_ORDERCALL  0x8004           //调用顺序错误
#define  HISI_EXCEPTION_RECONNECT   0x8005          //预览时重连
#define  HISI_EXCEPTION_ALARMRECONNECT   0x8006     //报警时重连
#define  HISI_EXCEPTION_NOTINIT  0x8007             //未调用初始化
#define  HISI_EXCEPTION_GETVIDEOPORT  0x8008        //获取视频端口失败
#define  HISI_EXCEPTION_GETHTTPPORT  0x8009         //获取HTTP服务器端口失败
#define  HISI_EXCEPTION_PLAYBACK   0x8010           //回放异常
#define  HISI_EXCEPTION_NOPLAYHANDLE  0x8011        //无播放器句柄
#define  HISI_EXCEPTION_EXMAXCHANNEL  0x8012        //超过最大通道号
#define  HISI_EXCEPTION_NETERROR  0x8013            //网络异常
#define  HISI_EXCEPTION_ORDER  0x8014               //函数调用顺序错误
#define  HISI_EXCEPTION_MAXPLAY  0x8015             //达到最大播放数
#define  HISI_EXCEPTION_EXMAXVALUE  0x8016          //超出最大值
#define  HISI_EXCEPTION_INVALIDHANDLE  0x8017       //无效的句柄

#define  HISI_DVR_GET_DEVICECFG	  1	   //获取设备参数
#define  HISI_DVR_GET_ENCODECFG   2    //获取编码参数
#define  HISI_DVR_GET_MISCCFG     3    //获取通用参数
#define  HISI_DVR_GET_NETCFG	  4	   //获取网络参数
#define  HISI_DVR_GET_SCREENCFG   5    //获取屏幕参数
#define  HISI_DVR_GET_PTZCFG      6    //获取云台参数
#define  HISI_DVR_GET_SENSORCFG   7    //获取报警参数
#define  HISI_DVR_GET_DETECTIONCFG  8  //获取侦测参数
#define  HISI_DVR_GET_SCHEDULECFG   9  //获取录像时间参数

#define  HISI_DVR_SET_ENCODECFG   20     //设置编码参数
#define  HISI_DVR_SET_MISCCFG     21     //设置通用参数
#define  HISI_DVR_SET_NETCFG	  22	 //设置网络参数
#define  HISI_DVR_SET_SCREENCFG   23     //设置屏幕参数
#define  HISI_DVR_SET_PTZCFG      24     //设置云台参数
#define  HISI_DVR_SET_SENSORCFG   25     //设置报警参数
#define  HISI_DVR_SET_DETECTIONCFG  26   //设置侦测参数
#define  HISI_DVR_SET_SCHEDULECFG   27   //设置录像时间参数

#define  HISI_DVR_PLAYSTART     1    //开始播放
#define  HISI_DVR_PLAYPAUSE     2    //暂停播放
#define  HISI_DVR_PLAYRESTART   3    //恢复播放
#define  HISI_DVR_PLAYSTOP      4    //停止播放
#define  HISI_DVR_PLAYFAST      5    //快放
#define  HISI_DVR_PLAYSLOW      6    //慢放
#define  HISI_DVR_PLAYNORMAL    7    //正常速度
#define  HISI_DVR_PLAYSTARTAUDIO  9  //打开声音
#define  HISI_DVR_PLAYSTOPAUDIO  10  //关闭声音
#define  HISI_DVR_PLAYGETPOS     11  //获取文件下载进度

#define  HISI_PTZ_UP            0    //上
#define  HISI_PTZ_DOWN          1    //下
#define  HISI_PTZ_LEFT          2    //左
#define  HISI_PTZ_RIGHT         3    //右
#define  HISI_PTZ_AUTO          4    //自动
#define  HISI_PTZ_FOCUSFAR      5    //聚焦-
#define  HISI_PTZ_FOCUSNEAR     6    //聚焦+
#define  HISI_PTZ_ZOOMIN        7    //缩小
#define  HISI_PTZ_ZOOMOUT       8    //放大
#define  HISI_PTZ_IRISOPEN      9    //光圈开
#define  HISI_PTZ_IRISCLOSE    10    //光圈关
#define  HISI_PTZ_AUX1         11    //辅助开关1
#define  HISI_PTZ_AUX2         12    //辅助开关2
#define  HISI_PTZ_CNT          13

#define  HISI_DVR_FILE_SUCCESS  1000    //获取文件信息成功
#define  HISI_DVR_FILE_NOFIND  1001     //未查找到文件
#define  HISI_DVR_ISFINDING  1002       //正在查找请等待
#define  HISI_DVR_NOMOREFILE  1003      //没有更多的文件，查找结束
#define  HISI_DVR_FILE_EXCEPTION  1004 //查找文件时异常

typedef struct
{
	char sIP[15];           //DVR IP地址
    int nVideoPort;         //DVR视频端口
    int nHttpPort;          //DVR,http服务器端口
}HISI_DEVCONNECTINFO, *PHISI_DEVCONNECTINFO;

typedef struct
{
    BYTE sSerialNumber[SERIALNO_LEN];     //88888167,ID号
    BYTE AlarmInPortNum;                  //报警输入数
    BYTE AlarmOutPortNum;                 //报警输出数
    BYTE DiskNum;                         //硬盘个数
    BYTE DVRType;                         //DVR设备类型
    BYTE ChanNum;                         //视频数 
    BYTE AudioChanNum;                    //音频数
    BYTE Res[24];                         //保留字节
}HISI_DEVCEINFO, *PHISI_DEVCEINFO;

typedef struct
{
    LONG Channel;                    //通道号,从1开始
    LONG LinkMode;                   //连接方式
    HWND PlayWnd;                    //视频播放窗口
}HISI_DEV_CLIENTINFO, *PHISI_DEV_CLIENTINFO;

typedef struct
{
    LONG Channel;                    //通道号,从1开始
    LONG Stream;
    LONG LinkMode;                   //连接方式
    HWND PlayWnd;                    //视频播放窗口
}HISI_DEV_CLIENTINFOEX, *PHISI_DEV_CLIENTINFOEX;


typedef struct
{
    char name[20];         //设备名称
    char model[20];            //设备型号
    char hwver[15];        //硬件版本
    char swver[15];        //软件版本
    char reldatetime[20];  //构建时间
    int camcnt;          //通道数
    int audcnt;          //音频数
    int sensorcnt;       //报警输入数
    int alarmcnt;        //报警输出数
}PHISI_DEVINFO, *HISI_DEVINFO;

typedef struct
{
    int mode;            //编码模式
    int fmt;             //编码格式
    int piclv;           //图像质量
    int bitmode;         //码流控制
    int bitvalue;        //码流码率
    int framerate;       //视频帧率
}HISI_ENCODEINFO, *PHISI_ENCODEINFO;

typedef struct
{
    int datefmt;          //日期格式
    int keylock;          //键盘锁定
    int keybuzzer;        //按键声音
    int lang;             //语言
    int standard;         //视频制式
    int dvrid;            //遥控器编号
    int hddoverwrite;     //自动覆盖
    int alpha;            //osd透明
    int autoswi;          //自动轮训
    int autoswiinterval;  //轮训间隔
    int autoswimode;      //轮训方式
}HISI_MISCINFO, *PHISI_MISCINFO;

typedef struct
{
    int dhcp;                 //启用DHCP
    char mac[20];             //MAC地址
    char ip[20];              //IP地址
    char submask[20];         //子网掩码
    char gateway[20];         //网关地址
    char dns[20];             //DNS地址
    int httpport;             //WEB端口
    int clientport;           //客户端端口
    int mobileport;           //手机端口
    DWORD enetid;             //易视网ID
    int ddns;                 //启用DDNS
    int ddnsprovider[20];     //提供商
    int ddnsurl[20];          //域名
    char ddnsusr[20];         //用户名
    char ddnspwd[20];         //密码
    int pppoe;                //启用PPPoE
    char pppoeusr[20];        //用户名
    char pppoepwd[20];        //密码
}HISI_NETWORKINFO, *PHISI_NETWORKINFO;

typedef struct
{
    char title[40];   //名称
}HISI_SCREENINFO, *PHISI_SCREENINFO;

typedef struct
{
    int id;               //设备地址
    int protocal;         //协议
    int baudrate;         //波特率
    int databit;          //数据位
    int stopbit;          //停止位
    int parity;           //奇偶校验
}HISI_PTZINFO, *PHISI_PTZINFO;

typedef struct
{
    int mode;               //类型
    int alarmduration;      //报警延时
    int alarm;              //报警
    int buzzer;             //蜂鸣器
}HISI_SENSORINFO, *PHISI_SENSORINFO;

typedef struct
{
    int sens;               //灵敏度
    int mdalarmduration;    //移动侦测持续时间
    int mdalarm;            //移动报警
    int mdbuzzer;           //移动蜂鸣
    int vlalarmduration;    //视频丢失持续时间
    int vlalarm;            //丢失报警
    int vlbuzzer;           //丢失蜂鸣
}HISI_DETECTIONINFO, *PHISI_DETECTIONINFO;

typedef struct
{
}HISI_SCHEDULEINFO, *PHISI_SCHEDULEINFO;

typedef struct
{
    DWORD dwYear;          //年
    DWORD dwMonth;         //月
    DWORD dwDay;           //日
    DWORD dwHour;          //小时
    DWORD dwMinute;        //分
    DWORD dwSecond;        //秒
}HISI_DVR_TIME, *PHISI_DVR_TIME;

typedef enum _RecotdType_t
{
	rt_timing=0,
	rt_motion=1,
	rt_alarm=2,
	rt_manual=3,
	rt_all=4,
}HISI_DVR_RECORDTYPE;

typedef struct
{
	char sFileName[100];
	int nChannel;
    HISI_DVR_TIME struStartTime;
	HISI_DVR_TIME struStopTime;
    DWORD dwFileSize;  
}HISI_DVR_FIND_DATA, *PHISI_DVR_FIND_DATA;

//录像回放时的帧头结构
typedef	enum
{
	AVENC_AUDIO = 0,
	AVENC_IDR,
	AVENC_PSLICE,
	AVENC_FRAME_TYPE_CNT,
}AVENC_FRAME_TYPE;

typedef enum
{
	REC_TYPE_NONE = 0,
	REC_TYPE_TIMER = 1,
	REC_TYPE_MOTION = 2,
	REC_TYPE_SENSOR = 4,
	REC_TYPE_MANUAL = 8,
}REC_TYPE;

#pragma pack(4)
typedef struct
{
	union
	{
		struct
		{
			unsigned int magic; //头标记
			int session_rnd;    //段随机数
			int frame_width; //分辨率 宽
			int frame_height; //分辨率 高
			int frame_rate; //帧率 如25fps
			int audio_sample_rate; //音频采样率
			char audio_format[8]; //音频格式
			int audio_data_width; //音频数据宽度 8bit/16bit
			AVENC_FRAME_TYPE frame_type; //帧类型，I/P/音频等
			int session_id; //段ID
			int channel; //通道号
			REC_TYPE rec_type; //录像类型，如手动，定时等
			LARGE_INTEGER frame_index; //帧在段中的索引
			unsigned int nSize; //帧大小，不包括帧头
			LARGE_INTEGER u64TSP;
			unsigned long nGenTime;
		};
		struct
		{
			unsigned int reserved[32-1];
			unsigned int magic2; //尾标记
		};
	};
}Frame_Head_t;
#pragma pack()

typedef struct
 {
    byte Channel[4];
 }HISI_WIRELESSMODULE;

typedef struct
{
    HISI_WIRELESSMODULE  Module[4];
}HISI_WIRELESSINFO, *PHISI_WIRELESSINFO;
  
//初始化
BOOL __stdcall HISI_DVR_Init();
BOOL __stdcall HISI_DVR_Cleanup();
//取版本信息
DWORD __stdcall HISI_DVR_GetSDKVersion();
//取错误码
DWORD __stdcall HISI_DVR_GetLastError();
//注册异常消息回调
BOOL __stdcall HISI_DVR_SetDVRMessage(void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser),void *pUser);
//通过ESeeID获取DVR的IP和端口
BOOL __stdcall HISI_DVR_GetConnectInfoByID(char *eSeeID, PHISI_DEVCONNECTINFO connectInfo);
//用户注册
LONG __stdcall HISI_DVR_Login(char *sDVRIP,WORD wDVRPort,WORD wHttpPort, char *sUserName,char *sPassword,PHISI_DEVCEINFO lpDeviceInfo);
BOOL __stdcall HISI_DVR_Logout(LONG lUserID);
//实时预览
LONG __stdcall HISI_DVR_RealPlay(LONG lUserID,PHISI_DEV_CLIENTINFO lpClientInfo);
LONG __stdcall HISI_DVR_RealPlayEx(LONG lUserID,PHISI_DEV_CLIENTINFOEX lpClientInfo);
BOOL __stdcall HISI_DVR_StopRealPlay(LONG lRealHandle);
//开启声音
BOOL __stdcall HISI_DVR_OpenSound(LONG lRealHandle);
BOOL __stdcall HISI_DVR_CloseSound();
//抓图
BOOL __stdcall HISI_DVR_CapturePicture(LONG lRealHandle,char *sPicFileName);//bmp
BOOL __stdcall HISI_DVR_SetRealDataCallBack(LONG lRealHandle,void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
//实时预览捕获数据
BOOL __stdcall HISI_DVR_SaveRealData(LONG lRealHandle,char *sFileName);
BOOL __stdcall HISI_DVR_StopSaveRealData(LONG lRealHandle);
//报警
LONG __stdcall HISI_DVR_SetupAlarmChan(char *pServerIP,WORD wServerPort,char *pUserName,char *pUserPassword);
BOOL __stdcall HISI_DVR_CloseAlarmChan(LONG lAlarmHandle);
BOOL __stdcall HISI_DVR_SetDVRMessageCallBack(BOOL (CALLBACK *fMessageCallBack)(LONG lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen, DWORD dwUser), DWORD dwUser);
//云台控制相关接口
BOOL __stdcall HISI_DVR_PTZControl(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
//参数配置 
BOOL __stdcall HISI_DVR_GetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
BOOL __stdcall HISI_DVR_SetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize);
//录像文件查找
LONG HISI_DVR_FindFile(LONG lUserID,LONG lChannel,HISI_DVR_RECORDTYPE dwFileType,PHISI_DVR_TIME lpStartTime,PHISI_DVR_TIME lpStopTime);
LONG HISI_DVR_FindNextFile(LONG lFindHandle,PHISI_DVR_FIND_DATA lpFindData);
BOOL HISI_DVR_FindClose(LONG lFindHandle);
//录像回放
LONG __stdcall HISI_DVR_PlayBackByTime(LONG lUserID,LONG lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, HWND hWnd);
BOOL __stdcall HISI_DVR_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *LPOutValue);
BOOL __stdcall HISI_DVR_StopPlayBack(LONG lPlayHandle);
LONG HISI_DVR_PlayBackByName(LONG lUserID,char *sPlayBackFileName,HWND hWnd);
//录像数据捕获
BOOL __stdcall HISI_DVR_SetPlayDataCallBack(LONG lPlayHandle,void(CALLBACK *fPlayDataCallBack) (LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
int __stdcall HISI_DVR_GetFileByTime(int lUserID, int lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, char *sSavedFileName);
LONG __stdcall HISI_DVR_GetFileByName(LONG lUserID,char *sDVRFileName,char *sSavedFileName);
BOOL __stdcall HISI_DVR_StopGetFile(int lFileHandle);
//录像下载
BOOL __stdcall HISI_DVR_PlayBackSaveData(LONG lPlayHandle,char *sFileName);
BOOL __stdcall HISI_DVR_StopPlayBackSave(LONG lPlayHandle);
//录像回放抓图
BOOL __stdcall HISI_DVR_PlayBackCaptureFile(LONG lPlayHandle,char *sFileName);
//语音广播
BOOL __stdcall HISI_DVR_ClientAudioStart();
BOOL __stdcall HISI_DVR_ClientAudioStop();
BOOL __stdcall HISI_DVR_AddDVR(LONG lUserID);
BOOL __stdcall HISI_DVR_DelDVR(LONG lUserID);
int __stdcall HISI_BroadcastStart();
int __stdcall HISI_BroadcastAddClient(
	char *pServerIP,
	WORD wServerPort,
	char *pDeviceName,
	char *pUserName,
	char *pUserPassword,
          HANDLE	&hBrdClient);
int __stdcall HISI_BroadcastDelClient(HANDLE hBrdClient);
int __stdcall HISI_BroadcastStop();
//文件播放
//初始化
BOOL __stdcall HISI_Play_Init();
BOOL __stdcall HISI_Play_Realese();
//辅助函数
BOOL  __stdcall HISI_Play_GetPort(LONG* nPort);
BOOL  __stdcall HISI_Play_FreePort(LONG nPort);
//文件操作
BOOL  __stdcall HISI_Play_OpenFile(LONG nPort,LPSTR sFileName);
BOOL  __stdcall HISI_Play_CloseFile(LONG nPort);
//播放控制
BOOL  __stdcall HISI_Play_Play(LONG nPort, HWND hWnd);
BOOL  __stdcall HISI_Play_Stop(LONG nPort);
BOOL  __stdcall HISI_Play_Pause(LONG nPort,DWORD nPause);
BOOL  __stdcall HISI_Play_Fast(LONG nPort);
BOOL  __stdcall HISI_Play_Slow(LONG nPort);
BOOL  __stdcall HISI_Play_OneByOne(LONG nPort);
BOOL  __stdcall HISI_Play_SetPlayPos(LONG nPort,LONG nRelativePos);
LONG  __stdcall HISI_PLAY_GetPlayPos(LONG nPort);
BOOL  __stdcall HISI_Play_SetVolume(LONG nPort,WORD nVolume);
BOOL  __stdcall HISI_Play_PlaySound(LONG nPort);
BOOL  __stdcall HISI_Play_StopSound();
//流操作
BOOL  __stdcall HISI_Play_OpenStream(LONG nPort);
BOOL  __stdcall HISI_Play_CloseStream(LONG nPort);
BOOL  __stdcall HISI_Play_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
//获取播放信息
DWORD  __stdcall HISI_Play_GetFileTime(LONG nPort);
DWORD  __stdcall HISI_Play_GetPlayedTime(LONG nPort);
//抓图
BOOL HISI_Play_CapturePicture(LONG nPort, char *sPicFileName);
#endif //
////////////////////////////////////////////////////////////////////////////////
// Copyright (C), 2009-2010, Beijing Hanbang Technology, Inc.
////////////////////////////////////////////////////////////////////////////////
//
// File Name:   NetSDK.h
// Author:      
// Version:     3.00
// Date:        
// Description: Header file of 7000SDK.dll and 7000SDK.lib.
// History:
//
////////////////////////////////////////////////////////////////////////////////

// 原汉邦接口
#ifndef HB_NETSDK_H
#define HB_NETSDK_H

#include "HBPlaySDK.h"

#define HB_SDVR_API  extern "C"/*__declspec(dllexport)*/

// #ifdef __cplusplus
// extern "C" {
// #endif

// 宏定义
#define TM_COM_GUI_BRUSH                    0x0001002e      //雨刷
#define TILT_UP			                    0x0001000c	/* 云台以SS的速度上仰 */
#define TILT_DOWN		                    0x0001000d	/* 云台以SS的速度下俯 */
#define PAN_LEFT		                    0x0001000e 	/* 云台以SS的速度左转 */
#define PAN_RIGHT		                    0x0001000f	/* 云台以SS的速度右转 */
#define ZOOM_IN			                    0x00010016	/* 焦距以速度SS变大(倍率变大) */
#define ZOOM_OUT		                    0x00010017 	/* 焦距以速度SS变小(倍率变小) */
#define IRIS_OPEN		                    0x00010018 	/* 光圈以速度SS扩大 */
#define IRIS_CLOSE		                    0x00010019	/* 光圈以速度SS缩小 */
#define FOCUS_FAR		                    0x00010015 	/* 焦点以速度SS后调 */
#define FOCUS_NEAR		                    0x00010014      /* 焦点以速度SS前调 */

#define LIGHT_PWRON		                    0x00010024	/* 接通灯光电源 */
#define WIPER_PWRON		                    0x00010025	/* 接通雨刷开关 */
#define PAN_AUTO		                    0x0001001c 	/* 云台以SS的速度左右自动扫描 */
#define SET_PRESET		                    0x0001001a 	// 设置预置点 
#define CLE_PRESET		                    18	// 清除预置点 
#define FAN_PWRON		                    19	/* 接通风扇开关 */
#define HEATER_PWRON                        20	/* 接通加热器开关 */
#define AUX_PWRON		                    21	/* 接通辅助设备开关 */

#define FILL_PRE_SEQ                        30	/* 将预置点加入巡航序列 */
#define SET_SEQ_DWELL                       31	/* 设置巡航点停顿时间 */
#define SET_SEQ_SPEED                       32	/* 设置巡航速度 */
#define CLE_PRE_SEQ		                    33	/* 将预置点从巡航序列中删除 */
#define STA_MEM_CRUISE                      34	/* 开始记录轨迹 */
#define STO_MEM_CRUISE                      35	/* 停止记录轨迹 */
#define RUN_CRUISE		                    36	/* 开始轨迹 */
#define RUN_SEQ			                    37	/* 开始巡航 */
#define STOP_SEQ		                    38	/* 停止巡航 */
#define GOTO_PRESET		                    0x0001001b 	/* 快球转到预置点 */
#define SYSTEM_RESET	                    40	/* 系统复位 */
////////////////////
//显示模式
#ifndef DISPLAY_MODE_defined
#define DISPLAY_MODE_defined
enum{NORMALMODE = 0,OVERLAYMODE};
#endif

//发送模式
#ifndef SEND_MODE_defined
#define SEND_MODE_defined
enum{PTOPTCPMODE,PTOPUDPMODE,MULTIMODE,RTPMODE,AUDIODETACH,NOUSEMODE};
#endif



#define HB_SDVR_SYSHEAD 	        64	//系统头数据
#define HB_SDVR_STREAMDATA 	        2	//流数据
#define HB_SDVR_BACKUPEND           3   // 备份结束

//播放控制命令宏定义 HB_SDVR_PlayBackControl,HB_SDVR_PlayControlLocDisplay,HB_SDVR_DecPlayBackCtrl的宏定义
#define HB_SDVR_PLAYSTART		    1//开始播放
#define HB_SDVR_PLAYSTOP		    2//停止播放
#define HB_SDVR_PLAYPAUSE		    3//暂停播放
#define HB_SDVR_PLAYRESTART		    4//恢复播放
#define HB_SDVR_PLAYFAST		    5//快放
#define HB_SDVR_PLAYSLOW		    6//慢放
#define HB_SDVR_PLAYBACK		    21//后退
#define HB_SDVR_PLAYNORMAL		    7//正常速度
#define HB_SDVR_PLAYFRAME		    8//单帧放
#define HB_SDVR_PLAYSTARTAUDIO		9//打开声音
#define HB_SDVR_PLAYSTOPAUDIO		10//关闭声音
#define HB_SDVR_PLAYAUDIOVOLUME		11//调节音量
#define HB_SDVR_PLAYGETPOS		    13 //获取文件回放的进度   当等于100时候表示结束
#define HB_SDVR_PLAYBYSLIDER	    22//按进度条播放

#define  HB_SDVR_SET_SERIALID       0x67
#define  HB_SDVR_GET_SERIALID       0x68
#define  HB_SDVR_GET_VLostStatus    0x69


//HB_SDVR_GetDVRConfig,HB_SDVR_GetDVRConfig的命令定义
#define HB_SDVR_GET_DEVICECFG		100		//获取设备参数
#define HB_SDVR_SET_DEVICECFG		101		//设置设备参数
#define HB_SDVR_GET_NETCFG			102		//获取网络参数
#define HB_SDVR_SET_NETCFG			103		//设置网络参数
#define HB_SDVR_GET_PICCFG			104		//获取图象参数
#define HB_SDVR_SET_PICCFG			105		//设置图象参数
#define HB_SDVR_GET_COMPRESSCFG		106		//获取压缩参数
#define HB_SDVR_SET_COMPRESSCFG		107		//设置压缩参数
#define HB_SDVR_GET_RECORDCFG		108		//获取录像时间参数
#define HB_SDVR_SET_RECORDCFG		109		//设置录像时间参数
#define HB_SDVR_GET_DECODERCFG		110		//获取解码器参数
#define HB_SDVR_SET_DECODERCFG		111		//设置解码器参数
#define HB_SDVR_GET_RS232CFG 		112		//获取232串口参数
#define HB_SDVR_SET_RS232CFG		113		//设置232串口参数
#define HB_SDVR_GET_ALARMINCFG 		114		//获取报警输入参数
#define HB_SDVR_SET_ALARMINCFG		115		//设置报警输入参数
//兼容最多128路机器 
#define HB_SDVR_GET_ALARMINCFG_NVS	128		//获取报警输入参数
#define HB_SDVR_SET_ALARMINCFG_NVS	129		//设置报警输入参数

#define HB_SDVR_GET_ALARMOUTCFG 	116		//获取报警输出参数
#define HB_SDVR_SET_ALARMOUTCFG		117		//设置报警输出参数
#define HB_SDVR_GET_TIMECFG 		118		//获取DVR时间
#define HB_SDVR_SET_TIMECFG			119		//设置DVR时间
#define HB_SDVR_GET_PREVIEWCFG 		120		//获取预览参数
#define HB_SDVR_SET_PREVIEWCFG		121		//设置预览参数
#define HB_SDVR_GET_VIDEOOUTCFG 	122		//获取视频输出参数
#define HB_SDVR_SET_VIDEOOUTCFG		123		//设置视频输出参数
#define HB_SDVR_GET_USERCFG 		124		//获取用户参数
#define HB_SDVR_SET_USERCFG			125		//设置用户参数
//兼容最多128路机器类型的扩展命令
#define HB_SDVR_GET_USERCFG_NVS		206		//获取用户参数
#define HB_SDVR_SET_USERCFG_NVS		207		//设置用户参数

#define HB_SDVR_GET_EXCEPTIONCFG 	126		//获取异常参数
#define HB_SDVR_SET_EXCEPTIONCFG	127		//设置异常参数
//叠加字符
#define HB_SDVR_GET_SHOWSTRING		130		//获取叠加字符参数
#define HB_SDVR_SET_SHOWSTRING		131		//设置叠加字符参数
//GE ODM
#define HB_SDVR_GET_EVENTCOMPCFG	132		//获取事件触发录像参数
#define HB_SDVR_SET_EVENTCOMPCFG	133		//设置事件触发录像参数

#define HB_SDVR_GET_FTPCFG			134		//获取抓图的FTP参数
#define HB_SDVR_SET_FTPCFG			135		//设置抓图的FTP参数
#define HB_SDVR_GET_JPEGCFG			136		//获取抓图的JPEG参数
#define HB_SDVR_SET_JPEGCFG			137		//设置抓图的JPEG参数
//北京华纬讯
#define HB_SDVR_GET_PPPOECFG		138		//获取PPPoE参数
#define HB_SDVR_SET_PPPOECFG		139     //设置PPPoE参数
//HS设备辅助输出
#define HB_SDVR_GET_AUXOUTCFG		140		//获取报警触发辅助输出设置
#define HB_SDVR_SET_AUXOUTCFG		141		//设置报警触发辅助输出设置

#define HB_SDVR_GET_PICCFG_EX		200		//获取图象参数（扩展）
#define HB_SDVR_SET_PICCFG_EX		201		//设置图象参数（扩展）

#define HB_SDVR_GET_PICCFG_EX_NVS	204		//获取图象参数（扩展）兼容最多128路机器
#define HB_SDVR_SET_PICCFG_EX_NVS	205		//设置图象参数（扩展）兼容最多128路机器

//SDK_V15 扩展命令
#define HB_SDVR_GET_USERCFG_EX 		202		//获取用户参数
#define HB_SDVR_SET_USERCFG_EX		203		//设置用户参数
#define HB_SDVR_GET_DNS             301
#define HB_SDVR_SET_DNS             302
#define HB_SDVR_GET_DNS_NVS         305
#define HB_SDVR_SET_DNS_NVS         306
#define HB_SDVR_GET_PPPoE           303
#define HB_SDVR_SET_PPPoE           304


#define	  HB_SDVR_SERVERCFG_GET		400	//获取平台服务器参数
#define	  HB_SDVR_SERVERCFG_SET		401	//获设置平台服务器参数


//消息方式
//异常类型
#define EXCEPTION_EXCHANGE			0x8000	//用户交互时异常
#define EXCEPTION_AUDIOEXCHANGE		0x8001	//语音对讲异常
#define EXCEPTION_ALARM				0x8002	//报警异常
#define EXCEPTION_PREVIEW			0x8003	//网络预览异常
#define EXCEPTION_SERIAL			0x8004	//透明通道异常
#define EXCEPTION_RECONNECT			0x8005	//预览时重连

#define NAME_LEN 					32
#define SERIALNO_LEN 				48
#define MACADDR_LEN 				6
#define MAX_ETHERNET 				2
#define PATHNAME_LEN 				128
#define PASSWD_LEN 					16
#define MAX_CHANNUM 				16
#define MAX_CHANNUM_EX				128  //为了兼容7024T及nvs机器类型
#define MAX_ALARMOUT 				4
#define MAX_ALARMOUT_EX 			128
#define MAX_TIMESEGMENT				2
#define MAX_PRESET					128
#define MAX_DAYS 					8
#define PHONENUMBER_LEN				32
#define MAX_DISKNUM 				16
#define MAX_WINDOW 					16
#define MAX_VGA 					1
#define MAX_USERNUM 				16
#define MAX_EXCEPTIONNUM			16
#define MAX_LINK 					32
#define MAX_ALARMIN 				16
#define MAX_ALARMIN_EX 				128
#define MAX_VIDEOOUT 				2
#define MAX_NAMELEN					16		//DVR本地登陆名
#define MAX_RIGHT					32		//权限
#define CARDNUM_LEN 				20
#define MAX_SHELTERNUM				4
#define MAX_DECPOOLNUM				4
#define MAX_DECNUM					4
#define MAX_TRANSPARENTNUM			2
#define MAX_STRINGNUM				4
#define MAX_AUXOUT					4

/* 网络接口定义 */
#define NET_IF_10M_HALF				1					/* 10M ethernet */
#define NET_IF_10M_FULL				2
#define NET_IF_100M_HALF			3					/* 100M ethernet */
#define NET_IF_100M_FULL			4
#define NET_IF_AUTO					5

//设备类型		
#define DVR                         1
#define ATMDVR                      2
#define DVS                         3
#define DEC                         4  /* 6001D */
#define ENC_DEC                     5  /* 6001F */
#define DVR_HC                      6
#define DVR_HT                      7
#define DVR_HF                      8
#define DVR_HS                      9
#define DVR_HTS                     10
#define DVR_HB                      11
#define DVR_HCS		                12
#define DVS_A		                13
#define MAX_LOG_NUM                100
/////
#define MFS_REC_TYPE_MANUAL         1 
#define MFS_REC_TYPE_SCHEDULE       2 
#define MFS_REC_TYPE_MOTION         4 
#define MFS_REC_TYPE_ALARM          8 
#define MFS_REC_TYPE_ALL            0xff
////////
#define MAX_REC_NUM 100
/*处理方式*/
#define NOACTION			        0x0				/*无响应*/
#define WARNONMONITOR		        0x1				/*监视器上警告*/
#define WARNONAUDIOOUT		        0x2				/*声音警告*/
#define UPTOCENTER			        0x4				/*上传中心*/
#define TRIGGERALARMOUT		        0x8				/*触发报警输出*/

 







/* PTZ type */
#define YOULI			0
#define LILIN_1016		1
#define LILIN_820		2
#define PELCO_P			3
#define DM_QUICKBALL	4
#define HD600			5
#define JC4116			6
#define PELCO_DWX		7
#define PELCO_D			8
#define VCOM_VC_2000	9
#define NETSTREAMER		10
#define SAE				11
#define SAMSUNG			12
#define KALATEL_KTD_312 13
#define CELOTEX			14
#define TLPELCO_P		15
#define TL_HHX2000		16
#define BBV				17
#define RM110			18
#define KC3360S			19
#define ACES			20
#define ALSON			21
#define INV3609HD		22
#define HOWELL			23
#define TC_PELCO_P		24
#define TC_PELCO_D		25
#define AUTO_M			26
#define AUTO_H			27
#define ANTEN			28
#define CHANGLIN		29
#define DELTADOME		30
#define XYM_12			31
#define ADR8060			32
#define EVI				33
#define Demo_Speed		34
#define DM_PELCO_D		35
#define ST_832			36
#define LC_D2104		37
#define HUNTER			38
#define A01				39
#define TECHWIN			40
#define WEIHAN			41
#define LG				42
#define D_MAX			43
#define PANASONIC		44
#define KTD_348			45
#define INFINOVA		46
#define PIH717			47
#define IDOME_IVIEW_LCU 48
#define DENNARD_DOME    49
#define PHLIPS			50
#define SAMPLE			51
#define PLD             52
#define PARCO           53
#define HY				54
#define NAIJIE			55
#define CAT_KING		56
#define YH_06			57
#define SP9096X			58
#define M_PANEL			59
#define M_MV2050		60
#define SAE_QUICKBALL	61
#define RED_APPLE		62
#define NKO8G			63
#define DH_CC440		64
///////////////////////////////////////
//DVR日志
/* 报警 */
//主类型
#define MAJOR_ALARM				0x1
//次类型
#define MINOR_ALARM_IN			0x1		/* 报警输入 */
#define MINOR_ALARM_OUT			0x2		/* 报警输出 */
#define MINOR_MOTDET_START		0x3		/* 移动侦测报警开始 */
#define MINOR_MOTDET_STOP		0x4		/* 移动侦测报警结束 */
#define MINOR_HIDE_ALARM_START	0x5		/* 遮挡报警开始 */
#define MINOR_HIDE_ALARM_STOP	0x6		/* 遮挡报警结束 */

/* 异常 */
//主类型
#define MAJOR_EXCEPTION			0x2
//次类型
#define MINOR_VI_LOST			0x21	/* 信号丢失 */
#define MINOR_ILLEGAL_ACCESS	0x22	/* 非法访问 */
#define MINOR_HD_FULL			0x23	/* 硬盘满 */
#define MINOR_HD_ERROR			0x24	/* 硬盘错误 */
#define MINOR_DCD_LOST			0x25	/* MODEM 掉线 */
#define MINOR_IP_CONFLICT		0x26	/* IP地址冲突 */
#define MINOR_NET_BROKEN		0x27	/* 网线断 */
/* 操作 */
//主类型
#define MAJOR_OPERATION			0x3
//次类型
#define MINOR_START_DVR			0x41	/* 开机 */
#define MINOR_STOP_DVR			0x42	/* 关机 */
#define MINOR_STOP_ABNORMAL		0x43	/* 非法关机 */

#define MINOR_LOCAL_LOGIN		0x50	/* 本地登陆 */
#define MINOR_LOCAL_LOGOUT		0x51	/* 本地注销登陆 */
#define MINOR_LOCAL_CFG_PARM	0x52	/* 本地配置参数 */
#define MINOR_LOCAL_PLAYBYFILE	0x53	/* 本地按文件回放 */
#define MINOR_LOCAL_PLAYBYTIME	0x54	/* 本地按时间回放 */
#define MINOR_LOCAL_START_REC	0x55	/* 本地开始录像 */
#define MINOR_LOCAL_STOP_REC	0x56	/* 本地停止录像 */
#define MINOR_LOCAL_PTZCTRL		0x57	/* 本地云台控制 */
#define MINOR_LOCAL_PREVIEW		0x58	/* 本地预览 */
#define MINOR_LOCAL_MODIFY_TIME	0x59	/* 本地修改时间 */
#define MINOR_LOCAL_UPGRADE		0x5a	/* 本地升级 */
#define MINOR_LOCAL_COPYFILE	0x5b	/* 本地备份文件 */

#define MINOR_REMOTE_LOGIN		0x70	/* 远程登录 */
#define MINOR_REMOTE_LOGOUT		0x71	/* 远程注销登陆 */
#define MINOR_REMOTE_START_REC	0x72	/* 远程开始录像 */
#define MINOR_REMOTE_STOP_REC	0x73	/* 远程停止录像 */
#define MINOR_START_TRANS_CHAN	0x74	/* 开始透明传输 */
#define MINOR_STOP_TRANS_CHAN	0x75	/* 停止透明传输 */
#define MINOR_REMOTE_GET_PARM	0x76	/* 远程获得参数 */
#define MINOR_REMOTE_CFG_PARM	0x77	/* 远程配置参数 */
#define MINOR_REMOTE_GET_STATUS 0x78	/* 远程获得状态 */
#define MINOR_REMOTE_ARM		0x79	/* 远程布防 */
#define MINOR_REMOTE_DISARM		0x7a	/* 远程撤防 */
#define MINOR_REMOTE_REBOOT		0x7b	/* 远程重启 */
#define MINOR_START_VT			0x7c	/* 开始语音对讲 */
#define MINOR_STOP_VT			0x7d	/* 停止语音对讲 */
#define MINOR_REMOTE_UPGRADE	0x7e	/* 远程升级 */
#define MINOR_REMOTE_PLAYBYFILE	0x7f	/* 远程按文件回放 */
#define MINOR_REMOTE_PLAYBYTIME	0x80	/* 远程按时间回放 */
#define MINOR_REMOTE_PTZCTRL	0x81	/* 远程云台控制 */
//////////////////////
enum BUSZZERSTATE
{
    BUZZER_CLOSE,
    BUZZER_OPEN
};
////////////////////////////////////////
#define	INFO_LEN		            32
#define	INFO_SEQ		            4
//////////////////////////////
#define COMM_ALARM					0x1100	//报警信息
#define COMM_CONNECT				0x1200	//主机网络断开
////////////////////////////
#define PRESETNUM                   16
////////////////////////////
//DS-6001D/F 
/*解码设备控制码定义*/
#define NET_DEC_STARTDEC		    1
#define NET_DEC_STOPDEC			    2
#define NET_DEC_STOPCYCLE		    3
#define NET_DEC_CONTINUECYCLE		4
//////////////////////////////////////////
//
#define  MAX_KEYNUM 19
/////////////////////////////////
//ptz协议
#define MAXPTZNUM                               100
///////////////////////////////////////////////////

////////////////////////////////////////////
#define     MAX_SMTP_HOST                       128
#define     MAX_SMTP_ADDR                       256
#define     MAX_STRING                          32
///////////////////////////////////////////

#define PT_ATMI_MAX_ALARM_NUM 	                10  //最多十个报警结果
// 错误码
#define HB_SDVR_NOERROR 			        0   //没有错误
#define HB_SDVR_PASSWORD_ERROR 				-1  //用户名密码错误
#define HB_SDVR_NOENOUGHPRI 				-2  //权限不足
#define HB_SDVR_NOINIT 					    -3  //没有初始化
#define HB_SDVR_CHANNEL_ERROR 				-4  //通道号错误
#define HB_SDVR_OVER_MAXLINK 				-5  //连接到DVR的客户端个数超过最大
#define HB_SDVR_VERSIONNOMATCH				-6  //版本不匹配
#define HB_SDVR_NETWORK_FAIL_CONNECT	    -7 //连接服务器失败
#define HB_SDVR_NETWORK_SEND_ERROR			-8 //向服务器发送失败
#define HB_SDVR_NETWORK_RECV_ERROR			-9 //从服务器接收数据失败
#define HB_SDVR_NETWORK_RECV_TIMEOUT	    -10 //从服务器接收数据超时
#define HB_SDVR_NETWORK_ERRORDATA			-11 //传送的数据有误
#define HB_SDVR_ORDER_ERROR				    -12 //调用次序错误
#define HB_SDVR_OPERNOPERMIT				-13 //无此权限
#define HB_SDVR_COMMANDTIMEOUT				-14 //DVR命令执行超时
#define HB_SDVR_ERRORSERIALPORT				-15 //串口号错误
#define HB_SDVR_ERRORALARMPORT				-16 //报警端口错误
#define HB_SDVR_PARAMETER_ERROR 			-17  //参数错误
#define HB_SDVR_CHAN_EXCEPTION				-18	//服务器通道处于错误状态
#define HB_SDVR_NODISK					    -19	//没有硬盘
#define HB_SDVR_ERRORDISKNUM				-20	//硬盘号错误
#define HB_SDVR_DISK_FULL				    -21	//服务器硬盘满
#define HB_SDVR_DISK_ERROR				    -22	//服务器硬盘出错
#define HB_SDVR_NOSUPPORT				    -23	//服务器不支持
#define HB_SDVR_BUSY					    -24	//服务器忙
#define HB_SDVR_MODIFY_FAIL				    -25	//服务器修改不成功
#define HB_SDVR_PASSWORD_FORMAT_ERROR	   	-26	//密码输入格式不正确
#define HB_SDVR_DISK_FORMATING				-27	//硬盘正在格式化，不能启动操作
#define HB_SDVR_DVRNORESOURCE				-28	//DVR资源不足
#define	HB_SDVR_DVROPRATEFAILED				-29  //DVR操作失败
#define HB_SDVR_OPENHOSTSOUND_FAIL 			-30  //打开PC声音失败
#define HB_SDVR_DVRVOICEOPENED 				-31  //服务器语音对讲被占用
#define	HB_SDVR_TIMEINPUTERROR				-32  //时间输入不正确
#define	HB_SDVR_NOSPECFILE				    -33  //回放时服务器没有指定的文件
#define HB_SDVR_CREATEFILE_ERROR			-34	//创建文件出错
#define	HB_SDVR_FILEOPENFAIL				-35  //打开文件出错
#define	HB_SDVR_OPERNOTFINISH				-36  //上次的操作还没有完成
#define	HB_SDVR_GETPLAYTIMEFAIL				-37  //获取当前播放的时间出错
#define	HB_SDVR_PLAYFAIL				    -38  //播放出错
#define HB_SDVR_FILEFORMAT_ERROR			-39  //文件格式不正确
#define HB_SDVR_DIR_ERROR				    -40	//路径错误
#define HB_SDVR_ALLOC_RESOUCE_ERROR			-41  //资源分配错误
#define HB_SDVR_AUDIO_MODE_ERROR			-42	//声卡模式错误
#define HB_SDVR_NOENOUGH_BUF				-43	//缓冲区太小
#define HB_SDVR_CREATESOCKET_ERROR		 	-44	//创建SOCKET出错
#define HB_SDVR_SETSOCKET_ERROR				-45	//设置SOCKET出错
#define HB_SDVR_MAX_NUM					    -46	//个数达到最大
#define HB_SDVR_USERNOTEXIST				-47	//用户不存在
#define HB_SDVR_WRITEFLASHERROR				-48  //写FLASH出错
#define HB_SDVR_UPGRADEFAIL				    -49  //DVR升级失败
#define HB_SDVR_CARDHAVEINIT				-50  //解码卡已经初始化过
#define HB_SDVR_PLAYERFAILED			    -51	//播放器中错误
#define HB_SDVR_MAX_USERNUM				    -52  //用户数达到最大
#define HB_SDVR_GETLOCALIPANDMACFAIL	    -53  //获得客户端的IP地址或物理地址失败
#define HB_SDVR_NOENCODEING				    -54	//该通道没有编码
#define HB_SDVR_IPMISMATCH				    -55	//IP地址不匹配
#define HB_SDVR_MACMISMATCH				    -56	//MAC地址不匹配
#define HB_SDVR_UPGRADELANGMISMATCH			-57	//升级文件语言不匹配
#define HB_SDVR_USERISALIVE				    -58	//用户已登陆 
#define HB_SDVR_UNKNOWNERROR				-59	//未知错误
#define HB_SDVR_KEYVERIFYFAIL               -60 // 密钥验证失败
#define HB_SDVR_IPERR			        	-101	//IP地址不匹配
#define HB_SDVR_MACERR			    		-102	//MAC地址不匹配
#define HB_SDVR_PSWERR			    		-103	//MAC地址不匹配
#define HB_SDVR_USERERR			    		-104	//MAC地址不匹配
#define HB_SDVR_USERISFULL			    	-105	//MAC地址不匹配
#define NO_PERMISSION					    0xf0   //用户没有权限

//查找文件和日志函数返回值
#define HB_SDVR_FILE_SUCCESS				1000	//获得文件信息
#define HB_SDVR_FILE_NOFIND				    1001	//没有文件
#define HB_SDVR_ISFINDING				    1002	//正在查找文件
#define	HB_SDVR_NOMOREFILE				    1003	//查找文件时没有更多的文件
#define	HB_SDVR_FILE_EXCEPTION				1004	//查找文件时异常
// 云台控制命令

// 回放控制命令

// 参数配置命令

#pragma pack(1)
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// 参数配置结构体定义
//为世纪瑞尔需要详细帧信息添加
typedef struct
{
    int frame_type;			  //帧类型 1：I帧 2：P帧 8：音频帧
    struct {
        short	year;
        short	month;
        short	day;
        short	hour;
        short	minute;
        short	second;
        short	milli;	
        short	res1;  //保留
    }ets;                       //时间
    unsigned int	frame_num;  //帧号
    unsigned int	width;	    //图像宽度
    unsigned int	height;	    //图像高度
    short			frame_rate; //帧率
    short			reserve1;	//保留
    int				reserve2;	//保留
}FRAMEINFO,*PFRAMEINFO;
//通道参数
typedef struct
{
	DWORD	dwHandleType;					//按位   2-声音报警   	5-监视器最大化	 	 
	WORD	wAlarmOut;					//报警输出触发通道 按位对应通道
}HB_SDVR_HANDLEEXCEPTION;
typedef struct
{
	DWORD	dwHandleType;					//按位 2-声音报警 5-监视器最大化 6-邮件上传 7-音频报警
	BYTE	wAlarmOut[MAX_CHANNUM_EX];					//报警输出触发通道 按位对应通道
}HB_SDVR_HANDLEEXCEPTION_EX;

typedef  struct  
{
	BYTE  wVodLost[MAX_CHANNUM_EX];     //对应通道 0：视频丢失  1：有视频
	DWORD dwres;						//保留
}HB_SDVR_VODLOST,*LPHB_SDVR_VODLOST;

//上传报警信息
typedef struct{
    BYTE byAlarm[MAX_CHANNUM];	//探头报警
    BYTE byVlost[MAX_CHANNUM];	//信号丢失
    BYTE byMotion[MAX_CHANNUM]; //移动报警
    BYTE byHide[MAX_CHANNUM];	//遮挡报警
    BYTE byDisk[MAX_DISKNUM];   //硬盘状态
}HB_SDVR_ALARMINFO,*LPHB_SDVR_ALARMINFO;

typedef struct	{
    BYTE byAlarm[MAX_CHANNUM_EX];					//探头报警  0-无报价  1-有报警
    BYTE byVlost[MAX_CHANNUM_EX];					//视频丢失  ...
    BYTE byMotion[MAX_CHANNUM_EX];					//移动报警	...
    BYTE byHide[MAX_CHANNUM_EX];						//遮挡报警	...		
    BYTE byDisk[MAX_DISKNUM];						//硬盘状态	
}HB_SDVR_ALARMINFO_EX,*LPHB_SDVR_ALARMINFO_EX;

typedef struct{
	DWORD dwYear;		//年
	DWORD dwMonth;		//月
	DWORD dwDay;		//日
	DWORD dwHour;		//时
	DWORD dwMinute;		//分
	DWORD dwSecond;		//秒
}HB_SDVR_TIME,*LPHB_SDVR_TIME;

typedef struct{
	BYTE byEnable;	//激活
	//开始时间
    BYTE byStartHour;
	BYTE byStartMin;
	//结束时间
	BYTE byStopHour;
	BYTE byStopMin;
}HB_SDVR_SCHEDTIME,*LPHB_SDVR_SCHEDTIME;

//  保留
typedef struct{
	BYTE Output[MAX_ALARMOUT];
}HB_SDVR_ALARMOUTSTATUS,*LPHB_SDVR_ALARMOUTSTATUS;

//图片质量 保留
typedef struct
{
	WORD	wPicSize;				/* 0=CIF, 1=QCIF, 2=D1 */
	WORD	wPicQuality;			/* 图片质量系数 0-最好 1-较好 2-一般 */
}HB_SDVR_JPEGPARA, *LPHB_SDVR_JPEGPARA;

typedef struct  {
	BYTE sSerialNumber[SERIALNO_LEN];		//保留
	BYTE byAlarmInPortNum;					//DVR报警输入个数
	BYTE byAlarmOutPortNum;					//DVR报警输出个数
	BYTE byDiskNum;		 					//DVR 硬盘个数
	BYTE byProtocol;						//新类型产品该值定为0x20，按协议二处理
	BYTE byChanNum;							//DVR 通道个数
	BYTE byStartChan;						//保留
	BYTE sDvrName[NAME_LEN];				//主机名
	BYTE sChanName[MAX_CHANNUM][NAME_LEN];  //通道名称
}HB_SDVR_DEVICEINFO, *LPHB_SDVR_DEVICEINFO;

//add by cui for 7024 or nvs 100325
typedef struct  {
	BYTE sSerialNumber[SERIALNO_LEN];		//序列号：主机端必须返回，从前往后处理，其余补零
	BYTE byAlarmInPortNum;					//DVR报警输入个数
	BYTE byAlarmOutPortNum;					//DVR报警输出个数
	BYTE byDiskNum;		 					//存储设备个数：硬盘/SD卡个数
	BYTE byProtocol;						//协议版本 0x20
	BYTE byChanNum;							//DVR 通道个数
	BYTE byEncodeType;						//主机编码格式：1为ANSI字符串，中文采用GB2312编码；2为UTF8
	BYTE sDvrName[NAME_LEN];				//主机名：须以’\0’结束,与主机编码格式有关
	BYTE sChanName[MAX_CHANNUM_EX][NAME_LEN];  //通道名称：须以’\0’结束,与主机编码格式有关
}HB_SDVR_DEVICEINFO_EX, *LPHB_SDVR_DEVICEINFO_EX;
//end add

//设备硬件信息
typedef struct{
    DWORD dwSize;
    BYTE sDVRName[NAME_LEN];				//DVR名称
    DWORD dwDVRID;							//保留
    DWORD dwRecycleRecord;					//保留
    //以下不能更改
    BYTE sSerialNumber[SERIALNO_LEN];		//保留
    BYTE sSoftwareVersion[16];				//软件版本号
    BYTE sSoftwareBuildDate[16];			//软件生成日期
    DWORD dwDSPSoftwareVersion;				//DSP软件版本
    //	BYTE sDSPSoftwareBuildDate[16];		// DSP软件生成日期
    BYTE sPanelVersion[16];					// 前面板版本
    BYTE sHardwareVersion[16];				//保留
    BYTE byAlarmInPortNum;					//DVR报警输入个数
    BYTE byAlarmOutPortNum;					//DVR报警输出个数
    BYTE byRS232Num;						//保留
    BYTE byRS485Num;						//保留
    BYTE byNetworkPortNum;					//保留
    BYTE byDiskCtrlNum;						//保留
    BYTE byDiskNum;							//DVR 硬盘个数
    BYTE byDVRType;							//DVR类型, 1:DVR 2:ATM DVR 3:DVS 建议使用HB_SDVR_GetDeviceType
    BYTE byChanNum;							//DVR 通道个数
    BYTE byStartChan;						//保留
    BYTE byDecordChans;						//保留
    BYTE byVGANum;							//保留
    BYTE byUSBNum;							//保留
    char reservedData[3];					//保留 
}HB_SDVR_DEVICECFG,*LPHB_SDVR_DEVICECFG;

//设备网络信息
typedef struct {
    char sDVRIP[16];					//DVR IP地址
    char sDVRIPMask[16];				//DVR IP地址掩码
    DWORD dwNetInterface;				//网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M自适应 6-100M半双工 7-1000M半双工
                                        // 8-1000M全双工 9-100M/1000M自适应 10-10000M半双工 11-10000M全双工 12-100M/1000M/10000M自适应(扩展)
    WORD wDVRPort;						//端口号
    BYTE byMACAddr[MACADDR_LEN];		//服务器的物理地址
}HB_SDVR_ETHERNET;

//网络配置结构
typedef struct{
    DWORD dwSize;
    HB_SDVR_ETHERNET struEtherNet[MAX_ETHERNET];		/* 以太网口 */
    char sManageHostIP[16];				//远程管理主机地址
    WORD wManageHostPort;				//保留
    char sDNSIP[16];					//DNS服务器地址  
    char sMultiCastIP[16];				//多播组地址
    char sGatewayIP[16];       			//网关地址 
    char sNFSIP[16];					//保留	
    BYTE sNFSDirectory[PATHNAME_LEN];	//保留
    DWORD dwPPPOE;						//0-不启用,1-启用
    BYTE sPPPoEUser[NAME_LEN];			//PPPoE用户名
    char sPPPoEPassword[PASSWD_LEN];	// PPPoE密码
    char sPPPoEIP[16];					//PPPoE IP地址 
    WORD wHttpPort;						//HTTP端口号
}HB_SDVR_NETCFG,*LPHB_SDVR_NETCFG;

typedef struct{
	LONG lChannel;						//通道号
	LONG lLinkMode;						//最高位(31)为0表示主码流，为1表示子码流，0－30位表示码流连接方式: 0：TCP方式,1：UDP方式,2：多播方式 
	HWND hPlayWnd;						//播放窗口的句柄,为NULL表示不播放图象
	char sMultiCastIP[16];					//保留
}HB_SDVR_CLIENTINFO,*LPHB_SDVR_CLIENTINFO;


typedef struct{
    LONG lChannel;						//通道号
    LONG lLinkMode;						//最高位(31)为0表示主码流，为1表示子码流，0－30位表示码流连接方式: 0：TCP方式,1：UDP方式,2：多播方式 
    HWND hPlayWnd;						//播放窗口的句柄,为NULL表示不播放图象
    char sMultiCastIP[16];					//保留
    DWORD msgid;
}HB_SDVR_CLIENTINFO_EX,*LPHB_SDVR_CLIENTINFO_EX;


typedef struct {
	DWORD	dwBrightValue;		//亮度  1-127
	DWORD	dwContrastValue;	//对比度1-127
	DWORD	dwSaturationValue;	//饱和度1-127
	DWORD	dwHueValue;			//色度	1-127
}HB_SDVR_VIDEOPARAM;

typedef struct {
	WORD wStartTime;			//高8位表示小时 低8位表示分钟
	WORD wEndTime;				//高8位表示小时 低8位表示分钟
	HB_SDVR_VIDEOPARAM VideoParam;
}HB_SDVR_SCHEDULE_VIDEOPARAM;

typedef struct  {
	BYTE	byChannel;			//通道号
	char reservedData[3];
	HB_SDVR_SCHEDULE_VIDEOPARAM Schedule_VideoParam[2]; //一天包含2个时间段
	HB_SDVR_VIDEOPARAM Default_VideoParam;				//不在时间段内就使用默认
}HB_SDVR_VIDEOEFFECT,*LPHB_SDVR_VIDEOEFFECT; 

typedef struct {
	BYTE Channel[MAX_CHANNUM_EX];
}HB_SDVR_REMOTERECORDCHAN,*LPHB_SDVR_REMOTERECORDCHAN;

typedef  enum
{
    NET_DEVTYPE_7000T = 0, 
    NET_DEVTYPE_8000T,
    NET_DEVTYPE_8200T,
    NET_DEVTYPE_8000ATM,
    NET_DEVTYPE_8600T,		//8600T
    NET_DEVTYPE_6200T,
    NET_DEVTYPE_8004AH,
    NET_DEVTYPE_8004AI,
    NET_DEVTYPE_7000H,
    NET_DEVTYPE_7200H,
    NET_DEVTYPE_7000M = 12,
    NET_DEVTYPE_8000M,
    NET_DEVTYPE_8200M,
    NET_DEVTYPE_7000L,
    NET_DEVTYPE_2201TL = 16,
    NET_DEVTYPE_2600T,
    NET_DEVTYPE_2600TB,		//人流统计智能分析盒
    NET_DEVTYPE_2600TC,		//车牌识别智能分析盒
    NET_DEVTYPE_9300,
    NET_DEVTYPE_9400,

    HB9824N16H = 1000,
    HB9832N16H,
    HB9904,
    HB9908,
    HB9912,
    HB9916,
    HB9932,
    HB7904,
    HB7908,
    HB7912,
    HB7916,
}HB_SDVR_TYPE_E;

typedef  enum
{
    NET_SIZE_8M = 0,		// 8M
    NET_SIZE_16M ,			// 16M
    NET_SIZE_32M ,			// 32M
    NET_SIZE_64M ,			// 64M
    NET_SIZE_128M ,			// 128M
    NET_SIZE_256M ,			// 256M
    NET_SIZE_512M ,			// 512M
    NET_SIZE_1024M,		    // 1024M
}HB_SDVR_MEMSIZE_E;

typedef struct {
	ULONG   dvrtype;        // 7004  8004  2004机器型号
	WORD    dwDevice_type;  // HB_SDVR_TYPE_E
    WORD    memory_size;    // HB_SDVR_MEMSIZE_E
    DWORD   dwReserve;
}HB_SDVR_INFO,*LPHB_SDVR_INFO; 

// 移动侦测区域，分22*18个小宏块
#define     MOTION_SCOPE_WIDTH      22
#define     MOTION_SCOPE_HIGHT      18
//通道图象结构
//移动侦测
typedef struct{
	BYTE byMotionScope[18][22];			//侦测区域,共有22*18个小宏块,为1表示该宏块是移动侦测区域,0-表示不是 
	BYTE byMotionSensitive;				//移动侦测灵敏度, 0 - 5,越高越灵敏,0xff关闭*/
	BYTE byEnableHandleMotion;			// 是否处理移动侦测 */ 
	HB_SDVR_HANDLEEXCEPTION struMotionHandleType;	// 处理方式 */
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间
	BYTE byRelRecordChan[MAX_CHANNUM]; //报警触发的录象通道,为1表示触发该通道	
}HB_SDVR_MOTION,*LPHB_SDVR_MOTION;

//add by cui for 7024 or nvs 100329
typedef struct{
	BYTE byMotionScope[18][22];			//侦测区域,共有22*18个小宏块,为1表示该宏块是移动侦测区域,0-表示不是 
	BYTE byMotionSensitive;				//移动侦测灵敏度, 0 - 5,越高越灵敏,0xff关闭*/
	BYTE byEnableHandleMotion;			// 是否处理移动侦测 */ 
	HB_SDVR_HANDLEEXCEPTION_EX struMotionHandleType;	// 处理方式 */
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间
	BYTE byRelRecordChan[MAX_CHANNUM_EX]; //报警触发的录象通道,为1表示触发该通道	
}HB_SDVR_MOTION_EX,*LPHB_SDVR_MOTION_EX;
//end add

//遮挡报警区域为 
typedef struct{
	DWORD dwEnableHideAlarm;			//保留
	WORD wHideAlarmAreaTopLeftX;		//保留
	WORD wHideAlarmAreaTopLeftY;		//保留
	WORD wHideAlarmAreaWidth;			//保留
	WORD wHideAlarmAreaHeight;			//保留
	HB_SDVR_HANDLEEXCEPTION struHideAlarmHandleType;	//保留
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//保留
}HB_SDVR_HIDEALARM,*LPHB_SDVR_HIDEALARM;

//遮挡报警区域为 
typedef struct{
	DWORD dwEnableHideAlarm;			//保留
	WORD wHideAlarmAreaTopLeftX;		//保留
	WORD wHideAlarmAreaTopLeftY;		//保留
	WORD wHideAlarmAreaWidth;			//保留
	WORD wHideAlarmAreaHeight;			//保留
	HB_SDVR_HANDLEEXCEPTION_EX struHideAlarmHandleType;	//保留
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//保留
}HB_SDVR_HIDEALARM_EX,*LPHB_SDVR_HIDEALARM_EX;

//信号丢失报警
typedef struct{
	BYTE byEnableHandleVILost;			// 是否处理信号丢失报警  
	HB_SDVR_HANDLEEXCEPTION strVILostHandleType;	//处理方式 	
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//保留
}HB_SDVR_VILOST,*LPHB_SDVR_VILOST;

typedef struct{
	BYTE byEnableHandleVILost;			// 是否处理信号丢失报警  
	HB_SDVR_HANDLEEXCEPTION_EX strVILostHandleType;	//处理方式 	
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//保留
}HB_SDVR_VILOST_EX,*LPHB_SDVR_VILOST_EX;

typedef struct{
	WORD wHideAreaTopLeftX;				// 遮盖区域的x坐标  
	WORD wHideAreaTopLeftY;				// 遮盖区域的y坐标 
	WORD wHideAreaWidth;				// 遮盖区域的宽  
	WORD wHideAreaHeight;				//遮盖区域的高 
}HB_SDVR_SHELTER,*LPHB_SDVR_SHELTER;

 
typedef struct
{	
	DWORD dwSize;
	BYTE sChanName[NAME_LEN];		// 通道名
	DWORD dwVideoFormat;			// 保留
	BYTE byBrightness;  			// 保留
	BYTE byContrast;    			// 保留
	BYTE bySaturation;  			// 保留
	BYTE byHue;    					// 保留	
	//显示通道名
	DWORD dwShowChanName;			// 保留 
	WORD wShowNameTopLeftX;			// 通道名称显示位置的x坐标  
	WORD wShowNameTopLeftY;			// 通道名称显示位置的y坐标  
 	HB_SDVR_VILOST struVILost;		// 信号丢失报警 
 	HB_SDVR_MOTION struMotion;	    // 移动侦测
 	HB_SDVR_HIDEALARM struHideAlarm;// 保留
 	DWORD dwEnableHide;				// 是否启动遮盖 ,0-否,1-是
	HB_SDVR_SHELTER struShelter[MAX_SHELTERNUM]; 
 	DWORD dwShowOsd;				// 保留
	WORD wOSDTopLeftX;				// 保留
	WORD wOSDTopLeftY;				// 保留
	BYTE byOSDType;					// 保留
 	BYTE byDispWeek;				/* 是否显示星期 */	
	BYTE byOSDAttrib;				//通道名 1-不透明 2-透明
 
}HB_SDVR_PICCFG_EX,*LPHB_SDVR_PICCFG_EX;

//add by cui for 7024 or nvs 100329
typedef struct
{
	DWORD dwSize;
	BYTE sChanName[NAME_LEN];		// 通道名
	DWORD dwVideoFormat;			// 保留
	BYTE byBrightness;  			// 保留
	BYTE byContrast;    			// 保留
	BYTE bySaturation;  			// 保留
	BYTE byHue;    					// 保留	
	//显示通道名
	DWORD dwShowChanName;			// 保留 
	WORD wShowNameTopLeftX;			// 通道名称显示位置的x坐标  
	WORD wShowNameTopLeftY;			// 通道名称显示位置的y坐标  
	HB_SDVR_VILOST_EX struVILost;		// 信号丢失报警
	HB_SDVR_MOTION_EX struMotion;	    // 移动侦测
	HB_SDVR_HIDEALARM_EX struHideAlarm;// 保留
	DWORD dwEnableHide;				// 是否启动遮盖 ,0-否,1-是
	HB_SDVR_SHELTER struShelter[MAX_SHELTERNUM]; 
	DWORD dwShowOsd;				// 保留
	WORD wOSDTopLeftX;				// 保留
	WORD wOSDTopLeftY;				// 保留
	BYTE byOSDType;					// 格式及语言，最高位为0表示解码后叠加，为1表示前端叠加；默认为0，设为0x80时表示将osd设为前端叠加
	BYTE byDispWeek;				/* 是否显示星期 */	
	BYTE byOSDAttrib;				//通道名 1-不透明 2-透明
	
}HB_SDVR_PICCFG_EX_EX,*LPHB_SDVR_PICCFG_EX_EX;
//end add

//兼容只有一个遮挡区域客户端版本 20100504
typedef struct
{
	DWORD dwSize;
	BYTE sChanName[NAME_LEN];		// 通道名
	DWORD dwVideoFormat;			// 保留
	BYTE byBrightness;  			// 保留
	BYTE byContrast;    			// 保留
	BYTE bySaturation;  			// 保留
	BYTE byHue;    					// 保留	
	//显示通道名
	DWORD dwShowChanName;			// 保留 
	WORD wShowNameTopLeftX;			// 通道名称显示位置的x坐标  
	WORD wShowNameTopLeftY;			// 通道名称显示位置的y坐标  
	HB_SDVR_VILOST struVILost;		// 信号丢失报警
	HB_SDVR_MOTION struMotion;	    // 移动侦测
	HB_SDVR_HIDEALARM struHideAlarm;// 保留
	DWORD dwEnableHide;				// 是否启动遮盖 ,0-否,1-是
	HB_SDVR_SHELTER struShelter[1]; 
	DWORD dwShowOsd;				// 保留
	WORD wOSDTopLeftX;				// 保留
	WORD wOSDTopLeftY;				// 保留
	BYTE byOSDType;					// 保留
	BYTE byDispWeek;				/* 是否显示星期 */	
	BYTE byOSDAttrib;				//通道名 1-不透明 2-透明
	
}HB_SDVR_PICCFG_EX_TMP,*LPHB_SDVR_PICCFG_EX_TMP;

//编码压缩参数
//压缩参数
typedef struct{
	BYTE byStreamType;				//码流类型0-无音频,1-有音频
	BYTE byResolution;  			//分辨率	0-CIF 1-HD1, 2-D1；协议二:增加 3-QCIF、 4-720p、5-1080p、6-960H、7-Q960H、8-QQ960H
	BYTE byBitrateType;				//码率类型	0:变码率，1:定码率 2：定画质
	BYTE  byPicQuality;				//图象质量	1-最好 2-次好 3-较好 4-一般5-较差 6-差	
    DWORD dwVideoBitrate; 			//协议一:视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-2M，6-3M，7-4M，8-6M，9-8M，10-12M ,11-自定义
                                    //协议二:视频码率 0-100K、1-128K、2-256K、3-512K、4-1M、5-1.5M、6-2M、7-3M、8-4M 其他:码率值(kbps)有效范围 30~2^32，大于等于32，以K为单位
	DWORD dwVideoFrameRate;			//帧率		2 至 25
}HB_SDVR_COMPRESSION_INFO,*LPHB_SDVR_COMPRESSION_INFO;

typedef struct{
	DWORD dwSize;
	BYTE byRecordType;							//0x0:手动录像，0x1:定时录象，0x2:移动侦测，0x3:报警，0x0f:所有类型
	HB_SDVR_COMPRESSION_INFO struRecordPara;	//录像流（主码流）
	HB_SDVR_COMPRESSION_INFO struNetPara;		//网传流（子码流）
}HB_SDVR_COMPRESSIONCFG,*LPHB_SDVR_COMPRESSIONCFG;
 

//录像参数
typedef struct{
	HB_SDVR_SCHEDTIME struRecordTime;
	BYTE byRecordType;			//保留
	char reservedData[3];		//保留
}HB_SDVR_RECORDSCHED,*LPHB_SDVR_RECORDSCHED;

typedef struct {
	WORD wAllDayRecord;			//保留
	BYTE byRecordType;			//保留
	char reservedData;			//保留
}HB_SDVR_RECORDDAY;

typedef struct {
	DWORD dwSize;
	DWORD dwRecord;					//是否录像 0-否 1-是 
	HB_SDVR_RECORDDAY struRecAllDay[MAX_DAYS];//星期
	HB_SDVR_RECORDSCHED struRecordSched[MAX_DAYS][MAX_TIMESEGMENT]; //时间段
	DWORD dwPreRecordTime;						//保留
}HB_SDVR_RECORD,*LPHB_SDVR_RECORD;


//解码器
typedef struct{
	DWORD dwSize;
	DWORD dwBaudRate;				// 波特率(bps)
    // 协议一，50 75 110 150 300 600 1200 2400 4800 9600 19200 38400 57600 76800 115.2k 
    // 协议二，0-default,1-2400,2-4800,3-9600,4-19200,5-38400； 自定义取值范围[300，115200]
	BYTE byDataBit;					// 数据位 5 6 7 8
	BYTE byStopBit;					// 停止位 1 2 
	BYTE byParity;                  // 校验位 (0-NONE,1-ODD,2-EVEN,3-SPACE)
	BYTE byFlowcontrol;				// 流控(0-无,1-Xon/Xoff,2-硬件)
	WORD wDecoderType;              // 云台协议值，最好先通过HB_SDVR_GetPTZType获取该列表 
 	//	 0-unknow 1-RV800  2-TOTA120 3-S1601 4-CLT-168 5-TD-500  6-V1200 7-ZION 8-ANT 9-CBC 10-CS850A 
	//	 11-CONCORD 12-HD600 13-SAMSUNG 14-YAAN 15-PIH 16-MG-CS160 17-WISDOM 18-PELCOD1 19-PELCOD2 20-PELCOD3 
	//	 21-PELCOD4 22-PELCOP1 23-PELCOP2 24-PELCOP3 25-Philips 26-NEOCAM  27-ZHCD 28-DongTian 29-PELCOD5 30-PELCOD6
	//	 31-Emerson 32-TOTA160 33-PELCOP5
	WORD wDecoderAddress;				// 解码器地址:0 - 255 
	BYTE bySetPreset[MAX_PRESET];		// 保留
	BYTE bySetCruise[MAX_PRESET];		// 保留
	BYTE bySetTrack[MAX_PRESET];		// 保留
}HB_SDVR_DECODERCFG,*LPHB_SDVR_DECODERCFG;


//RS232 
typedef struct{
	char sRemoteIP[16];            //远端IP地址
	char sLocalIP[16];             //本地IP地址
	char sLocalIPMask[16];         //本地IP地址掩码
	BYTE sUsername[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	BYTE byPPPMode;					//PPP模式, 0－主动，1－被动	
	BYTE byRedial;					//是否回拨 ：0-否,1-是
	BYTE byRedialMode;				//回拨模式,0-由拨入者指定,1-预置回拨号码
	BYTE byDataEncrypt;				//数据加密,0-否,1-是
	DWORD dwMTU;					//MTU
	char sTelephoneNumber[PHONENUMBER_LEN];	//电话号码
}HB_SDVR_PPPCFG,*LPHB_SDVR_PPPCFG;

typedef struct{
	DWORD dwSize;
	DWORD dwBaudRate;				// 波特率(bps)  
	BYTE byDataBit;					// 数据有几位 5－8 
	BYTE byStopBit;					// 停止位 1-2 
	BYTE byParity;					// 校验 0－无校验，1－奇校验，2－偶校验;
	BYTE byFlowcontrol;				// 0－无，1－软流控,2-硬流控
	DWORD dwWorkMode;				// 保留
	HB_SDVR_PPPCFG struPPPConfig;   // 保留
}HB_SDVR_RS232CFG,*LPHB_SDVR_RS232CFG;

//报警输入
typedef struct{
	DWORD dwSize;
	BYTE sAlarmInName[NAME_LEN];		// 报警通道名
	BYTE byAlarmType;					// 保留
	BYTE byAlarmInHandle;				// 是否处理 0-1
	HB_SDVR_HANDLEEXCEPTION struAlarmHandleType;	//处理方式 
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间
	BYTE byRelRecordChan[MAX_CHANNUM];		//报警触发的录象通道,为1表示触发该通道
	BYTE byEnablePreset[MAX_CHANNUM];		// 是否调用预置点 仅用byEnablePreset[0]来判断;
	BYTE byPresetNo[MAX_CHANNUM];			// 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 
	BYTE byEnableCruise[MAX_CHANNUM];		// 保留
	BYTE byCruiseNo[MAX_CHANNUM];			// 保留
	BYTE byEnablePtzTrack[MAX_CHANNUM];		// 保留 
	BYTE byPTZTrack[MAX_CHANNUM];			// 保留
	BYTE byRecordTm;						// 报警录像时间 1-99秒 
}HB_SDVR_ALARMINCFG,*LPHB_SDVR_ALARMINCFG;

//add by cui for 7024 or nvs 100325
typedef struct{
	DWORD dwSize;
	BYTE sAlarmInName[NAME_LEN];		// 报警通道名
	BYTE byAlarmType;					// 保留
	BYTE byAlarmInHandle;				// 是否处理 0-1
	HB_SDVR_HANDLEEXCEPTION_EX struAlarmHandleType;	//处理方式 
	HB_SDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间
	BYTE byRelRecordChan[MAX_CHANNUM_EX];		//报警触发的录象通道,为1表示触发该通道
	BYTE byEnablePreset[MAX_CHANNUM_EX];		// 是否调用预置点 仅用byEnablePreset[0]来判断;
	BYTE byPresetNo[MAX_CHANNUM_EX];			// 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 
	BYTE byEnableCruise[MAX_CHANNUM_EX];		// 保留
	BYTE byCruiseNo[MAX_CHANNUM_EX];			// 保留
	BYTE byEnablePtzTrack[MAX_CHANNUM_EX];		// 保留 
	BYTE byPTZTrack[MAX_CHANNUM_EX];			// 保留
	BYTE byRecordTm;						// 报警录像时间 1-99秒 
}HB_SDVR_ALARMINCFG_EX,*LPHB_SDVR_ALARMINCFG_EX;
//end add

//DVR报警输出
typedef struct{
	DWORD dwSize;
	BYTE sAlarmOutName[NAME_LEN];			// 名称 
	DWORD dwAlarmOutDelay;					// 输出保持时间 单位秒
	BYTE byEnSchedule;						// 报警输出布防时间激活 0-屏蔽 1-激活 
	HB_SDVR_SCHEDTIME struAlarmOutTime[MAX_DAYS][MAX_TIMESEGMENT];// 报警输出激活时间段 			
}HB_SDVR_ALARMOUTCFG,*LPHB_SDVR_ALARMOUTCFG;
 

//用户权限
typedef struct{
	BYTE sUserName[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	DWORD dwLocalRight[MAX_RIGHT];	/* 本地权限 */
 	DWORD dwRemoteRight[MAX_RIGHT];	/* 远程权限 */
	/*数组 0: 通道权限*/
	/*数组 1: 显示设置*/
	/*数组 2: 录像参数*/
	/*数组 3: 定时录像*/
	/*数组 4: 移动录像*/
	/*数组 5: 报警录像*/
	/*数组 6: 网络参数*/
	/*数组 7: 云台设置*/
	/*数组 8: 存储管理*/
	/*数组 9: 系统管理*/
	/*数组 10: 信息查询*/
	/*数组 11: 手动录像*/
	/*数组 12: 回放*/
	/*数组 13: 备份*/
	/*数组 14: 视频参数*/
	/*数组 15: 报警清除*/
	/*数组 16: 远程预览*/
	char sUserIP[16];					/* 用户IP地址(为0时表示允许任何地址) */	
	BYTE byMACAddr[MACADDR_LEN];		/* 物理地址 */	
}HB_SDVR_USER_INFO,*LPHB_SDVR_USER_INFO;

typedef struct{
	BYTE sUserName[NAME_LEN];		    /* 用户名 */
	BYTE sPassword[PASSWD_LEN];		    /* 密码 */
	BYTE dwLocalRight[MAX_RIGHT];	    //本地权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    /*数组 1: 常规设置*/
    /*数组 2: 录像设置*/
    /*数组 3: 输出设置*/
    /*数组 4: 报警设置*/
    /*数组 5: 串口设置*/
    /*数组 6: 网络设置*/
    /*数组 7: 录像回放*/
    /*数组 8: 系统管理*/
    /*数组 9: 系统信息*/
    /*数组 10: 报警清除*/
    /*数组 11: 云台控制*/
    /*数组 12: 关机重启*/
    /*数组 13: USB升级*/
    /*数组 14：备份*/
	BYTE LocalChannel[MAX_CHANNUM_EX];	//本地用户对通道的操作权限，最大128个通道，0-无权限，1-有权限
	BYTE dwRemoteRight[MAX_RIGHT];	    //远程登陆用户所具备的权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    /*数组 1: 远程预览*/
    /*数组 2: 参数设置*/
    /*数组 3: 远程回放*/
    /*数组 4: 远程备份*/
    /*数组 5: 查看日志*/
    /*数组 6: 语音对讲*/
    /*数组 7: 远程升级*/
    /*数组 8：远程重启*/
	BYTE RemoteChannel[MAX_CHANNUM_EX];	/* 远程通道权限*/
	char sUserIP[16];				    /* 用户IP地址(为0时表示允许任何地址) */	
	BYTE byMACAddr[MACADDR_LEN];		/* 物理地址 */	
}HB_SDVR_USER_INFO_EX,*LPHB_SDVR_USER_INFO_EX;

typedef struct{
	DWORD dwSize;
	HB_SDVR_USER_INFO struUser[MAX_USERNUM];
}HB_SDVR_USER,*LPHB_SDVR_USER;

typedef struct{
	DWORD dwSize;
	HB_SDVR_USER_INFO_EX struUser[MAX_USERNUM];
}HB_SDVR_USER_EX,*LPHB_SDVR_USER_EX;

//DNS
typedef struct	{
	DWORD dwSize;
	char sDNSUser[INFO_LEN];				// DNS账号
	char sDNSPassword[INFO_LEN];			// DNS密码
	char sDNSAddress[INFO_SEQ][INFO_LEN];	// DNS解析地址
	BYTE sDNSALoginddress;					//DNS解析地址中sDNSAddress数组中的指定解析地址的行数
	BYTE sDNSAutoCon;						//DNS自动重连
	BYTE sDNSState;							//DNS登陆  0-注销 1-登陆
	BYTE sDNSSave;							//DNS信息保存
	WORD sDNServer;// 0-- hanbang.org.cn 1--oray.net 2--dyndns.com
	WORD reserve;	//1--重启主机,0--不重启
}HB_SDVR_DNS,*LPHB_SDVR_DNS;
typedef struct	{
	DWORD dwSize;
	char sDNSUser[INFO_LEN];				// DNS账号
	char sDNSPassword[INFO_LEN];			// DNS密码
	char sDNSAddress[INFO_SEQ][INFO_LEN];	// DNS解析地址
	BYTE sDNSALoginddress;					//DNS解析地址中sDNSAddress数组中的指定解析地址的行数
	BYTE sDNSAutoCon;						//DNS自动重连
	BYTE sDNSState;							//DNS登陆  0-注销 1-登陆
	BYTE sDNSSave;							//DNS信息保存
	WORD sDNServer;// 0-- hanbang.org.cn 1--oray.net 2--dyndns.com
	WORD reserve;	//1--重启主机,0--不重启
	BYTE sDNSname[128];//域名服务器
}HB_SDVR_DNS_EX,*LPHB_SDVR_DNS_EX;

//PPPoE
typedef struct	{
	DWORD dwSize;
	BYTE sPPPoEUser[INFO_LEN];				//PPPoE用户名
	char sPPPoEPassword[INFO_LEN];			// PPPoE密码
	BYTE sPPPoEAutoCon;						//PPPoE自动重连
	BYTE sPPPoEState;						//PPPoE登陆  0-注销 1-登陆
	BYTE sPPPoESave;						//DNS信息保存
	char reservedData;
}HB_SDVR_PPPoE,*LPHB_SDVR_PPPoE;

//平台信息
typedef struct  {
	char sServerIP[16];						//接入服务器IP地址
	ULONG nPort;							//接入服务器端口号
	char puId[NAME_LEN];					//设备注册ID号
	ULONG  nInternetIp ;					// 本地外网IP
    ULONG  nVideoPort;						//视频端口
    ULONG  nTalkPort;						//对讲端口
    ULONG  nCmdPort;						//命令端口
    ULONG  nVodPort;						//点播端口
	ULONG	tran_mode;						// 1 子码流  0 主码流
   // 以下新增
  ULONG ftp_mode;       // 以FTP方式进行中心存储 1 开启 0 关闭
  ULONG max_link;       // 最大连接数 0 - 32
}HB_SDVR_SERVERCFG,*LPHB_SDVR_SERVERCFG;

typedef struct
{
	char sFileName[100];			//文件名
	HB_SDVR_TIME struStartTime;		//文件的开始时间
	HB_SDVR_TIME struStopTime;		//文件的结束时间
	DWORD dwFileSize;				//文件的大小
	unsigned char nCh;				//通道号
	unsigned char nType;			//录像类型
}HB_SDVR_FIND_DATA,*LPHB_SDVR_FIND_DATA;	//cwh 20080730	


typedef struct {
	BYTE byRecordStatic;				//通道是否在录像,0-不录像,1-录像
	BYTE bySignalStatic;				//连接的信号状态,0-正常,1-信号丢失
	BYTE byHardwareStatic;				//保留
	char reservedData;
	DWORD dwBitRate;					//实际码率
	DWORD dwLinkNum;					//客户端连接的个数
	DWORD dwClientIP[MAX_LINK];			//保留
}HB_SDVR_CHANNELSTATE,*LPHB_SDVR_CHANNELSTATE;

typedef struct HB_SDVR_DISKSTATE_ST
{
    DWORD dwVolume;				//硬盘的容量（MB）
    DWORD dwFreeSpace;			//硬盘的剩余空间（MB）
    DWORD dwHardDiskStatic;		//硬盘状态（dwVolume有值时有效） 0-正常 1-磁盘错误 2-文件系统出错
}HB_SDVR_DISKSTATE,*LPHB_SDVR_DISKSTATE;

typedef struct{
	DWORD dwDeviceStatic; 				//保留
	HB_SDVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM]; //硬盘状态
	HB_SDVR_CHANNELSTATE struChanStatic[MAX_CHANNUM];//通道的状态
	DWORD  byAlarmInStatic ;			//报警端口的状态 按位表示
	DWORD  byAlarmOutStatic ;			//报警输出端口的状态 按位表示
	DWORD  dwLocalDisplay;				//保留
}HB_SDVR_WORKSTATE,*LPHB_SDVR_WORKSTATE;

//add by cui for 7024 or nvs 100325
typedef struct{
	DWORD dwDeviceStatic; 				//保留
	HB_SDVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM]; //硬盘状态
	HB_SDVR_CHANNELSTATE struChanStatic[MAX_CHANNUM_EX];//通道的状态
	DWORD  byAlarmInStatic[MAX_ALARMIN_EX] ;			//报警端口的状态 按位表示
	DWORD  byAlarmOutStatic[MAX_ALARMOUT_EX] ;			//报警输出端口的状态 按位表示
	DWORD  dwLocalDisplay;				//保留
}HB_SDVR_WORKSTATE_EX,*LPHB_SDVR_WORKSTATE_EX;
//end add


typedef struct {
	DWORD  byChannel;			//设置通道
	WORD Preset[PRESETNUM];
	WORD PresetPoll;			//多预置点轮巡开启或关闭表示
	WORD presettime;			//多预置点轮巡时间
}HB_SDVR_PRESETPOLL,*LPHB_SDVR_PRESETPOLL;

//预览参数
typedef struct{
	long bToScreen;
	long bToVideoOut;
	long nLeft;
	long nTop;
	long nWidth;
	long nHeight;
	long nReserved;
}HB_SDVR_DISPLAY_PARA,*LPHB_SDVR_DISPLAY_PARA; 
typedef struct{
	LONG lChannel;//通道号
	LONG lLinkMode; //最高位(31)为0表示主码流，为1表示子码流，0－30位表示码流连接方式:0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-电话线，5－128k宽带，6－256k宽带，7－384k宽带，8－512k宽带；
	char* sMultiCastIP;
	HB_SDVR_DISPLAY_PARA struDisplayPara;
}HB_SDVR_CARDINFO,*LPHB_SDVR_CARDINFO;
//2005-08-01
/* 解码设备透明通道设置 */
typedef struct {
	DWORD dwEnableTransPort;	/* 是否启动透明通道 0－不启用 1－启用*/
	char sDecoderIP[16];		/* DVR IP地址 */
	WORD wDecoderPort;			/* 端口号 */
	WORD wDVRTransPort;			/* 配置前端DVR是从485/232输出，1表示485串口,2表示232串口 */		
	char cReserve[4];
}HB_SDVR_PORTINFO, *LPHB_SDVR_PORTINFO;

/*连接的通道配置*/
typedef struct {
	char sDVRIP[16];				/* DVR IP地址 */
	WORD wDVRPort;			 		/* 端口号 */
	BYTE sUserName[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	BYTE byChannel;					/* 通道号 */
	BYTE byLinkMode;				/* 连接模式 */	
	BYTE byLinkType;				/* 连接类型 0－主码流 1－子码流 */
}HB_SDVR_DECCHANINFO, *LPHB_SDVR_DECCHANINFO;

/*每个解码通道的配置*/
typedef struct {	
	BYTE	byPoolChans;			/*每路解码通道上的循环通道数量, 最多4通道*/
	HB_SDVR_DECCHANINFO struchanConInfo[MAX_DECPOOLNUM];
	BYTE	byEnablePoll;			/*是否轮巡 0-否 1-是*/
	BYTE	byPoolTime;				/*轮巡时间 0-保留 1-10秒 2-15秒 3-20秒 4-30秒 5-45秒 6-1分钟 7-2分钟 8-5分钟 */	
}HB_SDVR_DECINFO, *LPHB_SDVR_DECINFO;

/*整个设备解码配置*/
typedef struct {
	DWORD	dwSize;
	DWORD	dwDecChanNum; 		/*解码通道的数量*/
	HB_SDVR_DECINFO struDecInfo[MAX_DECNUM];
}HB_SDVR_DECCFG, *LPHB_SDVR_DECCFG;


typedef struct{
	USHORT m_Year;
	USHORT m_Month;
	USHORT m_Day;
	USHORT m_Hour;
	USHORT m_Minute;
	USHORT m_Second;
	BYTE DeviceName[24];	//设备名称
	DWORD dwChannelNumer;	//通道号
	BYTE CardNumber[32];	//卡号
	char cTradeType[12];	//交易类型
	DWORD dwCash;			//交易金额
}HB_SDVR_TRADEINFO,*LPHB_SDVR_TRADEINFO;

//以下为ATM专用
/*帧格式*/
typedef struct{
	BYTE code[12];		/* 代码 */
}HB_SDVR_FRAMETYPECODE;

typedef struct{
	DWORD dwSize;	
	char sATMIP[16];						/* ATM IP地址 */
	DWORD dwATMType;						/* ATM类型 */
	DWORD dwInputMode;						/* 输入方式	*/	
	DWORD dwFrameSignBeginPos;              /* 报文标志位的起始位置*/
	DWORD dwFrameSignLength;				/* 报文标志位的长度 */
	BYTE  byFrameSignContent[12];			/* 报文标志位的内容 */
	DWORD dwCardLengthInfoBeginPos;			/* 卡号长度信息的起始位置 */
	DWORD dwCardLengthInfoLength;			/* 卡号长度信息的长度 */
	DWORD dwCardNumberInfoBeginPos;			/* 卡号信息的起始位置 */
	DWORD dwCardNumberInfoLength;			/* 卡号信息的长度 */
	DWORD dwBusinessTypeBeginPos;           /* 交易类型的起始位置 */
	DWORD dwBusinessTypeLength;				/* 交易类型的长度 */
	HB_SDVR_FRAMETYPECODE frameTypeCode[10];/* 类型 */
}HB_SDVR_FRAMEFORMAT,*LPHB_SDVR_FRAMEFORMAT;

//武汉网吧 2005-06-29
typedef struct
{
	char sFileName[100];//图片名
	HB_SDVR_TIME struTime;//图片的时间
	DWORD dwFileSize;//图片的大小
	char sCardNum[32];	//卡号
}HB_SDVR_FIND_PICTURE,*LPHB_SDVR_FIND_PICTURE;



/* 控制网络文件回放 */
typedef struct {
	DWORD dwSize;
	char sDecoderIP[16];		/* DVR IP地址 */
	WORD wDecoderPort;			/* 端口号 */
	WORD wLoadMode;				/* 回放下载模式 1－按名字 2－按时间 */
	union
	{
		BYTE byFile[100];		/* 回放的文件名 */
		struct 
		{
			DWORD dwChannel;
			BYTE sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE sPassword[PASSWD_LEN];	/* 密码 */
			HB_SDVR_TIME struStartTime;	/* 按时间回放的开始时间 */
			HB_SDVR_TIME struStopTime;	/* 按时间回放的结束时间 */			
		}bytime;
	}mode_size;
}HB_SDVR_PLAYREMOTEFILE,*LPHB_SDVR_PLAYREMOTEFILE;

/*当前设备解码连接状态*/
typedef struct {
	DWORD dwWorkType;		/*工作方式：1：轮巡、2：动态连接解码、3：按文件回放 4：按时间回放*/
	char sDVRIP[16];		/*连接的设备ip*/
	WORD wDVRPort;			/*连接端口号*/
	BYTE byChannel;					/* 通道号 */
	BYTE byLinkMode;				/* 连接模式 */
	DWORD	dwLinkType;		/*连接类型 0－主码流 1－子码流*/
	union
	{
		struct 
		{
			BYTE sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE sPassword[PASSWD_LEN];	/* 密码 */
			char cReserve[52];
		}userInfo;
		struct 
		{			
			BYTE   fileName[100];		
		}fileInfo;
		struct 
		{
			DWORD	dwChannel;
			BYTE	sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE	sPassword[PASSWD_LEN];	/* 密码 */
			HB_SDVR_TIME struStartTime;		/* 按时间回放的开始时间 */
			HB_SDVR_TIME struStopTime;		/* 按时间回放的结束时间 */	
		}timeInfo;
	}objectInfo;
}HB_SDVR_DECCHANSTATUS, *LPHB_SDVR_DECCHANSTATUS;

typedef struct {
	DWORD   dwSize;
	HB_SDVR_DECCHANSTATUS struDecState[MAX_DECNUM];	
}HB_SDVR_DECSTATUS, *LPHB_SDVR_DECSTATUS;
typedef struct {
	DWORD dwSize;
	HB_SDVR_PORTINFO struTransPortInfo[MAX_TRANSPARENTNUM]; /* 数组0表示485 数组1表示232 */
}HB_SDVR_PORTCFG, *LPHB_SDVR_PORTCFG;	

//自定义云台协议
typedef struct {
 BYTE     CheckSum;//效验码位置
 BYTE     PortNum;//地址码位置
 BYTE     PreSet;//预制点位置
 BYTE     CheckSumMode;//效验码计算模式
 BYTE     KeyLen;//码长度
 BYTE     KeyNum;//发码数
 BYTE     CommandKey[MAX_KEYNUM][24];
}STRUCT_SDVR_DECODERCUSTOMIZE,*LPSTRUCT_SDVR_DECODERCUSTOMIZE;


typedef struct {
	int ptznum;
	char ptztype[MAXPTZNUM][10];
}STRUCT_SDVR_PTZTYPE,*LPSTRUCT_SDVR_PTZTYPE;

typedef struct 
{
	WORD enable;//使能
	WORD time;  //延迟时间
}STRUCT_ALARMIN_WAIT, *LPSTRUCT_ALARMIN_WAIT;


//add by cui for ipc 
typedef struct
{
	BYTE  bVideoOut;		//视频输出
	BYTE  bTemperature;		//温度探测
	BYTE  bVoltage;			//电压探测
	BYTE  bSubStream;		//子码流
	DWORD Rserve1;			//保留
	DWORD Rserve2;			//保留

}STRUCT_SDVR_IPCCONFIG,*LPSTRUCT_SDVR_IPCCONFIG; 


typedef struct
{
	WORD selIndex;
	WORD Rserve;	
}STRUCT_SDVR_IPCPIC,*LPSTRUCT_SDVR_IPCPIC;


typedef struct
{
	WORD selIndex;
	WORD Rserve;	
}STRUCT_SDVR_IPCAGC,*LPSTRUCT_SDVR_IPCAGC;

//add by njt 091026 for ipc
typedef struct
{
    BYTE safeoption;    // 安全选项设置，取值范围[0,2]  0:自动选择  1：开放系统   2：共享密钥
    BYTE pswformat;     // 密钥格式设置，取值范围[0,1]  0：16进制   1：ASCII码
    BYTE pswtype;       // 密 钥 类 型设置，取值范围[0,3]   0：禁用  1：64位  2:128位   3:152位
    BYTE pswword[62];   // 密码，以’\0’结尾，定义62byte是为了与STRUCT_SDVR_IPCWPAPSK等大小。
                        //【备注：密码长度说明，选择64位密钥需输入16进制数字符10个，或者ASCII码字符5个。选择128位密钥需
                        // 输入16进制数字符26个，或者ASCII码字符13个。选择152位密钥需输入16进制数字符32个，或者ASCII
                        // 码字符16个。】
    BYTE reserve[3];	//保留
}STRUCT_SDVR_IPCWEP,*LPSTRUCT_SDVR_IPCWEP;

typedef struct
{
    BYTE safeoption;    // 安全选项设置，取值范围[0,2] 0：自动选择   1：WPA-PSK    2:WPA2-PSK
    BYTE pswmod;        // 加密方法设置,取值范围[0,2]  0：自动选择   1：TKIP   2:AES
    BYTE pawword[64];   // psk密码，8到63个字符，以’\0’结尾
    BYTE reserve[2];	// 保留
}STRUCT_SDVR_IPCWPAPSK,*LPSTRUCT_SDVR_IPCWPAPSK;

typedef struct
{
    DWORD nSecCmdParaSize;        // 建议添加，结构体长度。
    BYTE ssid[50];      // SSID号以’\0’结尾
    BYTE wirelessIP[16];// 无线ip以’\0’结尾
    BYTE safetype;      // 安全类型设置，取值范围[0,2]    0：WEB、1：WPA-PSK/WPA2-PSK、2：无加密
    BYTE reserve[3];	// 保留  	
    union
    {                   // 因为以下两个结构体不可能同时使用，建议用联合体。
        STRUCT_SDVR_IPCWEP ipcwep;      // 安全类型为WEP时参数结构体
        STRUCT_SDVR_IPCWPAPSK ipcwpapsk;// 安全类型为WPA-PSK/WPA2-PSK时参数结构体
    }u;
}STRUCT_SDVR_IPCWIRELESS,*LPSTRUCT_SDVR_IPCWIRELESS;


typedef struct
{
	BYTE channel; //通道号
	short iframerate; //帧间隔
	BYTE Reserve;//保留
	
}STRUCT_SDVR_IFRAMERATE,*LPSTRUCT_SDVR_IFRAMERATE;



typedef struct 
{
    char server[32];		// 服务器
    DWORD port;				// 端口
    DWORD auto_enbale;		// 开启ntp服务,0-表示手动,1-表示自动
    DWORD server_index;		// 服务器索引号
    DWORD sync_period;		// 同步周期，
    DWORD sync_unit;		// 同步周期，0-分钟 1-小时 2-天 3-星期 4-月
    DWORD sync_time;		//保留
	DWORD time_zone;   //时区
    DWORD reserve;			// 保留
}HB_SDVR_NTPCONFIG,*LPHB_SDVR_NTPCONFIG;

typedef struct 
{
    char host[MAX_SMTP_HOST];			//发送邮件的SMTP服务器，例如：126信箱的是smtp.126.com
    DWORD	port;						// 服务器端口，发送邮件(SMTP)端口：默认值25
    char	user[32];					// 邮件用户名
    char	pwd[32];					// 邮件用户密码
    char	send_addr[MAX_SMTP_HOST];	// FROM：邮件地址
    char	recv_addr[MAX_SMTP_ADDR];	// TO：邮件地址，如果是多个邮件地址，以';'隔开
    DWORD send_period;					// 上传周期,单位(分钟)
    DWORD snap_enable;					// 是否抓拍上传
    char	reserve[MAX_STRING];		//
} HB_SDVR_SMTPCONFIG,*LPHB_SDVR_SMTPCONFIG;

typedef struct 
{
	DWORD  poll_type; //轮训类型：0：轮训；1：spot轮巡
    DWORD enable; // 启用？0-禁用，1-启用
    DWORD period; // 轮训间隔，单位秒
    DWORD format; // 画面格式：0-0ff, 1-1, 2-2, 4-2x2, 9-3x3, 16-4x4
    BYTE ch_list[MAX_CHANNUM];//
} HB_SDVR_POLLCONFIG,*LPHB_SDVR_POLLCONFIG;

typedef struct 
{
    DWORD  poll_type; //轮训类型：0：轮训；1：spot轮巡
    DWORD enable; // 启用？0-禁用，1-启用
    DWORD period; // 轮训间隔，单位秒
    DWORD format; // 画面格式：0-0ff, 1-1, 2-2, 4-2x2, 9-3x3, 16-4x4
    BYTE ch_list[MAX_CHANNUM_EX];//
} HB_SDVR_POLLCONFIG128,*LPHB_SDVR_POLLCONFIG128;

typedef struct 
{
    BYTE matrix_channel[MAX_CHANNUM];	// 视频矩阵对应通道 从1开始，0xff表示关闭
    BYTE reserve[32];						// 保留位
}HB_SDVR_VIDEOMATRIX,*LPHB_SDVR_VIDEOMATRIX;

typedef struct 
{
    BYTE matrix_channel[MAX_CHANNUM_EX];	// 视频矩阵对应通道 从1开始，0xff表示关闭
    BYTE reserve[32];						// 保留位
}HB_SDVR_VIDEOMATRIX128,*LPHB_SDVR_VIDEOMATRIX128;


// 系统时间定义
typedef struct {
	unsigned int sec : 6;
	unsigned int min : 6;
	unsigned int hour : 5;
	unsigned int day : 5;
	unsigned int month : 4;
	unsigned int year : 6;
} ASYSTIME, *PASYSTIME;	


/*********************************************************************
//
// 智能
//
********************************************************************/
//一个点的坐标
typedef struct
{
    USHORT	x;          //横坐标
    USHORT	y;          //纵坐标
}PT_ATMI_POINT_S, *PPT_ATMI_POINT_S;

// 客流统计参数
typedef struct PT_HDC_CTRLPARAM_ST
{
    DWORD           dwWidth;            // 处理视频的宽度，默认值352
    DWORD           dwHeight;           // 处理视频高度，默认值288
    DWORD           objWidth;           // 单个目标的宽度，单位为像素，默认值55
    PT_ATMI_POINT_S ptStart;            // 检测线起点，默认值（5,216)
    PT_ATMI_POINT_S ptEnd;              // 检测线终点，默认值(347,216)
    PT_ATMI_POINT_S ptDirection;        // 检测线的方向，默认值(290, 205)
    DWORD           dwPassFrames;       // 初始化的单目标在合成图中的高度，即目标通过检测线的帧数，默认值15
    DWORD           dwMutiObjWidth;     // 三个以上目标并行时矩形框的宽度，默认值110
    DWORD           dwMutiObjWidthEdge; // 与dwMutiObjWidth有关，dwMutiObjWidthEdge = （dwMutiObjWidth / 2 - 5）/ 2，默认值25
    DWORD           dwThreshBackDiff;   // 背景差阀值，默认值50，比较敏感
    DWORD           dwThreshFrameDiff;  // 帧间差阀值，默认值20
    BYTE            byStartPtLabel;     // 起点检测标记，0表示任何目标均计数，1表示小于阀值的目标不计数，默认值为0
    BYTE            byEndPtLable;       // 终点检测标记，0表示任何目标均计数，1表示小于阀值的目标不计数，默认值为0
    BYTE            byReserve[2];      // 保留字段
    DWORD           dwHalfObjW;         // 阀值，与前两项相关，宽度小于该阀值不计数，默认值为20
}PT_HDC_CTRLPARAM, *LPPT_HDC_CTRLPARAM;

/*****************************************************************

以下为四路智能的报警通信结构

*****************************************************************/
//矩形坐标
typedef struct
{
    int left;         //矩形左坐标
    int top;         //矩形上坐标
    int right;      //矩形右坐标
    int bottom;  //矩形下坐标
}PT_ATMI_RECT, *PPT_ATMI_RECT;

//报警类型及位置信息
typedef struct
{
    int alarm_type;         //类型,GUI_ATMI_ALARM_TYPE_E
    PT_ATMI_RECT position;       //坐标位置
}PT_ATMI_ALARM_POSITION_S, *PPT_ATMI_ALARM_POSITION_S;

// 1.人脸通道报警结构体
typedef struct
{
    int alarm_num;                                             //报警个数
    PT_ATMI_ALARM_POSITION_S alarm_area[10];       //报警坐标值,一共有alarm_num个，后面的全为0
}PT_ATMI_FACE_ALARM_S, *PPT_ATMI_FACE_ALARM_S;

// 2.面板通道报警结构体
typedef struct
{
    int alarm_num;                                             //报警个数
    PT_ATMI_ALARM_POSITION_S alarm_area[10];       //报警坐标值,一共有alarm_num个，后面的全为0
}PT_ATMI_PANEL_ALARM_S, *PPT_ATMI_PANEL_ALARM_S;

// 3.加钞间检测输出信息
typedef struct
{
    int type; //是否有人闯入，0表示无，1表示有
}PT_ATMI_MONEY_ALARM_S, *PPT_ATMI_MONEY_ALARM_S;

// 4.环境报警结构体,alarm_num所对应的区域在前，track_num所对应的区域紧跟在alarm_num区域后
typedef struct
{
    int alarm_num;  //报警目标数量
    int track_num;   //跟踪目标数量
    PT_ATMI_ALARM_POSITION_S envi_alarm_region[25];
}PT_ATMI_ENVI_ALARM_S, *PPT_ATMI_ENVI_ALARM_S;

typedef enum
{
    PT_ATMI_FACE_BLOCK = 0,					//人脸遮挡
    PT_ATMI_FACE_NOSIGNAL,					//有脸通道视频丢失
    PT_ATMI_FACE_UNUSUAL,					//人脸异常
    PT_ATMI_FACE_NORMAL,					//人脸正常
    PT_ATMI_PANEL_BLOCK  = 40, 				//面板遮挡
    PT_ATMI_PANEL_NOSIGNAL,					//面板通道视频丢失
    PT_ATMI_PANEL_PASTE,						//贴条
    PT_ATMI_PANEL_KEYBOARD,				//装假键盘
    PT_ATMI_PANEL_KEYMASK,					//破坏密码防护罩	
    PT_ATMI_PANEL_CARDREADER,				//破坏读卡器
    PT_ATMI_PANEL_TMIEOUT,					//超时报警
    PT_ATMI_ENTER,							//有人进入
    PT_ATMI_EXIT,								//人撤离
    PT_ATMI_MONEY_BLOCK = 80,				//加钞间视频遮挡
    PT_ATMI_MONEY_NOSIGNAL,				//加钞间通道视频丢失
    PT_ATMI_MONEY_UNUSUAL,					//加钞间异常,即有人闯入加钞间
    PT_ATMI_ENVI_BLOCK = 120,					//环境通道视频遮挡
    PT_ATMI_ENVI_NOSIGNAL,					//环境通道视频丢失
    PT_ATMI_ENVI_GATHER,						//多人聚集
    PT_ATMI_ENVI_MANYPEOPLEINREGION,		//违规取款
    PT_ATMI_ENVI_LINGERING,					//人员徘徊
    PT_ATMI_ENVI_LIEDOWN,					//人员倒地
    PT_ATMI_ENVI_FORBIDREGION,				//非法进入警戒区
    PT_ATMI_ENVI_LEAVEOBJECT,				//物品遗留
}PT_ATMI_ALARM_TYPE_E;

//报警图片结构体
typedef struct
{
	DWORD pic_alarm_type;                     // PT_ATMI_ALARM_TYPE_E; 
	DWORD pic_format;                         // 图片格式CIF:0  D1:1
	DWORD pic_size;
}PT_ATMI_ALARM_PICINFO_S, *PPT_ATMI_ALARM_PICINFO_S;

typedef enum
{
    HBGK_HDCCOUNT_DIR1 = 0,	//与标记方向相同
    HBGK_HDCCOUNT_DIR2		//与标记方向相反
}PT_HDCCOUNT_DIRECTION_E;

typedef struct PT_HDC_RESULT_ST
{
    DWORD dwResultType;     // 输出结果总类型
    DWORD dwSubType;        // 输出结果子类型，表示人员流动统计的方向见PT_HDCCOUNT_DIRECTION_E
    DWORD dwTrackNum;       // 当前输出统计的ID编号(已统计人数)
    PT_ATMI_RECT    rcPos;  // 当前输出编号的外接矩形框
}PT_HDC_RESULT, *LPPT_HDC_RESULT;

//报警时主机传给客户端的总结构体
typedef struct
{
    // int chn;    //通道号,每次报警后，根据通道号，去读取下面四个结构体中对应的那一个
    BYTE byChn;
    BYTE byReserve1;
    BYTE byInfoType;        // 上传信息类型
                            // 0, PT_ATMI_FACE_ALARM_S
                            // 1, PT_ATMI_PANEL_ALARM_S
                            // 2, PT_ATMI_MONEY_ALARM_S
                            // 3, PT_ATMI_ENVI_ALARM_S
                            // 4, PT_HDC_RESULT
    BYTE byReserve2;

    union
    {
        PT_ATMI_FACE_ALARM_S atmi_face_alarm;           // 1.人脸通道报警结构体
        PT_ATMI_PANEL_ALARM_S atmi_panel_alarm;        // 2.面板通道报警结构体
        PT_ATMI_MONEY_ALARM_S atmi_money_alarm;        // 3.加钞间通道报警结构体
        PT_ATMI_ENVI_ALARM_S atmi_envi_alarm;                // 4.环境通道报警结构体
        PT_HDC_RESULT           hdc;
    }info;

    PT_ATMI_ALARM_PICINFO_S alarm_picinfo;
    ASYSTIME alarmtime;  //报警时间
}PT_ATMI_ALARM_INFO_S, *PPT_ATMI_ALARM_INFO_S;
/*****************************************************************

以下为四路智能的设置或获取的界面结构

*****************************************************************/
//多边形表示结构体，带区域类型
typedef struct
{
    PT_ATMI_POINT_S point[10];  //多边形顶点坐标
    int 	   point_num;    //点的个数
    int      region_type; //区域类型
}PT_ATMI_POLYGON_S, *PPT_ATMI_POLYGON_S;

//矩形区域，带区域类型
typedef struct
{
    PT_ATMI_RECT region;  //矩形区域坐标
    int region_type;   //区域类型
}PT_ATMI_RECT_S, *PPT_ATMI_RECT_S;

//人脸感兴趣区域以及该区域中人脸的大小
typedef struct
{
    PT_ATMI_RECT_S roi;    //坐标
    int min_face; //最小尺寸
    int max_face;//最大尺寸
}PT_ATMI_FACE_ROI_S, *PPT_ATMI_FACE_ROI_S;

// 1.人脸通道中所设置的区域
typedef struct
{
    int num;
    PT_ATMI_FACE_ROI_S face_roi[10];
}PT_ATMI_FACEROI_ALL_S, *PPT_ATMI_FACEROI_ALL_S;

// 2.面板通道中所设置的区域
typedef struct
{
    int num;
    PT_ATMI_POLYGON_S atmi_panel_region[20];
}PT_ATMI_PANEL_REGION_S, *PPT_ATMI_PANEL_REGION_S;

// 3.加钞间通道中所设置的区域及参数
typedef struct
{
    PT_ATMI_POLYGON_S pol_proc_region;	// 处理区域，默认4个点，包含全图
    PT_ATMI_RECT_S no_process[10];	        // 不处理区域
    int no_process_num;		        // 不处理区域个数 (0)
    int warn_interval;	                        // 两次报警时间间隔，(100 秒)
}PT_ATMI_DISTRICTPARA_S, *PPT_ATMI_DISTRICTPARA_S;	

// 4.场景通道中所设置的区域
typedef	struct
{
    PT_ATMI_POLYGON_S pol_proc_region;		// 图像中的处理区域，多边形表示

    /*用于ATM机前尾随取款检测的参数，标识ATM前人站立的区域*/
    PT_ATMI_POLYGON_S tail_region[10];		        // Region in polygon.
    int tail_num;						// Region number. default: 0

    /*用于禁止区域进入报警，标识选定的禁止进入的区域*/
    PT_ATMI_POLYGON_S forbid_region[10];		// Region in polygon.
    int forbid_num;					// Region number.	default: 0

    PT_ATMI_POLYGON_S obj_height;				        // 目标（人）在图像中的高度，默认85
}PT_ATMI_SCENE_COMMONPARA_S, *PPT_ATMI_SCENE_COMMONPARA_S;

// 5.环境通道设置的参数,以下以帧为单位的，我们在界面上做为秒，然后在内部再转化为帧数
typedef struct
{
    /*物品遗留算法相关参数*/
    int objlv_frames_th;				// 物品遗留时间阈值(帧) (30)

    /*人员徘徊算法相关参数*/
    int mv_block_cnt;				        // 移动距离(20，0表示此规则无效)
    SHORT mv_stay_frames;			        // 场景中出现时间阈值(帧),存在总时间(0表示此规则无效)
    SHORT mv_stay_valid_frames;		        // ATM区域停留时间阈值(帧),ATM区域前停留时间(200, 0表示此规则无效)

    /*多人聚集算法相关参数*/
    SHORT gather_cnt;				        // 最多聚集人数(4)
    SHORT gather_interval_frames;			// 报警间隔时间(帧)(1000 frames,约100秒)
    int gather_frame_cnt;				// 多人聚集时间阈值(帧) (100)

    /*人员躺卧算法相关参数*/
    int liedown_frame_cnt;				// 躺卧时间阈值(帧).(20 frames)

    /*尾随取款算法相关参数*/
    SHORT after_frame_cnt;				// 可疑行为时间阈值(帧)(20 frames)
    SHORT after_interval_frames;			// 报警间隔时间(帧)(1000 frames,约100秒)

    /*禁止进入算法相关参数*/
    SHORT forbid_frame_cnt;				// 禁止站立时间阈值(帧)(20 frames)
    SHORT reserve;                                            // 保留
}PT_ATMI_SCENE_WARN_PARAM_S, *PPT_ATMI_SCENE_WARN_PARAM_S;

// 1.人脸通道设置结构体
typedef struct
{
    SHORT face_unusual;                             //是否打开异常人脸（戴口罩、蒙面等）检测功能，1 为打开，0 为关闭。默认为 0  
    SHORT output_oneface;             //设置人脸只输出一次与否，0为否，1为是，默认为1
    int fd_rate;                                      //设置人脸检测跟踪间隔
    PT_ATMI_FACEROI_ALL_S face_roi;  //人脸通道的区域及其它参数
    int abnormalface_alarmtime;      //报警触发时间阀值（秒）
}PT_ATMI_SET_FACE_S, *PPT_ATMI_SET_FACE_S;

//面板告警参数结构体
typedef struct 
{
    int    AlphaVal;                        //检测库alpha值(5) 		
    int    BetaVal;                         //检测库Beta值(3)
    int    MetinThVal;                      //前景融背景阈值(4500)
    int    LBTWTriggerVal;                  //取走遗留报警阈值(75)	

    int    AppearCntThdVal;                 //区域入侵报警基数(40)
    int    AppearCntTriggerVal;             //区域入侵报警阈值(40)
    int    LBTWCntThdVal;                   //取走遗留报警基数(75)		  
    int    LBTWCntTriggerVal;               //取走遗留报警阈值(75)		  

    int    PanelTimeOutTriggerVal;          //超时报警阈值(1500)

    int    OpenLightTriggerVal;             //进变化报警阈值(45)    
    int    CloseLightTriggerVal;            //出变化报警阈值(55)

    DWORD  AppearMinWidth;                  //区域入侵最小目标宽度(10) 	
    DWORD  AppearMinHeight;                 //区域入侵最小目标高度(10)  
    DWORD  AppearMaxWidth;                  //区域入侵最大目标宽度(200)  		
    DWORD  AppearMaxHeight;                 //区域入侵最大目标高度(200) 

    DWORD  LBTWMinWidth;                    //取走遗留最小目标宽度(10) 			  
    DWORD  LBTWMinHeight;                   //取走遗留最小目标高度(10)   
    DWORD  LBTWMaxWidth;                    //取走遗留最大目标宽度(200)  
    DWORD  LBTWMaxHeight;                   //取走遗留最大目标高度(200)
}STRUCT_SDVR_PANELALARMCFG, *PTSTRUCT_SDVR_PANELALARMCFG;


// 2.面板通道设置结构体
typedef struct
{
    int timeout_enable;                          //超时时间
    PT_ATMI_PANEL_REGION_S panel_region; //面板通道区域及其它参数
    STRUCT_SDVR_PANELALARMCFG panel_alarm_param;//面板通道报警设置参数
}PT_ATMI_SET_PANEL_S, *PPT_ATMI_SET_PANEL_S;

// 3.加钞间通道设置结构体
typedef struct
{
    PT_ATMI_DISTRICTPARA_S money_para; //加钞间通道区域及其它参数
}PT_ATMI_SET_MONEY_S, *PPT_ATMI_SET_MONEY_S;

// 4.环境通道设置结构体
typedef struct
{
    PT_ATMI_SCENE_WARN_PARAM_S envi_para; //环境通道参数
    PT_ATMI_SCENE_COMMONPARA_S envi_region;//环境通道区域
}PT_ATMI_SET_ENVI_S, *PPT_ATMI_SET_ENVI_S;

//客户端设置或获取到主机四路智能总的结构体
typedef struct
{
    // int chn;                                      //通道号
    BYTE byChn;                                 // 通道号
    BYTE byReserve1;                           // 保留
    BYTE bySetInfoType;                         // 设置参数类型，
                                                // 0, PT_ATMI_SET_FACE_S;
                                                // 1, PT_ATMI_SET_PANEL_S;
                                                // 2, PT_ATMI_SET_MONEY_S;
                                                // 3, PT_ATMI_SET_ENVI_S;
                                                // 4, PT_HDC_CTRLPARAM;
    BYTE byReserve2;                           // 保留
    
    int chn_attri;                              // 通道属性(人脸、面板、加钞、环境)，目前未用，防止以后用
    SHORT channel_enable;                       // 通道开关，0关闭，1打开
    SHORT if_pic;                               // 是否需要抓取图片
    SHORT enc_type;                             // 抓取图片的格式
    SHORT email_linkage;                        // 联动email
    UINT sensor_num;                            // 探头输出,位表示
    UINT rec_linkage;                           // 联动录像，位表示

    union
    {
        PT_ATMI_SET_FACE_S  face_set_para;      // 人脸通道设置结构体
        PT_ATMI_SET_PANEL_S panel_set_para;     // 面板通道设置结构体
        PT_ATMI_SET_MONEY_S money_set_para;     // 加钞间通道设置结构体
        PT_ATMI_SET_ENVI_S  envi_set_para;      // 环境通道设置结构体
        PT_HDC_CTRLPARAM    hdc;                // 人流统计参数设置
    }setInfo;
}STRUCT_SDVR_INTELLECTCFG;
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// 接口函数定义
//3. 登陆以及返回设备信息
//SDK初始化 
HB_SDVR_API BOOL __stdcall HB_SDVR_Init();

//SDK释放
HB_SDVR_API BOOL __stdcall HB_SDVR_Cleanup();

//报警信息接收窗口
/*
功  能：设置接收两种消息的句柄和方式 （回调或者向线程发消息）  
参  数：
nMessage：COMM_ALARM(报警信息)或COMM_CONNECT(连接状态) 
		hWnd：句柄(可以是窗口，可以是线程句柄，建议使用线程以防止阻塞) 
		返回值：TRUE-成功	FASLE-失败	*/
								
// 注意使用HB_SDVR_SetDVRMessage，HB_SDVR_SetDVRMessage_Nvs时最好不要同时使用，同时使用时注意使用不同的窗口句柄，否则无法区分
// 使用HB_SDVR_SetDVRMessage时请用HB_SDVR_ALARMINFO对LPARAM进行解析
// 使用HB_SDVR_SetDVRMessage_Nvs时请用HB_SDVR_ALARMINFO_EX对LPARAM进行解析
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessage(UINT nMessage,HWND hWnd);
//扩展接口，为了兼容最多128路机器。by cui 10.05.20
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessage_Nvs(UINT nMessage,HWND hWnd);

//设置报警信息回调-基于窗口消息
/*
功  能：设置接收消息的回调函数 （IP区分） 
参  数：
#define COMM_ALARM				0x1100	//报警信息
#define COMM_CONNECT				0x1200	//主机网络断开
fMessCallBack： 消息回调函数
lCommand： 消息的类型 例COMM_ALARM
sDVRIP： ip地址
pBuf：存放信息的缓冲区
dwBufLen：缓冲区的大小
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessCallBack(BOOL (CALLBACK *fMessCallBack)(LONG lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen));
//兼容128路接口
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessCallBack_Nvs(BOOL (CALLBACK *fMessCallBack)(LONG lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen));


//设置报警信息回调-基于线程消息
/*
功  能：设置接收消息的回调函数 （ID区分） 
参  数：
#define COMM_ALARM				0x1100	//报警信息
#define COMM_CONNECT				0x1200	//主机网络断开
fMessCallBack： 消息回调函数
lCommand： 消息的类型 例COMM_ALARM
lUserID ：由HB_SDVR _Login 返回
pBuf：存放信息的缓冲区
dwBufLen：缓冲区的大小
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessCallBack_EX(BOOL (CALLBACK *fMessCallBack_EX)(LONG lCommand,LONG lUserID,char *pBuf,DWORD dwBufLen));
//兼容128路接口
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRMessCallBack_EX_Nvs(BOOL (CALLBACK *fMessCallBack_EX)(LONG lCommand,LONG lUserID,char *pBuf,DWORD dwBufLen));

HB_SDVR_API BOOL __stdcall HB_SDVR_SetDEVMessCallBack(LONG lUserID, BOOL (CALLBACK *fMessCallBack)(LONG lCommand, char* sDVRIP, LONG lUserID,char *pBuf,DWORD dwBufLen, DWORD dwUser), DWORD dwUser);


//设置连接超时时间
//DWORD dwTryTimes保留
HB_SDVR_API BOOL __stdcall HB_SDVR_SetConnectTime(DWORD dwWaitTime,DWORD dwTryTimes);

//SDK版本
HB_SDVR_API DWORD __stdcall HB_SDVR_GetSDKVersion();

//系统是否支持
//返回：成功-0xFF   失败-0
HB_SDVR_API int __stdcall HB_SDVR_IsSupport();





HB_SDVR_API LONG __stdcall HB_SDVR_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPHB_SDVR_DEVICEINFO lpDeviceInfo);
HB_SDVR_API LONG __stdcall HB_SDVR_LoginA(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPHB_SDVR_DEVICEINFO lpDeviceInfo);
HB_SDVR_API LONG __stdcall HB_SDVR_LoginW(TCHAR *sDVRIP,WORD wDVRPort,TCHAR *sUserName,TCHAR *sPassword,LPHB_SDVR_DEVICEINFO lpDeviceInfo);
//为兼容最多128路机器类型的扩展接口 10.05.25
HB_SDVR_API LONG __stdcall HB_SDVR_Login_Nvs(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPHB_SDVR_DEVICEINFO_EX lpDeviceInfo);
/**********************************************************************************
函数名：HB_SDVR_Login_Ex
功  能:登录扩展函数，可以使用户多次登录同一个dvr。
其  他：用法同HB_SDVR_Login
***********************************************************************************/
HB_SDVR_API LONG __stdcall HB_SDVR_Login_Ex(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPHB_SDVR_DEVICEINFO lpDeviceInfo);
//可以使用户多次登录并且兼容最多128路机器类型的扩展接口 10.05.25
HB_SDVR_API LONG __stdcall HB_SDVR_Login_Ex_Nvs(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPHB_SDVR_DEVICEINFO_EX lpDeviceInfo);

//4. 注销
/*
功  能：注销
参  数：
sDVRIP： IP地址用户ID 值，由HB_SDVR _Login 返回
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_Logout(LONG lUserID);


//5. 实时视频
/*
功  能：开启远程视频
参  数：
lDVRIP： IP地址用户ID 值，由NET_DVR_Login 返回
lWindows：通道号
lpClientInfo：指向HB_SDVR_CLIENTINFO结构的指针
返回值：FASLE-失败 ，其他值表示返回视频流的ID值，该ID值是由SDK分配，作为HB_SDVR _StopRealPlay等函数的参数
*/


HB_SDVR_API LONG __stdcall HB_SDVR_RealPlay(LONG lUserID,LONG lWindows,LPHB_SDVR_CLIENTINFO lpClientInfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_UpdataRealPlayWnd(LONG lRealHandle,HWND hPlayWnd);
//6. 关闭视频
/*
功  能：关闭远程视频
参  数：
lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回
返回值：TRUE-成功	FASLE-失败*/

HB_SDVR_API BOOL __stdcall HB_SDVR_StopRealPlay(LONG lRealHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_StopRealPlayEx(LONG lRealHandle);

//7. 视频参数
/*
功  能：调整视频参数
参  数：
lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回
videoeff：指向HB_SDVR_VIDEOEFFECT结构的指针
返回值：TRUE-成功	FASLE-失败*/


HB_SDVR_API BOOL __stdcall HB_SDVR_ClientSetVideoEffect(LONG lRealHandle,LPHB_SDVR_VIDEOEFFECT videoeff);

HB_SDVR_API BOOL __stdcall HB_SDVR_ClientGetVideoEffect(LONG lRealHandle,LPHB_SDVR_VIDEOEFFECT videoeff);
/*参  数：
lUserID： sDVRIP： IP地址用户ID 值，由HB_SDVR _Login 返回
lChannel：通道号
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_ClientSetVideoEffect_Ex(LONG lUserID, LONG lChannel,LPHB_SDVR_VIDEOEFFECT videoeff);
HB_SDVR_API BOOL __stdcall HB_SDVR_ClientGetVideoEffect_Ex(LONG lUserID, LONG lChannel,LPHB_SDVR_VIDEOEFFECT videoeff);


//8. 请求关键帧
/*
功  能：实时视频中产生关键帧
参  数：
lUserID： sDVRIP： IP地址用户ID 值，由HB_SDVR _Login 返回
lChannel：通道号
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_MakeKeyFrame(LONG lUserID, LONG lChannel);

//9. 云台控制(透明云台) 
//功  能：云台控制命令（默认速度）根据视频流ID来控制
//参  数：
//lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回
//dwPTZCommand：控制命令
//#define TM_COM_GUI_BRUSH   0x0001002e   //雨刷
//#define TILT_UP			0x0001000c	/* 云台以SS的速度上仰 */
//#define TILT_DOWN		0x0001000d	/* 云台以SS的速度下俯 */
//#define PAN_LEFT		0x0001000e 	/* 云台以SS的速度左转 */
//#define PAN_RIGHT		0x0001000f	/* 云台以SS的速度右转 */
//#define ZOOM_IN			0x00010016	/* 焦距以速度SS变大(倍率变大) */
//#define ZOOM_OUT		0x00010017 	/* 焦距以速度SS变小(倍率变小) */
//#define IRIS_OPEN		0x00010018 	/* 光圈以速度SS扩大 */
//#define IRIS_CLOSE		0x00010019	/* 光圈以速度SS缩小 */
//#define FOCUS_FAR		0x00010015 	/* 焦点以速度SS后调 */
//#define FOCUS_NEAR		0x00010014  /* 焦点以速度SS前调 */
//#define LIGHT_PWRON		0x00010024	/* 接通灯光电源 */
//#define WIPER_PWRON		0x00010025	/* 接通雨刷开关 */
//#define PAN_AUTO		0x0001001c 	/* 云台以SS的速度左右自动扫描 */
//dwStop：让云台停止还是开始
//返回值：TRUE-成功	FASLE-失败
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZControl(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZControl_Other(LONG lUserID,LONG lChannel,DWORD dwPTZCommand,DWORD dwStop);
//透明云台
HB_SDVR_API BOOL __stdcall HB_SDVR_TransPTZ(LONG lRealHandle,char *pPTZCodeBuf,DWORD dwBufSize);
HB_SDVR_API BOOL __stdcall HB_SDVR_TransPTZ_Other(LONG lUserID,LONG lChannel,char *pPTZCodeBuf,DWORD dwBufSize);

//10.主机控制
//重启
/*
功  能：远程重启主机 
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
返回值： FASLE-失败 TRUE-成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_RebootDVR(LONG lUserID);

//关闭DVR
/*
功  能：远程关闭主机 
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
返回值： FASLE-失败 TRUE-成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_ShutDownDVR(LONG lUserID);
 

//11.升级控制
/*
功  能：远程升级主机 
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
sFileName：升级的文件名及路径
返回值： FASLE-失败  其他返回升级的ID*/
HB_SDVR_API LONG __stdcall HB_SDVR_Upgrade(LONG lUserID,char *sFileName);

/*
功  能：远程升级主机状态 
参  数：
lUpgradeHandle： 升级的ID，由HB_SDVR_Upgrade返回
返回值： FASLE-失败 
其他值：
-1 版本不对，升级失败
100 数据传输完成，等待主机更新  
101 主机更新成功*/
HB_SDVR_API int __stdcall HB_SDVR_GetUpgradeState(LONG lUpgradeHandle);

//升级不允许中断 此接口保留
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseUpgradeHandle(LONG lUpgradeHandle);

//12.对讲操作 
//语音对讲
/*
功  能：开始语音对讲
参  数：
lUserID：NET_DVR_Login ()的返回值
fVoiceDataCallBack：回调函数，回调音频数据
dwUser：用户数据
回调函数说明：
lVoiceComHandle：HB_SDVR_StartVoiceCom ()的返回值
pRecvDataBuffer：存放数据的缓冲区指针
dwBufSize：缓冲区的大小
byAudioFlag：数据类型
0- 客户端采集的音频数据
1- 客户端收到设备端的音频数据
dwUser：用户数据，就是上面输入的用户数据
返回值：-1表示失败，其他值作为HB_SDVR _SetVoiceComClientVolume ()等函数的参数 */
HB_SDVR_API LONG __stdcall HB_SDVR_StartVoiceCom(LONG lUserID, void(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle,char *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,DWORD dwUser), DWORD dwUser);


/*
功  能：设置语音对讲PC 端的音量
参  数：
lVoiceComHandle：HB_SDVR _StartVoiceCom 的返回值
wVolume：设置后的音量，从0-0xffff
返回值：TRUE 表示成功，FALSE 表示失败。*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SetVoiceComClientVolume(LONG lVoiceComHandle,WORD wVolume);

/*
功  能：结束对讲
参  数：
lVoiceComHandle：HB_SDVR _StartVoiceCom 的返回值
返回值：TRUE 表示成功，FALSE 表示失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_StopVoiceCom(LONG lVoiceComHandle);

//开启语音广播
HB_SDVR_API BOOL __stdcall HB_SDVR_ClientAudioStart();
HB_SDVR_API BOOL __stdcall HB_SDVR_ClientAudioStop();
HB_SDVR_API BOOL __stdcall HB_SDVR_AddDVR(LONG lUserID);
HB_SDVR_API BOOL __stdcall HB_SDVR_DelDVR(LONG lUserID);

//13.透明通道
/*//*特别注意 开启485通道的时候一定要在232上channel=2设置一下才可以
功  能：建立透明通道
参  数： 
lUserID：NET_DVR_Login ()的返回值
lSerialPort：串口号，1-232 串口，2-485 串口
dwUser：用户数据
fSerialDataCallBack：回调函数
回调函数说明：
lSerialHandle：NET_DVR_SerialStart()的返回值
pRecvDataBuffer：存放接收到数据的缓冲区指针
dwBufSize：缓冲区的大小
dwUser：上面的用户数据
返回值：-1表示失败，其他值作为HB_SDVR_SerialSend()等函数的参数*/
HB_SDVR_API LONG __stdcall HB_SDVR_SerialStart(LONG lUserID,LONG lSerialPort,void(CALLBACK *fSerialDataCallBack)(LONG lSerialHandle,char *pRecvDataBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);

/*
功  能：通过透明通道向DVR 串口发送数据
参  数：lSerialHandle：NET_DVR_SerialStart 的返回值
lChannel：硬盘录像机的通道号, 以485 建立透明通道时有效,指明往哪个通道送数据,以232 建立透明通道时设置成0;
pSendBuf：要发送的缓冲区的指针
dwBufSize：缓冲区的大小
返回值：TRUE 表示成功，FALSE 表示失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SerialSend(LONG lSerialHandle, LONG lChannel, char *pSendBuf,DWORD dwBufSize);

/*
功能：断开透明通道
参数说明：
lSerialHandle：NET_DVR_SerialStart 的返回值
返回值：TRUE 表示成功，FALSE 表示失败。*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SerialStop(LONG lSerialHandle);
 
//14.网络键盘
/*
功  能：网络键盘
参  数：
lUserID：  用户ID 值，由HB_SDVR _Login 返回
lKeyIndex：键值*/
#define   TM_COM_GUI_LOGIN        0x00010000 //登录
#define   TM_COM_GUI_RECORD       0x00010001 //录像
#define   TM_COM_GUI_PLAYBACK     0x00010002 //回放
#define   TM_COM_GUI_SETUP        0x00010003 //设置
#define   TM_COM_GUI_BACKUP       0x00010004 //备份
#define   TM_COM_GUI_DN           0x00010007 //主机号
#define   TM_COM_GUI_CN           0x00010008 //中文
#define   TM_COM_GUI_BKSPACE      0x0001000b //删除
#define   TM_COM_GUI_UP           0x0001000c //上
#define   TM_COM_GUI_DOWN         0x0001000d //下
#define   TM_COM_GUI_LEFT         0x0001000e //左
#define   TM_COM_GUI_RIGHT        0x0001000f //右
#define   TM_COM_GUI_PAGEUP       0x00010010 //上页
#define   TM_COM_GUI_PAGEDOWN     0x00010011 //下页
#define   TM_COM_GUI_RETURN       0x00010012 //返回
#define   TM_COM_GUI_ENTER        0x00010013 //确认
#define   TM_COM_GUI_NEAR         0x00010014 //摄像头近
#define   TM_COM_GUI_FAR          0x00010015 //摄像头远
#define   TM_COM_GUI_ZOOMIN    0x00010016 //摄像头变焦近（ZOOM+）
#define   TM_COM_GUI_ZOOMOUT   0x00010017 //摄像头变焦远（ZOOM-）
#define   TM_COM_GUI_APER_INC     0x00010018 //摄像头光圈+
#define   TM_COM_GUI_APER_DEC     0x00010019 //摄像头光圈-
#define   TM_COM_GUI_PRESET_SET   0x0001001a //摄像头预置
#define   TM_COM_GUI_PRESET_GET   0x0001001b //摄像头调用
#define   TM_COM_GUI_AUTO         0x0001001c //摄像头自动
#define   TM_COM_GUI_MUTE         0x0001001d //静音
#define   TM_COM_GUI_INFO         0x0001001e //信息
#define   TM_COM_GUI_STEP         0x0001001f //帧进
#define   TM_COM_GUI_PLAY         0x00010020 //播放
#define   TM_COM_GUI_FASTF        0x00010021 //快进
#define   TM_COM_GUI_FASTB        0x00010022 //快退
#define   TM_COM_GUI_CLRALT       0x00010023 //报警清除
#define   TM_COM_GUI_F1           0x00010024
#define   TM_COM_GUI_F2           0x00010025
#define   TM_COM_GUI_IGEFORMAT    0x00010026 //画面格式
#define   TM_COM_GUI_IGESWITCH    0x00010027 //画面轮换
#define   TM_COM_GUI_STOP         0x00010028 
#define   TM_COM_GUI_SHUTDOWN     0x00010029 //关机
#define   TM_COM_GUI_PWDRST       0x0001002a  //密码复位
#define   TM_COM_GUI_F1VGA2TV     0x0001002b  //vga与电视切换
#define   TM_COM_GUI_MOUSESTATUS  0x0001002c //鼠标
#define   TM_COM_GUI_VIDEOPARAM   0x0001002d //视频参数
#define   TM_COM_GUI_DIGIT    0x00011000 //数字（参数为0、1、2、3、 4、5、6、7、8、9）
#define   TM_COM_GUI_CHAR    0x00012000 //字符（参数为A、B、C..X、Y、Z、*、#）
/*
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_ClickKey(LONG lUserID,LONG lKeyIndex);

//15.手动录像
/*
功  能：获取远程手动录像
参  数：
lUserID：   用户ID 值，由HB_SDVR _Login 返回
lChannel：按照低位到高位的顺序表示通道号
lRecordType：保留
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRRecord(LONG lUserID,WORD* lChannel,LONG lRecordType);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRRecord_Nvs(LONG lUserID,LPHB_SDVR_REMOTERECORDCHAN lChannel,LONG lRecordType);

/*
功  能：设置远程手动录像
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lChannel：按照低位到高位的顺序表示通道号
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRRecord(LONG lUserID,WORD  lChannel);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRRecord_Nvs(LONG lUserID,LPHB_SDVR_REMOTERECORDCHAN lChannel);

//16.设备类型
//返回：7004  8004  2004机器型号
 
/*
 typedef struct {
 	ULONG  dvrtype;    //7004  8004  2004机器型号
 	ULONG  nNULL1;         
 	ULONG  nNULL2;
  }HB_SDVR_INFO,*LPHB_SDVR_INFO; */
 

 //超宇版本

HB_SDVR_API BOOL __stdcall  HB_SDVR_GetDeviceType(LONG lUserID,LPHB_SDVR_INFO device);
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetDeviceType(LONG lUserID,LPHB_SDVR_INFO device);
//17.设备硬件信息
//18.设备网络信息
//19.通道参数(包括报警录像,移动录像等)
//20.编码压缩参数
//21.录像参数
//22.解码器参数(云台参数)
//23.报警输入
//24.报警输出
//25.用户权限
//26.DNS
//27.PPPoE
//28.平台信息
//DVR设备参数
//32.报警输出状态




/////////////////////////////////////////////////////////////////////////////////////
/*
功  能：获取远程主机配置
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
dwCommand：命令
HB_SDVR_SET_DEVICECFG:   设备硬件信息
HB_SDVR_SET_NETCFG:		 设备网络信息
HB_SDVR_SET_PICCFG_EX:	 通道参数(包括报警录像,移动录像等)	 
HB_SDVR_SET_COMPRESSCFG: 编码压缩参数
HB_SDVR_SET_RECORDCFG:	 录像参数
HB_SDVR_SET_DECODERCFG:  解码器参数(云台参数)
HB_SDVR_SET_RS232CFG:    RS232
HB_SDVR_SET_ALARMINCFG:	 报警输入
HB_SDVR_SET_ALARMOUTCFG: 报警输出	
HB_SDVR_SET_TIMECFG:     时间
HB_SDVR_SET_USERCFG:	 用户权限
HB_SDVR_SET_DNS:         DNS
HB_SDVR_SET_PPPoE:		 PPPoE	
HB_SDVR_SERVERCFG_SET:   平台信息
lChannel：通道
lpOutBuffer：缓冲区数据
dwInBufferSize：缓冲区数据大小
lpBytesReturned：保留
type：保留
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned,DWORD type);

/*
功  能：远程主机配置
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
dwCommand：命令
HB_SDVR_SET_DEVICECFG:
HB_SDVR_SET_NETCFG:
HB_SDVR_SET_PICCFG_EX:
HB_SDVR_SET_COMPRESSCFG:
HB_SDVR_SET_RECORDCFG:
HB_SDVR_SET_DECODERCFG:
HB_SDVR_SET_RS232CFG:
HB_SDVR_SET_ALARMINCFG:
HB_SDVR_SET_ALARMOUTCFG:
HB_SDVR_SET_TIMECFG:
HB_SDVR_SET_USERCFG:
HB_SDVR_SET_DNS:
HB_SDVR_SET_PPPoE:
HB_SDVR_SERVERCFG_SET:
lChannel：通道
lpInBuffer：缓冲区数据
dwInBufferSize：缓冲区数据大小
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpInBuffer,DWORD dwInBufferSize);

//29.串口信息
//30.远程录像文件查询和点播  下载
/*
功  能：远程文件回放
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lChannel：通道号
dwPTZCommand：控制命令
dwStop：让云台停止还是开始
dwSpeed：速度
返回值：：FALSE 表示失败，其他值作为HB_SDVR _FindClose 等函数的参数*/
HB_SDVR_API LONG __stdcall HB_SDVR_FindFile(LONG lUserID,LONG lChannel,DWORD dwFileType, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);
HB_SDVR_API LONG __stdcall HB_SDVR_FindFile_ByCard(LONG lUserID,char * lpcard,DWORD dwFileType, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);

HB_SDVR_API LONG __stdcall HB_SDVR_FindFileWithChl(LONG lUserID,LONG lChannel,DWORD dwFileType, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);
/*
功  能：获取远程文件的信息
参  数：
lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回 
lpFindData： 指向HB_SDVR_FIND_DATA的结构体的指针
返回值：返回下列值
#define HB_SDVR_FILE_SUCCESS				1000	//获得文件信息
#define HB_SDVR_FILE_NOFIND					1001	//没有文件
#define HB_SDVR_ISFINDING					1002	//正在查找文件
#define	HB_SDVR_NOMOREFILE	 1003	//查找文件时没有更多的文件
#define	HB_SDVR_FILE_EXCEPTION				1004	//查找文件时异常*/
//录像类型

HB_SDVR_API LONG __stdcall HB_SDVR_FindNextFile(LONG lFindHandle,LPHB_SDVR_FIND_DATA lpFindData);
HB_SDVR_API LONG __stdcall HB_SDVR_FindNextFile_ByCard(LONG lFindHandle,LPHB_SDVR_FIND_DATA lpFindData);

/*
功  能：结束获取远程文件的信息
参  数：
lFindHandle： 文件流的ID值，由HB_SDVR_FindFile返回 
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_FindClose(LONG lFindHandle);

/*
功  能：根据文件名回放
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
Channel：通道号
sPlayBackFileName： 要保存的文件名及路径
hWnd：显示的窗口句柄
返回值：FASLE-失败 ，其他值表示返回视频流的ID值，该ID值是由SDK分配 */
HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByName(LONG lUserID,char *sPlayBackFileName, HWND hWnd);

/*
功  能：根据时间段回放
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
Channel：通道号
lpStartTime： 开始时间
lpStopTime：结束时间
hWnd：显示的窗口句柄
返回值：FASLE-失败 ，其他值表示返回视频流的ID值，该ID值是由SDK分配 */

HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByTime(LONG lUserID,LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, HWND hWnd);
//add by cui for feilong 08.12.19
HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByTime_ex(LONG lUserID,LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, HWND hWnd);
//add by xuyao for ATM 2010
HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByTime_Name(LONG lUserID,LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, HWND hWnd, LPVOID pName);

HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByTimeWithChl(LONG lUserID,LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, HWND hWnd);

HB_SDVR_API LONG __stdcall HB_SDVR_PlayBackByTimeWithChl_ex(LONG lUserID,LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, HWND hWnd);
/*
功  能：回放控制
参  数：
lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回 
dwControlCode：控制命令
#define HB_SDVR_PLAYSTART		1//开始播放
#define HB_SDVR_PLAYSTOP		2//停止播放
#define HB_SDVR_PLAYPAUSE		3//暂停播放
#define HB_SDVR_PLAYRESTART		4//恢复播放
#define HB_SDVR_PLAYFAST		5//快放
#define HB_SDVR_PLAYSLOW		6//慢放
#define HB_SDVR_PLAYNORMAL		7//正常速度
#define HB_SDVR_PLAYFRAME		8//单帧放
#define HB_SDVR_PLAYSTARTAUDIO		9//打开声音
#define HB_SDVR_PLAYSTOPAUDIO		10//关闭声音
dwInValue：HB_SDVR_PLAYFAST和HB_SDVR_PLAYSLOW需要速度倍数  范围0-3
lpOutValue：保留
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);



/*
功  能：停止回放 
参  数：
lRealHandle： 视频流的ID值，由HB_SDVR_RealPlay返回 
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_StopPlayBack(LONG lPlayHandle);

/*
功  能：根据文件名备份 
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
sDVRFileName：远程文件的文件名
sSavedFileName：要保存本地的文件名及路径
返回值：FALSE 表示失败，其他值表示返回备份流的ID值，该ID值是由SDK分配*/
HB_SDVR_API LONG __stdcall HB_SDVR_GetFileByName(LONG lUserID,char *sDVRFileName,char *sSavedFileName);

/*
功  能：根据文件名备份 
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
sDVRFileName：远程文件的文件名
sSavedFileName：要保存本地的文件名及路径,如果为空的话,表示下载文件不保存
返回值：FALSE 表示失败，其他值表示返回备份流的ID值，该ID值是由SDK分配*/
HB_SDVR_API LONG __stdcall HB_SDVR_GetFileByName_EX(LONG lUserID,char *sDVRFileName,char *sSavedFileName);

/*
功  能：根据时间段备份
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lChannel：通道号
lpStartTime：开始时间
lpStopTime：结束时间
sSavedFileName：要保存本地的文件名
返回值：FALSE 表示失败，其他值表示返回备份流的ID值，该ID值是由SDK分配*/
HB_SDVR_API LONG __stdcall HB_SDVR_GetFileByTime(LONG lUserID, LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, char *sSavedFileName);

HB_SDVR_API LONG __stdcall HB_SDVR_GetFileByTimeEx(LONG lUserID, LONG lChannel, BYTE byType, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, char *sSavedFileName);

HB_SDVR_API LONG __stdcall HB_SDVR_GetFileByTimeWithChl(LONG lUserID, LONG lChannel, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime, char *sSavedFileName);

typedef enum
{
    HB_SDVR_RECMANUAL = 1,                           // 手动录像
    HB_SDVR_RECSCHEDULE = 2,                         // 定时录像
    HB_SDVR_RECMOTION = 4,                           // 移动侦测录像
    HB_SDVR_RECALARM = 8,                            // 报警录像
    HB_SDVR_REC_ALL = 0xff,                          // 所有录像
}HB_SDVR_RECTYPE_E;


// 使用结构体参数
typedef void (CALLBACK* PHB_SDVR_STREAMDATA_PROC)(long lRealHandle,DWORD dwDataType, 
                                                  BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);

typedef struct ST_HB_SDVR_FILEGETCOND
{
    DWORD               dwSize;
    DWORD               dwChannel;      // 通道号
    HB_SDVR_RECTYPE_E   dwFileType;     // 文件类型
    HB_SDVR_TIME        struStartTime;  // 下载时间段开始时间
    HB_SDVR_TIME        struStopTime;   // 结束时间
    PHB_SDVR_STREAMDATA_PROC    pfnDataProc;
    void*               pContext;
    char*               pSaveFilePath;
    DWORD               dwResever[4];
}HB_SDVR_FILEGETCOND, *LPHB_SDVR_FILEGETCOND;

HB_SDVR_API LONG __stdcall HB_SDVR_GetFile(LONG lUserID, LPHB_SDVR_FILEGETCOND pGetFile);

/*
功  能：停止备份 
参  数：
lFileHandle： 备份流的ID值，由HB_SDVR_GetFileByTime或HB_SDVR_GetFileByName返回 
返回值：TRUE-成功	FASLE-失败*/
HB_SDVR_API BOOL __stdcall HB_SDVR_StopGetFile(LONG lFileHandle);

/*
功  能：备份总的数据大小  
参  数：
lFileHandle： 备份流的ID值，由HB_SDVR_GetFileByTime或HB_SDVR_GetFileByName返回 
返回值： FASLE-失败 其他值为数据量 单位为 K*/
HB_SDVR_API DWORD __stdcall HB_SDVR_GetDownloadTotalSize(LONG lFileHandle);

/*
功  能：备份已经接受的数据量  
参  数：
lFileHandle： 备份流的ID值，由HB_SDVR_GetFileByTime或HB_SDVR_GetFileByName返回 
返回值： FASLE-失败 其他值为数据量 单位为 K*/
HB_SDVR_API int __stdcall HB_SDVR_GetDownloadPos(LONG lFileHandle);

/*
功  能：备份已经接受的数据量  
参  数：
lFileHandle： 备份流的ID值，由HB_SDVR_GetFileByTime或HB_SDVR_GetFileByName返回 
返回值： FASLE-失败 其他值为数据量 单位为 B*/
HB_SDVR_API double __stdcall HB_SDVR_GetDownloadBytesSize(LONG lFileHandle);	//cwh 20080806


//31.远程服务器工作状态
/*
功  能：服务器状态
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lpWorkState：指向HB_SDVR_WORKSTATE的结构体指针
返回值：：FALSE 表示失败，TRUE表示成功*/

/*
功  能：服务器状态
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lpWorkState：指向HB_SDVR_WORKSTATE的结构体指针
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRWorkState(LONG lUserID,LPHB_SDVR_WORKSTATE lpWorkState);
//兼容最多128路的扩展接口
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRWorkState_Nvs(LONG lUserID,LPHB_SDVR_WORKSTATE_EX lpWorkState);


//33.日志
/*
功  能：查询日志
参  数：
lUserID：  IP地址用户ID 值，由HB_SDVR _Login 返回
lpStartTime：开始时间
lpStopTime：结束时间
返回值：：FALSE 表示失败，其他返回日志ID号
*/
HB_SDVR_API LONG __stdcall HB_SDVR_FindDVRLog(LONG lUserID, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);

/*
功  能：下一条日志
参  数：
lLogHandle：   日志ID 值，由HB_SDVR_FindDVRLog返回
lpLogData：一条日志信息
nlanguage:语言 0：中文，1：英文。
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API LONG __stdcall HB_SDVR_FindNextLog(LONG lLogHandle,char *lpLogData,int nlanguage = 0);

/*
功  能：结束日至查找
参  数：
lLogHandle：   日志ID 值，由HB_SDVR_FindDVRLog返回
返回值：：FALSE 表示失败，TRUE表示成功*/
HB_SDVR_API BOOL __stdcall HB_SDVR_FindLogClose(LONG lLogHandle);



//34.N/P制切换
//#define   NET_SDVR_SET_PRESETPOLL   0x73
//#define   NET_SDVR_GET_PRESETPOLL   0x74



HB_SDVR_API BOOL __stdcall  HB_SDVR_GET_PRESETPOLL (LONG lUserID,  LPHB_SDVR_PRESETPOLL presetpoll);
HB_SDVR_API BOOL __stdcall  HB_SDVR_SET_PRESETPOLL  (LONG lUserID, LPHB_SDVR_PRESETPOLL presetpoll);
						

//35.多预置点轮巡
//#define   NET_SDVR_SET_VIDEOSYS       0x75
//#define   NET_SDVR_GET_VIDEOSYS       0x76
//只用一个字节代表视频制式值，1---PAL，2---NTSC4.43  3--NTSC3.58

HB_SDVR_API BOOL __stdcall  HB_SDVR_GET_VIDEOSYS  (LONG lUserID,BYTE* videosys);
HB_SDVR_API BOOL __stdcall  HB_SDVR_SET_VIDEOSYS  (LONG lUserID,BYTE videosys);





//其他

//刷新主机保存配置
HB_SDVR_API BOOL __stdcall HB_SDVR_REFRESH_FLASH(LONG lUserID);

//开启声音
HB_SDVR_API BOOL __stdcall HB_SDVR_OpenSound(LONG lRealHandle);

//关闭声音
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseSound();

//开启声音
HB_SDVR_API BOOL __stdcall HB_SDVR_OpenSoundShare(LONG lRealHandle);

//关闭声音
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseSoundShare(LONG lRealHandle);

//设置音量 
HB_SDVR_API BOOL __stdcall HB_SDVR_Volume(LONG lRealHandle,WORD wVolume);

//本地录像
HB_SDVR_API BOOL __stdcall HB_SDVR_SaveRealData(LONG lRealHandle,char *sFileName);

//停止本地录像
HB_SDVR_API BOOL __stdcall HB_SDVR_StopSaveRealData(LONG lRealHandle);

//设置实时流数据回调
HB_SDVR_API BOOL __stdcall HB_SDVR_SetRealDataCallBack(LONG lRealHandle,void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);

//设置实时原始数据带帧信息回调
HB_SDVR_API BOOL __stdcall HB_SDVR_SetRealDataCallBack_Ex(LONG lRealHandle,void(CALLBACK *fRealDataCallBack) (LONG lRealHandle,  PFRAMEINFO pFarmeInfo, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
//抓图
HB_SDVR_API BOOL __stdcall HB_SDVR_CapturePicture(LONG lRealHandle,char *sPicFileName);

//不解码
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetDecMode(BOOL bSDKDec ); //全局，在7000SDK中，不使用内部解码函数

//报警清除
HB_SDVR_API BOOL __stdcall  HB_SDVR_ClearAlarm(LONG lUserID);

//设置获取序列号
HB_SDVR_API BOOL __stdcall  HB_SDVR_GetSEQ(LONG lUserID,char *buff,DWORD dwBufSize);
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetSEQ(LONG lUserID,char *buff,DWORD dwBufSize);

//视频丢失状态  按位
HB_SDVR_API USHORT __stdcall  HB_SDVR_GET_VideoLostStatus(LONG lUserID );
//兼容最多128路类型机器 add by cui for 7024 or nvs 100325
HB_SDVR_API BOOL   __stdcall  HB_SDVR_GET_VideoLostStatus_Nvs(LONG lUserID ,LPHB_SDVR_VODLOST lpVodLost);

HB_SDVR_API BOOL __stdcall HB_SDVR_SetDownDataCallBack(LONG lFileHandle,void(CALLBACK *fRealDataCallBack) (LONG lFileHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);

HB_SDVR_API BOOL __stdcall  HB_SDVR_GetPicFromDVR(LONG lUserID,USHORT channel,char *sPicFileName);

HB_SDVR_API BOOL __stdcall  HB_SDVR_GetDelayPicFromDVR(LONG lUserID,USHORT channel,char *sPicFileName);

HB_SDVR_API BOOL __stdcall  HB_SDVR_RegisterDrawDCFun(long lRealHandle,void (CALLBACK* DrawDCFun)(long nChl,HDC hDc,long nReserved),long nReserved);

//回调时指定输出格式
#define SDVR_OUT_FMT_YUV_420 0x00000601                  // YUV_420
#define SDVR_OUT_FMT_YUV_422 0x00000102                  // YUV_422

//解码后回调 获取解码后数据和时间，帧
typedef HB_FRAME_INFO FRAME_INFO;
//实时数据回调  解码后的数据 帧信息包括时间
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetRealDecCallBack(LONG lRealHandle,void(CALLBACK *DecCBFun) (long nChl, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2, long dwUser),long nOutFormat,long dwUser);

//点播数据回调
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetPlayDecCallBack(LONG lRealHandle,void(CALLBACK *DecCBFun) (long nChl, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2, long dwUser),long nOutFormat,long dwUser);
typedef HB_VIDEO_TIME VIDEO_TIME;
//原始数据流 分帧 且包含帧信息
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetParseCallBack(LONG lRealHandle,void (CALLBACK* SrcDataParseCBFun)(long nChl,char *SrcDataBuf,long nSize,long nFrameType,VIDEO_TIME ets,long user),long nRseserved);

HB_SDVR_API BOOL __stdcall  HB_SDVR_SetParseCallBack_Ex(LONG lRealHandle,void (CALLBACK* SrcDataParseCBFun)(long nChl, const HB_FRAME* pFrame, LPVOID pContext ),long dwUser);
 //下载回调
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetDownloadCallBack(LONG lFileHandle,void (CALLBACK* SrcDataParseCBFun)(long nChl,char *SrcDataBuf,long nSize,long nFrameType, VIDEO_TIME ets,long user),long nReserved1);

HB_SDVR_API BOOL __stdcall  HB_SDVR_SetDownloadCallBackEx(LONG lFileHandle,void (CALLBACK* SrcDataParseCBFun)(long nChl, const HB_FRAME* pFrame, LPVOID pContext ),long dwUser);


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*后面接口保留   20080702
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HB_SDVR_API BOOL __stdcall HB_SDVR_RegisterDrawFun(LONG lRealHandle,void (CALLBACK* fDrawFun)(LONG lRealHandle,HDC hDc,LONG dwUser),DWORD dwUser);
HB_SDVR_API BOOL __stdcall HB_SDVR_RigisterDrawFun(LONG lRealHandle,void (CALLBACK* fDrawFun)(LONG lRealHandle,HDC hDc,LONG dwUser),DWORD dwUser);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetPlayerBufNumber(LONG lRealHandle,DWORD dwBufNum);
HB_SDVR_API BOOL __stdcall HB_SDVR_ThrowBFrame(LONG lRealHandle,DWORD dwNum);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetAudioMode(DWORD dwMode);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZPreset(LONG lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZPreset_Other(LONG lUserID,LONG lChannel,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
HB_SDVR_API BOOL __stdcall HB_SDVR_TransPTZ_EX(LONG lRealHandle,char *pPTZCodeBuf,DWORD dwBufSize);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZControl_EX(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZPreset_EX(LONG lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZCruise(LONG lRealHandle,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZCruise_Other(LONG lUserID,LONG lChannel,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZCruise_EX(LONG lRealHandle,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZTrack(LONG lRealHandle,DWORD dwPTZTrackCmd);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZTrack_Other(LONG lUserID,LONG lChannel,DWORD dwPTZTrackCmd);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZTrack_EX(LONG lRealHandle,DWORD dwPTZTrackCmd);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetPlayDataCallBack(LONG lPlayHandle,void(CALLBACK *fPlayDataCallBack) (LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
HB_SDVR_API BOOL __stdcall HB_SDVR_PlayBackSaveData(LONG lPlayHandle,char *sFileName);
HB_SDVR_API BOOL __stdcall HB_SDVR_StopPlayBackSave(LONG lPlayHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetPlayBackOsdTime(LONG lPlayHandle, LPHB_SDVR_TIME lpOsdTime);
HB_SDVR_API DWORD __stdcall HB_SDVR_GetPlayBackDTS(LONG lPlayHandle);  //返回当前帧的DTS时间
HB_SDVR_API BOOL __stdcall HB_SDVR_PlayBackCaptureFile(LONG lPlayHandle,char *sFileName);
HB_SDVR_API BOOL __stdcall HB_SDVR_RestoreConfig(LONG lUserID);
HB_SDVR_API BOOL __stdcall HB_SDVR_SaveConfig(LONG lUserID);
HB_SDVR_API LONG __stdcall HB_SDVR_FormatDisk(LONG lUserID,LONG lDiskNumber);
// LONG *pCurrentFormatDisk,正在格式化的硬盘号[0, 15]
// LONG *pCurrentDiskPos,正在格式化的硬盘进度[0, 100]
// LONG *pFormatStatic,格式化状态 0，正在格式化；1，格式化完成；2，格式化错误；3，要格式化的硬盘不存在；4格式化中途错误；5，磁盘正在被使用
HB_SDVR_API BOOL __stdcall HB_SDVR_GetFormatProgress(LONG lFormatHandle,LONG *pCurrentFormatDisk,LONG *pCurrentDiskPos,LONG *pFormatStatic);
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseFormatHandle(LONG lFormatHandle);
HB_SDVR_API LONG __stdcall HB_SDVR_SetupAlarmChan(LONG lUserID);
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseAlarmChan(LONG lAlarmHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetAlarmOut(LONG lUserID,LPHB_SDVR_ALARMOUTSTATUS lpAlarmOutState);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetAlarmOut(LONG lUserID,LONG lAlarmOutPort,LONG lAlarmOutStatic);
HB_SDVR_API void* __stdcall HB_SDVR_InitG722Decoder(int nBitrate);
HB_SDVR_API void __stdcall HB_SDVR_ReleaseG722Decoder(void *pDecHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_DecodeG722Frame(void *pDecHandle, unsigned char* pInBuffer, unsigned char* pOutBuffer);
HB_SDVR_API void* __stdcall HB_SDVR_InitG722Encoder();
HB_SDVR_API BOOL __stdcall HB_SDVR_EncodeG722Frame(void *pEncodeHandle,unsigned char* pInBuffer, unsigned char* pOutBuffer);
HB_SDVR_API void __stdcall HB_SDVR_ReleaseG722Encoder(void *pEncodeHandle);

// 该两函数没有实现，与HB_SDVR_ClientSetVideoEffect/HB_SDVR_ClientGetVideoEffect有何区别？
// HB_SDVR_API BOOL __stdcall HB_SDVR_SetVideoEffect(LONG lUserID,LONG lChannel,DWORD dwBrightValue,DWORD dwContrastValue, DWORD dwSaturationValue,DWORD dwHueValue);
// HB_SDVR_API BOOL __stdcall HB_SDVR_GetVideoEffect(LONG lUserID,LONG lChannel,DWORD *pBrightValue,DWORD *pContrastValue, DWORD *pSaturationValue,DWORD *pHueValue);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZControlWithSpeed(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, DWORD dwSpeed);
HB_SDVR_API BOOL __stdcall HB_SDVR_PTZControlWithSpeed_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCommand, DWORD dwStop, DWORD dwSpeed);
HB_SDVR_API DWORD __stdcall HB_SDVR_GetLastError();

///////////////////////////////////////////////////////////////////////////////////////////////////
 

HB_SDVR_API BOOL __stdcall HB_SDVR_InitDevice_Card(long *pDeviceTotalChan);
HB_SDVR_API BOOL __stdcall HB_SDVR_ReleaseDevice_Card();
HB_SDVR_API BOOL __stdcall HB_SDVR_InitDDraw_Card(HWND hParent,COLORREF colorKey);
HB_SDVR_API BOOL __stdcall HB_SDVR_ReleaseDDraw_Card();
HB_SDVR_API LONG __stdcall HB_SDVR_RealPlay_Card(LONG lUserID,LPHB_SDVR_CARDINFO lpCardInfo,long lChannelNum);
HB_SDVR_API BOOL __stdcall HB_SDVR_ResetPara_Card(LONG lRealHandle,LPHB_SDVR_DISPLAY_PARA lpDisplayPara);
HB_SDVR_API BOOL __stdcall HB_SDVR_RefreshSurface_Card();
HB_SDVR_API BOOL __stdcall HB_SDVR_ClearSurface_Card();
HB_SDVR_API BOOL __stdcall HB_SDVR_RestoreSurface_Card();
HB_SDVR_API BOOL __stdcall HB_SDVR_OpenSound_Card(LONG lRealHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_CloseSound_Card(LONG lRealHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetVolume_Card(LONG lRealHandle,WORD wVolume);
HB_SDVR_API BOOL __stdcall HB_SDVR_AudioPreview_Card(LONG lRealHandle,BOOL bEnable);
HB_SDVR_API BOOL __stdcall HB_SDVR_CapturePicture_Card(LONG lRealHandle, char *sPicFileName);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDspErrMsg_Card(UINT nMessage,HWND hWnd);
HB_SDVR_API BOOL __stdcall HB_SDVR_ResetDSP_Card(long lChannelNum);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetSerialNum_Card(long lChannelNum,DWORD *pDeviceSerialNo);
HB_SDVR_API HANDLE __stdcall HB_SDVR_GetChanHandle_Card(LONG lRealHandle);

HB_SDVR_API BOOL __stdcall HB_SDVR_CaptureJPEGPicture(LONG lUserID, LONG lChannel, LPHB_SDVR_JPEGPARA lpJpegPara, char *sPicFileName);

// HB_SDVR_API BOOL __stdcall HB_SDVR_StopPPPoE(LONG lUserID);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetConfigFile(LONG lUserID, char *sFileName);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetConfigFile(LONG lUserID, char *sFileName);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetConfigFile_EX(LONG lUserID, char *sOutBuffer, DWORD dwOutSize);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetConfigFile_EX(LONG lUserID, char *sInBuffer, DWORD dwInSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_SetTrainInfo(LONG lUserID,LPVOID lpTrainInfoBuf,DWORD dwTrainInfolen);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetTrainInfo(LONG lUserID,LPVOID lpTainOutInfoBuf,DWORD dwTrainOutInfolen, LPDWORD lpBytesReturned);
HB_SDVR_API LONG __stdcall HB_SDVR_FindFileByTrainRunFlag(LONG lUserID, LONG lChannel, DWORD dwFileType, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);
// HB_SDVR_API LONG __stdcall HB_SDVR_FindPicture(LONG lUserID,LONG lChannel,DWORD dwFileType, BOOL bNeedCardNum, BYTE *sCardNumber, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);
// HB_SDVR_API LONG __stdcall HB_SDVR_FindNextPicture(LONG lFindHandle,LPHB_SDVR_FIND_PICTURE lpFindData);
// HB_SDVR_API BOOL __stdcall HB_SDVR_CloseFindPicture(LONG lFindHandle);
// HB_SDVR_API BOOL __stdcall HB_SDVR_GetPicture(LONG lUserID,char *sDVRFileName,char *sSavedFileName);

HB_SDVR_API BOOL __stdcall HB_SDVR_SetOEMInfo(LONG lUserID,LPVOID lpOEMInfoBuf,DWORD dwOEMInfolen);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetOEMInfo(LONG lUserID,LPVOID lpOEMOutInfoBuf,DWORD dwOEMOutInfolen, LPDWORD lpBytesReturned);


 
HB_SDVR_API LONG __stdcall HB_SDVR_StartVoiceCom_MR(LONG lUserID, void(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle,char *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,DWORD dwUser), DWORD dwUser);
HB_SDVR_API BOOL __stdcall HB_SDVR_VoiceComSendData(LONG lVoiceComHandle,char *pSendBuf,DWORD dwBufSize);

 
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDecInfo(LONG lUserID, LONG lChannel, LPHB_SDVR_DECCFG lpDecoderinfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDecInfo(LONG lUserID, LONG lChannel, LPHB_SDVR_DECCFG lpDecoderinfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDecTransPort(LONG lUserID, LPHB_SDVR_PORTCFG lpTransPort);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDecTransPort(LONG lUserID, LPHB_SDVR_PORTCFG lpTransPort); 
HB_SDVR_API BOOL __stdcall HB_SDVR_DecPlayBackCtrl(LONG lUserID, LONG lChannel, DWORD dwControlCode, DWORD dwInValue,DWORD *lpOutValue, LPHB_SDVR_PLAYREMOTEFILE lpRemoteFileInfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_StartDecSpecialCon(LONG lUserID, LONG lChannel, LPHB_SDVR_DECCHANINFO lpDecChanInfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_StopDecSpecialCon(LONG lUserID, LONG lChannel, LPHB_SDVR_DECCHANINFO lpDecChanInfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_DecCtrlDec(LONG lUserID, LONG lChannel, DWORD dwControlCode);
HB_SDVR_API BOOL __stdcall HB_SDVR_DecCtrlScreen(LONG lUserID, LONG lChannel, DWORD dwControl);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDecCurLinkStatus(LONG lUserID, LONG lChannel, LPHB_SDVR_DECSTATUS lpDecStatus);

HB_SDVR_API BOOL __stdcall HB_SDVR_ClientGetframeformat(LONG lUserID, LPHB_SDVR_FRAMEFORMAT lpFrameFormat);
HB_SDVR_API BOOL __stdcall HB_SDVR_ClientSetframeformat(LONG lUserID, LPHB_SDVR_FRAMEFORMAT lpFrameFormat);
HB_SDVR_API LONG __stdcall HB_SDVR_FindFileByCard(LONG lUserID,LONG lChannel,DWORD dwFileType, BOOL bNeedCardNum, BYTE *sCardNumber, LPHB_SDVR_TIME lpStartTime, LPHB_SDVR_TIME lpStopTime);


HB_SDVR_API BOOL __stdcall HB_SDVR_StartListen(char *sLocalIP,WORD wLocalPort);
HB_SDVR_API BOOL __stdcall HB_SDVR_StopListen();

HB_SDVR_API BOOL __stdcall HB_SDVR_SetShowMode(DWORD dwShowType,COLORREF colorKey);
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDVRIPByResolveSvr(char *sServerIP, WORD wServerPort, BYTE *sDVRName,WORD wDVRNameLen,BYTE *sDVRSerialNumber,WORD wDVRSerialLen,char* sGetIP);

HB_SDVR_API BOOL __stdcall HB_SDVR_RealPlayPause(LONG lRealHandle);
HB_SDVR_API BOOL __stdcall HB_SDVR_RealPlayRestart(LONG lRealHandle, HWND hPlayWnd);
HB_SDVR_API BOOL __stdcall HB_SDVR_SendTo232Port(LONG lUserID,char *pSendBuf,DWORD dwBufSize);

HB_SDVR_API BOOL __stdcall  HB_SDVR_GET_PRESETPOLL (LONG lUserID,  LPHB_SDVR_PRESETPOLL presetpoll) ;
HB_SDVR_API BOOL __stdcall  HB_SDVR_SET_PRESETPOLL  (LONG lUserID, LPHB_SDVR_PRESETPOLL presetpoll) ;
HB_SDVR_API BOOL __stdcall  HB_SDVR_GET_VIDEOSYS  (LONG lUserID,BYTE* videosys) ;
HB_SDVR_API BOOL __stdcall  HB_SDVR_SET_VIDEOSYS  (LONG lUserID,BYTE  videosys) ;
HB_SDVR_API BOOL __stdcall  HB_SDVR_RegisterEndPlayCallback
(void (CALLBACK* endplayCallBk)(DWORD playwnd,long nReserved1, long nReserved2),long nReserved);

//add by cui 09.01.05
/*
	功能：画面的局部放大。
	输入：lPlayHandle 播放句柄，nRegionNum 显示的区域号（传入1—3），pSrcRect 要放大的区域，
			hdestWnd 显示视频的窗口句柄，bEnable 1显示 0不显示。
*/
HB_SDVR_API	BOOL __stdcall HB_SDVR_SetDisplayRegion(LONG lPlayHandle,DWORD nRegionNum,RECT *pSrcRect,HWND hdestWnd,BOOL bEnable);
//add by cui 09.05.15
HB_SDVR_API	BOOL __stdcall	HB_SDVR_GetPictureSize(LONG lPlayHandle, long *pWidth, long *pHeight);

HB_SDVR_API	BOOL __stdcall HB_SDVR_SetPicQuality(LONG lPlayHandle,BOOL bHighQuality);
HB_SDVR_API	BOOL __stdcall HB_SDVR_GetPicQuality(LONG lPlayHandle,BOOL *bHighQuality);



HB_SDVR_API BOOL __stdcall HB_SDVR_SetPTZProtocol(LONG lUserID,
												  LPSTRUCT_SDVR_DECODERCUSTOMIZE lpStructPtzProtocol,
												  LONG lSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetPTZProtocol(LONG lUserID,
												  LPSTRUCT_SDVR_DECODERCUSTOMIZE lpStructPtzProtocol,
												  LONG lSize);
//恢复DVR缺省参数设置
//nType: 0:部分缺省;1:所有缺省.
//cwh 20090318
HB_SDVR_API BOOL __stdcall  HB_SDVR_RecoverDefault(LONG lUserID,BYTE nType);



HB_SDVR_API BOOL __stdcall HB_SDVR_GetPTZType(LONG lUserID,
												  LPSTRUCT_SDVR_PTZTYPE lpStructPtzType,
												  LONG lSize);



//延时布防 //add by cwh 20090803
/**********************************************************
参数：
	lUserID：登陆ID
	struParam：STRUCT_ALARMIN_WAIT结构体
返回值：
	TRUE：成功；
	FALSE：失败。
***********************************************************/
HB_SDVR_API BOOL __stdcall  HB_SDVR_SetDelayDefence(LONG lUserID,STRUCT_ALARMIN_WAIT struParam);

//获取布防状态 //add by cwh 20090810
/**********************************************************
参数：
	lUserID：登陆ID
	struParam：STRUCT_ALARMIN_WAIT结构体
返回值：
	TRUE：成功；
	FALSE：失败。
***********************************************************/
HB_SDVR_API BOOL __stdcall  HB_SDVR_GetDelayDefence(LONG lUserID,LPSTRUCT_ALARMIN_WAIT pStruParam);

/*
功能：获取IPC参数
结构体：STRUCT_SDVR_IPCCONFIG
参数：登录id lUserID 
返回值：成功ture 失败false
*/

HB_SDVR_API BOOL __stdcall HB_SDVR_GetIpcConfig(LONG lUserID,LPSTRUCT_SDVR_IPCCONFIG pStruIpcParam);
/*
功能：设置IPC参数
结构体：STRUCT_SDVR_IPCCONFIG
参数：登录id lUserID 
返回值：成功ture 失败false
*/

HB_SDVR_API BOOL __stdcall HB_SDVR_SetIpcConfig(LONG lUserID,LPSTRUCT_SDVR_IPCCONFIG pStruIpcParam);
/*
功能：设置IPC快门
参数：登录id lUserID 
返回值：成功ture 失败false
*/


HB_SDVR_API BOOL __stdcall HB_SDVR_GetIpcPicConfig(LONG lUserID,LPSTRUCT_SDVR_IPCPIC pStruIpcPic);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetIpcPicConfig(LONG lUserID,LPSTRUCT_SDVR_IPCPIC pStruIpcPic);
/*
功能：设置IPCAGC
参数：登录id lUserID 
返回值：成功ture 失败false
*/


HB_SDVR_API BOOL __stdcall HB_SDVR_GetIpcAgcConfig(LONG lUserID,LPSTRUCT_SDVR_IPCAGC pStruIpcAgc);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetIpcAgcConfig(LONG lUserID,LPSTRUCT_SDVR_IPCAGC pStruIpcAgc);


/*
功能：设置IPC无线参数设置
STRUCT_SDVR_IPCWIRELESS
参数： 
返回值：成功ture 失败false
*/
 
HB_SDVR_API	BOOL __stdcall HB_SDVR_SetIPCWirelessSet(LONG lUserID, LPSTRUCT_SDVR_IPCWIRELESS pStruIpcWireless);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetIPCWirelessSet(LONG lUserID,LPSTRUCT_SDVR_IPCWIRELESS pStruIpcWireless);
// 老7000sdk接口！神马玩意
HB_SDVR_API BOOL __stdcall HB_SDVR_SetIPCWirelessGet(LONG lUserID,LPSTRUCT_SDVR_IPCWIRELESS pStruIpcWireless);
/*********************************************************************************
add by cui 09.10.09
功能：设置ouerlay模式。
参数: bOverlayMode[In] : 为TRUE 表示采用Overlay 模式, 如果创建Overlay
		平面失败,将自动采用其它显示模式.
		colorKey [In] : 要采用的透明色. 透明色相当于一层透视膜，显示的
		画面只能穿过这种颜色，而其他的颜色将挡住显示的画面.用户应该在显示窗口
		中涂上这种颜色，那样才能看到显示画面.一般应该使用一种不常用的颜色作为
		透明色.这是一个DWORD 值:0x00rrggbb,最高字节为0，后三个字节分别表示
		r,g,b 的值.

*********************************************************************************/
HB_SDVR_API	BOOL __stdcall HB_SDVR_SetOverlayMode(LONG lPlayHandle, BOOL bOverlayMode, COLORREF colorKey);
//add by njt for 泰晨
/*
功能：获取底层UserID
参数：
   lUserID ：由HB_SDVR_Login返回
返回值：
    成功:返回底层UserID
	失败:返回false
*/
HB_SDVR_API LONG __stdcall HB_SDVR_GetUserID(LONG lUserID);
/*ADD by njt
 功能： 设置7000T的帧间隔
 参数： lUserID ：登录id 
       iFrameRate为STRUCT_SDVR_IFRAMERATE结构体
 */


HB_SDVR_API BOOL __stdcall  HB_SDVR_SetIFrameRate(LONG lUserID,LPSTRUCT_SDVR_IFRAMERATE pStruiFrameRate);
HB_SDVR_API BOOL __stdcall  HB_SDVR_GetIFrameRate(LONG lUserID, LONG lChannel, LPSTRUCT_SDVR_IFRAMERATE pStruiFrameRate);
HB_SDVR_API VOID __stdcall HB_SDVR_SendAudio(char *pAuidoBuffer,int length);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////以下是8000TH新添加的协议接口////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
//add by cuigc for 8000TH 100401
功能：8000TH  NTP配置参数的设置和查询。
参数: lUserID 用户ID，用户登录时返回的。pStruNtpPara NTP配置参数。
返回：true 成功   false 失败。
*********************************************************************************/


HB_SDVR_API BOOL __stdcall  HB_SDVR_NTPConfigSet(LONG lUserID,LPHB_SDVR_NTPCONFIG pStruNtpPara);
HB_SDVR_API BOOL __stdcall  HB_SDVR_NTPConfigGet(LONG lUserID,LPHB_SDVR_NTPCONFIG pStruNtpPara);

/*********************************************************************************
//add by cuigc for 8000TH 100401
功能：8000TH 邮件服务参数的设置和查询。
参数: lUserID 用户ID，用户登录时返回的。pStruSmtpPara 邮件服务配置参数。
返回：true 成功   false 失败。
*********************************************************************************/



HB_SDVR_API BOOL __stdcall  HB_SDVR_SMTPConfigSet(LONG lUserID,LPHB_SDVR_SMTPCONFIG pStruSmtpPara);
HB_SDVR_API BOOL __stdcall  HB_SDVR_SMTPConfigGet(LONG lUserID,LPHB_SDVR_SMTPCONFIG pStruSmtpPara);

/*********************************************************************************
//add by cuigc for 8000TH 100401
功能：8000TH 轮巡配置参数的设置和查询。
参数: lUserID 用户ID，用户登录时返回的。pStruPollPara 轮巡配置参数。
返回：true 成功   false 失败。
*********************************************************************************/



HB_SDVR_API BOOL __stdcall  HB_SDVR_PollConfigSet(LONG lUserID,LPHB_SDVR_POLLCONFIG pStruPollPara);
HB_SDVR_API BOOL __stdcall  HB_SDVR_PollConfigGet(LONG lUserID,LPHB_SDVR_POLLCONFIG pStruPollPara);

HB_SDVR_API BOOL __stdcall  HB_SDVR_SetPollConfig(LONG lUserID, LPVOID lpBuf, DWORD dwSize);
HB_SDVR_API BOOL __stdcall  HB_SDVR_GetPollConfig(LONG lUserID, LPVOID lpBuf, DWORD* pSize);

/*********************************************************************************
//add by cuigc for 8000TH 100401
功能：8000TH 视频矩阵参数的设置和查询。
参数: lUserID 用户ID，用户登录时返回的。pStruVideoMatrixPara 视频矩阵配置参数。
返回：true 成功   false 失败。
*********************************************************************************/




HB_SDVR_API BOOL __stdcall  HB_SDVR_VideoMatrixSet(LONG lUserID,LPHB_SDVR_VIDEOMATRIX pStruVideoMatrixPara);
HB_SDVR_API BOOL __stdcall  HB_SDVR_VideoMatrixGet(LONG lUserID,LPHB_SDVR_VIDEOMATRIX pStruVideoMatrixPara);

HB_SDVR_API BOOL __stdcall  HB_SDVR_SetVideoMatrixConfig(LONG lUserID, LPVOID lpBuf, DWORD dwSize);
HB_SDVR_API BOOL __stdcall  HB_SDVR_GetVideoMatrixConfig(LONG lUserID, LPVOID lpBuf, DWORD* lpSize);

/*********************************************************************************
//add by njt for 8000TH 
功能：平台信息的设置和查询。
参数: lUserID 用户ID，用户登录时返回的。
返回：true 成功   false 失败。
*********************************************************************************/


// typedef struct
// {
// 	BYTE plat_type[MAX_PLATNUM];//平台类型
// 	BYTE reserve[32];
// }HB_SDVR_PLATPARAM,*LPHB_SDVR_PLATPARAM;


//HB_SDVR_API BOOL __stdcall  HB_SDVR_GETPLATPARAM(LONG lUserID,LPHB_SDVR_PLATPARAM pStrplatparam);
//HB_SDVR_API BOOL __stdcall  HB_SDVR_SETPLATPARAM(LONG lUserID,LPHB_SDVR_PLATPARAM pStrplatparam);
HB_SDVR_API BOOL __stdcall HB_SDVR_GETPLATPARAM(LONG lUserID, LPVOID lpBuffer,DWORD dwBufferSize,DWORD type);
HB_SDVR_API BOOL __stdcall HB_SDVR_SETPLATPARAM(LONG lUserID, LPVOID lpBuffer,DWORD dwBufferSize,DWORD type);


// add 2010/08/04
/*
功能：设置蜂鸣器状态
    参数：lUserID：由HB_SDVR_Login返回
返回值：
    成功：返回TRUE
    失败：返回FALSE
*/
// 2010/08/04 设置蜂鸣器报警
typedef struct _STRUCT_BUZZER_CTRL
{
    int ctrl;			//1.开  0.关
}STRUCT_BUZZER_CTRL, *LPSTRUCT_BUZZER_CTRL;

HB_SDVR_API BOOL __stdcall HB_SDVR_SetBuzzerState( LONG lUserID, 
                                                  BUSZZERSTATE WorkState );


HB_SDVR_API BOOL __stdcall HB_SDVR_GetBuzzerState( LONG lUserID,
                                                  BUSZZERSTATE *pWorkState);

//报警通道
HB_SDVR_API LONG __stdcall HB_SDVR_AlarmStart(LONG lUserID,void(CALLBACK *fAlarmDataCallBack)(LONG lAlarmHandle,char *pRecvDataBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
HB_SDVR_API LONG __stdcall HB_SDVR_AlarmStop(LONG lUserID);


// 智能ATM
HB_SDVR_API LONG __stdcall HB_SDVR_GetAlarmConfig(LONG lUserID, LPVOID lpOutBuffer, int channel);
HB_SDVR_API LONG __stdcall HB_SDVR_SetAlarmConfig(LONG lUserID, LPVOID lpInBuffer, int channel);
HB_SDVR_API BOOL __stdcall HB_SDVR_ResetAlarmEnvi(LONG lUserID);

typedef struct     {
	unsigned            second : 6; // 秒: 0~59
	unsigned            minute : 6; // 分: 0~59
	unsigned            hour : 5; // 时: 0~23
	unsigned            day : 5; // 日: 1~31
	unsigned            month : 4; // 月: 1~12
	unsigned            year : 6; // 年: 2000~2063
}MFS_Field_Time;

// 泸州智能
#define HB_MAX_AM_COUNT	16

typedef struct 
{
	WORD enable;      //0-撤防，1-布防
	WORD time;         //布防延时时间（此变量暂时无用）
	DWORD reserver[4];  // 保留
}HB_SDVR_REAL_DEFENCE, *LPHB_SDVR_REAL_DEFENCE;

typedef struct
{
	WORD alm_ch;                							//报警通道
	WORD alm_type;             							//报警类型0-无报警1-探头报警2-移动侦测3-视频丢失
	MFS_Field_Time time;        								//报警发生时间点
}HB_SDVR_ALMINFO, *LPHB_SDVR_ALMINFO;

typedef struct
{
	DWORD alm_count;                         				//掉线期间报警总数
	HB_SDVR_ALMINFO alminfo[HB_MAX_AM_COUNT];    			//每次报警的相关信息，只存储最新的16次报警
	DWORD reserver[4];      // 保留
}HB_SDVR_DISCONN_ALMSTAT, *LPHB_SDVR_DISCONN_ALMSTAT;

// 获取实时布防状态
HB_SDVR_API BOOL __stdcall HB_SDVR_GetRealDefenceCfg(LONG lUserID, LPHB_SDVR_REAL_DEFENCE lpCfg, DWORD* pDataSize);
// 实时布防、撤防
HB_SDVR_API BOOL __stdcall HB_SDVR_SetRealDefenceCfg(LONG lUserID, LPHB_SDVR_REAL_DEFENCE lpCfg, DWORD dwDataSize);
// 获取主机掉线期间的报警信息
HB_SDVR_API BOOL __stdcall HB_SDVR_GetDisconAlarmInfo(LONG lUserID, LPHB_SDVR_DISCONN_ALMSTAT lpInfo, DWORD* pDataSize);

// 2011/09/21 T系列机器增加遮挡报警设置的设置/获取
// 命令号:
#define NET_SDVR_GET_VCOVER_DETECT  0x98
#define NET_SDVR_SET_VCOVER_DETECT  0x99

// 数据体结构
typedef struct HB_SDVR_VCOVER_ALM_ST
{
    BYTE    byChannel;          // 通道号 [0,n] 
    DWORD   dwVcover_Enable;    // 遮挡报警使能， 1-启用；0-不启用；
    DWORD   dwSensor_Out;       // 联动报警输出， 按位表示， 1-联动；0-不联动；
}HB_SDVR_VCOVER_ALM, *LPHB_SDVR_VCOVER_ALM;

// 接口函数
HB_SDVR_API BOOL __stdcall HB_SDVR_GetVcoverAlarmCfg(LONG lUserID, LPHB_SDVR_VCOVER_ALM lpCfg, DWORD* pDataSize);
HB_SDVR_API BOOL __stdcall HB_SDVR_SetVcoverAlarmCfg(LONG lUserID, LPHB_SDVR_VCOVER_ALM lpCfg, DWORD dwDataSize);

// 2011/09/21 IPC相关接口变动
// 1.无线参数配置 数据体结构变动
// 2.工作模式参数去掉，使用工作参数替换，命令号变更为0xB0/0xB1
// 3.原0xB0-0xB6废弃

// 命令号
#define NET_SDVR_IPCWORKPARAM_GET   0xB0
#define NET_SDVR_IPCWORKPARAM_SET   0xB1

typedef struct HB_SDVR_REQIPCWORKPARAM_ST
{
    BYTE cbStreamType;  // 码流类型 0-主码流 1-子码流 2-第三码流
    BYTE cbReserve[3];
}HB_SDVR_REQIPCWORKPARAM, *LPHB_SDVR_REQIPCWORKPARAM;

// 数据体结构
// typedef struct	{
//     BYTE	byEnable;  		// 布防时间使能  0-关闭，1-启动	
//     BYTE	byStartHour;  	//开始小时 0-23
//     BYTE	byStartMin;  		//开始分钟 0-59
//     BYTE	byStopHour; 		//结束小时  0-23
//     BYTE	byStopMin;  		//结束分钟  0-59
// }STRUCT_SDVR_SCHEDTIME; 


typedef struct HB_SDVR_SCHEDTIME_V2_ST
{
    BYTE	byStartHour;  			//开始小时 0-23
    BYTE	byStartMin;  			//开始分钟 0-59
    BYTE	byStopHour; 			//结束小时  0-23
    BYTE	byStopMin;  			//结束分钟  0-59
} HB_SDVR_SCHEDTIME_V2, *LPHB_SDVR_SCHEDTIME_V2;	

typedef struct HB_SDVR_ICRTIME_ST
{
    WORD 	wLightRange;		//ICR亮度切换临界值，取值范围0 < wLightRange< 2^16;
    WORD 	wEnable;        // 0--亮度值有效  1--时间段有效
    HB_SDVR_SCHEDTIME_V2 stSchedTime[2];
}HB_SDVR_ICRTIME, *LPHB_SDVR_ICRTIME;

typedef struct HB_SDVR_SHUTTERVAL_ST
{
    DWORD  dwShutterIndex; //当前快门时间索引值,表示基于dwShutterVal中的位置，例如dwShutterIndex = 2，
    //则当前快门时间为dwShutterVal[2];
    DWORD	 dwShutterVal[32];	//获取快门时间的支持参数列表,当dwShutterVal[1]=0,表示是一个取值范围，如
    //dwShutterVal[0]= 4096,则表示取值范围为：1/[1,4096*2],当dwShutterVal[1] != 0时，
    //表示有多个具体的索引值，比如：dwShutterVal[0]= 2048，dwShutterVal[1]=4096，当dwShutterVal[x]=0则表示数据共有x个。
}HB_SDVR_SHUTTERVAL, *LPHB_SDVR_SHUTTERVAL;

typedef struct HB_SDVR_SCENEVAL_ST
{
    DWORD dwSceneIndex;	//当前镜头索引值，表示基于cbSceneVal中的位置，例如dwSceneIndex = 2，
    //则当前镜头为：cbSceneVal[2] = “JCD661 lens”，当cbSceneVal[x] =”\0”表示总共有
    //x个数据项；
    BYTE	cbSceneVal[8][32];	//该机型支持的镜头种类,//0 - Full Maual lens,1 - DC Iris lens, //2 - JCD661 lens,
    //3 - Ricom NL3XZD lens,4 - Tamron 18X lens，
}HB_SDVR_SCENEVAL, *LPHB_SDVR_SCENEVAL;

typedef struct HB_SDVR_RESOLUTION_ST
{
    DWORD	dwResoluIndex;	//当前分辨率索引值，表示基于dwResolution中的位置，例如dwResoluIndex= 2，
    //则当前分辨率为dwResolution[2]中所指定的分辨率
    DWORD	dwResolution[16];	//该机型支持的分辨率，用DWORD来表示支持的分辨率，例如：
    //dwResolution[0]=0x07800438，高两字节（0x0780=1920）、低两字节（0x0438=1080）；
}HB_SDVR_RESOLUTION, *LPHB_SDVR_RESOLUTION;

typedef struct HB_SDVR_AGCVAL_ST
{
    DWORD dwAgcIndex;       //当前AGC的索引值，表示基于cbAgcVal中的位置，例如cbAgcVal =2，则表示AGC
                            //值为cbAgcVal[2]中的值；
    BYTE	cbAgcVal[32];	//AGC（自动增益）的支持参数列表,当cbAgcVal[1]= 0时表示cbAgcVal[0]中存储的是
                            //一个取值范围，如cbAgcVal[0]= 128,则表示取值范围为：[1,128],当cbAgcVal[1]!=0
                            //时，则表示cbAgcVal数组中存储的是具体的值，例如 cbAgcVal[0]= 32，//cbAgcVal[1]=64等，当cbAgcVal [x] =0表示总共有x个数据项。
}HB_SDVR_AGCVAL, *LPHB_SDVR_AGCVAL;

typedef struct HB_SDVR_FRAMERATE_ST
{
    BYTE	cbMinFrameRate;	//该机型支持的最小编码帧率值;，取值范围为：1—2^8，下同。
    BYTE	cbMaxFrameRate;	//该机型支持的最大编码帧率值;
    BYTE	cbCurFrameRate;	//该机型设置的当前编码帧率值;
    BYTE   cbreserve;		//保留
}HB_SDVR_FRAMERATE, *LPHB_SDVR_FRAMERATE;

typedef struct HB_SDVR_IPCWORKMODE_ST
{
    DWORD   dwLength;		//结构体长度
    BYTE    cbStreamEnable;   //是否开启当前码流
    BYTE    cbStreamType;    //码流类型 0-主流1-子流 2-第三码流
    BYTE    cbAudioEnable;    //音频使能 0-无音频 ,1-有音频
    BYTE  	cbAntiFlicker;     //抗闪烁设置 0-60HZ   1-50HZ
    HB_SDVR_FRAMERATE   stFrameRate;	//编码帧率设置;
    HB_SDVR_SHUTTERVAL  stShutterVal;	//快门相关参数获取
    HB_SDVR_SCENEVAL	stSceneVal;	//镜头相关参数获取
    HB_SDVR_RESOLUTION	stResolution;	//解析度相关
    HB_SDVR_AGCVAL		stAgcVal;		//Agc相关
    DWORD	dwBitRateVal;		//视频码率 0-100K 1-128K，2-256K，3-512K，4-1M，5-1.5M，6-2M，7-3M, 8-4M
    //9-5M，10-6M，11-7M，12-8M, 13-9M，14-10M，15-11 M，16-12M
    //其他：码率值（kbps）有效范围 32~2^32,大于等于32，以K为单位；
    BYTE	cbFoucusSpeedVal;	//光学变焦速度值，0：不支持
    BYTE	cbDigitalFoucusVal;//数字变焦值，0：不支持
    BYTE	cbImageTurnVal;	//当前图像翻转设置 //1-不翻转,2-水平翻转 3-垂直翻转, 4-水平&垂直,0-不支持
    BYTE	cbBlackWhiteCtrlVal; //当前黑白模式设置 //1- Off, 2- On, 3–Auto, 0-不支持
    BYTE	cbIRISCtrl;		 //Iris control mode 光圈控制模式设置，1-Off,2-Basic, 3-Advanced,0-不支持
    BYTE	cbAutoFoucusVal;	//是否支持自动对焦，//0-不支持,1-支持
    BYTE 	cbAWBVal;		//白平衡场景模式设置，1-auto_wide, 2-auto_normal, 3-sunny, 4-shadow, 5-indoor,
    //6-lamp, 7-FL1, 8-FL2,0-不支持
    BYTE 	cbA3Ctrl;      //3A控制0-off; 1-Auto Exposure; 2-Auto White Balance; 3-both, (Auto Focus no support)
    HB_SDVR_ICRTIME stICRTime; //ircut(滤光片切换模式设置)仅在模式4时才设置获取该值
    BYTE	cbFNRSuppVal;	//当前帧降噪设置，1-开,2-关,0-不支持
    BYTE	cbStreamKindVal;	//当前码流类型，1-定码流,2-变码流
    BYTE	cbVideoOutKindVal;	//vout视频输出设置：0-disable, 1-CVBS, 2-HDMI,3-YPbPr等等
    BYTE	cbWDRVal;		//该机型是否支持宽动态设置,0-不支持,1-支持
    BYTE    cbColorMode;     //色彩风格设置 0-TV   1--PC
    BYTE    cbSharpNess;		//锐度设置，取值范围为：[1,255]
    BYTE	cbPlatformType;	//平台类别
    BYTE	cbReserve[17];		//保留
} HB_SDVR_IPCWORKMODE, *LPHB_SDVR_IPCWORKMODE;

// 接口函数
HB_SDVR_API BOOL __stdcall HB_SDVR_IpcGetWorkParam(LONG lUserID, LPHB_SDVR_IPCWORKMODE lpCfg, DWORD* pDataSize);
HB_SDVR_API BOOL __stdcall HB_SDVR_IpcSetWorkParam(LONG lUserID, LPHB_SDVR_IPCWORKMODE lpCfg, DWORD dwDataSize);

// 2011/09/22 NVR新增协议
// 命令号
//nvr新增28个协议
#define NET_SDVR_STREAM_TYPE_NVR                0xC0  // 数据流类型(文件头)
#define NET_SDVR_WORK_STATE_EX                  0xC1  // 获取主机设备工作状态扩展
#define NET_SDVR_GET_CH_CLIENT_IP               0xC2  // 获取对应通道连接的客户端IP列表
#define NET_SDVR_LOG_QUERY_EX                   0xC3  // NVR日志信息查询
#define NET_SDVR_SERIAL_START_NVR               0xC4  // 建立NVR透明通道
#define NET_SDVR_SERIAL_STOP_NVR                0xC5  // 关闭NVR透明通道
#define NET_SDVR_DEVICECFG_GET_EX               0xC6  // 获取设备信息(扩展)
#define NET_SDVR_DEVICECFG_SET_EX               0xC7  // 设置设备信息(扩展)
#define NET_SDVR_PTZLIST_GET_NVR                0xC8  // 获取NVR云台协议列表
#define NET_SDVR_ALRM_ATTR_NVR                  0xC9  // 获取NVR报警输入输出端口属性
#define NET_SDVR_ALRMIN_GET_NVR                 0xCA  // 获取NVR报警输入参数
#define NET_SDVR_ALRMIN_SET_NVR                 0xCB  // 设置NVR报警输入参数
#define NET_SDVR_ALRMOUT_GET_NVR                0xCC  // 获取NVR报警输出参数
#define NET_SDVR_ALRMOUT_SET_NVR                0xCD  // 设置NVR报警输出参数
#define NET_SDVR_ALRMIN_STATUS_GET_NVR          0xCE  // 获取NVR报警输入状态
#define NET_SDVR_ALRMOUT_STATUS_GET_NVR         0xCF  // 获取NVR报警输出状态
#define NET_SDVR_ALRMOUT_STATUS_SET_NVR         0xD1  // 设置NVR报警输出状态
#define NET_SDVR_PICCFG_GET_EX_NVR              0xD2  // 获取NVR通道参数
#define NET_SDVR_PICCFG_SET_EX_NVR              0xD3  // 设置NVR通道参数
#define NET_SDVR_RECORD_GET_EX_NVR              0xD4  // 获取NVR录像参数
#define NET_SDVR_RECORD_SET_EX_NVR              0xD5  // 设置NVR录像参数
#define NET_SDVR_MOTION_DETECT_GET_NVR          0xD6  // 获取NVR移动侦测参数
#define NET_SDVR_MOTION_DETECT_SET_NVR          0xD7  // 设置NVR移动侦测参数
#define NET_SDVR_ABNORMAL_ALRM_GET_NVR          0xD8  // 获取NVR异常报警参数
#define NET_SDVR_ABNORMAL_ALRM_SET_NVR          0xD9  // 设置NVR异常报警参数
#define NET_SDVR_PARAM_FILE_EXPORT              0xDA  // 主机参数文件导出
#define NET_SDVR_PARAM_FILE_IMPORT              0xDB  // 主机参数文件导入
#define NET_SDVR_RESOLUTION_GET_NVR             0xDC  // 获取NVR主机分辨率
#define NET_SDVR_RESOLUTION_SET_NVR             0xDD  // 设置NVR主机分辨率
#define NET_SDVR_QUERY_MONTH_RECFILE            0x47  // 按月查询录像


//数据流解码类型(实时视频、回放、备份)
//#define NET_SDVR_STREAM_TYPE_NVR       0xC0  
typedef struct
{
    BYTE sBuff[64];         // 文件头类型
} HB_STREAM_TYPE;


//获取主机设备工作状态
//#define NET_SDVR_WORK_STATE_EX          0xC1 
// typedef struct	
// {
//     DWORD dwVolume;				//硬盘的容量（MB）
//     DWORD dwFreeSpace;			//硬盘的剩余空间（MB）
//     DWORD dwHardDiskStatic;		//硬盘状态（dwVolume有值时有效） 0-正常 1-磁盘错误 2-文件系统出错
// } STRUCT_SDVR_DISKSTATE;

typedef struct 
{
    BYTE byRecordStatic;			//通道是否在录像,0-不录像,1-录像
    BYTE bySignalStatic;			//连接的信号状态,0-正常,1-信号丢失
    BYTE byHardwareStatic;			//保留
    BYTE byLinkNum; 				//客户端连接的个数：同一通道当前时间的实时流的连接数。不分主子码流，同一IP多个连接算多个连接
    DWORD dwBitRate;				//实际码率
} HB_SDVR_CHANNELSTATE_EX;

typedef struct	
{
    DWORD dwSize ; 										//结构体大小
    HB_SDVR_DISKSTATE  struHardDiskStatic[16];		//硬盘状态
    HB_SDVR_CHANNELSTATE_EX struChanStatic[128];	//通道的状态
    BYTE byAlarminStatusLocal[128];						//本地报警输入端口的状态
    BYTE byAlarmoutStatusLocal[128];					//本地报警输出端口的状态
    DWORD dwReserve[4];									//保留
} HB_SDVR_WORKSTATE_V2, *LPHB_SDVR_WORKSTATE_V2;


//获取各通道实时视频流连接的客户端ip列表
//#define NET_SDVR_GET_CH_CLIENT_IP       0xC2
typedef struct
{
    DWORD dwSize;						    //结构体大小
    BYTE  byChannel;					    //通道号[0, n-1],n:通道数
    BYTE  byClientIpNum;					//此通道连接客户端IP个数
    BYTE  byReserve1[2];					//保留
    DWORD dwDwClientIP[64];				    //客户端IP列表
    DWORD dwReserve2[4];					//保留
} HB_CLIENT_IP_INFO, *LPHB_CLIENT_IP_INFO;


//日志命令结构体
//#define NET_SDVR_LOG_QUERY_EX           0xC3
typedef struct
{
    WORD wYear;			    //年: 2000~2063
    BYTE byMonth;			//月: 1~12
    BYTE byDay;				//日: 1~31
    WORD wStart; 			//查询从第几条开始，一般为0。
    WORD wnum;  			//一次查询个数，最多为100。
    BYTE byPriType;    		//主类型 （需扩展所有）
    BYTE bySecType;  		//次类型
    BYTE byReserve[6];		//保留
} HB_REQLOG_EX, *LPHB_REQLOG_EX;

typedef struct 
{
    DWORD  dwSize;					    //结构体大小
    DWORD  dwTotalLogNum;	    		//日志总条数
    DWORD  dwCurLogNum;				    //本次查到的条数
    DWORD  dwStart; 				    //本次查询到的日志的起始编号
    BYTE   byEncType;					//编码格式 1- UTF-8  2-gb2312   
    BYTE   byReserve[3];				//保留
    BYTE   sSigalLogData[100][128];     // 日志信息 (每次查询最多支持100条日志，日志多于100条									//  需要多次调用，每条128字节，每条以‘\0’结束)
} HB_SDVR_LOGINFO_EX, *LPHB_SDVR_LOGINFO_EX;

typedef enum //主类型
{
    LOG_PRI_ALL = -1, //全部
    LOG_PRI_ERROR, // 异常
    LOG_PRI_ALARM, // 报警
    LOG_PRI_OPERATE, // 操作
    LOG_PRI_MAX
} LOG_PRI_TYPE;

typedef enum //操作次类型
{
    LOG_OP_ALL = -1,
    LOG_OP_POWERON, // 开机
    LOG_OP_SHUTDOWN, // 关机
    LOG_OP_EXC_SHUTDOWN, //异常关机
    LOG_OP_REBOOT, // 重启
    LOG_OP_LOGIN, // 登陆
    LOG_OP_LOGOUT, // 注销
    LOG_OP_SETCONFIG, // 配置
    LOG_OP_FRONTEND_SETCONFIG, //前端设备配置
    LOG_OP_UPGRADE, // 升级
    LOG_OP_FRONTEND_UPGRADE, //前端设备升级
    LOG_OP_RECORD_START, // 本地启动手动录像
    LOG_OP_RECORD_STOP, // 本地停止手动录像
    LOG_OP_PTZ, // 云台控制
    LOG_OP_MANUAL_ALARM, //本地手动报警
    LOG_OP_FORMAT_DISK, // 格式化硬盘
    LOG_OP_FILE_PLAYBACK, // 本地回放文件
    LOG_OP_EXPORT_CONFIGFILE, //导出本地配置文件
    LOG_OP_LMPORT_CONFIGFILE, //导入本地配置文件
    LOG_OP_FREXPORT_CONFIGFILE, //导出前端设备配置文件
    LOG_OP_FRLMPORT_CONFIGFILE, //导入前端设备配置文件 
    LOG_OP_BACKUP_REC, //本地备份录像文件
    LOG_OP_DEFAULT, //本地恢复缺省
    LOG_OP_SETTIME, // 本地设置系统时间
    LOG_OP_TRANSCOM_OPEN, // 建立透明通道
    LOG_OP_TRANSCOM_CLOSE, // 断开透明通道
    LOG_OP_TALKBACK_START, // 对讲开始
    LOG_OP_TALKBACK_STOP, // 对讲结束

    LOG_OP_TYPE_NONE,    // 无录像
    LOG_OP_TYPE_MANUAL,  // 手动录像
    LOG_OP_TYPE_TIME,    // 定时录像
    LOG_OP_TYPE_MOTION,  // 移动录像
    LOG_OP_TYPE_SENSOR,  // 探头报警
    LOG_OP_TYPE_MOTION_OR_SENSOR,	// 移动或报警录像
    LOG_OP_TYPE_MOTION_AND_SENSOR,	// 移动与探头报警
    LOG_OP_REMOTE_LOGIN,	// 前端设备登陆
    LOG_OP_REMOTE_LOGOUT,	// 前端设备注销

    LOG_OP_TYPE_MAX
} LOG_OPERATE_TYPE;

typedef enum //报警次类型
{
    LOG_ALM_ALL = -1,
    LOG_ALM_LOCAL_SENSORIN, // 本地报警输入
    LOG_ALM_LOCAL_SENSOROUT,// 本地报警输出
    LOG_ALM_FRONTEND_SENSORIN,//前端设备报警输入  
    LOG_ALM_FRONTEND_SENSOROUT,//前端设备报警输出
    LOG_ALM_MOTION_START, // 移动侦测开始
    LOG_ALM_MOTION_STOP, // 移动侦测结束
    LOG_ALM_MAIL_UPLOAD, // 邮件上传
    LOG_ALM_TYPE_MAX
} LOG_ALARM_TYPE;

typedef enum //错误次类型
{
    LOG_ERR_ALL = -1,
    LOG_ERR_VIDEOLOST, // 视频丢失
    LOG_ERR_HD_ERROR, // 磁盘错误
    LOG_ERR_HD_FULL, // 磁盘满
    LOG_ERR_LOGIN_FAIL, // 登陆失败
    LOG_ERR_TEMP_HI, // 温度过高
    LOG_ERR_HD_PFILE_INDEX, // 磁盘主索引错误
    LOG_ERR_HD_DEV_FATAL, // 磁盘设备致命错误
    LOG_ERR_IP_CONFLICT, //ip冲突
    LOG_ERR_NET_EXCEPTION, //网络异常
    LOG_ERR_REC_EXCEPTION, //录像异常
    LOG_ERR_FRONTEND_EXCEPTION, //前端设备异常
    LOG_ERR_TIME_EXCEPTION, //时间异常
    LOG_ERR_FRONTBOARD_EXCEPTION, //前面板异常
    LOG_ERR_TYPE_MAX
} LOG_ERROR_TYPE;

//建立nvr透明通道
//#define NET_SDVR_SERIAL_START_NVR       0xC4
//关闭NVR透明通道
//#define NET_SDVR_SERIAL_STOP_NVR        0xC5  
typedef struct
{
    BYTE  byOpType; 			//0-（混合DVR,设置本地），1-前端设备所属的 (为1时byChannel生效)
    BYTE  bySeriaType;		    //一个字节的串口类型，1：232  2：485。
    BYTE  byChannel;   		    //[0, n-1],n:通道数
    BYTE  byReserve[5];		    //保留
} HB_NVR_SERIAL_START, *LPHB_NVR_SERIAL_START;


//获取设备信息扩展
//#define NET_SDVR_DEVICECFG_GET_EX       0xC6
//设置设备信息(扩展)
//#define NET_SDVR_DEVICECFG_SET_EX       0xC7  
typedef struct	
{
    DWORD dwSize;						//结构体大小
    BYTE sDVRName[32];					//设备, 以’\0’结束字符串
    DWORD dwDVRID;						//保留
    DWORD dwRecycleRecord;				//协议二: //录像覆盖策略 0-循环覆盖 1-提示覆盖
    BYTE sSerialNumber[48];				//序列号
    BYTE sSoftwareVersion[64];			//软件版本号以’\0’结束字符串协议二: （主机型号 软件版本号）
    BYTE sSoftwareBuildDate[32];		//软件生成日期以’\0’结束字符串协议二:（Build 100112）
    DWORD dwDSPSoftwareVersion;			//DSP软件版本
    BYTE sPanelVersion[32];				//前面板版本，以’\0’结束字符串，IPC无
    BYTE sHardWareVersion[32];	        //(保留)协议二: 当软件版本号超过16字节时会使用作为主机型号显示
    BYTE byAlarmInPortNum;		        //报警输入个数, NVR只取本地报警输入
    BYTE byAlarmOutPortNum;	  	    	//报警输出个数, NVR只取本地报警输出
    BYTE byRS232Num;			        //保留
    BYTE byRS485Num;					//保留
    BYTE byNetworkPortNum;				//保留
    BYTE byDiskCtrlNum;					//保留
    BYTE byDiskNum;						//硬盘个数
    BYTE byDVRType;						//DVR类型, 1:NVR 2:ATM NVR 3:DVS 4:IPC 5:NVR （建议使用//NET_SDVR_GET_DVRTYPE命令）
    BYTE byChanNum;						//通道个数[0, 128]
    BYTE byStartChan;					//保留
    BYTE byDecordChans;					//保留
    BYTE byVGANum;						//保留
    BYTE byUSBNum;						//保留
    BYTE byReserve[3];					//保留
} HB_DEVICEINFO_V2, *LPHB_DEVICEINFO_V2;


//获取nvr云台协议列表
//#define NET_SDVR_PTZLIST_GET_NVR        0xC8
typedef struct
{
    BYTE  byType; 		    //0-NVR本地云台，1-前端设备云台 (为1时byChannel生效)
    BYTE  byChannel;   	    //[0, n-1],n:通道数
    BYTE  byReserve[2];	    //保留
} HB_NVR_PTZLIST, *LPHB_NVR_PTZLIST;

typedef struct 
{
    DWORD 	dwPtznum;				//协议个数（限制为最多100个）
    BYTE	byReserve[4];		    //保留
        BYTE   	sPtzType[100][10];	    //协议名列表―――0，unknow;
} HB_NVR_PTZLIST_INFO, *LPHB_NVR_PTZLIST_INFO;

//获取NVR报警输入输出端口属性
//#define NET_SDVR_ALRM_ATTR_NVR                  0xC9 
typedef struct
{
    DWORD dwSize;                       // 结构体大小
    BYTE byOpType;                      // 0-本地 1-前端 (为1时,byChannel有效)
    BYTE byChannel;                     // 操作前端某通道设备 [0, n-1], n:通道个数
    BYTE byAlarmInNum;					// 此设备拥有报警输入个数
    BYTE byAlarmOutNum;				    // 此设备拥有报警输出个数
    BYTE sAlarmInPortName[128][32];		// 报警输入端口名， 以’\0’结束字符串
    BYTE sAlarmOutPortName[16][32];		// 报警输出端口名， 以’\0’结束字符串
    BYTE sDevName[32];					// 通道对应设备名称
    DWORD dwIP;						    // 设备IP
    BYTE byReserve[4];			        // 保留
} HB_NVR_ALRM_PORT_ATTR, *LPHB_NVR_ALRM_PORT_ATTR;


//获取nvr报警输入参数
//#define NET_SDVR_ALRMIN_GET_NVR         0xCA
//设置nvr报警输入参数
//#define NET_SDVR_ALRMIN_SET_NVR         0xCB	

typedef struct
{
    DWORD dwSize;                      			//结构体大小
    BYTE  byOpType;                        		//0-本地 1-前端 (为1时,byChannel有效)
    BYTE  byChannel;                     		//操作前端某通道设备 [0, n-1], n:通道个数
    BYTE  byAlarmInPort;				    	//报警输入端口号[0, n-1], n:报警输入个数
    BYTE  sAlarmInName[32];			    		//报警输入端口名， 以’\0’结束字符串
    BYTE  byAlarmType;				    		//探头类型 0-常闭1-常开
    BYTE  byEnSchedule;							//报警输入布防时间激活 0-屏蔽 1-激活 
    BYTE  byWeekEnable;               			//每天使能位0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]来设置每一天) 
    BYTE  byAllDayEnable[8];					//全天使能 ,0-不使能 1-使能若此项使能,则对应的天为全天布防,不用判断时间段	
    HB_SDVR_SCHEDTIME_V2 struAlarmTime[8][8];  //布防时间段
    DWORD dwHandleType;	            			//按位 2-声音报警 5-监视器最大化 //6-邮件上传

    // 联动报警输出
    BYTE  byAlarmOutLocal[16];		            //报警输出端口(本地)
    BYTE  byAlarmOutRemote[128][16];		    //报警输出端口(前端设备)

    // 联动录像
    BYTE  byRelRecordChan[128];		            //报警触发的录象通道,为1表示触发该通道 0为不触发

    // 联动其他
    BYTE  byEnablePreset[128];				    //是否调用预置点 仅用byEnablePreset[0]来判断
    BYTE  byPresetNo[128];					    //调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 [1, 254]
    BYTE  byReserve[32];			        	//保留
} HB_NVR_ALRMININFO, *LPHB_NVR_ALRMININFO;


//获取nvr报警输出参数
//#define NET_SDVR_ALRMOUT_GET_NVR        0xCC
//设置nvr报警输出参数
//#define NET_SDVR_ALRMOUT_SET_NVR        0xCD
typedef struct	
{
    DWORD dwSize;					            // 结构体大小
    BYTE byOpType;                              // 0-本地 1-前端 (为1时,byChannel有效)
    BYTE byChannel;                             // 操作前端某通道设备 [0, n-1], n:通道个数
    BYTE byALarmOutPort;			            // 报警输出通道号 [0, n-1], n:报警输出端口数
    BYTE sAlarmOutName[32];			            // 名称 以’\0’结束字符串
    DWORD dwAlarmOutDelay;			            // 输出保持时间 单位秒 [2, 300]
    BYTE byAlarmType;				            // 探头类型 0-常闭1-常开 (保留)    
    BYTE byEnSchedule;				            // 报警输出布防时间激活 0-屏蔽 1-激活 
    BYTE byWeekEnable;                          // 每天使能位0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)  
    BYTE byFullDayEnable[8];     		        // 完整天录像 0-不使能(缺省值) 1-使能
    HB_SDVR_SCHEDTIME_V2 struAlarmTime[8][8];   //布防时间段, 8个时间段

    BYTE  byReserve[32]; 				        // 保留
} HB_NVR_ALARMOUTINFO, *LPHB_NVR_ALARMOUTINFO;


//获取nvr报警输入状态
//#define NET_SDVR_ALRMIN_STATUS_GET_NVR  0xCE
typedef struct	
{
    BYTE  byOpType;                 //  0-本地 1-前端 (为1时,byChannel有效)
    BYTE  byChannel;                // 操作前端某通道设备 [0, n-1], n:通道个数
    BYTE  byAlarm; 			        // 保留
    BYTE  byReserve1;			    // 保留
    BYTE  byAlarmIn[128];           // 报警输入状态 128个报警输入, 0-无输入 1-有输入
    BYTE  byRreserve2[32];		    // 保留
} HB_NVR_ALRMIN_STATUS, *LPHB_NVR_ALRMIN_STATUS;

//获取nvr报警输出状态
//#define NET_SDVR_ALRMOUT_STATUS_GET_NVR 0xCF
//设置nvr报警输出状态
//#define NET_SDVR_ALRMOUT_STATUS_SET_NVR 0xD1
typedef struct	
{
    BYTE    byOpType;           //  0-本地 1-前端 (为1时,byChannel有效)
    BYTE    byChannel;          // 操作前端某通道设备 [0, n-1], n:通道个数
    BYTE	byAlarm; 		    // 报警输出状态 0-不报警 1-报警
    BYTE	byReserve1;			// 保留
    BYTE	byAlarmOut[16];  	// 报警输出状态 16个报警输出, 获取命令时,byAlarm无效,byAlarmOut[16]中为1的是有输出,0为无输出；设置命令时byAlarm有效，byAlarmOut[16]中0-状态不变 1-执行byAlarm操作
    BYTE 	byReserve2[32];
} HB_NVR_ALRMOUT_STATUS, *LPHB_NVR_ALRMOUT_STATUS;


//获取nvr通道参数
//#define NET_SDVR_PICCFG_GET_EX_NVR      0xD2
//设置nvr通道参数
//#define NET_SDVR_PICCFG_SET_EX_NVR      0xD3 
// typedef struct	
// {
//     WORD wHideAreaTopLeftX;				    // 遮盖区域的x坐标  0~704
//     WORD wHideAreaTopLeftY;				    // 遮盖区域的y坐标  0~576
//     WORD wHideAreaWidth;					// 遮盖区域的宽 0~704
//     WORD wHideAreaHeight;					// 遮盖区域的高 0~576
// } HB_SDVR_SHELTER;

typedef struct
{
    BYTE byBrightness;                // 亮度      取值范围[0，255] 缺省值128
    BYTE byConstrast;                 // 对比度    取值范围[0，255] 缺省值128
    BYTE bySaturation;                // 饱和度    取值范围[0，255] 缺省值128
    BYTE byHue;                       // 色度      取值范围[0，255] 缺省值128
    BYTE bySharp;                     // 锐度      0（缺省值）或1    
    DWORD dwReserved;                 // 预留
} VIDEO_INFO, *PVIDEO_INFO;

typedef struct	
{
    DWORD dwSize; 					// 长度(结构体大小)

    // 通道名相关
    BYTE sChanName[32];				// 通道名 以’\0’结束字符串
    BYTE byChannel; 					// 通道号 [0, n－1] n:通道数
    DWORD dwShowChanName;		    // 是否显示通道名 0-显示 1-不显示
    BYTE byOSDAttrib;				// 通道名 1-不透明 2-透明（只针对PC端显示）
    WORD wShowNameTopLeftX;		    // 通道名称显示位置的x坐标 左->右 0~视频实际宽度－通道名长度
    WORD wShowNameTopLeftY;		    // 通道名称显示位置的y坐标 上->下 0~视频实际高度－字体高度

    // 日期相关
    DWORD dwShowTime;				// 是否显示时间 0-显示 1-不显示
    WORD wOSDTopLeftX;				// 时间osd坐标X [0, 实际宽－时码长度]
    WORD wOSDTopLeftY;				// 时间osd坐标Y[0, 实际高－字体高度]
    BYTE byDateFormat;				// 日期格式
    //  0 - YYYY-MM-DD    （缺省值）
    //  1 - MM-DD-YYYY
    //  2 - YYYY年MM月DD日
    //  3 - MM月DD日YYYY年

    // 星期相关
    BYTE byDispWeek;				// 是否显示星期 0-显示 1-不显示
    BYTE byOSDLanguage;				// 星期语言 0-中文 1-英文 (可扩展)

    // 亮度色度相关
    VIDEO_INFO  struVideoInfo;                  // 视频信息

    // 遮挡区域相关
    DWORD dwEnableHide;		                // 视频遮挡使能 ,0-不遮挡,1-遮挡(遮挡区域全黑) 2-遮挡(遮挡区域马赛克)  
    HB_SDVR_SHELTER	struShelter[16];	// 视频遮挡区域	
    DWORD dwOsdOverType; 		// osd叠加类型 0-不叠加 1-前端叠加 2-后端叠加
    DWORD dwReserve[32];						// 保留
} HB_NVR_CHN_ATTR_INFO, *LPHB_NVR_CHN_ATTR_INFO;



//获取nvr录像参数
//#define NET_SDVR_RECORD_GET_EX_NVR      0xD4
//设置nvr录像参数
//#define NET_SDVR_RECORD_SET_EX_NVR      0xD5
typedef struct
{
    BYTE    byStreamtype;             // 流类型     0-变码流（缺省值） 1-定码流
    BYTE    byQuality;                // 视频质量   1-最高 2-较高 3-高（缺省值） 4-中 5-低 6-最低
    BYTE    byResolution;             // 主码流     0-DIF 1-D1（缺省值） 2-720P 3-1080P
    // 子码流     0-CIF 1-D1(缺省值)
    BYTE    byFramerate;              // 帧率       取值范围[2,25] 缺省值25
    BYTE    byMaxbitrate;             // 码流(主)   0-100K 1-128K 2-256K 3-512K 4-1M 5-1.5M 6-2M（缺省值） 7-3M 8-4M 9-6M 10-8M
    // 码流（子） 0-30K 1-45K 2-60K 3-75K 4-90K 5-100K 6-128K 7-256K 8-512K(缺省值) 9-1M 10-2M
    BYTE    byAudio;                  // 音频标识   0-无音频 1-有音频（缺省值）
    DWORD   dwReserved;               // 预留
} HB_RECORD_PARAM,  *LPHB_RECORD_PARAM;

typedef struct
{
    BYTE byStarth;                    // 起始时间-时
    BYTE byStartm;                    // 起始时间-分
    BYTE byStoph;                     // 结束时间-时
    BYTE byStopm;                     // 结束时间-分
    BYTE byRecType;                   // 录像类型  0 - 无 1-手动(无效)  2-定时  3-移动  4-报警 5-移动 | 报警  6 -移动 & 报警
    BYTE byReserve[3];				// 保留
}HB_REC_TIME_PERIOD, *LPHB_REC_TIME_PERIOD;

typedef struct
{
    BYTE byEnable;  	    // 完整天使能  0-不使能(缺省值) 1-使能
    BYTE byRecType; 	    // 完整天对应的录像类型 0 - 无 1-手动(无效)  2-定时  3-移动  4-报警 5-移动 | 报警  6- 移动 & 报警
    BYTE byReserve[2];	// 保留
} HB_FULL_DAY_S;

typedef struct
{
    BYTE byEnable;                                // 使能时间表 0-不使能(缺省值) 1-使能    
    BYTE byWeekEnable;                            // 每天使能位 0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)  
    HB_FULL_DAY_S	struFullDayEnable[8];       // 完整天录像
    HB_REC_TIME_PERIOD struAlarmTime[8][8]; // [0-7][0]代表全天使能的设置项

    DWORD  dwReserved;                            // 预留
} HB_REC_TIME_SCHEDULE, *LPHB_REC_TIME_SCHEDULE;

typedef struct
{
    DWORD   dwSize;                   			    // 结构体大小
    BYTE	byChannel;							    // 通道号
    WORD    wPreRecTime;            				    // 预录时间      取值范围[5，30]秒  缺省值10
    DWORD   dwDelayRecTime;         				    // 录像持续时间  取值范围[0,180]秒  缺省值30 (对3-移动录像 4-报警录像 5-移动 | 报警  6-移动 & 报警 有效)
    HB_REC_TIME_SCHEDULE struTimeSchedule;  // 录像时间表与录像类型设置

    HB_RECORD_PARAM    struTimeRecord;      		// 定时           录像参数
    HB_RECORD_PARAM    struMoveRecord;      	    // 移动           录像参数
    HB_RECORD_PARAM    struAlarmRecord;     	    // 报警           录像参数
    HB_RECORD_PARAM    struMoveOrAlarmRecord;       // 移动 | 报警    录像参数 
    HB_RECORD_PARAM    struMoveAndAlarmRecord;      // 移动 & 报警   录像参数
    HB_RECORD_PARAM    struNetRecParam[4];     	    // 子码流     录像参数 (保留)

    DWORD   byLinkMode;                             // 码流类型(0-主码流， 1-第一子码流，2-第二子码流....)
    DWORD   dwReserved[31];              			    // 预留
} HB_RECORD_SET, *LPHB_RECORD_SET; 


//获取nvr移动侦测参数
//#define NET_SDVR_MOTION_DETECT_GET_NVR  0xD6
//设置nvr移动侦测参数
//#define NET_SDVR_MOTION_DETECT_SET_NVR  0xD7
typedef struct	
{
    DWORD dwSize; 				                // 长度（结构体大小）
    BYTE byChannel; 			                // 通道号 [0, n－1] n:通道数

    BYTE byMotionScope[18][22];                 // 侦测区域,共有32*32个小宏块,为1表示该宏块是移动侦测区域,0-表示不是 
    BYTE byMotionSensitive;		                // 移动侦测灵敏度, 0 - 5,越高越灵敏 

    // 时间表相关
    BYTE byEnableHandleMotion;                  // 移动侦测布防使能 0-撤防 1-布防	
    BYTE byWeekEnable;                          // 设置每天0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)  
    BYTE byFullDayEnable[8];                    // 完整天录像 0-不使能(缺省值) 1-使能,若此项使能,则对应的天为全天布防,不用判断时间段
    HB_SDVR_SCHEDTIME_V2 struAlarmTime[8][8];   // 布防时间段, 8个时间段
    DWORD	dwHandleType;	                    // 按位 2-声音报警5-监视器最大化 //6-邮件上传

    // 联动报警输出
    BYTE	byAlarmOutLocal[16];		        // 报警输出端口(本地)
    BYTE	byAlarmOutRemote[128][16];			// 报警输出端口(前端设备)

    // 联动录像    
    BYTE byRecordChannel[128];		            // 联动的录像通道，为0-不联动 1-联动

    // 联动其他  
    BYTE byEnablePreset[128];			        // 是否调用预置点 仅用byEnablePreset[0]来判断;
    BYTE byPresetNo[128];				        // 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点 [1, 254]
    DWORD dwReserve[32];			            // 保留
} HB_NVR_MOTION, *LPHB_NVR_MOTION;




//获取nvr异常报警参数
//#define NET_SDVR_ABNORMAL_ALRM_GET_NVR  0xD8
//设置nvr异常报警参数
//#define NET_SDVR_ABNORMAL_ALRM_SET_NVR  0xD9
typedef struct	
{
    DWORD dwSize; 				            // 长度（结构体大小）
    BYTE byAbnormalAlarmType;               // 1-视频丢失 2-网络断开 3-温度过高 4-遮挡报警...            
    BYTE byChannel;                         // 通道号 (对视频丢失, 遮挡报警, 网络断开…有效)

    BYTE byEnableAbnormal;		            // 异常报警使能 0-不报警 1-报警； 
    WORD wHideAlarmAreaTopLeftX;		    // [0, 实际宽－1]（遮挡报警时有效）
    WORD wHideAlarmAreaTopLeftY;		    // [0, 实际高－1]（遮挡报警时有效）
    WORD wHideAlarmAreaWidth;			    // [16, 实际宽] （遮挡报警时有效）
    WORD wHideAlarmAreaHeight;			    // [16, 实际高] （遮挡报警时有效）

    // 联动报警输出
    BYTE	byAlarmOutLocal[16];			//报警输出端口(本地)
    BYTE	byAlarmOutRemote[128][16];	    //报警输出端口(前端设备)

    BYTE byWeekEnable;                      // 设置每天0-不使能 1-使能(若使能,只取struAlarmTime[0][0~7]对每天做设置)  
    BYTE byFullDayEnable[8];                // 完整天录像 0-不使能(缺省值) 1-使能,若此项使能,则对应的天为全天布防,不用判断时间段
    HB_SDVR_SCHEDTIME_V2 struAlarmTime[8][8];   //布防时间段, 8个时间段
    DWORD	dwHandleType;	                // 处理方式 按位  2-声音报警5-监视器最大化 //6-邮件上传

    DWORD dwReserve[32];                    // 保留
} HB_NVR_ABNORMAL, *LPHB_NVR_ABNORMAL;



//数文件导出
//#define NET_SDVR_PARAM_FILE_EXPORT      0xDA
typedef struct
{
    DWORD dwFileSize;	    // 导出文件的大小
    DWORD dwReserve;		// 保留
//    BYTE *pFileData; 	    // 参数文件数据
} HB_EXPT_REQ, *LPHB_EXPT_REQ;


//参数文件导入
//#define NET_SDVR_PARAM_FILE_IMPORT      0xDB 
typedef struct
{
    DWORD dwFileSize;	    // 导出文件的大小
    DWORD dwReserve;		// 保留
} HB_IMPT_REQ, *LPHB_IMPT_REQ;

typedef struct 
{
    BYTE   bySupportResolution[32];   	// 该参数表示nvr主机支持的输出分辨率格式，
                                        // 数组下标代表映射表序号(映射表如下)，1表示支持，0表示不支持
    BYTE    byCurResolution;			// 主机端当前输出分辨率
    BYTE    reserve[7];				    // 保留
} HB_NVR_RESOLUTION, *LPHB_NVR_RESOLUTION;
// 映射列表：
//      0-HDMI 1080P X 60HZ
// 		1-HDMI 1080P X 50HZ
// 		2-HDMI 720P X 60HZ 
// 		3-HDMI 720P X 50HZ
// 		4-VGA  1024 X 768


HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetWorkStatus(LONG lUserID, LPHB_SDVR_WORKSTATE_V2 lpWorkStatus, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetChnClientIP(LONG lUserID, LPHB_CLIENT_IP_INFO lpClientIP, DWORD* lpDataSize);

typedef struct HB_LOG_REQ_PARAM_ST
{
    WORD wBeginYear;
    BYTE byBeginMon;
    BYTE byBeginDay;

    WORD wEndYear;
    BYTE byEndMon;
    BYTE byEndDay;

    BYTE byPriType;
    BYTE bySecType;
    DWORD dwReserve[4];
}HB_LOG_REQ_PARAM, *LPHB_LOG_REQ_PARAM;

HB_SDVR_API LONG __stdcall HB_SDVR_NvrFindLog(LONG lUserID, LPHB_LOG_REQ_PARAM lpParam);

// //查找文件和日志函数返回值
// #define HB_SDVR_FILE_SUCCESS				1000	//获得文件信息
// #define HB_SDVR_FILE_NOFIND				    1001	//没有文件
// #define HB_SDVR_ISFINDING				    1002	//正在查找文件
// #define	HB_SDVR_NOMOREFILE				    1003	//查找文件时没有更多的文件
// #define	HB_SDVR_FILE_EXCEPTION				1004	//查找文件时异常
HB_SDVR_API LONG __stdcall HB_SDVR_NvrFindNextLog(LONG lLogHandle, char* pLogData, BYTE* pEncType);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrFindLogClose(LONG lLogHandle);

HB_SDVR_API LONG __stdcall HB_SDVR_NvrSerialStart(LONG lUserID, LPHB_NVR_SERIAL_START lpSerial, DWORD dwDataSize,
            void(CALLBACK *fSerialDataCallBack)(LONG lSerialHandle,char *pRecvDataBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSerialSend(LONG lSerialHandle, char* pSendData, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSerialStop(LONG lSerialHandle);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetDevInfo(LONG lUserID, LPHB_DEVICEINFO_V2 lpDevInfo, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetDevInfo(LONG lUserID, LPHB_DEVICEINFO_V2 lpDevInfo, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetPtzList(LONG lUserID, LPHB_NVR_PTZLIST lpPtz, DWORD dwDataSize, LPHB_NVR_PTZLIST_INFO lpPtzInfo, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAlarmAttr(LONG lUserID, LPHB_NVR_ALRM_PORT_ATTR lpAlarmAttr, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAlarmInCfg(LONG lUserID, LPHB_NVR_ALRMININFO lpAlarmIn, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetAlarmInCfg(LONG lUserID, LPHB_NVR_ALRMININFO lpAlarmIn, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAlarmOutCfg(LONG lUserID, LPHB_NVR_ALARMOUTINFO lpAlarmOut, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetAlarmOutCfg(LONG lUserID, LPHB_NVR_ALARMOUTINFO lpAlarmOut, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAlarmInStatus(LONG lUserID, LPHB_NVR_ALRMIN_STATUS lpAlarmInStat, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAlarmOutStatus(LONG lUserID, LPHB_NVR_ALRMOUT_STATUS lpAlarmOutStat, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetAlarmOutStatus(LONG lUserID, LPHB_NVR_ALRMOUT_STATUS lpAlarmOutStat, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetPicCfg(LONG lUserID, BYTE byChnl, LPHB_NVR_CHN_ATTR_INFO lpChlInfo, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetPicCfg(LONG lUserID, LPHB_NVR_CHN_ATTR_INFO lpChlInfo, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetRecordCfg(LONG lUserID, LPHB_RECORD_SET lpRecordSet, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetRecordCfg(LONG lUserID, LPHB_RECORD_SET lpRecordSet, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetMotDetCfg(LONG lUserID, LPHB_NVR_MOTION lpMotion, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetMotDetCfg(LONG lUserID, LPHB_NVR_MOTION lpMotion, DWORD dwDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetAbnorAlarmCfg(LONG lUserID, LPHB_NVR_ABNORMAL lpAbnor, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetAbnorAlarmCfg(LONG lUserID, LPHB_NVR_ABNORMAL lpAbnor, DWORD dwDataSize);

HB_SDVR_API LONG __stdcall HB_SDVR_NvrExpParamFile(LONG lUserID, char* pSaveFile);

#define HB_IMPORT_OK           0x01     // 导入成功
#define HB_TRANS_FILE_ERR      0x02     // 数据传输错误
#define HB_FILE_VERSION_ERR    0x03     // 文件版本错误

typedef struct HB_PARAMFILE_STATUS_ST
{
    DWORD dwFileSize;
    DWORD dwGotSize;
    DWORD dwStatus;     // 导入状态码，仅导入时有效
    DWORD dwReserve[4];
}HB_PARAMFILE_STATUS, *LPHB_PARAMFILE_STATUS;

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrExpParamFileStatus(LONG lExpHandle, LPHB_PARAMFILE_STATUS lpExpStatus);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrExpParamFileClose(LONG lExpHandle);

HB_SDVR_API LONG __stdcall HB_SDVR_NvrImpParamFile(LONG lUserID, char* pImpFileName);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrImpParamFileStatus(LONG lImpHandle, LPHB_PARAMFILE_STATUS lpImpStatus);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrImpParamFileClose(LONG lImpHandle);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrGetResolution(LONG lUserID, LPHB_NVR_RESOLUTION lpResolution, DWORD* lpDataSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_NvrSetResolution(LONG lUserID, LPHB_NVR_RESOLUTION lpResolution, DWORD dwDataSize);

#define NET_SDVR_GET_ZERO_VENCCONF					0xA8	//获取复合通道视频参数
#define NET_SDVR_SET_ZERO_VENCCONF					0xA9	//设置复合通道视频参数

// 复合通道编码参数配置
//#define MAX_CHANNUM 128
typedef enum
{
    NET_AUSTREAM_DISABLE, //视频流
    NET_AUSTREAM_ENABLE, //复合流
}NET_AUSTREAMADD_E;

typedef enum
{
    NET_QCIF, //QCIF
    NET_QVGA, //QVGA
    NET_CIF, //CIF
    NET_DCIF, //DCIF
    NET_HD1, //HD1
    NET_VGA, //VGA
    NET_FD1, //FD1
    NET_SD, //SD
    NET_HD //HD
}NET_RESOLUTION_E;

typedef enum
{
    NET_BITRATE_CHANGE, //变码率
    NET_BITRATE_NOCHANGE, //定码率
}NET_BITRATETYPE_E;

typedef enum
{
    NET_VQUALITY_BEST=0, //最高
    NET_VQUALITY_BETTER, //较高
    NET_VQUALITY_GOOD, //高
    NET_VQUALITY_NORMAL, //中
    NET_VQUALITY_BAD, //低
    NETT_VQUALITY_WORSE //最低
}NET_VQUALITY_E;

typedef struct
{
    NET_AUSTREAMADD_E byStreamType; //视频流类型
    NET_RESOLUTION_E byResolution; //视频分辨率
    NET_BITRATETYPE_E byBitrateType; //码率类型
    NET_VQUALITY_E byPicQuality; //图像质量
    DWORD dwVideoBitrate; //视频码率 实际码率
    WORD dwVideoFrameRate; //帧率 PAL 2-30 N 2-30
    WORD quant;//量化因子 1-31
}HB_SDVR_VENC_CONFIG, *LPHB_SDVR_VENC;

typedef struct 
{
    DWORD 					enable; // 零通道使能，1-启用，0-不启用
    char 					chlist[MAX_CHANNUM_EX];// 零通道画面格式输出, 对应通道按数组下标从0开始表示, 0-不选中, 1-选中
    HB_SDVR_VENC_CONFIG 			venc_conf; //编码参数
    DWORD 					reserve;//保留
}HB_SDVR_ZERO_VENC_CONFIG, *LPHB_SDVR_ZERO_VENC_CONFIG;

HB_SDVR_API LONG __stdcall HB_SDVR_ZeroRealPlay(LONG lUserID, LPHB_SDVR_CLIENTINFO lpClientInfo);

HB_SDVR_API BOOL __stdcall HB_SDVR_ZeroStopRealPlay(LONG lRealHandle);

HB_SDVR_API BOOL __stdcall HB_SDVR_ZeroGetConfig(LONG lUserID, DWORD dwCommand, LPVOID lpOutBuffer, LPDWORD lpOutBufferSize, LPDWORD lpReturned);

HB_SDVR_API BOOL __stdcall HB_SDVR_ZeroSetConfig(LONG lUserID, DWORD dwCommand, LPVOID lpInBuffer, DWORD dwBufferSize, LPDWORD lpReturned);


typedef struct TAG_HB_SDVR_VOD_PARAM 
{
    BYTE        byChannel;                  // 通道号 [0, n-1],n:通道数
    BYTE        byType;                     // 录像类型:1-手动，2-定时，4-移动，8-报警，0xFF-全部
    WORD        wLoadMode;                  // 回放下载模式 1-按时间， 2-按名字
    union
    {
        struct
        {
            HB_SDVR_TIME struStartTime;         // 最多一个自然天
            HB_SDVR_TIME struStopTime;          // 结束时间最多到23:59:59,
            // 即表示从开始时间开始一直播放
            char cReserve[16];
        }byTime;

        BYTE    byFile[64];                 // 是否够长？
    }mode;

    DWORD dwReserve[4];                    // 保留 
}HB_SDVR_VOD_PARAM, *LPHB_SDVR_VOD_PARAM;

HB_SDVR_API LONG __stdcall HB_SDVR_Vod(LONG lUserID, LPHB_SDVR_VOD_PARAM pVodParam, HWND hWnd);

#define HB_SDVR_VOD_PLAYSTART   1
#define HB_SDVR_VOD_PLAYPAUSE   2
#define HB_SDVR_VOD_PLAYFAST    3
#define HB_SDVR_VOD_PLAYSLOW    4
#define HB_SDVR_VOD_PLAYNORMAL  5
#define HB_SDVR_VOD_PLAYFRAME   6
#define HB_SDVR_VOD_PLAYSETPOS  7
#define HB_SDVR_VOD_PLAYGETPOS  8

HB_SDVR_API BOOL __stdcall HB_SDVR_VodControl(LONG lVodHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

HB_SDVR_API BOOL __stdcall HB_SDVR_StopVod(LONG lVodHandle);

//////////////////////////////////////////
////////IPC新协议
/////////////////////////////////////////
#define HB_IPCCFG_THERMAL_IMAGING   1
#define HB_IPCCFG_IP_FILTER         2       // ip地址过滤
#define HB_IPCCFG_BLC               3       // 背光补偿
#define HB_IPCCFG_PROTOCL           4       // 协议

typedef struct TAG_HB_SDVR_IPC_THERMAL_IMAGING
{
    DWORD   dwSize;                         // 结构体长度                 
    char    shutter_correct;                // 快门校正 0:not support 1:close 2:open      
    char    electronic_enlarge;             // 电子放大 0:not support 1:normal_display 2:enlarge_display
    char    pseudo_colormode;               // 伪彩模式 0:not support 1:white hot 2:black hot 3:fusion 4:rainbow 5:globow
                                            // 6:ironbow1 7:ironbow2 8:sepia 9:color1 10:color2 11:icefire 12:rain
    char    auto_correct_switch;            // 自动校正开关 0:not support 1:close 2:open
    char    auto_agcmode;                   // 自动增益模式 0:不支持 1:自动增益 2:线性直方图 3:一次亮度 4:自动亮度 5:手动
    char    contrast;                       // 对比度 （0～255）
    short   light;                          // 亮度 -1:不支持
    short   light_bias;                     // 亮度偏置 -1:不支持
    short   reserve[3];                     // 保留
}HB_SDVR_IPC_THERMAL_IMAGING, *LPHB_SDVR_IPC_THERMAL_IMAGING;

typedef struct TAG_HB_SDVR_IPC_IP_FILTER
{
    DWORD   dwSize;                 // sizeof(HB_SDVR_IPC_IP_FILTER)
    char    cIPFilter;              // 局域网IP地址过滤 0-不支持 1-打开 2-关闭
    char    cIPRule;                // 规则 1-允许通过 2-不允许通过
    char    cPortFilter;            // 端口过滤 0-不支持 1-打开 2-关闭
    char    cPortRule;              // 规则 1-允许通过 2-不允许通过
    DWORD   dwIPBegin;              // 局域网IP起始地址
    DWORD   dwIPEnd;                // 局域网IP结束地址，结束地址的值要大于起始地址，
                                    // 如果结束地址为空，则认为只过滤起始地址
    DWORD   dwPortBegin;            // 过滤端口起始
    DWORD   dwPortEnd;              // 过滤端口结束
    DWORD   dwReserve[3];           // 保留
}HB_SDVR_IPC_IP_FILTER, *LPHB_SDVR_IPC_IP_FILTER;

typedef struct TAG_HB_SDVR_IPC_BLC
{
    DWORD   dwSize;                 // sizeof(HB_SDVR_IPC_BLC)
    BYTE    byBLCEnable;            // 背光补偿 0-不支持 1-打开 2-关闭
    BYTE    byReserve[3];           // 保留
}HB_SDVR_IPC_BLC, *LPHB_SDVR_IPC_BLC;

typedef struct TAG_HB_SDVR_IPC_PROTOCL
{
    DWORD dwSize;
    BYTE byProtocl;                 // 0不支持， 1-7000sdk, 2-ONVIF(码流不带汉邦帧头)
    BYTE byReserve[3];
}HB_SDVR_IPC_PROTOCL, *LPHB_SDVR_IPC_PROTOCL;

typedef struct TAG_HB_SDVR_IPC_CFG
{
    DWORD	dwIPCCfgType;	        // 1:STRUCT_IPC_THERMAL_IMAGING 2:...
    DWORD	dwSize;		            // sizeof(STRUCT_IPC_THERMAL_IMAGING)...
    union
    {
        HB_SDVR_IPC_THERMAL_IMAGING thermal;
        HB_SDVR_IPC_IP_FILTER IPFilter;
        HB_SDVR_IPC_BLC blc;
        HB_SDVR_IPC_PROTOCL protocl;
    }cfg;
}HB_SDVR_IPC_CFG, *LPHB_SDVR_IPC_CFG;

HB_SDVR_API BOOL __stdcall HB_SDVR_SetIPCCfg(LONG lUserID, LPHB_SDVR_IPC_CFG lpCfg, DWORD dwSize);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetIPCCfg(LONG lUserID, LPHB_SDVR_IPC_CFG lpCfg, DWORD* pSize);

typedef struct TAG_HB_SDVR_IPSERVER
{
    DWORD   dwSize;
    DWORD   dwIP;                   // IPServer IP地址
    DWORD   dwPort;                 // IPServer 端口
    BYTE    byRegID[64];            // 设备注册码
    char    reserve[4];
}HB_SDVR_IPSERVER, *LPHB_SDVR_IPSERVER;

HB_SDVR_API BOOL __stdcall HB_SDVR_SetIPServer(LONG lUserID, LPHB_SDVR_IPSERVER lpIPServer);

HB_SDVR_API BOOL __stdcall HB_SDVR_GetIPServer(LONG lUserID, LPHB_SDVR_IPSERVER lpIPServer);




typedef enum                    //IPC命令分类命令
{
    IPC_VIDEO_CMD = 0,      //IPC音视频命令
    IPC_NET_CMD,            //IPC网络命令
    IPC_STORE_CMD,          //IPC存储命令
    IPC_ALARM_CMD,          //IPC报警命令 
    IPC_MANAGE_CMD,         //IPC管理命令
    IPC_PRI_CMD_MAX
}HB_SDVR_IPC_PRI_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//音视频命令
//////////////////////////////////////////////////////////////////////////////
typedef enum                    
{
    IPC_IMAGE_PARAM = 0,      //IPC图像参数 
    IPC_VIDEO_PARAM,          //IPC视频参数  
    IPC_VIDEO_ENCODE,         //IPC视频编码参数  
    IPC_PICTURE_SNAP,         //IPC图像抓拍参数 
    IPC_OSD_OVERLAY,          //IPC字符叠加参数
    IPC_MASK,                 //IPC遮挡参数   
    IPC_ADVANCE_PARAM,        //IPC高级参数  
    IPC_AUDIO_IN_PARAM,       //IPC音频输入参数
    IPC_AUDIO_OUT_PARAM,      //IPC音频输出参数
    IPC_VIDEO_CMD_MAX
}HB_SDVR_IPC_VIDEO_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//网络命令
//////////////////////////////////////////////////////////////////////////////
typedef enum                    
{
    IPC_IP_PARAM = 0,           //IPC 有线网络参数   
//     IPC_WLAN,                   //IPC 无线网络参数
//     IPC_DDNS,                   //IPC DDNS参数    
    IPC_PPPOE,                  //IPC PPPOE参数   
    IPC_E_MAIL,                 //IPC E_MAIL参数   
//    IPC_UPNP,                   //IPC UPNP参数  
    IPC_FTP,                    //IPC FTP参数   
//    IPC_NAS,                    //IPC NAS参数  
//    IPC_AUTO_REGIST,            //IPC 自动注册参数
    IPC_PLATFORM,               //IPC 平台服务器信息    
//    IPC_IP_FILTER,              //IPC IP地址过滤参数   
    IPC_NET_CMD_MAX
}HB_SDVR_IPC_NET_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//存储命令
//////////////////////////////////////////////////////////////////////////////
typedef enum 
{   
    IPC_TIME_RECORD = 0,        //IPC定时录像参数
    IPC_RECORD_MODE,          //存储方式
    IPC_DISK_CFG,           //IPC存储设备状态
    IPC_STORE_CMD_MAX       //存储类命令最大值
}IPC_STORE_CMD_TYPE_E;

//////////////////////////////////////////////////////////////////////////////
//报警命令
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
    IPC_MOTION = 0,     //IPC移动侦测参数
    IPC_ALARMIN,        //IPC报警输入参数
    IPC_ALARMOUT,       //IPC报警输出参数
    IPC_NET_BUG,        //IPC网络故障报警参数
    IPC_STORE_BUG,      //IPC存储故障报警参数
    IPC_ALARM_CMD_MAX   //报警类命令最大值
}IPC_ALARM_CMD_TYPE_E;


//////////////////////////////////////////////////////////////////////////////
//管理类命令
//////////////////////////////////////////////////////////////////////////////
typedef enum 
{
    IPC_DEVICE_INFO = 0,    //IPC设备信息    
    IPC_AUTO_MAINTAINING,   //IPC自动维护参数
    IPC_MANAGE_CMD_MAX      //设备管理类命令最大值
} IPC_MANAGE_CMD_TYPE_E;




/*时间段*/
typedef struct
{
    WORD uYear;    //年
    BYTE uMonth;   //月
    BYTE uDay;     //日
    BYTE uWeek;    //星期
    BYTE uHour;    //小时
    BYTE uMin;     //分钟
    BYTE uSec;     //秒
}HB_SDVR_IPC_SYS_TIME;

typedef struct
{
    BYTE uStartHour;     //开始
    BYTE uStartMin;
    BYTE uEndHour;       //结束
    BYTE uEndMin;
}HB_SDVR_IPC_TIME_PERIOD;

typedef struct
{
    BYTE uSelect[4];        //0-no     1-yes
    HB_SDVR_IPC_TIME_PERIOD Period[4];
}HB_SDVR_IPC_TIME_ITEM;

typedef struct
{
    int     nStatus;    //0-off, 1-on
    HB_SDVR_IPC_TIME_ITEM  Item[8];   // 0-7: everyday, monday...sunday
}HB_SDVR_IPC_TIME_SCHEDULE;
/*视频、音频*/
typedef struct
{                                                                      
    HB_SDVR_IPC_TIME_PERIOD  Time;         
    short    sBrightValue;        
    short    sContrastValue;      
    short    sSaturationValue;    
    short    sHueValue;           
    short    sSharpness;   
    short    sReserve;        
}HB_SDVR_IMAGE_PARAM_ITEM;

typedef struct
{                                                                     
    int    nLens;
    int   nChannelid;
    HB_SDVR_IMAGE_PARAM_ITEM Item[3];      
}HB_SDVR_IPC_IMAGE_PARAM;

typedef struct
{
    int nLensIris;           
    int nLensIndex;
    BYTE    uLensVal[16][32];                            
}HB_SDVR_IPC_LENS;

typedef struct
{   
    int  nAeContrl;
    int  nShutterIndex;        
    int  nShutterVal[32]; 
    int  nAgcIndex;          
    int  nAgcVal[32]; 
}HB_SDVR_IPC_AE;

typedef struct
{
    int nMaxValue; 
    int nMinValue;
    int nCurValue;
}HB_SDVR_IPC_ICR_ABILITY;

typedef struct
{
    int  nDaynightModel;     
    int  nIcrEnable;                      
    int  nLightRange;
    HB_SDVR_IPC_ICR_ABILITY BlackwhiteValue;
    HB_SDVR_IPC_ICR_ABILITY ColorValue;
    int  nMinInterval;      
    HB_SDVR_IPC_TIME_PERIOD TimeRange[2]; 
}HB_SDVR_IPC_DAY_NIGHT;

typedef struct
{
    int    nLens;
    int   nChannelid;              
    HB_SDVR_IPC_AE           AeModel;                        
    HB_SDVR_IPC_DAY_NIGHT    Daynight;                                   
    HB_SDVR_IPC_LENS         IrisModel;          
    int        nImageFlip;
    int        nImagSpin;          
    int        nSceneModel;            
}HB_SDVR_IPC_VIDEO_PARAM;

typedef struct
{
    int nResolutionIndex;      
    int nResolution[32][2];   
}HB_SDVR_IPC_RESOLUTION_PARAM;

typedef struct
{
    short sMinFramerate;
    short sMaxFramerate; 
    short sCurFramerate; 
    short sReserve;   
}HB_SDVR_IPC_FRAMERATE;

typedef struct
{
    int            nEnable;
    int            nEncodeType;          
    short            sStreamControl;       
    short            sIFrame;                     
    int            nVideoBitrate;        
    HB_SDVR_IPC_RESOLUTION_PARAM Resolution;           
    HB_SDVR_IPC_FRAMERATE        Framerate;            
}HB_SDVR_IPC_STREAM_PARAM;

typedef struct
{
    int    nLens;
    int   nChannelid;
    int    nEncodeModel;               
    int    nStreamType;                                 
    HB_SDVR_IPC_STREAM_PARAM Stream[4];   
    int     nReserved;      
}HB_SDVR_IPC_VIDEO_ENCODE;

typedef struct
{
    int nPosx;
    int nPosy;
    int nReserved;
}HB_SDVR_IPC_OSD_POS;

typedef struct
{
    int  nEnable;             
    HB_SDVR_IPC_OSD_POS OsdPos;            
    char cOsdStrings[128];   
    int  nReserved;          
}HB_SDVR_IPC_OSD_USERDEF;

typedef struct
{
    int    nLens;
    int   nChannelid;
    int   nOsdEnable;                   
    short   sOsdAttribute;                
    short   sOsdAddModel;                
    short   sChNameEnable;            
    short   sTimeInfoEnable;           
    short   sWeekDisplay;              
    short   sTimeFormat;                 
    char    cChName[32];                 
    HB_SDVR_IPC_OSD_POS  ChNamePos;                  
    HB_SDVR_IPC_OSD_POS  TimePos;                     
    HB_SDVR_IPC_OSD_USERDEF OsdUserdef[8];            
}HB_SDVR_IPC_OSD_OVERLAY;

typedef struct
{
    int nStartx;           
    int nStarty;             
    int nWidth;           
    int nHeight;          
}HB_SDVR_IPC_MASK_AREA;

typedef struct
{
    int   nLens;
    int   nChannelid;
    int   nMaskEnable;
    HB_SDVR_IPC_MASK_AREA Maskarea[8];  
}HB_SDVR_IPC_MASK;


/*网络*/
typedef struct
{
    BYTE   uIp[4];
    BYTE   uMask[4];
    BYTE   uGateway[4];
    BYTE   uDns[4];
    BYTE   uDnsBak[4];
}HB_SDVR_IPC_IPV4;

typedef struct
{
    WORD uIp[8];
    BYTE uGateway[16];       
    BYTE uDns[16];           
    BYTE uDnsBak[16];       
    BYTE uSubnetPrefix;     
}HB_SDVR_IPC_IPV6;

typedef struct
{
    int    nLens;
    BYTE   uNetInterface;      
    BYTE   uNetModel;          
    BYTE   uMacAddr[6];          
    HB_SDVR_IPC_IPV4     Ipv4;               
    HB_SDVR_IPC_IPV6     Ipv6;               
    int    nListenPort;        
    int    nHttpPort;          
    int    nMulticast;          
}HB_SDVR_IPC_IP_PARAM;

typedef struct
{
    int    nLens;
    int    nChannelid;
    HB_SDVR_IPC_TIME_SCHEDULE Schedule;
    int    nReserved;     
}HB_SDVR_IPC_TIME_RECORD;
 

typedef struct
{
    int    nLens;               
    int    nChannelid;         
    int    nCoverDelete;         
    char   cManualRcd[8];           
    char   cTimeRcd[8];             
    char   cLinkageRcd[8];          
}HB_SDVR_IPC_RECORD_MODE;
typedef struct
{
    char  cDevName[16];           
    char  cStatus[32];             
    unsigned int uDiskcapacity;          
    unsigned int uDiskFree;              
}HB_SDVR_IPC_DISK_PARAM;
typedef struct
{   
    int    nLens;             
    int    nDisknum;          
    HB_SDVR_IPC_DISK_PARAM Diskinfo[12];  
}HB_SDVR_IPC_DISK_CFG;





typedef struct 
{
    int nLens;
    int nEnable;                
    int     nMd5Auth;               
    int     nUseIpv6;               
    int     nUseSsl;                
    int     nUseStarttls;           
    short     sAccessoryEnable;       
    WORD    uPort;                   
    char    cSmtpServer[128];       
    char    cUserName[32];           
    char    cPwd[32];               
    char    cSendPerson[128];       
    char    cRecvPerson[256];       
    int     nSendPeriod;            
    int     nSnapEnable;            
    char    cMailTopic[32];         
}HB_SDVR_IPC_E_MAIL; 


typedef struct
{
    int nLens;
    int nPppoeEnable;    
    int nAutoCon;       
    int nState;      
    char cUserName[32]; 
    char cPwd[32];   
    int  nPpppoeSave;      
    BYTE    uIpv4[4];    
    BYTE    uGatewayv4[4];           
    WORD    uIpv6[8];                
    BYTE    uGatewayv6[16];    
}HB_SDVR_IPC_PPPOE;




typedef struct 
{
    int  nRecord;   
    int  nDelayTime;  
    int  nRecordTime;  
    int  nReserved[2];  
}HB_SDVR_IPC_LINKAGE_RECORD;

typedef struct 
{
    int nPtz;     
    int nPtzItem;       
    int nPtzAddr;    
    int nReserved;   
}HB_SDVR_IPC_LINKAGE_PTZ;
typedef struct
{
    int nAlarmOut;      
    int nAlarm;          
    int nDelayTime;     
    int nContinueTime; 
}HB_SDVR_IPC_LINKAGE_ALARM;

typedef struct
{
    int     nSnap;     
    short   sDelayTime;    
    short   sPicNum;       
    int     nReserved;       
}HB_SDVR_IPC_LINKAGE_SNAP;

typedef struct 
{
    int  nEmail;        
    int  nDelayTime;    
    int  nReserved;   
}HB_SDVR_IPC_LINKAGE_MAIL;

typedef struct
{ 
    HB_SDVR_IPC_LINKAGE_MAIL   Mail;     
    HB_SDVR_IPC_LINKAGE_SNAP   Snap;     
    HB_SDVR_IPC_LINKAGE_ALARM  Alarm;   
    HB_SDVR_IPC_LINKAGE_PTZ    Ptz;      
    HB_SDVR_IPC_LINKAGE_RECORD Record;  
}HB_SDVR_IPC_LINKAGE;
typedef struct 
{
    int    nLens;
    int    nChannelid;
    int             nMotionEnable;            
    int             nMotionBlock[18];        
    int             nSensitivity;             
    int             nReserved;                
    HB_SDVR_IPC_TIME_SCHEDULE  MonitorTime;            
    HB_SDVR_IPC_LINKAGE        LinkageOut;             
}HB_SDVR_IPC_MOTION;

typedef struct
{
    HB_SDVR_IPC_TIME_SCHEDULE  MonitorTime;    
    int                        nAlarmInType;   
    HB_SDVR_IPC_LINKAGE        LinkageOut;
}HB_SDVR_IPC_ALARMIN_PARAM;
typedef struct
{
    int                   nLens;
    HB_SDVR_IPC_ALARMIN_PARAM    AlarmIn[4];    
}HB_SDVR_IPC_ALARMIN;
typedef struct 
{
    int  nAlarmTime;       
    HB_SDVR_IPC_TIME_SCHEDULE Time;  
}HB_SDVR_IPC_ALARMOUT_PARAM;
typedef struct 
{
    int                   nLens;
    HB_SDVR_IPC_ALARMOUT_PARAM  AlarmOut[4];  
}HB_SDVR_IPC_ALARMOUT;
typedef struct 
{
    int  nLens;
    int  nEnable;
    short sRecordEnable; 
    short sAlarmEnable;        
    short sRecordTime;  
    short sAlarmoutTime;
}HB_SDVR_IPC_NET_BUG;
typedef struct
{
    short sEnable;         
    short sEmail;          
    short sAlarmoutEnable; 
    short sAlarmoutDelay;  
}HB_SDVR_IPC_SAVE_BUG_PROCESS;
typedef struct 
{
    int  nLens;
    HB_SDVR_IPC_SAVE_BUG_PROCESS NoSd;     
    HB_SDVR_IPC_SAVE_BUG_PROCESS NoFreeSd;   
    HB_SDVR_IPC_SAVE_BUG_PROCESS ErrorSd;	
}HB_SDVR_IPC_STORE_BUG;


typedef union
{
    HB_SDVR_IPC_MOTION     Motion;
    HB_SDVR_IPC_ALARMIN    Alarmin;
    HB_SDVR_IPC_ALARMOUT   Alarmout;
    HB_SDVR_IPC_NET_BUG    NetBug;
    HB_SDVR_IPC_STORE_BUG  StoreBug;
}HB_SDVR_IPC_ALARM_CFG_U;

typedef struct
{
    int  nLens;
    char cDevName[32];         
    char cdDevType[32];       
    char cSoftVersion[32];    
    char cImprint[32];          
    BYTE            uSn[4];               
    BYTE            uMacAddr[6];       
    BYTE            uReserved[2];
}HB_SDVR_IPC_DEVICE_INFO;
typedef struct
{
    int  nLens;
    short  sAutoReboot;  
    short  sStyle;         
    HB_SDVR_IPC_SYS_TIME RebootTime; 
}HB_SDVR_IPC_AUTO_MAINTAINING;
typedef union
{
    HB_SDVR_IPC_DEVICE_INFO        DevInfo;
    //HB_SDVR_IPC_NTP_PARAM          NtpParam;
    HB_SDVR_IPC_AUTO_MAINTAINING   AutoMaintaining;
}HB_SDVR_IPC_MANAGE_CFG_U;

typedef struct
{
    int        nLens;    
    int        nChannelid;     
    int        nSnapEnable;         
    int        nSnapType;         
    int        nSnapResIndex;        
    int        nSnapRes[32][2];          
    int        nPictureFormat;     
    int        nPictureQuality;     
    int        nSnapSpeed;          
    HB_SDVR_IPC_TIME_SCHEDULE Schedule;    
}HB_SDVR_IPC_PICTURE_SNAP;

typedef struct
{
    int             nLens;    
    int             nChannelid;        
    char            cAutoDropframe;           
    char            cAntiFlicker;              
    char            cWdr;                       
    char            cColorStyle;               
    char            cDenoise3d;                
    BYTE   			byDenoise3dVal; 
    char            cTimeDomain;                
    BYTE   			bySpaceDomain; 
    char            cDenoise2d;                
    char            cDeFog; 
    char            cDeformityAdjust;          
    char            cPseudoColor;  
    char            cFocusSpeed;               
    char            cDigitalFoucus;            
    char            cBlc;                      
    char            cAutoFoucus;               
    char            cCurframeDenoise;          
    char            cVoutType;  
}HB_SDVR_IPC_ADVANCE_PARAM;


typedef struct
{
    int             nLens;    
    int             nChannelid; 
    char            cAudioInCh;
    char            cAudioEnable;   
    char            cVolume;          
    char            cCompressType;       
    int             nBitrateIndex;       
    DWORD           dwBitrate[16];    
    int             nSamplerateIndex;    
    DWORD           dwSamplerate[16];
}HB_SDVR_IPC_AUDIO_IN_PARAM;

typedef struct
{
    int             nLens;    
    int             nChannelid; 
    char            cAudioOutCh;
    char            cAudioEnable;   
    char            cVolume;          
    char            cCompressType;       
    int             nBitrateIndex;       
    DWORD           dwBitrate[16];    
    int             nSamplerateIndex;    
    DWORD           dwSamplerate[16];  
}HB_SDVR_IPC_AUDIO_OUT_PARAM;

typedef struct
{
    int             nLens;                
    short           sEnable;              
    WORD            uPort;              
    char     cServerAddress[128];    
    char     cUsername[32];          
    char     cPwd[32];               
    char     cSavePath[128];   
}HB_SDVR_IPC_FTP;
typedef struct 
{
    char    cDeviceId[32];             
    int     nDevicePort;               
    char    cDeviceDomainName[64];    
    char    cDevicePwd[32];            
    int     nDeviceExpires;            
    int     nDeviceAlarminNum;        
    char    cDeviceAlarminId[8][32]; 
}HB_SDVR_IPC_GB28181_DEVICE_INFO;
typedef struct 
{
    char    cSmssvrIp[32];            
    int     nSmssvrPort; 
}HB_SDVR_IPC_GB28181_SMS_SERVER_INFO;
typedef struct 
{
    char    cSipsvrIp[32];            
    char    cSipsvrId[32];            
    int     nSipsvrPort;              
    char    cSipsvrDomainName[64]; 
}HB_SDVR_IPC_GB28181_SIP_SERVER_INFO;

typedef struct
{
    char    cUsername[32];               
    char    cPassword[16];              
    int     nProtocolPort;  
}HB_SDVR_IPC_PLATFORM_INFO;
typedef struct
{
    HB_SDVR_IPC_GB28181_DEVICE_INFO         DevInfo;         
    HB_SDVR_IPC_GB28181_SMS_SERVER_INFO     SmsserverInfo;  
    HB_SDVR_IPC_GB28181_SIP_SERVER_INFO     SipserverInfo;
}HB_SDVR_IPC_GB28181_INFO;

typedef struct
{
    int             nLens;                
    int             nProtocolType;              
    union
    {
        HB_SDVR_IPC_PLATFORM_INFO   Onvif;
        HB_SDVR_IPC_PLATFORM_INFO   Psia;
        HB_SDVR_IPC_GB28181_INFO    Gb28181;
    }PlatformCfg;
}HB_SDVR_IPC_PLATFORM;

typedef union
{
    HB_SDVR_IPC_IP_PARAM           IpParam;
    //    IPC_WLAN               wlan;
    //    IPC_DDNS               ddns;
    HB_SDVR_IPC_PPPOE              Pppoe;
    HB_SDVR_IPC_E_MAIL             Email;
    //    IPC_UPNP               upnp;
    HB_SDVR_IPC_FTP                Ftp;
    //    IPC_NAS                nas;
    //    IPC_AUTO_REGIST        auto_regist;
    HB_SDVR_IPC_PLATFORM           Platform;
    //    IPC_IP_FILTER          ip_filter;
}HB_SDVR_IPC_NET_CFG_U;
typedef union
{    
    HB_SDVR_IPC_TIME_RECORD   TimeRecord;
    HB_SDVR_IPC_RECORD_MODE   RecordMode;
    HB_SDVR_IPC_DISK_CFG      DiskCfg;
}HB_SDVR_IPC_STORE_CFG_U;

typedef union
{
    HB_SDVR_IPC_IMAGE_PARAM           ImageParam;
    HB_SDVR_IPC_VIDEO_PARAM           VideoParam;
    HB_SDVR_IPC_VIDEO_ENCODE          VideoEncode;
    HB_SDVR_IPC_PICTURE_SNAP          PictureSnap;
    HB_SDVR_IPC_OSD_OVERLAY           OsdOverlay;
    HB_SDVR_IPC_MASK                  Mask;
    HB_SDVR_IPC_ADVANCE_PARAM         AdvanceParam;
    HB_SDVR_IPC_AUDIO_IN_PARAM        AudioInParam;
    HB_SDVR_IPC_AUDIO_OUT_PARAM       AudioOutParam;
}HB_SDVR_IPC_VIDEO_CFG_U;



typedef struct
{
    int   nPriCmdType; //对应HB_SDVR_IPC_PRI_CMD_TYPE_E
    int   nSecCmdType; //对应HB_SDVR_IPC_VIDEO_CMD_TYPE_E的子命令
    int   nChannelid;
}HB_SDVR_IPC_CMD, *PHB_SDVR_IPC_CMD;

typedef struct
{
    int   nPriCmdType; //对应HB_SDVR_IPC_PRI_CMD_TYPE_E
    int   nSecCmdType; //对应HB_SDVR_IPC_VIDEO_CMD_TYPE_E的子命令
    int   nSecCmdParaSize;  
    union
    {
        HB_SDVR_IPC_VIDEO_CFG_U VideoCfg;
        HB_SDVR_IPC_NET_CFG_U   NetCfg;
        HB_SDVR_IPC_STORE_CFG_U StoreCfg;
        HB_SDVR_IPC_ALARM_CFG_U AlarmCfg;      
        HB_SDVR_IPC_MANAGE_CFG_U ManageCfg;
    }IpcCfg;
    int nReserved[2];
}HB_SDVR_IPC_CONFIG, *PHB_SDVR_IPC_CONFIG; 



HB_SDVR_API BOOL __stdcall HB_SDVR_SetIPCParameterConfig( IN LONG lUserID, IN const HB_SDVR_IPC_CONFIG* pIpcConfig);

// HB_SDVR_API BOOL __stdcall HB_SDVR_GetIPCParameterConfig( LONG lUserID, IN const HB_SDVR_IPC_CMD* pIpcCmd,
//                                                          OUT HB_SDVR_IPC_CONFIG* pIpcConfig );

HB_SDVR_API BOOL __stdcall HB_SDVR_GetIPCParameterConfig( LONG lUserID,IN OUT HB_SDVR_IPC_CONFIG* pIpcConfig );


HB_SDVR_API LONG __stdcall HB_SDVR_SetEndecryptPassword(LONG lUserID, char* pStrPwd);

typedef struct TAG_HB_SDVR_QUERY_MONTH
{
    BYTE    byChannel;          // 通道号[0,n-1], n:通道数
    BYTE    byType;             // 查询录像类型  0x01:手动 0x02:定时 0x04:移动 0x08:报警 0xFF所有
    BYTE    byYear;             // 查询年份[0, 63], 实际年份-2000 
    BYTE    byMonth;            // 查询月份[1, 12]
    BYTE    byReserver[32];
}HB_SDVR_QUERY_MONTH, *LPHB_SDVR_QUERY_MONTH;

typedef struct TAG_HB_SDVR_RECFILE_MONTHINFO
{
    BYTE    byDate[31];         // 返回有录像数据的日期， 数据[n]代表某月的第n+1天, 0:无录像 1:有
    BYTE    byReserver[9];      // 保留
}HB_SDVR_RECFILE_MONTHINFO, *LPHB_SDVR_RECFILE_MONTHINFO;

HB_SDVR_API BOOL __stdcall HB_SDVR_QueryRecFileByMonth(LONG lUserID, LPHB_SDVR_QUERY_MONTH lpQuery, LPHB_SDVR_RECFILE_MONTHINFO lpInfo);


typedef  struct 
{ 
    DWORD  dwResolution;		//分辨率值，如：0x07800438，高两字节(0x0780=1920)、低两字节(0x0438=1080)
    DWORD  dwVideoBitrate_support [32];	//该分辨率下支持的码率范围，每一个数组代表一种码率，数组的值
    //如果为0，表示该数组未用到，不为0，表示支持的码率值，单位为Kbit/s
    WORD  wVideoFrameRate_min;		//该分辨率下的最小帧率
    WORD  wVideoFrameRate_max;	//该分辨率下的最大帧率
    BYTE  byPicQuality_support[10];	//该分辨率下支持的图像质量等级,每个数组代表一种图像质量等级，
    //0数组是最高， 1数组是较高， 2数组是高， 3数组是中，4数组是低， 
    //5数组是最低，该数组为1，表示支持该种图像质量
    BYTE  reserve[2]; 				//保留
} STRUCT_SDVR_RESOLUTION;


//发送的时候只需要填写byChannel,dwSize,byCompressionType这三个字段)
typedef  struct 
{
    DWORD  dwSize;				//结构体大小
    BYTE  byChannel;			//通道号
    BYTE  byCompressionType;	//码流，0-主码流，1-子码流1，子码流2…
    BYTE  byCompression_support;	//支持的码流，每位代表一种码流，该位为1表示支持该码流， 从低位开始，								//0位代表主码流，第1位代表子码流1，第2位代表子码流2...
    BYTE  byBitrateTypeIndex;		//当前码流类型索引值，表示基于dwBitrateType中的位置,
    //例如dwBitrateTypeIndex = 0，则当前码流类型为dwBitrateType的第0位
    //所指定的码流类型，即变码流。
    BYTE  byBitrateType_support;	//支持的码流类型，每一位代表一种码流类型，该位为1表示支持该码流类型，
    //从低位开始，第0位是变码流，第1位是定码流
    BYTE  byRecordType_index;	//当前录像类型索引值
    BYTE  byRecordType_support;	//支持的录像类型，每位代表一种录像类型，该位为1表示支持该类型，
    //从低位开始，第0位手动录像，第1位定时录像，第2位移动录像，
    //第3位报警录像，……第15位所有录像
    BYTE  byAudioflag;			//当前是否有音频，0-无音频，1-有音频
    BYTE  byAudio_support;		//是否支持音频，0-不支持，1-支持，当不支持音频时，byAudioflag只能为0
    BYTE  byPicQuality;			//当前图像质量， 0--最高， 1-较高， 2-高， 3-中，4-低， 5-最低
    WORD  wVideoFrameRate;		//当前帧率值
    DWORD  dwVideoBitrate;		//当前码率值，单位为Kbit/s
    BYTE  reserve[3];				//保留
    BYTE  byResoluIndex;			//当前分辨率索引值，表示基于byResolution_support中的位置
    STRUCT_SDVR_RESOLUTION  Resolution_support[16];		//支持的分辨率，最大16种分辨率，每个结构
    //体代表一种分辨率及该分辨率下支持的码率，帧率，图像质量范围，该结构
    //体的dwResolution为0，表示该结构体未用到
} STRUCT_SDVR_COMPRESSINFO_SUPPORT,* LPSTRUCT_SDVR_COMPRESSINFO_SUPPORT;



HB_SDVR_API BOOL __stdcall HB_SDVR_GetChlParamSupport( IN LONG lUserID, IN OUT LPSTRUCT_SDVR_COMPRESSINFO_SUPPORT pCompressinfoSupport );



typedef struct 
{
    BYTE  sUserName[32];		//用户名
    BYTE  sPassword[32];			//密码
    BYTE  byLocalRight[32];		//本地权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    //数组1-常规设置、数组2-录像设置、数组3-输出设置、数组4-报警设置、
    //数组5-串口设置、数组6-网络设置、数组7-录像回放、数组8-系统管理、
    //数组9-系统信息、数组10-报警清除、数组11-云台控制、数组12-关机重启、
    //数组-13-USB升级、数组14-备份
    BYTE  byLocalChannel[128];	//本地用户对通道的操作权限，最大128个通道，0-无权限，1-有权限
    BYTE  byRemoteRight[32];		//远程登录用户所具备的权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    //数组1-显示设置、数组2-录像参数、数组3-定时录像、数组4-移动录像、
    //数组5-报警录像、数组6-网络参数、数组7-云台设置、数组8-存储管理
    //数组9-系统管理、数组10-信息查询、数组11-手动录像、数组12-回放、
    //数组-13-备份、数组14-视频参数、数组-15-报警清除、数组16-远程预览
    BYTE  byRemoteChannel[128];	//远程登录用户对通道的操作权限，最大128个通道，0-无权限，1-有权限
    DWORD  dwUserIP;			//用户IP地址(为0时表示允许任何地址)
    BYTE  byMACAddr[8];		//物理地址
}STRUCT_USERINFO;

typedef struct 
{
    BYTE  sUserName[32];		//用户名，以’\0’结束字符串
    BYTE  sPassword[32];			//密码，以’\0’结束字符串
    BYTE  byLocalRight[32];		//本地权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    //数组1-手动录像、数组2-手动报警、数组3-录像回放、数组4-备份管理、
    //数组5-磁盘管理、数组6-系统关机、数组7-系统重启、数组8-云台控制、
    //数组9-报警清除、数组10-常规设置、数组11-输出设置、数组12-录像设置、
    //数组13-定时录像、数组14-报警设置、数组15-串口设置、数组16-云台设置、
    //数组17-网络设置、数组18-系统信息、数组19-录像状态、数组20-报警状态、
    //数组21-在线状态、数组22-日志查询、数组23-快速设置、数组24-用户管理、
    //数组25-恢复出厂设置、数组26-升级权限、数组27-定时重启、
    //数组28-卡号录像
    BYTE  byLocalChannel[128];	//本地用户对通道的操作权限，最大128个通道，0-无权限，1-有权限
    BYTE  byRemoteRight[32];		//远程登陆用户所具备的权限 1.数组0未使用；2.取值：0-无权限，1-有权限
    //数组 1-远程预览、数组 2-参数设置、数组 3-远程回放、数组 4-远程备份、
    //数组 5-查看日志、数组 6-语音对讲、数组 7-远程升级、数组 8-远程重启
    BYTE  byRemoteChannel[128];	//用户远程登陆时对通道所具备的权限，最大128个通道，0-无权限，1-有权限
    DWORD  dwUserIP;			//用户登录时pc机的ip地址，为0表示任何PC机都可以使用该用户登陆到
    //DVR上，不为0表示只有ip地址为设定值的pc机才可以使用该用户登录到
    //DVR上
    BYTE  byMACAddr[8];		//用户登录时PC机的MAC地址，为0表示任何PC机都可以使用该用户登陆
    //到DVR上，不为0表示只有MAC地址为设定值的PC机才可以使用该用户
    //登陆到DVR上

}STRUCT_USERINFO_GUI;

typedef struct 
{
    BYTE  user [32];				//用户名，以’\0’结束字符串
    BYTE  pwd [32];				//密码，以’\0’结束字符串
    BYTE  grp_name[32];			//分组名
    LONG64  local_authority[64];		//本地用户使用权限，每位代表一个通道,bit0~bit63表示0~63通道，
    //每个数组代表一种权限，数组0-实时预览、数组1-手动录像、
    //数组2-录像查询回放、数组3-备份管理、数组4-录像参数、数组5-云台设置、
    //数组6-截图设置、数组7-通道设置、数组8-定时录像、数组9-移动检测、
    //数组10-报警管理、数组11-常规设置、数组12-串口设置、数组13-磁盘设置、
    //数组14-网络设置、数组15-信息查看、数组16-升级管理、数组17-快速设置、
    //数组18-出厂设置、数组19-系统关机、数组20-卡号录像
    LONG64  remote_authority[64]; 	//远程权限，每位代表一个通道，bit0~bit63表示0~63通道，
    //每个数组代表一种权限，数组0-远程预览、数组1-参数设置、数组2-远程回									//放、数组3-远程备份、数组4-查看日志、数组5-语音对讲、数组6-远程升级
    DWORD  dwbind_ipaddr;		//用户登录时pc机的ip地址，为0表示任何PC机都可以使用该用户登陆到
    //DVR上，不为0表示只有ip地址为设定值的pc机才可以使用该用户登录到
    //DVR上
    BYTE  bybind_macaddr[8];		//用户登录时PC机的MAC地址，为0表示任何PC机都可以使用该用户登陆
    //到DVR上，不为0表示只有MAC地址为设定值的PC机才可以使用该用户
    //登陆到DVR上
}STRUCT_USERINFO_9000;

typedef  struct 
{
    DWORD  dwSize;				//结构体大小
    WORD  wUserInfoMode;		//用户权限模式，1-老的权限模式，2-新GUI权限模式，3-9000项目权限模式
    BYTE  reserve[2];				//保留
    union
    {
        STRUCT_USERINFO  userInfo[16];				//当dwUserInfoMode=1时，使用该结构体
        STRUCT_USERINFO_GUI  userInfoGui[16];		//当dwUserInfoMode=2时，使用该结构体
        STRUCT_USERINFO_9000  userInfo9000[16];		//当dwUserInfoMode=3时，使用该结构体
    }info;
}STRUCT_SDVR_USER_INFO_EX1, *PSTRUCT_SDVR_USER_INFO_EX1;

HB_SDVR_API BOOL __stdcall HB_SDVR_GetUserInfo( IN LONG lUserID, OUT PSTRUCT_SDVR_USER_INFO_EX1 pUserInfoEx1 );
HB_SDVR_API BOOL __stdcall HB_SDVR_SetUserInfo( IN LONG lUserID, IN PSTRUCT_SDVR_USER_INFO_EX1 pUserInfoEx1 );

// 夏令时按周设置时间
typedef  struct
{
    BYTE  month;	//夏令时按月设置，月[1，12]
    BYTE  weeks;	//夏令时按周设置，周[1，5]
    BYTE  week;		//夏令时按周设置，星期[0，6]，
    BYTE  hour;		//夏令时按周设置,  时[0，23]
    BYTE  min;		//夏令时按周设置，分[0，59]
    BYTE  sec;		//夏令时按周设置，秒[0，59]
} STRUCT_SDVR_DST_WEEK_TIME_S;
//说明：按周设置的时间，表示第几月的第几个星期几的几时几分几秒，如month=5，weeks=2，week=1，hour=10，min=0，sec=0，表示5月份的第2个星期1的10：00：00


//系统时间定义
typedef struct {
    unsigned int sec : 6;
    unsigned int min : 6;
    unsigned int hour : 5;
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 6;
} HSYSTIME;
//夏令时时间设置
typedef  struct
{
    BYTE  dst_en;			//夏令时使能键，0-不使能，1-使能
    BYTE  dsttype_en;		//按周设置为0, 按日期设置为1
    HSYSTIME  start_date;		//按日期设置的开始时间
    HSYSTIME  end_date;		//按日期设置的结束时间
    STRUCT_SDVR_DST_WEEK_TIME_S  start_time;	//按周设置的开始时间
    STRUCT_SDVR_DST_WEEK_TIME_S  end_time;		//按周设置的结束时间
    BYTE  reserve[4];			//保留
}STRUCT_SDVR_DST_TIME_S;

HB_SDVR_API BOOL __stdcall HB_SDVR_GetDstTime( IN LONG lUserID, OUT STRUCT_SDVR_DST_TIME_S* pDstTime );
HB_SDVR_API BOOL __stdcall HB_SDVR_SetDstTime( IN LONG lUserID, IN STRUCT_SDVR_DST_TIME_S* pDstTime );

#define OSDINFONUM_MAX	        64	//OSD信息数组最大个数
#define OSDSTRSIZE_MAX	        100	//OSD字符串最大个数

typedef  struct 
{ 
    BYTE  id;                 		// 通道字符叠加信息号 [0, n－1] n: 叠加字符信息组数
    BYTE  byLinkMode;        		// 0-主码流  1-子码流  
    BYTE  byChanOSDStrSize;			// 叠加字符信息里字符串数据的长度，包含字符串结束符'\0',[1, 100]
    BYTE  byOSDAttrib;				// 通道字符叠加信息  1-不透明  2-透明(只针对 PC 端显示)
    BYTE  byOSDType; 				// 格式及语言，最高位为 0表示解码后叠加，为 1表示前端叠加
    // 设为 0x80 时表示将 osd 设为前端叠加
    char  reservedData[3];				// 保留
    DWORD  dwShowChanOSDInfo;	// 是否显示通道字符叠加信息  0-显示  1-不显示 
    WORD  wShowOSDInfoTopLeftX;	// 通道字符叠加信息显示位置的 x 坐标
    //  [0,  实际宽－叠加字符数据长度]
    WORD  wShowOSDInfoTopLeftY;	// 通道字符叠加信息显示位置的 y 坐标 
    //  [0,  实际高－字体高度] 
    char  data[OSDSTRSIZE_MAX];						// 叠加字符信息里的字符串数据，包含字符串结束符'\0',长度小于100。
} HB_SDVR_STRUCT_SDVR_OSDINFO; 

typedef  struct 
{ 
    BYTE   byChannel;				// 通道号 [0, n－1] n:通道数
    BYTE   byOSDInfoNum; 			// 包含的叠加字符信息组数[1,64]，每组结构为STRUCT_SDVR_OSDINFO
    WORD   byChanOSDInfoSize;      // 叠加字符信息的数据包大小,保留
    HB_SDVR_STRUCT_SDVR_OSDINFO OsdInfo[OSDINFONUM_MAX];
} HB_SDVR_STRUCT_SDVR_OSDCFG; 


HB_SDVR_API BOOL __stdcall HB_SDVR_GetOsdCfg( IN LONG lUserID, IN OUT HB_SDVR_STRUCT_SDVR_OSDCFG* pOsdCfg );
HB_SDVR_API BOOL __stdcall HB_SDVR_SetOsdCfg( IN LONG lUserID, IN const HB_SDVR_STRUCT_SDVR_OSDCFG* pOsdCfg);


typedef struct ST_HB_SDVR_INITIATIVE_LOGIN
{ 
    char sDVRID[SERIALNO_LEN];  
    char sSerialNumber[SERIALNO_LEN]; 
    BYTE byAlarmInPortNum;
    BYTE byAlarmOutPortNum; 
    BYTE byDiskNum;  
    BYTE byProtocol;             
    BYTE byChanNum;   
    BYTE byEncodeType; 
    BYTE reserve[26];    
    char sDvrName[NAME_LEN];     
    char sChanName[MAX_CHANNUM_EX][NAME_LEN];   
}HB_SDVR_INITIATIVE_LOGIN, *LPHB_SDVR_INITIATIVE_LOGIN;

typedef struct 
{ 
    BYTE byChannel;
    BYTE byAlarmStat;
    BYTE reserve1[2];
    DWORD dwAlarmType;
    LPHB_SDVR_TIME dwAlarmTime;
    BYTE reserve2[4];
}HB_SDVR_ALARM_REQ;

typedef BOOL (CALLBACK *PInitiativeAlarmCallBack)( LONG lUserID, HB_SDVR_ALARM_REQ Alarm, PVOID pContext );
typedef BOOL (CALLBACK *PInitiativeLoginCallBack)( LONG lUserID,
    char *sDVRIP,//保留
    LPHB_SDVR_INITIATIVE_LOGIN pDeviceInfo, 
    PVOID pContext );

//设置主动登录回调函数
//pLoginCallBack == NULL关闭主动登录。
HB_SDVR_API BOOL HB_SDVR_SetInitiativeLoginCallBack( WORD wDVRPort, PInitiativeLoginCallBack pLoginCallBack, PVOID pContext ); 

typedef struct ST_HB_SDVR_REALPLAYCON
{
    DWORD               dwSize;
    DWORD               dwChl;
    HWND                hWnd;
    DWORD               dwStreamType;   // 0-主码流 1-子码流
    DWORD               dwLinkMode;     // 0-TCP 1-UDP
    DWORD               dwMultiCast;    // 是否多播
    DWORD               dwOSDScheme;    // osd字符编码格式 
    DWORD               dwMultiCastIP;  // 多播IP地址
    DWORD               dwPort;         // 多播端口
    PHB_SDVR_STREAMDATA_PROC    pfnDataProc;
    void*               pContext;
    DWORD               dwReserver[4];
}HB_SDVR_REALPLAYCON, *LPHB_SDVR_REALPLAYCON;

//打开视频请求 主动模式
HB_SDVR_API LONG __stdcall HB_SDVR_InitiativeRealPlay(LONG lUserID, DWORD dwMsgID, LPHB_SDVR_REALPLAYCON pRealPlay);

typedef struct ST_HB_SDVR_PLAYBACKCON
{
    DWORD               dwSize;
    DWORD               dwChannel;      // 通道号
    HB_SDVR_RECTYPE_E   dwFileType;     // 文件类型
    HWND                hWnd;
    HB_SDVR_TIME        struStartTime;  // 下载时间段开始时间
    HB_SDVR_TIME        struStopTime;   // 结束时间
    PHB_SDVR_STREAMDATA_PROC    pfnDataProc;
    void*               pContext;
    DWORD               dwResever[4];
}HB_SDVR_PLAYBACKCON, *LPHB_SDVR_PLAYBACKCON;

//远程录像点播扩展 主动模式
HB_SDVR_API LONG __stdcall HB_SDVR_InitiativePlayBack(LONG lUserID, DWORD dwMsgid, LPHB_SDVR_PLAYBACKCON pPlayBack);

//远程录像备份扩展 主动模式
HB_SDVR_API LONG __stdcall HB_SDVR_InitiativeGetFile(LONG lUserID,  DWORD dwMsgid, LPHB_SDVR_FILEGETCOND pGetFile);

//语音对讲协议扩展 主动模式
HB_SDVR_API LONG __stdcall HB_SDVR_InitiativeStartVoiceCom(LONG lUserID, DWORD dwMsgid, void(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle,
    char *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,DWORD dwUser), DWORD dwUser);

//主机端抓图扩展 主动模式
HB_SDVR_API BOOL __stdcall HB_SDVR_InitiativeGetPicFromDev(LONG lUserID, DWORD dwMsgid, USHORT channel,char *sPicFileName);

//DDNS测试
HB_SDVR_API BOOL HB_SDVR_TestDDNS(LONG lUserID);

//邮件测试
HB_SDVR_API BOOL HB_SDVR_TestEMAIL(LONG lUserID);

//登陆
/*
功  能：登陆主机
参  数：
sDVRIP： IP地址
wDVRPort： 端口
sUserName：用户名
sPassword：密码
lpDeviceInfo： 指向HB_SDVR_DEVICEINFO 结构的指针
返回值：-1 表示失败，其他值表示返回用户的ID值，该ID值是由SDK分配，每个用户ID 值在客户端是唯一的*/
//山东中孚加解密
#define MAX_IPC_CHANNUM 4
typedef struct
{
    BYTE  dongle_type[MAX_IPC_CHANNUM];		//0: 未连接加密机模块, 1: 山东中孚SATA加密机
    BYTE  realtime_encrypt[MAX_IPC_CHANNUM];	//0: 未启用加密, 1: 启用加密数据连接
    BYTE  record_encrypt[MAX_IPC_CHANNUM];	//0: 未启用加密, 1: 启用加密数据连接
} STRUCT_SDVR_DONGLEINFO;

typedef struct 
{
    BYTE  channel;			// 通道号
    BYTE  stream_mode;		// 0: 实时流, 1: 历史回放
    BYTE  stream_type;		// 0: 主码流, 1: 子码流
} STRUCT_SDVR_DONGLE_CHANNEL_INFO;

typedef struct  
{
    BYTE  realtime_enc_enable;
    BYTE  reserve;

}STRUCT_SDVR_DONGLE_ENABLE;

//
HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_GetEncInfo(IN LONG lUserID, OUT STRUCT_SDVR_DONGLEINFO* pDongleInfo);
HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_OpenKey(IN LPCTSTR pKeyPath, OUT HANDLE& pHKey);
HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_SetEncInfo(IN LONG lUserID, IN HANDLE hKey, IN STRUCT_SDVR_DONGLE_CHANNEL_INFO* pDongleInfo);


HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_SetEncStatus(IN LONG lUserID, IN STRUCT_SDVR_DONGLE_ENABLE* pDonleEnable);
HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_GetEncStatus(IN LONG lUserID, OUT STRUCT_SDVR_DONGLE_ENABLE* pDonleEnable);
HB_SDVR_API BOOL __stdcall HB_SDVR_DONGLE_CloseKey(IN HANDLE hKey);
#pragma pack()
// #ifdef __cplusplus
// };
// #endif


#endif  // HB_NETSDK_H
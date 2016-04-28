#ifndef NETCLIENTTYPES_H
#define NETCLIENTTYPES_H

#include "GlobalTypes.h"

#ifdef WIN32
#else
#define __stdcall
#endif

#define LEN_8   8
#define LEN_16  16
#define LEN_32  32
#define LEN_64  64
#define LEN_128 128
#define LEN_256 256
#define LEN_1300 1300 //对于一次协议不能完全发送的协议，控制字符数组字段个数。比如65字节数组MAX：1300/65 = 20.剩余140字节保存其它int型变量

#define TD_FALSE 0
#define TD_TRUE  1


#define TD_NULL                 0L
#define TD_NULL_PTR             TD_NULL

#define TD_SUCCESS              0
#define TD_FAILURE              (-1)

#define  TD_LITTLE_ENDIAN       1234      
#define  TD_BIG_ENDIAN          4321      


#ifdef _MSC_VER
typedef __int64                 TD_S64;
typedef unsigned __int64        TD_U64;
#endif

#if defined __INTEL_COMPILER || defined __GNUC__
typedef long long               TD_S64;
typedef unsigned long long      TD_U64;
#endif

#define MAX_LOCAL_CHANNEL_NUM	32	
#define MAX_DIGIT_CHANNEL_NUM	32
#define	MAX_CHANNEL_NUM		(MAX_LOCAL_CHANNEL_NUM + MAX_DIGIT_CHANNEL_NUM)	   //支持3511
#define MAX_TOTAL_CHANNEL_NUM	MAX_CHANNEL_NUM

#define MAX_CONNECTION		32
#define MAX_PORT_NUM        64
#define MAX_DOWNLOAD_NUM    5
#define MAX_COM_NUM			16	   //最大串口数
#define MAX_INTERTALK_NUM	1      //最大双向对讲数
#define MAX_PICTURECHANNEL_NUM  	1      //最大图片通道数
#define MAX_CAPTURECHANNEL_NUM  	1      //最大抓拍通道数
#define MAX_TRACECHANNEL_NUM        1


#define MAX_RECV_CHANNEL    1024
#define MAX_ENCODER         1024
#define LENGTH_RECV_ORDER   1024

#define LENGTH_USER_NAME_BASE64		50
#define LENGTH_PASSWORD_BASE64		50

#define LENGTH_USER_NAME	16
#define LENGTH_PASSWORD		16
#define LENGTH_CHN_TITLE    32
#define LENGTH_CHANNEL_TITLE  64
#define LENGTH_DEVICE_NAME  32
#define LENGTH_IPV4			16	
#define LENGTH_IPV6			32
#define LENGTH_SUB_MASK		16


//connect mode
#define NETMODE_TCP     1   //Tcp connect
#define NETMODE_UDP     2   //Udp connect
#define NETMODE_MC      3   //Multicast connect
#define NVS_ACTIVE      4   //Positive Mode
#define NETMODE_P2P		5   //P2P connect

//Video resolution
#define QCIF			0   //QCif 			176*144
#define HCIF			1   //HCif			352*144	
#define FCIF			2	//Cif			352*288	
#define HD1				3	//HD1			720*288
#define FD1				4	//D1			720*576
#define MD1				5	//MD1			720*288
#define QVGA			6   //QVGA			320x240
#define VGA				7   //VGA			640*480
#define HVGA			8	//HVGA			640*240
#define HD_720P			9   //720p			1280*720
#define HD_960P			10	//960P			1280*960
#define HD_200W			11  //200W			1600*1200
#define HD_1080P		12	//1080P			1920*1080
#define HD_QXGA			13	//QXGA			2048*1536
#define QHD				0x100	//QHD		960*540
#define VZ_960H			0x200	//960H		960*576
#define VZ_5MA			0x300	//500W(1)	2448*2048
#define VZ_5M			0x400	//500W(2)	2560*1920
#define VZ_QSXGA		0x500	//500W(3)	2560*2048

//视频翻转
#define VZ_QCIF_REVERSE			(0x100000+QCIF)
#define VZ_HCIF_REVERSE			(0x100000+HCIF)
#define VZ_FCIF_REVERSE			(0x100000+FCIF)
#define VZ_HD1_REVERSE			(0x100000+HD1)
#define VZ_FD1_REVERSE			(0x100000+FD1)
#define VZ_MD1_REVERSE			(0x100000+MD1)
#define VZ_QVGA_REVERSE			(0x100000+QVGA)
#define VZ_VGA_REVERSE			(0x100000+VGA)
#define VZ_HVGA_REVERSE			(0x100000+HVGA)
#define VZ_HD_720P_REVERSE		(0x100000+HD_720P)
#define VZ_HD_960P_REVERSE		(0x100000+HD_960P)
#define VZ_HD_200W_REVERSE		(0x100000+HD_200W)
#define VZ_HD_1080P_REVERSE		(0x100000+HD_1080P)
#define VZ_HD_QXGA_REVERSE		(0x100000+HD_QXGA)
#define VZ_QHD_REVERSE			(0x100000+QHD)
#define VZ_VZ_960H_REVERSE		(0x100000+VZ_960H)
#define VZ_VZ_5MA_REVERSE		(0x100000+VZ_5MA)
#define VZ_VZ_5M_REVERSE		(0x100000+VZ_5M)
#define VZ_VZ_QSXGA_REVERSE		(0x100000+VZ_QSXGA)

//Stream type
#define MAIN_STREAM   0           //Basic stream(hight quality)
#define SUB_STREAM    1           //Extended stream(low bitrate)
#define FLAG_THREE_STREAM  256		 //三码流
#define FLAG_CONID_THREE_STREAM		8 //移位标识三码流

#define LAN_VIDEO MAIN_STREAM     //for old compatible
#define WAN_VIDEO SUB_STREAM    

//Device type
#define NVS_T       0           //T serials NVS
#define NVS_S       1           //S serials NVS
#define NVS_TPLUS   2           //T+ serials NVS

//Product Model
#define TC_NVSS					0x0000
#define TC_NS621S				0x0010			
#define TC_NS621S_USB			0x0011			
#define TC_NS224S				0x0020			
#define TC_NC621S				0x0030			
#define TC_NC8000S				0x0040			
#define TC_NC8001S				0x0041			
#define TC_NC8100S				0x0042			
#define TC_NC8101S				0x0043			
#define TC_NC8200S				0x0044			
#define TC_NC8700S2				0x0045
#define	TC_NC9100S1_MP_IR       0x0046	
#define TC_NC8250				0x0050			
#define TC_NC9010S2_MP			0x0051			
#define TC_NC9000S2_2MP			0x0052			
#define TC_NC9010N1_2MP			0x0053			
#define TC_NC9000S3_3MP			0x0054			
#define TC_NH9106N1_2MPIR		0x0055			
#define	TC_NS921_N1_2MP			0x0056	
#define	TC_NS921S3_HD_V1        0x0056			
#define TC_CC9118_MP_E			0x0057			
#define TC_NH9206N1_MPIR_IVS	0x0058			
#define TC_NC9100S3_3MP_IR30    0x0059          
#define TC_NT9054S2_MPIR		0x005A	
#define	TC_NC9000S3_2MP_E       0x005B			
#define	TC_NC9200S3_MP_E_IR15   0x005C
#define TC_NH9206S3_2MP_IVS		0x005D	
#define	TC_NC9000S3_MP_E        0x005E
#define TC_NS621S2				0x0060			
#define TC_NS622S2				0x0061			
#define TC_NS324S2				0x0062			
#define TC_NS628S2 				0x0064	
#define	TC_FS0013ERS_HD         0x0070
#define TC_NC9100S3E_MP_IR30	0x0080
#define TC_NC9000S3E_MP			0x0081
#define TC_NC9200S3E_MP_IR		0x0082
#define TC_NC9100S3E_2MP_IR30	0x0083
#define TC_NC9000S3E_2MP		0x0084
#define TC_NC9200S3E_2MP_IR		0x0085
#define TC_NC921S3E_MP_HD_C		0x0086
#define TC_NH9406S3E_MPIR       0x0087
#define TC_NH9406S3E_2MPIR		0x0088
#define TC_NC9320S3E_2MP_E		0x0090

#define TC_NC9010I_2MP			0x00A1			
#define TC_NC9000I_5MP			0x00A2			
#define TC_21X_R2				0x00A3			
#define TC_21X_R3				0x00A4			
#define TC_21X_R5				0x00A5
#define TC_218_T5	            0x00A8
#define	TC_218_T3H				0x00A9	
#define	TC_217_T5				0x00AA	
#define	TC_217_T3H				0x00AB	
//end

#define TC_2816AN_SH			0x0100			
#define TC_2808AN_S_3511		0x0110			
#define TC_2816AN_SD			0x0120			
#define TC_2816AN_SD_E          0x0121			
#define TC_2808AN_S_3515		0x0130			
#define TC_2804AN_MX			0x0131			
#define TC_2816AN_S				0x0140			
#define TC_H802BHX_T			0x0141			
#define TC_2832AN_SS            0x0142			
#define TC_H804BE_HD            0x0143			
#define TC_1002S2_3C			0x0150			
#define TC_H804N_HD				0x0151			
#define	TC_2802AN_SDI			0x0160			
#define TC_H908NC_H_V50			0x0161			
#define TC_2800AN_SF_L_H		0x0170			
#define TC_2800AN_SF_H			0x0171			
#define TC_2804AN_SA			0x0172			
#define TC_2800AN_SF_L			0x0173			
#define TC_2800AN_SF			0x0174			
#define TC_H804BE_P				0x0175	
#define TC_2808AN_SF_L			0x0176
#define	TC_2804AN_SQ        	0x0177

#define TC_2800AN_R16_S2		0x017C
#define	TC_2804AN_M				0x017D
#define TC_2800AN_R4_S1			0x017E
#define TC_2800AN_R4_S2			0x017F
#define TC_2800AN_R8_S2			0x017F

#define TC_H804N_HD_P			0x0180
#define TC_2800AN_R16_S2_V2_0   0x0181
#define TC_2800AN_R16_S4	    0x0181
#define TC_2800AN_R32_S4        0x0181

#define TC_2816AN_SR_V2_0		0x0182
#define TC_2832AN_SR_V2_0		0x0182

#define TC_ND921S2_MP			0x0400			
#define	TC_ND921S2_2MP			0x0410			
#define	TC_ND921S2_SDI			0x0411			
#define	TC_2804AN_SDI			0x0500	


//Encode type
#define H263		11
#define H264		21
#define MP4			31
#define MJPEG		41

//	SendStringToServer
#define SEND_STRING_CMD		0
#define SEND_STRING_DATA	1
#define SEND_UTF8_STRING	2

//H264 Decod mode
#define H264DEC_DECTWO	0		//decode 2 field
#define H264DEC_DECTOP	1		//decode top field （low CPU cost）

//Message define
#define WCM_RECVMESSAGE         1   //Received string
#define WCM_ERR_ORDER           2   //Occur error in command socket
#define WCM_ERR_DATANET         3   //Occur error in data socket
#define WCM_TIMEOUT_DATANET     4   //Process stream timeout
#define WCM_ERR_PLAYER          5   //Occur error in player
#define WCM_ERR_USER            6   //User define error
#define WCM_LOGON_NOTIFY        7   //Logon notify
#define WCM_VIDEO_HEAD          8   //Received video head
#define WCM_VIDEO_DISCONNECT    9   //the connection were disconnect by mediacenter

//Message of Mediacenter
#define WCM_CLIENT_CONNECT      10  //There a client connected to Mediacenter
#define WCM_CLIENT_DISCONNECT   11  //A client disconnected from Mediacenter
#define WCM_CLIENT_LOGON        12  //A client logon/logogg the Mediacenter

#define WCM_RECORD_ERR          13  //Occur when recording file

//Directory Service Mode
#define WCM_DSM_REGERR          14  //Error on proxy regist to Directory server
#define WCM_DSM_ENCODERADD      15  //A NVS regist on the proxy
#define WCM_DSM_ENCODERDEL      16  //A NVS's regist connection disconnected.
//#define	WCM_DSM_ENCODERCHANGE	28	// A NVS'S IP changed.

//Message of Download logfile
#define WCM_LOGFILE_FINISHED    17  //When logfile download finished

//Message of query file
#define WCM_QUERYFILE_FINISHED  18  //Query finished record files

#define WCM_DWONLOAD_FINISHED   19  //Download finished
#define WCM_DWONLOAD_FAULT		20  //Download fault
#define WCM_REBUILDINDEX        22  //Finished of rebuild index file

//Message of talk
#define WCM_TALK				23  //Begin to talk

//Message of DiskManager
#define WCM_DISK_FORMAT_PROGRESS	24
#define WCM_DISK_FORMAT_ERROR		25
#define WCM_DISK_PART_ERROR			26

//Message of Backup Kernel
#define	WCM_BUCKUP_KERNEL			27

//Message of LocalstoreClearDisk
#define	WCM_LOCALSTORE_PROGRESS		28
#define WCM_DOWNLOAD_INTERRUPT		29	//  Download interrupt    
#define WCM_QUERYLOG_FINISHED		30  //	Query finished log

#define WCM_INTERTALK_READY			31	//	Intertalk is ready for now ...
#define WCM_CONTROL_DEVICE_RECORD	32	//	Control device record (start, stop, package)

#define WCM_RECORD_OVER_MAX_LIMIT	33	//	The size of record file is too big, and we should start to capture a new file.
#define WCM_ERR_DATANET_MAX_COUNT	34	//	Max DataNet

#define WCM_CDBURN_STATUS			35
#define WCM_NEED_DECRYPT_KEY		36	//	Need decrypt key for video
#define WCM_DECRYPT_KEY_FAILED		37	//	decrypt key is not matched
#define WCM_DECRYPT_SUCCESS			38	//	decrypt success

#define WCM_ERR_DIGITCHANNEL_NOT_ENABLED	39	//	The digital channel is not enabled
#define WCM_ERR_DIGITCHANNEL_NOT_CONNECTED	40	//	The digital channel is not connected

#define WCM_ENCRYPT_CLEARED			41   //	clear encrypt
#define WCM_FTP_UPDATE_STATUS       42   //FTP_UPDATE_STATUS
#define	WCM_BUCKUP_IMAGE			43
#define WCM_REBUILDINDEX_PROGRESS   44   //rebuild index file progress

#define	WCM_ILLEGAL_RECORD			45   //record notify when there is illegal patking

#define WCM_QUERY_ATMFILE_FINISHED  46  //Query ATM record files finished

#define WCM_AUTOTEST_INFO			47  //自动化调试@130109

#define WCM_LASTERROR_INFO			48	//设备返回的错误码

#define	WCM_LOCALSTORE_LOCK_FILE	49  //文件加解锁

#define WCM_DISK_QUOTA				50	//磁盘配额

#define WCM_CONNECT_INFO			51	//连接信息

#define WCM_USER_CHANGE             100          //用户信息改变
#define WCM_UNSUPPORT_STREAM        101          //设备不支持该路码流
#define WCM_BROADCAST_MSG			102          //通用广播消息



//IPC 3MP
#define PARA_CHECKBADPIXEL_STATUS           196     //坏点检测状态
#define PARA_DEVICE_STATE                   197     //设备实时状态
#define PARA_CHECKIRIS_STATUS               198     //光圈检测状态

//Number of Show Video
#define MAX_DRAW_NUM	2
#define MAX_OSDTYPE_NUM         10

//User 
#define AUT_BROWSE            1     //Only can preview video
#define AUT_BROWSE_CTRL       2     //Can preview and control device
#define AUT_BROWSE_CTRL_SET   3     //Preview, control device, modify settings
#define AUT_ADMIN             4      //Super user, No.0 user is super user,
                             //User name is Admin, which can not be modified,
                             //Can add, delete, modify user's authority



typedef int						ALARMTYPE;
#define ALARM_VDO_MOTION		0
#define ALARM_VDO_REC			1
#define ALARM_VDO_LOST			2
#define ALARM_VDO_INPORT		3
#define ALARM_VDO_OUTPORT		4
#define ALARM_VDO_COVER 		5
#define ALARM_VCA_INFO			6			//	VCA报警信息
#define ALARM_AUDIO_LOST		7
#define ALARM_EXCEPTION		    8

//Logon state

#define LOGON_DSMING       3    //DSM（Directory Sevices Mode）connecting
#define LOGON_RETRY        2    //Retry
#define LOGON_SUCCESS      0    //Logon successfully
#define LOGON_ING          1    //Being logon
#define LOGON_FAILED       4   //Fail to logon
#define LOGON_TIMEOUT      5   //Logon timeout
#define NOT_LOGON          6   //Not logon
#define LOGON_DSMFAILED    7   //DSM connection failure
#define LOGON_DSMTIMEOUT   8   //DSM connection 

//Player state

#define    PLAYER_STOP          0    //Not require to play
#define    PLAYER_WAITTING      0x01 //Require to play but not play, waiting for data
#define    PLAYER_PLAYING       0x02 //Playing
#define    PLAYER_CARDWAITTING  0x04 //Require to hardware decode
#define    PLAYER_CARDPLAYING   0x08  //Being hardware decode output



//PAL/NTSC
// enum VIDEO_NORM
// {
//     VIDEO_MODE_PAL    = 0x00,
//     VIDEO_MODE_NTSC   = 0x01,
//     VIDEO_MODE_AUTO   = 0x02
// };
typedef int VIDEO_NORM;
#define VIDEO_MODE_PAL 0x00
#define VIDEO_MODE_NTSC 0x01
#define VIDEO_MODE_AUTO 0x02

//Character overlay type
// enum
// {
//     OSDTYPE_TIME      = 0x01,   //Overlay time
//     OSDTYPE_TITLE     = 0x02,   //Overlay character string
//     OSDTYPE_LOGO      = 0x04    //Overlay mark
// };

#define OSDTYPE_TIME	0x01
#define OSDTYPE_TITLE	0x02
#define OSDTYPE_LOGO	0x04
#define OSDTYPE_ITS		0x05

//Image property
// enum
// {
//     BRIGHTNESS = 0,         //Brightness
//     CONTRAST   = 1,         //Contrast
//     SATURATION = 2,         //Saturation
//     HUE        = 3          //Hue
// };
#define BRIGHTNESS 0
#define CONTRAST   1
#define SATURATION 2
#define HUE        3

//Prefer mode
// enum
// {
//     PRE_VDOQUALITY = 0,     //Video quality prefer
//     PRE_FRAMERATE  = 2      //Framerate prefer
// };
#define PRE_VDOQUALITY 0
#define PRE_FRAMERATE  2

//Stream encode type
// enum
// {
//     NO_STREAM   = 0,    //Null
//     ONLY_VIDEO  = 1,    //Video stream
//     ONLY_AUDIO  = 2,    //Audio stream
//     VIDEO_AUDIO = 3     //Video and audio stream
// };
#define NO_STREAM  0
#define ONLY_VIDEO 1
#define ONLY_AUDIO 2
#define VIDEO_AUDIO 3

// enum
// {
//     DISABLE     = 0,
//     ENABLE      = 1
// };

#define  DISABLE 0
#define  ENABLE  1
// enum
// {
//     LOW         = 0,
//     HIGH        = 1
// };
#define LOW 0
#define HIGH 1

//Talk
//enum
//{
//    TALK_BEGIN_OK       = 0,    //Start talk successfully
//    TALK_BEGIN_ERROR    = 1,   //Fail to start talk
//    TALK_ERROR          = 2,    //Talk error
//    TALK_END_OK         = 3
//};

#define TALK_BEGIN_OK			0
#define TALK_BEGIN_ERROR		1
#define TALK_ERROR				2
#define TALK_END_OK				3

//enum
//{
//    TALK_STATE_NO_TALK      = 0,
//    TALK_STATE_ASK_BEGIN    = 1,
//    TALK_STATE_TALKING      = 2,
//    TALK_STATE_ASK_STOP     = 3,
//    TALK_STATE_RESUME       = 4         //  2010-4-26-16:21 @yys@,  正在自动恢复对讲过程中
//
//};

#define TALK_STATE_NO_TALK			0			//	没有对讲
#define TALK_STATE_ASK_BEGIN		1			//	已经请求开始对讲
#define TALK_STATE_TALKING			2			//	正在对讲
#define TALK_STATE_ASK_STOP			3			//	已经请求停止对讲
#define TALK_STATE_RESUME			4			//  2010-4-26-16:21 @yys@,	正在自动恢复对讲过程中

//Core remote upgrade
// enum
// {
//     PRO_UPGRADE_OK      = 0,    // Remote upgrade success
//     PRO_UPGRADE_ERROR   = -1    // Remote upgrade failure
// };
#define  PRO_UPGRADE_OK 0
#define  PRO_UPGRADE_ERROR -1
#define  PRO_UPGRADE_READY -2

// enum
// {
//     WEB_UPGRADE_OK      = 0,    // Remote upgrade success
//     WEB_UPGRADE_ERROR   = -1    // Remote upgrade failure
// };
#define WEB_UPGRADE_OK 0
#define WEB_UPGRADE_ERROR -1
#define WEB_UPGRADE_READY -2
//兼容IE
#define WEB_UPGRADE_REDAY	WEB_UPGRADE_READY

//视频参数和设备定义
typedef int							PARATYPE;
#define PARA_VIDOEPARA				0
#define PARA_VIDEOPARA				0 
#define PARA_VIDEOPARA				0 
#define PARA_VIDEOQUALITY			1     
#define PARA_FRAMERATE				2     
#define PARA_IFRAMERATE				3     
#define PARA_STREAMTYPE				4     
#define PARA_MOTIONDETECTAREA		5
#define PARA_THRESHOLD          	6    
#define PARA_MOTIONDETECT			7     
#define PARA_OSDTEXT				8    
#define PARA_OSDTYPE				9     
#define PARA_ALMINMODE				10    
#define PARA_ALMOUTMODE				11    
#define PARA_ALARMINPUT				12    
#define PARA_ALARMOUTPUT			13    
#define PARA_AlMVDOCOVTHRESHOLD		14    
#define PARA_ALMVIDEOCOV			15    
#define PARA_RECORDCOVERAREA		16    
#define PARA_RECORDCOVER			17    
#define PARA_ALMVDOLOST				18    
#define PARA_DEVICETYPE				19    
#define PARA_NEWIP					20
#define PARA_AUDIOCHN				21    
#define PARA_IPFILTER				22    
#define PARA_COVERAREA				23    
#define PARA_VIDEOHEADER			24
#define PARA_VIDEOSIZE				25    
#define PARA_BITRATE				26    
#define PARA_DATACHANGED			27
#define PARA_PARSECHANGED			28   

#define PARA_APPIFRAMERATE			29    
#define PARA_APPFRAMERATE			30    
#define PARA_APPVIDEOQUALITY		31    
#define PARA_APPVIDEOSIZE			32    
#define PARA_APPSTREAMTYPE			33    
#define PARA_APPBITRATE				34    
#define PARA_APPCOVERAREA			35    
#define PARA_APPVIDEOHEADER			36    

#define PARA_REDUCENOISE			37    
#define PARA_BOTHSTREAMSAME			38    
#define PARA_PPPOE					39    

#define PARA_ENCODETYPE				40    
#define PARA_PREFERMODE				41    

#define PARA_LOGFILE				42    
#define PARA_SETLOGOOK				43    

#define PARA_STORAGE_SCHEDULE   	44   
#define PARA_STORAGE_TASKSTATE		45    
#define PARA_STORAGE_ALARMSTATE		46    
#define PARA_STORAGE_PRERECORD		47    
#define PARA_STORAGE_RECORDRULE		49    
#define PARA_STORAGE_EXTNAME		50    
#define PARA_STORAGE_MAPDEVICE		51    
#define PARA_STORAGE_MOUNTUSB		52    
#define PARA_STORAGE_DISKSTATE		53    
#define PARA_AUDIOCODER				54    
#define PARA_NPMODE					55    
#define PARA_STORAGE_RECORDSTATE	56    

#define PARA_PU_MANAGERSVR			57    
#define PARA_PU_DEVICEID			58    
#define PARA_STREAMCLIENT			59    
#define PARA_DATEFORMAT				60    
#define PARA_HTTPPORT				61    

#define PARA_CMOS_SCENE				62    
#define PARA_SMTP_INTO				63    
#define PARA_SMTP_ENABLE			64    
#define PARA_SENSORFLIP				65    

#define PRAM_WIFI_PARAM				66
#define PARA_WIFI_SEARCH_RESULT		67   

#define PARA_PRIVACYPROTECT			68
#define PARA_NTP					69
#define PARA_ALARTHRESHOLD			70
#define PARA_OSDALPHA				71
#define PARA_WORDOVERLAY			72

#define PARA_ALARMSERVER			73
#define PARA_DHCP_BACK				74
#define PARA_WIFIDHCP				75
#define PARA_DIAPHANEITY			76
#define PARA_PTZ_PROTOCOL			77
#define PARA_3D						78
#define PARA_DISK_USAGE				79
#define PARA_VIDEOPARA_SCHEDULE		80
#define PARA_ALARM_INPORT			81
#define PARA_ALARM_OUT				82
#define PARA_INPORT_SCHEDULE		83
#define PARA_OUTPORT_SCHEDULE		84
#define PARA_MOTION_SCHEDULE		85
#define PARA_VDOLOST_SCHEDULE		86
#define PARA_VDOLOST_LINKREC		87
#define PARA_MOTIONDEC_LINKREC		88
#define PARA_ALMINPORT_LINKREC		89
#define PARA_VDOLOST_LINKSNAP		90
#define PARA_MOTIONDEC_LINKSNAP		91
#define PARA_ALMINPORT_LINKSNAP		92
#define PARA_VDOLOST_LINKPTZ		93
#define PARA_ALMINPORT_LINKPTZ		94
#define PARA_VDOLOST_LINKSNDDIS		95
#define PARA_MOTIONDEC_LNKSNDDIS	96
#define PARA_ALMINPORT_LNKSNDDIS	97
#define PARA_ALMINPORT_LNKOUT		98
#define PARA_VDOLOST_LNKOUT			99
#define PARA_MOTIONDEC_LNKOUT		100
#define PARA_OUTPORT_DELAY			101
#define PARA_UPNP_ENABLE			102
#define PARA_SYSINFO_RESULT			103
#define PARA_DDNSCHANGED 			104	   
#define PARA_FUNCLIST				105	
#define PARA_OUTPORT_STATE			106
#define PARA_ZTEINFO				107
#define PARA_ONLINESTATE			108
#define PARA_DZINFO					109
#define PARA_COMSERVER				110
#define PARA_VENCTYPE				111  //视频编码改变 主码流
#define PARA_PTZAUTOPBACK			112
#define PARA_3GDEVICESTATUS			113
#define PARA_3GDIALOG				114
#define PARA_3GMESSAGE				115
#define PARA_HDCAMER				116
#define PARA_HXLISTENPORTINFO		117
#define PARA_3GTASKSCHEDULE			118
#define PARA_3GNOTIFY				119
#define PARA_COLORPARA				120
#define PARA_EXCEPTION				121
#define PARA_CAHNNELNAME			122
#define PARA_CUSTOMRECTYPE			123
#define PARA_FTP_UPDATE				124
#define PARA_FTP_UPDATE_STATUS		125
#define PARA_CHNPTZFORMAT			126
#define PARA_3GVPDN					127
#define PARA_VIDEOCOVER_SCHEDULE	128
#define PARA_CHNPTZCRUISE			129
#define PARA_VDOCOVER_LINKPTZ		130

#define PARA_VCA_CHANNEL			131
#define PARA_VCA_VIDEOSIZE			132
#define PARA_VCA_ADVANCED			133
#define PARA_VCA_TARGET				134
#define PARA_VCA_ALARMSTAT			135
#define PARA_VCA_RULESET			136
#define PARA_VCA_RULEEVENT0			137
#define PARA_VCA_RULEEVENT1			138
#define PARA_VCA_RULEEVENT2			139
#define PARA_VCA_ALARMSCHEDULE		140
#define PARA_VCA_SCHEDULEENABLE		141
#define PARA_VCA_ALARMLINK			142

#define PARA_FTP_SNAPSHOT			143
#define PARA_FTP_LINKSEND			144
#define PARA_FTP_TIMEDSEND			145

#define PARA_DVR3G_POWERDELAY		146
#define PARA_DVR3G_SIMNUM			147
#define PARA_DVR3G_GPSINFO			148
#define PARA_DVR3G_GPSFILTER		149

#define PARA_CDBURN_MODE			150					//	刻录方式设置
#define PARA_VIDEOENCRYPT			151
#define PARA_PREIVEWREOCRD			152

#define PARA_DIGITALCHANNEL			153
#define PARA_NPMODE_EX				154

#define	PARA_SIP_VIDEOCHANNEL		155			//	SIP视频通道设置
#define PARA_SIP_ALARMCHANNEL		156			//	SIP报警通道设置

#define PARA_VIDEOCOMBINE			157        //	多画面合成
#define PARA_PLATFORM_RUN			158			//	PlatForm Run

#define PARA_ITS_CHNLENABLE         159       //
#define PARA_ITS_CHNLLOOP           160       //
#define PARA_ITS_CHNLTIME           161       //
#define PARA_ITS_CHNLSPEED          162       //
#define PARA_ITS_CHNLRECO           163       //
#define PARA_ITS_CHNLVLOOP          164       //

#define PARA_ITS_LPOPTIM_FIRSTHZ    165       //
#define PARA_ITS_LPOPTIM_NPENABLE   166       //
#define PARA_ITS_LPOPTIM_OTHER      167       //

#define PARA_ITS_TIMERANGE			168         //相机时间段设置 
#define PARA_ITS_TIMERANGEPARAM     169			//时间段参数设置
#define PARA_ITS_TIMERANGE_AGCBLOCK			170     //时间段测光区域使能
#define PARA_ITS_TIMERANGE_FLASHLAMP		171     //时间段闪光灯使能
#define PARA_ITS_DETECTMODE					172     //相机检测模式设置
#define PARA_ITS_BLOCK						173		//相机测光区域设置
#define PARA_ITS_LOOPMODE					174		//线圈工作模式	
#define PARA_ITS_DEVICETYPE					175		//相机外设类型
#define PARA_ITS_SWITCHTIME					176     //设置视频与外触发模式切换时间和设置外设延时抓拍时间（主要用于雷达）
#define PARA_JPEGQUALITY					177     //设置JPEG图片质量	

#define PARA_VCA_RULEEVENT9					178		//智能分析人脸识别参数
#define PARA_VCA_RULEEVENT10				179		//智能分析视频诊断参数

#define PARA_ITS_TEMPLATENAME				180		//高清相机模板名称设置

#define PARA_ITS_RECOPARAM					181		//交通-设置识别算法参数

#define PARA_ITS_DAYNIGHT					182		//交通-白天夜晚开始时间设置
#define PARA_ITS_CAMLOCATION				183		//交通-相机位置
#define PARA_ITS_WORKMODE					184		//交通-相机工作模式
#define PARA_TIMEZONE_SET                   185     //设置时区
#define PARA_LANGUAGE_SET                   186     //设置语言

#define PARA_CHANNELENCODEPROFILE_SET       187     //通道编码

#define PARA_EXCEPTION_HANDLE               188    //异常处理

#define PARA_ITS_CHNLIGHT					189		//车道对应的信号灯
#define PARA_ITS_CAPTURE					190		//车道对应的抓拍位置
#define PARA_ITS_RECOGNIZE					191		//是否启用识别功能								
#define PARA_IMG_DISPOSAL					192		//图片效果处理功能
#define PARA_WATERMARK						193		//是否启用水印功能
#define PARA_SYSTEM_TYPE					194		//系统类型
#define PARA_ITS_LIGHT_INFO					195		//信号灯对应的参数

#define PARA_CHECKBADPIXEL_STATUS           196     //坏点检测状态
#define PARA_DEVICE_STATE                   197     //设备实时状态
#define PARA_CHECKIRIS_STATUS               198     //光圈检测状态

#define PARA_ITS_ILLEGALPARK				199     //设置违章停车参数
#define PARA_ITS_ILLEGALPARKPARAM           200    //设置违章停车标定区域参数

#define PARA_LAN_IPV4						201     //网卡IPv4地址
#define PARA_LAN_IPV6						202     //网卡IPv6地址
#define PARA_LAN_WORKMODE					203     //网络工作模式
#define PARA_PWM_STATUS                     204     //红外灯PWM控制值

#define PARA_AUDIOMIX	                    205     //混音合成参数
#define PARA_AUDIOLOST_ALARMSCHEDULE		206		//音频丢失报警参数模板
#define PARA_AUDIOLOST_ALARMLINK			207		//音频丢失报警参数模板
#define PARA_AUDIOLOST_ALARMSCHENABLE		208		//音频丢失报警参数模板

#define PARA_ITS_SWITCH_INTERVAL			209		//相机外触发纯视频自动切换时间间隔
#define PARA_ITS_VIDEODETECT				210		//智能相机图像检测
#define PARA_ITS_REFERENCLINES				211		//智能相机绊线设置
#define PARA_ITS_DETECTAREA					212		//智能相机检测区域设置
#define PARA_ITS_RECOTYPE					213		//智能相机算法类型设置
#define PARA_METHODMODE				        214     //设置视频源制式的获取方式

#define PARA_LOCALSTORE_CHANNELPARA	        215     //通道相关存储策略


#define PARA_WIFIWORKMODE				    216      //设置WIFI工作模式
#define PARA_WIFIAPDHCPPARA					217      //设置DHCP服务配置参数 Ip范围 租用时间等
#define PARA_WIFIAPPARA						218      //设置WIFI_AP网络参数信息

#define PARA_ITS_ENABLEPARAM				219		 //设置交通相关功能使能
#define PARA_ITS_REDLIGHTDETECTAREA			220		 //设置红灯检测区域参数
#define PARA_ATM_INFO						221		 //设置ATM信息
#define PARA_AUDIO_SAMPLE					222		 //设置音频采样率
#define PARA_IPCPnP							223		 //设置数字通道即插即用
#define PARA_WIFIDHCPAP						224		 //设置AP模式DHCP功能
#define PARA_MIXAUDIO   			        225		 //混音
#define PARA_DOME_TITLE   			        226		 //	球机标题
#define PARA_HARDWARE_VOLTAGE               227      //设置8127相机电压

#define PARA_ALARMTRIGGER_AUDIOLOSE	        228      //设置音频丢失报警参数值

#define PARA_VIDEOCOVER_ALARMSCHEDULE		229		 //视频遮挡报警参数模板
#define PARA_VIDEOCOVER_ALARMLINK			230		 //视频遮挡报警联动设置
#define PARA_VIDEOCOVER_ALARMSCHENABLE		231		 //视频遮挡报警模板使能
#define PARA_HOLIDAY_PLAN_SCHEDULE			232		 //假日模板
#define PARA_VCA_RULEEVENT12				233
#define PARA_VCA_RULEEVENT13				234
#define PARA_VDOLOST_LNKSINGLEPIC			235
#define PARA_ALMINPORT_LNKSINGLEPIC			236
#define PARA_MOTIONDEC_LNKSINGLEPIC			237
#define PARA_VDOCOVER_LNKSINGLEPIC			238
#define PARA_CHANNEL_TYPE				    239  //通道类型
#define PARA_OTHER_ALARMSCHEDULE			240 	//其他报警参数模板
#define PARA_OTHER_ALARMLINK				241		//其他报警参数模板
#define PARA_OTHER_ALARMSCHENABLE			242		//其他报警参数模板
#define PARA_PORTSET						243		//端口设置参数改变
#define PARA_DISKGROUP						244		
#define PARA_DISKQUOTA						245			
#define PARA_NEW_IP							246

//add by wd @20130603
#define  PARA_ITS_CROSSINFO					247     //路口信息
#define  PARA_ITS_AREAINFO					248     //增益区域
#define  PARA_JPEGSIZEINFO					249    //相机抓拍分辨率	
#define  PARA_DEVSTATUS						250
//add end 

#define  PARA_HD_TEMPLATE_INDEX				251		//高清模板编号
#define	 PARA_STREAM_DATA					252		//用户自定义数据插入
#define  PARA_VCA_RULEEVENT14_LEAVE_DETECT	253		//离岗检测消息
#define  PARA_DOME_PTZ						254		//球机PTZ参数改变消息
#define  PARA_ITS_TEMPLATEMAP				255     //时间段与高清摄像机模板映射关系
#define  PARA_GPS_CALIBRATION				256     //是否启用GPS校时
#define  PARA_ALARM_THRESHOLD				257     //低压报警阈值
#define  PARA_SHUTDOWN_THRESHOLD			258     //低压关机阈值
#define  PARA_SMART_SCHEDULE				259		//智能录像模板
#define  PARA_VIDEO_SCHEDULE				260
#define  PARA_ITS_CHNCARSPEED				261		//车道内车辆速度参数

#define  PARA_DOME_SYETEM				    262		//球机系统参数
#define  PARA_DOME_MENU						263		//球机菜单参数
#define  PARA_DOME_WORK_SCHEDULE			264		//球机运行模板参数
#define  PARA_INTERESTED_AREA 				265		//感兴趣区域参数
#define  PARA_APPEND_OSD				    266		//附加字符叠加参数
#define  PARA_AUTO_REBOOT					267		//NVR自动重启布防时间
#define	 PARA_IP_FILTER						268		//IP地址过滤
#define	 PARA_DATE_FORMAT					269		//日期时间格式
#define  PARA_NETCONNECT_INFO_MTU			270     //MTU参数（底层socket发送分包的最大单元）
#define  PARA_LANSET_INFO					271     //网卡配置参数
#define  PARA_DAYLIGHT_SAVING_TIME			272		//夏令时
#define  PARA_NET_OFF_LINE					273
#define	 PARA_PICTURE_MERGE					274		//图像合成
#define  PARA_SNAP_SHOT_INFO			    275		//前后抓拍参数
#define	 PARA_IO_LINK_INFO					276
#define  PARA_COMMAND_ITS_FOCUS				278		//聚焦相机控制
#define  PARA_VCA_RULEEVENT7				279		//物品遗留丢失
#define	 PARA_VCA_RULEEVENT11				280		//跟踪事件
#define	 PARA_DEV_COMMONNAME  				281		//自定义设备通用接口的别名（64字节）

#define  PARA_APPVENCTYPE				    282  //视频编码改变 副码流
#define  PARA_THIRD_VENCTYPE				283  //视频编码改变 三码流
#define	 PARA_ITS_DEV_COMMONINFO  			284		//ITS设备通用信息消息


typedef int							IDENTIFY;
#define CLIENT						0
#define PROXY						1
#define CLIENT_PROXY				2

// enum DECDATATYPE
// {
//     T_AUDIO8,T_YUV420,T_YUV422
// };
typedef int DECDATATYPE;
#define T_AUDIO8 0
#define T_YUV420 1
#define T_YUV422 2

typedef struct
{
    int     m_iPara[10];
    char    m_cPara[33];
}STR_Para;

//add by wd 20130621
#define MAX_DEVSTATUS_NUM 4
typedef struct 
{
	int     iType;
	int     iStatus[MAX_DEVSTATUS_NUM];
}STR_DevStatus;
//add end

//Templet time
/*typedef struct
{
    UINT8		m_u8StartHour;
    UINT8		m_u8StartMin;
    UINT8		m_u8StopHour;
    UINT8		m_u8StopMin;
}NVS_TEMPLETTIME,*PNVS_TEMPLETTIME;*/

//Schedle time
typedef struct
{
    unsigned short      iStartHour;
    unsigned short      iStartMin;
    unsigned short      iStopHour;
    unsigned short      iStopMin;
    unsigned short      iRecordMode; //iEnable;
}NVS_SCHEDTIME,*PNVS_SCHEDTIME;

typedef struct
{
	int		 iSize;
	int      iStartHour;
	int      iStartMin;
	int      iStopHour;
	int      iStopMin;
	int      iRecordMode; 
}NVS_SCHEDTIME_Ex,*PNVS_SCHEDTIME_Ex;

typedef struct
{
    unsigned short      m_u16Brightness;
    unsigned short      m_u16Hue;
    unsigned short      m_u16Contrast;
    unsigned short      m_u16Saturation;
    /*
    UINT8		m_u8StartHour;
    UINT8		m_u8StartMin;
    UINT8		m_u8StopHour;
    UINT8		m_u8StopMin;
    */
    NVS_SCHEDTIME strctTempletTime;
}STR_VideoParam;

typedef struct
{
    char    cEncoder[16];       //NVS IP，
    char    cClientIP[16];      //Client IP，
    int     iChannel;           //Channel Number，
    int     iStreamNO;          //Stream type
    int     iMode;              //Network mode，1（TCP）， 2（UDP），3（multicast）
}LINKINFO, *PLINKINFO;

typedef struct
{
    int             iCount;                     //Connect Count，
    unsigned int    uiID[MAX_ENCODER];          //ID
}UIDLIST, *PUIDLIST;

typedef struct
{
    char        m_cHostName[32];    //NVS host name
    char        m_cEncoder[16];     //NVS (IP)
    int         m_iRecvMode;        //Network mode
    char        m_cProxy[16];       //Proxy (IP)
    char        m_cFactoryID[32];   //ProductID
    int         m_iPort;            //NVS port
    int         m_nvsType;          //NVS type(NVS_T or NVS_S or DVR ...eg)

	int         m_iChanNum;         //encoder channel num
    int         m_iLogonState;      //encoder logon state 090414 zyp add
    int         m_iServerType;      //是主动模式设备SERVER_ACTIVE，还是被动模式设备SERVER_NORMAL
}ENCODERINFO,*PENCODERINFO;

typedef struct
{
    int             m_iServerID;        //NVS ID,NetClient_Logon 返回值
    int             m_iChannelNo;       //Remote host to be connected video channel number (Begin from 0)
    char            m_cNetFile[255];    //Play the file on net, not used temporarily
    char            m_cRemoteIP[16];    //IP address of remote host
    int             m_iNetMode;         //Select net mode 1--TCP  2--UDP  3--Multicast
    int             m_iTimeout;         //Timeout length for data receipt
    int             m_iTTL;             //TTL value when Multicast
    int             m_iBufferCount;     //Buffer number
    int             m_iDelayNum;        //Start to call play progress after which buffer is filled
    int             m_iDelayTime;       //Delay time(second), reserve
    int             m_iStreamNO;        //Stream type
    int             m_iFlag;            //0，首次请求该录像文件；1，操作录像文件
    int             m_iPosition;        //0～100，定位文件播放位置；-1，不进行定位
    int             m_iSpeed;           //1，2，4，8，控制文件播放速度
}CLIENTINFO;

//Version message structure, with which to transmit SDK version message
typedef struct
{
    unsigned short  m_ulMajorVersion;
    unsigned short  m_ulMinorVersion;
    unsigned short  m_ulBuilder;
    char*           m_cVerInfo;
}SDK_VERSION;

//OSD param
typedef struct
{
    unsigned char   ucCovTime;
    unsigned char   ucCovWord;
    int             iCovYear;
    int             iCovMonth;
    int             iCovDay;
    int             iCovHour;
    int             iCovMinute;
    int             iCovSecond;
    unsigned char   ucPosition;
    char            cCovWord[32];
}OSD_PROPERTY;

//Hardware decode to show external data parameter
typedef struct
{
    int     m_iChannelNum;      //Decode card hardware channel number
    int     m_iVideoWidth;      //Video width
    int     m_iVideoHeight;     //Video height
    int     m_iFrameRate;       //Frame rate
    int     m_iDisPos;          //Video display position
    int     m_iAudioOut;        //whether to output audio
}DecoderParam;

typedef struct
{
    unsigned long nWidth;    //Video width, audio data is 0；
    unsigned long nHeight;   //Video height, audio data is 0；
    unsigned long nStamp;    //Time stamp(ms)。
    unsigned long nType;     //Audio type，T_AUDIO8,T_YUV420，。
    unsigned long nFrameRate;//Frame rate。
    unsigned long nReserved; //reserve
}FRAME_INFO;

// enum RAWFRAMETYPE
// {
//     VI_FRAME = 0,   //视频I帧
//     VP_FRAME = 1,   //视频P帧
//     AUDIO_FRAME = 5 //音频帧
// };
typedef int RAWFRAMETYPE;
#define VI_FRAME 0
#define VP_FRAME 1
#define AUDIO_FRAME 5


typedef struct
{
    unsigned int nWidth;    //Video width, audio data is 0
    unsigned int nHeight;   //Video height, audio data is 0
    unsigned int nStamp;    //Time stamp(ms)
    unsigned int nType;     //RAWFRAMETYPE, I Frame:0,P Frame:1,B Frame:2,Audio:5
    unsigned int nEnCoder;  //Audio or Video encoder(Video,0:H263,1:H264, 2:MP4. Audio,不压缩:0,G711_A:0x01,G711_U:0x02,ADPCM_A:0x03,G726:0x04)
    unsigned int nFrameRate;//Frame rate
    unsigned int nReserved; //reserve
}RAWFRAME_INFO;
   
//命令字的回调函数           
typedef void (*PROXY_NOTIFY)(int _ulLogonID,int _iCmdKey, char* _cData,  int _iLen,int _iUser);

//网络接收的原始数据,不是完整的一帧数据，可用于代理转发
typedef void (*NVSDATA_NOTIFY)(unsigned int _ulID,unsigned char *_cData,int _iLen,int _iUser);

#define STREAM_INFO_SYSHEAD     1  //系统头数据
#define STREAM_INFO_STREAMDATA  2  //视频流数据（包括复合流和音视频分开的视频流数据）
//完整的一帧数据,可用于写录像文件,或者送播放器器播放。要区分_ulStreamType的类型
typedef void (__stdcall *FULLFRAME_NOTIFY)(unsigned int _ulID,unsigned int _ulStreamType,unsigned char *_cData,int _iLen,int _iUser);
typedef void (__stdcall *FULLFRAME_NOTIFY_V4)(unsigned int _ulID, unsigned int _ulStreamType, unsigned char *_cData, int _iLen, int _iUser, int _iUserData); //_iUser：文件头数据，_iUserData：用户数据
//未解码前的标准数据,纯h264数据
typedef void (__stdcall *RAWFRAME_NOTIFY)(unsigned int _ulID,unsigned char* _cData,int _iLen, RAWFRAME_INFO *_pRawFrameInfo, int _iUser);

//下载数据，用于下载播放
typedef void (__stdcall *RECV_DOWNLOADDATA_NOTIFY)(unsigned int _ulID, unsigned char* _ucData,int _iLen, int _iFlag, void* _lpUserData);


//===========================================================================
//  storage  add 2007.6.13
//===========================================================================

#define MAX_DAYS            7
#define MAX_TIMESEGMENT     4
#define MAX_PAGE_SIZE       20
#define MAX_PAGE_LOG_SIZE	20
#define MAX_BITSET_COUNT    2

//Record type： 1-Manual record，2-Schedule record，3-Alarm record
// enum RECORD_TYPE
// {
//     RECORD_ALL=0xFF, RECORD_MANUAL=1, RECORD_TIME=2, RECORD_ALARM=3, RECORD_OTHER
// };
typedef int RECORD_TYPE;
#define RECORD_ALL 0xFF
#define RECORD_MANUAL 1
#define RECORD_TIME	  2
#define RECORD_ALARM  3
#define RECORD_OTHER  4

//Record state：
// enum RECORD_STATE
// {
//     REC_STOP=0, REC_MANUAL=1, REC_TIME=2, REC_ALARM=3
// };
 typedef int RECORD_STATE;
#define REC_STOP 0
#define REC_MANUAL 1
#define REC_TIME 2
#define REC_ALARM 3

//Audio encoder：
// enum AUDIO_ENCODER
// {
//     G711_A              = 0x01,  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
//     G711_U              = 0x02,  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
//     ADPCM_DVI4          = 0x03,  /* 32kbps ADPCM(DVI4) */
// 	G726_16KBPS         = 0x04,  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
//     G726_24KBPS         = 0x05,  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
//     G726_32KBPS         = 0x06,  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
//     G726_40KBPS         = 0x07,  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
//     MPEG_LAYER2         = 0x0E,  /* Mpeg layer 2*/
// 	AMR_NB				= 0x15,
//     ADPCM_IMA           = 0x23,  /* 32kbps ADPCM(IMA) */
//     MEDIA_G726_16KBPS   = 0x24,  /* G726 16kbps for ASF ... */
//     MEDIA_G726_24KBPS   = 0x25,  /* G726 24kbps for ASF ... */
//     MEDIA_G726_32KBPS   = 0x26,  /* G726 32kbps for ASF ... */
//     MEDIA_G726_40KBPS   = 0x27   /* G726 40kbps for ASF ... */
// };
typedef int AUDIO_ENCODER;
#define   G711_A              0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define   G711_U              0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define   ADPCM_DVI4          0x03  /* 32kbps ADPCM(DVI4) */
#define   G726_16KBPS         0x04  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
#define   G726_24KBPS         0x05  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
#define   G726_32KBPS         0x06  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
#define   G726_40KBPS         0x07  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
#define   MPEG_LAYER2         0x0E  /* Mpeg layer 2*/
#define   AMR_NB			  0x15
#define	  MPEG4_AAC			  0x16	/* MPEG-4 aac HEv2 ADTS*/
#define   ADPCM_IMA           0x23  /* 32kbps ADPCM(IMA) */
#define   MEDIA_G726_16KBPS   0x24  /* G726 16kbps for ASF ... */
#define   MEDIA_G726_24KBPS   0x25  /* G726 24kbps for ASF ... */
#define   MEDIA_G726_32KBPS   0x26  /* G726 32kbps for ASF ... */
#define   MEDIA_G726_40KBPS   0x27   /* G726 40kbps for ASF ... */

//Record mode param
typedef struct
{
    int  iPreRecord[MAX_CHANNEL_NUM];           /* Prerecord enabled: 0-Enable 1-Disable*/
    int  iPreRecordTime[MAX_CHANNEL_NUM];       /* Prerecord time 5-30s，default 10s */
    int  iDelayTime[MAX_CHANNEL_NUM];           /* Delay time*/
    int  iDelayEnable[MAX_CHANNEL_NUM];         /* Delay enabled: 0-Enable 1-Disable*/
    char cExternName[10];   /* Record file extended name */
    int  iRecordTime;       /* Record time length */
    int  iRecPolicy;        /* Storage strategy */
    int  iFreeDisk;         /* Minimum free disk space */
    int  iFileSize;         /* File maximum space*/
}NVS_RECORD,*PNVS_RECORD;

//Record time parameter
typedef struct
{
    unsigned short iYear;   /* Year */
    unsigned short iMonth;  /* Month */
    unsigned short iDay;    /* Day */
    unsigned short iHour;   /* Hour */
    unsigned short iMinute; /* Minute */
    unsigned short iSecond; /* Second */
} NVS_FILE_TIME,*PNVS_FILE_TIME;

//Record File Property
typedef struct
{
    int             iType;          /* Record type 1-Manual record, 2-Schedule record, 3-Alarm record*/
    int             iChannel;       /* Record channel 0~channel defined channel number*/
    char            cFileName[250]; /* File name */
    NVS_FILE_TIME   struStartTime;  /* File start time */
    NVS_FILE_TIME   struStoptime;   /* File end time */
    int             iFileSize;      /* File size */
}NVS_FILE_DATA,*PNVS_FILE_DATA;

typedef struct
{
	int				iSize;
	NVS_FILE_DATA	tFileData;		//文件基本信息
	int			    iLocked;		//加解锁状态
}NVS_FILE_DATA_EX,*PNVS_FILE_DATA_EX;

//Reserch parameter
typedef struct
{
    int             iType;          /* Record type 0xFF-All, 1-Manual record, 2-Schedule record, 3-Alarm record*/
    int             iChannel;       /* Record channel 0xFF-All, 0~channel-defined channel number*/
    NVS_FILE_TIME   struStartTime;  /* Start time of file */
    NVS_FILE_TIME   struStopTime;   /* End time of file */
    int             iPageSize;      /* Record number returned by each research*/
    int             iPageNo;        /* From which page to research */
    int             iFiletype;      /* File type, 0-All, 1-AVstream, 2-picture*/
    int             iDevType;       /* 设备类型，0-摄像 1-网络视频服务器 2-网络摄像机 0xff-全部*/
}NVS_FILE_QUERY, *PNVS_FILE_QUERY;

typedef struct  
{
	NVS_FILE_QUERY	fileQuery;
	char			cOtherQuery[65];
	int				iTriggerType;		//报警类型 3:端口报警,4:移动报警,5:视频丢失报警,0x7FFFFFFF:无效
	int				iTrigger;			//端口（通道）号
}NVS_FILE_QUERY_EX, *PNVS_FILE_QUERY_EX;

//Net storage device
typedef struct
{
    char cDeviceIP[16];
    char cStorePath[250];
    char cUsername[16];
    char cPassword[16];
    int  iState;
}NVS_NFS_DEV,*PNVS_NFS_DEV;

//Diskinfo
//disk manager
#define DISK_SATA_NUM	8
#define DISK_USB_NUM	4
#define	DISK_NFS_NUM	1
#define	DISK_ESATA_NUM	1
#define	DISK_SD_NUM		1

#define DNO_ESATA	32	// esata disk first no
#define DNO_SD		50	// SD disk first no

// enum DISK_STATUSTYPE
// {
//     DISK_ZERO = 0,DISK_NOTFORMAT,DISK_FORMATED,DISK_CANUSE,DISK_READING
// };
typedef int DISK_STATUSTYPE;
#define DISK_ZERO 0
#define DISK_NOTFORMAT 1
#define DISK_FORMATED  2
#define DISK_CANUSE    3
#define DISK_READING   4

/*typedef struct
{
    int  iTotal;        //total size
    int  iFree;         //free size
    int  iReserved;     //reserved
}NVS_DISKINFO, *PNVS_DISKINFO;*/

typedef struct
{
    unsigned int  m_u32TotalSpace; // 总大小
    unsigned int  m_u32FreeSpace;  // 剩余空间
    unsigned short  m_u16PartNum;    // 分区数  1～4
    unsigned short  m_u16Status;     // 状态 0，无磁盘；1，未格式化；2，已格式化；3，已挂载；4，读写中
    unsigned short  m_u16Usage;      // 用途 0，录像；1，备份
    unsigned short  m_u16Reserve;    //	保留
}NVS_DISKINFO, *PNVS_DISKINFO;

//配额结构体
#define  CMD_DISK_QUOTA_MAX_USED  			1
#define  CMD_DISK_QUOTA_TOTAL				2
#define  CMD_DISK_QUOTA_CURRENT_USED		3
typedef struct
{
	int  iSize;												//结构体大小
	int  iRecordQuota; 										//录像配额（单位：GB）
	int  iPictureQuota;										//图片配额（单位：GB）
}DISK_QUOTA;

typedef struct
{
	int  iSize;												//结构体大小
	char cRecordQuota[65]; 										//已用录像配额（单位：GB）
	char cPictureQuota[65];										//已用图片配额（单位：GB）
}DISK_QUOTA_USED;
//盘组结构体
#define MAX_DISK_GROUP_NUM			8
typedef struct
{
	int  iSize;												//结构体大小 
	int  iGroupNO;											//盘组编号，0-7
	unsigned  int	 uiDiskNO[2];							//磁盘编号，按位表示，只能选择0-7
	//或者32，从小到大，对应bit位从低到高
	unsigned  int  uiChannelNO[4];							//通道编号,按位表示，通道号从小到大，对应
	//bit位从低到高最大可设256通道
}DISK_GROUP;

//单个权限信息结构体
#define MAX_MODIFY_AUTHORITY_NUM    26				//最大权限个数
typedef struct 
{
	int iLevel;										// 权限号
	unsigned int uiList[4];							//通道列表数组
}AUTHORITY_INFO;
//用户权限结构体
typedef struct
{
	int iNeedSize;				//用户使用时，iNeedSize代表一次设置需要修改的权限数,最大不超过10
	AUTHORITY_INFO  strAutInfo[MAX_MODIFY_AUTHORITY_NUM];
}USER_AUTHORITY;

//用户权限组别结构体
#define MAX_AUTHORITY_GROUP_NUM		4	//权限组的种类数
typedef struct
{
	int iSize;												//结构体大小 
	int iGroupNO;											//权限组编号，1普通用户；2特权用户；
	//3超级用户；4管理员
	unsigned int uiList[2];									//该权限组所对应的权限号，按位表示，
	//权限编号从小到大，对应bit位从低到高
	char  cReserved[256];									//预留
}GROUP_AUTHORITY;

//Storage device info
/*typedef struct
{
    NVS_DISKINFO  usbDisk;  //usb disk information
    NVS_DISKINFO  nfsDisk;  //nfs disk information
    NVS_DISKINFO  ideDisk;  //ide disk information
}NVS_STORAGEDEV, *PNVS_STORAGEDEV;*/

typedef struct
{
    NVS_DISKINFO m_strctSATA[DISK_SATA_NUM];
    NVS_DISKINFO m_strctUSB[DISK_USB_NUM];
    NVS_DISKINFO m_strctNFS[DISK_NFS_NUM];
    NVS_DISKINFO m_strctESATA[DISK_ESATA_NUM];
    NVS_DISKINFO m_strctSD[DISK_SD_NUM];
}NVS_STORAGEDEV, *PNVS_STORAGEDEV;

// enum SMTP_AUTHTYPE
// {
//     AUTH_OFF=0,AUTH_PLAIN,AUTH_CRAM_MD5,AUTH_DIGEST_MD5,AUTH_GSSAPI,AUTH_EXTERNAL,AUTH_LOGIN,AUTH_NTLM,SMTP_AUTHTYPE_LAST
// };
typedef int SMTP_AUTHTYPE;
#define AUTH_OFF			0
#define AUTH_PLAIN			1
#define AUTH_CRAM_MD5		2
#define AUTH_DIGEST_MD5 	3
#define AUTH_GSSAPI			4
#define AUTH_EXTERNAL		5
#define AUTH_LOGIN			6
#define AUTH_NTLM			7
#define SMTP_AUTHTYPE_LAST	8
// enum SCENE_TYPE
// {
//     AUTO=0, SCENE1,SCENE2,SCENE3,SCENE4,SCENE5,SCENE6,SCENE7,SCENE8,SCENE9,SCENE10,SCENE11,SCENE_TYPE_LAST
// };
typedef int SCENE_TYPE;
#define AUTO			0
#define SCENE1			1
#define SCENE2			2
#define SCENE3 			3
#define SCENE4			4
#define SCENE5			5
#define SCENE6			6
#define SCENE7			7
#define SCENE8			8
#define SCENE9			9
#define SCENE10			10
#define SCENE11			11
#define SCENE_TYPE_LAST	12

//SMTP alarm info
typedef struct
{
    char            cSmtpServer[32];    //smtp server
    unsigned short  wdSmtpPort;         //smtp server port
    char            cEmailAccount[32];  //mail account
    char            cEmailPassword[32];  //mail password
    int             iAuthtype;           //authtype
    char            cEmailAddress[32];  //mailbox address
    char            cMailSubject[32];   //mail subject
}SMTP_INFO,*PSMTP_INFO;
//add SMTP alarm info by gjf
typedef struct SMTP_INFOEX
{
	SMTP_INFO	smtpInfo;
	char		cMailAddr[3][32];		//	另外3个地址
}*PSMTP_INFOEX;
//add end 
//---------------------------------------------------------------------------

typedef struct
{
    char cESSID[33];            //ESSID
    char cEncryption[16];       //wifi encrypttion flag; 0 no encryption，1 digital encryption
}WIFI_INFO, *PWIFI_INFO;

typedef struct
{
    char    m_cDDNSUserName[32];
    char    m_cDDNSPwd[32];
    char    m_cDDNSNvsName[32];
    char    m_cDDNSDomain[32];
    int     m_iDDNSPort;
    int     m_iDDNSEnable;
}DDNS_INFO, *PDDNS_INFO;

typedef struct
{
    char    cESSID[33];         //ESSID
    char    cWifiSvrIP[16];     //wifiIP
    char    cWifiMask[16];          //wifi mask
    char    cWifiGateway[16];       //wifi gateway
    char    cWifiDNS[16];           //wifi DNS
    char    cWifiKeyType[16];       //wifi KeyType：Hex；ASCII
    char    cWifiPassword[128];     //wifi password, @yys@, 32->128, 2010-07-05
    char    cEncryption[16];        //wifi encrypttion flag; NULL no encryption，"WEP" encryption
    char    cWifiKeyNum[2];         //wifi KeyNum (1,2,3,4)
    int     iPwdFormat;
    int     iHaveCard;
    int     iCardOnline;
}NVS_WIFI_PARAM, *PNVS_WIFI_PARAM;

//兼容IE
//wifiap
//typedef struct
//{
//	char	cESSID[64];			    //ESSID!
//	char	cWifiSvrIP[16];		    //wifiapIP
//	char	cWifiMask[16];			//wifiap mask
//	char	cWifiGateway[16];		//wifiap gateway
//	char	cWifiDNS[16];			//wifiap DNS
//	char	cWifiKeyType[16];		//wifiap KeyType：Hex；ASCII
//	char	cWifiPassword[128];		//wifiap password,
//	char	cEncryption[16];		//wifiap encrypttion flag; NULL no encryption，"WEP" encryption
//	char	cWifiKeyNum[2];         //wifiap KeyNum (1,2,3,4)
//	int		iPwdFormat;
//	int		iHaveCard;
//	int		iCardOnline;
//}NVS_WIFIAP_PARAM, *PNVS_WIFIAP_PARAM;

//兼容SDK4.0和3.3
typedef struct NVS_IPAndID
{
    char *m_pIP;
    char *m_pID;
	union
	{
		unsigned int *m_puiLogonID;
		int  *m_piLogonID;
	};
}*pNVS_IPAndID;

typedef struct			//定制的通用信息
{
	char    m_cParam1[64];
	char    m_cParam2[64];
	char    m_cParam3[64];
	char    m_cParam4[64];
	char    m_cParam5[64];
	char    m_cParam6[64];
	char    m_cParam7[64];
	char    m_cParam8[64];
	char    m_cParam9[64];
	char    m_cParam10[64];
	char    m_cParam11[64];
	char    m_cParam12[64];
	char    m_cParam13[64];
	char    m_cParam14[64];
	char    m_cParam15[64];
	char    m_cParam16[64];
	char    m_cParam17[64];
	char    m_cParam18[64];
	char    m_cParam19[64];
	char    m_cParam20[64];
}DZ_INFO_PARAM, *PDZ_INFO_PARAM;


#define MAX_PARAM_NUM 32

typedef struct STRCT_ParamPackage
{
	char			m_strParam[MAX_PARAM_NUM][256];
	int				m_iParam[MAX_PARAM_NUM];
	void*           m_lpVoid[MAX_PARAM_NUM];
	
}*pSTRCT_ParamPackage;
//--------------------------------------------------------

#ifndef HIWORD
#define HIWORD(l)   ((unsigned short) (((unsigned int) (l) >> 16) & 0xFFFF))
#endif

#ifndef LOWORD
#define LOWORD(l)   ((unsigned short) (l))
#endif

#define CHANNEL_INTERTALK	2		//双向对讲
#define CHANNEL_DOWNLOAD    3		//文件下载
#define STREAM_DOWNLOAD     CHANNEL_DOWNLOAD
#define CHANNEL_PICTURE     4		//图片抓拍    
#define CHANNEL_SIMUCAP  	5		//模拟抓拍流
#define CHANNEL_TRACK  	    6		//轨迹流
#define CHANNEL_THREE_STREAM	254	//三码流

#define DOWNLOAD_CHANNEL_TAG  (250)

#define SERVER_NORMAL  0
#define SERVER_ACTIVE  1

#define DATA_RECEIVE_NOT  0      //没有接收
#define DATA_RECEIVE_WAIT 1      //等待接收
#define DATA_RECEIVE_HEAD 2      //已经收到视频头，但是还没有收到数据								 
#define DATA_RECEIVE_ING  3      //正在接收ing
#define DATA_RECEIVE_DIGITALCHANNEL_FAILED  4      //数字通道未连接

#define INFO_USER_PARA     0
#define INFO_CHANNEL_PARA  1
#define INFO_ALARM_PARA    2
#define INFO_VIDEO_HEAD    3

typedef void (*CMDSTRING_NOTIFY)(char *_cBuf,int _iLen,void* _pUserData); 
  
#define PROTOCOL_COUNT			64				//	最多支持的协议个数
#define PROTOCOL_NAME_LENGTH	32				//	单个协议名称的最大长度
typedef struct
{
	int     iType;							   //整数， 0代表设备支持的协议, 1代表正在使用的协议
	int		iCount;					           //服务器支持的协议类型数
	char 	cProtocol[PROTOCOL_COUNT][PROTOCOL_NAME_LENGTH];		//各协议名称，最多支持个协议，每条协议名称最长字节；
} st_NVSProtocol;  

#ifdef WIN32
typedef struct
{
	char m_cIP[32];
	char m_cDeviceID[64];
	int  m_iLogonID;
	int  m_iChannel;
	int  m_iStreamNO;
	int  m_iDrawIndex;
}st_ConnectInfo,*pst_ConnectInfo;
#else
typedef struct
{
	char m_cIP[32];
	char m_cDeviceID[64];
	int  m_iLogonID;
	int  m_iChannel;
	int  m_iStreamNO;
	int  m_iDrawIndex;
	char m_cDownLoadFile[256];
}st_ConnectInfo,*pst_ConnectInfo;
#endif


#define CLIENT_DEFAULT 0       //连接代理的默认客户端
#define CLIENT_DECODER 1       //对解码器特殊处理

#define MAX_DATA_CHAN MAX_CHANNEL_NUM		//包含副码流
#define MAX_FILE_CHAN 5

#define DATA_CMD  1
#define DATA_DATA 2
typedef void (*INNER_DATA_NOTIFY)(unsigned int _ulID,void *_pBlock,int _iType,int _iUser);

#define REC_FILE_TYPE_STOP      (-1)
#define REC_FILE_TYPE_NORMAL	0
#define REC_FILE_TYPE_AVI		1
#define REC_FILE_TYPE_ASF		2
#define REC_FILE_TYPE_AUDIO     3
#define REC_FILE_TYPE_RAWAAC    4
#define REC_FILE_TYPE_VIDEO     5


typedef struct					//  2010-1-26-18:09 @yys@
{
	int			iChannelNo;		//	通道号
	int			iLogType;		//	日志类型
	int			iLanguage;		//	语言类型
	NVS_FILE_TIME	struStartTime;		//	开始时间
	NVS_FILE_TIME	struStopTime;		//	结束时间
	int			iPageSize;		//	页大小
	int			iPageNo;		//	页编号
}NVS_LOG_QUERY, *PNVS_LOG_QUERY;

typedef struct  
{
	int				iChannel;
	int				iLogType;
	NVS_FILE_TIME	struStartTime; 	/* File start time */
	NVS_FILE_TIME	struStoptime; 	/* File end time */
	char			szLogContent[129];					
}NVS_LOG_DATA,*PNVS_LOG_DATA;

#define DOWNLOAD_TYPE_NOTHING		0
#define DOWNLOAD_TYPE_ERROR			1
#define DOWNLOAD_TYPE_PIC			2
#define DOWNLOAD_TYPE_VIDEO			3
#define DOWNLOAD_TYPE_TIMESPAN		4

typedef struct  
{
	int iPreset[32]	;				//预置位号 取值范围：1-255	
	int	iStayTime[32];				//停留时间 取值范围：1-60	
	int	iSpeed[32];					//速度	   取值范围：0-100	
}st_PTZCruise,*Pst_PTZCruise;

/************************************************************************
*  CD-Burn 相关设置                                                                    
************************************************************************/
#define		CDBURN_CMD_SET_MIN					0
#define		CDBURN_CMD_SET_START				(CDBURN_CMD_SET_MIN+0)				//	开始刻录
#define		CDBURN_CMD_SET_STOP					(CDBURN_CMD_SET_MIN+1)				//	停止刻录
#define		CDBURN_CMD_SET_MODE					(CDBURN_CMD_SET_MIN+2)				//	设置刻录模式
#define		CDBURN_CMD_SET_RESUME				(CDBURN_CMD_SET_MIN+3)				//	继续刻录
#define		CDBURN_CMD_SET_MAX					(CDBURN_CMD_SET_MIN+4)

//#define		CDBURN_CMD_GET_MIN					(CDBURN_CMD_SET_MAX)			//	考虑下面的扩展兼容性
#define		CDBURN_CMD_GET_MIN					(3)									//	Get命令下限
#define		CDBURN_CMD_GET_MODE					(CDBURN_CMD_GET_MIN+0)				//	得到刻录模式
#define		CDBURN_CMD_GET_CDROMLIST			(CDBURN_CMD_GET_MIN+1)				//	得到当前光驱列表
#define		CDBURN_CMD_GET_CDROMCOUNT			(CDBURN_CMD_GET_MIN+2)				//	得到当前光驱的个数
#define		CDBURN_CMD_GET_STATUS				(CDBURN_CMD_GET_MIN+3)				//	得到当前刻录状态
#define		CDBURN_CMD_GET_MAX					(CDBURN_CMD_GET_MIN+4)

#define		CDBURN_MAX_COUNT				32			//	最多允许的光驱数

#define		CDBURN_STATUS_FREE				0		//	光盘未使用
#define		CDBURN_STATUS_BUSY				1		//	正在刻录
#define		CDBURN_STATUS_BAD				2		//	光盘已损坏
#define		CDBURN_STATUS_FULL				3		//	光盘已经满
#define		CDBURN_STATUS_PACK				4		//	光盘正在打包
#define     CDBURN_STATUS_BEGINFAILED       102     //  开始刻录失败 

#define		MAX_DVDNAME_LEN					31

struct TCDBurnStatus
{
	int				iCDRomID;					//	光驱ID
	int				iState;						//	当前状态
	unsigned long	ulTotal;					//	总大小
	unsigned long	ulFree;						//	空余大小
	char			cReserved[4];				//	预留4个字节
};

struct TCDBurnPolicy
{
	int				iCDRomID;								//	光驱ID，只在单盘刻录时有用

	int				iMode;									//	0-单盘刻录, 1-多盘同刻, 2-循环刻录
	int				iChannelBits[CDBURN_MAX_COUNT];			//	通道列表，按位实现
	int				iDeviceBits[CDBURN_MAX_COUNT];			//	光驱列表，按位实现
	//扩展20121025
	int				iDiskType;								//	光盘类型
	int				iBurnSpeed;								//	刻录速度
	int				iBurnHour;								//	刻录时长
	int				iResSpace;								//	预留空间
	char			cDVDName[MAX_DVDNAME_LEN+1];			//	光盘文件名
};

struct TCBurnStopMode
{
	int             iDeviceNum;                            //光驱编号
	int             iFlagByBits;                            //bit0: 1不弹盘，0弹盘；bit1：1不封盘， 0封盘
};       

/************************************************************************
*	视频加密 Video Encrypt & Decrypt                                                                      
************************************************************************/
struct TVideoEncrypt
{
	int			iChannel;					//	加密通道, -1：表示所有通道
	int			iType;						//	加密类型, -- 0，不加密；1，AES；其他待扩展
	int			iMode;						//	加密算法或方法，目前用不到
	char		cPassword[17];				//	加密密码
};

struct TVideoDecrypt
{
	int			iChannel;							//	解密通道
	char		cDecryptKey[17];					//	解密密钥
};

/************************************************************************
   Digital Channel Param  20110303                                                                   
************************************************************************/
#define DC_CMD_GET_MIN				0
#define DC_CMD_GET_ALL				(DC_CMD_GET_MIN+0)
#define DC_CMD_GET_IPCPnP			(DC_CMD_GET_MIN+2)
#define DC_CMD_GET_MAX				(DC_CMD_GET_MIN+3)

#define DC_CMD_SET_MIN				(0)
#define DC_CMD_SET_ALL				(DC_CMD_SET_MIN+1)
#define DC_CMD_SET_IPCPnP			(DC_CMD_SET_MIN+2)
#define DC_CMD_SET_MAX				(DC_CMD_SET_MIN+3)
/************************************************************************
   数字通道即插即用工作模式
***********************************************************************/
#define DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MIN         0
#define DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_OFF        (DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MIN + 0)//关闭
#define DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_AUTO_ADD   (DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MIN + 1)//自动添加
#define DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_AUTO_FIND  (DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MIN + 2)//自动发现(提示用户手动添加)
#define DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MAX        (DIGITAL_CHANNEL_PLUGANDPLAY_WORKMODE_MIN + 0)

//  [12/15/2012]
#define	MAX_RTSPURL_LEN				(127)

//	协议类型
#define SERVERTYPE_PRIVATE			(0)
#define SERVERTYPE_ONVIF			(1)
#define SERVERTYPE_PUSH				(2)
#define SERVERTYPE_RTSP				(3)

struct TDigitalChannelParam
{
	int iChannel;							//	[数字通道号]--取值范围据设备类型而定，登录时会向客户端发送数字通道数
	int	iEnable;							//	[使能]--0，禁用该数字通道；1，启用该数字通道，默认为启用
	int iConnectMode;						//	[连接方式]--0，IP；1，域名；2，主动模式，默认为IP
	int	iDevChannel;						//	[前端设备通道号]--取值范围已前端设备能力而定，默认为0
	int iDevPort;							//	[前端设备端口号]--81～65535，默认为3000
	int iStreamType;						//	[码流类型]--0，主码流；1，副码流，默认为主码流
	int iNetMode;							//	[网络类型]--1，TCP；2，UDP；3，组播，暂定为TCP,不可更改
	int iPtzAddr;							//	[PTZ地址]--0～256，为空则使用默认值

	char cIP[33];							//	[连接参数]--iConnectMode=0时，IP地址；iConnectMode=1时，域名；iConnectMode=2时，设备ID，默认为空，至多32个字符
	char cProxyIP[33];						//	[代理IP]--iConnectMode=2时，该字段无效，默认为空，至多32个字符
	char cPtzProtocolName[33];				//	[PTZ协议]--登录设备时会向客户端发送设备支持的PTZ协议列表，为空则使用默认值，至多32个字符
	char cUserName[17];						//	[用户名]--登录前端设备的用户名，不可为空，至多16个字符
	char cPassword[17];						//	[密码]--登录前端设备的密码，不可为空，至多16个字符
	char cEncryptKey[17];					//	[视频加密密码]--前端设备视频加密的密码，为空则表示不加密，至多16个字符
	int iServerType;						//  前端设备所采用的网络协议(Miracle新增字段)
											//  0:私有协议（即Tiandy协议）
											//  1:Onvif协议；
											//  2:Push流
											//	3:RTSP
	//  扩展RTSP url[12/15/2012]
	char cRTSPUrl[MAX_RTSPURL_LEN+1];		//	RTSP url
};

/************************************************************************
*	得到设备通道的属性参数                                                                     
************************************************************************/
#define		CHANNEL_TYPE_LOCAL			0			//	本地模拟通道
#define		CHANNEL_TYPE_DIGITAL		2			//	数字通道
#define		CHANNEL_TYPE_COMBINE		3			//	合成通道

#define		CHANNEL_TYPE_MAINSTREAM		0			//	主码流
#define     CHANNEL_TYPE_SUBSTREAM      1           //	副码流
#define		CHANNEL_TYPE_THIRDSTREAM	4			//	三码流

#define GENERAL_CMD_MIN						0
#define GENERAL_CMD_GET_CHANNEL_TYPE		(GENERAL_CMD_MIN+1)			//	得到此设备的某个通道的属性(旧)
#define GENERAL_CMD_CHANNEL_TYPE			(GENERAL_CMD_MIN+1)			//	得到此设备的某个通道的属性(新)
#define GENERAL_CMD_CHANTYPE_LIST			(GENERAL_CMD_MIN+2)			//	得到此设备的各通道可编辑的类型
#define GENERAL_CMD_MAX						(GENERAL_CMD_MIN+3)

/************************************************************************
* VCA 相关数据结构，供上层软件使用,下面的CMDID使用enum最好(sizeof(enum))，
	但考虑到CB与VC的兼容性问题，统一使用#define实现
************************************************************************/
#define VCA_MAX_RULE_NUM				8				//	每个通道所允许的最多规则数
#define VCA_MAX_EVENT_NUM				14				//	最多的事件个数
#define VCA_MAX_TRIPWIRE_NUM			8				//	最多的单绊线个数
#define VCA_MAX_DBTRIPWIRE_NUM			4				//	最多的双绊线个数
														//
#define VCA_MAX_OSC_REGION_NUM			3				//	最大物品丢失区域个数

#define VCA_MAX_RULE_NAME_LEN			17				//	规则名称的长度

typedef int vca_EEventType;

#define VCA_EVENT_MIN							0						//	事件ID的下限 "[0,9)"
#define VCA_EVENT_TRIPWIRE						(VCA_EVENT_MIN+0)		//	绊线事件
#define VCA_EVENT_DBTRIPWIRE					(VCA_EVENT_MIN+1)		//	双绊线事件
#define VCA_EVENT_PERIMETER						(VCA_EVENT_MIN+2)		//	周界事件
#define VCA_EVENT_LOITER						(VCA_EVENT_MIN+3)		//	徘徊事件
#define VCA_EVENT_PARKING						(VCA_EVENT_MIN+4)		//	停车事件
#define VCA_EVENT_RUN							(VCA_EVENT_MIN+5)		//	奔跑事件
#define VCA_EVENT_HIGH_DENSITY					(VCA_EVENT_MIN+6)		//	人员密度事件
#define VCA_EVENT_ABANDUM						(VCA_EVENT_MIN+7)		//	遗弃物事件
#define VCA_EVENT_OBJSTOLEN						(VCA_EVENT_MIN+8)		//	被盗物事件
#define VCA_EVENT_FACEREC						(VCA_EVENT_MIN+9)		//	人脸识别事件
#define	VCA_EVENT_VIDEODETECT					(VCA_EVENT_MIN+10)		//	视频诊断事件
#define	VCA_EVENT_TRACK							(VCA_EVENT_MIN+11)		//	跟踪事件
#define	VCA_EVENT_FLUXSTATISTIC					(VCA_EVENT_MIN+12)		//	流量统计事件
#define	VCA_EVENT_CROWD						    (VCA_EVENT_MIN+13)		//	人群聚集事件
#define	VCA_EVENT_LEAVE_DETECT					(VCA_EVENT_MIN+14)		//	离岗检测事件
#define	VCA_EVENT_MAX							(VCA_EVENT_MIN+15)		//	无效事件ID，最大上限


#define VCA_CMD_SET_MIN							1									//	VCA设置命令下限
#define VCA_CMD_SET_CHANNEL						(VCA_CMD_SET_MIN+ 0)				//	设置VCA通道号及使能
#define VCA_CMD_SET_VIDEOSIZE					(VCA_CMD_SET_MIN+ 1)				//	设置VCA通道的视频大小
#define VCA_CMD_SET_ADVANCE_PARAM				(VCA_CMD_SET_MIN+ 2)				//	设置VCA高级参数
#define VCA_CMD_SET_TARGET_PARAM				(VCA_CMD_SET_MIN+ 3)				//	设置VCA叠加参数和颜色设置
#define VCA_CMD_SET_ALARM_STATISTIC				(VCA_CMD_SET_MIN+ 4)				//	设置VCA报警计数为零
#define VCA_CMD_SET_RULE_COMMON					(VCA_CMD_SET_MIN+ 5)				//	设置VCA规则常规参数
#define VCA_CMD_SET_RULE0_TRIPWIRE				(VCA_CMD_SET_MIN+ 6)				//	设置VCA规则（单绊线）
#define VCA_CMD_SET_RULE1_DBTRIPWIRE			(VCA_CMD_SET_MIN+ 7)				//	设置VCA规则（双绊线）
#define VCA_CMD_SET_RULE2_PERIMETER				(VCA_CMD_SET_MIN+ 8)				//	设置VCA规则（周界）
#define VCA_CMD_SET_ALARM_SCHEDULE				(VCA_CMD_SET_MIN+ 9)				//	设置VCA报警模板
#define VCA_CMD_SET_ALARM_LINK					(VCA_CMD_SET_MIN+10)				//	设置VCA联动输出端口
#define VCA_CMD_SET_SCHEDULE_ENABLE				(VCA_CMD_SET_MIN+11)				//	设置VCA布防使能
#define VCA_CMD_SET_RULE9_FACEREC				(VCA_CMD_SET_MIN+12)				//	设置VCA规则（人脸识别）
#define VCA_CMD_SET_RULE10_VIDEODETECT			(VCA_CMD_SET_MIN+13)				//	设置VCA规则（视频诊断）
#define VCA_CMD_SET_RULE8_ABANDUM		        (VCA_CMD_SET_MIN+14)				//	设置VCA规则（遗弃物）
#define VCA_CMD_SET_RULE7_OBJSTOLEN             (VCA_CMD_SET_MIN+15)                //  设置VCA规则（被盗物）
#define VCA_CMD_SET_RULE11_TRACK	            (VCA_CMD_SET_MIN+16)                //  设置VCA规则（跟踪）
#define	VCA_CMD_CALL_TRACK_NO					(VCA_CMD_SET_MIN+17)				//  调用起始跟踪位
#define VCA_CMD_SET_RULE12_FLUXSTATISTIC	    (VCA_CMD_SET_MIN+18)				//	设置VCA规则（流量统计)
#define VCA_CMD_SET_RULE13_CROWD				(VCA_CMD_SET_MIN+19)				//	设置VCA规则（人群聚集)
#define VCA_CMD_SET_CHANNEL_ENABLE				(VCA_CMD_SET_MIN+20)				//	设置VCA通道使能(0:不启用智能分析 1:启用本地通道智能分析 2:启用前端通道智能分析)
#define VCA_CMD_SET_RULE14_LEAVE_DETECT			(VCA_CMD_SET_MIN+21)				//	设置VCA规则（离岗检测)
#define VCA_CMD_SET_MAX							(VCA_CMD_SET_MIN+22)				//	VCA设置命令上限


#define VCA_CMD_GET_MIN							(16)								//	VCA读取命令下限,为了兼容VIDEODETECT之前的宏
#define VCA_CMD_GET_CHANNEL						(VCA_CMD_GET_MIN+ 0)				//	读取VCA通道号及使能
#define VCA_CMD_GET_VIDEOSIZE					(VCA_CMD_GET_MIN+ 1)				//	读取VCA通道的视频大小
#define VCA_CMD_GET_ADVANCE_PARAM				(VCA_CMD_GET_MIN+ 2)				//	读取VCA高级参数
#define VCA_CMD_GET_TARGET_PARAM				(VCA_CMD_GET_MIN+ 3)				//	读取VCA叠加参数和颜色设置
#define VCA_CMD_GET_ALARM_STATISTIC				(VCA_CMD_GET_MIN+ 4)				//	读取VCA报警计数
#define VCA_CMD_GET_RULE_COMMON					(VCA_CMD_GET_MIN+ 5)				//	读取VCA规则常规参数
#define VCA_CMD_GET_RULE0_TRIPWIRE				(VCA_CMD_GET_MIN+ 6)				//	读取VCA规则（单绊线）
#define VCA_CMD_GET_RULE1_DBTRIPWIRE			(VCA_CMD_GET_MIN+ 7)				//	读取VCA规则（双绊线）
#define VCA_CMD_GET_RULE2_PERIMETER				(VCA_CMD_GET_MIN+ 8)				//	读取VCA规则（周界）
#define VCA_CMD_GET_ALARM_LINK					(VCA_CMD_GET_MIN+ 9)				//	读取VCA联动输出端口
#define VCA_CMD_GET_ALARM_SCHEDULE				(VCA_CMD_GET_MIN+10)				//	读取VCA报警模板
#define VCA_CMD_GET_SCHEDULE_ENABLE				(VCA_CMD_GET_MIN+11)				//	读取VCA布防使能
#define VCA_CMD_GET_RULE9_FACEREC				(VCA_CMD_GET_MIN+12)				//	读取VCA规则（人脸识别）
#define VCA_CMD_GET_RULE10_VIDEODETECT			(VCA_CMD_GET_MIN+13)				//	读取VCA规则（视频诊断）
#define VCA_CMD_GET_RULE8_ABANDUM			    (VCA_CMD_GET_MIN+14)				//	设置VCA规则（遗弃物）
#define VCA_CMD_GET_RULE7_OBJSTOLEN             (VCA_CMD_GET_MIN+15)				//  设置VCA规则（被盗物）
#define VCA_CMD_GET_RULE11_TRACK	            (VCA_CMD_GET_MIN+16)                //  设置VCA规则（跟踪）
#define VCA_CMD_GET_RULE12_FLUXSTATISTIC	    (VCA_CMD_GET_MIN+18)				//	设置VCA规则（流量统计)
#define VCA_CMD_GET_RULE13_CROWD				(VCA_CMD_GET_MIN+19)				//	设置VCA规则（人群聚集)
#define VCA_CMD_GET_CHANNEL_ENABLE				(VCA_CMD_GET_MIN+20)				//	读取VCA通道使能(0:不启用智能分析 1:启用本地通道智能分析 2:启用前端通道智能分析)
#define VCA_CMD_GET_STATISTIC_INFO				(VCA_CMD_GET_MIN+21)				//  读取VCA通道人流量统计数据
#define VCA_CMD_GET_RULE14_LEAVE_DETECT			(VCA_CMD_GET_MIN+22)				//  读取VCA规则（离岗检测）
#define VCA_CMD_GET_MAX							(VCA_CMD_GET_MIN+23)				//	VCA读取命令的上限

#define VCA_ALARMLINK_MIN                        0
#define VCA_ALARMLINK_AUDIO	                    (VCA_ALARMLINK_MIN)                 //联动声音提示
#define VCA_ARARMLINK_SCREEMSHOW                (VCA_ALARMLINK_MIN + 1)             //联动屏幕显示
#define VCA_ALARMLINK_OUTPORT                   (VCA_ALARMLINK_MIN + 2)             //联动输出端口
#define VCA_ALARMLINK_RECODER                   (VCA_ALARMLINK_MIN + 3)             //联动录像
#define VCA_ALARMLINK_PTZ                       (VCA_ALARMLINK_MIN + 4)             //联动PTZ
#define VCA_ALARMLINK_CAPTUREPIC                (VCA_ALARMLINK_MIN + 5)             //联动抓拍
#define VCA_ALARMLINK_SINGLEPIC					(VCA_ALARMLINK_MIN + 6)				//联动单画面
#define VCA_ALARMLINK_MAX                       (VCA_ALARMLINK_MIN + 7)

#define VCA_ALARMTYPE_MIN                       0         
#define VCA_ALARMTYPE_VIDEOLOST                 (VCA_ALARMTYPE_MIN)                 //视频丢失
#define VCA_ALARMTYPE_PORT                      (VCA_ALARMTYPE_MIN + 1)				//端口
#define VCA_ALARMTYPE_MOVE						(VCA_ALARMTYPE_MIN + 2)				//移动侦测
#define VCA_ALARMTYPE_COVER						(VCA_ALARMTYPE_MIN + 3)				//视频遮挡
#define VCA_ALARMTYPE_VCA						(VCA_ALARMTYPE_MIN + 4)				//智能分析
#define VCA_ALARMTYPE_MAX						(VCA_ALARMTYPE_MIN + 5)

#define VCA_LINKPTZ_TYPE_MIN                    0
#define VCA_LINKPTZ_TYPE_NOLINK                 (VCA_LINKPTZ_TYPE_MIN )          //不联动
#define VCA_LINKPTZ_TYPE_PRESET                 (VCA_LINKPTZ_TYPE_MIN + 1)		 //预置位
#define VCA_LINKPTZ_TYPE_TRACK                  (VCA_LINKPTZ_TYPE_MIN + 2)		 //轨迹
#define VCA_LINKPTZ_TYPE_PATH                   (VCA_LINKPTZ_TYPE_MIN + 3)		 //路径
#define VCA_LINKPTZ_TYPE_MAX                    (VCA_LINKPTZ_TYPE_MIN + 4)

/************************************************************************/
/* 智能分析视频诊断类型                                                 */
/************************************************************************/
#define	VCA_AVD_NOISE 				(1<<0)   	//	噪声诊断
#define VCA_AVD_CLARITY				(1<<1)		//	清晰度诊断
#define VCA_AVD_BRIGHT_ABMNL		(1<<2)		//	亮度异常诊断
#define VCA_ADV_COLOR				(1<<3)		//	偏色诊断
#define VCA_ADV_FREEZE				(1<<4)		//	画面冻结诊断
#define VCA_ADV_NOSIGNAL			(1<<5)		//	信号丢失诊断
#define VCA_ADV_CHANGE				(1<<6)		//	场景变换诊断
#define VCA_ADV_INTERFERE			(1<<7)		//	人为干扰诊断
#define VCA_ADV_PTZ_LOST_CTL		(1<<8)		//	PTZ失控诊断


//联动
#define	MAX_BITSET_NUM		4
#define	MAX_ALARM_LINKTYPE  6

// typedef enum __tagLinkPTZType
// {
// 	LINKPTZ_TYPE_MIN = 0,
// 	LINKPTZ_TYPE_NOLINK = LINKPTZ_TYPE_MIN,			//不联动
// 	LINKPTZ_TYPE_PRESET,						//预置位
// 	LINKPTZ_TYPE_TRACK,							//轨迹
// 	LINKPTZ_TYPE_PATH							//路径
// }ELinkPTZType, *PELinkPTZType;	
typedef int ELinkPTZType;
typedef int __tagLinkPTZType;
typedef int * PELinkPTZType ;
#define LINKPTZ_TYPE_MIN	0
#define LINKPTZ_TYPE_NOLINK LINKPTZ_TYPE_MIN
#define LINKPTZ_TYPE_PRESET 1
#define LINKPTZ_TYPE_TRACK  2
#define LINKPTZ_TYPE_PATH	3

//时间段
typedef struct __tagAlarmScheduleParam
{
	int				iBuffSize;

	int				iWeekday;								//	星期日到星期六（0-6）
	int				iParam1;
	int				iParam2;
	NVS_SCHEDTIME	timeSeg[MAX_DAYS][MAX_TIMESEGMENT];		//	时间段

	void*			pvReserved;									
}TAlarmScheduleParam, *PTAlarmScheduleParam;

//报警模板使能
typedef struct __tagAlarmScheEnableParam
{
	int				iBuffSize;

	int				iEnable;						//	报警模板使能
	int				iParam1;						//	取值由iAlarmType而定
	int				iParam2;						//	取值由iAlarmType而定
	int				iParam3;						//	保留

	void*			pvReserved;									
}TAlarmScheEnableParam, *PTAlarmScheEnableParam;


struct vca_TPoint
{
	int iX;
	int	iY;
} ;					//	sizeof = 2*4 = 8

struct vca_TLine
{
	vca_TPoint 	stStart;
	vca_TPoint 	stEnd;
} ;						//	sizeof = 2*8 = 16

struct vca_TPolygon
{
	int 		iPointNum;
	vca_TPoint 	stPoints[VCA_MAX_POLYGON_POINT_NUM];   
} ;						//	sizeof = 32*8+4 = 260

struct vca_TDisplayParam
{
	int				iDisplayRule;			//	是否显示规则，比如绊线，周界线	
	int				iDisplayStat;			//	是否显示报警计数
	int				iColor;					//	正常时的颜色
	int				iAlarmColor;			//	报警时的颜色
};	
				
struct vca_TAlarmTimeSegment
{
	int		iStartHour;					
	int		iStartMinute;
	int		iStopHour;
	int		iStopMinute;
	int		iEnable;
};				//	报警时间段

struct vca_TAlarmSchedule
{
	int						iWeekday;					//	星期日到星期六（0-6）
	vca_TAlarmTimeSegment	timeSeg[7][4];				//	时间段
};			//	报警布防模板

struct vca_TLinkPTZ
{
	unsigned short	usType;								//	0不联动该通道，1预置位，2轨迹，3路径
	unsigned short	usPresetNO;							//	预置位号
	unsigned short	usTrackNO;							//	轨迹号
	unsigned short	usPathNO;							//	路径号
};

//	报警联动
struct vca_TAlarmLink
{
	int						iLinkType;					//	0，联动声音提示；1，联动屏幕显示；2，联动输出端口；3，联动录像；4，联动PTZ；5，联动抓拍
	int						iLinkChannel;
	
	int						iLinkSet[6];				//	0,1,2,3,5
	vca_TLinkPTZ			ptz[MAX_CHANNEL_NUM];		//	4
};					

struct vca_TScheduleEnable
{
	int						iEnable;					//	是否使能	
	int						iParam;						//	参数，保留
};

// 单绊线参数
struct vca_TTripwire
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	int					iTargetTypeCheck;		//	目标类型限制
	int					iMinDistance;			//	最小距离,目标运动距离必须大于此阈值
	int					iMinTime;				//	最短时间,目标运动距离必须大于此阈值	
	int					iType;					//	表示穿越类型
	int					iDirection;				//	单绊线禁止方向角度
	vca_TLine			stLine;					//	绊线坐标
}; 

struct vca_TPerimeter
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	int					iTargetTypeCheck;		//	区分人车
	int					iMode;					//	监测模式
	int 				iMinDistance;			//	最小距离
	int 				iMinTime;				//	最短时间		
	int					iType;					//	是否做方向限制
	int 				iDirection;				//	禁止方向角度(单位: 角度)
	vca_TPolygon		stRegion;				//	区域范围	
} ;		// 周界参数

struct vca_TFaceRec
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	vca_TPolygon		stRegion;				//	区域范围
};		//人脸识别参数

struct vca_TVideoDetection
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	int					m_iCheckTime;
};

struct vca_tOSC
{
	int                 iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
	int                 iColor;					//区域颜色
	int					iAlarmColor;			//报警时区域颜色
	int					iMinTime;				//遗弃物在区域存在的最短时间
	int 				iMinSize;				//最小像素尺寸
	int 				iMaxSize;				//最大像素尺寸
	int 				iSunRegionCount;		//子多边形个数
	vca_TPolygon 		stMainRegion;			//主多边形区域
	vca_TPolygon 		stSubRegion[VCA_MAX_OSC_REGION_NUM];	//子多边形区域
};

typedef	struct vca_tTrack
{
	int					m_iStartPreset;			//起始跟踪点
	vca_TPolygon		m_TrackRegion;			//跟踪区域
	int					m_iScene;				//场景大/中/小
	int					m_iWeekDay;				//星期
	NVS_SCHEDTIME		m_timeSeg[MAX_DAYS][MAX_TIMESEGMENT];		//跟踪时间段
}vca_tTrack, *LPvca_tTrack;

typedef	struct vca_tFluxStatistic
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	vca_TPolygon		stRegion;				//	区域范围	
}vca_tFluxStatistic, *LPvca_tFluxStatistic;

typedef	struct vca_tCrowd
{
	int					iValid;					//	是否有效,本来由规则中的iEventID判断哪个事件有效即可，
												//	但如果所有规则都不生效时iEventID总会指向一个事件，上层无法判断是否真的有效，只能加一个事件有效字段
	vca_TPolygon		stRegion;				//	区域范围	
}vca_tCrowd, *LPvca_tCrowd;

#define  MAX_RULE_REGION_NUM	4
typedef struct vca_tLeaveDetect
{
	int					iValid;					//	此事件检测是否有效,0：无效 1：有效
	int					iLeaveAlarmTime;		//	离岗报警时间,60~3600,单位：秒 ,默认值：120S
	int					iRuturnClearAlarmTime;	//	回岗消警时间,10~300,单位：秒   默认值：15S
	int					iAreaNum;				//	规则区域总数,1～4
	vca_TPolygon		stRegion[MAX_RULE_REGION_NUM];			//	区域范围	
}vca_tLeaveDetect, *LPvca_tLeaveDetect;

#define	EVENT_BUF_RESERVED		2048			//预留大小
typedef union vca_UEventParam
{	
	char cBuf[EVENT_BUF_RESERVED];							//	联合体预留空间改为2048
	vca_TTripwire		tripwire;
	vca_TPerimeter		perimeter;
	vca_TFaceRec		m_stFaceRec;
	vca_TVideoDetection	m_stVideoDetection;
	vca_tOSC            m_stOSC;
	vca_tTrack			m_stTrack;
	vca_tFluxStatistic  m_stFluxStatic;
	vca_tCrowd          m_stCrowd;
	vca_tLeaveDetect	m_stLeaveDetect;
}vca_UEventParam, *LPvca_UEventParam;
	
// 规则设置参数
struct vca_TRuleParam
{
	char 				cRuleName[VCA_MAX_RULE_NAME_LEN];	// 规则名字
	int					iValid;								// 该规则是否生效

	vca_TDisplayParam	stDisplayParam;						//	显示时的参数设定

	int					iAlarmCount;						//	报警次数
	vca_TAlarmSchedule	alarmSchedule;						//	报警布防模板参数
	vca_TAlarmLink		alarmLink;							//	报警联动设置参数
	vca_TScheduleEnable	scheduleEnable;						//	布防使能

	vca_EEventType		iEventID;							// 行为分析事件类型 
	vca_UEventParam		events;								// 行为分析事件参数
};	

// 智能分析配置参数
struct vca_TConfig
{
	int		iVideoSize;						// 视频大小
	int		iDisplayTarget;					// 是否叠加目标框
	int		iDisplayTrace;					// 是否叠加轨迹
	int		iTargetColor;					// 目标框颜色
	int		iTargetAlarmColor;				// 报警时目标框颜色
	int		iTraceLength;					// 轨迹长度
};	  

// 智能分析高级参数
struct vca_TAdvParam
{
	int		iEnable; 					//是否启用高级参数
	int		iTargetMinSize; 			//目标最小像素数
	int		iTargetMaxSize; 			//目标最大像素数
	int   	iTargetMinWidth;  			//最大宽度
	int		iTargetMaxWidth;  			//最小宽度
	int		iTargetMinHeight;  			//最大高度
	int		iTargetMaxHeight;  			//最小高度
	int     iTargetMinSpeed;			//目标最小像素速度(-1为不做限制)
	int     iTargetMaxSpeed;			//目标最大像素速度(-1为不做限制)
	int 	iTargetMinWHRatio;			//最小长宽比
	int 	iTargetMaxWHRatio;			//最大长宽比
	int		iSensitivity;				//灵敏度级别
};	

struct TStatisticInfo
{
	int					iSize;								//结构体大小
	int					iFluxIn;							//进入人数
	int					iFluxOut;							//离开人数
};

//智能分析通道参数
struct vca_TVCAChannelParam
{
	int					iEnable;					//	是否使能此通道智能分析
	vca_TConfig			config;  					//	智能分析配置参数    	
	vca_TAdvParam		advParam;					//	智能分析高级参数

	int					iRuleID;
	vca_TRuleParam	rule[VCA_MAX_RULE_NUM]; 		//	规则设置参数	
};

//	VCA配置的参数总集, 
struct vca_TVCAParam
{
	int						iEnable;								//	是否使能智能分析
	int						iChannelBit;							//	智能分析通道的Bit集

	int						iChannelID;								//	VCA通道
	vca_TVCAChannelParam	chnParam[MAX_CHANNEL_NUM];				//	每个通道的参数设置
};					

struct vca_TAlarmInfo
{
	int				iID;				//	报警消息ID，用于获取具体的信息
	int				iChannel;			//	通道号
	int				iState;				//	报警状态
	int				iEventType;			//	事件类型
	int				iRuleID;			//	规则ID

	unsigned int	uiTargetID;			//	目标ID
	int				iTargetType;		//	目标类型
	RECT			rctTarget;			//	目标位置
	int				iTargetSpeed;		//	目标速度
	int				iTargetDirection;	//	目标方向
};

/************************************************************************
* FTP 定时更新相关                                                                     
************************************************************************/

//	FTP相关协议
#define FTP_CMD_SET_MIN				0
#define FTP_CMD_SET_SNAPSHOT		(FTP_CMD_SET_MIN+0)
#define FTP_CMD_SET_LINKSEND		(FTP_CMD_SET_MIN+1)
#define FTP_CMD_SET_TIMEDSEND		(FTP_CMD_SET_MIN+2)
#define FTP_CMD_SET_UPDATE			(FTP_CMD_SET_MIN+3)
#define FTP_CMD_SET_MAX				(FTP_CMD_SET_MIN+4)

//#define FTP_CMD_GET_MIN				(FTP_CMD_SET_MAX)		//	考虑下面的扩展兼容性
#define FTP_CMD_GET_MIN				(4)
#define FTP_CMD_GET_SNAPSHOT		(FTP_CMD_GET_MIN+0)
#define FTP_CMD_GET_LINKSEND		(FTP_CMD_GET_MIN+1)
#define FTP_CMD_GET_TIMEDSEND		(FTP_CMD_GET_MIN+2)
#define FTP_CMD_GET_UPDATE			(FTP_CMD_GET_MIN+3)
#define FTP_CMD_GET_MAX				(FTP_CMD_GET_MIN+4)

struct FTP_SNAPSHOT
{
	int		iChannel;			//	通道 
	int		iEnable;			//	使能
	int		iQValue;			//	质量
	int		iInterval;			//	时间间隔
	int		iPictureSize;       //  抓拍图片大小	0x7fff：代表自动，其余对应分辨率大小
	int		iPicCount;			//  抓拍图片数量
};

struct FTP_LINKSEND
{
	int		iChannel;			//	通道
	int		iEnable;			//	使能
	int		iMethod;			//	方式
};

struct FTP_TIMEDSEND	
{
	int		iChannel;			//	通道
	int		iEnable;			//	使能
	int		iFileType;			//	文件类型
	int		iHour;				//	时间(hour)
	int		iMinute;			//	时间(Minute)
	int		iSecond;			//	秒数(Second)
};

struct FTP_UPDATE
{
	char	cFtpAddr[32];		//	升级使用的Ftp地址
	char	cFileName[32];		//	升级使用的文件名
	char	cUserName[16];		//	升级使用的用户名
	char	cPassword[16];		//	升级使用的密码
	int		iPort;				//	端口
	int		iUsage;				//	标志位用途
};

/************************************************************************
* 3G DVR 相关设置
************************************************************************/
#define		DVR3G_CMD_SET_MIN					0
#define		DVR3G_CMD_SET_POWERDELAY			(DVR3G_CMD_SET_MIN+0)				//	延时开关机
#define		DVR3G_CMD_SET_SIMNUM				(DVR3G_CMD_SET_MIN+1)				//	SIM卡号
#define		DVR3G_CMD_SET_GPSOVERLAY			(DVR3G_CMD_SET_MIN+2)				//	GPS信息
#define		DVR3G_CMD_SET_GPSFILTER				(DVR3G_CMD_SET_MIN+3)				//	GPS过滤
#define		DVR3G_CMD_SET_FTPUPLOAD_MODE		(DVR3G_CMD_SET_MIN+4)				//	Ftp自动上传的方式
#define		DVR3G_CMD_SET_VPDN					(DVR3G_CMD_GET_MIN+5)				//	VPDN
#define		DVR3G_CMD_SET_MAX					(DVR3G_CMD_SET_MIN+6)

//#define		DVR3G_CMD_GET_MIN					(DVR3G_CMD_SET_MAX)					//	考虑下面的扩展兼容性
#define		DVR3G_CMD_GET_MIN					(5)									//  Get命令下限
#define		DVR3G_CMD_GET_POWERDELAY			(DVR3G_CMD_GET_MIN+0)				//	延时开关机
#define		DVR3G_CMD_GET_SIMNUM				(DVR3G_CMD_GET_MIN+1)				//	SIM卡号
#define		DVR3G_CMD_GET_GPSOVERLAY			(DVR3G_CMD_GET_MIN+2)				//	GPS信息
#define		DVR3G_CMD_GET_GPSFILTER				(DVR3G_CMD_GET_MIN+3)				//	GPS过滤
#define		DVR3G_CMD_GET_FTPUPLOAD_MODE		(DVR3G_CMD_GET_MIN+4)				//	Ftp自动上传的方式
#define		DVR3G_CMD_GET_VPDN					(DVR3G_CMD_GET_MIN+5)				//	VPDN
#define		DVR3G_CMD_GET_MAX					(DVR3G_CMD_GET_MIN+6)

struct TDVR3GInfo
{
	int		iPowerDelayOnTime;						//	延时开机的时间，秒数，范围0~999秒， 0表示延时开机不使能。
	int		iPowerDelayOffTime;						//	延时关机的时间，秒数， 范围0~999秒，0表示延时关机不使能。	
	int		iGpsOverlay[MAX_CHANNEL_NUM];			//	使能叠加GPS信息，与通道相关
	int		iGpsFilter;								//	bitset, 0-不转发, 65535-所有. GPGGA-bit 1，GPRMC-bit 2，GPVTG-bit 3，GPGLL-bit 4，GPGSA- bit 5, GPGSV-bit 6，其它位暂时保留。
	char	cSimNum[33];							//	SIM卡号，长度最长为32位。
};

struct TDVR3GInfoEx
{
	TDVR3GInfo	dvr3GInfo;
	int			iFtpUploadMode;					//	上传方式
	char		cReserved[64];					//	预留字段
};

#define DVR3G_VPDN_MAX_LEN 32

struct TDVR3GVPDN
{
	int iSize;
	char cDialNumber[DVR3G_VPDN_MAX_LEN];	//接入号码
	char cAccount[DVR3G_VPDN_MAX_LEN];		//账号
	char cPassword[DVR3G_VPDN_MAX_LEN];		//密码
};

/************************************************************************
* 多画面合成                                                                     
************************************************************************/
struct TVideoCombine 
{
	int     iPicNum;     		// 合成画面数
	int		iRec;  				// 合成位置
	char	cChannelID[300];   	// 合成通道信息
};

/************************************************************************
* 混音                                                                     
************************************************************************/
#define MAX_MIX_NUM 300
typedef struct __tagAudioMix
{	
	int		iEnable;					//混音使能
	int		iChannel;					//音频合成通道的通道号
	char	cMixChannels[MAX_MIX_NUM];	//音源组合
	void*	pvReserved;					//保留参数,同时也是为了与TVideoCombine的大小区分
}TAudioMix,	*PTAudioMix;


/************************************************************************
* SIP协议相关                                                                     
************************************************************************/
#define SIP_CMD_GET_MIN						0
#define SIP_CMD_GET_ALARMCHANNEL			(SIP_CMD_GET_MIN+0)
#define SIP_CMD_GET_VIDEOCHANNEL			(SIP_CMD_GET_MIN+1)
#define SIP_CMD_GET_MAX						(SIP_CMD_GET_MIN+2)

//#define SIP_CMD_SET_MIN						(SIP_CMD_GET_MAX)		//	考虑下面的扩展兼容性
#define SIP_CMD_SET_MIN						(2)
#define SIP_CMD_SET_ALARMCHANNEL			(SIP_CMD_SET_MIN+0)
#define SIP_CMD_SET_VIDEOCHANNEL			(SIP_CMD_SET_MIN+1)
#define SIP_CMD_SET_MAX						(SIP_CMD_SET_MIN+2)

struct TSipVideoChannel
{
	int		iChannelNo;
	char	cChannelID[33];
	int		iLevel;
	int		iPtzTime;
};

struct TSipAlarmChannel
{
	int		iChannelNo;
	char	cChannelID[33];
	int		iLevel;
};

#define CHARSET_LENGTH          32              //  表示字符集字符串长度
#define LANGUAGE_COUNT			255				//	最多支持的语言个数
#define LANGUAGE_NAME_LENGTH	32				//	单个语言名称的最大长度
typedef struct
{
	int    iCount;
	char   cLanguage[LANGUAGE_COUNT][LANGUAGE_NAME_LENGTH];
} st_NVSLanguageList;

typedef struct
{
	unsigned long nWidth;
	unsigned long nHeight;
	unsigned long nStamp;
	unsigned long nType;
	unsigned long nFrameRate;
	unsigned long nReserved;
}PSPACK_INFO;

//2012-04-22
/************************************************************************
* 新增数据回调结构体相关                                                                     
************************************************************************/
#define 	DTYPE_MIN			0
#define 	DTYPE_H264_MP		(DTYPE_MIN + 0)
#define     DTYPE_RAW_AUDIO		(DTYPE_MIN + 1)
#define 	DTYPE_PS			(DTYPE_MIN + 2)
#define 	DTYPE_MAX			(DTYPE_MIN + 2)

typedef void (*RAWH264_MP_NOTIFY)(unsigned int _ulID, unsigned char* _cData, 
								  int _iLen, RAWFRAME_INFO *_pRawFrameInfo, int _iUser);

typedef void (*RAW_AUDIO_NOTIFY)(unsigned int _ulID, unsigned char* _cData, int _iLen, int Type, void* _pvUserData);
//PS流回调与纯音频回调一样
typedef RAW_AUDIO_NOTIFY	PS_STREAM_NOTIFY;

//PS流封装的回调函数 
typedef void (*PSPACK_NOTIFY)(unsigned long _ulID, unsigned char* _ucData, int _iSize, PSPACK_INFO* _pPsPackInfo, void* _pContext);

/************************************************************************/
/*                   不兼容回调                                         */
/************************************************************************/

//报警消息回调
typedef void (*ALARM_NOTIFY_V4)(int _ulLogonID, int _iChan, int _iAlarmState,ALARMTYPE _iAlarmType,int _iUser);

//设备参数改变回调   
typedef void (*PARACHANGE_NOTIFY_V4)(int _ulLogonID, int _iChan, PARATYPE _iParaType,STR_Para* _strPara,int _iUser);

//主回调函数,负责通知设备上下线、视频数据等相关消息，_iWparam参照WCM_LOGON_NOTIFY等消息定义
typedef void (*MAIN_NOTIFY_V4)(int _ulLogonID,int _iWparam, int _iLParam,int _iUser); 

//串口收数回调
typedef void (*COMRECV_NOTIFY_V4)(int _ulLogonID, char *_cData, int _iLen,int _iComNo,int _iUser); 

//解码后的音视频数据
typedef void (*DECYUV_NOTIFY_V4)(unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo, int _iUser);


#define UPGRADE_PROGRAM			1		//	程序升级
#define UPGRADE_WEB				2		//	网页升级

typedef void (*UPGRADE_NOTIFY_V4)(int _iLogonID, int _iServerState, int _iUserData);


typedef void (__stdcall *RECVDATA_NOTIFY)(unsigned long _ulID,unsigned char* _ucData,int _iLen);		//	不建议使用此回调函数
typedef void (__stdcall *RECVDATA_NOTIFY_EX)(unsigned long _ulID, unsigned char* _ucData,int _iLen, int _iFlag, void* _lpUserData);

#ifdef WIN32
typedef void (__stdcall *LOGON_NOTIFY)(int _iLogonID, int _iLogonState);
typedef void (__stdcall *ALARM_NOTIFY)(int _iLogonID, int _iCh, void* _vContext,ALARMTYPE _iAlarmType);
typedef void (__stdcall *PARACHANGE_NOTIFY)(int _iLogonID, int _iCh, PARATYPE _iParaType,LPVOID _strPara);
typedef void (__stdcall *MAIN_NOTIFY)(int _iLogonID,int _iWParam,int _iLParam, void* _lpNoitfyUserData);
typedef void (__stdcall *ALARM_NOTIFY_EX)(int _iLogonID, int _iChannel, void* _vContext,ALARMTYPE _iAlarmType, void* _lpNoitfyUserData);
typedef void (__stdcall *PARACHANGE_NOTIFY_EX)(int _iLogonID, int _iChannel, PARATYPE _iParaType,LPVOID _strPara, void* _lpNoitfyUserData);
typedef void (__stdcall *COMRECV_NOTIFY)(int _iLogonID, char *_buf, int _length,int _iComNo);
typedef void (__stdcall *DECYUV_NOTIFY)(unsigned long _ulID, unsigned char* _ucData, int _iSize, FRAME_INFO *_pFrameInfo, void* _pContext);
//升级内核程序
typedef void (__stdcall *PROUPGRADE_NOTIFY)(int _iLogonID,int _iServerState);
//升级网页
typedef void (__stdcall *WEBUPGRADE_NOTIFY)(int _iLogonID,int _iServerState);    
#else
typedef void (*ALARM_NOTIFY)(int _ulLogonID, int _iChan, int _iAlarmState,ALARMTYPE _iAlarmType,int _iUser);
typedef void (*PARACHANGE_NOTIFY)(int _ulLogonID, int _iChan, PARATYPE _iParaType,STR_Para* _strPara,int _iUser);
typedef void (*MAIN_NOTIFY)(int _ulLogonID,int _iWparam, int _iLParam,int _iUser); 
typedef void (*COMRECV_NOTIFY)(int _ulLogonID, char *_cData, int _iLen,int _iComNo,int _iUser);
typedef void (*DECYUV_NOTIFY)(unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo, int _iUser);
//升级内核程序
typedef void (*PROUPGRADE_NOTIFY)(int _iLogonID,int _iServerState,int _iUser);
//升级网页
typedef void (*WEBUPGRADE_NOTIFY)(int _iLogonID,int _iServerState,int _iUser);    
#endif

//通道相关存储策略
#define STORAGE_CMD_MIN 0
#define STORAGE_CMD_STORAGE_RULE STORAGE_CMD_MIN+0
#define STORAGE_CMD_MAX STORAGE_CMD_MIN+1

#define STORAGE_RULE_MIN 0
#define STORAGE_RULE_RECORD_AUDIO STORAGE_RULE_MIN+0
#define STORAGE_RULE_STORAGE_TIME STORAGE_RULE_MIN+1
#define STORAGE_RULE_EXTRACT_FRAME STORAGE_RULE_MIN+2
#define STORAGE_RULE_REDUNDANCE_RECORD STORAGE_RULE_MIN+3
#define STORAGE_RULE_SUB_RECORD STORAGE_RULE_MIN+4
#define STORAGE_RULE_SUB_STORAGE_TIME STORAGE_RULE_MIN+5
#define STORAGE_RULE_MAX STORAGE_RULE_MIN+6
typedef struct STORAGE_RULE
{
	int			iSize;		//Size of the structure,must be initialized before used
	int			iType;		//参数类型 0:是否记录音频 1:过期时间(单位:天) 2:是否开启抽帧功能 3：是否开启冗余录像
	int			iValue;		//参数值 iType = 0，2，3时，0:不记录或不开启 1:记录或开启;
							//iType = 1时，范围为[0,60]。0表示不强制执行过期操作，磁盘满后覆盖。
}*PSTORAGE_RULE;


//************************************************************************/
//*							网卡参数
//************************************************************************/
#define MAX_LAN_NUM						2
#define MAX_WIFICARD_NUM				2

#define LAN_CMD_SET_MIN					0
#define LAN_CMD_SET_IPV4				(LAN_CMD_SET_MIN+0)
#define LAN_CMD_SET_IPV6				(LAN_CMD_SET_MIN+1)
#define LAN_CMD_SET_WORKMODE			(LAN_CMD_SET_MIN+2)
//#define LAN_CMD_SET_LANNUM			(LAN_CMD_SET_MIN+3)
#define LAN_CMD_SET_DHCP				(LAN_CMD_SET_MIN+4)
#define LAN_CMD_SET_WIFIDHCPMODE		(LAN_CMD_SET_MIN+5)
#define LAN_CMD_SET_WIFIWORKMODE		(LAN_CMD_SET_MIN+6)
#define LAN_CMD_SET_WIFIAPDHCPPARA		(LAN_CMD_SET_MIN+7)
#define LAN_CMD_SET_WIFIAPPARA			(LAN_CMD_SET_MIN+8)
#define LAN_CMD_SET_WIFIPARA			(LAN_CMD_SET_MIN+9)
#define LAN_CMD_SET_MAX					(LAN_CMD_SET_MIN+10)

#define LAN_CMD_GET_MIN					0
#define LAN_CMD_GET_IPV4				(LAN_CMD_GET_MIN+0)
#define LAN_CMD_GET_IPV6				(LAN_CMD_GET_MIN+1)
#define LAN_CMD_GET_WORKMODE			(LAN_CMD_GET_MIN+2)
#define LAN_CMD_GET_LANNUM				(LAN_CMD_GET_MIN+3)
#define LAN_CMD_GET_DHCP				(LAN_CMD_GET_MIN+4)
#define LAN_CMD_GET_WIFIDHCPMODE		(LAN_CMD_GET_MIN+5)
#define LAN_CMD_GET_WIFIWORKMODE		(LAN_CMD_GET_MIN+6)
#define LAN_CMD_GET_WIFIAPDHCPPARA		(LAN_CMD_GET_MIN+7)
#define LAN_CMD_GET_WIFIAPPARA			(LAN_CMD_GET_MIN+8)
#define LAN_CMD_GET_WIFIPARA			(LAN_CMD_GET_MIN+9)
#define LAN_CMD_GET_MAX					(LAN_CMD_GET_MIN+10)

typedef struct LANPARAM_IPV4 
{
	int iSize;						//sizeof(LANPARAM_IPV4)
	int iLanNo;						//网卡编号 0:Lan1 1:Lan2	
	int iLanType;					//网卡类型 预留，填0即可。
	//默认10M/100M/1000M自适应，不可更改。
	char cIP[LENGTH_IPV4];			//IPV4 IP地址			
	char cMask[LENGTH_IPV4];		//IPV4 子网掩码
	char cGateway[LENGTH_IPV4];		//IPV4 默认网关
	char cDNS[LENGTH_IPV4];			//IPV4 首选DNS服务器
	char cBackDNS[LENGTH_IPV4];		//IPV4 备用DNS服务器
	char cReserved[64];				//预留，填0即可。
	//用于以后其他网络属性的扩展，比如MTU					
} *PLANPARAM_IPV4;

typedef struct LANPARAM_IPV6 
{
	int iSize;						//sizeof(LANPARAM_IPV6)
	int iLanNo;						//网卡编号 0:Lan1 1:Lan2	
	int iPrefixLen;					//IPV6 子网前缀长度
	char cIP[LENGTH_IPV6];			//IPV6 IP地址	
	char cGateway[LENGTH_IPV6];		//IPV6 默认网关
	char cDNS[LENGTH_IPV6];			//IPV6 首选DNS服务器
	char cBackDNS[LENGTH_IPV6];		//IPV6 备用DNS服务器
	char cReserved[64];				//预留，填0即可。
	//如有IPV6相关的基本属性可以通过该字段实现。					
} *PLANPARAM_IPV6;

typedef struct LANPARAM_WORKMODE 
{
	int iSize;						//sizeof(LANPARAM_WORKMODE)
	int iWorkMode;					//工作模式	0:负载均衡 1:网络容错 2:多址设定					
	int iMainLanNo;					//主网卡编号 0:Lan1 1:Lan2					
} *PLANPARAM_WORKMODE;

typedef struct LANPARAM_DHCP 
{
	int iSize;						//sizeof(LANPARAM_WORKMODE)
	int iLanNo;						//网卡编号 0:Lan1 1:Lan2	
	int iEnable;					//DHCP使能 0:停用 1:启动 
} *PLANPARAM_DHCP;
//add wifi&wifiap
typedef struct WIFIPARAM_DHCP       //cb@120711
{
	int iSize;						//sizeof(WIFIPARAM_DHCP)
	int iWifiDHCPMode;				//网卡工作模式 0:无线网卡0 DHCP； 1:无线网卡0 ap模式DHCP	
	int iEnable;					//DHCP使能 0:停用 1:启动 
	int iReserved;                  //待扩展参数 PS：目前只是一个无线网卡有两种DHCP类型
} *PWIFIPARAM_DHCP;

typedef struct WIFIAPDHCPPARA_DHCP       
{
	int iSize;						//sizeof(WIFIAPDHCPPARA_DHCP)
	int iDHCPStart;					//DHCP分配范围开始	
	int iDHCPEnd;					//DHCP分配范围结束 
	int iDHCPLease;                //DHCP租期
} *PWIFIAPDHCPPARA_DHCP;

typedef struct ITS_OSD
{
	int iX;
	int iY;
	int iEnable;
} *PITS_OSD;

// typedef	enum __tagAlarmLinkType
// {
// 	ALARM_LINKTYPE_AUDIO = 0,
// 	ALARM_LINKTYPE_VIDEO,
// 	ALARM_LINKTYPE_OUTPORT,
// 	ALARM_LINKTYPE_RECORD,
// 	ALARM_LINKTYPE_PTZ,
// 	ALARM_LINKTYPE_SNAPSHOT
// }EAlarmLinkType, *PEAlarmLinkType;
typedef int __tagAlarmLinkType;
typedef int EAlarmLinkType;
typedef int *PEAlarmLinkType;

//modify by zhy 2013.03.06
//////////////////////////////////////General AlarmLinkType////////////////////////////////////
#define ALARMLINKTYPE_MIN                               0  
#define ALARMLINKTYPE_LINKSOUND			(ALARMLINKTYPE_MIN + 0)		//联动声音提示
#define ALARMLINKTYPE_LINKDISPLAY		(ALARMLINKTYPE_MIN + 1)		//联动屏幕显示
#define ALARMLINKTYPE_LINKOUTPORT		(ALARMLINKTYPE_MIN + 2)     //联动输出端口 
#define ALARMLINKTYPE_LINKRECORD     	(ALARMLINKTYPE_MIN + 3)     //联动录像  
#define ALARMLINKTYPE_LINKPTZ	     	(ALARMLINKTYPE_MIN + 4)     //联动PTZ  
#define ALARMLINKTYPE_LINKSNAP   	    (ALARMLINKTYPE_MIN + 5)     //联动抓拍 
#define ALARMLINKTYPE_LINKSINGLEPIC		(ALARMLINKTYPE_MIN + 6)		//联动单画面

//兼容IE
#define ALARM_LINKTYPE_AUDIO		ALARMLINKTYPE_LINKSOUND			//联动声音提示
#define ALARM_LINKTYPE_VIDEO		ALARMLINKTYPE_LINKDISPLAY		//联动屏幕显示
#define ALARM_LINKTYPE_OUTPORT		ALARMLINKTYPE_LINKOUTPORT		//联动输出端口 
#define ALARM_LINKTYPE_RECORD		ALARMLINKTYPE_LINKRECORD		//联动录像  
#define ALARM_LINKTYPE_PTZ			ALARMLINKTYPE_LINKPTZ			//联动PTZ  
#define ALARM_LINKTYPE_SNAPSHOT		ALARMLINKTYPE_LINKSNAP   		//联动抓拍
#define ALARM_LINKTYPE_SINGLEPIC	ALARMLINKTYPE_LINKSINGLEPIC		//联动单画面

typedef struct __tagAlarmLink
{
	int				iLinkSetSize;
	int				iLinkSet[MAX_ALARM_LINKTYPE*MAX_BITSET_NUM];	
	//取值由iLinkType而定,MAX_BITSET_NUM用于扩展，如0 Type与0+MAX_ALARM_LINKTYPE为同一种联动类型的参数，后者为扩展
	//iLinkType=0,1时，iLinkSet中对应位置数据表示使能iEnable，0，不使能；1，使能。
	//iLinkType=2,3,5时，iLinkSet中对应位置数据表示按位使能iEnableByBits，
	//从最低位至最高位每一位表示一个音视频通道/输出端口的使能。
	//iLinkType=4时，iLinkSe对应位置数据t表示联动的通道号

	int				iPtzSize;
	struct			vca_TLinkPTZ		ptz[MAX_CHANNEL_NUM];		//iLinkType=4时存储联动PTZ的参数
}TAlarmLink, *PTAlarmLink;							//	报警联动参数

typedef struct __tagAlarmLinkParam
{
	int				iBuffSize;

	int				iAlarmTypeParam;				//	报警类型参数
	//	取值由iAlarmType而定，假如iAlarmType为智能分析，则iAlarmTypeParam表示iRuleID
	int				iReserved;						//	取值由iAlarmType而定，假如iAlarmType为智能分析，则iAlarmTypeParam表示iEventID
	int				iLinkType;
	union
	{
		int iChannelSet[4];
		int iEnable;								//联动单画面用此结构
		struct
		{
			TAlarmLink		stLinkContent;				//	联动参数
			void*			pvReserved;		
		};										
	};
}TAlarmLinkParam, *PTAlarmLinkParam;

/************************************************************************/
/* 通用报警参数															*/
/************************************************************************/
//命令
// typedef enum __tagAlarmSetCmd
// {
// 	CMD_SET_ALARMSCHEDULE = 0,
// 	CMD_SET_ALARMLINK,
// 	CMD_SET_ALARMSCH_ENABLE
// }EAlarmSetCmd, *PEAlarmSetCmd;
typedef int __tagAlarmSetCmd;
typedef int EAlarmSetCmd;
typedef int * PEAlarmSetCmd;
#define CMD_SET_ALARMSCHEDULE	0
#define CMD_SET_ALARMLINK		1
#define CMD_SET_ALARMSCH_ENABLE 2
#define CMD_SET_ALARMTRIGGER	3

// typedef enum __tagAlarmGetCmd
// {
// 	CMD_GET_ALARMSCHEDULE = 0,
// 	CMD_GET_ALARMLINK,
// 	CMD_GET_ALARMSCH_ENABLE
// }EAlarmGetCmd, *PEAlarmGetCmd;
typedef int __tagAlarmGetCmd;
typedef int EAlarmGetCmd;
typedef int * PEAlarmGetCmd;
#define CMD_GET_ALARMSCHEDULE	0
#define CMD_GET_ALARMLINK		1
#define CMD_GET_ALARMSCH_ENABLE 2
#define CMD_GET_ALARMTRIGGER	3

//报警参数标识
#define ATPI_AUDIO_LOST			0		//音频丢失报警触发参数
#define AUDIO_LOST_PARAM_COUNT	1		

//报警阀值参数
typedef struct __tagAlarmTriggerParam
{
	int				iBuffSize;
	int				iType;				//	报警类型
	int				iID;				//	报警参数标识
	int				iValue;				//	参数值
}TAlarmTriggerParam, *PTAlarmTriggerParam;


//////////////////////////////////////ALARM CLEAR TYPE////////////////////////////////////CMD_GET_ALARMSCHEDULE

#define  ALARM_TYPE_MIN                          0
#define  ALARM_TYPE_VIDEO_LOST					 (ALARM_TYPE_MIN)       //视频丢失
#define  ALARM_TYPE_PORT_ALARM                   (ALARM_TYPE_MIN + 1)   //端口报警            
#define  ALARM_TYPE_MOTION_DETECTION			 (ALARM_TYPE_MIN + 2)   //移动侦测
#define  ALARM_TYPE_VIDEO_COVER					 (ALARM_TYPE_MIN + 3)   //视频遮挡
#define	 ALARM_TYPE_VCA							 (ALARM_TYPE_MIN + 4)	//智能分析
#define  ALARM_TYPE_AUDIOLOST					 (ALARM_TYPE_MIN + 5)	//音频丢失
#define  ALARM_TYPE_TEMPERATURE                  (ALARM_TYPE_MIN + 6)	//温湿度
#define  ALARM_TYPE_EXCPETION				     (ALARM_TYPE_MIN + 100) //异常报警
#define  ALARM_TYPE_ALL							 (ALARM_TYPE_MIN + 255) //全部
#define  ALARM_TYPE_MAX                          (ALARM_TYPE_ALL + 1)

///////////////////////////////////////ExceptionType///////////////////////////////////

#define  EXCEPTION_TYPE_MIN						0
#define  EXCEPTION_TYPE_DISK_FULL				(EXCEPTION_TYPE_MIN + 0)  //磁盘满			
#define  EXCEPTION_TYPE_NO_DISK					(EXCEPTION_TYPE_MIN + 1)  //无磁盘
#define  EXCEPTION_TYPE_DISK_IO_ERROR			(EXCEPTION_TYPE_MIN + 2)  //磁盘读写错误
#define  EXCEPTION_TYPE_NOALLOW_ACCESS			(EXCEPTION_TYPE_MIN + 3)  //非法访问
#define  EXCEPTION_TYPE_IP_COLLISION			(EXCEPTION_TYPE_MIN + 4)  //IP冲突
#define  EXCEPTION_TYPE_NETWORK_INTERRUPT		(EXCEPTION_TYPE_MIN + 5)  //网络中断
#define  EXCEPTION_TYPE_SYSTEM_BUSY				(EXCEPTION_TYPE_MIN + 6)  //系统忙	
#define  EXCEPTION_TYPE_NO_REDUNDANCY_DISK		(EXCEPTION_TYPE_MIN + 7)  //无冗余盘
#define  EXCEPTION_TYPE_ABNORMAL_VOLTAGE		(EXCEPTION_TYPE_MIN + 8)  //电压异常
#define  EXCEPTION_TYPE_MAC_COLLISION			(EXCEPTION_TYPE_MIN + 9)  //MAC冲突
#define  EXCEPTION_TYPE_MAX						(EXCEPTION_TYPE_MIN + 10)	

//////////////////////////////////////Exception Handle////////////////////////////////////
#define  EXCEPTION_HANDLE_ENABLE                 0x01         //使能异常处理 
#define  EXCEPTION_HANDLE_DIALOG				 0x02         //是否弹出提示对话框
#define  EXCEPTION_HANDLE_LINK_BELL              0x04         //是否联动蜂鸣器
#define  EXCEPTION_HANDLE_LINK_NETCLIENT         0x08         //是否通知网络客户端

//////////////////////////////////////AlarmLinkType////////////////////////////////////
#define ALARMLINKTYPE_MIN                               0  
#define ALARMLINKTYPE_VIDEOLOST_LINKRECORD     	(ALARMLINKTYPE_MIN + 0)   //视频丢失报警联动录像    
#define ALARMLINKTYPE_VIDEOLOST_LINKSNAP   	    (ALARMLINKTYPE_MIN + 1)   //视频丢失报警联动抓拍 
#define ALARMLINKTYPE_VIDEOLOST_LINKOUTPORT     (ALARMLINKTYPE_MIN + 3)   //视频丢失联动输出端口 
#define ALARMLINKTYPE_MOTIONDETECT_LINKRECORD   (ALARMLINKTYPE_MIN + 4)   //移动侦测报警联动录像 
#define ALARMLINKTYPE_MOTIONDETECT_LINKSNAP     (ALARMLINKTYPE_MIN + 5)   //移动侦测报警联动抓拍
#define ALARMLINKTYPE_MOTIONDETECT_LINKOUTPORT 	(ALARMLINKTYPE_MIN + 6)   //移动侦测联动输出端口 
#define ALARMLINKTYPE_PORTALARM_LINKRECORD     	(ALARMLINKTYPE_MIN + 7)   //端口报警联动录像
#define ALARMLINKTYPE_PORTALARM_LINKSNAP       	(ALARMLINKTYPE_MIN + 8)   //端口报警联动抓拍
#define ALARMLINKTYPE_PORTALARM_LINKOUTPORT    	(ALARMLINKTYPE_MIN + 9)   //端口报警联动输出端口
#define ALARMLINKTYPE_MAX					   	(ALARMLINKTYPE_PORTALARM_LINKOUTPORT + 1)

/************************************************************************/
/*  智能交通 电子警察*/
/************************************************************************/

#define SN_ENCRYPT_TYPE_MASK					0x01
#define SN_ENCRYPT_TYPE_RECOGNIZE_ARITHMETIC	0x00			//识别算法加密类型
#define SN_ENCRYPT_TYPE_PROGRAM					0x01			//程序加密类型

#define SYSTEM_TYPE_MASK					0x04					
#define SYSTEM_TYPE_DEBUG					0x00				//调试
#define SYSTEM_TYPE_GATE					0x03				//卡口
#define SYSTEM_TYPE_ECOP					0x04				//电警

#define SN_REG_MASK							0x02				
#define SN_REG_RECOGNIZE_DOG				0x01				//识别狗
#define SN_REG_ENCRYPT_DOG					0x02				//智能交通加密狗



//IPC 3MP
#define MAX_CHANNEL_TYPE		2
#define MAX_REALTYPE_NUM        2  //实时数据类型种类，0：高清相机实时亮度值；1：相机实时锐度信息

struct STRCT_REAL_STATE 
{
	int        m_iTypes[MAX_REALTYPE_NUM];  //每个type的type值
	int        m_iValues[MAX_REALTYPE_NUM]; //每个type对应的实时数据
};

//ITScb@121010
//智能相机扩展
////CMD集锦
///************************************************************************
//*	锐视相机时间段                                                                     
//************************************************************************/
//#define ITS_CMD_SET_MIN                         0
//#define ITS_CMD_SET_TIMERANGE_ENABLE			0                           //设置时间段使能
//#define ITS_CMD_SET_TIMERANGE_AGCBLOCK			1							//设置时间段测光区域使能
//#define ITS_CMD_SET_TIMERANGE_FLASHLAMP			2							//设置时间段闪光灯使能
//
//#define ITS_CMD_GET_TIMERANGE_ENABLE			3							//获取时间段使能
//#define ITS_CMD_GET_TIMERANGE_AGCBLOCK			4							//获取时间段测光区域使能
//#define ITS_CMD_GET_TIMERANGE_FLASHLAMP			5							//获取时间段闪光灯使能
///************************************************************************/
///*   智能交通车道参数                                                                 
///************************************************************************/
//#define ITS_ROADWAY_CMD_SET_MIN     0
//#define ITS_ROADWAY_CMD_SET_ENABLE  (ITS_ROADWAY_CMD_SET_MIN + 0)	    //设置车道使能
//#define ITS_ROADWAY_CMD_SET_LOOP    (ITS_ROADWAY_CMD_SET_MIN + 1)		//设置车道线圈
//#define ITS_ROADWAY_CMD_SET_TIME    (ITS_ROADWAY_CMD_SET_MIN + 2)		//设置车道时间
//#define ITS_ROADWAY_CMD_SET_SPEED   (ITS_ROADWAY_CMD_SET_MIN + 3)		//设置车道速度
//#define ITS_ROADWAY_CMD_SET_RECO    (ITS_ROADWAY_CMD_SET_MIN + 4)		//设置测到识别区域
//#define ITS_ROADWAY_CMD_SET_VLOOP   (ITS_ROADWAY_CMD_SET_MIN + 5)		//设置虚拟线圈
//#define ITS_ROADWAY_CMD_SET_LIGHT   (ITS_ROADWAY_CMD_SET_MIN + 6)		//设置车道信号灯
//#define ITS_ROADWAY_CMD_SET_CAPTURE (ITS_ROADWAY_CMD_SET_MIN + 7)		//设置车道抓拍
//#define ITS_ROADWAY_CMD_SET_REFERENCELINE	(ITS_ROADWAY_CMD_SET_MIN + 8)		//设置车道绊线
//#define ITS_ROADWAY_CMD_SET_MAX     (ITS_ROADWAY_CMD_SET_MIN + 9)		//
//
//#define ITS_ROADWAY_CMD_GET_MIN     0
//#define ITS_ROADWAY_CMD_GET_ENABLE  (ITS_ROADWAY_CMD_GET_MIN + 0)	    //获得车道使能
//#define ITS_ROADWAY_CMD_GET_LOOP    (ITS_ROADWAY_CMD_GET_MIN + 1)		//获得车道线圈
//#define ITS_ROADWAY_CMD_GET_TIME    (ITS_ROADWAY_CMD_GET_MIN + 2)		//获得车道时间
//#define ITS_ROADWAY_CMD_GET_SPEED   (ITS_ROADWAY_CMD_GET_MIN + 3)		//获得车道速度
//#define ITS_ROADWAY_CMD_GET_RECO    (ITS_ROADWAY_CMD_GET_MIN + 4)		//获得测到识别区域
//#define ITS_ROADWAY_CMD_GET_VLOOP   (ITS_ROADWAY_CMD_GET_MIN + 5)		//获得虚拟线圈
//#define ITS_ROADWAY_CMD_GET_LIGHT   (ITS_ROADWAY_CMD_GET_MIN + 6)		//获得车道信号灯
//#define ITS_ROADWAY_CMD_GET_CAPTURE (ITS_ROADWAY_CMD_GET_MIN + 7)		//获得车道抓拍
//#define ITS_ROADWAY_CMD_GET_REFERENCELINE	(ITS_ROADWAY_CMD_GET_MIN + 8)	//设置车道绊线
//#define ITS_ROADWAY_CMD_GET_MAX     (ITS_ROADWAY_CMD_GET_MIN + 9)		//
///************************************************************************/
///*	智能交通车牌优化
///************************************************************************/
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN                   0
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_FIRST_HZ				(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 0)	    //设置车牌优化首汉字
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_NOPLATE_ENABLE		(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 1)		//设置是否允许无牌车
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_OTHER					(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 2)		//设置待检索车牌和不可信车牌
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MAX					(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 3)		//
//
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN                   0										   		
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_FIRST_CHARACTER       (ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 0)		//获得车牌优化首汉字
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_NOPLATE_ENABLE		(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 1)		//获得是否允许无牌车
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_OTHER					(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 2)		//获得待检索车牌和不可信车牌
//#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MAX					(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 3)		//
///************************************************************************/
///*  交通违章检测球  
///************************************************************************/
//#define ITS_EXTRAINFO_CMD_SET_MIN								 0
////违停项目
//#define ITS_ILLEGALPARK_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 0)	    //设置违章停车参数
//#define ITS_ILLEGALPARKPARM_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 1)		//设置违章停车标定区域参数
//#define ITS_LICENSEOPTIMIZEOTHER_CMD_SET						(ITS_EXTRAINFO_CMD_SET_MIN + 2)		//设置待检索车牌和不可信车牌
//#define ITS_OPTIM_CMD_SET										(ITS_EXTRAINFO_CMD_SET_MIN + 3)		//设置车牌优化首汉字
//#define ITS_RECOPARAM_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 4)		//设置识别算法参数
//#define ITS_ROADWAYENABLE_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 5)		//设置车道
//#define ITS_CAMLOCATION_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 6)		//设置设备信息
//#define ITS_EXACTCONFIRM_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 7)		//设置精确定位信息
////智能相机
//#define ITS_VIDEODECTECT_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 8)		//图像检测参数
//#define ITS_DETECTAREA_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 10)	//轨迹分析检测区域参数
//#define ITS_RECOTYPE_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 11)	//算法类型参数
////交通一体机
//#define ITS_REDLIGHTDETECTAREA_CMD_SET							(ITS_EXTRAINFO_CMD_SET_MIN + 12)	//设置红灯检测区域参数
//#define ITS_ENABLE_CMD_SET										(ITS_EXTRAINFO_CMD_SET_MIN + 13)	//设置交通相关功能使能协议
//
//#define ITS_EXTRAINFO_CMD_SET_MAX								(ITS_EXTRAINFO_CMD_SET_MIN + 15)	//
//
//#define ITS_EXTRAINFO_CMD_GET_MIN								 0
////违停项目
//#define ITS_ILLEGALPARK_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 0)	    //获得违章停车参数
//#define ITS_ILLEGALPARKPARM_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 1)		//获得违章停车标定区域参数
//#define ITS_LICENSEOPTIMIZEOTHER_CMD_GET						(ITS_EXTRAINFO_CMD_GET_MIN + 2)		//获得待检索车牌和不可信车牌
//#define ITS_OPTIM_CMD_GET										(ITS_EXTRAINFO_CMD_GET_MIN + 3)		//获得车牌优化首汉字
//#define ITS_RECOPARAM_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 4)		//获得识别算法参数
//#define ITS_ROADWAYENABLE_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 5)		//获得车道
//#define ITS_CAMLOCATION_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 6)		//获得设备信息
////智能相机
//#define ITS_VIDEODECTECT_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 7)		//图像检测参数
//#define ITS_DETECTAREA_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 9)		//轨迹分析检测区域参数
//#define ITS_RECOTYPE_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 10)	//算法类型参数
//#define ITS_CAMRATYPE_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 11)	//相机类型
////交通一体机
//#define ITS_REDLIGHTDETECTAREA_CMD_GET							(ITS_EXTRAINFO_CMD_SET_MIN + 12)	//获得红灯检测区域参数
//#define ITS_ENABLE_CMD_GET										(ITS_EXTRAINFO_CMD_SET_MIN + 13)	//获得交通相关功能使能协议
//#define ITS_VERSIONPRO_CMD_GET									(ITS_EXTRAINFO_CMD_SET_MIN + 14)	//获得相机版本信息
//
//#define ITS_EXTRAINFO_CMD_GET_MAX								(ITS_EXTRAINFO_CMD_GET_MIN + 15)	//
////CMD集锦END 建议保留原位置注释，以便相关参数在同一个位置，提高可读性

/************************************************************************
*	相机测光区域坐标                                                                   
************************************************************************/
#define MAX_ITS_BLOCK        5  


struct ITS_TBlock  
{
	int iX;					
	int iY;
};

struct ITS_TOTAL_TBlock
{
	ITS_TBlock block[MAX_ITS_BLOCK];
};
/************************************************************************
*	锐视相机时间段                                                                     
************************************************************************/
#define ITS_CMD_SET_TIMERANGE_ENABLE			0                           //设置时间段使能
#define ITS_CMD_SET_TIMERANGE_AGCBLOCK			1							//设置时间段测光区域使能
#define ITS_CMD_SET_TIMERANGE_FLASHLAMP			2							//设置时间段闪光灯使能

#define ITS_CMD_GET_TIMERANGE_ENABLE			3							//获取时间段使能
#define ITS_CMD_GET_TIMERANGE_AGCBLOCK			4							//获取时间段测光区域使能
#define ITS_CMD_GET_TIMERANGE_FLASHLAMP			5							//获取时间段闪光灯使能

#define MAX_ITS_TIMERANGE                8

struct ITS_TTimeRange 
{
	int iEnable;								//是否启用该时间段，1-启用，0-不启用
	int iTimeRange;								//时间范围： bit24-bit31:开始小时
	//					bit16-bit23:开始分钟
	//					bit8-bit15:结束小时
	//					bit0-bit7:结束分钟	
};

struct ITS_TOTAL_TTimeRange 
{
	ITS_TTimeRange timerange[MAX_ITS_TIMERANGE];
};
/************************************************************************
*	锐视相机时间段通用参数                                                                     
************************************************************************/
#define MAX_ITS_TEMPLATE                8
#define MAX_TIME_RANGE_PARAM  			25
struct ITS_TTimeRangeParam 
{
	int iType;							// 0-设置增益 1-设置曝光 2-设置白平衡 3-设置亮度
	int iAutoEnable[MAX_TIME_RANGE_PARAM];	//  1、1-自动；0-手动。
	//	2、特殊说明（iType为12时，0-日光模式；1-荧光灯模式；2-不进行白平衡）。
	//	3、iType为255时，代表：1-自动；0-手动。
	//  4、iType为8时1-自动（普通模式），0-手动 2-自动（专家模式）3-ITS相机3D降噪级别   //add by wd @20130619
	int iParam1[MAX_TIME_RANGE_PARAM];		//0--光圈调节：手动下：代表具体值；自动下：1开启光圈，0关闭光圈。
	//1--超宽动态：1代表开启；0代表关闭
	//2--背光补偿：1代表开启；0代表关闭
	//3--曝光时间：手动下：代表具体值；自动下：代表期望值
	//4--快门调节：手动下：代表具体值；自动下：代表期望值
	//5--增益调节：手动下：代表具体值；自动下：代表期望值
	//6--gamma调节：手动下：代表具体值；自动下：代表期望值
	//7--锐度调节：手动下：代表具体值；自动下：代表期望值
	//8--降噪调节：手动下：代表具体值；自动(简单模式)下：代表期望值：自动(专家模式)下：代表2D降噪期望值   ITS相机3D降噪级别：3-高，2-中，1-低，0-最低 //add by wd @20130619
	//9--曝光区域：代表左上角X坐标
	//10--背光补偿区域：代表左上角X坐标
	//11--AF区域设置：代表左上角X坐标
	//12--目标亮度调节：手动下：代表具体值；自动下：代表期望值
	//13--白平衡调节：手动下：代表白平衡的R分量：0-255；自动下：代表白平衡的R分量校正系数：范围100-200，精度为5
	//14--jpeg图像质量
	//15--lut使能
	//16--自动亮度调节使能
	int iParam2[MAX_TIME_RANGE_PARAM];		//0--光圈调节：未使用
	//1--超宽动态：未使用
	//2--背光补偿：未使用
	//3--曝光时间：手动下：未使用；自动下：代表上限值
	//4--快门调节：手动下：未使用；自动下：代表上限值
	//5--增益调节：手动下：未使用；自动下：代表上限值
	//6--gamma调节：手动下：未使用；自动下：代表上限值
	//7--锐度调节：手动下：未使用；自动下：代表上限值
	//8--降噪调节：手动下：未使用；自动(简单模式)下：未使用：自动(专家模式)下：代表3D降噪期望值
	//9--曝光区域：代表左上角Y坐标
	//10--背光补偿区域：代表左上角Y坐标
	//	11--AF区域设置：代表左上角Y坐标
	//12--目标亮度调节：手动下：代表具体值；自动下：代表上限值
	//13--白平衡调节：手动下：代表白平衡的G分量：0-255；自动下：代表白平衡的G分量校正系数：范围100-200，精度为5
	//14--jpeg图像质量
	//15--lut使能
	//16--自动亮度调节使能
	int iParam3[MAX_TIME_RANGE_PARAM];		//0--光圈调节：未使用
	//1--超宽动态：未使用
	//	2--背光补偿：未使用
	//3--曝光时间：手动下：未使用；自动下：代表下限值
	//4--快门调节：手动下：未使用；自动下：代表下限值
	//5--增益调节：手动下：未使用；自动下：代表下限值
	//6--gamma调节：手动下：未使用；自动下：代表下限值
	//7--锐度调节：手动下：未使用；自动下：代表下限值
	//8--降噪调节：手动下：未使用；自动下：未使用
	//9--曝光区域：代表右下角X坐标
	//10--背光补偿区域：代表右下角X坐标
	//11--AF区域设置：代表右下角X坐标
	//12--目标亮度调节：手动下：代表具体值；自动下：代表下限值
	//13--白平衡调节：手动下：代表白平衡的B分量：0-255；自动下：代表白平衡的B分量校正系数：范围100-200，精度为5
	//14--jpeg图像质量
	//15--lut使能
	//16--自动亮度调节使能
	int iParam4[MAX_TIME_RANGE_PARAM];		//0--光圈调节：未使用
	//1--超宽动态：未使用
	//2--背光补偿：未使用
	//3--曝光时间：未使用
	//4--快门调节：未使用
	//5--增益调节：未使用
	//6--gamma调节：未使用
	//7--锐度调节：未使用
	//8--降噪调节：未使用
	//9--曝光区域：代表右下角Y坐标
	//10--背光补偿区域：代表右下角Y坐标
	//11--AF区域设置：代表右下角Y坐标
	//12--目标亮度调节：未使用
	//13--白平衡调节：未使用
	//14--jpeg图像质量
	//15--lut使能
	//16--自动亮度调节使能
};

struct ITS_TOTAL_TTimeRangeParam 
{
	ITS_TTimeRangeParam timerangeparam[MAX_ITS_TEMPLATE +1];
};

struct ITS_TTemplateMap 
{
	int iTemplateID;					//模板编号
	char cTemplateName[64];				//模板名称
};

struct ITS_TOTAL_TTemplateMap 
{
	ITS_TTemplateMap templatemap[MAX_ITS_TIMERANGE];
};

typedef struct ITS_ILLEGALRECORD
{
	long m_lCarID;
	int  m_iRecordFlag;
	int  m_iIllegalType;
	int  m_iPreset;
}*pITS_ILLEGALRECORD;

/************************************************************************
*	锐视相机工作模式                                                                    
************************************************************************/
struct ITS_CamWorkMode 
{
	int iWorkMode;							//工作模式  0-卡口模式   1-超速模式
	int iInterval;								//时间间隔	
};

/************************************************************************/
//*   智能交通车道参数                                                                 
/************************************************************************/

//从9开始GET/SET使用统一的宏定义，增加时注意修改ITS_ROADWAY_CMD_GET_MAX/ITS_ROADWAY_CMD_SET_MAX的值
#define ITS_ROADWAY_CMD_SET_MIN				0
#define ITS_ROADWAY_CMD_SET_ENABLE			(ITS_ROADWAY_CMD_SET_MIN + 0)	    //设置车道使能
#define ITS_ROADWAY_CMD_SET_LOOP			(ITS_ROADWAY_CMD_SET_MIN + 1)		//设置车道线圈
#define ITS_ROADWAY_CMD_SET_TIME			(ITS_ROADWAY_CMD_SET_MIN + 2)		//设置车道时间
#define ITS_ROADWAY_CMD_SET_SPEED			(ITS_ROADWAY_CMD_SET_MIN + 3)		//设置车道速度
#define ITS_ROADWAY_CMD_SET_RECO			(ITS_ROADWAY_CMD_SET_MIN + 4)		//设置测到识别区域
#define ITS_ROADWAY_CMD_SET_VLOOP			(ITS_ROADWAY_CMD_SET_MIN + 5)		//设置虚拟线圈
#define ITS_ROADWAY_CMD_SET_LIGHT			(ITS_ROADWAY_CMD_SET_MIN + 6)		//设置车道信号灯
#define ITS_ROADWAY_CMD_SET_CAPTURE			(ITS_ROADWAY_CMD_SET_MIN + 7)		//设置车道抓拍
#define ITS_ROADWAY_CMD_SET_REFERENCELINE	(ITS_ROADWAY_CMD_SET_MIN + 8)		//设置车道绊线
#define ITS_ROADWAY_CMD_CHNLCARSPEED        (ITS_ROADWAY_CMD_SET_MIN + 9)		//设置/获取 车道不同车辆类型的速度检测参数
#define ITS_ROADWAY_CMD_SET_MAX				(ITS_ROADWAY_CMD_SET_MIN + 10)		

#define ITS_ROADWAY_CMD_GET_MIN				0
#define ITS_ROADWAY_CMD_GET_ENABLE			(ITS_ROADWAY_CMD_GET_MIN + 0)	    //获得车道使能
#define ITS_ROADWAY_CMD_GET_LOOP			(ITS_ROADWAY_CMD_GET_MIN + 1)		//获得车道线圈
#define ITS_ROADWAY_CMD_GET_TIME			(ITS_ROADWAY_CMD_GET_MIN + 2)		//获得车道时间
#define ITS_ROADWAY_CMD_GET_SPEED			(ITS_ROADWAY_CMD_GET_MIN + 3)		//获得车道速度
#define ITS_ROADWAY_CMD_GET_RECO			(ITS_ROADWAY_CMD_GET_MIN + 4)		//获得测到识别区域
#define ITS_ROADWAY_CMD_GET_VLOOP			(ITS_ROADWAY_CMD_GET_MIN + 5)		//获得虚拟线圈
#define ITS_ROADWAY_CMD_GET_LIGHT			(ITS_ROADWAY_CMD_GET_MIN + 6)		//获得车道信号灯
#define ITS_ROADWAY_CMD_GET_CAPTURE			(ITS_ROADWAY_CMD_GET_MIN + 7)		//获得车道抓拍
#define ITS_ROADWAY_CMD_GET_REFERENCELINE	(ITS_ROADWAY_CMD_GET_MIN + 8)		//获得车道绊线
#define ITS_ROADWAY_CMD_GET_MAX				(ITS_ROADWAY_CMD_GET_MIN + 10)		

#define MAX_ROADWAY_COUNT					4          //最大车道数
#define MAX_LOOP_COUNT						4          //车道内最大线圈数
#define DAY_OR_NIGHT						2          //0---白天，1---晚上

#define LIGHT_COUNT_EX                      8                   //信号灯数 
#define LIGHT_COUNT							4					//信号灯数
#define LIGHT_COM_COUNT						4					//信号灯串口数
#define CAPTURE_PLACE_COUNT					3					//车道对应的抓拍位置数目

#define CAPTURE_TYPE_MASK					0x01FF				// 升级到后8位 [4/19/2012 hanyongqiang]
#define CAPTURE_TYPE_GATE					0x01				//卡口
#define CAPTURE_TYPE_RED_LIGHT				0x02				//闯红灯 
#define CAPTURE_TYPE_REVERSE				0x04				//逆行
#define CAPTURE_TYPE_OVERSPEED				0x08				//超速

//智能相机扩展
#define	MAX_ITS_REFLINE_NUM		25
#define MAX_ITS_DETECTMODE		5

struct TITSRoadwayInfo 
{
	int iRoadwayID;
	int  iEnable;
	char cChannelName[32];
	char cChannelDir[32];
};

struct TITSRoadwayInfoEx
{
	int iRoadwayID;
	int  iEnable;
	char cChannelName[51];
	char cChannelDir[32];
};

//add by wd @20130531 设置车道信息 扩展
typedef struct __tagTITSRoadwayInfo_V1
{
	int  iBufSize;                //根据所需结构体的长度(可自定义)
	int  iRoadwayID;              //车道编号 最大支持4个车道：0-3
	int  iEnable;                 //车道使能标志  1-使能；0-不使能
	char cChannelName[51];        //车道名称  长度不超过50字符
	char cChannelDir[32];         //车道方向  长度不超过31字符
	int	 iChannelDownUp;          //车道上下行  0-上行，1-下行
	//add by wd 20130619 扩展字段 如下
	int  iUses;                   //车道用途 0-普通车道，1-非机动车道，2-公交车道,3-小型汽车车道
} TITSRoadwayInfo_V1, *PTITSRoadwayInfo_V1;
//add ended

struct TITSRoadWayLoop
{
	int iRoadwayID;
	int iComportNo;
	int iSpeedLoopNo;
	int iCaptureLoopNo;
};

struct TITSRoadwayTime
{
	int iRoadwayID;
	int iLoopMaxTime;
	int iLoopMinTime;
	int iLoopDelayTime;
};

struct TITSRoadwaySpeed
{
	int iRoadwayID;
	int iLoopDistance;
	int iSpeedLimit;
	int iSpeedModify;
};

struct TITSRoadwayReco
{
	int iRoadwayID;
	int iRoadwayRange;
};

struct TITSRoadwayVLoop
{
	int iRoadwayID;
	int iLoopID;
	int iDayNight;
	int iPoint1[DAY_OR_NIGHT][MAX_LOOP_COUNT];
	int iPoint2[DAY_OR_NIGHT][MAX_LOOP_COUNT];
	int iPoint3[DAY_OR_NIGHT][MAX_LOOP_COUNT];
	int iPoint4[DAY_OR_NIGHT][MAX_LOOP_COUNT];
};

struct TITSRoadwayLight			//信号灯
{
	int iRoadwayID;
	int iComNo;				//信号灯对应的串口号，范围0-2（其中0、1为RS232串口，2为RS485串口）
	int iFloodID;			//补光灯编号,按位					
	char cLightID[32];	//其他信号灯,格式4,0,1,2,3……(第一位标示一共几个灯，后面对于4路红灯检测器，范围0-3。)					
};
//智能相机扩展
typedef struct __tagTITSRoadwayLight_V1
{
	TITSRoadwayLight m_stLight;
	int				 m_iCompelRedlight;		//强制红灯
}TITSRoadwayLight_V1, *PTITSRoadwayLight_V1;

struct TITSRoadwayCapture			//抓拍位置
{
	int iRoadwayID;                         //车道编号   最大支持4个车道：0-3
	int iType;							//车道抓拍类型
	//bit0--卡口
	//bit1--闯红灯 
	//bit2--逆行 
	//bit3--超速
	//bit4--禁止左行驶抓拍 
	//bit5--禁止右行驶抓拍 
	//bit6--压黄线抓拍
	//bit7--非机动车抓拍
	//bit8--不按规定车道行驶 (不按导向行驶)
	//bit9--禁止直行    //add by wd @20130619 扩展
	//bit10--公交车道
	//bit11--压车道线
	//bit12--待转区域闯红灯
	//bit13--违法停车  //add end
	char cPlace[CAPTURE_PLACE_COUNT][64];	//车辆经过线圈时的抓拍位置
	//0——不抓拍
	//1——进入测速线圈时抓拍
	//2——离开测速线圈时抓拍
	//3——进入抓拍线圈时抓拍
	//4——离开抓拍线圈时抓拍
	//5——延时抓拍
	//按类型进行，例：1,2,3,4
	int iChannelTpye;                       //类别
	//0--左转车道
	//1--右转车道
	//2--直行车道
	//3--左转直行车道
	//4--右转直行车道
	//5--非机动车道 ---预留                 //modify by wd @20130619 
	//6--左转右转车道
	//7--左转车道加待转线
	int iRecognizePlace;                   //识别策略
	//0--识别第一张
	//1--识别第二张
	//2--先识别第一张再识别第二张,取置信度高的结果
	//3--识别第二张,如果未识别出结果,再识别第一张
	//4--识别第一张,如果未识别出结果,再识别第二张
	//5—识别第三张                        //add by wd @20130619 
};

struct ITS_RecoParamEx					//锐视相机识别算法扩展参数   
{
	int iMaxPlateNO;					//最大车牌数
	int iMaxPlateWidth;					//最大车牌宽度
	int iMinPlateWidth;					//最小车牌宽度
	int iRoadwayID;						//车道编号
	int iEnable;						//使能标志	0：禁用识别；1：启用识别					
	int iEngineNum;						//识别引擎个数	暂不支持，填0即可	
	int iAreaType;						//识别区域类型
	int iPlateType;						//识别车辆类型
	int iSpeed;							//车辆速度。注：车辆速度指的是车辆在视频画面中的移动速度，而非车辆的实际行使速度。	范围1-10					
	int iMaxSkip;						//最大遮挡帧数
	int iMinValid;						//最小车牌置信度
	int iFramePercent;					//识别比率
	int iMinCapDiff;					//抓图更新阈值
	char cCaliInfo[76];					//车牌标定  20120229扩展
	//20121030扩展
	int	iPlateCharType;					//车牌每一位的识别字符类型,
	//当前车牌为7位，使用后14位表示每位车牌的字符类型，每两位表示一位字符类型
	//00-汉字 01-字母 10-数字 11-字母或数字
	int iConfid;						//车牌置信度阈值
};

//ITS绊线参数---智能相机v3.2
typedef struct __tagTITS_RefLine
{
	int			m_iLineID;
	int			m_iEnable;
	int			m_iLineType;
	vca_TLine	m_stLine1;
	vca_TLine	m_stLine2;				//预留
	int			m_iDistance;
}TITS_RefLine, *PTITS_RefLine;

typedef struct __tagTITS_ReflineAarry
{
	int			m_iRoadwayID;
	int			m_iLineNum;
	TITS_RefLine m_stLines[MAX_ITS_REFLINE_NUM];
}TITS_RefLineAarry, *PTITS_ReflineArray;


#define MAX_VEHICLE_TYPE 3//最大车辆类型数
typedef struct __tagTITS_ChnCarSpeedPara
{
	int iCarWayNo;						//车道编号：最大支持4个车道，0-3
	int iCarType;						//车辆类型：0-不检测，1-小车，2-大车
	int iSpeedHighLimit;				//车道限速上限：m/s（解析时除以1000，转换成保留3为小数）
	int iSpeedLowLimit;					//车道限速下限：m/s（解析时除以1000，转换成保留3为小数）
	int iHighExceedPercent;				//高速执法百分比：0-100
	int iLowExceedPercent;				//低速执法百分比：0-100
}TITS_ChnCarSpeedPara, *PTITS_ChnCarSpeedPara;


struct TITSRoadwayParam
{
	int iRoadWayID;

	//modified by wd @20130531 
	//TITSRoadwayInfoEx info;
	TITSRoadwayInfo_V1 RoadWayInfo;
	//modified end

	TITSRoadWayLoop loop;
	TITSRoadwayTime time;
	TITSRoadwaySpeed speed;
	TITSRoadwayReco reco;
	TITSRoadwayVLoop vloop;
	TITSRoadwayCapture capture;
	TITSRoadwayCapture captureNew;
	ITS_RecoParamEx recopara;
	TITSRoadwayLight_V1	light;
	TITS_RefLineAarry   m_stLineArray;	
};

/************************************************************************/
//*	智能交通车牌优化
/************************************************************************/

#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN                   0
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_FIRST_HZ				(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 0)	    //设置车牌优化首汉字
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_NOPLATE_ENABLE		(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 1)		//设置是否允许无牌车
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_OTHER					(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 2)		//设置待检索车牌和不可信车牌
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MAX					(ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_MIN + 3)		//

#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN                   0										   		
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_FIRST_CHARACTER       (ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 0)		//获得车牌优化首汉字
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_NOPLATE_ENABLE		(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 1)		//获得是否允许无牌车
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_OTHER					(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 2)		//获得待检索车牌和不可信车牌
#define ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MAX					(ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_MIN + 3)		//

struct TITSLicensePlateOptimizeFirstHZInfo
{
	char cModifyChar[9];
	int iMinCharConfid;
	char cModifyAlpha[10];
	int iMinAlphaConfig;
};

struct TITSLicesePlateOptimizeOther    //检索车牌和不可信车牌
{
	int iType;                         //类型 0：待检索汉字；1：不可信汉字
	int iCount;                        //首汉字数目 最多支持8个
	char cModifyChar[8][3];            //首汉字    应设置成邻省车牌首汉字或不可能出现的车牌首汉字。不超过4个字节
};

#define MAX_OPTIMIZEOTHERTYPE_NUM 2    //0：待检索汉字；1：不可信汉字
struct TITSLicensePlateOptimizeParam
{
	int iEnableNoPlate;
	TITSLicensePlateOptimizeFirstHZInfo  firstHZinfo;
	//modify by wd @20130626
	TITSLicesePlateOptimizeOther other[MAX_OPTIMIZEOTHERTYPE_NUM];
};

/************************************************************************/
///*  设置待检索车牌和不可信车牌//非本地车牌 
/************************************************************************/
#define  MAX_MODIFYCHAR_COUNT    8
struct ITS_LicenseOptimizeOther
{
	int			iType;      							//0：待检索汉字；1：不可信汉字
	int			iCount;									//首汉字数目 最多支持8个
	char		cModifyChar[MAX_MODIFYCHAR_COUNT][5];	//应设置成邻省车牌首汉字或不可能出现的车牌首汉字。不超过4个字节
	int			iOtherCharWeight[MAX_MODIFYCHAR_COUNT];	//首汉字优化最低置信度
} ;

/************************************************************************/
///*  交通违章检测球  
/************************************************************************/
#define ITS_EXTRAINFO_CMD_SET_MIN								 0
//违停项目
#define ITS_ILLEGALPARK_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 0)	    //设置违章停车参数
#define ITS_ILLEGALPARKPARM_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 1)		//设置违章停车标定区域参数
#define ITS_LICENSEOPTIMIZEOTHER_CMD_SET						(ITS_EXTRAINFO_CMD_SET_MIN + 2)		//设置待检索车牌和不可信车牌
#define ITS_OPTIM_CMD_SET										(ITS_EXTRAINFO_CMD_SET_MIN + 3)		//设置车牌优化首汉字
#define ITS_RECOPARAM_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 4)		//设置识别算法参数
#define ITS_ROADWAYENABLE_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 5)		//设置车道
#define ITS_CAMLOCATION_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 6)		//设置设备信息
#define ITS_EXACTCONFIRM_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 7)		//设置精确定位信息
//智能相机
#define ITS_VIDEODECTECT_CMD_SET								(ITS_EXTRAINFO_CMD_SET_MIN + 8)		//图像检测参数
#define ITS_DETECTAREA_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 10)	//轨迹分析检测区域参数
#define ITS_RECOTYPE_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 11)	//算法类型参数
//交通一体机
#define ITS_REDLIGHTDETECTAREA_CMD_SET							(ITS_EXTRAINFO_CMD_SET_MIN + 12)	//设置红灯检测区域参数
#define ITS_ENABLE_CMD_SET										(ITS_EXTRAINFO_CMD_SET_MIN + 13)	//设置交通相关功能使能协议
#define ITS_DAYNIGHT_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 14)	//设置交通相关功能使能协议
#define ITS_WORKMODE_CMD_SET									(ITS_EXTRAINFO_CMD_SET_MIN + 15)	//设置工作模式
#define  ITS_LIGHTINFO_CMD_SET                                  (ITS_EXTRAINFO_CMD_SET_MIN + 16)   //设置信号灯对应的参数
//add by wd @20130603
#define ITS_CROSSINFO_CMD_SET                                   (ITS_EXTRAINFO_CMD_SET_MIN + 17)	//设置路口信息参数
//add by wd @20130619
#define ITS_AREAINFO_CMD_SET                                    (ITS_EXTRAINFO_CMD_SET_MIN + 18)    //设置增益区域参数
#define ITS_EXTRAINFO_CMD_SET_MAX								(ITS_EXTRAINFO_CMD_SET_MIN + 19)	//最大
//end

#define ITS_EXTRAINFO_CMD_GET_MIN								 0
//违停项目
#define ITS_ILLEGALPARK_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 0)	    //获得违章停车参数
#define ITS_ILLEGALPARKPARM_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 1)		//获得违章停车标定区域参数
#define ITS_LICENSEOPTIMIZEOTHER_CMD_GET						(ITS_EXTRAINFO_CMD_GET_MIN + 2)		//获得待检索车牌和不可信车牌
#define ITS_OPTIM_CMD_GET										(ITS_EXTRAINFO_CMD_GET_MIN + 3)		//获得车牌优化首汉字
#define ITS_RECOPARAM_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 4)		//获得识别算法参数
#define ITS_ROADWAYENABLE_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 5)		//获得车道
#define ITS_CAMLOCATION_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 6)		//获得设备信息
//智能相机
#define ITS_VIDEODECTECT_CMD_GET								(ITS_EXTRAINFO_CMD_GET_MIN + 7)		//图像检测参数
#define ITS_DETECTAREA_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 9)		//轨迹分析检测区域参数
#define ITS_RECOTYPE_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 10)	//算法类型参数
#define ITS_CAMRATYPE_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 11)	//相机类型
//交通一体机
#define ITS_REDLIGHTDETECTAREA_CMD_GET							(ITS_EXTRAINFO_CMD_SET_MIN + 12)	//获得红灯检测区域参数
#define ITS_ENABLE_CMD_GET										(ITS_EXTRAINFO_CMD_SET_MIN + 13)	//获得交通相关功能使能协议
#define ITS_VERSIONPRO_CMD_GET									(ITS_EXTRAINFO_CMD_SET_MIN + 14)	//获得相机版本信息
#define ITS_DAYNIGHT_CMD_GET									(ITS_EXTRAINFO_CMD_SET_MIN + 15)	//设置交通相关功能使能协议
#define ITS_WORKMODE_CMD_GET									(ITS_EXTRAINFO_CMD_GET_MIN + 16)    //获取工作模式
#define ITS_LIGHTINFO_CMD_GET                                   (ITS_EXTRAINFO_CMD_GET_MIN + 17)    //获取信号灯对应的参数
//add by wd @20130603
#define ITS_CROSSINFO_CMD_GET	                                (ITS_EXTRAINFO_CMD_GET_MIN + 18)	//获取路口信息参数
//add by wd @20130619
#define ITS_AREAINFO_CMD_GET	                                (ITS_EXTRAINFO_CMD_GET_MIN + 19)    //获取增益区域参数
#define ITS_EXTRAINFO_CMD_GET_MAX								(ITS_EXTRAINFO_CMD_GET_MIN + 21)	//最大
//add end

#define MAX_PRESET_COUNT			8					//违章停车最多预置位数
#define MAX_AREA_COUNT				4					//违章停车最多区域数
#define MAX_PARAM_COUNT				4					//违章停车四边形区域中最多标定位置数
/************************************************************************/
///*  设置违章停车参数  
/************************************************************************/
//struct ITS_IllegalPark
//{
//	int			iPresetNo;      						//预置位编号
//	int			iAreaNo;								//区域编号
//	int		  	iIllegalParkTime;						//违章停车检测时间
//	int			iTimeRange[MAX_TIMESEGMENT];								//使能时间范围
//	POINT		arrPTArea[MAX_AREA_COUNT];				//区域四个点坐标  iX1,iY1:iX2,iY2:iX3,iY3:iX4,iY4
//} ;

struct ITS_IllegalPark                                  //扩展违停参数（iCheckParkTime&iSensitivity）@120905
{
	int			iPresetNo;      						//预置位编号   最多8个，0-7
	int			iAreaNo;								//区域编号     最多4个，0-3
	int		  	iIllegalParkTime;						//违章停车检测时间  秒为单位
	int			iTimeRange[MAX_TIMESEGMENT];								//使能时间范围
	POINT		arrPTArea[MAX_AREA_COUNT];				//区域四个点坐标  iX1,iY1:iX2,iY2:iX3,iY3:iX4,iY4
	int         iCheckParkTime;                         //停车判断时间
	int         iSensitivity;                           //灵敏度等级
} ;

/************************************************************************/
//  设置违章停车标定区域参数 
/************************************************************************/
struct ITS_IllegalParkParm
{
	int			iPresetNo;      					    //预置位编号
	int			iAreaNo;								//区域编号
	POINT       arrPTParam[MAX_PARAM_COUNT][2];         //标定位置两个点坐标 iAX1,iAY1:iAX2,iAY2;iBX1,iBY1:iBX2,BiY2;iCX1,iCY1:iCX2,iCY2;iDX1,iDY1:iDX2,iDY2
} ;

/************************************************************************/
//  设置待检索车牌和不可信车牌//非本地车牌 
/************************************************************************/
//#define  MAX_MODIFYCHAR_COUNT    8
//struct ITS_LicenseOptimizeOther
//{
//	int			iType;      							//0：待检索汉字；1：不可信汉字
//	int			iCount;									//首汉字数目 最多支持8个
//	char		cModifyChar[MAX_MODIFYCHAR_COUNT][5];	//应设置成邻省车牌首汉字或不可能出现的车牌首汉字。不超过4个字节
//	int			iOtherCharWeight[MAX_MODIFYCHAR_COUNT];	//首汉字优化最低置信度
//} ;


/************************************************************************/
//*  设置精确定位参数 
/************************************************************************/
struct ITS_ExactConfirm
{
	int			iPresetNo;      						//预置位编号
	int			iAreaNo;								//区域编号
	int         iLocalPos1;								//标定块编号
} ;

/************************************************************************/
//*							智能相机参数				
/************************************************************************/

#define		MAX_ITS_DETECTAREA_NUM		16
#define		MAX_ITS_AREA_POINTNUM		16
//130T算法私有参数
typedef struct __tagTITS_Params130T
{
	int			m_iZoomRate;
	int			m_iVehicleWidth;
	int			m_iConfidenceValve;
	int			m_iProportion;
}TITS_Params130T, *PTITS_Params130T;

//ITS图像检测参数
typedef	struct __tagTITS_VDetect
{
	int			m_iEngineType;
	int			m_iEnable;
	int			m_iVedioType;
	int			m_iVedioWidth;
	int			m_iVedioHeight;
	int			m_iVehicleMinSize;
	int			m_iVehicleMaxSize;
	int			m_iModelType;
	int			m_iFrameRateCount;
	TITS_Params130T	m_stParmas130T;
}TITS_VDetect, *PTITS_VDetect;

typedef	struct __tagTITS_VDetect_Ex
{
	int				m_iSize;
	TITS_VDetect	m_tVDetect;
	int				m_iVDetectMotor;	//非机动车检测使能
}TITS_VDetect_Ex, *PTITS_VDetect_Ex;

//ITS图像检测区域参数
#define  MAX_ITS_DETECTAREAPOINT_NUM  15
typedef struct __tagTITS_DetectArea
{ 
	int			m_iRegionID;                      //区域编号  0~11
	int			m_iEnabled;                       //使能标记  0：不启用，1：启用 
	int			m_iPointCount;                    //坐标个数 4~15
	vca_TPoint	m_arrPoint[MAX_ITS_AREA_POINTNUM];//标定位置两个点坐标（最多15个点） iAX1:iAY1,iAX2:iAY2,iAX3:iAY3,iAX4:iAY4,…
}TITS_DetectArea, *LTITS_PDetectArea;

/************************************************************************/
//*  交通相关功能使能参数
/************************************************************************/

#define MAX_ITS_ENABLE_NUM	8
#define MAX_ITS_POWERINPHASEENABLE_NUM	0
#define MAX_ITS_ITSMANUALENABLE_NUM	1
struct ITS_EnalbeParam
{
	int iType;	    // 功能类型 0--电源同步功能  1--启动手动模式  2--CRC校验功能  3--视频测速功能 4—红灯增益使能 5—ftp使能
					// 6--图像合成功能   7--人脸识别功能
	int iEnable;	// 0-不使能；1-使能
};

//#define	MAX_ITS_REDLIGHT_DETECTAREA_NUM		4
#define	MAX_ITS_REDLIGHT_DETECTAREA_NUM		8

struct ITS_RedLightDetectArea
{
	int iRegionID;	//红灯区域编号 0-3
	int iEnabled;	//使能标记	0：不启用，1：启用					
	RECT rcStandardArea;	//标定区域位置
	RECT rcReviseArea;		
};

//add by wd @20130603
typedef struct __tagITS_RedLightDetectAreaV1
{
	int  iBufSize;                  //根据所需结构体的长度(可自定义)
	int  iRegionID;	                //红灯编号 8个
	int  iEnabled;	                //使能标记	0：不启用，：启用	
	RECT rcStandardArea;	        //标定区域位置
	RECT rcReviseArea;		
	int  iLightType;                //灯盘类型 0-单灯灯盘，1-三灯灯盘，2-五灯灯盘红，3-五灯灯盘绿
	int  iChannelType;              //红灯区域对应的车道类型 车道类型按位设置,0-不启用，1-启用： bit0-直行 bit1-左转 bit2-右转 bit3-掉头
} ITS_RedLightDetectAreaV1, *PITS_RedLightDetectAreaV1;
//ended

//add by wd @20130603 路口信息结构体
struct ITS_CrossInfo
{
	int iBufSize;                //根据所需结构体的长度(可自定义)
	char pcCrossingID[64];       //路口编号  长度不超过63字符
	char pcCrossingName[64];     //路口名称  长度不超过63字符
};
//add end

//add by wd @20130620增益区域参数
#define  MAX_AREAINFOPOINT_NUM 6
#define	 MAX_ITS_AREAINFOREGIONID_NUM		8     //区域编号 
#define  MAX_ITS_AREAINFO_TYPE				2		//区域类型
struct ITS_AreaInfo
{
	int iBufSize;                 //根据所需结构体的长度
	int iType;                    //区域类型  0—红灯增益
	int iRegionID;               //区域编号区域ID，0~7
	int iEnabled;                //使能标记 0：不启用，1：启用
	int iCount;                  //坐标个数 4~6
	vca_TPoint  stTPoint[MAX_AREAINFOPOINT_NUM];	         //标定位置两个点坐标（最多6个点）
};
//add end

/************************************************************************
*	锐视相机识别算法参数                                                                     
************************************************************************/
struct ITS_RecoParam 
{
	int iMaxPlateNO;					//最大车牌数
	int iMaxPlateWidth;					//最大车牌宽度
	int iMinPlateWidth;					//最小车牌宽度
};

/************************************************************************
*	锐视相机位置                                                                     
************************************************************************/
struct ITS_CamLocation
{
	char cDeviceVode[64];								//设备编号
	char cRoadName[64];									//路口名称
};

//	ITS(智能交通)配置的变量总集
struct ITS_VariableParam
{
	int m_iAgcBlock[MAX_ITS_TIMERANGE];              //时间段测光区域使能
	int m_iFlashLamp[MAX_ITS_TIMERANGE];             //时间段闪光灯使能
	int m_iDetectMode;								 //相机检测模式
	int m_iLoopMode;			  				     //线圈工作模式
	int m_iITSDeviceType;							 //相机外设类型

	//智能相机
	int	m_iITSCamraType;
	//相机版本信息
	char m_strITSVersionPro[1024];	
};


#define CAMERA_PARAM_JPEG_QUALITY			0
#define CAMERA_PARAM_LUT					1

struct TCameraParam
{
	int iParamType;		//参数类型 0:图片质量 1:LUT  其它预留					
	int iParamValue;	//参数值 iParamType=0时：0-100，数值越大质量越好; iParamType=1时：0:不启用;1:启用		
};

/************************************************************************
* 得到设备端连接信息                                                                     
************************************************************************/
#define MAX_CONNECT_COUNT		128

struct TChannelConnectInfo
{
	int iChannelID;					//	取值范围据设备总通道数而定（规则与NVSSDK中相同），数据通道从0开始，命令通道忽略
	char cClientIP[16];				//	客户端IP地址
	int iChannelType;				//通道类型，0代表命令通道，1代表数据通道
	int iNetMode;					//1，TCP； 2，UDP； 3，多播； 4，主动模式
	int iConnectState;				//连接状态，0代表增加连接；  1代表断开连接
	char cUserName[17];				//用户名，最多16个字符
};

struct TTotalConnectInfo
{
	TChannelConnectInfo	connInfo[MAX_CONNECT_COUNT];
};

/************************************************************************
*	平台服务程序列表及控制                                                                     
************************************************************************/
#define MAX_PLATFORM_COUNT			10
#define MAX_PALTFORM_NAME_LENGTH	33

#define PLATFORM_CMD_SET_MIN		0
#define PLATFORM_CMD_SET_RUN		(PLATFORM_CMD_SET_MIN+0)
#define PLATFORM_CMD_SET_MAX		(PLATFORM_CMD_SET_MIN+1)

//#define PLATFORM_CMD_GET_MIN		(PLATFORM_CMD_SET_MAX)			//	考虑下面的扩展兼容性			
#define PLATFORM_CMD_GET_MIN		(1)
#define PLATFORM_CMD_GET_LIST		(PLATFORM_CMD_GET_MIN+0)
#define PLATFORM_CMD_GET_MAX		(PLATFORM_CMD_GET_MIN+1)


struct TPlatformVersion
{
	char cData[33];
};

struct TPlatformApp
{
	char cName[MAX_PLATFORM_COUNT][MAX_PALTFORM_NAME_LENGTH];			//	平台服务程序的名称，最多10个，单个长度最长32字节
	int iState[MAX_PLATFORM_COUNT];										//	各个平台服务程序的状态, 0-停止，1-运行
};

//ATM相关参数
#define ATM_CONFIG_CMD_MIN							0
#define ATM_CONFIG_CMD_ATM_INFO				(ATM_CONFIG_CMD_MIN+0)
#define ATM_CONFIG_CMD_OSD_INFO				(ATM_CONFIG_CMD_MIN+1)
#define ATM_CONFIG_CMD_PROTOCOL_COUNT		(ATM_CONFIG_CMD_MIN+2)
#define ATM_CONFIG_CMD_PROTOCOL_NAME		(ATM_CONFIG_CMD_MIN+3)
#define ATM_CONFIG_CMD_MAX					(ATM_CONFIG_CMD_MIN+4)

#define ATM_PROTOCOL_NAME_LEN 31
#define ATM_PROTOCOL_NAME_COUNT 40
#define ATM_FIELD_COUNT	5
#define ATM_FIELD_LEN	64
#define ATM_CARD_ID_LEN 32

//ATM文件查询相关参数
#define ATM_QUERY_CMD_MIN						0
#define ATM_QUERY_CMD_FIELD				(ATM_QUERY_CMD_MIN+0)
#define ATM_QUERY_CMD_CARD				(ATM_QUERY_CMD_MIN+1)
#define ATM_QUERY_CMD_MAX				(ATM_QUERY_CMD_MIN+2)

typedef struct ATM_INFO
{
	int		iSize;									//Size of the structure,must be initialized before used
	int		iInformWay;								//通信方式 0:串口,1:UDP
	char	cProtocolName[ATM_PROTOCOL_NAME_LEN+1];	//协议类型 协议厂家
	char	cSrcIP[LENGTH_IPV4];					//ATM IP地址
	int		iSrcPort;								//ATM 端口号
	char	cDestIP[LENGTH_IPV4];					//设备IP地址 默认0
	int		iDestPort;								//设备端口号
}*PATM_INFO;

typedef struct ATM_OSD_INFO
{
	int				iSize;					//Size of the structure,must be initialized before used
	int 	        iX; 	    			//横坐标
	int             iY; 	    			//纵坐标
	unsigned int	uEnable;				//使能 通道按位取
}*PATM_OSD_INFO;

typedef struct ATM_PROTOCOL_NAME
{
	int		iSize;							//Size of the structure,must be initialized before used
	int		iIndex;							//协议索引
	char	cName[ATM_PROTOCOL_NAME_LEN+1];	//协议名称
}*PATM_PROTOCOL_NAME;

typedef struct ATM_FIELD_QUERY
{
	int				iSize;										//Size of the structure,must be initialized before used
	int          	iType; 										//录像类型 33:ATM
	int     	    iChannel; 									//通道号 从0开始,0xff代表所有
	NVS_FILE_TIME	struStartTime; 								//开始时间
	NVS_FILE_TIME	struStopTime; 								//结束时间
	int     	    iPageSize;									//页大小
	int         	iPageNo;									//页编号
	int             iFiletype;									//文件类型 0:全部,1:视频,2:图片
	int				iDevType;									//设备类型 0:摄像机,1:网络视频服务器,2:网络摄像机,0xff:全部
	char			cOtherQuery[65];							//字符叠加
	int				iTriggerType;								//报警类型 3:端口报警,4:移动报警,5:视频丢失报警,0x7FFFFFFF:无效
	int				iTrigger;									//端口（通道）号
	char			cField[ATM_FIELD_COUNT][ATM_FIELD_LEN+1];	//域查询
}*PATM_FIELD_QUERY;

typedef struct ATM_CARD_QUERY
{
	int				iSize;					//Size of the structure,must be initialized before used
	int          	iType; 					//录像类型 33:ATM
	int     	    iChannel; 				//通道号 从0开始,0xff代表所有
	NVS_FILE_TIME	struStartTime; 			//开始时间
	NVS_FILE_TIME	struStopTime; 			//结束时间
	int     	    iPageSize;				//页大小
	int         	iPageNo;				//页编号
	int             iFiletype;				//文件类型 0:全部,1:视频,2:图片
	int				iDevType;				//设备类型 0:摄像机,1:网络视频服务器,2:网络摄像机,0xff:全部
	char			cOtherQuery[65];		//字符叠加
	int				iTriggerType;			//报警类型 3:端口报警,4:移动报警,5:视频丢失报警,0x7FFFFFFF:无效
	int				iTrigger;				//端口（通道）号
	char			cID[ATM_CARD_ID_LEN+1];	//卡号
	int				iOperate;				//业务类型 0:代表查询,1:取款,2:改密,3:转账,4:存款,5:无卡查询,6:无卡存款,20:其他
	int				iQuantity;				//金额:代表金额数目（分）
	int				iAbnormity;				//异常情况 0:吞钞,1:吞卡
}*PATM_CARD_QUERY;

typedef struct ATM_FILE_DATA
{
	int				iSize;					//Size of the structure,must be initialized before used
	int             iType; 	        		//录像类型 33:ATM
	int 	        iChannel; 	    		//通道号 从0开始,0xff代表所有
	char 		    cFileName[250]; 		//文件名
	NVS_FILE_TIME	struStartTime; 			//开始时间
	NVS_FILE_TIME	struStoptime; 			//结束时间
	int             iFileSize; 	    		//文件大小
	int				iOperate;				//操作类型 1:取款,2:改密,3:转账,4:存款,5:无卡查询,6:无卡存款,20:其他,21:吞钞,22:吞卡
	NVS_FILE_TIME	struOperateTime;		//操作时间
}*PATM_FILE_DATA;

//音频采样率相关参数
#define AUDIO_SAMPLE_CMD_MIN						0			
#define AUDIO_SAMPLE_CMD_SAMPLE				(AUDIO_SAMPLE_CMD_MIN+0)	//设置或获取某通道的采样率
#define AUDIO_SAMPLE_CMD_SAMPLE_COUNT		(AUDIO_SAMPLE_CMD_MIN+1)	//获得某通道支持的采样率个数
#define AUDIO_SAMPLE_CMD_SAMPLE_LIST		(AUDIO_SAMPLE_CMD_MIN+2)	//获得某通道支持的第几个采样率，对应结构体为AUDIO_SAMPLE
#define AUDIO_SAMPLE_CMD_MAX				(AUDIO_SAMPLE_CMD_MIN+3)

#define MAX_AUDIO_SAMPLE_NUM 16

typedef struct AUDIO_SAMPLE
{
	int				iSize;					//Size of the structure,must be initialized before used
	int				iIndex;					//采样率索引
	int				iSample;				//音频采样率
}*PAUDIO_SAMPLE;

/*-------------------------------------------------------*/
//系统类型参数
#define	SYSTEMTYPE_WORKMODE		0		//	工作模式	
#define SYSTEMTYPE_DEVPROD		1		//	设备制造商
typedef struct __tagSYSTEMTYPE
{
	int m_iSize;
	int m_iWorkMode;					//	不修改此参数时赋0x7FFFFFFF
	int m_iDevProducter;
}SYSTEMTYPE, *LPSYSTEMTYPE;


//交通相关
#define MAX_ROADWAY_COUNT           4          //最大车道数
#define MAX_LOOP_COUNT              4           //车道内最大线圈数
#define DAY_OR_NIGHT                2          //0---白天，1---晚上

#define LIGHT_COUNT							4					//信号灯数
#define LIGHT_COM_COUNT						4					//信号灯串口数
#define CAPTURE_PLACE_COUNT					3					//车道对应的抓拍位置数目

struct TImgDisposal	//图片效果
{
	int iChannelID;
	int iStartUp;		//图片效果处理是否启用标识, 0：不启用 1：启用
	int iQuality;		//质量,	范围：0到100
	int iSaturation;	//饱和度,范围：0到255
	int iBrighten;		//亮度,范围：0到255
	int iContrast;		//对比度,范围：0到255
	int iGamma;			//伽马值,范围：0到50	
	int iAcutance;		//锐度,范围：0到255
	int iImgEnhanceLevel;//图像增强级别,范围：0～3					
};

struct TECOPChannelParam	//车道相关参数
{
	TImgDisposal tImgDisposal;
	int iRecognizeEnable;
	int iWaterMarkEnable;
};

//信号灯对应的参数
struct TITSLightInfo
{
	int iLightID;						//信号灯编号 0-3	
	int iTimeInterval;					//信号灯时间间隔 单位秒	
	int iTimeAcceptDiff;				//信号灯时间容忍值 单位秒					
};
//扩展信号灯参数
//扩展信号灯参数
typedef	struct __tagTITSLightInfoEx
{
	int				iBufSize;
	TITSLightInfo	m_stLightInfo;			//其中 信号灯编号 0-7	
	int				iChannelType;			//信号灯对应的车道类型  车道类型按位设置,0-不启用，1-启用：bit0-直行 bit1-左转 bit2-右转 bit3-掉头
	int				iPhase;					//红灯相位值   相位值 0~360
	int				iDetectType;			//检测红灯还是绿灯 0—红灯　1—绿灯
	int				m_iYellowLightTime;		//黄灯持续时间, 单位ms：0-100000ms----->add new
	int				m_iLightEnhanceLevel;	//红灯增益等级;增益范围：1~255；0-保留；
}TITSLightInfoEx,LPTITSLightInfoEx;

struct TECOPParam
{
	TECOPChannelParam tChannel[MAX_ROADWAY_COUNT];
	int iSystemType;	//系统类型
	//0：调试
	//3：卡口
	//4：电警	
	int iLockRet;		//获取注册结果
	//bit0：识别狗
	//bit1：智能交通加密狗
	//0：未注册，1：注册
	TITSLightInfo tLightInfo[LIGHT_COUNT];
};

typedef int				VIDEO_METHOD;
#define VIDEO_MODE_HAND			0x00
#define VIDEO_MODE_AUT			0x01

#define MAX_MONITOR_DESCLEN     512
typedef struct MONITOR_INFO
{
	char        cDriverDesc[MAX_MONITOR_DESCLEN];
	char        cDriverName[MAX_MONITOR_DESCLEN];	
	RECT		rect;
}*PMONITOR_INFO;

typedef struct
{
	int         m_iStructSize;        //结构体大小
	char        m_cVersion[32];       //服务器版本号
	char		m_cUIVersion[32];	  //UI服务器版本号
	char		m_cSlaveVersion[32];  //从片版本号
	char        m_cPlugInVersion[32]; //外挂版本号 
	char		m_cSCMVersion[32];	  //单片机版本号
}SERVER_VERSION;

/************************************************************************/
/*							串口格式设置                                */
/************************************************************************/
typedef struct COMFORMAT
{
	int				iSize;				//Size of the structure,must be initialized before used
	int				iComNo;				//串口编号
	char			cDeviceName[32];	//协议名称
	char			cComFormat[32];		//格式串 9600,n,8,1
	int				iWorkMode;			//工作模式 1:协议控制,2:透明通道,3:行业预留,4:7601B串行报警主机,5:485键盘
	int				iComType;			//串口类型 0:485,1:232,2:422
} *PCOMFORMAT;

/*-------------------------------------------------------*/
//球机高级参数
#define	MAX_DOME_PRESET_NUM			255	//	最大预置位编号个数
#define	MAX_DOME_SCAN_NUM			255	//	最大扫描编号个数
#define	MAX_DOME_CURISE_NUM			255	//	最大巡航编号个数
#define	MAX_DOME_PATTERN_NUM		255	//	最大模式路径编号个数
#define	MAX_DOME_ZONES_NUM			255	//	最大区域提示编号个数

#define TITLETYPE_RESERVED			0	//	预留
#define TITLETYPE_PRESET			1	//	预置位
#define TITLETYPE_SCAN				2	//	扫描
#define TITLETYPE_CRUISE			3	//	巡航
#define TITLETYPE_PATTERN			4	//	模式路径
#define TITLETYPE_ZONES				5	//	区域提示

#define	MAX_TITLE_LEN				31

#define	CMD_DOME_ADV_SETTITLE		0	//	设置球机标题
typedef struct __tagDOME_TITLE
{
	int		m_iStructSize;				//	结构体size
	int		m_iType;					//	标题类型
	int		m_iNum;						//	标题编号
	char	m_cTitle[MAX_TITLE_LEN+1];	//	标题名
}DOME_TITLE, *LPDOME_TITLE;

/*-------------------------------------------------------*/
//cb@1212068124: SET GET的CMD使用同一个名字，使代码可读性和易用性更好；
#define IPC_CMD_MIN 0
#define IPC_CMD_SENSOR_VOLTAGE       (IPC_CMD_MIN + 0)
#define IPC_CMD_MAX                  (IPC_CMD_MIN + 1)

typedef struct  
{
	int		iType; 
	int		iMold;
	float   iValue;
	int     iReserved;
}HardWare_Param;

typedef struct
{
	unsigned int uiTextColor;
	unsigned char ucOSDText[LENGTH_CHANNEL_TITLE+1];
}OSD_TEXT;

//假日计划相关参数
#define HOLIDAY_PLAN_CMD_MIN						0			
#define HOLIDAY_PLAN_CMD_SCHEDULE			(HOLIDAY_PLAN_CMD_MIN+0)	//设置或获取假日计划录像模板
#define HOLIDAY_PLAN_CMD_MAX				(HOLIDAY_PLAN_CMD_MIN+1)
#define MAX_HOLIDAY_PLAN_SCHEDULE					10

typedef struct
{
	unsigned short iYear;
	unsigned short iMonth;
	unsigned short iDay;
	unsigned short iWeekOfMonth;
	unsigned short iDayOfWeek;
}HOLIDAY_TIME;

typedef struct
{
	int iPlanID;		//计划模板ID,[0,9]
	int iEnable;		//是否使能,1:使能 0:不使能
	char cPlanName[33]; //计划模板名称
	int iMode;			//时间格式,0:按日期(年月日) 1:按星期(月周 星期) 2:按月份(月日)
	HOLIDAY_TIME tStartTime;	//开始时间
	HOLIDAY_TIME tEndTime;		//结束时间
}HOLIDAYPLAN_SCHEDULE;

//M7.6之后设备返回的错误ID		EC:ERROR CODE
//音视频
#define EC_AV_SWITCHOVER_CHANNEL			0x1000	//（数字通道）切换通道类型失败
#define EC_AV_QUERY_FILE					0x1010	//（断电续传）查询不到传输文件
//字符叠加
#define EC_OSD_LOGO_FORMAT					0x2001	//（字符叠加）传输的logo图片格式不对
#define EC_OSD_LOGO_DATA					0x2002	//（字符叠加）传输的logo图片数据错误
//串口PTZ
#define EC_SERIAL_PORT_PTZ					0x3000
//异常
#define EC_EXCEPTION						0x4000
//报警
#define EC_ALARM							0x5000
//存储
#define EC_STORAGE_LOCK_FILE				0x6000	//（加解锁）加锁文件失败
#define EC_STORAGE_UNLOCK_FILE				0x6001	//（加解锁）解锁文件失败
#define EC_STORAGE_REDUNDANCY				0x6010	//（存储策略）没有启动盘组策略，无法启动冗余录像
#define EC_STORAGE_HOLIDAY_TIME				0x6020	//（假日计划）假日模板存在时间冲突
//网络服务
#define EC_NET_SERVICE						0x7000	
//用户
#define EC_LOGON_USERNAME					0x8000	//（登录）用户名不存在
#define EC_LOGON_PASSWORD					0x8001	//（登录）密码错误
#define EC_LOGON_DECRYPT_PWD				0x8002	//（登录）解密密码不对
#define EC_LOGON_AUTHORITY					0x8010	//（操作）用户权限不足
#define EC_LOGON_AUTHORITY_GROUP			0x8020	//（修改用户权限）用户所在组不够，不能配置高权限
//PU设置
#define EC_PU								0x9000
//磁盘管理
#define EC_DISK_RECORDING					0xA000	//(用途)正在录像，无法修改此盘
#define EC_DISK_MEMORY						0xA001	//(用途)盘组中录像磁盘不足
#define EC_DISK_TYPE						0xA002	//(用途)磁盘类型不支持此用途
#define EC_DISK_NO_DISK						0xA010	//(盘组）此盘组没有录像盘
#define EC_DISK_NO_SETTING					0xA011	//（盘组）此盘组未设置任何磁盘
#define EC_DISK_REPEAT_ADD					0xA012	//（盘组）重复添加同一磁盘到不同盘组
#define EC_DISK_NO_RECORD_CHANNEL			0xA013	//（盘组）此盘组中未添加任何录像通道
#define EC_DISK_RECORD_QUOTA_BIG			0xA020	//（配额）录像配额过大
#define EC_DISK_IMAGE_QUOTA_BIG				0xA021	//（配额）图片配额过大
#define EC_DISK_DEL_LOCK_FILE				0xA022	//（配额）修改配额策略时，无法删除加锁文件
//系统管理
#define EC_SYSTEM							0xB000	
//通信
#define EC_COM								0xC000
//网络连接
#define EC_NET_CONNECTION					0xD000	
//智能分析
#define EC_VCA								0xE000	
//ATM
#define EC_ATM								0xF000	
//交通相关
#define EC_ITS								0x10000	
//DZ相关
#define EC_DZ								0x11000	
//通用使能
#define EC_COMMON_ENABLE					0x12000


//M7.6之后设备新增通用使能ID		CI:COMMON ID
#define CI_ALARM_MOTION_DETECT					0x5000
#define CI_ALARM_VIDEO_COVER					0x5001
#define CI_NET_SERVICE_SNMP			0x7000
#define CI_NET_SERVICE_SMTP			0x7001

#define CI_STORAGE_DISK_GROUP		0xA000
#define CI_STORAGE_DISK_QUOTA		0xA001

#define CI_VEHICLE_GPS_CALIBRATION				0x12001
#define CI_VEHICLE_ALARM_THRESHOLD				0x12002
#define CI_VEHICLE_SHUTDOWN_THRESHOLD			0x12003

#define CI_NET_CONNECT_INFO			0xD001      //底层socket发送分包的最大单元
#define CI_COMMON_ID_EIS			0x1001		//电子防抖
 

typedef struct  
{
	int iSNMPEnable;
	int iSMTPEnable[MAX_CHANNEL_NUM];
	int iDiskGroup;
	int iDiskQuota;
	int iMDAlarm[MAX_CHANNEL_NUM];
	int iODAlarm[MAX_CHANNEL_NUM];
	int iGPSCalibration;			//GPS校时 0:禁用,1:启用
	int iAlarmThreshold;			//表示设备低压报警阈值
	int iShutdownThreshold;			//表示设备低压关机阈值
}COMMON_ENABLE;

typedef struct
{ 
	int m_iSize;             //结构体大小
	COMMON_ENABLE tEnable;   //详见COMMON_ENABLE
	int iMTUValue;           //MTU设置（底层socket发送分包的最大单元）       
		
}COMMON_ENABLE_EX;


//add by wd @20130621
//相机抓拍分辨率结构体 
struct JPEGSizeInfo
{
	int iBufSize;                 //根据所需结构体的长度
	int iChannelNo;              //通道号 0~n-1
	int iWidth;                   //抓拍图片宽  宽，像素值
	int iHeight;                 //抓拍图片高  高，像素值
};
//add end

//下载相关参数
#define DOWNLOAD_FLAG_MIN							0
#define DOWNLOAD_FLAG_FIRST_REQUEST		(DOWNLOAD_FLAG_MIN+0)
#define DOWNLOAD_FLAG_OPERATE_RECORD	(DOWNLOAD_FLAG_MIN+1)
#define DOWNLOAD_FLAG_BREAK_CONTINUE	(DOWNLOAD_FLAG_MIN+2)
#define DOWNLOAD_FLAG_MAX				(DOWNLOAD_FLAG_MIN+3)

#define DOWNLOAD_CMD_MIN							0
#define DOWNLOAD_CMD_FILE				(DOWNLOAD_CMD_MIN+0)
#define DOWNLOAD_CMD_TIMESPAN			(DOWNLOAD_CMD_MIN+1)
#define DOWNLOAD_CMD_CONTROL			(DOWNLOAD_CMD_MIN+2)
#define DOWNLOAD_CMD_FILE_CONTINUE		(DOWNLOAD_CMD_MIN+3)
#define DOWNLOAD_CMD_MAX				(DOWNLOAD_CMD_MIN+4)

typedef struct
{
	int				m_iSize;			//结构体大小
	char            m_cRemoteFilename[255];   //前端录像文件名
	char			m_cLocalFilename[255];	  //本地录像文件名
	int				m_iPosition;		//文件定位时,按百分比0～100;断点续传时，请求的文件指针偏移量
	int				m_iSpeed;			//1，2，4，8，控制文件播放速度, 0-暂停
	int				m_iIFrame;			//只发I帧 1,只播放I帧;0,全部播放					
	int				m_iReqMode;			//需求数据的模式 1,帧模式;0,流模式					
}DOWNLOAD_FILE;

typedef struct
{
	int				m_iSize;			//结构体大小
	char			m_cLocalFilename[255]; //本地录像文件名
	int				m_iChannelNO;		//通道号
	NVS_FILE_TIME	m_tTimeBegin;		//开始时间
	NVS_FILE_TIME	m_tTimeEnd;			//结束时间
	int				m_iPosition;		//按时间点定位，>100
	int				m_iSpeed;			//1，2，4，8，控制文件播放速度, 0-暂停
	int				m_iIFrame;			//只发I帧 1,只播放I帧;0,全部播放
	int				m_iReqMode;			//需求数据的模式 1,帧模式;0,流模式
}DOWNLOAD_TIMESPAN;

typedef struct
{
	int				m_iSize;			//结构体大小
	int				m_iPosition;		//0～100，定位文件播放位置；-1，不进行定位
	int				m_iSpeed;			//1，2，4，8，控制文件播放速度, 0-暂停
	int				m_iIFrame;			//只发I帧 1,只播放I帧;0,全部播放
	int				m_iReqMode;			//需求数据的模式 1,帧模式;0,流模式
}DOWNLOAD_CONTROL;

//自动化调试相关协议
#define CMD_AUTOTEST_MIN                    0
#define	CMD_AUTOTEST_RESERVED 				(CMD_AUTOTEST_MIN+0)      //预留
#define	CMD_AUTOTEST_SETMACADDR				(CMD_AUTOTEST_MIN+1)	  //设置MAC地址； 
#define	CMD_AUTOTEST_LAN					(CMD_AUTOTEST_MIN+2)	  //调试网卡
#define	CMD_AUTOTEST_AUDIOIN				(CMD_AUTOTEST_MIN+3)      //调试音频输入；
#define	CMD_AUTOTEST_VIDEOIN				(CMD_AUTOTEST_MIN+4)	  //调试视频输入；
#define	CMD_AUTOTEST_AUDIOOUT				(CMD_AUTOTEST_MIN+5)	  //调试音频输出；
#define	CMD_AUTOTEST_VIDEOOUT				(CMD_AUTOTEST_MIN+6)	  //调试视频输出；
#define	CMD_AUTOTEST_MICIN					(CMD_AUTOTEST_MIN+7)	  //调试MIC输入；
#define	CMD_AUTOTEST_SPEAKER				(CMD_AUTOTEST_MIN+8)	  //调试SPEAKER输出；
#define	CMD_AUTOTEST_VIDEOADJUST			(CMD_AUTOTEST_MIN+9)	  //调试视频调节；协议为：AUTOTEST_ADADJUST
#define	CMD_AUTOTEST_USB					(CMD_AUTOTEST_MIN+10)     //调试USB口；
#define	CMD_AUTOTEST_SATA					(CMD_AUTOTEST_MIN+11)	  //调试SATA口；
#define	CMD_AUTOTEST_ALARMIN				(CMD_AUTOTEST_MIN+12)	  //调试报警输入端口；
#define	CMD_AUTOTEST_ALARMOUT				(CMD_AUTOTEST_MIN+13)	  //调试报警输出端口；
#define	CMD_AUTOTEST_SERIAL					(CMD_AUTOTEST_MIN+14)	  //调试串口；
#define	CMD_AUTOTEST_RTC			   		(CMD_AUTOTEST_MIN+15)	  //调试时钟芯片；
#define	CMD_AUTOTEST_VGADETECTIVE   		(CMD_AUTOTEST_MIN+16)	  //调试VGA信号侦测；设备回
#define	CMD_AUTOTEST_HDMIDETECTIVE			(CMD_AUTOTEST_MIN+17)	  //调试HDMI信号侦测；设备回
#define	CMD_AUTOTEST_RESETDETECTIVE			(CMD_AUTOTEST_MIN+18)	  //调试复位信号侦测；设备回
#define	CMD_AUTOTEST_FORMATDISK				(CMD_AUTOTEST_MIN+19)	  //格式化磁盘；
#define	CMD_AUTOTEST_BACKUPSYSTEM			(CMD_AUTOTEST_MIN+20)	  //备份系统；
#define	CMD_AUTOTEST_ENABLEGUIDE			(CMD_AUTOTEST_MIN+21)	  //启用开机向导；

#define CMD_AUTOTEST_IRIS					(CMD_AUTOTEST_MIN+22)	  //光圈校正；
#define CMD_AUTOTEST_BADPOINTS				(CMD_AUTOTEST_MIN+23)	  //坏点校正；
#define CMD_AUTOTEST_IRCUT					(CMD_AUTOTEST_MIN+24)	  //IRCUT校正；
#define CMD_AUTOTEST_SDCARD					(CMD_AUTOTEST_MIN+25)	  //SD卡校正；
#define CMD_AUTOTEST_VERIFYTIME				(CMD_AUTOTEST_MIN+26)	  //时间校正；
#define CMD_AUTOTEST_CALIBRATEVIDEOBRIGHTNESS	(CMD_AUTOTEST_MIN+27) //亮度差异校正；
#define CMD_AUTOTEST_POWER_SYNC				(CMD_AUTOTEST_MIN+28)	  //电源同步检测
#define	CMD_AUTOTEST_END					(CMD_AUTOTEST_MIN+100)	  //调试结束；
#define	CMD_AUTOTEST_MAX					(CMD_AUTOTEST_MIN+101)

#define MAX_AUTOTEST_ID     CMD_AUTOTEST_MAX

typedef struct
{
	int     iTestParam[5];
	char    cTestParam[65];
}strAutoTest_Para;

#define MAX_HD_TEMPLATE_NUMBER	8

//用户自定义插入数据
#define STREAMDATA_CMD_MIN		                0
#define	STREAMDATA_CMD_USER_DEFINE				STREAMDATA_CMD_MIN + 1
#define STREAMDATA_CMD_MAX						STREAMDATA_CMD_MIN + 1
#define MAX_INSERT_STREAM_LEN					64

#define INSERTDATA_FLAG_MIN						0
#define INSERTDATA_MAIN_STRAM					INSERTDATA_FLAG_MIN + 1
#define INSERTDATA_SUB_STRAM					INSERTDATA_FLAG_MIN + 2
#define INSERTDATA_MAIN_SUB						INSERTDATA_FLAG_MIN + 3
#define INSERTDATA_FLAG_MAX						INSERTDATA_FLAG_MIN + 4
typedef struct __tagTStreamData
{
	int  iSize;				//结构体大小
	char cStreamData[MAX_INSERT_STREAM_LEN];
	int  iStreamLen;
} TStreamData, *PTStreamData;

#define DOME_PTZ_TYPE_MIN  1
#define DOME_PTZ_TYPE_PRESET_FREEZE_UP  		(DOME_PTZ_TYPE_MIN +0)
#define DOME_PTZ_TYPE_AUTO_FLIP 	 			(DOME_PTZ_TYPE_MIN +1)
#define DOME_PTZ_TYPE_PRESET_SPEED_LEVE			(DOME_PTZ_TYPE_MIN +2)
#define DOME_PTZ_TYPE_MANUL_SEPPD_LEVEL			(DOME_PTZ_TYPE_MIN +3)
#define DOME_PTZ_TYPE_WAIT_ACT             		(DOME_PTZ_TYPE_MIN +4)
#define DOME_PTZ_TYPE_INFRARED_MODE 			(DOME_PTZ_TYPE_MIN +5)
#define DOME_PTZ_TYPE_MAX			 			(DOME_PTZ_TYPE_MIN +6)
typedef struct
{
	int iSize;
	int iType;       		//类型
	int iAutoEnable; 		//0--不使能，1--使能
	int iParam1;			//参数
							//1--启用预置位冻结：未使用
							//2--启用自动翻转：未使用
							//3--预置位速度等级：0--低，1--中，2--高
							//4--手控速度等级：0--低，1--中，2--高
							//5--启用待机动作：具体数值：30、60、300、600、1800（单位：秒）
							//6--红外灯模式：0--手动，1--自动
	int iParam2;    		//参数
							//1--启用预置位冻结：未使用
							//2--启用自动翻转：未使用
							//3--预置位速度等级：未使用
							//4--手控速度等级：未使用
							//5--启用待机动作：0--预置位，1--扫描，2--巡航，3--模式路径
							//6--红外灯模式："0--手动时，代表红外灯亮度，具体数值：[0,10]；
								//1--自动时，代表红外灵\敏度，具体数值：0-最低，1-较低，2-标准，
								//3-较高，4-最高；"
	int iParam3;	//预留
	int iParam4;	//预留	
}DOMEPTZ;

/*****************************************************************************/
#define GET_USERDATA_INFO_MIN                            (0)                           
#define GET_USERDATA_INFO_TIME							 (GET_USERDATA_INFO_MIN )		//获得用户数据中的时间信息
#define GET_USERDATA_INFO_OSD							 (GET_USERDATA_INFO_MIN +1)		//获得用户数据中的OSD信息
#define GET_USERDATA_INFO_GPS                            (GET_USERDATA_INFO_MIN +2)		//获得用户数据中的GPS信息
#define GET_USERDATA_INFO_VCA                            (GET_USERDATA_INFO_MIN +3)		//获得用户数据中的VCA信息
#define GET_USERDATA_INFO_USER_DEFINE                    (GET_USERDATA_INFO_MIN +4)		//获得用户数据中的VCA信息
#define GET_USERDATA_INFO_MAX                            (GET_USERDATA_INFO_MIN +4)	
/*****************************************************************************/

//广播消息ID
#define MSG_VEHICLE_GPS_CALIBRATION				0x12001		//GPS校时 iMsgValue(0:禁用,1:启用)
#define MSG_VEHICLE_VOLTAGE						0x12002		//iMsgValue(表示电压值)
#define MSG_VEHICLE_TEMPERATURE					0x12003		//iMsgValue(表示温度值)
#define MSG_VEHICLE_SATELLITE_NUM				0x12004		//iMsgValue(表示卫星个数)
#define MSG_VEHICLE_SIGNAL_INTENSITY			0x12005		//iMsgValue(表示GPS信号强度)
#define MSG_VEHICLE_GPS_MODULE_TYPE				0x12006		//GPS模块类型 iMsgValue(0:无模块,1:GPS,2:北斗)
#define MSG_VEHICLE_ALARM_THRESHOLD				0x12007		//低压报警阈值
#define MSG_VEHICLE_SHUTDOWN_THRESHOLD			0x12008		//低压关机阈值

#define MSG_VALUE_MAX_LEN 64
typedef struct  
{
	int iMsgID;								//消息ID
	int iChannelNo;							//通道号
	int iMsgValue;							//消息附带参数
	char cMsgValue[MSG_VALUE_MAX_LEN];		//消息附带参数
}BROADCAST_MSG,*PBROADCAST_MSG;

//模块能力ID
#define MODULE_CAP_MIN				(0) 
#define MODULE_CAP_VEHICLE	(MODULE_CAP_MIN+0)
#define MODULE_CAP_MAX		(MODULE_CAP_MIN+1)

//车载模块能力
#define MODULE_CAP_VEHICLE_GPS_OVERLAY			0x1
#define MODULE_CAP_VEHICLE_POWER_DELAY			0x2
#define MODULE_CAP_VEHICLE_ALARM_THRESHOLD		0x4
#define MODULE_CAP_VEHICLE_SHUTDOWN_THRESHOLD	0x8

//模拟485键盘控制指令
#define KEYBOARD_CTRL_MIN			0
#define KEYBOARD_CURRENT_SCREEN		KEYBOARD_CTRL_MIN + 0 	//设置UI选中窗口，Value为UI窗口号
#define KEYBOARD_SINGLE_SCREEN 		KEYBOARD_CTRL_MIN + 1 	//单屏显示UI窗口，Value预留
#define KEYBOARD_PRESET_CALL		KEYBOARD_CTRL_MIN + 2 	//从单屏显示恢复，Value未使用
#define KEYBOARD_SCREEN_RRSTORE 	KEYBOARD_CTRL_MIN + 3 	//调用预置位,Value为预置位号
#define KEYBOARD_CTRL_MAX			KEYBOARD_CTRL_MIN + 4

#define TTEMPLATE_CMD_MIN				0
#define TTEMPLATE_CMD_SMART	(TTEMPLATE_CMD_MIN+0)
#define TTEMPLATE_CMD_VIDEO	(TTEMPLATE_CMD_MIN+1)
#define TTEMPLATE_CMD_MAX	(TTEMPLATE_CMD_MIN+2)

#define SMART_TTEMPLATE_MAX_NUM	4
typedef struct  
{
	int iWeek;								//星期日到星期六为～，iWeekday=7，代表假日计划
	int iIndex[SMART_TTEMPLATE_MAX_NUM];		//模板编号1-8，-不启用，-8代表模板-模板
}SMART_TEMPLATE,*PSMART_TEMPLATE;

typedef struct  
{
	int iIndex;			//模板编号
	int iType;			//参数类型
	int iValue;			//参数值
}VIDEO_TEMPLATE,*PVIDEO_TEMPLATE;

//*****VIDEO_TEMPLATE对应的type和value******/
// 1--编码方式	0，H.264；，M-JPEG；，MPEG4
// 2--编码Profile 0:baseline,1:main,2:high
// 3--分辨率	详见分辨率页
// 4--帧率	1～
// 5--压缩模式	0，CBR；，VBR
// 6--码率	单位为KBytes/s，如kbps的码率，此处应置(除以)
// 7--画面质量	4～，越小质量越高
// 8--I帧帧率	0-100
// 9--码流类型	3，音视频符合流；，音频流；，视频流
// 10--音频编码算法	AUDIO_CODEC_FORMAT_G711A   = 1,   /*G.711 A率*/
//					AUDIO_CODEC_FORMAT_G711Mu  = 2,   /*G.711 Mu率*/
//					AUDIO_CODEC_FORMAT_ADPCM   = 3,   /*ADPCM */
//					AUDIO_CODEC_FORMAT_G726    = 4,   /*G.726 */
//					AUDIO_CODEC_FORMAT_AAC_LC  = 22---31,   /*AAC */预留一个区间给AAC用于扩展
//					AUDIO_CODEC_FORMAT_BUTT

//add by 20131022
#define DEVICE_STATE_MIN            0
#define DEVICE_STATE_BRIGHT			(DEVICE_STATE_MIN)    //亮度
#define DEVICE_STATE_ACUTANCE		(DEVICE_STATE_MIN+1)  //锐度
#define DEVICE_STATE_SYSTEM			(DEVICE_STATE_MIN+2)  //系统
#define DEVICE_STATE_MAX			(DEVICE_STATE_MIN+2)  

#define NVS_TIME NVS_FILE_TIME
typedef struct __tagSystemState
{
	int iSize;
	int iCamera;				//摄像机状态
	int iHLimit;				//水平限位
	int iVLimit;				//垂直限位
	int iInterface;				//接口模组
	int iTSensor;				//温度传感器
	int temperature;			//球机温度
	int itemperatureScale;		//温度单位
	NVS_TIME strPublishData;		//发布日期
}TSystemState, *pTSystemState;

#define NET_CLIENT_MIN					0	
#define NET_CLIENT_DOME_MENU			(NET_CLIENT_MIN + 0)	//球机菜单参数
#define NET_CLIENT_DOME_WORK_SCHEDULE	(NET_CLIENT_MIN + 1)	//球机运行模板参数
#define NET_CLIENT_INTERESTED_AREA		(NET_CLIENT_MIN + 2)	//感兴趣区域
#define NET_CLIENT_APPEND_OSD			(NET_CLIENT_MIN + 3)	//附加字符叠加
#define NET_CLIENT_LOGONFAILED_REASON	(NET_CLIENT_MIN + 4)	//登陆失败
#define NET_CLIENT_AUTOREBOOT			(NET_CLIENT_MIN + 5)	//NVR自动重启布防时间
#define NET_CLIENT_IP_FILTER			(NET_CLIENT_MIN + 6)	//IP地址过滤（黑白名单）
#define NET_CLIENT_DATE_FORMATE			(NET_CLIENT_MIN + 7)	//叠加字符日期显示格式
#define NET_CLINET_COLOR2GRAY			(NET_CLIENT_MIN + 8)	//视频彩转灰即时生效
#define NET_CLINET_LANPARAM			    (NET_CLIENT_MIN + 9)	//网卡配置功能
#define NET_CLINET_DAYLIGHT_SAVING_TIME	(NET_CLIENT_MIN + 10)	//设置设备夏令时
#define NET_CLINET_NETOFFLINE			(NET_CLIENT_MIN + 11)	//强制断开用户连接
#define NET_CLINET_HTTPPORT				(NET_CLIENT_MIN + 12)	//HTTP端口
#define NET_CLINET_PICTURE_MERGE		(NET_CLIENT_MIN + 13)	//图像合成
#define NET_CLIENT_SNAP_SHOT_INFO		(NET_CLIENT_MIN + 14)	//前后抓拍参数
#define NET_CLIENT_IO_LINK_INFO			(NET_CLIENT_MIN + 15)	//IO联动设备类型
#define NET_CLIENT_DEV_COMMONNAME		(NET_CLIENT_MIN + 16)	//自定义设备通用接口的别名
#define NET_CLIENT_ITS_DEV_COMMONINFO	(NET_CLIENT_MIN + 17)	//ITS设备通用信息
#define NET_CLIENT_MAX					(NET_CLIENT_MIN + 18)			

#define MAX_DOME_TYPE	25
#define MAX_DOME_PARA_GROUP_NUM		8
typedef struct __tagDomeParam
{
	int iType;
	int iParam1;
	int iParam2;
	int iParam3;
	int iParam4;
}TDomeParam, *pTDomeParam;

#define MAX_SCHEDULE 8
typedef struct __tagDomeWork
{
	int iBeginHour;
	int iBeginMinute;
	int iEndHour;
	int iEndMinute;
	int iWorkType;  //0：无动作1：预置位2：扫描 3：巡航 4：模式
	int iWorkValue; //预置位号取值范围1～8，扫描号取值范围：1～4，巡航号取值范围：1～4，模式路径号取值范围：1～4 
	int iEnable;
}TDomeWork, *pTDomeWork;

//彩转灰
typedef struct __tagColor2GrayParam
{
	int  m_isize;         //结构体大小
	int  m_iColor2Gray;   //彩转灰类型
	int  m_iDayRange;     //白天亮度值
	int  m_iNightRange;   //夜晚亮度值
	int  m_iTimeRange;    //定时范围：白天开始时间，晚上开始时间。
	int  m_iColorDelay;   //彩转黑延时
	int  m_iGrayDelay;    //黑转彩延时
}TColor2GrayParam,*pTColor2GrayParam;

//网卡参数
typedef struct __tagLanParam
{
	int m_iSize;		  //结构体大小
	int m_iNo;			  //网卡编号：lan1：0； lan2:1
	int m_iMode;		  //网卡模式：0：保留；1：半双工；2：保留；3：双工。
	int m_iSpeed;		  //速率
}TLanParam,*pTLanParam;

#define MAX_DEVCOMNAME_NO   3		//通道类型数目
#define DEVCOMNAME_VIDEO    0		//视频
#define DEVCOMNAME_ALARMIN	1       //报警输入
#define DEVCOMNAME_ALARMOUT 2       //报警输出
//自定义设备通用接口的别名
typedef struct __tagDevCommonName
{
	int  m_iSize;				//结构体大小
	int	 m_iChannelType;		//通道类型
	char m_cChanneleName[LEN_64+1];   //通道名称
}TDevCommonName,*pTDevCommonName;

typedef struct __tagDomeWorkSchedule
{	
	int iWeekDay;
	TDomeWork tWork[MAX_SCHEDULE];
}TDomeWorkSchedule, *pTDomeWorkSchedule;

#define  MAX_APPEND_DSD_LAY_BUM	7
#define MAX_OSD_LENGTH 256
typedef struct __tagAppendOSD
{
	int iSize;
	int iLayNo;
	int iColor;
	int iDiaphaneity;
	int iFontSize;
	int iPosX;
	int iPosY;
	char pcText[MAX_OSD_LENGTH];
}TAppendOSD, *pTAppendOSD;

#define MAX_INTERESTED_AREA_NUM	8
typedef struct __tagInterestedArea
{
	int iSize;
	int iIndex;
	int iEnable;
	int iAbsQp;
	int iQp;
	int iLeft;
	int iTop;
	int iRight;
	int iBottom;
}TInterestedArea, *pTInterestedArea;

#define MAX_NVR_AUTOREBOOT_SCHEDULE 9
typedef struct __tagAutoRebootSchedule
{
	int iSize;
	int iWeekDay;			//星期日到星期六为0～6，7-每天，8-从不
	int iHour;
	int iMinute;
}TAutoRebootSchedule, *pTAutoRebootSchedule;

#define MAX_IP_FILTER_NUM	16
typedef struct __tagIpFilter
{
	int iSize;
	char cIp[LENGTH_IPV4];
	char cSubMask[LENGTH_SUB_MASK];
	int iFilterType;								//过滤类型:0,禁用IP权限设定;1,禁止IP访问;2,允许IP访问
	int iIpNum;										//过滤ip数量,最大支持16个不同的IP地址
	char cFilterIp[MAX_IP_FILTER_NUM][LENGTH_IPV4];	//网络地址字符串。如：pcFilterIp[0]=“192.168.1.10”
}TIpFilter, *pTIpFilter;

typedef struct __tagDateFormat
{
	int iSize;
	int iFormatType;	//格式类型:case 0:/*yyyy/mm/dd*/; 1:/*mm/dd/yyyy*/; 2:/*dd/mm/yyyy*/; 3:/*M day yyyy*/; 4:/*day M yyyy*/
	char cSeparate;		//分隔符,可设置为“/”，“-”
	char cReserved[3];	//字节对齐
	int iFlagWeek;		//表示星期是否显示: 0-不显示，1-显示					
	int iTimeMode;		//表示时间制式: 0-24小时制，1-12小时制							
}TDateFormat, *pDateFormat;

//夏令时
typedef struct __tagDaylightSavingTime
{
	int m_iSize;
	int m_iMonth;				//月份
	int m_iWeekOfMonth;			//星期编号(0：末个，1：首个，2：第二个，3：第三个，4：第四个)
	int m_iDayOfWeek;			//星期（星期日到星期六为0～6）
	int m_iHourOfDay;			//小时（0～23）
}TDaylightSavingTime, *pTDaylightSavingTime;

typedef struct __tagDaylightSavingTimeSchedule
{
	int m_iSize;
	int m_iDSTEnable;					//夏令时使能,0-禁用，1-启用
	int m_iOffsetTime;					//偏移时间,0～120（单位：分）
	TDaylightSavingTime m_tBeginDST;	//起始时间
	TDaylightSavingTime m_tEndDST;		//结束时间
}TDaylightSavingTimeSchedule, *pTDaylightSavingTimeSchedule;

//远程强制断开用户连接
typedef struct __tagNetOffLine
{
	int iSize;
	char cIPAddr[LENGTH_IPV4];		//IP地址、域名
	int iOffTime;					//断开时间,秒；最小10秒
}TNetOffLine, *pTNetOffLine;

//HTTP端口
typedef struct __tagHttpPort
{
	int iSize;
	int iPort;			//http端口号
	int iHttpsport;		//https端口号,默认443
}THttpPort, *pTHttpPort;

//登录失败错误码
#define UNKNOW_ERROR			0
#define CIPHER_USERNAME_ERROR	1
#define CIPHER_USERPASS_ERROR	2
#define NO_SUPPORT_ALGORITHM	3
#define LOGON_NET_ERROR			0xFF01
#define LOGON_PORT_ERROR		0xFF02

//高清摄像机参数模板类型
#define CAMERA_PARA_MIN								0
#define CAMERA_PARA_IRIS_ADJUSTMENT 				CAMERA_PARA_MIN + 0		//0--光圈调节
#define CAMERA_PARA_WDR								CAMERA_PARA_MIN + 1		//1--超宽动态
#define CAMERA_PARA_BLC								CAMERA_PARA_MIN + 2		//2--背光补偿
#define CAMERA_PARA_EXPOSURE_TIME					CAMERA_PARA_MIN + 3		//3--曝光时间
#define CAMERA_PARA_SHUTTER_ADJUSTMENT				CAMERA_PARA_MIN + 4		//4--快门调节
#define CAMERA_PARA_GAIN_ADJUSTMENT					CAMERA_PARA_MIN + 5		//5--增益调节
#define CAMERA_PARA_GAMMA_ADJUSTMENT				CAMERA_PARA_MIN + 6		//6--gamma调节
#define CAMERA_PARA_SHARPNESS_ADJUSTMENT			CAMERA_PARA_MIN + 7		//7--锐度调节
#define CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT		CAMERA_PARA_MIN + 8		//8--降噪调节
#define CAMERA_PARA_EXPOSURE_REGION					CAMERA_PARA_MIN + 9		//9--曝光区域
#define CAMERA_PARA_BLC_REGION						CAMERA_PARA_MIN + 10	//10--背光补偿区域
#define CAMERA_PARA_AF_REGION_SET					CAMERA_PARA_MIN + 11	//11--AF区域设置
#define CAMERA_PARA_TARGET_BRIGHTNESS_ADJUSTMENT	CAMERA_PARA_MIN + 12	//12--目标亮度调节
#define CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT		CAMERA_PARA_MIN + 13	//13--白平衡调节
#define CAMERA_PARA_JPEG_IMAGE_QUALITY				CAMERA_PARA_MIN + 14	//14--JPEG图像质量
#define CAMERA_PARA_LUT_ENABLE						CAMERA_PARA_MIN + 15	//15--LUT使能
#define CAMERA_PARA_AUTOMATIC_BRIGHTNESS_ADJUST		CAMERA_PARA_MIN + 16	//16--自动亮度调节使能
#define CAMERA_PARA_HSBLC							CAMERA_PARA_MIN + 17	//17--强光抑制功能
#define CAMERA_PARA_AUTO_EXPOSURE_MODE				CAMERA_PARA_MIN + 18	//18--自动曝光模式
#define CAMERA_PARA_SCENE_MODE						CAMERA_PARA_MIN + 19	//19--场景模式
#define CAMERA_PARA_FOCUS_MODE						CAMERA_PARA_MIN + 20	//20--聚焦模式
#define CAMERA_PARA_MIN_FOCUSING_DISTANCE			CAMERA_PARA_MIN + 21	//21--最小聚焦距离
#define CAMERA_PARA_DAY_AND_NIGHT					CAMERA_PARA_MIN + 22	//22--日夜切换
#define CAMERA_PARA_RESTORE_DEFAULT					CAMERA_PARA_MIN + 23	//23--恢复默认
#define CAMERA_PARA_THROUGH_FOG						CAMERA_PARA_MIN + 24	//24--去雾
#define CAMERA_PARA_MAX								CAMERA_PARA_MIN + 25

//球机菜单参数模板类型
#define DOME_PARA_MIN										0
#define DOME_PARA_PRESET_TITLE_DISPLAY_TIME					DOME_PARA_MIN + 1		//1--预置位标题显示时间
#define DOME_PARA_AUTOMATIC_FUNCTION_TITLE_DISPLAY_TIME		DOME_PARA_MIN + 2		//2--自动功能标题显示时间
#define DOME_PARA_REGION_TITLE_DISPLAY_TIME					DOME_PARA_MIN + 3		//3--区域标题显示时间
#define DOME_PARA_COORDINATE_DIRECTION_DISPLAY_TIME			DOME_PARA_MIN + 4		//4--坐标方向显示时间
#define DOME_PARA_TRACEPOINTS_DISPLAY_TIME					DOME_PARA_MIN + 5		//5--跟踪点标题显示时间
#define DOME_PARA_TITLE_BACKGROUND							DOME_PARA_MIN + 6		//6--标题背景
#define DOME_PARA_AUTOMATIC_STOP_TIME						DOME_PARA_MIN + 7		//7--自动停止时间
#define DOME_PARA_MENU_OFF_TIME								DOME_PARA_MIN + 8		//8--菜单关闭时间
#define DOME_PARA_VERTICAL_ANGLE_ADJUSTMENT					DOME_PARA_MIN + 9		//9--垂直角度调整
#define DOME_PARA_MANIPULATION_SPEED_RATING					DOME_PARA_MIN + 10		//10--操控速度等级
#define DOME_PARA_PRESET_SPEED_RATING						DOME_PARA_MIN + 11		//11--预置位速度等级
#define DOME_PARA_TEMPERATURE_CONTROL_MODE					DOME_PARA_MIN + 12		//12--温度控制模式
#define DOME_PARA_485_ADDRESS_SETTING						DOME_PARA_MIN + 13		//13--485地址设置
#define DOME_PARA_ZERO_SETTING								DOME_PARA_MIN + 14		//14--零点设置
#define DOME_PARA_NORTH_SETTING								DOME_PARA_MIN + 15		//15--指北设置
#define DOME_PARA_CONTROL_MODE								DOME_PARA_MIN + 16		//16--控制方式
#define DOME_PARA_SENSITIVE_THRESHOLD						DOME_PARA_MIN + 17		//17--感光阈值
#define DOME_PARA_DELAY_TIME								DOME_PARA_MIN + 18		//18--延时时间
#define DOME_PARA_ZOOM_MATCH								DOME_PARA_MIN + 19		//19--变倍匹配
#define DOME_PARA_PRESET									DOME_PARA_MIN + 20		//20--预置位
#define DOME_PARA_SCANNING									DOME_PARA_MIN + 21		//21--扫描
#define DOME_PARA_SCHEMA_PATH								DOME_PARA_MIN + 22		//22--模式路径
#define DOME_PARA_SCHEMA_PATH_CURRENT_STATE					DOME_PARA_MIN + 23		//23--模式路径当前状态
#define DOME_PARA_REGIONAL_INDICATIVE						DOME_PARA_MIN + 24		//24--区域指示
#define DOME_PARA_CRUISE									DOME_PARA_MIN + 25		//25-巡航
#define DOME_PARA_MAX										DOME_PARA_MIN + 26

#define COMMAND_ID_MIN					0
#define COMMAND_ID_ITS_FOCUS			COMMAND_ID_MIN + 1		//五点聚焦相机控制协议
#define COMMAND_ID_MAX					COMMAND_ID_MIN + 2

//图像合成方式设置
#define MAX_ITS_MERGE_TYPE	4
typedef struct __tagTITS_MergeInfo
{
	int		m_iSize;
	int		m_iMergeType;		//合成图片张数类型:2-两张合成方式类型,3-三张合成方式类型
	int		m_iMergeMode;		//合成方式:两张合成方式类型：0-垂直合成模式,1-水平合成模式
	//三张合成方式类型:0-品字形,上一下二;1-品字形,上二下一;2-左二右一;3-左一右二;
	//4-垂直排列;5-水平排列;6-田字形
	int		m_iResizePercent;	//图像缩放比例
}TITS_MergeInfo, *PTITS_MergeInfo;

//前后抓拍参数
#define MAX_LINK_CAMERA_ID		4
typedef struct __tagTITS_SnapShotInfo
{
	int		m_iSize;
	int		m_iRoadNo;				//车道编号
	int		m_iEnable;				//使能
	char	m_cLinkIP[LENGTH_IPV4];	//联动相机IP
	int		m_iLinkRoadNo;			//联动相机车道ID
}TITS_SnapShotInfo, *pTITS_SnapShotInfo;

//IO联动设备类型设置
#define MAX_IO_DEVICE_NUM	10
typedef struct __tagTITS_IOLinkInfo
{
	int   m_iSize;
	int   m_iIONo;			//IO口编号,0-10
	int   m_iLinkDevice;	//设备联动类型,0-闪光灯,1-频闪灯
}TITS_IOLinkInfo, *pTITS_IOLinkInfo;

//时间段闪光灯使能
typedef struct __tagTITS_FlashEnable
{
	int   m_iSize;
	int   m_iIndex;				//时间段编号,0-7，支持最多8个时间段
	int   m_iFlashLampEnable;	//是否启用闪光灯
	int   m_iVideoLinkEnbale;	//视频联动使能,按位bit0:0-不使能，1-使能
}TITS_FlashEnable, *pTITS_FlashEnable;

#define REBUILDINDEX_SUCCESS			0
#define REBUILDINDEX_NO_DISK			1
#define REBUILDINDEX_EXCEPTION			2

#define MAX_ITS_DEV_COMMOMINFO_TYPE		3
typedef struct tagITS_DevCommonInfo
{
	int		iSize;
	int		iType;					//信息类型,0-保留，1-机关代码，2-机关名称
	char	cCommonInfo[LEN_64];	//信息内容,长度不超过63字符
}ITS_DevCommonInfo, *pITS_DevCommonInfo;

typedef struct tagITS_CamLocationEx
{
	int				iSize;
	ITS_CamLocation tITS_CamLocation;	//锐视相机位置设备信息结构体
	int				iDeviceType;		//设备类型,按位，bit0：闯红灯设备,bit1：测速证设备,bit2：监控录像,
										//bit3：数码照相,bit4：卡口监控,bit5：区间测速证设备；
}ITS_CamLocationEx, *pITS_CamLocationEx;

#endif

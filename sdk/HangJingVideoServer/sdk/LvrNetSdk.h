#ifndef __LVR_NET_SDK_H__
#define __LVR_NET_SDK_H__

#ifdef __LVR_NET_EXPORT__
#define LVR_NET_API  extern "C" __declspec(dllexport)
#else
#define LVR_NET_API  extern "C" __declspec(dllimport)
#endif

// protocol mode
#define TCP_PROTOCOL_MODE						0x00000001 // TCP
#define UDP_PROTOCOL_MODE						0x00000002 // UDP
#define MULTICAST_MODE							0x00000004 // multicast
#define RTP_PROTOCOL_MODE						0x00000008 // RTP
#define SELECT_SUB_STREAM						0x80000000 // select sub-stream

// callback data type
#define	LVR_NET_IFRAME							0x1000 // video Iframe
#define	LVR_NET_PFRAME						0x2000 // video Pframe
#define	LVR_NET_BFRAME						0x3000 // video Bframe
#define	LVR_NET_AUDIO							0x4000 // audio frame
#define LVR_NET_VIDEOEND						0xD000 // the end of video frame via network
#define LVR_NET_AUDIOEND						0xE000 // the end of audio frame via network

// wrong code
#define LVR_NET_OUTOF_MEMORY					               0x00000001 // memory configuration fail
#define LVR_NET_INVALID_PARAMETER				               0x00000002 // invalid parameter
#define LVR_NET_SEND_FAIL					               0x00000003 // send fail
#define LVR_NET_TRY_TIMEOUT					               0x00000004 // try timeout
#define LVR_NET_CONNECT_FAIL					               0x00000005 // connect server fail
#define LVR_NET_INVALID_FILE					               0x00000006 //invalid file
#define LVR_NET_LINK_FAIL						0x00000007 // buildup link fail
#define LVR_NET_WINSOCK_INIT					               0x00000008 // Winsock initiation fail
#define LVR_NET_LOGIN_FAIL						0x00000009 // user login fail
#define LVR_NET_TIME_ERROR						0x0000000A // illegal time parameter
#define LVR_NET_LOG_NOMORE						0x0000000B // no more log record
#define LVR_NET_FILE_NOMORE						0x0000000C // no more files
#define LVR_NET_DDNS_ERROR						0x0000000D // DDNS analyze error
#define LVR_NET_INVALID_TIME					               0x0000000E // invalid time
#define LVR_NET_CREATE_FILE_FAIL				               0x0000000F // create file fail
#define LVR_NET_VERSION_NOTMATCH				               0x00000010 // server version not match
#define LVR_NET_PRECREATE_FAIL					               0x00000020 // video precreate fail
#define LVR_NET_SERVER_SUSPEND					               0x00000030 // server suspend
#define LVR_NET_REALPLAY_SUSPEND				               0x00000040 // realplay suspend
#define LVR_NET_INTERNAL_ERROR					               0x00000050 // internal error

// DVR record mode 
#define LVR_NET_AUTO_RECORD						0x1000 // auto record
#define LVR_NET_MANUAL_RECORD					               0x2000 // manual record

// PTZ control protocol mode 
#define PROTOCOL_PELCO_D1						1
#define PROTOCOL_PELCO_D2						2
#define PROTOCOL_PELCO_D3						3
#define PROTOCOL_PELCO_P1						16
#define PROTOCOL_PELCO_P2						17
#define PROTOCOL_PELCO_P3						18

// PTZ control£¨"//"can  be done£©
#define LVR_NET_LIGHT_PWRON						1 /* light power on */
#define LVR_NET_WIPER_PWRON						2 /* wiper power on */
#define LVR_NET_FAN_PWRON						3 /* fan power on */
#define LVR_NET_HEATER_PWRON					               4 /* heater power on */
#define LVR_NET_AUX_PWRON						5 /* auxiliary device power on */
#define LVR_NET_SET_PRESET						7 // set preset
#define LVR_NET_CLR_PRESET						8 // clear preset
#define LVR_NET_CALL_PRESET						9 // call preset
#define LVR_NET_IRIS_SMALL						12 // aperture small
#define LVR_NET_IRIS_BIG						              13 // aperture big
#define LVR_NET_FOCUS_NEAR						14 // focus near
#define LVR_NET_FOCUS_FAR						15 // focus far
#define LVR_NET_ZOOM_WIDE						16 // zoom wide  (Magnification wide)
#define LVR_NET_ZOOM_TELE						17 // zoom norrow(Magnification norrow)
#define LVR_NET_TILT_UP							21 //tilt up 
#define LVR_NET_TILT_DOWN						22 // tilt down
#define LVR_NET_PAN_LEFT						23 // pan left
#define LVR_NET_PAN_RIGHT						24 // pan right
#define LVR_NET_PAN_AUTO					29 /* PTZ automatically scan the left and right sides at SS speed */
#define LVR_NET_FILL_PRE_SEQ					               30 /* fill the preset into the list of SEQ */
#define LVR_NET_SET_SEQ_DWELL					               31 /*set dwell time of SEQ*/
#define LVR_NET_SET_SEQ_SPEED					              32 /*set speed of SEQ*/
#define LVR_NET_CLE_PRE_SEQ						33 /*clear the preset from list of SEQ*/
#define LVR_NET_RUN_SEQ							37 /*run SEQ*/
#define LVR_NET_STOP_SEQ						38 /*stop SEQ*/
#define LVR_NET_PATTERN_START					              34 // start pattern 
#define LVR_NET_PATTERN_STOP					                35 // stop pattern
#define LVR_NET_RUN_PATTERN						36 // run pattern

// parameters
#define LVR_NET_DEVICE_CONFIG					0x1000 // device configuration, LVR_NET_DEVICE_INFO 
#define LVR_NET_TIME_CONFIG					0x1001 // system time £¬LVR_NET_TIME 
#define LVR_NET_NORMAL_CONFIG					0x1002 // normal configuration, LVR_NET_NORMAL_SETTING 
#define LVR_NET_ENCODE_CONFIG					0x1003 // encode configuration, LVR_NET_ENCODE_SETTING 
#define LVR_NET_OVERLAY_CONFIG					0x1004 // encode OSD configuration, LVR_NET_ENCODE_OVERLAY 
#define LVR_NET_GLOBAL_CONFIG					0x1005 // record mode configuration, LVR_NET_RECORD_GLOBAL 
#define LVR_NET_RECORD_CHANNEL_CONFIG			0x1006 // record channel configuration,LVR_NET_RECORD_CHANNEL 
#define LVR_NET_PTZ_CONFIG					0x1007 // PTZ configuration, LVR_NET_PTZ_SETTING 
#define LVR_NET_NETWORK_CONFIG				0x1008 // network configuration, LVR_NET_NETWORK_SETTING 
#define LVR_NET_ALARM_CONFIG					0x1009 // alarm configuration, LVR_NET_ALARM_SETTING 
#define LVR_NET_MOTION_CONFIG					0x100A // motion detection configuration,LVR_NET_MOTION_DETECT 
#define LVR_NET_VIDEOLOSS_CONFIG				0x100B // video loss configuration, LVR_NET_VIDEO_DETECT 
#define LVR_NET_VIDEOOVERLAY_CONFIG				0x100C // video overlay configuration, LVR_NET_VIDEO_DETECT 
#define LVR_NET_CHANNEL_CONFIG					0x100D // channel configuration,LVR_NET_CHANNEL_SETTING 
#define LVR_NET_SUB_ENCODE_CONFIG				0x100E // substream configuration, LVR_NET_ENCODE_SETTING

#define LVR_NET_CONFIG_FIRST					LVR_NET_DEVICE_CONFIG
#define LVR_NET_CONFIG_LAST						LVR_NET_SUB_ENCODE_CONFIG

// LVR_NET_ENCODE_SETTING
#define ENCODE_FORMAT_QCIF						0 // QCIF encode format
#define ENCODE_FORMAT_CIF						1 // CIF encode format
#define ENCODE_FORMAT_HD1						3 // HALF D1 encode format
#define ENCODE_FORMAT_D1I						6 // interlace D1  encode format
#define ENCODE_FORMAT_D1P						7 // non interlaceD1  encode format

// LVR_NET_RECORD_CHANNEL
#define LVR_NET_NORMAL_MASK						0x0001 // normal record
#define LVR_NET_MOVEDETECTION_MASK				              0x0002 // move detection record
#define LVR_NET_ALARM_MASK						0x0004 // alarm record

#define LVR_NET_ALARMOUT_MASK					0x0001 // alarm output
#define LVR_NET_SCREENTIP_MASK					0x0002 // screen tip

#define LVR_NET_ALL_FILE						0xFF //all file 
#define LVR_NET_NORMAL_FILE						0x00 // normal record
#define LVR_NET_ALARM_FILE						0x01 // alarm record
#define LVR_NET_MOTION_FILE						0x02 // detect motion

#define LVR_NET_CLOSED_STATUS					0 // close record status
#define LVR_NET_NORMAL_STATUS					1 // normal record status
#define LVR_NET_ALARM_STATUS					2 // alarm record status
#define LVR_NET_MOTION_STATUS					3 // detect motion status

#define LVR_NET_ALL_LOG							0x00FF // all log
#define LVR_NET_SYSTEM_LOG						0x0001 // system operation
#define LVR_NET_SETTING_LOG						0x0002 // parameter setup
#define LVR_NET_DATA_LOG						0x0004 // data management
#define LVR_NET_ALARM_LOG						0x0008 // alarm events
#define LVR_NET_RECORD_LOG						0x0010 // record operation
#define LVR_NET_USER_LOG						0x0020 // user management 
#define LVR_NET_CLEAR_LOG						0x0040 // record clearance
#define LVR_NET_FILE_LOG						0x0080 // file operation

// LVR_NET_SYSTEM_LOG
#define LOG_OPEN_ALARMIN						0x2000 // open alarm
#define LOG_CLOSE_ALARMIN						0x2001 // close alarm
#define LOG_OPEN_ALARMOUT						0x2002 // open alarm output
#define LOG_CLOSE_ALARMOUT						0x2003 // close alarm output
#define LOG_DEVICE_REBOOT						0x2004 // reboot device
#define LOG_DEVICE_POWEROFF						0x2005 // poweroff device
#define LOG_SYSTEM_UPGRADE						0x2006 // upgrade system
#define LOG_DEVICE_ILLEGAL_POWEROFF				               0x2007 // device illegal poweroff
#define LOG_DEVICE_POWERON						0x2008 // device poweron
#define LOG_CHANNELNAME_SETTING					0x2009 // channel name setting

// LVR_NET_SETTING_LOG
#define LOG_SET_TIME							0x2010 // set time
#define LOG_NORMAL_SETTING						0x2011 // normal setting
#define LOG_ENCODE_SETTING						0x2012 // encode setting
#define LOG_RECORD_SETTING						0x2013 // record setting
#define LOG_PTZ_SETTING							0x2014 // PTZ setting
#define LOG_NET_SETTING							0x2015 // net setting
#define LOG_ALARM_SETTING						0x2016 // alarm setting
#define LOG_VIDEODETECT_SETTING					0x2017 // video detect setting 
#define LOG_DISPLAY_SETTING						0x2018 // local display setting

// LVR_NET_DATA_LOG
#define LOG_DISK_FORMAT						0x2020 // format disk
#define LOG_DISK_READWRITE						0x2021 // set readwrite disk
#define LOG_DISK_READONLY						0x2022 // set readonly disk

// LVR_NET_ALARM_LOG
#define LOG_ALARM_START						0x2030 // start alarm
#define LOG_ALARM_STOP							0x2031 // stop alarm
#define LOG_DISK_NOSPACE						0x2032 //  no space in disk
#define LOG_RECORD_NODISK						0x2033 // no disk
#define LOG_ALARM_VIDEOLOSS						0x2034 // video loss alarm
#define LOG_ALARM_NO_VALID_DISK					0x2035 // invalid disk
#define LOG_ALARM_ERR_SECTOR					              0x2036 // error sector of disk
#define LOG_ALARM_SYSTEM_ERROR					0x2037 // wrong code

// LVR_NET_RECORD_LOG
#define LOG_START_RECORD						0x2040 // manual start record
#define LOG_STOP_RECORD						0x2041 // manual stop record

// LVR_NET_USER_LOG
#define LOG_USER_ADD							0x2050 // add user
#define LOG_USER_DEL							0x2051 // delete user
#define LOG_USER_PASSWORD						0x2052 // revise user
#define LOG_USER_LOGIN							0x2053 // user login
#define LOG_USER_LOGOUT						0x2054 // user logout
#define LOG_USER_PARAMETER						0x2055 // user parameter

// LvrNetSetWindowMsg  message type
#define MSG_EXP_REALPLAY_FAILED					0x1001 // abnormal live display initiation
#define MSG_EXP_RECORD_CREATE					0x1101 // abnormal record create
#define MSG_EXP_RECORD_CONFIG					               0x1102 // abnormal record configuration
#define MSG_EXP_RECORD_STOP						0x1104 // stream format change,stop record

#define MSG_EXP_SERVER_CONNECT					0x1501 // abnormal connection with server
#define MSG_EXP_REALPLAY_CONNECT				               0x1502 // abnormal connection with channels
#define MSG_EXP_DATA_RECV						0x1503 // abnormal reception of data
#define MSG_EXP_CMD_RECV						0x1504 // abnormal reception of order
#define MSG_EXP_PLAYBACK_RECV					               0x1505 // abnormal reception of playback
#define MSG_EXP_DOWNLOAD_RECV					0x1506 // abnormal reception of download
#define MSG_EXP_UPGRADE_RECV					               0x1507 // abnormal reception of upgrade progress
#define MSG_EXP_UPGRADE_SEND					               0x1508 // abnormal sending of upgrade

#define MSG_RES_SERVER_CONNECT					0x1601 // resume connection with server
#define MSG_RES_REALPLAY_CONNECT				               0x1602 // resume connection with channels

#define MSG_SERVER_STATUS_CHANGE				               0x1701 // change server status

// LvrNetSetCallback callback order type
#define PHYSICAL_INPUT_ALARM					               0x0001 // alarm input
#define VIDEO_LOSS_ALARM						0x0002 // video loss
#define MOTION_DETECT_ALARM						0x0004 // detect motion
#define VIDEO_COVER_ALARM						0x0008 // video cover

// Play control command
#define LVR_NET_PLAY_START						0x4001 // start to play
#define LVR_NET_PLAY_STOP						0x4002 // stop playing
#define LVR_NET_PLAY_PAUSE						0x4003 // pause playing
#define LVR_NET_PLAY_SET_RATE					               0x4004 // set the speed of playing
#define LVR_NET_PLAY_GET_RATE					               0x4005 // to get the speed of play
#define LVR_NET_PLAY_FRAME						0x4006 // play alone frame
#define LVR_NET_SET_POS							0x4007 // set playback progress
#define LVR_NET_GET_POS							0x4008 // obtain playback progress
#define LVR_NET_GET_FRAMES						0x4009 // obtain having played frames
#define LVR_NET_TOTAL_FRAMES					               0x400A // obtain total frames
#define LVR_NET_GET_TIME						0x400B // obtain having played time
#define LVR_NET_TOTAL_TIME						0x400C // obtain total time

// pDataCallBack: callback live data and remote files playback data
// pBuffer point to the standard stream data, dwDataLen:data length£¬do not loose this pointer
// to callback remote playback data , LVR_NET_AUDIOEND and LVR_NET_VIDEOEND stands for the last frame.
// if all the remote playback data is over£¬pBuffer is NULL
// dwTimeStamp is the time stamp£¬the beginning is arbitrary£¬1000HZ/s
// when these data is video, you can use VIDEO_SYSTEM_MASK or ENCODE_FORMAT_MASK for dwDataFlags to get more information
// PALformat video resolution: CIF:352*288 HALF D1:704*288 D1:720*576
// NTSC format video resolution: CIF:352*240 HALF D1:704*240 D1:720*480
#define VIDEO_SYSTEM_MASK		0x0040 // video format 0:PAL 0x40:NTSC
#define ENCODE_FORMAT_MASK		0x0f00 // encode format 0x0100:CIF 0x0300:HALF D1 0x0600:D1I(interlaceD1) 0x0700:D1P(non-interlaceD1)

typedef void (CALLBACK *pMessageCallBack)(LONG lvrNetHandle, LONG lCommand, CHAR *pBuf, DWORD dwBufLen);
typedef void (CALLBACK *pLvrNetPlayDraw)(LONG lvrHandle, HDC hDC, DWORD dwUser);
typedef void (CALLBACK *pDataCallBack)(LONG lvrHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwDataLen, DWORD dwTimeStamp, DWORD dwDataFlags, DWORD dwUser);

typedef struct  {
	BYTE byChannelsNum;			// channels number
	BYTE byAlarmInputNum;		              // alarm input number
	BYTE byAlarmOutputNum;		              // alarm output number
	BYTE byAudioNum;			              // audio number
	BYTE byHarddiskNum;			// HDD number
	BYTE byUsbNum;				// USB port number
	WORD woSoftwareVersion;		               // LVR version number
	WORD woMcuVersion;			// MCU version number
	WORD woHardwareVersion;		               // hardware version information
	BYTE byReleaseDate[8];		// release date YYYYMMDD(ASCII)
	WORD woEncodeAbility;		// encode mode supported gy the host(use 1<<ENCODE_FORMAT_QCIF,1<<ENCODE_FORMAT_D1P...test byte,0 ineffective)
	WORD woAudioAbility;		// audio channel supported by the host(each byte stands for one channel,0 is ineffective)
	BYTE byCifEncFrames[2];		// CIF encode frame rate(0 stands for PAL,1 stands for NTSC,thereinafter inclusive)
	BYTE byHd1EncFrames[2];		// HD1encode frame rate
	BYTE byD1EncFrames[2];		// D1encode frame rate
	WORD woMachineFlags;		// other sign(0 ineffective)
}LVR_NET_DEVICE_INFO, *LPLVR_NET_DEVICE_INFO;

typedef struct {
	DWORD dwAlarmInput;		// each byte stands for the alarm input of the corresponding channel
	DWORD dwVideoLoss;		// each byte stands for the video loss of the corresponding channel
	DWORD dwMotionDetect;		// each byte stands for the motion detection of the corresponding channel
	DWORD dwVideoCover;		// each byte stands for the video cover of the corresponding channel
	DWORD dwReserve[16];		// reserve
}LVR_NET_ALARM_INFO, *LPLVR_NET_ALARM_INFO;

typedef struct  {
	WORD woYear;				// year
	BYTE byMonth;				// month
	BYTE byDay;				// day
	BYTE byHour;				// hour
	BYTE byMinute;				// minute
	BYTE bySecond;				// second
	BYTE byWeek;				// week£¬often overlooked when transfered as parameter
}LVR_NET_TIME, *LPLVR_NET_TIME;

typedef struct  {
	BYTE byBeginHour;			               //  begining hour
	BYTE byBeginMinute;			// begining minute
	BYTE byBeginSecond;			// begining second
	BYTE byEndHour;				// end hour
	BYTE byEndMinute;			// end minute
	BYTE byEndSecond;			// end second
	WORD woTaskFlags;			// task flags£¨LVR_NET_ALARMOUT_MASK¡¢LVR_NET_SCREENTIP_MASK£©
}LVR_NET_TASK_SCHEDULE, *LPLVR_NET_TASK_SCHEDULE;

typedef struct  {	
	BYTE byDateFormat;			// date format 0 - YMD; 1 - MDY; 2 - DMY
	BYTE byDateSperate;			// date sperate £¨please do not change it£©
	BYTE byTimeFormat;			// time format  0 - 24 mode; 1 - 12 mode
	BYTE byOsdLanguage;			// OSD language£¨please do not change it£©
	BYTE byDeviceNum;			// device number£¨remote control operation device address£©
	BYTE byVideoFormat;			// video format 0 - PAL; 1 - NTSC
	WORD woReserve;				// reserve
}LVR_NET_NORMAL_SETTING, *LPLVR_NET_NORMAL_SETTING;

typedef struct  {
	BYTE byStreamType;			// stream type 0 - video ; 1 - audio and video;
	BYTE byFormatType;			//  ENCODE_FORMAT_xxx
	BYTE byFramesRate;			// frame rate
	BYTE byQuality;				// encode quality  0~5£¬0 - best £»5 - worst
	BYTE byGop;					// Pframe interval£¬stable
	BYTE byEncodeType;			// encode type 0 - VBR; 1 - CBR;
	BYTE byMaxBitRate;			// bitrate 0 - 64kbps; 1 - 128kbps; 2 - 256kbps; 3 - 384kbps; 4 - 512kbps; 5 - 768kbps; 6 - 1Mbps
	BYTE byReserve;				// reserve
}LVR_NET_ENCODE_SETTING, *LPLVR_NET_ENCODE_SETTING;

typedef struct  {
	LONG lTimePosX;		                  // horizontal position of the OSD record time£¨take D1 resolution for example,hereinafter inclusive£©
	LONG lTimePosY;				  // vertical position of the OSD record time
	LONG lTitlePosX;			                // horizontal position of the OSD record title
	LONG lTitlePosY;			               // vertical position of the OSD record title
	LONG lCoverPosX;			               // horizontal position of the cover area
	LONG lCoverPosY;			               //  vertical position of the cover area
	LONG lCoverWidth;			               // cover width
	LONG lCoverHeight;			// cover height
	BOOL bOverlayTime;			// OSD overlay record time  
	BOOL bOverlayTitle;			// OSD overlay record title
	BOOL bAreaCover;			              // area cover
}LVR_NET_ENCODE_OVERLAY, *LPLVR_NET_ENCODE_OVERLAY;

typedef struct  {
	WORD woRecordCover;			// record cover mode 0 - circulation cover£»1 - stop recording while no space in disk
	WORD woRecordTime;			// record time£¨unit£ºminute£¬max:120 minutes£©
}LVR_NET_RECORD_GLOBAL, *LPLVR_NET_RECORD_GLOBAL;

typedef struct  {
	BOOL bAlarmPrerecord;		          // alarm prerecord
	LVR_NET_TASK_SCHEDULE lvrRecordSchedule[7][4];	// record schedule
}LVR_NET_RECORD_CHANNEL, *LPLVR_NET_RECORD_CHANNEL;

typedef struct  {
	WORD woBitRate;				// bitrate
	BYTE byDataBit;				// data bit
	BYTE byStartBit;			             // start bit
	BYTE byStopBit;				// stop bit 
	BYTE byParity;				// Parity
	BYTE byFlowControl;			// flow control
	BYTE byReserve;
}LVR_NET_SERIAL_SETTING, *LPLVR_NET_SERIAL_SETTING;

typedef struct  {
	LVR_NET_SERIAL_SETTING lvrSerial;	              // communication parameter
	BYTE byDecoderType;			// decoder type
	BYTE byDecoderAddress;		             // decorder address
	WORD woReserve;				// reserve
}LVR_NET_PTZ_SETTING, *LPLVR_NET_PTZ_SETTING;

typedef struct  {
	BOOL bEnableUPnP;			// UPnP enable
	BOOL bEnableDHCP;			// DHCP enable 
	CHAR sEthernetIP[16];		// IP address
	CHAR sEthernetIPMask[16];	                // ethernet IP mask
	CHAR sGatewayIP[16];		// gateway IP
	CHAR sDNSIP[16];			// DNS IP
	WORD woServerPort;		// server port
	WORD woHttpPort;			// HTTP port
	BOOL bEnableMulticast;		// multi cast enable£¨ineffective right now£©
	CHAR sMulticastIP[16];		// multi cast IP   £¨ ineffective right now£©
	WORD woMulticastPort;		// multi cast port£¨ineffective right now£©
	WORD woMobilePort;			//mobile port
	BOOL bEnablePPPoE;			// PPPoE enable
	CHAR sPPPoEUser[32];		// PPPoE  user
	CHAR sPPPoEPassword[32];	// PPPoE password
	CHAR sPPPoEIP[16];			// PPPoE IP address£¨only read£©
	LONG lDDNSType;				// DDNS type£¨ please do not change it £©
	CHAR sDomainName[64];		// DDNS name£¨ please do not change it £©
	CHAR sDDNSUser[32];		// DDNS user £¨ please do not change it £©
	CHAR sDDNSPassword[32];		// DDNS password£¨please do not change it £©
	BYTE byMacAdderss[6];		// network card MAC address£¨only read£©
}LVR_NET_NETWORK_SETTING, *LPLVR_NET_NETWORK_SETTING;

typedef struct  {
	BYTE byAlarmType;			// alarm type£¬0 - open; 1 - close
	BYTE byDelayTime;			// alarm delay time£¨s£©
	BOOL bDisplayLoop;			// display loop
	DWORD dwRecordChannel;		           // linkage record channel£¨each bite stands for corresponding video channel£©
	DWORD dwAlarmOut;			// alarm output channel £¨each bite stands for corresponding video channel£©
	LVR_NET_TASK_SCHEDULE lvrAlarmSchedule[7][2];	// alarm schedule
}LVR_NET_ALARM_SETTING, *LPLVR_NET_ALARM_SETTING;

typedef struct 
{
	CHAR sChannelName[16];		// channel name
}LVR_NET_CHANNEL_SETTING;

typedef struct  {
	BYTE byDelayTime;			// delay time£¨s£©
	BOOL bDisplayLoop;			// display loop
	DWORD dwRecordChannel;		              // linkage record channel£¨each bite stands for corresponding video channel£©
	DWORD dwAlarmOut;			// alarm output channel £¨each bite stands for corresponding video channel£©
	LVR_NET_TASK_SCHEDULE lvrDetectSchedule[7][2];	// motion detection schedule
}LVR_NET_VIDEO_DETECT, *LPLVR_NET_VIDEO_DETECT;

typedef struct  {
	BYTE byDelayTime;			// alarm delay time£¨s£©
	BOOL bDisplayLoop;			// display loop
	DWORD dwRecordChannel;		              // linkage record channel£¨each bite stands for corresponding video channel£©
	DWORD dwAlarmOut;			// alarm output channel £¨each bite stands for corresponding video channel£©
	DWORD dwSensitive;			// sensitivity 0~4£¬0 - most sensitive 4 -  least sensitive
	WORD woHorzNum;			// horizontal block number£¬32 bites each line, the former woHorzNum bites are effective
	WORD woVertNum;			// vertical block number
	BYTE byDetectArea[32][16];	// detect area£¬woHorzNum¡ÁwoVertNum
	LVR_NET_TASK_SCHEDULE lvrMotionSchedule[7][2];	// motion detection schedule
}LVR_NET_MOTION_DETECT, *LPLVR_NET_MOTION_DETECT;

typedef struct  {
	CHAR sUserName[8];			// user name£¬max 8 bite£¬end with 0 when less than 8 bite
	CHAR sPassword[8];			//password£¬max 8 bite£¬end with 0 when less than 8 bite
	BOOL bLgoinMore;			// whether allow more login or not
	BYTE byPreviewRight[32];	// channel preview right
	BYTE bySettingRight[32];	// parameter setting right
	BYTE byControlRight[32];	// control right 
}LVR_NET_USER_ACCOUNT, *LPLVR_NET_USER_ACCOUNT;

typedef struct  {
	DWORD dwUserNum;
	LVR_NET_USER_ACCOUNT lvrUser[12];
}LVR_NET_USER_SETTING, *LPLVR_NET_USER_SETTING;

typedef struct  {
	BYTE byDiskType;			// disk type
	BYTE byDiskValid;			// valid disk
	BYTE byDiskState;			// disk state
	BYTE byDiskSlot;			// disk slot
	DWORD dwCapacity;			// capacity
	DWORD dwFreeSpace;			// free space 
}LVR_NET_HARDDISK_INFOMATION;
/*
typedef struct  {
	DWORD dwDiskNum;
	LVR_NET_HARDDISK_INFOMATION lvrDisk[8];
};
*/
typedef struct  {
	LONG lChannel;				// display channel
	DWORD dwLinkMode;			// transmission protocol£¬start SELECT_SUB_STREAM to open sub-stream
	HWND hPlayWnd;				// window display handle £¬NULL means no sign
}LVR_NET_PREVIEW, *LPLVR_NET_PREVIEW;

typedef struct  {
	float fAlpha;				// brightness 0.0 ~ 1.0
	COLORREF crMask;			// bright color
	DWORD dwUser;				// user-defined context
	pLvrNetPlayDraw pPlayDraw;	// parameter pointer
}LVR_NET_MIXER, *LPLVR_NET_MIXER;

typedef struct  {
	WORD woType;				// log type
	WORD woOperate;				// operate type
	LVR_NET_TIME logTime;		              // log time
	CHAR logString[32];			// log information
}LVR_NET_LOG, *LPLVR_NET_LOG;

typedef struct {
	CHAR sFileName[32];			// file name
	DWORD dwFileSize;			// file size
	LVR_NET_TIME startTime;		// start time
	LVR_NET_TIME stopTime;		// stop time
}LVR_NET_FILE, *LPLVR_NET_FILE;

typedef struct  {
	BYTE Output[4];				// alarm output 0:effective  1:ineffective
}LVR_NET_ALARMOUTSTATUS, *LPLVR_NET_ALARMOUTSTATUS;

LVR_NET_API BOOL __stdcall LvrNetStartup();
LVR_NET_API void __stdcall LvrNetCleanup();

LVR_NET_API BOOL __stdcall LvrNetCheckEnv();
LVR_NET_API DWORD __stdcall LvrNetGetLastError();

LVR_NET_API BOOL __stdcall LvrNetConnectTimes(DWORD dwWaitTime, DWORD dwTryTimes);
LVR_NET_API BOOL __stdcall LvrNetSetWindowMsg(HWND hWnd, UINT nMsg);
LVR_NET_API BOOL __stdcall LvrNetSetCallback(pMessageCallBack pUserCallback);

LVR_NET_API BOOL __stdcall LvrNetGetIPByDDNS(CHAR *sDDNS, WORD woDDNSPort, CHAR *sDomainName, WORD woDomainNameLen, CHAR *sGetIP);
LVR_NET_API LONG __stdcall LvrNetLogin(CHAR *sServerIP, WORD woServerPort, CHAR *sUserName, CHAR *sUserPassword, LPLVR_NET_DEVICE_INFO pDeviceInfo);
LVR_NET_API BOOL __stdcall LvrNetLogout(LONG lvrNetHandle);

LVR_NET_API BOOL __stdcall LvrNetSetConfig(LONG lvrNetHandle, DWORD dwCommand, LONG lChannel, LPVOID pSetBuffer, DWORD dwBufferSize);
LVR_NET_API BOOL __stdcall LvrNetGetConfig(LONG lvrNetHandle, DWORD dwCommand, LONG lChannel, LPVOID pGetBuffer, DWORD dwBufferSize, LPDWORD pBytesReturned);
LVR_NET_API BOOL __stdcall LvrNetRestoreConfig(LONG lvrNetHandle, DWORD dwCommand);

LVR_NET_API BOOL __stdcall LvrNetGenKeyFrame(LONG lvrNetHandle, LONG lChannel);

LVR_NET_API LONG __stdcall LvrNetRealPlay(LONG lvrNetHandle, LPLVR_NET_PREVIEW lvrPreview);
LVR_NET_API BOOL __stdcall LvrNetRealDataCallBack(LONG lvrRealHandle, pDataCallBack pUserCallback, DWORD dwUser);
LVR_NET_API BOOL __stdcall LvrNetStopRealPlay(LONG lvrRealHandle);

LVR_NET_API BOOL __stdcall LvrNetSetPlayBuffer(LONG lvrRealHandle, DWORD dwBufferNum);

LVR_NET_API BOOL __stdcall LvrNetOpenSound(LONG lvrHandle);
LVR_NET_API BOOL __stdcall LvrNetCloseSound(LONG lvrHandle);

LVR_NET_API LONG __stdcall LvrNetStartVoiceCom(LONG lvrNetHandle);
LVR_NET_API BOOL __stdcall LvrNetStopVoiceCom(LONG lVoiceComHandle);
LVR_NET_API BOOL __stdcall LvrNetSetVoiceComClientVolume(LONG lVoiceComHandle, LONG lVolume);

LVR_NET_API BOOL __stdcall LvrNetSetVolume(LONG lvrHandle, LONG lBalance, LONG lVolume);
LVR_NET_API BOOL __stdcall LvrNetGetVolume(LONG lvrHandle, LONG *pBalance, LONG *pVolume);

LVR_NET_API	BOOL __stdcall LvrNetPlayMixer(LONG lvrHandle, LPLVR_NET_MIXER lvrMixer);
LVR_NET_API	BOOL __stdcall LvrNetCaptureImage(LONG lvrHandle, CHAR *pImageFile);

LVR_NET_API BOOL __stdcall LvrNetStartSave(LONG lvrRealHandle, CHAR *pFileName);
LVR_NET_API BOOL __stdcall LvrNetStopSave(LONG lvrRealHandle);

LVR_NET_API BOOL __stdcall LvrNetFormatDisk(LONG lvrNetHandle, LONG lFormatDisk);

LVR_NET_API BOOL __stdcall LvrNetSetVideoEffect(LONG lvrRealHandle, DWORD dwBright, DWORD dwContrast, DWORD dwSaturation, DWORD dwHue);
LVR_NET_API BOOL __stdcall LvrNetGetVideoEffect(LONG lvrRealHandle, DWORD *pBright, DWORD *pContrast, DWORD *pSaturation, DWORD *pHue);

LVR_NET_API BOOL __stdcall LvrNetStartRecord(LONG lvrNetHandle, LONG lChannel, LONG lRecordType);
LVR_NET_API BOOL __stdcall LvrNetStopRecord(LONG lvrNetHandle, LONG lChannel);

LVR_NET_API BOOL __stdcall LvrNetRealPTZControl(LONG lvrRealHandle, DWORD dwCommand, BOOL bStop);
LVR_NET_API BOOL __stdcall LvrNetRealPTZControlWithSpeed(LONG lvrRealHandle, DWORD dwCommand, BOOL bStop, DWORD dwSpeed);
LVR_NET_API BOOL __stdcall LvrNetRealPTZPreset(LONG lvrRealHandle, DWORD dwCommand, DWORD dwPresetNumber);
LVR_NET_API BOOL __stdcall LvrNetRealPTZTrack(LONG lvrRealHandle, DWORD dwCommand);

LVR_NET_API BOOL __stdcall LvrNetPTZControl(LONG lvrNetHandle, LONG lChannel, DWORD dwCommand, BOOL bStop);
LVR_NET_API BOOL __stdcall LvrNetPTZControlWithSpeed(LONG lvrNetHandle, LONG lChannel, DWORD dwCommand, BOOL bStop, DWORD dwSpeed);
LVR_NET_API BOOL __stdcall LvrNetPTZPreset(LONG lvrNetHandle, LONG lChannel, DWORD dwCommand, DWORD dwPresetNumber);
LVR_NET_API BOOL __stdcall LvrNetPTZTrack(LONG lvrNetHandle, LONG lChannel, DWORD dwCommand);

LVR_NET_API BOOL __stdcall LvrNetSetAlarmOut(LONG lvrNetHandle, LONG lAlarmOut, LONG lAlarmOutState);
LVR_NET_API BOOL __stdcall LvrNetGetAlarmOut(LONG lvrNetHandle, LPLVR_NET_ALARMOUTSTATUS pAlarmoutState);

LVR_NET_API LONG __stdcall LvrNetFindFile(LONG lvrNetHandle, LONG lChannel, DWORD dwFileType, BOOL bPlayback, LPLVR_NET_TIME pStart, LPLVR_NET_TIME pStop);
LVR_NET_API BOOL __stdcall LvrNetFindNextFile(LONG lvrFileHandle, LPLVR_NET_FILE pLvrFile);
LVR_NET_API BOOL __stdcall LvrNetFindFileClose(LONG lvrFileHandle);

LVR_NET_API LONG __stdcall LvrNetPlayByFile(LONG lvrNetHandle, CHAR *pFile, HWND hPlayWnd);
LVR_NET_API BOOL __stdcall LvrNetPlayControl(LONG lvrPlayHandle, DWORD dwCommand, LPARAM lParam);
LVR_NET_API BOOL __stdcall LvrNetPlayDataCallBack(LONG lvrPlayHandle, pDataCallBack pUserCallback, DWORD dwUser);
LVR_NET_API BOOL __stdcall LvrNetPlayClose(LONG lvrPlayHandle);

LVR_NET_API LONG __stdcall LvrNetStreamDataPlay(HWND hPlayWnd, DWORD dwReserve);
LVR_NET_API BOOL __stdcall LvrNetStreamDataInput(LONG lvrStreamHandle, BYTE *pBuffer, DWORD dwDataLen, DWORD dwTimeStamp, DWORD dwDataFlags);
LVR_NET_API BOOL __stdcall LvrNetStreamPlayClose(LONG lvrStreamHandle);

LVR_NET_API LONG __stdcall LvrNetGetFileByName(LONG lvrNetHandle, CHAR *pGetFile, CHAR *pSaveFile);
LVR_NET_API BOOL __stdcall LvrNetStopGetFile(LONG lvrGetHandle);
LVR_NET_API LONG __stdcall LvrNetGetFilePos(LONG lvrGetHandle);

LVR_NET_API LONG __stdcall LvrNetFindLog(LONG lvrNetHandle, DWORD dwLogType, LPLVR_NET_TIME pStart, LPLVR_NET_TIME pStop);
LVR_NET_API BOOL __stdcall LvrNetFindNextLog(LONG lvrLogHandle, LPLVR_NET_LOG pLvrLog);
LVR_NET_API BOOL __stdcall LvrNetFindLogClose(LONG lvrLogHandle);

LVR_NET_API LONG __stdcall LvrNetUpgrade(LONG lvrNetHandle, CHAR *pFileName);
LVR_NET_API LONG __stdcall LvrNetGetUpgradeState(LONG lvrUpgradeHandle, LONG *pComplete);
LVR_NET_API BOOL __stdcall LvrNetStopUpgrade(LONG lvrUpgradeHandle);

LVR_NET_API BOOL __stdcall LvrNetRebootDevice(LONG lvrNetHandle);
LVR_NET_API BOOL __stdcall LvrNetShutdownDevice(LONG lvrNetHandle);

LVR_NET_API DWORD __stdcall LvrNetGetSdkVersion();

#endif // #ifndef __LVR_NET_SDK_H__

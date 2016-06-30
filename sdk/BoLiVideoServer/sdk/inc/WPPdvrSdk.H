#ifndef _WP_PDVR_SDK_H_
#define _WP_PDVR_SDK_H_

#define DLL_EXPORT extern "C" _declspec(dllexport)

//error return
#define WP_PDVR_NOERROR						200				//no error
#define WP_PDVR_NOINIT						201				//without initialized
#define WP_PDVR_NETINIT_FIAL				202				//initialize network failed
#define WP_PDVR_INVALID_INDEX				203				//invalid PDVR index 
#define WP_PDVR_INVALID_CAM_INDEX			204				//invalid camera index
#define WP_PDVR_NOT_CONNECT					205				//not connect PDVR
#define WP_PDVR_CONNECT_FAIL				206				//connect PDVR failed
#define WP_PDVR_PARAM_ERROR					210				//invalid param
#define WP_PDVR_MAX_NUM						211				//the connect camera is max for this PDVR
#define WP_PDVR_CON_CAM_FAIL				212				//connect camera failed
#define WP_PDVR_PLAYBACK_CON_FAIL			215				//connect playback failed
#define WP_PDVR_PLAYBACK_NOT_CON			216				//not connect playback
#define WP_PDVR_GET_RECORD_INFO_FAIL		217				//get record information failed
#define WP_PDVR_PLAYBACK_JUMPTO_FAIL		218				//playback jump to failed
#define WP_PDVR_OPEN_RECORD_FILE_FAIL		219				//open record file failed
#define WP_PDVR_START_RECORD_FILE_FAIL		220				//start playback failed
#define WP_PDVR_STOP_RECORD_FILE_FAIL		221				//stop playback failed
#define WP_PDVR_PAUSE_RECORD_FILE_FAIL		222				//pause playback failed
#define WP_PDVR_CONTINUE_RECORD_FILE_FAIL	223				//continue playback failed
#define WP_PDVR_SET_PLAYBACK_RATE_FAIL		224				//set rate of playback failed
#define WP_PDVR_FILEJUMP_FAIL				258
#define WP_PDVR_STOP_VIEW_CAMERA_FAIL		225				//stop view failed
#define WP_PDVR_DISCONNECT_FAIL				226				//disconnect PDVR failed
#define WP_PDVR_SURFACE_HAS_CREATE			227				//the screen has been used
#define WP_PDVR_SURFACE_NOT_CREATE			228				//the surface has not exist
#define WP_PDVR_NOT_CONNECT_CAMERA			229				//not connect camera
#define WP_PDVR_SENT_MESSAGE_FAILED			230				//Send message to PDVR failed
#define WP_PDVR_GET_CAMINFO_FAILED			232				//Get camera info failed
#define WP_PDVR_GET_NETINFO_FAILED			259
#define WP_PDVR_CREATE_FILE_FAILED			235				//Download record file failed
#define WP_PDVR_RECV_FAILED					236				//Recv data from PDVR failed
#define WP_PDVR_HAS_NO_FILE_TO_DOWNLOAD		237				//Has no record to download
#define WP_PDVR_DOWNLOAD_HOUR_INVALID		238				//Download start hour must be same with end hour
#define WP_PDVR_DOWNLOAD_FILEPATH_NULL		239				//The path to storage download file is null
#define WP_PDVR_ALREADY_CONNECTED			240				//The pdvr already connected
#define WP_PDVR_DOWNLOAD_DATE_INVALID		242				//The download date is invalid
#define WP_PDVR_PLAYBACK_TIME_INVALID		243				//The playback time is invalid
#define WP_PDVR_PLAYBACK_DATE_INVALID		244				//The playback date is invalid
#define WP_PDVR_OTHER_DATE_IS_PLAYBACK		245				//Other date is playback
#define WP_PDVR_TALK_FAILED					246
#define WP_PDVR_STOP_LISTEN_FAILED			247
#define WP_PDVR_NOT_FINISHED_DOWNLOAD		248
#define WP_PDVR_CHANNEL_NOCAM				249
#define WP_PDVR_CHANNEL_NOTCONNECT			250
#define WP_PDVR_CHANNEL_NOTPREVIEW			251
#define WP_PDVR_CHANNEL_CAPTURE_FAILED		252
#define WP_PDVR_USER_NOT_AUTHORITY			255
#define WP_PDVR_INITSOCK_FAILED				256
#define WP_PDVR_USER_PASSWORD_ERROR			257
#define WP_PDVR_UPDATE_FAILED				260
#define WP_PDVR_UPDATE_CAMERA_FAILED		261

//////////
#define WP_CAPTURE_NOERROR				600		//没有错误
#define WP_CAPTURE_BUF_NULL				601		//数据缓存为空	
#define WP_CAPTURE_PATH_NULL			602		//文件的路径为空
#define WP_CAPTURE_CREAT_FILE_FAILED	603		//创建文件失败


//the date has record or not
#define THE_DAY_HAS_RECORD						300				//the day has record
#define THE_DAY_NOT_RECORD						301				//the day has nothing record

//DataCallBack type param
#define DATA_TYPE_AUDIO							2				//Audio data
#define	DATA_TYPE_HD_IFRAME						3				//Encode HD data, I Frame
#define	DATA_TYPE_HD_PFRAME						4				//Encode HD data, P Frame
#define DATA_TYPE_CIF_IFRAME					5				//Encode CIF data, I Frame
#define	DATA_TYPE_CIF_PFRAME					6				//Encode CIF data, p Frame
#define DATA_TYPE_HD_IMAGE							7		        //Big Jpg picture
#define DATA_TYPE_CIF_IMAGE							8		        //Big Jpg picture

//the mode for record	
#define RECORD_CONTINUE 						'C'				//continue record
#define RECORD_MOTION 							'M'				//remove motion record
#define RECORD_NO 								'N'				//no record

//数据的格式
#define DATA_FORMAT_YUYV				1		//YUYV格式的数据
#define DATA_FORMAT_RGB24				2		//RGB24格式的数据

typedef enum{
	IPC_CONNECT = 0,											//connect camera，if param1 and param2 all is 264, then the encode is H.264
	IPC_DISCONNECT,												//disconnect camera
	IPC_MOTION,													//move detection
	IPC_ALERT,													//camera alarm input
};

//stream type
typedef enum
{
	STREAM_B = 0,
	AUDIO,
	STREAM_S,
	STREAM_B_JPG,
	STREAM_S_JPG,
	STREAMYUYV,
//	STREAM_JPG = 51,   //capture jpg picture
}MEDIATYPE;

typedef enum
{
	STREAM_B_COMMAND_IMAGE = 1,
	STREAM_S_COMMAND_IMAGE = 2,
}JPEGTYPE;

typedef struct _ETHER_DEVICE
{
	char 			ethName[24];
	unsigned char	mac[6];
	char			reserve[2];
	in_addr 		ipaddr;
	in_addr 		netmask;
	in_addr			gateway;
}ETHER_DEVICE, *PETHER_DEVICE;

//record file information
typedef struct _FILEIMAGE
{
	unsigned char	hour;										//start time
	unsigned char	min;
	unsigned char	sec;
	unsigned char	type;	
	unsigned short	len;	
	unsigned char	camId;
	unsigned char	reserve;									//the device of storage	
}FILEIMAGE, *PFILEIMAGE;

struct FIINFO{
	FILEIMAGE		fi;
	FIINFO			*next;		
};

//PTZ operate
#define MAX_RESETNUM	128
enum{
	PTZ_UP = 0,													//OperatePTZ:Turn up.
	PTZ_DOWN,													//OperatePTZ:Turn down.
	PTZ_LEFT,													//OperatePTZ:Turn left.
	PTZ_RIGHT,													//OperatePTZ:Turn right.
	PTZ_FOCUSFAR,												//OperatePTZ:Focus far.
	PTZ_FOCUSNEAR,												//OperatePTZ:Focus near.
	PTZ_ZOOMWIDE,												//OperatePTZ:Zoom wide.
	PTZ_ZOOMTELE,												//OperatePTZ:Zoom telescope
	PTZ_IRISCLOSE,												//OperatePTZ:Open iris.
	PTZ_IRISOPEN,												//OperatePTZ:Close iris.
	PTZ_SETPRESET = 19,											//SetPTZInfo:Add a preset point.
	PTZ_CLEARPRESET,											//SetPTZInfo:Delete a preset point.
	PTZ_GOTO_PRESET,											//Go go preset
	PTZ_PANSTOP = 23,											//OperatePTZ:Left or right stop.
	PTZ_TILTSTOP,												//OperatePTZ:Up or down stop.
	PTZ_ZOOMSTOP,												//OperatePTZ:Zoom stop.
	PTZ_FOCUSSTOP,												//OperatePTZ:Focus stop.
	PTZ_IRISSTOP,												//OperatePTZ:Iris stop.
	PTZ_AUTOFOCUS = 50,											//OperatePTZ:Auto focus.
	PTZ_MANUALFOCUS,											//OperatePTZ:Manual focus.
	PTZ_PAN_SPEED = 53,											//OperatePTZ:Set the horizontal speed.
	PTZ_TILT_SPEED,												//OperatePTZ:Set the vertical speed.
	PTZ_SETZEROPOS = 57,										//OperatePTZ:Set zero position.
	PTZ_CRUISE_ON = 80,											//SetPTZInfo:Start auto cruise.
	PTZ_CRUISE_OFF = 81,										//OperatePTZ:Stop auto cruise.
};

//for box display
enum DECODEBOXOPT{
	FOUR_S_STREAM = 0,
	FOUR_S_ROTATE,
	ONE_B_STREAM,	
	ONE_B_ROTATE,
};

enum EVENTTYPE{
	NVR_DISCONNECT = 201,
};

#define		MAX_CRUISE			4
#define		PRESETS_PER_PATH	128
#define		MAX_PRESET			PRESETS_PER_PATH*MAX_CRUISE

typedef struct _PRESET{
	unsigned short ID;
	char	name[26];
}PRESET;

typedef struct _CRUISEINDEX{
	WORD	id;
	WORD	interval;
}CRUISEINDEX;

typedef struct _CRUISESET{
	int			number:14;
	int         type:2;
	int         reserve:16;
	CRUISEINDEX	index[PRESETS_PER_PATH];
}CRUISESET;

typedef struct _EXTPTZINFO{
	char			bExtPTZEnable;
	char			reserve3;
	char			bAutoFocus;
	char			bEnable;
	int				presetnum;
	int				reserve4;
	
	int				protocol;     
	int				reserve5;        
	int				baudrate;
	int				reserve6;
	
	char			bCruise;
	char			CruisePath;
	WORD			reserve0;
	int				reserve1;
	int 			panSpeed;
	int 			tiltSpeed;
	PRESET  		PreSet[MAX_PRESET];
	CRUISESET		Cruise[MAX_CRUISE];
}EXTPTZINFO;

#define MAX_SERVER				128
//#define MAX_CAMERA				16
#define MAX_CAMERA				64    //for stream media.

typedef struct _IPC_VIDEO_INFO{
	DWORD			version;
	WORD			stream0_width;
	WORD			stream0_height;
	WORD			stream1_width;
	WORD			stream1_height;
    WORD			streamType; 			//mpeg4 : 0 	  h264 : 264
	WORD			reserve;
}IPC_VIDEO_INFO, *PIPC_VIDEO_INFO;

#define MAX_OSDTEXT_LEN			36
typedef struct _IPC_CONNECT_INFO{	
	char			reserve0;	
	char			reserve1;	
	char			reserve2;
	char			groupId;
	char			ethName[16];
	in_addr			ipaddr;
	char			mac[6];
	char			reserve[2];
	char 			OSDText[MAX_OSDTEXT_LEN];
	int				isView;
	int 			frameRate;
	int 			frameRateNightCtrl;
}IPC_CONNECT_INFO, *PIPC_CONNECT_INFO;

typedef struct _DVR_DEVICEINFO{
	int maxCamNum;
	int connCamNum;
	IPC_VIDEO_INFO camVideoInfo[MAX_CAMERA];
	IPC_CONNECT_INFO camConnectInfo[MAX_CAMERA];
}DVR_DEVICEINFO, *PDVR_DEVICEINFO;

typedef struct _DATETIME{           
// 	WORD			yy;
// 	WORD			mon;
// 	WORD			dd;
// 	WORD			hh;
// 	WORD			min;
// 	WORD			ss;
	unsigned long yy:6;
    unsigned long mon:4;
    unsigned long dd:5;
    unsigned long hh:5;
    unsigned long min:6;
    unsigned long ss:6;
}DATETIME;

#define CALLBACK_DATA_FORMAT_ENCODE 0
#define CALLBACK_DATA_FORMAT_DECODE	1


//for network
DLL_EXPORT int WP_Init();																						//Init network.
DLL_EXPORT int WP_Cleanup();																					//Clear out network.
	
//for connect PDVR
DLL_EXPORT int WP_PDVR_Connect(char *pszAddress,DWORD dwPort,char *pszUserName,char *pszPassWord,LPARAM lparam=NULL);																//Connect PDVR.sServerIp:ip of PDVR.return the index of PDVR
DLL_EXPORT int WP_PDVR_DisConnect(int serverId);																//Disconnect PDVR.serverId:index of PDVR

//for get info
DLL_EXPORT int WP_PDVR_GetDeviceInfo(int serverId, DVR_DEVICEINFO *pDvrDeviceInfo);		//Get the device info from PDVR.
DLL_EXPORT int WP_PDVR_GetPDVRNetInfo(int serverId, ETHER_DEVICE **etherDevive);		//Get the network info about PDVR.ETHER_DEVICE:the struct include adaptor name,ip,mark ip,gateway of PDVR.

//for connect camera
DLL_EXPORT int WP_PDVR_ConnectCamera(int serverId, int cameraId, int streamType);				//Connect camera.serverId:index of PDVR.cameraId:index of camera.streamType:type of stream(0:HD, 2:CIF)
DLL_EXPORT int WP_PDVR_DisConnectCamera(int serverId, int cameraId, int streamType);							//Disconnect camera.serverId:index of PDVR.cameraId:index of camera

//for data callback
typedef bool (CALLBACK *PreviewDataCallBack)(int serverId, int cameraId, int type, BYTE *pData, int len, int param1, int param2, void *pReserved);		//Data callback.index:camera index.type:frame type.pData:callback data.len:size of data.param1:width of video.param2:height of video
DLL_EXPORT int WP_GetPreviewDataCallBack(PreviewDataCallBack fData, int serverId = 0, void *pReserved = NULL, int len = 0);																		//Set data callback
typedef bool (CALLBACK *PlaybackDataCallBack)(int serverId, int cameraId, int type, BYTE *pData, int len, int param1, int param2, void *pReserved);		//Data callback.index:camera index.type:frame type.pData:callback data.len:size of data.param1:width of video.param2:height of video
DLL_EXPORT int WP_GetPlaybackDataCallBack(PlaybackDataCallBack fData, int serverId = 0, void *pReserved = NULL, int len = 0);																		//Set data callback
typedef bool (CALLBACK *EventCallBack)(int serverId, int cameraId, int EventType, void *pReserved);				//Event callback function. index:camera index. type:event type
DLL_EXPORT int WP_SetEventCallBack(EventCallBack fEvent, int serverId = 0, void *pReserved = NULL, int len = 0);										//Set the event callback function
// typedef bool (CALLBACK *AudioDataCallBack)(int serverId, int cameraId, int type, BYTE *pData, int len,void *pReserved);		//Data callback.index:camera index.type:frame type.pData:callback data.len:size of data.param1:width of video.param2:height of video
// DLL_EXPORT int WP_GetAudioDataCallBack(AudioDataCallBack fData, int serverId = 0, void *pReserved = NULL, int len = 0);																		//Set data callback

//for listen
DLL_EXPORT int WP_PDVR_StartListen(int serverId, int cameraId);												//Open the listen device. index:index of camera. one camera at one time.
DLL_EXPORT int WP_PDVR_PlayAudio(unsigned char *ostream);														//Play the audio data.
DLL_EXPORT int WP_PDVR_StopListen(int serverId);																//Close the listen device.
DLL_EXPORT int WP_PDVR_GetVolumn(DWORD &volume);
DLL_EXPORT int WP_PDVR_SetVolumn(WORD volume);

DLL_EXPORT int WP_PDVR_SendAudioData(int serverId, int cameraId,char *pData);
DLL_EXPORT int WP_PDVR_StartTalk(int serverId, int cameraId);
DLL_EXPORT int WP_PDVR_StopTalk(int serverId);

//for playback
DLL_EXPORT int WP_PDVR_PlaybackByTime(int serverId, int cameraId, DATETIME startTime, DATETIME endTime);
DLL_EXPORT int WP_PDVR_CheckHasRecord(int serverId, int year, int month, int day);							//Check the day has recorder or not.serverId:index of PDVR.
DLL_EXPORT int WP_PDVR_GetADayRecordInfo(int serverId, int year, int month, int day, FIINFO **pFiHead);		//Get the recorder information.return from pFiHead
DLL_EXPORT int WP_PDVR_StartPlayBack(int serverId, int cameraId);												//Start playback.serverId:index of PDVR.camera:index of camera
DLL_EXPORT int WP_PDVR_StopPlayBack(int serverId, int cameraId);												//Stop playback.
DLL_EXPORT int WP_PDVR_PausePlayBack(int serverId, int cameraId);												//Pause playback.
DLL_EXPORT int WP_PDVR_ContinuePlayBack(int serverId, int cameraId);											//Continue playback.
DLL_EXPORT int WP_PDVR_SetPlayBackRate(int serverId, int cameraId, int rate);									//Set the rate of playback.rate:range 0 to 5(0:1X, 1:2X, 2:4X, 3:1/2X, 4:1/4X, 5:fast playback)
DLL_EXPORT int WP_PDVR_JumpToPlayBack(int serverId, int cameraId, int hour, int min, int sec);				//Jump to certain time.
DLL_EXPORT int WP_PDVR_DestroyPlayBack(int serverId);															//Close playback.
DLL_EXPORT int WP_PDVR_GetPBCurTime(int serverId, int cameraId, DWORD& year, DWORD& month, DWORD& day, DWORD& hour, DWORD& minute, DWORD& second);
DLL_EXPORT int WP_PDVR_EndTime(int serverId, int cameraId, int year, int mon, int day, int hour, int min, int sec);
DLL_EXPORT int WP_PDVR_JumpToPlay(int serverId, int cameraId, int jumpTime);

//for control
DLL_EXPORT int WP_PDVR_SetRGB(int serverId, int cameraId, unsigned char r, unsigned char b);					//Set color of camera. r and b are range from 120 to 200
DLL_EXPORT int WP_PDVR_SetContrast(int serverId, int cameraId, int contrast);									//Set contrast of video.The range of contrast is -128~127
DLL_EXPORT int WP_PDVR_SetBrightness(int serverId, int cameraId, int bright);									//Set brightness of video.The range of bright is -128~127
DLL_EXPORT int WP_PDVR_SetBalance(int serverId, int cameraId, int value);										//Set white balance of camera.The range of value is 1 to 6,1:Auto,2:Outdoor,3:fluorescence light,4:manual,5:indoor,6:tungsten filament
DLL_EXPORT int WP_PDVR_SetShutterSpeed(int serverId, int cameraId, int value);								//Set the speed of shutter.The value range from 3~8.3:1 times.4:1/2 times.5:1/4 times.6:1/8 times.7:1/16 times.8:1/20 times
DLL_EXPORT int WP_PDVR_ForceReduceFrame(int serverId, int cameraId, int value);								//Reduce frame forcedly.The value range from is 1~4. 1:full. 2:1/2. 3:1/3. 4:1/4
DLL_EXPORT int WP_PDVR_AutoReduceNight(int serverId, int cameraId, int value);								//Reduce frame in night automatically.The value is 0 or 1. 0:close this function. 1:open this function.
DLL_EXPORT int WP_PDVR_EnhanceEdge(int serverId, int cameraId, int value);									//Enhance the edge of video.The value is 0 or 1. 0:close this function. 1:open this function.
DLL_EXPORT int WP_PDVR_SetIRChangeMode(int serverId, int cameraId, int value);								//Set the mode for IR change.The value range from 0~2, 0:use hardware, 1: use hardware and software, 2:use software
DLL_EXPORT int WP_PDVR_SetExposeMode(int serverId, int cameraId, int value);									//Set the mode for expose light.The value is 0 or 1, 0:natural light, 1:electric light
DLL_EXPORT int WP_PDVR_SetExposePriority(int serverId, int cameraId, int value);								//Set the priority mode for expose.The value range from 0~3, 0:the brightest priority, 1:the darker priority, 2:the brighter priority, 3:the darkest priority
DLL_EXPORT int WP_PDVR_SetSensitivity(int serverId, int cameraId, int value);									//Set sensitivity for expose.The value range from 0 to 40
DLL_EXPORT int WP_PDVR_InvertVideo(int serverId, int cameraId);												//Invert the video.
DLL_EXPORT int WP_PDVR_SynchronizeTime(int serverId, struct tm sm);

//for PTZ
DLL_EXPORT int WP_PDVR_GetPTZInfo(int serverId, int cameraId, EXTPTZINFO *PTZInfo);
DLL_EXPORT int WP_PDVR_OperatePTZ(int serverId, int cameraId, int operate, int value = 0);						//Control the PTZ.
DLL_EXPORT int WP_PDVR_SetPTZInfo(int serverId, int cameraId, int operate, int GroupId, int PresetId, int StayTime, char *PresetName = 0);
																													//Set the PTZ info.GroupId:The id of cruise group.The cruise group id range 0~3.
																													//PresetId:The id of the preset point,a cruise group has the max num of preset is 128.
																													//StayTime:The time for each preset point to stay.
																													//PresetName:The name of the preset point.

//for record
DLL_EXPORT int WP_PDVR_SetRecord(int serverId, int cameraId, int weekDay, int startTime, int endTime, char mode); //Control record.weekDay:choose the day of a week to record.
																													//startTime:the time to start record.
																													//endTime:the time to stop record.
																													//mode:refer to the mode to record.

//for update
//DLL_EXPORT char *WP_PDVR_SelectFilePath();																		//Select the update file.
DLL_EXPORT int WP_PDVR_UpdatePDVR(int serverId, char *fileStr);													//Update the software of PDVR.fileStr:the name of update file
DLL_EXPORT int WP_PDVR_UpdateCamera(int serverId, int cameraId, char *fileStr);									//Update the software of camera.

//for DBox display
DLL_EXPORT int WP_PDVR_SetOptOnTv(int serverId, int cameraId, char *dboxIp, int optType, WORD rotateTime);		//Control PDVR on tv. serverId:the index of PDVR. cameraId:the index of cameraId.
																													//dboxip:the ip of decoder box.
																													//optType:the type to control decoder box. 0:four small stream on tv. 1:four small stream rotate on tv. 
																													//2:one big stream on tv. 3:one big stream rotate on tv. 
																													//rotateTime:the time for rotate.
//for photo
//DLL_EXPORT int WP_PDVR_CaptureJPG(unsigned char *pImageBuf, int width, int height, int dataFormat, char *fileName);     //Save the decoded data to jpg image.
                                                                                                                          //pImageBuf: the decoded data
                                                                                                                          //width:     the width of the image
                                                                                                                          //height:    the height of the image
                                                                                                                          //dataFormat:the format of the decoded data( DATA_FORMAT_YUYV / DATA_FORMAT_RGB24 )
                                                                                                                          //fileName:  the path and filename of the file
DLL_EXPORT int WP_PDVR_SaveJPG(unsigned char *pImageBuf, int length, char *fileName, char *pImagePath);
DLL_EXPORT int WP_PDVR_SendCommandToJPG(int serverId, int cameraId, int streamType);
DLL_EXPORT int  WP_PDVR_CaptureBMP(unsigned char *pImageBuf, int width, int height, int dataFormat, char *fileName, char *pImagePath);    //Save the decoded data to bmp image
//DLL_EXPORT int WP_PDVR_OnPhoto_Bmp(unsigned char* pImageBuf, int width, int height, char *pImageName, char *pImagePath = NULL);	//Photo. pImageBuf:decoded data. pImagePath:The default path is "c:\image"

typedef bool (CALLBACK *ProgressCallBack)(int currentPos);		
DLL_EXPORT int WP_GetProgressCallBack(ProgressCallBack fProgress);
DLL_EXPORT int WP_PDVR_GetFileByTime(int serverId, int cameraId, DATETIME dateStartTime, DATETIME dateEndTime, const char *pFilePath);

#endif		
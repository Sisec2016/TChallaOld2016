#ifndef _SNPLAYEX_HPP
#define _SNPLAYEX_HPP

#include <Windows.h>
#include <climits>
#include <cfloat>

#include "SnplayExDef.hpp"


//************************************
// Method:    获取播放库SDK版本号和build号SnPlay_GetSdkVersion
// FullName:  SnPlay_GetSdkVersion
// Returns:   DWORD PLAY_DLL_EXPORT
//************************************
DWORD PLAY_DLL_EXPORT SnPlay_GetSdkVersion();


//************************************
// Method:    初始化播放器,在调用播放器sdk所有函数之前调用,仅仅调用一次
// FullName:  SnPlay_Init
// Returns:   BOOL PLAY_DLL_EXPORT  成功返回TURE；失败返回FALSE
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Init();

//************************************
// Method:    反初始化播放器，在调用完播放器sdk所有函数后调用，仅仅调用一次
// FullName:  SnPlay_Destory
// Returns:   void PLAY_DLL_EXPORT
//************************************
void PLAY_DLL_EXPORT SnPlay_Destory();







//************************************
// Method:    获取未使用的通道号SnPlay_GetPort
// FullName:  SnPlay_GetPort
// Returns:   BOOL PLAY_DLL_EXPORT，成功返回TURE；失败返回FALSE
// Parameter: LONG * nPort	[out],播放通道号，指向用于获取端口号的LONG型变量指针 上限200
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_GetPort(LONG* nPort);


//************************************
// Method:    释放已使用的通道号
// FullName:  SnPlay_FreePort
// Returns:   BOOL PLAY_DLL_EXPORT，成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	释放已使用的通道号，释放成功后，外部程序需将nPort置为-1
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_FreePort(LONG nPort);



//------------------------------------------------------
//播放控制相关，播放，快进，慢进，暂停
//------------------------------------------------------

//************************************
// Method:    获取指定通道的播放状态,在调用快进，慢进，播放时状态的获取
// FullName:  SnPlay_GetPlayStatus
// Returns:   PLAY_EX_STATUS  PLAY_DLL_EXPORT
// Parameter: LONG nPort 播放通道号
//************************************
PLAY_EX_STATUS  PLAY_DLL_EXPORT SnPlay_GetPlayStatus(LONG nPort);



//************************************
// Method:    设置播放器播放文件时候播放状态
//			  播放器开始播放以后快进、慢进、暂停、正常播放状态的改变
//			  不包括停止, 停止时候调用SnPlay_Stop
//			  不包括暂停，暂停时调用SnPlay_Pause
// FullName:  SnPlay_SetPlayStatus
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: LONG nPort				播放通道号
// Parameter: PLAY_EX_STATUS pstatus	播放状态
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetPlayStatus(LONG nPort,PLAY_EX_STATUS pstatus);


//************************************
// Method:    开启播放,EX_PLAY,对于文件和实时流均调用此接口
// FullName:  SnPlay_Play
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: LONG nPort	播放通道号
// Parameter: HWND hWnd		播放视频的窗口句柄
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Play(LONG nPort, HWND hWnd);


//************************************
// Method:    关闭播放SnPlay_Stop
// FullName:  SnPlay_Stop
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	 播放通道号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Stop(LONG nPort);


//************************************
// Method:    暂停/恢复播放,兵兵开关
// FullName:  SnPlay_Pause
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort			播放通道号
// Parameter: DWORD nPause			TURE暂停，FALSE恢复
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Pause(LONG nPort,DWORD nPause);


//************************************
// Method:  单帧前进
//			恢复正常播放需要调用SnPlay_SetPlayStatus(EX_PLAY)
// FullName:  SnPlay_OneByOne
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	播放通道号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_OneByOne(LONG nPort);






//************************************
// Method:  设置快进速度
//			建议使用SnPlay_SetPlayStatus函数替换
// FullName:  SnPlay_FastEx
// Returns:   BOOL PLAY_DLL_EXPORT,成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	播放通道号
// Parameter: PLAY_EX_STATUS pstatus	开进速度,EX_PLAY2X,EX_PLAY4X,EX_PLAY8X,EX_PLAY16X
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_FastEx(LONG nPort,PLAY_EX_STATUS pstatus);


//************************************
// Method:    快速播放
//			  建议使用SnPlay_SetPlayStatus函数替换
//			  每次调用将使当前播放速度加快一倍(2,4,8,16)，最多调用4次；//			  
// FullName:  SnPlay_Fast
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	播放通道号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Fast(LONG nPort);


//************************************
// Method:    慢速播放
//			  建议使用SnPlay_SetPlayStatus函数替换
//			  每次调用将使当前播放速度慢一倍(2,4,8,16)；最多调用4次；
// FullName:  SnPlay_Slow
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort		播放通道号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Slow(LONG nPort);

//************************************
// Method:    快退播放
//			  建议使用SnPlay_SetPlayStatus函数替换
//			  每次调用将使当前播放速度加快一倍(2,4,8,16)，最多调用4次；//			  
// FullName:  SnPlay_Fast
// Returns:   BOOL PLAY_DLL_EXPORT	成功返回TURE；失败返回FALSE
// Parameter: LONG nPort	播放通道号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_Back(LONG nPort);


//************************************
// Method:    获取当前帧率
// FullName:  SnPlay_GetCurrentFrameRate
// Returns:   DWORD PLAY_DLL_EXPORT
// Parameter: LONG nPort	播放通道号
//************************************
DWORD PLAY_DLL_EXPORT SnPlay_GetCurrentFrameRate(LONG nPort);


//-----------------------------------------------------------------------------
//文件播放相关
//-----------------------------------------------------------------------------

//************************************
// Method:    设置解码消息回调,主要通知播放文件结束
// FullName:  SnPlay_SetDecMsgCallBack

// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: long lPort	 =player session
// Parameter: CALLBACK * DecMsgFun
// Parameter: long lPort	 =player session
// Parameter: int nFlag		 =消息类型，0表示缓冲区空
// Parameter: void * pUserData  =上下文数据
// Parameter: void * pUserData	=上下文数据
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetDecMsgCallBack(long lPort, 
	void (CALLBACK* DecMsgFun)(long lPort, int nFlag , void *pUserData), void *pUserData);


//************************************
// Method:    设置文件总图像帧数
// FullName:  SnPlay_SetFileFrameCnt
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: LONG nport		播放通道号
// Parameter: int fileFrameCnt	文件总帧数
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetFileFrameCnt(LONG nPort,int fileFrameCnt);

//************************************
// Method:    设置文件当前播放位置(百分比)
// FullName:  SnPlay_SetPlayPos
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: LONG nPort			播放通道号
// Parameter: float fRelativePos	播放位置,范围0-100%
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetPlayPos(LONG nPort,float fRelativePos);


//************************************
// Method:    获取文件当前播放位置（百分比）
// FullName:  SnPlay_GetPlayPos
// Returns:   float PLAY_DLL_EXPORT		文件播放位置范围0-100%
// Parameter: LONG nPort				播放通道号
//************************************
float PLAY_DLL_EXPORT SnPlay_GetPlayPos(LONG nPort);

//************************************
// Method:    设置当前播放播放位置到指定帧号
// FullName:  SnPlay_SetCurrentFrameNum
// Returns:   BOOL PLAY_DLL_EXPORT		成功返回TURE,失败返回FALSE
// Parameter: LONG nPort		播放通道号
// Parameter: DWORD nFrameNum	指定帧号
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);

//************************************
// Method:    获取文件当前播放帧号
// FullName:  SnPlay_GetCurrentFrameNum
// Returns:   DWORD PLAY_DLL_EXPORT
// Parameter: LONG nPort	播放通道号
//************************************
DWORD PLAY_DLL_EXPORT SnPlay_GetCurrentFrameNum(LONG nPort);




//************************************
// Method:    抓图(BMP格式)
// FullName:  SnPlay_CaptureBmpPicture
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: long lPort		 播放通道号
// Parameter: char * filename	 抓图文件名 
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_CaptureBmpPicture(long lPort,char * filename);


/*函数说明：CaptureBmpPicture
/*参数: long lPort  = player session
/*            char * filename= the file's name of saved Jpeg file*/

//************************************
// Method:    抓图(jpeg格式)
// FullName:  SnPlay_CaptureJpegPicture
// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: long lPort		播放通道号
// Parameter: char * filename	抓图文件名
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_CaptureJpegPicture(long lPort,char * filename);


//-----------------------------------------------------------------------------
//数据流接口
//-----------------------------------------------------------------------------

//************************************
// Method:    输入流数据,外部调用者必须保证失败时候再次尝试输入数据，否则数据会丢失
// FullName:  SnPlay_InputData
// Returns:   BOOL PLAY_DLL_EXPORT	TURE=输入到播放器。FALSE 表示失败，数据没有输入播放器
// Parameter: LONG nPort		播放通道号
// Parameter: PBYTE pBuf		流数据缓冲区地址
// Parameter: DWORD nSize		流数据缓冲区大小
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);



















/*函数说明：打开文件SnPlay_OpenFile
/*参 数：LONG nPort 播放通道号
/*参 数：LPSTR sFileName 文件名
/*返回值：成功返回TURE；失败返回FALSE
/*注 意：文件不能超过4G或小于4K*/
BOOL PLAY_DLL_EXPORT SnPlay_OpenFile(LONG nPort,LPSTR sFileName);

/*函数说明：关闭文件
/*参 数：无
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_CloseFile(LONG nPort);


/*函数说明：设置流播放模式SnPlay_SetStreamOpenMode
/*参数：LONG nPort 播放通道号
/*参数：DWORD nMode 流播放模式：EX_STREAM,EX_FILE_STREAM EX_STREAM模式（默认）下, 会尽量保正实时性, 防止数据阻塞; 而且数据检查严格;
/*      EX_FILE_STREAM模式下则不然.
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_SetStreamOpenMode(LONG nPort,DWORD nMode);

/*函数说明：获取流播放模式SnPlay_GetStreamOpenMode
/*参 数：LONG nPort 播放通道号
/*返回值：STREAME_REALTIME或STREAME_FILE*/
LONG PLAY_DLL_EXPORT SnPlay_GetStreamOpenMode(LONG nPort);

/*函数说明：打开流SnPlay_OpenStream
/*参 数：LONG nPort 播放通道号
/*参 数：PBYTE pFileHeadBuf 文件头数据
/*参 数：DWORD nSize 文件头长度
/*参 数：DWORD nBufPoolSize 设置播放器中存放数据流的缓冲区大小。 范围是SOURCE_BUF_MIN~ SOURCE_BUF_MAX。该值过小会导致无法解码，建议标清设备该值大于等于200*1024，高清设备大于等于600*1024。
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize, DWORD nBufPoolSize);

/*函数说明：关闭流SnPlay_CloseStream
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_CloseStream(LONG nPort);



/*函数说明：打开流（以音视频分开输入方式）SnPlay_OpenStreamEx
/*参 数：LONG nPort 播放通道号
/*参 数：PBYTE pFileHeadBuf 文件头数据
/*参 数：DWORD nSize DWORD 文件头长度
/*参 数：nBufPoolSize 设置播放器中存放数据流的缓冲区大小。范围是SOURCE_BUF_MIN~ SOURCE_BUF_MAX
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：以音视频分开输入的方式打开流*/
BOOL PLAY_DLL_EXPORT SnPlay_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize, DWORD nBufPoolSize);

/*函数说明：关闭流（以音视频分开输入方式）SnPlay_CloseStreamEx
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_CloseStreamEx(LONG nPort);

/*函数说明：输入视频流SnPlay_InputVideoData
/*参 数：LONG nPort 播放通道号
/*参数 PBYTE pBuf 缓冲区地址 
/*参数DWORD nSize 缓冲区大小
/*返回值：TURE,表示已经输入数据。FALSE 表示失败，数据没有输入
/*说 明：输入视频流 (可以是复合流，但音频数据会被忽略);；打开流之后才能输入数据*/
BOOL PLAY_DLL_EXPORT SnPlay_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);

/*函数说明：输入音频流SnPlay_InputAudioData
/*参 数：LONG nPort 播放通道号
/*参 数：PBYTE pBuf 缓冲区地址 
/*参 数：DWORD nSize 缓冲区大小
/*返回值：TURE,表示已经输入数据。FALSE 表示失败，数据没有输入
/*说 明：输入音频流；打开声音之后才能输入数据。返回False是由于内部缓冲区满，建议客户暂停输入数据线程，再次输入数据，确保播放库不丢失数据*/
BOOL PLAY_DLL_EXPORT SnPlay_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);







/*函数说明：以独占方式打开声音SnPlay_PlaySound
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：同一时刻只能有一路声音。如果现在已经有声音打开，则自动关闭原来已经打开的声音*/
BOOL PLAY_DLL_EXPORT SnPlay_PlaySound(LONG nPort);

/*函数说明：关闭声音（独占方式）SnPlay_StopSound
/*参 数：无
/*返回值：成功返回TURE；失败返回FALSE
/*注 意：SnPlay_PlaySound，SnPlay_StopSound需要配对调用*/
BOOL PLAY_DLL_EXPORT SnPlay_StopSound(LONG nPort);

/*函数说明：以共享方式打开声音SnPlay_PlaySoundShare
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：以共享方式播放声音，只管播放本路声音而不去关闭其他路的声音*/
BOOL PLAY_DLL_EXPORT SnPlay_PlaySoundShare(LONG nPort);

/*函数说明：关闭声音（共享方式）SnPlay_StopSoundShare
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：以共享方式关闭声音。SnPlay_PlaySound和SnPlay_StopSound是以独占方式播放声音的*/
BOOL PLAY_DLL_EXPORT SnPlay_StopSoundShare(LONG nPort);

/*函数说明：设置音量SnPlay_SetVolume
/*参 数：LONG nPort 播放通道号
/*参 数：WORD nVolume 音量值，范围0-0XFFFF
/*返回值：成功返回TURE；失败返回FALSE
说 明：可以在播放之前设置，返回值是FALSE，但设置的值被保存，并作为启动声音时的初始音量。这里的音量是只声卡输出的主音量，会影响到其他的声音应用*/
BOOL PLAY_DLL_EXPORT SnPlay_SetVolume(LONG nPort,WORD nVolume);

/*函数说明：获取音量SnPlay_GetVolume
/*参 数：LONG nPort 播放通道号
/*返回值：音量值。这里的音量是只声卡输出的主音量，会影响到其他的声音应用*/
WORD PLAY_DLL_EXPORT SnPlay_GetVolume(LONG nPort);

/*函数说明：调整WAVE波形SnPlay_AdjustWaveAudio
/*参 数：LONG nPort 播放通道号
/*参 数：LONG nCoefficient 调整参数，0是不调整， 范围从MIN_WAVE_COEF 到 MAX_WAVE_COEF，
/*返回值：成功返回TURE；失败返回FALSE
说 明：调整WAVE波形，可以改变声音的大小。和SnPlay_SetVolume的不同在于，它是调整声音数据，只对该路其作用，而SnPlay_SetVolume是调整声卡音量，对整个系统起作用*/
BOOL PLAY_DLL_EXPORT SnPlay_AdjustWaveAudio(LONG nPort,LONG nCoefficient);

/*函数说明：设置图像质量SnPlay_SetPicQuality
/*参 数：LONG nPort 播放通道号
/*BOOL bHighQuality 等于1时图像高质量，等于0时低质量（默认值）。
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：当设置成高质量时画面效果好，但CPU利用率高。在支持多路播放时，可以设为低质量，以降低CPU利用率；当某路放大播放时将该路设置成高质量，以达到好的画面效果*/
BOOL PLAY_DLL_EXPORT SnPlay_SetPicQuality(LONG nPort,BOOL bHighQuality);

/*函数说明：获取图像质量SnPlay_GetPictureQuality
/*参 数：LONG nPort 播放通道号
/*参 数：[out]BOOL *bHighQuality 1表示高质量，0表示低质量
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_GetPictureQuality(LONG nPort,BOOL *bHighQuality);

/*函数说明：设置视频参数SnPlay_SetColor
/*参 数：LONG nPort 播放通道号 
/*参 数：DWORD nRegionNum 显示区域，参考SnPlay_SetDisplayRegion 如果只有一个显示区域(通常情况);设为0
/*参 数：int nBrightness  亮度，默认64 范围0-128
/*参 数：int nContrast  对比度，默认64 范围0-128
/*参 数：int nSaturation  饱和度，默认64 范围0-128
/*参 数：int nHue 色调，默认64 范围0-128
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

/*函数说明：获取视频参数SnPlay_GetColor
/*参 数：LONG nPort 播放通道号
/*参 数：DWORD nRegionNum 显示区域
/*参 数：[out]int *pBrightness 亮度，默认64； 范围0-128
/*参 数：[out]int *pContrast 对比度，默认64； 范围0-128
/*参 数：[out]int *pSaturation 饱和度，默认64； 范围0-128
/*参 数：[out]int *pHue 色调，默认64； 范围0-128
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast,int *pSaturation, int *pHue);

/*函 数：设置文件当前播放时间（毫秒）SnPlay_SetPlayedTimeEx
参 数：LONG nPort DWORD nTime播放通道号 设置文件播放到指定时间，单位毫秒
返回值：成功返回TURE；失败返回FALSE
说明：根据时间设置文件播放位置*/
BOOL PLAY_DLL_EXPORT SnPlay_SetPlayedTimeEx(LONG nPort,DWORD nTime);

/*函 数：获取文件当前播放时间（毫秒）SnPlay_GetPlayedTimeEx
参 数：LONG nPort播放通道号
返回值：文件当前播放的时间，单位毫秒*/
DWORD PLAY_DLL_EXPORT SnPlay_GetPlayedTimeEx(LONG nPort);


/*函 数：获取文件总时间SnPlay_GetFileTime
参 数：LONG nPort播放通道号
返回值：文件总时间长度，单位秒*/
DWORD PLAY_DLL_EXPORT SnPlay_GetFileTime(LONG nPort);

/*函 数：获取文件总帧数SnPlay_GetFileTotalFrames
参 数：LONG nPort播放通道号
返回值：文件总帧数*/
DWORD PLAY_DLL_EXPORT SnPlay_GetFileTotalFrames(LONG nPort);


/*函 数：获取已播放时间SnPlay_GetPlayedTime
参 数：LONG nPort播放通道号
返回值：文件当前播放时间，单位秒*/
DWORD PLAY_DLL_EXPORT SnPlay_GetPlayedTime(LONG nPort);

/*函 数：获取已解码的视频帧数SnPlay_GetPlayedFrames
参 数：LONG nPort播放通道号
返回值：已经解码的视频帧数*/
DWORD PLAY_DLL_EXPORT SnPlay_GetPlayedFrames(LONG nPort);

/*函 数：获取原始图像大小SnPlay_GetPictureSize
参 数：
LONG nPort, [out]LONG *pWidth, [out]LONG *pHeight
播放通道号 原始图像的宽度 原始图像的高度
返回值：成功返回TURE；失败返回FALSE
说 明：获得码流中原始图像的大小，根据此大小来设置显示窗口的区域，可以不使用显卡做缩放工作，对于那些不支持硬件缩放的显卡来说非常有用*/
BOOL PLAY_DLL_EXPORT SnPlay_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);

/*函 数：获取文件头长度SnPlay_GetFileHeadLength
参 数：无
返回值：返回用于交互的海康媒体文件头或海康媒体信息头的大小*/
DWORD PLAY_DLL_EXPORT SnPlay_GetFileHeadLength();;

/*函 数：设置解码回调流类型SnPlay_SetDecCBStream
参 数：
LONG nPort DWORD nStream
播放通道号 1视频流，2音频流，3复合流
返回值：成功返回TURE；失败返回FALSE
说 明：建议在解码回调函数前使用*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDecCBStream(LONG nPort,DWORD nStream);

/*函 数：解码回调SnPlay_SetDecCallBack
参 数：
LONG nPort void (CALLBACK* DecCBFun); DecCBFun回调函数参数说明 nPort pBuf nSize pFrameInfo nReserved1，nReserved2 SNEX_FRAME_INFO结构说明typedef struct{ long nWidth; long nHeight; long nStamp; long nType long nFrameRate; DWORD dwFrameNum; }SNEX_FRAME_INFO; 宏定义说明T_AUDIO16 T_RGB32 T_UYVY
播放通道号 解码回调函数指针，不能为NULL 播放器通道号 解码后的音视频数据 解码后的音视频数据pBuf的长度 图像和声音信息 保留参数 画面宽，单位像素。如果是音频数据则为0； 画面高。如果是音频数据则为0； 时标信息，单位毫秒数据类型，T_AUDIO16，T_RGB32， T_YV12， 编码时产生的图像帧率帧号 音频数据;采样率16khz，单声道，每个采样点16位表示。视频数据。每个像素4个字节，排列方式与位图相似，“B-G-R-0 …”，第一个像素位于图像左下角。视频数据，uyvy格式。“U0-Y0-V0-Y1-U2-Y2-V2-Y3….”，第一个像素位于图像左上角
返回值：成功返回TURE；失败返回FALSE
说 明：设置回调函数，替换播放器中的显示部分，由用户自己控制显示，该函数在SnPlay_Play之前调用，在SnPlay_Stop时自动失效，下次调用SnPlay_Play之前需要重新设置。*/	
BOOL PLAY_DLL_EXPORT SnPlay_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,SNEX_FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));


/*函 数：解码回调（增加用户传递参数）SnPlay_SetDecCallBackMend
参 数：
LONG nPort void (CALLBACK* DecCBFun); long nUser DecCBFun回调函数参数 long nPort char * pBuf long nSize SNEX_FRAME_INFO * pFrameInfo long nUser long nReserved2 SNEX_FRAME_INFO类型说明 typedef struct{ long nWidth long nHeight long nStamp long nType long nFrameRate }SNEX_FRAME_INFO;
播放通道号 解码回调函数，不能为NULL 用户数据 播放通道号 解码后的视音频数据 解码后的视音频数据长度 图像与声音信息 用户数据 保留参数 画面宽，单位像素。如果是音频数据则为0 画面高。如果是音频数据则为0 时标信息，单位毫秒 数据类型，T_AUDIO16，T_RGB32， T_YV12 编码时产生的图像帧率
返回值：成功返回TURE；失败返回FALSE
说 明：设置回调函数，替换播放器中的显示部分，由用户自己控制显示，该函数在SnPlay_Play之前调用，在SnPlay_Stop时自动失效，下次调用SnPlay_Play之前需要重新设置。注意解码部分不控制速度，只要用户从回调函数中返回，解码器就会解码下一部分数据。这个功能的使用需要用户对视频显示和声音播放有足够的了解，否则请慎重使用，有关知识请参阅directx开发包。和解码回调*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDecCallBackMend(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,SNEX_FRAME_INFO * pFrameInfo, long nUser, long nReserved2), long nUser);

/*函 数：音频解码回调SnPlay_SetAudioCallBack *
参 数：
LONG nPort void (__stdcall * funAudio); long nUser funAudio回调函数参数 long nPort char * pAudioBuf long nSize long nStamp long nType long nUser
播放通道号 音频解码回调函数 用户数据 播放通道号 wave格式音频数据 音频数据长度 时标(ms); 音频类型T_AUDIO16, 采样率16khz，单声道，每个采样点16位 用户数据
返回值：成功返回TURE；失败返回FALSE		*/
BOOL PLAY_DLL_EXPORT SnPlay_SetAudioCallBack(LONG nPort, void (__stdcall * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);;

/*函 数：文件结束消息SnPlay_SetFileEndMsg
参 数：
LONG nPort HWND hWnd UINT nMsg
播放通道号消息发送的窗口用户自定义的输入的消息；当播放到文件结束时用户从hWnd窗口过程中收到这个消息。此消息函数中的wParam参数返回nPort的值
返回值：成功返回TURE；失败返回FALSE
说 明：设置文件结束时要发送的消息；从2.4版本SDK起，当文件播放完时，解码线程将不会自动结束，需要用户做停止工作。应用程序在收到这个消息后要调用播放结束函数SnPlay_Stop(nPort);*/
BOOL PLAY_DLL_EXPORT SnPlay_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);

/*函 数：文件结束回调SnPlay_SetFileEndCallback
参 数：
LONG nPort void(CALLBACK*FileEndCallback); void *pUser FileEndCallback回调函数参数 long nPort void *pUser
播放通道号 文件结束回调函数 用户数据 播放通道号 用户数据
返回值：成功返回TURE；失败返回FALSE
说 明：设置文件播放结束回调函数。在SnPlay_OpenSteam/SnPlay_OpenFile之前调用才有效	*/	
BOOL PLAY_DLL_EXPORT __stdcall SnPlay_SetFileEndCallback(LONG nPort, void(CALLBACK*FileEndCallback)(long nPort, void *pUser), void *pUser);;

/*函 数：分辨改变通知消息SnPlay_SetEncChangeMsg
参 数：
LONG nPort HWND hWnd UINT nMsg
播放通道号 hWnd 消息发送的窗口 用户输入的消息；当设置解码时编码格式发生改变时要发送此定义的消息。消息函数中的wParam参数值是返回nPort的值。
返回值：成功返回TURE；失败返回FALSE
说 明：设置解码时编码分辨率发生改变时要发送的消息*/		
BOOL PLAY_DLL_EXPORT SnPlay_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

/*函 数：分辨率改变通知回调SnPlay_SetEncTypeChangeCallBack
参 数：
LONG nPort void(CALLBACK *funEncChange); long nUser funEncChange回调函数参数 long nPort long nUser
播放通道号 分辨率发生改变时通知用户的回调函数 用户数据 播放通道号 用户数据
返回值：成功返回TURE；失败返回FALSE
说 明：需要在打开文件之前使用*/		
BOOL PLAY_DLL_EXPORT SnPlay_SetEncTypeChangeCallBack (LONG nPort,void(CALLBACK *funEncChange)(long nPort,long nUser),long nUser);

/*函 数：设置丢B帧个数SnPlay_ThrowBFrameNum
参 数：
LONG nPort DWORD nNum
播放通道号 不解码B帧的帧数。范围0~2
返回值：成功返回TURE；失败返回FALSE
说 明：设置不解码B帧帧数；不解码B帧，可以减小CPU利用率，如果码流中没有B帧，那么设置这个值将不会有作用。如在快速播放，和支持多路而CPU利用率太高的情况下可以考虑使用。*/
BOOL PLAY_DLL_EXPORT SnPlay_ThrowBFrameNum(LONG nPort,DWORD nNum);

/*函 数：检查帧号是否连续SnPlay_CheckDiscontinuousFrameNum
参 数：LONG nPort BOOL bCheck播放通道号 帧号不连续时是否跳下一个I帧
返回值：成功返回TURE；失败返回FALSE
说 明：检查帧号是否连续， 4.8build0813、6.1.1.17版本支持。	*/	
BOOL PLAY_DLL_EXPORT SnPlay_CheckDiscontinuousFrameNum(LONG nPort, BOOL bCheck);

/*函 数：解码密钥SnPlay_SetSecretKey
参 数：
LONG nPort LONG lKeyType char *pSecretKey LONG lKeyLen
播放通道号 密钥类型 密钥串 密钥长度，单位为bit（1字节为8 bit）
返回值：
成功返回TURE；失败返回FALSE
说 明：
如果在编码时设置了密钥，那么在解码之前需要调用该接口设置密钥才能正常解码。该接口在SnPlay_OpenSteam/SnPlay_OpenFile之前调用才有效。	*/	
BOOL PLAY_DLL_EXPORT __stdcall SnPlay_SetSecretKey(LONG nPort, LONG lKeyType, char *pSecretKey, LONG lKeyLen);

/*函 数：设置OVERLAY显示模式及关键色SnPlay_SetOverlayMode	
参 数：
LONG nPort BOOL bOverlay
播放通道号
TRUE表示将首先尝试使用OVERLAY模式，如果不行再使用		
返回值：成功返回TURE；失败返回FALSE
说 明：设置OVERLAY模式显示画面。在一块显卡中同一时刻只能有一个OVERLAY表面处于活动状态，如果此时系统中已经有程序使用了OVERLAY，那么播放器就不能再创建OVERLAY表面，它将自动改用Off_Screen表面，并不返回FALSE。一些常用的播放器，以及我们卡的预览都可能使用了overlay表面。同样，如果播放器使用了OVERLAY表面，那么，其他的程序将不能使用OVERLAY表面，特别注意，我们的卡在预览时可能也要使用OVERLAY(用户可设置);，如果先打开播放器（并且使用了OVERLAY），再启动预览，那么预览可能因为得不到OVERLAY而失败。使用OVERLAY模式的优点是：大部份的显卡都支持OVERLAY，在一些不支持BLT硬件缩放和颜色转换的显卡上(如SIS系列显卡);使用OVERLAY模式（OVERLAY模式下的缩放和颜色转换由显卡支持），可以大大减小cpu利用率并提高画面质量（相对于软件缩放和颜色转换）。缺点是：只能有一路播放器使用。该设置必须在PLAY之前使用，而且需要设置透明色。*/
BOOL PLAY_DLL_EXPORT SnPlay_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);

/*函 数：获取OVERLAY关键色SnPlay_GetColorKey
参 数：LONG nPort 播放通道号
返回值：颜色值	*/	
COLORREF PLAY_DLL_EXPORT SnPlay_GetColorKey(LONG nPort);

/*函 数：设置或增加显示区域SnPlay_SetDisplayRegion
参 数：LONG nPort DWORD
播放通道号 显示区域序号，0~(MAX_DISPLAY_WND-1);。nRegionNum RECT *pSrcRect HWND hDestWnd BOOL bEnable
如果nRegionNum为0，表示对主要显示窗口(SnPlay_Play中设置的窗口);进行设置，将忽略hDestWnd和bEnable的设置。 设置在要显示的原始图像上的区域，如：如果原始图像是352*288，那么pSrcRect可设置的范围只能在（0，0，352，288）之中。如果pSrcRect=NULL,将显示整个图像。 设置显示窗口。如果该区域的窗口已经设置过（打开过），那么该参数被忽略。 打开（设置）或关闭显示区域。	
返回值：
成功返回TURE；失败返回FALSE
说 明：
设置或增加显示区域。可以做局部放大显示。*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);

/*函 数：刷新显示SnPlay_RefreshPlay
参 数：LONG nPort播放通道号
返回值：成功返回TURE；失败返回FALSE
说 明：刷新显示。当用户暂停时如果刷新了窗口，则窗口中的图像因为刷新而消失，此时调用这个接口可以重新把图像显示出来。只有在暂停和单帧播放时才会执行，其它情况会直接返回。*/
BOOL PLAY_DLL_EXPORT SnPlay_RefreshPlay(LONG nPort);

/*函 数：刷新显示（多显示区域）SnPlay_RefreshPlayEx
参 数：LONG nPort DWORD nRegionNum播放通道号 显示区域序号
返回值：成功返回TURE；失败返回FALSE
说 明：刷新显示，同SnPlay_RefreshPlay。为支持SnPlay_SetDisplayRegion而增加一个参数。	*/	
BOOL PLAY_DLL_EXPORT SnPlay_RefreshPlayEx(LONG nPort,DWORD nRegionNum);

/*函 数：设置显示模式SnPlay_SetDisplayType
参 数：LONG nPort LONG nType播放通道号 两种模式： ISPLAY_NORMAL 正常分辨率数据送显卡显示。 DISPLAY_QUARTER 1/4分辨率数据送显卡显示。
返回值：成功返回TURE；失败返回FALSE
说 明：设置显示的模式，在小画面显示时，采用DISPLAY_QUARTER 可以减小显卡工作量，从而支持更多路显示，但画面显示质量有下降。在正常和大画面显示时应该使用*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDisplayType(LONG nPort,LONG nType);

/*函 数：获取显示模式SnPlay_GetDisplayType
参 数：LONG nPort播放通道号
返回值：DISPLAY_NORMAL 或 DISPLAY_QUARTER*/		
LONG PLAY_DLL_EXPORT SnPlay_GetDisplayType(LONG nPort);

/*函 数：获取源缓冲区剩余数据大小SnPlay_GetSourceBufferRemain
参 数：LONG nPort 播放通道号
返回值：当前源缓冲的大小（BYTE）	*/	
DWORD PLAY_DLL_EXPORT SnPlay_GetSourceBufferRemain(LONG nPort);

/*函 数：设置源缓冲区阈值及回调指针SnPlay_SetSourceBufCallBack
参 数：nThreShold SourceBufCallBack dwUser pReserved SourceBufCallBack回调函数参数说明 nPort nBufSize dwUser pResvered
阀值 回调函数指针 用户数据 保留数据 播放器通道号 缓冲区中剩余数据 用户数据 保留数据
返回值：成功返回TURE；失败返回FALSE
说 明：设置源缓冲区阀值和剩余数据小于等于阀值时的回调函数指针。只有在数据量从大到小"越过"指定阈值的时候, 才会触发回调; 一次触发后需要调用		*/
BOOL PLAY_DLL_EXPORT SnPlay_SetSourceBufCallBack(LONG nPort,DWORD nThreShold, void (CALLBACK * SourceBufCallBack)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);

/*函 数：重置回调标志为有效状态SnPlay_ResetSourceBufFlag
参 数：LONG nPor 播放通道号
返回值：成功返回TURE；失败返回FALSE
说 明：重置回调标志位为有效状态。*/		
BOOL PLAY_DLL_EXPORT SnPlay_ResetSourceBufFlag(LONG nPort);

/*函 数：设置播放缓冲区最大缓冲帧数SnPlay_SetDisplayBuf
参 数：
LONG nPort DWORD nNum
播放通道号 播放缓冲区最大缓冲帧数。范围：MIN_DIS_FRAMES ~MAX_DIS_FRAMES。一帧352*288图像的所需内存最小值是 352*288*3/2大约150K 。最大值是352*288*4大约405K。
返回值：成功返回TURE；失败返回FALSE
说 明：设置播放缓冲区（即解码后的图像缓冲区）大小；这个缓冲区比较重要，他直接影响播放的流畅性和延时性。在一定范围内缓冲越大越流畅，同时延时越大。在播放文件时用户最好可以考虑开大缓冲（如果内存足够大），我们的默认值是15（帧），在25帧/秒的情况下即0.6秒的数据。在播放流时我们的默认值是10(帧);，如果用户追求最大延时最小，可以考虑适当减小这个值。*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDisplayBuf(LONG nPort,DWORD nNum);

/*函 数：获取播放缓冲区最大缓冲帧数SnPlay_GetDisplayBuf
参 数：LONG nPort播放通道号
返回值：播放缓冲区最大缓冲帧数	*/	
DWORD PLAY_DLL_EXPORT SnPlay_GetDisplayBuf(LONG nPort);

/*函 数：清空所有缓冲区的剩余数据SnPlay_ResetSourceBuffer
参 数：LONG nPort 播放通道号
返回值：成功返回TURE；失败返回FALSE	*/	
BOOL PLAY_DLL_EXPORT SnPlay_ResetSourceBuffer(LONG nPort);

/*函 数：清空指定缓冲区的剩余数据SnPlay_ResetBuffer
参 数：LONG nPort DWORD nBufType 缓冲区宏定义 BUF_VIDEO_SRC BUF_AUDIO_SRC BUF_VIDEO_RENDER BUF_AUDIO_RENDER
播放通道号 缓冲区类型 视频数据源缓冲区，缓冲解码之前视频数据，只对流模式有效，单位byte。 音频数据源缓冲区，缓冲解码之前音频数据，只对流模式有效，单位byte。且音视频数据分开送到情况下才有效 视频播放缓冲区剩余数据，单位帧数。 音频播放缓冲区剩余数据，单位帧数，音频40ms数据定为一帧。
返回值：成功返回TURE；失败返回FALSE		*/
BOOL PLAY_DLL_EXPORT SnPlay_ResetBuffer(LONG nPort,DWORD nBufType);

/*函 数：获取指定缓冲区的大小SnPlay_GetBufferValue
参 数：LONG nPort DWORD nBufType 缓冲区宏定义 BUF_VIDEO_SRC BUF_AUDIO_SRC BUF_VIDEO_RENDER BUF_AUDIO_RENDER
播放通道号 缓冲区类型 视频数据源缓冲区，缓冲解码之前视频数据，只对流模式有效，单位byte。 音频数据源缓冲区，缓冲解码之前音频数据，只对流模式有效，单位byte。且音视频数据分开送到情况下才有效 视频播放缓冲区剩余数据，单位帧数。 音频播放缓冲区剩余数据，单位帧数，音频40ms数据定为一帧。
返回值：根据参数不同，返回缓冲区值，源缓冲区返回byte,解码后缓冲区返回帧数。
说 明：获取播放器中的缓冲区大小（帧数或者byte）。这个接口可以帮助用户了解缓冲区中的数据，从而在网络延时方面有所估计。*/
DWORD PLAY_DLL_EXPORT SnPlay_GetBufferValue(LONG nPort,DWORD nBufType);

/*函 数：设置建立索引回调SnPlay_SetFileRefCallBack
参 数：
LONG nPort void (__stdcall *pFileRefDone); DWORD nUser pFileRefDone回调函数参数说明 nPort nUser
播放通道号 索引回调函数 用户数据 播放器通道号 用户数据
返回值：
成功返回TURE；失败返回FALSE
说 明：
文件索引建立后回调。 为了能在文件中准确快速的定位，我们在文件打开的时候生成文件索引。这个过程耗时比较长，大约每秒处理40M左右的数据，主要是因为从硬盘读数据比较慢。建立索引的过程是在后台完成，需要使用索引的函数要等待这个过程结束，而其他接口不会受到影响。 打开文件时是否建立文件的关键帧索引, 如果索引回调未触发, 表明录像文件异常。*/
BOOL PLAY_DLL_EXPORT SnPlay_SetFileRefCallBack(LONG nPort, void (__stdcall *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);

/*函 数：查找指定位置之前的关键帧位置SnPlay_GetKeyFramePos
/*参 数：LONG nPort DWORD nValue DWORD nType PSNEX_FRAME_POS pFramePos PSNEX_FRAME_POS类型说明 typedef struct{ long nFilePos long nFrameNum long nFrameTime }SNEX_FRAME_POS,*PSNEX_FRAME_POS;
播放通道号 当前位置，可以是时间或帧号，类型由nType指定 nValue类型。如果nType 是BY_FRAMENUM则nValue表示帧号，如果nType 是BY_FRAMTIME，则nValue表示时间，单位毫秒 查找到的关键帧的文件位置、帧序号、时标信息 文件位置 帧序号 帧时标（毫秒）
返回值：成功返回TURE；失败返回FALSE	
说 明：查找指定位置之前的关键帧位置。图像解码必须从关键帧开始，如果用户保存的文件不是从关键帧开始的，那么到下一个关键帧之前的数据会被忽略。如果用户要截取文件中的一段数据，则应该考虑从关键帧开始截取。结束位置则关系不大，最多丢失3帧数据。 在文件索引建立完成的前提下, 这两个接口（81、82）可以用来实现剪辑录像文件, 剪辑精度与关键帧间隔有关.*/	
BOOL PLAY_DLL_EXPORT SnPlay_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PSNEX_FRAME_POS pFramePos);

/*函 数：查找指定位置之后的关键帧位置SnPlay_GetNextKeyFramePos
参 数：
LONG nPort DWORD nValue DWORD nType PSNEX_FRAME_POS pFramePos
播放通道号 当前位置，可以是时间或帧号，类型由nType指定 nValue类型。如果nType 是BY_FRAMENUM则nValue表示帧号，如果nType 是BY_FRAMTIME，则nValue表示时间，单位毫秒 查找到的关键帧的文件位置、帧序号、时标信息
返回值：成功返回TURE；失败返回FALSE
说 明：查找指定位置之后的关键帧位置 在文件索引建立完成的前提下, 这两个接口（81、82）可以用来实现剪辑录像文件, 剪辑精度与关键帧间隔有关.*/
BOOL PLAY_DLL_EXPORT SnPlay_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PSNEX_FRAME_POS pFramePos);

/*函 数：获取文件索引SnPlay_GetRefValue
参 数：
LONG nPort [out]BYTE *pBuffer DWORD *pSize
播放通道号 索引信息 输入pBuffer的大小，输出索引信息大小。注意：可以在第一次指定pSize=0,pBuffer=NULL,从pSize的返回值获得需要的缓冲区大小。然后分配足够的缓冲，再调用一次
返回值：成功返回TURE；失败返回FALSE
说 明：获取文件索引信息，以便下次打开同一个文件时直接使用这个信息。必须在索引建成后才能获得信息。*/
BOOL PLAY_DLL_EXPORT SnPlay_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);

/*函 数：设置文件索引SnPlay_SetRefValue
参 数：
LONG nPort BYTE *pBuffer
播放通道号 索引信息		
DWORD nSize
索引信息的长度
返回值：成功返回TURE；失败返回FALSE
说 明：设置文件索引。如果已经有了文件索引信息，可以不再调用生成索引的回调函数 SnPlay_SetFileRefCallBack，直接输入索引信息。	*/
BOOL PLAY_DLL_EXPORT SnPlay_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);

/*函 数：枚举系统中的显示设备SnPlay_InitDDrawDevice 注意：V6.1.1.0及以上的版本对于多屏显示自适应处理，不需要再调用下面这部分函数。
参 数：无
返回值：成功返回TURE；失败返回FALSE		*/
BOOL PLAY_DLL_EXPORT SnPlay_InitDDrawDevice();

/*函 数：释放枚举显示设备过程分配的资源SnPlay_ReleaseDDrawDevice
参 数：无
返回值：Void	*/	
void PLAY_DLL_EXPORT SnPlay_ReleaseDDrawDevice();


/*函 数：获取显示设备（显卡）个数SnPlay_GetDDrawDeviceTotalNums
参 数：如果返回0，则表示系统中只有主显示设备。如果返回1，则表示系统中安装了多块显卡，但只有一块显卡与Windows桌面绑定。返回其他值，则表示系统中与桌面绑定的显卡数目。在多显卡的系统中可以通过设置显示属性，而指定任意一块显卡作为主显示设备。
返回值：成功返回TURE；失败返回FALSE
说 明：获得系统中与windows桌面绑定的总的显示设备数目（这里主要是指显卡）	*/	
DWORD PLAY_DLL_EXPORT SnPlay_GetDDrawDeviceTotalNums();

/*函 数：设置播放窗口使用的显示设备SnPlay_SetDDrawDevice
参 数：LONG nPort DWORD nDeviceNum
播放通道号 显示设备的设备号，如果是0，则表示使用主显示设备
返回值：成功返回TURE；失败返回FALSE
说 明：设置播放窗口使用的显卡。注意该窗口必须在该显卡所对应的监视器上才能显示播放画面。*/		
BOOL PLAY_DLL_EXPORT SnPlay_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

/*函 数：设置播放窗口使用的显示设备（多显示区域）SnPlay_SetDDrawDeviceEx *
参 数：LONG nPort, DWORD nRegionNum DWORD nDeviceNum
播放通道号 显示区域 显示设备的设备号
返回值：成功返回TURE；失败返回FALSE
说 明：设置播放窗口使用的显卡，功能同SnPlay_SetDDrawDevice。 为支持SnPlay_SetDisplayRegion而增加一个参数。*/		
BOOL PLAY_DLL_EXPORT SnPlay_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum, DWORD nDeviceNum);;

/*函 数：获取指定显卡和监视器信息SnPlay_GetDDrawDeviceInfo
参 数：
DWORD nDeviceNum LPSTR lpDriverDescription DWORD nDespLen [out]LPSTR lpDriverName [out]DWORD nNameLen [out]HMONITOR *hhMonitor
显示设备的设备号，如果是0，则表示主显示设备。 表示lpDriverDescription已分配空间的大小，单位byte。 表示lpDriverName已分配空间的大小，单位byte 显示设备的描述信息 显示设备的设备名
显示设备使用的监视器句柄，通过Windows API 函数GetMonitorInfo，可以得到详细信息，供用户定位窗口位置。
返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_GetDDrawDeviceInfo(DWORD nDeviceNum, LPSTR lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName , DWORD nNameLen,HMONITOR *hhMonitor);

/*函 数：获取指定显示设备的系统信息SnPlay_GetCapsEx
参 数：DWORD nDDrawDeviceNum
指定显示设备的设备号，如果是0，则表示主显示设备。
返回值：指定显示设备的系统信息	*/	
int PLAY_DLL_EXPORT SnPlay_GetCapsEx(DWORD nDDrawDeviceNum);

/*函 数：抓图回调SnPlay_SetDisplayCallBack
参 数：LONG nPort void (CALLBACK* DisplayCBFun); DisplayCBFun抓图回调函数参数说明 nPort pBuf nSize nWidth nHeigh nStamp nType nReceaved
播放通道号 抓图回调函数，可以为NULL 通道号 返回图像数据 返回图像数据大小 画面宽，单位像素 画面高 时标信息，单位毫秒 数据类型， T_YV12，T_RGB32，T_UYVY， 详见SnPlay_SetDecCallBack宏定义 保留
返回值：成功返回TURE；失败返回FALSE	
说 明：设置抓图回调函数；注意要尽快返回，如果要停止回调，可以把回调函数指针DisplayCBFun设为NULL。一旦设置回调函数，则一直有效，直到程序退出。该函数可以在任何时候调用 回调在时钟线程中触发, 不能出现耗时操作, 否则会打乱时钟脉冲, 影响显示*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun) (long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp, long nType,long nReceaved));

/*函 数：图像数据转为BMP格式 SnPlay_ConvertToBmpFile
参 数：char * pBuf long nSize long nWidth long nHeight long nType char *sFileName
抓图回调函数中图像缓冲区 抓图回调函数中图像的大小 抓图回调函数中图像宽度 抓图回调函数中图像高度 抓图回调函数中图像类型 要保存的文件名。最好以BMP作为文件扩展名
返回值：成功返回TURE；失败返回FALSE
说 明：将抓图得到的图像数据保存成BMP文件。转换函数占用的cpu资源，如果不需要保存图片，则不要调用*/		
BOOL PLAY_DLL_EXPORT SnPlay_ConvertToBmpFile (char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);

/*函 数：图像数据转为JPEG 格式SnPlay_ConvertToJpegFile
参 数：char *pBuf long nSize long nWidth long nHeight long nType char *sFileName
图像数据缓存 图像大小 图像宽度 图像高度 图像类型（yv12） 保存路径
返回值：成功返回TURE；失败返回FALSE
说 明：抓图存为JPEG文件, 该函数可在显示回调函数中使用, 用法参见SnPlay_ConvertToBmpFile	*/	
BOOL PLAY_DLL_EXPORT SnPlay_ConvertToJpegFile(char *pBuf, long nSize, long nWidth, long nHeight, long nType, char *sFileName);

/*函 数：直接抓取BMP图像SnPlay_GetBMP
参 数：LONG nPort PBYTE pBitmap 播放通道号
DWORD nBufSize DWORD* pBmpSize
大小， 即sizeof(BITMAPFILEHEADER); + sizeof(BITMAPINFOHEADER); + w * h * 4， 其中w和h分别为图像宽高。 申请的缓冲区大小 获取到的实际bmp图像大小
返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_GetBMP(LONG nPort,PBYTE pBitmap,DWORD nBufSize, DWORD* pBmpSize);

/*函 数：直接抓取JPEG图像SnPlay_GetJPEG
参 数：LONG nPort PBYTE pJpeg DWORD nBufSize DWORD* pJpegSize
播放通道号 存放JEPG图像数据地址，由用户分配，不得小于JPEG图像大小，建议大小w * h * 3/2， 其中w和h分别为图像宽高。 申请的缓冲区大小 获取到的实际JPEG图像数据大小
返回值：成功返回TURE；失败返回FALSE	*/	
BOOL PLAY_DLL_EXPORT SnPlay_GetJPEG(LONG nPort,PBYTE pJpeg,DWORD nBufSize, DWORD* pJpegSize);

/*函 数：设置JPEG图像质量SnPlay_SetJpegQuality
参 数：long nQuality
图像质量参数，范围0~100 0: 图像质量最差, 但抓取的图像大小最小 100: 图像质量最好, 但抓取的图像大小最大
返回值：成功返回TURE；失败返回FALSE
说 明：设置抓取的jpeg图像质量, 设置范围0~100, 建议使用75~90, 若不调用该函数, 则采用默认图像质量, 目前默认为80。需要在抓图进行前调用，建议在openfile之前使用*/
BOOL PLAY_DLL_EXPORT SnPlay_SetJpegQuality(long nQuality);

/*函 数：画图回调SnPlay_RegisterDrawFun
参 数：LONG nPort void (CALLBACK* DrawFun);播放通道号 画图回调函数	
LONG nUser DrawFun 回调函数参数说明 long nPort HDC hDc LONG nUser
用户数据 播放通道号 表面设备上下文，可以像操作显示窗口客户区DC那样操作它。 用户数据，就是上面输入的用户数据；
返回值：成功返回TURE；失败返回FALSE
说 明：注册一个回调函数，获得当前表面的device context, 你可以在这个DC上画图（或写字），就好像在窗口的客户区DC上绘图，但这个DC不是窗口客户区的DC，而是DirectDraw里的Off-Screen表面的DC。注意，如果是使用overlay表面，这个接口无效，你可以直接在窗口上绘图，只要不是透明色就不会被覆盖。 回调在时钟线程中触发, 不能出现耗时操作, 否则会打乱时钟脉冲, 影响显示*/
BOOL PLAY_DLL_EXPORT SnPlay_RegisterDrawFun(LONG nPort, void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);

/* 函数说明: 设置数据校验SnPlay_SetVerifyCallBack *
/* 参 数：LONG nPort 播放通道号
/* DWORD nBeginTime  校验开始时间，单位ms
/* DWORD nEndTime  校验结束时间，单位ms
/* void (__stdcall* funVerify); 当发现数据被修改时回调的函数
/* DWORD nUser 用户数据 
/* funVerify 回调函数参数说明: 
/* long nPort  播放通道号
/* SNEX_FRAME_POS * pFilePos  出错信息
/* DWORD bIsVideo 是否视频数据，1视频，0音频
/* DWORD nUser 用户数据
/* SNEX_FRAME_POS类型定义: 
/* long nFilePos  出错的文件位置
/* long nFrameNum  出错后正常的帧号
/* long nFrameTime  出错后正常的时间（相对此文件开始时间）
/* long nErrorFrameNum  出错时的帧号
/* SYSTEMTIME *pErrorTime  出错的绝对时间（设备录象文件有用）
/* long nErrorLostFrameNum 出错时丢失的帧数
/* long nErrorFrameSize 出错时错误的数据大小               
/* 返回值：成功返回TURE；失败返回FALSE
/* 说 明：注册一个回调函数，校验数据是否被修改，实现水印功能。现在可以发现数据丢失情况。注意，该校验在建立文件索引的时候进行，所以必须建文件索引才能校验。在openfile之前使用。*/
BOOL PLAY_DLL_EXPORT SnPlay_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (__stdcall* funVerify)(long nPort, SNEX_FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser), DWORD nUser);
		
			
/* 函数说明: 获取原始帧数据回调函数SnPlay_GetOriginalFrameCallBack *
/* 参 数：LONG nPort 播放通道号
/* BOOL bIsChange  是否要改变每帧的参数
/* BOOL bNormalSpeed  是否要以正常速度得到原始帧
/* long nStartFrameNum  如果要改变原始帧帧号，则是此文件的开始帧号 
/* long nStartStamp  如果要改变原始帧时标，则是此文件的开始时标
/* [out]long nFileHeader 文件头版本信息，如果版本不匹配，返回不成功
/* void(CALLBACK *funGetOrignalFrame); 原始帧回调函数
/* long nUser 用户数据
/* funGetOrignalFrame 回调函数参数: 
/* long nPort 播放通道号
/* SNEX_FRAME_TYPE *frameType 数据帧信息
/* long nUser  用户数据
/* SNEX_FRAME_TYPE类型说明 
/* typedef struct{ char *pDataBuf  数据帧首地址
/* long nSize  数据帧的大小
/* long nFrameNum  数据帧的个数
/* BOOL bIsAudio  是否音频帧
/* long nReserved 保留 } SNEX_FRAME_TYPE;        
/* 返回值：成功返回TURE；失败返回FALSE
/* 说 明：创建得到原始数据的回调函数，可以改变每帧的时标和帧号，在文件打开之后调用，用于将两个文件拼接在一起*/	
BOOL PLAY_DLL_EXPORT SnPlay_GetOriginalFrameCallBack(LONG nPort, BOOL bIsChange, BOOL bNormalSpeed, long nStartFrameNum, long nStartStamp, long nFileHeader, void(CALLBACK *funGetOrignalFrame) (long nPort,SNEX_FRAME_TYPE *frameType, long nUser), long nUser);
		 
/* 函数说明: 获取文件最后的时标和帧号SnPlay_GetFileSpecialAttr *
/* 参 数：LONG nPort 播放通道号 
/* [out]DWORD *pTimeStamp 文件结束时标
/* [out]DWORD *pFileNum 文件结束帧号
/* [out]DWORD *nFileHeader 文件头信息	 
/* 返回值：成功返回TURE；失败返回FALSE
/* 说 明：得到文件最后的时标和帧号，在文件打开之后调用。与上个文件一起使用，用于文件拼接*/
BOOL PLAY_DLL_EXPORT SnPlay_GetFileSpecialAttr(LONG nPort, DWORD *pTimeStamp,DWORD *pFileNum ,DWORD *nFileHeader);;
 
/* 函数说明：码流错误直接跳至下一关键帧SnPlay_PlaySkipErrorData
/* 参 数：LONG nport 播放通道号, BOOL bSkip TRUE 码流错误时会直接跳下一个关键帧解码； FALSE 寻找下一帧数据解码	 
/* 返回值：成功返回TURE；失败返回FALSE
/* 说 明：如果在码流有错误的情况下，不允许出现花屏，建议可以设置成TRUE*/
BOOL PLAY_DLL_EXPORT SnPlay_PlaySkipErrorData(LONG nport, BOOL bSkip);

/* 函数说明：检查帧号连续性SnPlay_CheckDiscontinueFrameNum
/* 参 数：LONG nport 播放通道号, BOOL bCheck TRUE 检查码流帧号连续性；FALSE 不检查码流帧号连续性	 
/* 返回值：成功返回TURE；失败返回FALSE
/* 说 明：在码流不连续的情况下，设置检查后，会跳下一个关键帧解码*/
BOOL PLAY_DLL_EXPORT SnPlay_CheckDiscontinueFrameNum(LONG nport, BOOL bCheck);

/*函数说明：获取录像文件长度
/*参数: long lPort  = player session
/*返回值：返回录像文件大小*/
unsigned long PLAY_DLL_EXPORT SnPlay_GetRecordSize(long lPort);

/*函数说明：开始录像
/*参数: long lPort  = player session
/*            char * filename= name of record file*/
BOOL PLAY_DLL_EXPORT SnPlay_StartRecord(long lPort,char * filename);

/*函数说明：停止录像
/*参数: long lPort  = player session*/
BOOL PLAY_DLL_EXPORT SnPlay_StopRecord(long lPort);


//*****************************************************************************
//暂时没有实现函数
//*****************************************************************************

/*函数说明： 测试播放所需系统功能SnPlay_GetCaps
/*参 数：无
/*返回值：1~8位分别表示以下信息（位与是TRUE表示支持）：
/*SUPPORT_DDRAW SUPPORT_BLT SUPPORT_BLTFOURCC SUPPORT_BLTSHRINKX SUPPORT_BLTSHRINKY SUPPORT_BLTSTRETCHX SUPPORT_BLTSTRETCHY SUPPORT_SSE SUPPORT_MMX
/*支持DIRECTDRAW；如果不支持，则播放器不能工作显卡支持BLT操作；如果不支持，则播放器不能工作显卡BLT支持颜色转换；如果不支持，播放器会使用软件方式作RGB转换显卡BLT支持X轴缩小；如果不支持，系统使用软件方式转换显卡BLT支持Y轴缩小；如果不支持，系统使用软件方式转换显卡BLT支持X轴放大；如果不支持，系统使用软件方式转换显卡BLT支持Y轴放大；如果不支持，系统使用软件方式转换CPU支持SSE指令,Intel Pentium3以上支持SSE指令CPU支持MMX指令集
/*说 明：测试播放器需要的一些系统功能*/
int PLAY_DLL_EXPORT SnPlay_GetCaps();


/*函数说明： 获取错误号SnPlay_GetLastError
/*参 数：LONG nPort 播放通道号
/*返回值：错误码，详见错误码宏定义
/*说 明：获得当前错误的错误码。用户在调用某个函数返回失败时，调用此函数获得错误的详细信息*/
DWORD PLAY_DLL_EXPORT SnPlay_GetLastError(LONG nPort);


/*函数说明：初始化Direct表面SnPlay_InitDDraw
/*参 数：HWND hWnd 应用程序主窗口的句柄
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：在使用vb,delphi开发时请注意，它们生成的对话框具有WS_CLIPCHILDREN窗口风格，必须去掉这种风格，否则显示画面会被对话框上的控件覆盖*/
BOOL PLAY_DLL_EXPORT SnPlay_InitDDraw(HWND hWnd);


/*函数说明：释放Direct表面SnPlay_RealeseDDraw
/*参 数：无
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_RealeseDDraw();

/*函数说明： 设置播放使用的定时器类型SnPlay_SetTimerType
/*参 数：LONG nPort  播放通道号
/*参 数：DWORD nTimerType TIMER_1 是多媒体时钟 一个进程中只能使用16个，时间精度高；TIMER_2 是等待计时器，使用数目没有限制，但时间精度较低，不推荐在高倍速播放时使用。默认情况下0~15路使用TIMER_1，其余使用TIMER_2； 
/*参 数：DWORD nReserved 保留参数
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);

/*函数说明：获取播放使用的定时器类型SnPlay_GetTimerType
/*参 数：LONG nPort 播放通道号
/*参数：[out]DWORD *pTimerType TIMER_1或TIMER_2
/*参数：DWORD *pReserved 保留参数
/*返回值：成功返回TURE；失败返回FALSE*/
BOOL PLAY_DLL_EXPORT SnPlay_GetTimerType(LONG nPort,DWORD *pTimerType, DWORD *pReserved);


/*函数说明：单帧回退SnPlay_OneByOneBack
/*参 数：LONG nPort 播放通道号
/*返回值：成功返回TURE；失败返回FALSE
/*说 明：每调用一次倒退一帧*/
BOOL PLAY_DLL_EXPORT SnPlay_OneByOneBack(LONG nPort);



/*函 数：去闪烁SnPlay_SetDeflash
参 数：
LONG nPort BOOL bDeflash
播放通道号 TRUE表示设置去闪烁，FALSE表示不设置，默认为不设置
返回值：成功返回TURE；失败返回FALSE
说 明：设置是否去闪烁功能, 原先在静止图像区域有噪声情况下, 图像会产生闪烁现象（或称刷新或跳动），启动去闪烁功能后，闪烁效果可消除或减轻，同时也能降低噪声*/
BOOL PLAY_DLL_EXPORT SnPlay_SetDeflash(LONG nPort,BOOL bDeflash);


/*函 数：获取当前是否采用OVERLAY显示模式SnPlay_GetOverlayMode
参 数：LONG nPort 播放通道号
返回值：0表示没有使用OVERLAY；1表示使用了OVERLAY表面；-1表示调用失败
说 明：检查当前播放器是否使用了OVERLAY模式	*/	
LONG PLAY_DLL_EXPORT SnPlay_GetOverlayMode(LONG nPort);


//************************************
// Method:    设置异常消息回调,主要通知播放时的异常信息
// FullName:  SnPlay_SetDecMsgCallBack

// Returns:   BOOL PLAY_DLL_EXPORT
// Parameter: long lPort	 =player session
// Parameter: CALLBACK * ExceptionMsgFun
// Parameter: long lPort	 =player session
// Parameter: int nFlag		 =异常类型，1表示录像异常
// Parameter: void * pUserData  =上下文数据
// Parameter: void * pUserData	=上下文数据
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetExceptionFilter(void (CALLBACK* ExceptionMsgFun)(long lPort, int nFlag , void *pUserData),long lPort,void *pUserData);


/*函 数：在图像上绘制矩形
参 数：LONG nPort 播放通道号
参 数：int ix,int iy, 左上角坐标
参 数：LONG lWidth,LONG lHeight， 矩形宽高
参 数：unsigned char RColor,unsigned char GColor,unsigned char BColor，线条颜色
返回值：TRUE表示成功；FALSE表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetRectangle(LONG nPort,int ix,int iy,LONG lWidth,LONG lHeight,unsigned char RColor,unsigned char GColor,unsigned char BColor,int index);

/*函 数：去除已绘矩形
参 数：LONG nPort 播放通道号
参 数：int index, 矩形框索引
返回值：TRUE表示成功；FALSE表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_RemoveRectangle(LONG nPort,int index);

/*函 数：获取当前已播放大小
参 数：LONG nPort 播放通道号
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
LONG PLAY_DLL_EXPORT SnPlay_GetPlaySize(LONG nPort);

/*函 数：获取当前水印信息
参 数：LONG nPort 播放通道号
	   char *cWaterMask 已解码后的水印
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_GetWaterMask(LONG nPort,char *cWaterMask);

/*函 数：设置水印信息回调
参 数：LONG nPort 播放通道号
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetWaterMaskCB(LONG nPort,void (CALLBACK* WaterMaskMsgFun)(char *WaterMask,void *pUserData),void *pUserData);

/*函 数：设置图像分辨率改变通知
参 数：LONG nPort 播放通道号
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_SetResNotifyCB(LONG nPort,void (CALLBACK* ResNotifyMsgFun)(int iWidth,int iHeight,void *pUserData),void *pUserData);

/*函 数：获取YUV数据
参 数：LONG nPort 播放通道号
参 数：unsigned char *pYUV(out) 图像yuv数据
参 数：int nWidth(in) 图像分辨率宽
参 数：int nHeight(in) 图像分辨率高
返回值：>0表示当前已播放大小；-1表示失败
说明：yuv申请内存大小=宽*高*3/2,yuv格式为yuv420*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_GetYUVData(LONG nPort,unsigned char *pYUV,int nWidth,int nHeight);

/*函 数：绘制yuv
参 数：LONG nPort 播放通道号
参 数：unsigned char *pYUV(in) 图像yuv数据
参 数：int nWidth(in) 图像分辨率宽
参 数：int nHeight(in) 图像分辨率高
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_DrawYUV(LONG nPort,unsigned char *pYUV,int nWidth,int nHeight);

/*函 数：停止绘制yuv
参 数：LONG nPort 播放通道号
参 数：unsigned char *pYUV(in) 图像yuv数据
参 数：int nWidth(in) 图像分辨率宽
参 数：int nHeight(in) 图像分辨率高
返回值：>0表示当前已播放大小；-1表示失败*/
//************************************
BOOL PLAY_DLL_EXPORT SnPlay_StopDrawYUV(LONG nPort);


#endif
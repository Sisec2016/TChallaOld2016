#ifndef _WP_DECODE_SDK_H_
#define _WP_DECODE_SDK_H_

#define DLL_EXPORT extern "C" _declspec(dllexport)

#define MAX_DECODE 0x0100

typedef enum{
	MPEG4 = 0,
	H264 = 264,
}ENCODE_TYPE;

#define WP_DECODE_NOERROR			0x012c		//没有错误
#define WP_DECODE_INITVIDEO_FAILED	0x012d		//初始化视频解码器失败
#define WP_DECODE_VIDEODEC_NOT_EXIST 0x012e		//视频解码器不存在
#define WP_DECODE_VIDEODEC_MAX			  0x012f	//创建视频解码器的个数已达到最大值
#define WP_DECODE_VIDEODEC_INVALID_INDEX	0x0130	//视频解码器的索引号非法
#define WP_DECODE_VIDEOBUF_NULL				0x0131	//未解码的视频数据为空
#define WP_DECODE_AUDIODEC_EXIST			0x0132	//音频解码器已经存在了
#define WP_DECODE_AUDIOBUF_NULL				0x0133	//未解码的音频数据为空
#define WP_DECODE_AUDIODEC_NOT_EXIST		0x0134	//音频解码器不存在
#define WP_DECODE_INIT_FAILED				0x0135	//初始化解码器的SDK失败
#define WP_DECODE_VIDEO_PARAM_INVALID       0x0136  //视频的参数非法

//****************************************************************
//Function:	int WP_DECODE_InitSdk()
//Description:初始化解码器的SDK
//return: 成功则WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_InitSdk();

//****************************************************************
//Function:	int WP_DECODE_CleanupSdk()
//Description:释放解码器的SDK
//return: 成功则WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_CleanupSdk();

//****************************************************************
//Function:	int WP_DECODE_InitVideoDec(int width, int height, int encodeFormat)
//Description:创建视频解码器
//Input: width 解码器的宽
//Input: height 解码器的高
//Input: encodeFormat 解码器的编码方式，参见ENCODE_TYPE
//return: 成功则返回解码器的索引号，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_InitVideoDec(int width, int height, int encodeFormat);								

//****************************************************************
//Function:	int WP_DECODE_DecVideo(int decodeIndex, unsigned char *istream, int istream_size, unsigned char *ostream)
//Description:解码视频数据
//Input: decodeIndex 解码器的索引号
//Input: istream 未解码的视频数据
//Input: istream_size 未解码的视频数据的长度
//Output: ostream 解码后的视频数据
//return: 成功则返回WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_DecVideo(int decodeIndex, unsigned char *istream, int istream_size, unsigned char *ostream);								

//****************************************************************
//Function:	int WP_DECODE_DestroyVideoDec(int decodeIndex)
//Description:销毁视频解码器
//Input: decodeIndex 解码器的索引号
//return: 成功则返回WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_DestroyVideoDec(int decodeIndex);

//****************************************************************
//Function:	int WP_DECODE_InitAudioDec()
//Description:创建音频解码器
//return: 成功则返回WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_InitAudioDec();

//****************************************************************
//Function:	int WP_DECODE_DecAudio(unsigned char *istream, int istream_size, unsigned char *ostream)
//Description:解码音频数据
//Input: istream 未解码的音频数据
//Input: istream_size 未解码的音频数据的长度
//Output: ostream 解码后的音频数据
//return: 成功则返回WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************																		
DLL_EXPORT int WP_DECODE_DecAudio(unsigned char *istream, int istream_size, unsigned char *ostream);	
		
//****************************************************************
//Function:	int WP_DECODE_DestroyAudioDec()
//Description:销毁音频解码器
//return: 成功则返回WP_DECODE_NOERROR，失败则返回错误信息
//****************************************************************
DLL_EXPORT int WP_DECODE_DestroyAudioDec();																		

#endif
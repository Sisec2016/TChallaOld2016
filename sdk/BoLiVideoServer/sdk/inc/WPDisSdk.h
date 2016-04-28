#ifndef _WP_DISPLAY_SDK_H_
#define _WP_DISPLAY_SDK_H_

#define DLL_EXPORT extern "C" _declspec(dllexport)

#define MAX_DEVICE			128

#define WP_DISPLAY_NOERROR		0x00c8		//没有错误
#define WP_DISPLAY_INITD3D_FAILED	0x00c9		//创建d3d设备失败
#define WP_DISPLAY_INITDIRECTDRAW_FAILED 0x00ca //创建directdraw设备失败
#define WP_DISPLAY_DEVICE_MAX	0x00cb//创建显示设备的个数已达到最大
#define WP_DISPLAY_D3DDEVICE_NOT_EXIST	0x00cc//该索引号的D3d显示对象不存在          204
#define WP_DISPLAY_DIRECTDRAW_NOT_EXIST	0x00cd//该索引号的directdraw显示对象不存在
#define WP_DISPLAY_DEVICE_INVALID_INDEX 0x00ce//显示设备的索引号非法
#define WP_DISPLAY_DATA_NULL	0x00cf//显示的数据为空
#define WP_DISPLAY_D3DDEVICE_HAS_EXIST 0x00d0 //该索引号的D3D设备已经创建了
#define WP_DISPLAY_PARAM_INVALID	0x00d1	//显示的参数非法
#define WP_DISPLAY_CREATESURFACE_FAIL	0x00d2	//创建显示区失败

#define WP_CAPTURE_NOERROR				600		//没有错误
#define WP_CAPTURE_BUF_NULL				601		//数据缓存为空	
#define WP_CAPTURE_PATH_NULL			602		//文件的路径为空
#define WP_CAPTURE_CREAT_FILE_FAILED	603		//创建文件失败



//数据的格式
#define DATA_FORMAT_YUYV				1		//YUYV格式的数据
#define DATA_FORMAT_RGB24				2		//RGB24格式的数据

//抓图是否叠加时间标签
typedef enum{
	PIC_ADD_TIME = 1001,
	PIC_NO_TIME = 1002,
}PicTimeLabel;

//for display
DLL_EXPORT int WP_DISPLAY_InitSdk();
DLL_EXPORT int WP_DISPLAY_CleanupSdk();
DLL_EXPORT int WP_DISPLAY_InitDevice(HWND hWnd);	
DLL_EXPORT int WP_DISPLAY_ReleaseDevice(int hWndId);																
DLL_EXPORT int WP_DISPLAY_CreateOneSurface(int hWndId, int width, int height);	//							
DLL_EXPORT int WP_DISPLAY_FreeOneSurface(int hWndId);														
DLL_EXPORT int WP_DISPLAY_DisplayFrame(int hWndId, BYTE *pVData);											
DLL_EXPORT int WP_DISPLAY_SetShowText(int hWndId, char *text);

//DLL_EXPORT int WP_DISPLAY_SetShowMode(int hWndId, int showMode);											//Set the show mode, the max channels count is showMode*showMode.

//for listen play audio
DLL_EXPORT int WP_DISPLAY_PlayAudio(unsigned char *ostream);														//Play the audio data.

//for capture picture
DLL_EXPORT int WP_DISPLAY_CaptureJPG(unsigned char *pImageBuf, int width, int height, int dataFormat, char *fileName, char *pImagePath);     //Save the decoded data to jpg image.
                                                                                                                          //pImageBuf: the decoded data
                                                                                                                          //width:     the width of the image
                                                                                                                          //height:    the height of the image
                                                                                                                          //dataFormat:the format of the decoded data( DATA_FORMAT_YUYV / DATA_FORMAT_RGB24 )
                                                                                                                          //fileName:  the path and filename of the file
DLL_EXPORT int  WP_DISPLAY_CaptureBMP(unsigned char *pImageBuf, int width, int height, int dataFormat, char *fileName, char *pImagePath, PicTimeLabel label);    //Save the decoded data to bmp image
                                                                                                                          //label:     whether add the time to the picture.

#endif
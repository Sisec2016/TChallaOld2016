// VirDisk_SageAPI.h : VirDisk_SageAPI DLL 的主头文件
//

#ifndef __VIR_DISK_API_H__
#define __VIR_DISK_API_H__


#ifdef _Sage_USB_API_DLL
#define SAGE_API extern "C" _declspec(dllexport)
#else
#define SAGE_API extern "C" _declspec(dllimport)
#endif

#define MAX_VIRDISK_NUM	11
#define EXIST_MARK	0XF5

#define FILESYS_NONE				0
#define FILESYS_FAT					1
#define FILESYS_NTFS					2

//UnMount操作
#define ERR_FILES_OPEN		6
#define TC_IOCTL(CODE) (CTL_CODE (FILE_DEVICE_UNKNOWN, 0x800 + (CODE), METHOD_BUFFERED, FILE_ANY_ACCESS))
#define TC_IOCTL_DISMOUNT_VOLUME						TC_IOCTL (4)
#define TC_IOCTL_DISMOUNT_ALL_VOLUMES					TC_IOCTL (5)
#define TC_IOCTL_GET_MOUNTED_VOLUMES				TC_IOCTL	(6)
#define TC_IOCTL_GET_DRIVER_VERSION											TC_IOCTL(1)
#define TC_IOCTL_LEGACY_GET_DRIVER_VERSION 							466968
#define WIN32_ROOT_PREFIX "\\\\.\\SageDisks"	

#define SSDDEVICE_INFO_LEN					64
typedef struct _SSDDeviceInfo
{
	UINT8 m_szPsn[32] ;							//PSN码
	UINT8 m_szDeviceName[20] ;				//SSD物理盘名称
	UINT32 m_nVolumeNum ;				//分区个数
	UINT8 m_chDiskLetter[8] ;							//分区盘符
}SSDDeviceInfo;

#define MAX_SAGE_SSD_COUNT 10
typedef struct _CurrentSSDDevInfo
{
	SSDDeviceInfo m_ssdDeviceList[ MAX_SAGE_SSD_COUNT ] ;
	UINT8 m_nSSDDevNum ;
	UINT8 m_Rev[3] ;
}CurrentSSDDevInfo;

#define SAFEDISK_INFO_LEN_SECTORS		2
typedef struct _SafeDiskInfo
{
	UINT8 m_szVersion[32] ;					//当前版本号
	UINT32 m_nPCNumber;					//当前已使用PC数量
	UINT8 m_nBlockIndex[400];				//隐藏区索引
	UINT32 m_nLimitPCNumber;			//限制数目
	UINT8 m_szPasswd[32] ;					//密码
	UINT8 m_szKey[32] ;							//镜像密钥
	UINT32 m_nCurIndex;						//当前PC索引号 
	UINT8 m_szPSN[32] ;						//当前设备PSN
	UINT32 m_nPromptMark ;					//如果用户自己设置了密码提示，标记为0xf5 否则为软件中的问题代号
	UINT8 m_szLoginQuestion[32] ;		//密码提示信息
	UINT8 m_szUserAnswer[32] ;			//用户答案
	UINT8 m_isLogin ;							//登陆状态
	UINT8 m_nRvs[415];							//保留
}SafeDiskInfo;

#define VIR_DISK_INFO_LEN 160
#define VDISK_NAME_LEN		64		//安全区名称长度
//安全区信息
typedef struct _VirDiskInfo
{
	UINT8 m_IsExist;				//存在标记									
	UINT8 m_nIsMount;			//挂载标记
	UINT8 m_chDiskLetter;		//挂载盘符
	UINT8 m_Rev ;					//保留位
	UINT8 m_chFilePath[VDISK_NAME_LEN];		//镜像路径
	UINT8 m_chDiskName[VDISK_NAME_LEN];	//挂载磁盘券名
	UINT64 m_nDiskCap;									//安全区容量
	UINT8 m_nRev[16];										//保留位
}VirDiskInfo;

#define SECURITY_DISK_INFO_LEN_SECTOR			4				
//数据宝信息
typedef struct _SecurityDiskInfo
{
	UINT32 m_nVirDiskCnt;										//安全区个数
	VirDiskInfo m_VirDiskInfo[MAX_VIRDISK_NUM];	//安全区信息
	UINT32 m_nCurIndex ;										//在当前PC上的配置位置编号
	UINT8 m_szPSN[32] ;											//当前设备PSN号
	UINT8 m_CheckBit ;											//数据完整性标记位
	UINT8 m_Rev[236] ;											//保留位
}SecurityDiskInfo;

//UnMount结构体
typedef struct
{
	int nDosDriveNo;	/* Drive letter to unmount */
	BOOL ignoreOpenFiles;
	BOOL HiddenVolumeProtectionTriggered;
	int nReturnCode;	/* Return code back from driver */
} UNMOUNT_STRUCT;

typedef struct
{
	unsigned __int32 ulMountedDrives;	/* Bitfield of all mounted drive letters */
	wchar_t wszVolume[26][MAX_PATH];	/* Volume names of mounted volumes */
	unsigned __int64 diskLength[26];
	int ea[26];
	int volumeType[26];	/* Volume type (e.g. PROP_VOL_TYPE_OUTER, PROP_VOL_TYPE_OUTER_VOL_WRITE_PREVENTED, etc.) */
} MOUNT_LIST_STRUCT;


//	安全区操作码
#define DEVICE_BASE_NAME    _T("\\FileDisk")
#define DEVICE_DIR_NAME     _T("\\Device")      DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX  DEVICE_DIR_NAME     DEVICE_BASE_NAME

#define FILE_DEVICE_FILE_DISK       0x8000
#define IOCTL_FILE_DISK_OPEN_FILE   CTL_CODE(FILE_DEVICE_FILE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE  CTL_CODE(FILE_DEVICE_FILE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_QUERY_FILE  CTL_CODE(FILE_DEVICE_FILE_DISK, 0x802, METHOD_BUFFERED, FILE_READ_ACCESS)

#define IOCTL_FILE_DISK_GET_DISK_VERSION	CTL_CODE(FILE_DEVICE_FILE_DISK, 0x805, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)


#define SAGE_VERSION	"SageVirDisk"
#define TC_MOUNT_PREFIX "\\Device\\SageDisksVolume"

/************************************************************************/
/* 检测加载驱动，存在则检测是否正常，不存在则安装
* 输入参数:
*		szDriverPath: 驱动路径
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API int __stdcall MyDriverAttachW_SageAPI( WCHAR *szDriverPath );

/************************************************************************/
/* 从aStartLetter之后获取有效的未被占用的盘符
* 输入参数:
*		aStartLetter: 起始盘符
*输出参数：
*		aVailLetter: 返回的可用盘符
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
UINT32 __stdcall GetVailLunA_SageAPI( CHAR* aVailLetter , CHAR  aStartLetter = 'D' );

/************************************************************************/
/*  卸载安全区  
* 输入参数:
*		iDriverNo: 安全区序号（例：A盘 对应 0 ， C盘 对应 2）
*		bForceUnmount: 强制卸载，不管当前磁盘是否有文件被占用
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API BOOL __stdcall UnMountVolume(int iDriverNo,BOOL bForceUnmount = TRUE);

/************************************************************************/
/* 卸载所有安全区
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall UnMountAllVolume();

/************************************************************************/
/* 获取所有未卸载安全区
*输入参数：
		unMountList：安全区挂载信息结构体
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API BOOL __stdcall GetUnMountAllVolumeList( MOUNT_LIST_STRUCT * unMountList);


/************************************************************************/
/*  获取SAGE SSD信息
* 参数:
*		_In szDeviceName : SSD物理设备名称，
*		_Out ssdDevInfo：当前SSD上的澜盾软件信息
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall GetSafeDiskInfoFromDeviceA_SageAPI( CHAR *szDeviceName ,SafeDiskInfo *ssdDevInfo) ;

/************************************************************************/
/*  设置SSD设备的信息，即把信息写回SSD设备  
* 参数:
*		_In szDeviceName : SSD物理设备名称，
*		_In ssdDevInfo：当前SSD上的澜盾软件信息
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall SetSafeDiskInfoA_SageAPI( CHAR *szDeviceName ,SafeDiskInfo *ssdDevInfo ) ;

/************************************************************************/
/*  从设备中获取安全区配置信息  
* 参数:
*		_In szDeviceName : SSD物理设备名称，
*		_In aStartIndex：PC在当前SSD上的配置信息索引位置
*		_In aSectsToWrite：配置信息占用空间大小
*		_Out secDiskInfo：配置信息
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall GetSecurityDiskInfoFromDeviceA_SageAPI( CHAR *szDeviceName , DWORD aStartIndex, DWORD aSectsToRead, SecurityDiskInfo * secDiskInfo ) ;

/************************************************************************/
/*  设置隐藏区配置数据  
* 参数:
*		_In szDeviceName : SSD物理设备名称，
*		_In aStartIndex：PC在当前SSD上的配置信息索引位置
*		_In aSectsToWrite：配置信息占用空间大小
*		_In secDiskInfo：配置信息
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall SetSecurityDiskInfoA_SageAPI( CHAR *szDeviceName , DWORD aStartIndex, DWORD aSectsToWrite, SecurityDiskInfo * secDiskInfo ) ;


/************************************************************************/
/*  查找镜像文件所在分区  
* 参数:
*		_In_Out szFileName : 镜像路径名称，
*		_In_Out chLetter：镜像所在盘符
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API BOOL __stdcall  isSafeAreaImgFileExistA_SageAPI( char *szFileName ,  CHAR &chLetter ) ;

typedef struct _CREATE_SECURITY_DISK_PARAM
{
	HWND hwnd;												//接收创建结果的窗口句柄
	INT iDriverNo;											//安全区挂载盘符序号
	UINT64 nDiskCapacity;								//安全区容量
	WCHAR wDiskImageFilePath[VDISK_NAME_LEN] ;	//安全区镜像文件路径
	INT nDiskSysType;										//安全区文件系统类型
	BOOL bQuickFormate ;								//安全区是否执行快速格式化
	BYTE szKey[32];												//安全区创建密钥
	UINT32 nKeyLength;									//密钥长度
}CreateSecurityDiskParam;

/************************************************************************/
/*  创建安全区进程调用接口
* 参数:
*		_In wCreateFilePath : 安全区创建进程路径
*		_In aCreateParam：安全区创建参数
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API BOOL __stdcall  CreateSecurityDiskW_SageAPI( const WCHAR *wCreateFilePath , const CreateSecurityDiskParam aCreateParam ) ;

typedef struct _MOUNT_SECURITY_DISK_PARAM
{
	HWND hwnd;												//接受挂载结果的窗口句柄
	WCHAR wDiskImageFilePath[VDISK_NAME_LEN] ;	//安全区镜像文件路径
	BYTE szKey[32];												//安全区创建密钥
	UINT32 nKeyLength;									//密钥长度
}MountSecurityDiskParam;

/************************************************************************/
/*  挂载安全区进程调用接口
* 参数:
*		_In wCreateFilePath : 安全区创建进程路径
*		_In aMountParam：安全区创建参数
*		_Out chMountLetter : 安全区挂载盘符
*		_In chMaxLetter : 当前安全区配置中最大已使用的盘符
* 返回值：
*	 	0--成功；非0--失败 
/************************************************************************/
SAGE_API UINT32 __stdcall MountSecurityDiskW_SageAPI( const WCHAR *wMountFilePath , const MountSecurityDiskParam aMountParam , WCHAR &chMountLetter , WCHAR chMaxLetter = L'D' ) ;

/************************************************************************/
/*  验证登陆密码
* 参数:
*		_In cDeviceName : SSD盘符名称
*		_In cPassword：登陆输入的密码
* 返回值：
*	 	1--成功；0--失败 
/************************************************************************/
SAGE_API BOOL __stdcall VerifyLoginPasswordA_SageAPI(CHAR* cDeviceName,CHAR* cPassword);
/************************************************************************/
/*  修改登录密码
* 参数:
*		_In cDeviceName : SSD盘符名称
*		_In cNewPassword：新的登陆密码
* 返回值：
*	 	0--成功；非0--失败  
/************************************************************************/
SAGE_API UINT32 __stdcall ModifyLoginPasswordA_SageAPI(CHAR* cDeviceName,CHAR* cNewPassword);
#endif //__VIR_DISK_API_H__
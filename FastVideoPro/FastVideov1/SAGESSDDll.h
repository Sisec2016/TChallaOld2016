#ifndef SAGESSD_H
#define SAGESSD_H
#include <windows.h>
#include <QString>
#include <string>
#include "VirDisk_SageAPI.h"

#define SAGE_API_ERR_LETTER_NO_EXIST -3
#define MESSAGE_NO_COME 0xf5
extern UINT32 g_nProcessState ;
extern HANDLE g_hEventMount ;
extern HANDLE g_hEventCreate ;

//获取系统有效盘符
void GetValidDeviceLetter( char *chDeviceLetter) ;

//获取SSD的序列号
UINT32 GetSageSSDPsn( CHAR *szDevName , CHAR szPsn[32] ) ;

//查找所有的澜盾SSD设备
UINT32 EnumSageSSDDev( CHAR szDeviceName[][32], UINT32 &nDeviceNum ) ;

//查询注册表，获取配置信息或者创建注册表信息
void GetRegeditInfo( HKEY &hKey , CHAR *szPSN , CHAR *szVersion , BOOL &bRegistered , UINT32 &nIndex ) ;

//安全区挂载线程
UINT32 StartMountProcess(const QString& strMountProcessPath , MountSecurityDiskParam aMountParam , CHAR chMaxLetter = 'D' ) ;

////////////////////////////////////////////////////////////////////////////////////

typedef int (*CheckDevice)(CHAR* DeviceName,BYTE *buf);

typedef int (*GetDiskInfo)(CHAR* DeviceName,BYTE *buf);

typedef int (*SavePartitionInfo)(CHAR* DeviceName,char* password,BYTE *buf);

typedef int (*ModifyPassword)(CHAR* DeviceName,char* sourcePassword, char* modifyPassword);

typedef int (*SwitchState)(CHAR* DeviceName,char* password,BYTE lockEnable);

typedef int (*ReadCurrentStates)(CHAR* DeviceName,BYTE* buf);

typedef int (*EraseAll)(CHAR* DeviceName);

typedef int (*Read2KRandomData)(CHAR* DeviceName,BYTE* buf);

typedef int (*SSDWriteSecurityData)(CHAR *a_deviceName,BYTE* a_buf,DWORD a_address,int a_sectors);

typedef int (*SSDReadSecurityData)(CHAR *a_deviceName,BYTE* a_buf,DWORD a_address,int a_sectors);

//2015-7-10 14:08:04 Bernard.luo Add	
typedef int (*GetReadOnlyState)(CHAR *szDeviceName , BOOL &bReadOnly );
typedef int (*EnablePartitionReadOnly)(CHAR *szDeviceName , UINT32 nLunIndex );
typedef int (*DisablePartitionReadOnly)(CHAR *szDeviceName, UINT32 nLunIndex );
typedef int (*GetHiddenCapacity)(CHAR *szDeviceName, UINT32 &nHiddenCap );

////////////////////////////////////////////////////////////////////////////////////

extern CheckDevice	checkDevice;
extern SavePartitionInfo savePartitionInfo;
extern ModifyPassword  modifyPassworda;
extern SwitchState	switchState;
extern ReadCurrentStates readCurrentStates;
extern Read2KRandomData read2KRandomData;
extern SSDWriteSecurityData writeSecurityData;
extern SSDReadSecurityData  readSecurityData;
extern EraseAll eraseAll;
extern GetDiskInfo getDiskinfo;

extern GetReadOnlyState getReadOnlyState;
extern EnablePartitionReadOnly  enablePartitionReadOnly;
extern DisablePartitionReadOnly disablePartitionReadOnly;
extern GetHiddenCapacity getHiddenCapacity;
////////////////////////////////////////////////////////////////////////////////////

extern int LoadSAGESSD_dll();
extern void FreeSAGESSD_dll();


#endif

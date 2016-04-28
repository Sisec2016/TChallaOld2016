#include "SAGESSDDll.h"
#include <windows.h>
#include <WinIoCtl.h>
#include <qdebug.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Advapi32.lib")

CheckDevice	checkDevice;
SavePartitionInfo savePartitionInfo;
ModifyPassword  modifyPassworda;
SwitchState	switchState;
ReadCurrentStates readCurrentStates;
Read2KRandomData read2KRandomData;
SSDWriteSecurityData writeSecurityData;
SSDReadSecurityData  readSecurityData;
EraseAll eraseAll;
GetDiskInfo getDiskinfo;

GetReadOnlyState getReadOnlyState;
EnablePartitionReadOnly  enablePartitionReadOnly;
DisablePartitionReadOnly disablePartitionReadOnly;
GetHiddenCapacity getHiddenCapacity;

HINSTANCE hInstLibrary = NULL;



UINT32 g_nProcessState ;
HANDLE g_hEventMount ;
HANDLE g_hEventCreate ;

//获取系统有效盘符
void GetValidDeviceLetter( char *chDeviceLetter)
{
    //取得逻辑磁盘的信息，然后判断
    std::string strDiskVolumn ;
    char  lpVolumeNameBuffer[MAX_PATH];  //硬盘卷标名称
    DWORD dwVolumeSerialNumber;      //序列号
    DWORD dwMaximumComponentLength;  //文件名最大长度
    DWORD FileSystemFlags;           //文件系统标志
    char  lpFileSystemNameBuffer[MAX_PATH];//文件系统名称

    DWORD dwDriveStrLen = 0;
    dwDriveStrLen= GetLogicalDriveStringsA(0,NULL);
    char *szDriveName = new char[dwDriveStrLen];

    char *pDriveName=NULL;
    int i = 0 ;
    if ( GetLogicalDriveStringsA( dwDriveStrLen , szDriveName ) )
    {
        pDriveName = szDriveName;
        while ( *pDriveName != NULL)
        {
            if(GetVolumeInformationA( pDriveName,
                lpVolumeNameBuffer,
                MAX_PATH ,
                &dwVolumeSerialNumber,
                &dwMaximumComponentLength,
                &FileSystemFlags,
                lpFileSystemNameBuffer,
                MAX_PATH) )
            {
                strDiskVolumn = pDriveName ;
                chDeviceLetter[i++] = strDiskVolumn.at(0) ;
            }
            pDriveName += strlen(pDriveName) + 1;
        }
    }
    delete []szDriveName ;
}

//获取SSD的序列号
UINT32 GetSageSSDPsn( CHAR *szDevName , CHAR szPsn[32] )
{
    BYTE buffer[512] ;
    CHAR temp ;
    int i , j , k ;

    memset( buffer , 0x00 , 512 ) ;
    memset( szPsn , 0x00 , 20 ) ;
    UINT32 retValue = getDiskinfo( szDevName , buffer );
    if ( 0 != retValue )
    {
        return -1 ;
    }

    for ( i = 0 ; i < 20 ; i += 2 )
    {
        temp = buffer[0x14+i];
        buffer[0x14+i] = buffer[0x14+i+1];
        buffer[0x14+i+1] = temp;
    }

    for(k =0;k<20;k++)
    {
        if (buffer[0x14+ k] != 0x20)
        {
            break;
        }
    }
    for (i = k;i < 20;i++)
    {
        for( j = 0;j < 20-i;j++)
        {
            if (buffer[0x14+i+j] != 0x20 && buffer[0x14+i+j] != 0x00)
            {
                break;
            }
        }
        if (i+j == 20)
        {
            break;
        }
        szPsn[i-k] = buffer[0x14+i];
    }
    return 0 ;
}


UINT32 EnumSageSSDDev( CHAR szDeviceName[][32], UINT32 &nDeviceNum )
{
    HANDLE hDevice;
    CHAR root[MAX_PATH];
    BOOL isOK;
    int drive;
    DWORD BytesReturn;
    DISK_GEOMETRY d_geo;
    PARTITION_INFORMATION pinfo;

    memset(&d_geo,0,sizeof(d_geo));
    nDeviceNum = 0 ;

    for (drive=0;  drive< MAX_SAGE_SSD_COUNT; drive++)
    {
        wsprintfA(root,  "\\\\.\\PHYSICALDRIVE%c" ,drive+'0');
        hDevice = CreateFileA( root ,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
        if (hDevice == INVALID_HANDLE_VALUE)
        {
            INT nErr = GetLastError() ;
            continue;
        }
        isOK = DeviceIoControl(
            hDevice,        // handle to a file
            IOCTL_DISK_GET_DRIVE_GEOMETRY,   // dwIoControlCode, control code of operation to perform
            NULL,                    // lpInBuffer is not used; must be NULL
            0,                       // nInBufferSize is not used; must be zero
            &d_geo,                 // lpOutBuffer is not used; must be NULL
            sizeof(DISK_GEOMETRY),   // nOutBufferSize is not used;	 must be zero
            (LPDWORD) &BytesReturn,  // pointer to variable to receive	output byte count
            NULL					// pointer to OVERLAPPED structure for asynchronous operation
            );
        if (!isOK)
        {
            CloseHandle(hDevice);
            continue;
        }

        isOK =  DeviceIoControl(
            (HANDLE) hDevice,        // handle to device of interest
            IOCTL_DISK_GET_PARTITION_INFO,   // dwIoControlCode, control code of operation to perform
            NULL,                    // lpInBuffer is not used; must be NULL
            0,                       // nInBufferSize is not used; must be zero
            (LPVOID) &pinfo,		// pointer to output buffer
            (DWORD) (sizeof(PARTITION_INFORMATION)),  // size, in bytes, of lpOutBuffer
            (LPDWORD) &BytesReturn,   // pointer to variable to receive output byte count
            (LPOVERLAPPED) NULL		// pointer to OVERLAPPED structure for asynchronous operation
            );
        CloseHandle(hDevice);
        if (!isOK)
            continue;
        int r;
        BYTE buf[0x200];
        r = checkDevice( root , buf );
        if (r==0)
        {
            wsprintfA( *(szDeviceName+ nDeviceNum), "%s" , root );
            nDeviceNum++;
            //break;
        }
    }
    if ( 0 == nDeviceNum )
    {
        return -1 ;
    }else
    {
        return 0 ;
    }
}

//查询注册表，获取配置信息或者创建注册表信息
void GetRegeditInfo( HKEY &hKey , CHAR *szPSN , CHAR *szVersion , BOOL &bRegistered , UINT32 &nIndex )
{
    UINT32 retValue = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\SAGE\\Vulture_SSDSafeDisk", 0 , KEY_ALL_ACCESS , &hKey);
    if ( retValue == ERROR_SUCCESS)
    {
        UINT i=0;
        CHAR portName[255],commName[255];
        DWORD dwLong,dwSize;
        while(1)
        {
            dwLong = dwSize = sizeof(portName)/sizeof(char);
            if( ::RegEnumValueA( hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize ) == ERROR_NO_MORE_ITEMS )
                break;
            if ( strcmp( szPSN , portName ) == 0)//如果相等，说明此U盘已在此电脑注册
            {
                bRegistered = TRUE;
                nIndex = *(DWORD*)commName;
                //break;
            }
            else if ( strcmp( portName , "Version") == 0 )
            {
                memcpy( szVersion,(char*)commName , 32 ) ;
            }
            i++;
            memset( portName , 0x00 , 255 ) ;
            memset( commName , 0x00 , 255 ) ;
        }
    }else	 //创建注册表信息
    {
        //REG_OPTION_NON_VOLATILE:保存，重启还在；REG_OPTION_VOLATILE:不保存，重启不在。
        retValue = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\SAGE\\Vulture_SSDSafeDisk",
            0 ,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey ,
            NULL);

        bRegistered = FALSE;
    }

}

UINT32 StartMountProcess(const QString& strMountProcessPath , MountSecurityDiskParam aMountParam , CHAR chMaxLetter )
{
    g_hEventMount = CreateEvent(NULL,FALSE,FALSE,NULL);

    WCHAR chLetter = 0 ;
    UINT32 retValue = MountSecurityDiskW_SageAPI( strMountProcessPath.toStdWString().c_str(), aMountParam , chMaxLetter ) ;
    if ( 0 != retValue )
    {
        return -1 ;
    }

    MSG msg;
    while (TRUE)
    {
        //wait for m_hThread to be over，and wait for QS_ALLINPUT（Any message is in the queue）
        retValue = MsgWaitForMultipleObjects (1, &g_hEventMount,   FALSE, INFINITE, QS_ALLINPUT);
        switch(retValue)
        {
        case WAIT_OBJECT_0:
            CloseHandle( g_hEventMount );
            if ( 2 == g_nProcessState )
            {
                retValue = 0 ;
            }else
            {
                retValue = -1 ;
            }
            g_nProcessState = MESSAGE_NO_COME;
            break; //break the loop
        case WAIT_OBJECT_0 + 1:
            //get the message from Queue and dispatch it to specific window
            PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
            DispatchMessage(&msg);
            continue;
        default:
            DWORD nErr = GetLastError();
            break; // unexpected failure
        }
        break;
    }
    return retValue ;
}

int LoadSAGESSD_dll()
{
    hInstLibrary = LoadLibraryA("SAGE_SSD.dll");//注意此处必须有_T()函数。
	if (hInstLibrary == NULL)     
	{     
		FreeLibrary(hInstLibrary);  
        qDebug()<<"hInstLibrary == NULL";
		return -1;
	} 
	//checkDevice
	checkDevice = (CheckDevice)GetProcAddress(hInstLibrary, "CheckDevice");
	if ( checkDevice == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"checkDevice == NULL";
		return -2;
	}

	getDiskinfo = (GetDiskInfo)GetProcAddress(hInstLibrary, "GetDiskInfo");
	if ( getDiskinfo == NULL )
	{       
        FreeLibrary(hInstLibrary);
        qDebug()<<"getDiskinfo == NULL";
		return -2;
	}
	//SavePartitionInfo
	savePartitionInfo = (SavePartitionInfo)GetProcAddress(hInstLibrary, "SavePartitionInfo");
	if ( savePartitionInfo == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"savePartitionInfo == NULL";
		return -2;
	}

	//ModifyPassword
	modifyPassworda = (ModifyPassword)GetProcAddress(hInstLibrary, "ModifyPassword");
	if ( modifyPassworda == NULL )
	{       
        FreeLibrary(hInstLibrary);
        qDebug()<<"modifyPassworda == NULL";
		return -2;
	}

	//SwitchState
	switchState = (SwitchState)GetProcAddress(hInstLibrary, "SwitchState");
	if ( switchState == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"switchState == NULL";
		return -2;
	}

	//ReadCurrentStates
	readCurrentStates = (ReadCurrentStates)GetProcAddress(hInstLibrary, "ReadCurrentStates");
	if ( readCurrentStates == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"readCurrentStates == NULL";
		return -2;
	}

	//Read2KRandomData
	read2KRandomData = (Read2KRandomData)GetProcAddress(hInstLibrary, "Read2KRandomData");
	if ( read2KRandomData == NULL )
	{       
        FreeLibrary(hInstLibrary);
        qDebug()<<"read2KRandomData == NULL";
		return -2;
	}

	//WriteSecurityData
	writeSecurityData = (SSDWriteSecurityData)GetProcAddress(hInstLibrary, "SSDWriteSecurityData");
	if ( writeSecurityData == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"writeSecurityData == NULL";
		return -2;
	}

	//ReadSecurityData
	readSecurityData = (SSDReadSecurityData)GetProcAddress(hInstLibrary, "SSDReadSecurityData");
	if ( readSecurityData == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"readSecurityData == NULL";
		return -2;
	}

	//EraseAll
	eraseAll = (EraseAll)GetProcAddress(hInstLibrary, "EraseAll");
	if ( eraseAll == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"eraseAll == NULL";
		return -2;
	}

	//GetReadOnlyState
	getReadOnlyState = (GetReadOnlyState)GetProcAddress(hInstLibrary, "GetReadOnlyState");
    if ( getReadOnlyState == NULL )
	{       
        FreeLibrary(hInstLibrary);
        qDebug()<<"getReadOnlyState == NULL";
		return -2;
	}

	//EnablePartitionReadOnly
	enablePartitionReadOnly = (EnablePartitionReadOnly)GetProcAddress(hInstLibrary, "EnablePartitionReadOnly");
    if ( enablePartitionReadOnly == NULL )
	{       
        FreeLibrary(hInstLibrary);
        qDebug()<<"enablePartitionReadOnly == NULL";
		return -2;
	}

	//DisablePartitionReadOnly
	disablePartitionReadOnly = (DisablePartitionReadOnly)GetProcAddress(hInstLibrary, "DisablePartitionReadOnly");
    if ( disablePartitionReadOnly == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"disablePartitionReadOnly == NULL";
		return -2;
	}

	//GetHiddenCapacity
	getHiddenCapacity = (GetHiddenCapacity)GetProcAddress(hInstLibrary, "GetHiddenCapacity");
    if ( getHiddenCapacity == NULL )
	{       
		FreeLibrary(hInstLibrary);  
        qDebug()<<"getHiddenCapacity == NULL";
        return -2;
	}

	return 0;
}

void FreeSAGESSD_dll()
{
	FreeLibrary(hInstLibrary);  
}

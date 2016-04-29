#include "safedisk.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QTime>
#include <vector>
#include <string>
#include <memory>

#include "SAGESSDDll.h"
#include "cwaitdlg.h"

#define DISK_LETTER_DATA   "D"
#define PROCESS_NONE   -1
#define RETURN_FAILED  -1

SafeDisk* SafeDisk::s_pInstance = nullptr;

SafeDisk::SafeDisk()
{
    m_bInit = false;
    m_bLogin = false;
    memset(&m_safeDiskInfo, 0, sizeof(SafeDiskInfo));
    memset(&m_secDiskInfo, 0, sizeof(SecurityDiskInfo));
    memset(m_szPSN, 0, sizeof(m_szPSN));
    memset(m_szDeviceName, 0, sizeof(m_szDeviceName));
    m_hEventCreate = NULL;
    m_hEventMount = NULL;
    m_nProcessState = PROCESS_NONE;
    m_nProcessStateMount = PROCESS_NONE;
    m_cMountedDevice = MOUNT_NONE;

}

SafeDisk::~SafeDisk(){
    FreeSAGESSD_dll();
}

bool SafeDisk::init(){
    if (!m_bInit){
        if (0 != LoadSAGESSD_dll())
        {
            qDebug()<<"0 != LoadSAGESSD_dll()";
            return false;
        }

        if (!MyDriverAttach()){
            return false;
        }

        char szSSDDeviceName[MAX_SAGE_SSD_COUNT][32];		//SSD设备物理盘名称
        UINT32 nSSDDeviceNum ;//SSD 设备个数
        UINT32 retValue = EnumSageSSDDev( szSSDDeviceName , nSSDDeviceNum ); //获取所有的澜盾SSD
        if (0 != retValue)
        {
            qDebug()<<QStringLiteral("未找到澜盾加密SSD！");
            QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("未找到澜盾加密SSD！"));
            return false;
        }else if (1 < nSSDDeviceNum)
        {
            QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("检测到多个澜盾加密SSD，请拔出其他SSD"));
            return false;
        }

        memcpy_s(m_szDeviceName, sizeof(m_szDeviceName), szSSDDeviceName[0], sizeof(szSSDDeviceName[0]));
        m_bInit = true;
    }

    return m_bInit;
}

#define MYWM_CREATE_VOLUME_FINISH						(WM_APP + 1)
#define MYWM_MOUNT_VOLUME_FINISH						(WM_APP + 2)
bool SafeDisk::nativeEvent(void *message){
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg != nullptr){
        switch (msg->message) {
        case MYWM_CREATE_VOLUME_FINISH:
            qDebug() << __FUNCTION__ <<" "<<__LINE__ << " "<< msg->wParam;
            m_nProcessState = msg->wParam;
            SetEvent(m_hEventCreate);
            break;
        case MYWM_MOUNT_VOLUME_FINISH:
            qDebug() << __FUNCTION__ <<" "<<__LINE__ << " "<< msg->wParam;
            m_nProcessStateMount = msg->wParam;
            SetEvent(m_hEventMount);
            break;
        default:
            break;
        }
    }

    return true;
}
bool SafeDisk::verifyPasswd(const QString& sPassword){
    if (!init()){
        return false;
    }

    auto pw = sPassword.toStdString();
    BOOL isSuc = VerifyLoginPasswordA_SageAPI(m_szDeviceName, (char *)pw.c_str());
    if (!isSuc)
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("密码错误！"));
        return false;
    }

    return true;
}
bool SafeDisk::modifyPasswd(const QString& sNewPassword){
    if (!m_bLogin){
        qDebug()<<"please login first";
        return false;
    }
    UINT32 retValue = ModifyLoginPasswordA_SageAPI(m_szDeviceName, (CHAR*)sNewPassword.toStdString().c_str());

    return 0 == retValue;
}

bool SafeDisk::login(const QString& sPassword){
    if (!verifyPasswd(sPassword)){
        return false;
    }
    //获取当前SSD信息
    ZeroMemory( (void*)&m_safeDiskInfo , sizeof( SafeDiskInfo ) ) ;
    int retValue = GetSafeDiskInfoFromDeviceA_SageAPI(m_szDeviceName , &m_safeDiskInfo ) ;
    if ( 0 != retValue )
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("获取SSD信息失败！"));
        return false;
    }

    ZeroMemory( (void*)&m_secDiskInfo , sizeof( SecurityDiskInfo ) ) ;
    retValue = GetSecurityDiskInfoFromDeviceA_SageAPI( m_szDeviceName , m_safeDiskInfo.m_nPCNumber , SECURITY_DISK_INFO_LEN_SECTOR , &m_secDiskInfo ) ;
    if (0 != retValue)
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("获取配置信息失败！"));
        return false;
    }
    else
    {
        qDebug()<< (QString(QStringLiteral("当前PC上创建了%1个安全区！")).arg(m_secDiskInfo.m_nVirDiskCnt));
    }

    memset( m_szPSN , 0x00 , 32 ) ;
    retValue = GetSageSSDPsn( m_szDeviceName, m_szPSN ) ;
    if (  0 != retValue )
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("获取PSN失败！"));
        return false;
    }

    m_bLogin = true;
    return true;
}

bool SafeDisk::Mount(const QWidget& wd){
    if (!m_bLogin){
        qDebug()<<"please login first";
        return false;
    }

    qDebug()<< QStringLiteral("Mount");
    if (m_secDiskInfo.m_nVirDiskCnt == 0){
        if (!CreateSafeDisk(wd))
        {
            return false;
        }
    }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
    QString mountExe = QApplication::applicationDirPath() + "/MountVolume_Client.exe";
    mountExe.replace("/", "\\");
    for ( UINT i = 0 , j = 1 ; i < MAX_VIRDISK_NUM  ; i++)
    {
        if ( EXIST_MARK != m_secDiskInfo.m_VirDiskInfo[i].m_IsExist)//如果标志位不存在则跳过本次循环
        {
            continue;
        }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        MountSecurityDiskParam aMountParam ;
        aMountParam.hwnd = (HWND)wd.winId();
        int n = strlen((char*)m_secDiskInfo.m_VirDiskInfo[i].m_chFilePath); //获取str的字符数
        int len = MultiByteToWideChar(CP_ACP, 0, (char*)m_secDiskInfo.m_VirDiskInfo[i].m_chFilePath , n , NULL, 0 );
        WCHAR *pWChar = new WCHAR[len + 1]; //以字节为单位
        MultiByteToWideChar(CP_ACP, 0, (char*)m_secDiskInfo.m_VirDiskInfo[i].m_chFilePath , n , pWChar, len );
        pWChar[len] = '\0'; //多字节字符以'\0'结束
        memcpy( aMountParam.wDiskImageFilePath , (void*)pWChar , VDISK_NAME_LEN*2 );
        delete[] pWChar;
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        memcpy( aMountParam.szKey , (BYTE*)m_safeDiskInfo.m_szKey , 32) ;
        aMountParam.nKeyLength = sizeof( m_safeDiskInfo.m_szKey ) ;

        m_hEventMount = CreateEvent(NULL, FALSE, FALSE, NULL);
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        WCHAR chLetter = 0 ;
        UINT32 retValue = MountSecurityDiskW_SageAPI( mountExe.toStdWString().c_str(), aMountParam , chLetter, L'E') ;
        if (0 != retValue )
        {
            qDebug()<< __FUNCTION__<<"  "<<__LINE__;
            CloseHandle( m_hEventMount );
            return false;
        }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        std::shared_ptr<bool> bCanGoOn = std::make_shared<bool>(false);
        CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在创建安全区中..."), [&]()
        {
            retValue = WaitForSingleObject(m_hEventMount, INFINITE) ;
            *bCanGoOn = true;
        }, [](bool){});

        while (!(*bCanGoOn)){
            ::Sleep(500);
        }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        CloseHandle( m_hEventMount );
        switch ( retValue )
        {
        case WAIT_OBJECT_0:
            if ( 2 == m_nProcessStateMount)
            {
                m_cMountedDevice = (CHAR)chLetter ;
                m_secDiskInfo.m_VirDiskInfo[i].m_nIsMount = 1 ;
                m_secDiskInfo.m_VirDiskInfo[i].m_chDiskLetter = chLetter ;
            }
            m_nProcessStateMount = MESSAGE_NO_COME;
            break; //break the loop
        case SAGE_API_ERR_LETTER_NO_EXIST:
            QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("无法获取系统可用盘符，部分安全区无法挂载，\r\n您可以尝试重启电脑操作！"));
        default:
            //DWORD nErr = GetLastError();
            m_secDiskInfo.m_VirDiskInfo[i].m_nIsMount = 0 ;
            m_secDiskInfo.m_VirDiskInfo[i].m_chDiskLetter = 0 ;
            break; // unexpected failure
        }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
        j++;
    }
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
    SetSecurityDiskInfoA_SageAPI( m_szDeviceName, m_safeDiskInfo.m_nPCNumber, SECURITY_DISK_INFO_LEN_SECTOR , &m_secDiskInfo);//修改本PC上的安全区信息
    qDebug()<< __FUNCTION__<<"  "<<__LINE__;
    return true;

}


bool SafeDisk::CreateSafeDisk(const QWidget& wd)
{
    std::shared_ptr<UINT32> pRetValue = std::make_shared<UINT32>(0);
    std::shared_ptr<bool> bCanGoOn = std::make_shared<bool>(false);
    ++m_safeDiskInfo.m_nPCNumber;
    QString createExe = QApplication::applicationDirPath() + "/CreateVolume_Client.exe";
    createExe.replace("/", "\\");
    VirDiskInfo& vdi = m_secDiskInfo.m_VirDiskInfo[0];
    vdi.m_nIsMount = 0x01 ;
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    //创建安全区镜像存储文件夹
    QDir d(DISK_LETTER_DATA"/VultureSafeArea");
    if (!d.exists())
    {
        d.mkpath(DISK_LETTER_DATA"/VultureSafeArea");
        SetFileAttributesA( DISK_LETTER_DATA"\\VultureSafeArea" , FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM ); //隐藏
    }

    qDebug()<<__FUNCTION__<<" "<<__LINE__;

    UINT32 nRandomNum = QTime::currentTime().msec();
    sprintf_s((char*)vdi.m_chFilePath, VDISK_NAME_LEN, "%s:\\VultureSafeArea\\%s_%dfdisk.img",
        DISK_LETTER_DATA, m_szPSN , nRandomNum );

    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    CHAR chLetter = 0;
    *pRetValue = GetVailLunA_SageAPI(&chLetter , 'H');//获取一个可用盘符
    if (0 != *pRetValue )
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("无法获取系统可用盘符，请重启电脑后操作！"));
        *pRetValue = RETURN_FAILED;
        goto EXIT2;
    }
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    vdi.m_chDiskLetter = chLetter ;

    CreateSecurityDiskParam securityDiskParam ;
    securityDiskParam.hwnd = (HWND)wd.winId();
    securityDiskParam.iDriverNo = chLetter - 65 ;

    ULARGE_INTEGER FreeAv, TotalBytes, FreeBytes;
    if (!GetDiskFreeSpaceExA(DISK_LETTER_DATA ,&FreeAv, &TotalBytes, &FreeBytes))
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("需要有D盘分区来创建安全区！"));
        *pRetValue = RETURN_FAILED;
        goto EXIT2;
    }
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    securityDiskParam.nDiskCapacity = FreeBytes.QuadPart / 1024 / 1024;
    int n = strlen((char*)vdi.m_chFilePath); //获取str的字符数
    int len = MultiByteToWideChar(CP_ACP, 0, (char*)vdi.m_chFilePath , n , NULL, 0 );
    WCHAR *pWChar = new WCHAR[len + 1]; //以字节为单位
    MultiByteToWideChar(CP_ACP, 0, (char*)vdi.m_chFilePath , n , pWChar, len );
    pWChar[len] = '\0'; //多字节字符以'\0'结束
    memcpy(securityDiskParam.wDiskImageFilePath , (void*)pWChar , VDISK_NAME_LEN*2 );
    delete[] pWChar;
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    securityDiskParam.nDiskSysType = FILESYS_FAT;
    securityDiskParam.bQuickFormate = TRUE;
    memcpy(securityDiskParam.szKey , m_safeDiskInfo.m_szKey , 32 ) ;
    securityDiskParam.nKeyLength = sizeof(m_safeDiskInfo.m_szKey) ;

    m_hEventCreate = CreateEvent(NULL, FALSE, FALSE, NULL);
    qDebug()<<__FUNCTION__<<" "<<__LINE__<<" "<<createExe<<" "<<QString::fromWCharArray(securityDiskParam.wDiskImageFilePath)<<" "<<securityDiskParam.iDriverNo
              <<" "<<securityDiskParam.nDiskCapacity;
    *pRetValue = CreateSecurityDiskW_SageAPI(createExe.toStdWString().c_str() , securityDiskParam) ;
    if (*pRetValue == 0)
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("创建安全区进程出错！"));
        *pRetValue = RETURN_FAILED;
        goto EXIT2;
    }

    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在创建安全区中..."), [=]()
    {
        *pRetValue = WaitForSingleObject(m_hEventCreate, 80000) ;
        *bCanGoOn = true;
    }, [](bool){});

    while (!(*bCanGoOn)){
        ::Sleep(500);
    }

    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    switch ( *pRetValue )
    {
    case WAIT_OBJECT_0:
        // hProcess所代表的进程在80秒内结束
        if (m_nProcessState != 0 )
        {
            m_nProcessState = MESSAGE_NO_COME;
            GetSafeDiskInfoFromDeviceA_SageAPI( m_szDeviceName , &m_safeDiskInfo);//获取USB设备信息
            *pRetValue = RETURN_FAILED;
            QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("创建失败！"));
            goto EXIT2;
        }
        break;
    case WAIT_TIMEOUT:
        // 等待时间超过80秒
        m_nProcessState = MESSAGE_NO_COME;
        GetSafeDiskInfoFromDeviceA_SageAPI( m_szDeviceName , &m_safeDiskInfo);//获取USB设备信息
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("创建出错，超时返回！"));
        *pRetValue = RETURN_FAILED;
        goto EXIT2;
        break;
    case WAIT_FAILED:
        // 函数调用失败，比如传递了一个无效的句柄
        m_nProcessState = MESSAGE_NO_COME;
        GetSafeDiskInfoFromDeviceA_SageAPI( m_szDeviceName , &m_safeDiskInfo);//获取USB设备信息

        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("创建失败，出错返回！"));
        *pRetValue = RETURN_FAILED;
        goto EXIT2;
        break;
    }

    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    m_safeDiskInfo.m_nCurIndex = m_safeDiskInfo.m_nPCNumber ;
    m_safeDiskInfo.m_nBlockIndex[m_safeDiskInfo.m_nPCNumber] = EXIST_MARK ;
    SetSafeDiskInfoA_SageAPI( m_szDeviceName , &m_safeDiskInfo );//修改U盘信息


    //修改卷区名称
//    USES_CONVERSION ;
    char strTemp[32];
    sprintf(strTemp, "%c:\\", chLetter);
    SetVolumeLabelA(strTemp , (char*)vdi.m_chDiskName );

    ++m_secDiskInfo.m_nVirDiskCnt;
    vdi.m_IsExist = EXIST_MARK ;
    memcpy( m_secDiskInfo.m_szPSN , m_szPSN , 32 ) ;
    SetSecurityDiskInfoA_SageAPI( m_szDeviceName, m_safeDiskInfo.m_nPCNumber ,
        SECURITY_DISK_INFO_LEN_SECTOR , &m_secDiskInfo );//修改本PC上的安全区信息
    *pRetValue = securityDiskParam.iDriverNo;
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
EXIT2:
    CloseHandle(m_hEventCreate);
    m_hEventCreate = NULL;
    if ( m_secDiskInfo.m_nVirDiskCnt > 0 ) //安全区不存在时不需要更新配置数据
    {
        GetSecurityDiskInfoFromDeviceA_SageAPI( m_szDeviceName , m_safeDiskInfo.m_nPCNumber ,
            SECURITY_DISK_INFO_LEN_SECTOR , &m_secDiskInfo ) ;
    }
    qDebug()<<__FUNCTION__<<" "<<__LINE__;
    return *pRetValue != RETURN_FAILED;;
}

bool SafeDisk::MyDriverAttach()
{
    //判断操作系统32 、64
    BOOL bWow64 = TRUE ;
    typedef BOOL (__stdcall *LPFN_ISWOW64PROCESS ) (HANDLE hProcess,PBOOL Wow64Process);
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress (GetModuleHandleA("kernel32"), "IsWow64Process");

    if (fnIsWow64Process != NULL)
    {
        if (!fnIsWow64Process (GetCurrentProcess(), &bWow64)){
            bWow64 = FALSE;
        }
    }

    QString createDriver = QApplication::applicationDirPath();
    createDriver.replace("/", "\\");
    if ( bWow64 )
    {
        createDriver += "\\sagedisks-x64.sys";
    }
    else
    {
        createDriver += "\\sagedisks.sys";
    }

    UINT32 retValue = MyDriverAttachW_SageAPI((WCHAR*)createDriver.toStdWString().c_str() );
    if ( 0 != retValue)
    {
        qDebug()<<QStringLiteral("澜盾驱动安装或加载失败！路径：")<<createDriver;
        return false;
    }
    else
    {
         qDebug()<<QStringLiteral("澜盾驱动安装或加载成功！路径：")<<createDriver;
         return true;
    }
}

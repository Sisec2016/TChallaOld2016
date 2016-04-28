#ifndef SAFEDISK_H
#define SAFEDISK_H
#include <QString>
#include <QWidget>
#include "SAGESSDDll.h"

#define MOUNT_NONE   0
class SafeDisk
{
    static SafeDisk* s_pInstance;
public:
    static SafeDisk &instance(){
        if (s_pInstance == nullptr){
            s_pInstance = new SafeDisk();
        }

        return *s_pInstance;
    }

private:
    SafeDisk();
    ~SafeDisk();
public:
    bool init();
    bool nativeEvent(void *message);
    bool verifyPasswd(const QString& sPassword);
    bool modifyPasswd(const QString& sNewPassword);
    bool login(const QString& sPassword);
    bool Mount(const QWidget& wd);
    char getMountDevice(){
        return m_cMountedDevice;
    }

protected:
    bool MyDriverAttach();
    bool CreateSafeDisk(const QWidget& wd);
protected:
    bool m_bInit;
    bool m_bLogin;
    SafeDiskInfo m_safeDiskInfo ;
    SecurityDiskInfo m_secDiskInfo;
    char m_szPSN[32] ;
    char m_szDeviceName[32];
    HANDLE m_hEventCreate;
    HANDLE m_hEventMount;
    int m_nProcessState;
    int m_nProcessStateMount;
    char m_cMountedDevice;
};

#endif // SAFEDISK_H

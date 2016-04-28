#ifndef _PROXYTYPES_H
#define _PROXYTYPES_H

#include "NetClientTypes.h"
#include "DEFINE_USER_ERROR.h"

#define MAX_PROXY               1024     //最多添加的代理(最大输入)
#define MAX_CLIENT_CONNECTION   1024     //最大的客户端连接数（最大输出）

#ifndef DEV_TIANDY
#define DEV_TIANDY   0
#endif

#ifndef LEN_8
#define LEN_8   8
#endif

#ifndef LEN_16
#define LEN_16  16
#endif

#ifndef LEN_32
#define LEN_32  32
#endif

#ifndef LEN_64
#define LEN_64  64
#endif

#ifndef LEN_128
#define LEN_128 128
#endif

#ifndef LEN_256
#define LEN_256 256
#endif

#ifndef STRUCT_RESERVE
#define STRUCT_RESERVE
typedef struct                            //This structure is for reserve.
{
	int   m_iReserved1;
	unsigned long m_dwReserved2;
	char  m_cReserved1[32];
	char  m_cReserved2[64];
}st_Reserve;
//typedef struct st_Reserve *pst_Reserve;
#endif

struct st_EncoderProxy
{
    char         m_cDevIP[LEN_16];         //dev ip :192.168.1.2
    unsigned int m_iType;                  //dev type: TIANDY-S
    char         m_cFactoryID[LEN_32];     //dev id: ID....
    char         m_cDevName[LEN_32];       //dev name: NVSS1  Reserved
    int          m_iPort;                  //dev port: 3000
    int          m_iNetMode;               //dev connect net mode: NETMODE_TCP
    char         m_cAccount[LEN_32];       //dev logon account: Admin
    char         m_cPwd[LEN_32];           //dev logon pwd: Admin

    char         m_cProxy[LEN_16];         //Proxy IP

    st_Reserve   m_stReserve;
};

struct st_NetInterface
{
    char m_IP[LEN_32][LEN_16];
};

typedef int (*NOTIFY_PROXYMAIN)(int _iProxyID,int _iWparam,int _iLparam);
typedef int (*NOTIFY_CLIENTCONNECT)(char *_cClientIP,int _iPort,int *_iPass);
typedef int (*NOTIFY_USERSTRING)(char *_cClientIP,int _iType,char *_cMsg,int _iLen);

#endif


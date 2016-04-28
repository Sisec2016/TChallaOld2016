#ifndef __TYPE_DEF_H
#define __TYPE_DEF_H


enum
{
	ERR_SUCCESS,
	ERR_EXIST,
	ERR_SHARE_NOT_LOGIN,//没有登录共享主机
	ERR_UNIMPORTANT,	//拷贝操作已经结束，文件可能没有完全拷贝
	ERR_UNKNOWN,
};
#define MAX_PATH_LEN 1024
typedef struct
{
	int iErr;	//错误类型ERR_SUCCESS等
	char szPath[MAX_PATH_LEN];	//重名文件、文件夹路径
	bool bIsCover;	//是否覆盖， true 覆盖
}T_ErrInfo;
typedef void (*pFuncMovePercentCallback)(unsigned int iHandle, unsigned int iUserData, int iCurPercent, int iTotalPercent, int iType, void *pParam);



#endif
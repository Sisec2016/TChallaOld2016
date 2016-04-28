#ifndef __SHARE_MODULE_API_H
#define __SHARE_MODULE_API_H

#include "dllexport.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

#include "TypeDef.h"

extern "C"
{
	/*共享主机登录
	  @szRemoteName  共享主机名，或者ip；("\\\\LM002-PC"  OR  "\\\\192.168.1.5")
	  @szUserName  共享主机用户名
	  @szPsw  共享主机用户登录密码
	*/
	DLLEXPORT_API bool share_Login(char *szRemoteName, char *szUserName, char *szPsw);
	/*把单个文件拷贝到指定目录
	  @szFileName 要移动的文件（F:\tools\ultraedit.exe）
	  @szPathMoveTo 要移动到的目录(E:\tools)

	  @return 拷贝操作句柄，可以停止拷贝，以及获取进度。
	*/
	DLLEXPORT_API unsigned int share_MoveFile(char *szFileName, char *szPathMoveTo, pFuncMovePercentCallback callback, unsigned int iUserData);
	/*把多个文件拷贝到指定目录(不能拷贝目录)
	  @vecFileName 要移动的文件
	    vecFileName.push_back("F:\tools\ultraedit.exe");
		vecFileName.push_back("F:\tools\bcompare.exe")
		@szPathMoveTo 要移动到的目录(E:\tools)

		@return 拷贝操作句柄，可以停止拷贝，以及获取进度。
	*/
	DLLEXPORT_API unsigned int share_MoveFiles(vector<string> &vecFileName, char *szPathMoveTo, pFuncMovePercentCallback callback, unsigned int iUserData);
	/*把某个目录下的多个文件、文件夹拷贝到指定目录（文件夹也可以拷贝），如有文件夹需要拷贝，需便利文件夹下的所有文件路径到@vecFileName中
	  @vecFileName 要移动的文件
	    vecFileName.push_back("E:\...\rootdir\VideoDown\ultraedit.exe");
		vecFileName.push_back("E:\...\rootdir\VideoDown\...\bcompare.exe")
		vecFileName.push_back("E:\...\rootdir\xxx.exe")
		@szPathMoveFrom 源目录（所有要移动的文件的第一个共同的顶级目录 如 E:\...\rootdir）
		@szPathMoveTo 要移动到的目录(F:\...\somedir)

		@return 拷贝操作句柄，可以停止拷贝，以及获取进度。
	*/
	DLLEXPORT_API unsigned int share_MoveFiles_2(vector<string> &vecFileName, char *szPathMoveFrom, char *szPathMoveTo, pFuncMovePercentCallback callback, unsigned int iUserData);
	/*把一个文件夹(包含子文件夹、文件)拷贝到指定目录
	  @szDir 要移动的文件夹（F:\tools）
	  @szPathMoveTo 要移动到的目录(E:)

	  @return 拷贝操作句柄，可以停止拷贝，以及获取进度。
	*/
	DLLEXPORT_API unsigned int share_MoveDirAndSub(char *szDir, char *szPathMoveTo, pFuncMovePercentCallback callback, unsigned int iUserData);
	/* 停止当前拷贝
	   @iHandle  拷贝句柄，每个拷贝函数返回值(unsigned int)
	*/
	DLLEXPORT_API void share_Stop(unsigned int &iHandle);
	//单个文件调用，多个文件时则反应当前正在拷贝的文件
	DLLEXPORT_API int  share_GetCurrentFilePercent(unsigned int iHandle);
	//多个文件调用
	DLLEXPORT_API int  share_GetTotalPercent(unsigned int iHandle);
};

#endif
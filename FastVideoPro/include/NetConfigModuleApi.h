#ifndef __NETCONFIG_MODULE_API_H
#define __NETCONFIG_MODULE_API_H

#include "dllexport.h"

extern "C"
{
	DLLEXPORT_API bool netconfig_SetIP(char* pIPAddress, char* pNetMask, char* pNetGate);
	DLLEXPORT_API bool netconfig_GetIP(char* pIPAddress, char* pNetMask, char* pNetGate, int iBufLen);
};

#endif
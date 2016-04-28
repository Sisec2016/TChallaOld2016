#ifndef _DLLEXPORT_H
#define _DLLEXPORT_H

#if defined(_WIN32)
	#if defined(DLL_EXPORTS)
		#define DLLEXPORT_API _declspec(dllexport)
	#else
		#define DLLEXPORT_API _declspec(dllimport)	
	#endif
#endif


#if !defined(DLLEXPORT_API)
	#define DLLEXPORT_API
	#define __stdcall
#endif


#endif


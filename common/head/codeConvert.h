// codeConvert.h: interface for the CodeConvert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODECONVERT_H__5EC20E9E_4032_4227_9342_37DB9D2AF18F__INCLUDED_)
#define AFX_CODECONVERT_H__5EC20E9E_4032_4227_9342_37DB9D2AF18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <sstream>

typedef wchar_t  WCHAR;
typedef __int64 LONGLONG; 
#define  AUTO_BUFFER   0 //缓存设为零，则每次都重新分配
#ifndef MTHCHR
#ifdef UNICODE
typedef wchar_t MTHCHR;
#else
typedef char MTHCHR;
#endif
#endif
class CodeConvert  
{
public:
	
	CodeConvert(int UincodeBufferSize = AUTO_BUFFER, int MbsBufferSize = AUTO_BUFFER, int BufferNum = 1);
	virtual ~CodeConvert();
    const MTHCHR* ToTChar(const WCHAR* psW)
	{
#ifdef UNICODE
		return psW;
#else
		return ToAnsi(psW);
#endif
	}
    const MTHCHR* ToTChar(const char* psA)
	{
#ifdef UNICODE
		return ToUncd(psA);
#else
		return psA;
#endif
	}
	const char* ToAnsi(const WCHAR* psW);
	const char* ToAnsi(const char* psA)
	{
		return psA;
	}
	const WCHAR* ToUncd(const char* psA);
	const WCHAR* ToUncd(const WCHAR* psW)
	{
		return psW;
	}
	const char* ConvertToString(int value, int nbase = 10) 
	{
		return _itoa(value, m_sBuf, nbase);
	}
	const char* ConvertToString(ULONG value, int nbase = 10) 
	{
		return _ultoa(value, m_sBuf, nbase);
	}
	const char* ConvertToString(long value, int nbase = 10) 
	{
		return _ltoa(value, m_sBuf, nbase);
	}
    const char* ConvertToString(LONGLONG value, int nbase = 10) 
    {
        return _i64toa(value, m_sBuf, nbase);
    }
	const char* ConvertToString(double value)
	{
		return _gcvt(value, sizeof(m_sBuf)-1, m_sBuf);
	}
	const WCHAR* ConvertToWString(double value)
	{
		return ToUncd(ConvertToString(value));
	}
	template <class T> 
	const WCHAR* ConvertToWString(T value, int nbase = 10)
	{
		return ToUncd(ConvertToString(value, nbase));
	}
	template <class T> 
    const MTHCHR* ConvertToTCHAR(T value, int nbase = 10)
	{
		return ToTChar(ConvertToString(value));
	}
    static double ttod(const MTHCHR *tNum)
	{
#ifdef _UNICODE
		WCHAR *pW;
		return wcstod(tNum, &pW);
#else
		return strtod(tNum, NULL);
#endif
	}

private:
    char** m_psChar;
	WCHAR** m_psWchar;
	int m_nBufferNum;
	int m_NowMbsBufIn;
	int m_NowUniBufIn;
	int m_nMSize;
	int m_nUSize;
	char m_sBuf[50];
};

#endif // !defined(AFX_CODECONVERT_H__5EC20E9E_4032_4227_9342_37DB9D2AF18F__INCLUDED_)

#pragma once
#ifndef DBAGENT_EXPORTS

typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned short USHORT;
typedef unsigned __int64 DWORDLONG;
#define  FALSE 0
#define  TRUE  1

#define interface struct
typedef unsigned __int64 entityid;

#ifndef tagDEC
typedef struct tagDEC { 
	USHORT wReserved; 
	union { 
		struct { 
			char scale;  // The number of decimal places for the 
			// number. Valid values are from 0 to 28. So 
			// 12.345 is represented as 12345 with a 
			// scale of 3. 
			char sign;  // 0 for positive numbers or DECIMAL_NEG for 
			// negative numbers. So -1 is represented as 
			// 1 with the DECIMAL_NEG bit set. 
		}; 
		USHORT signscale; 
	}; 
	ULONG Hi32;            // The high 32 bits of your number 
	union { 
		struct { 
#ifdef _MAC 
			ULONG Mid32; 
			ULONG Lo32; 
#else 
			ULONG Lo32; 
			ULONG Mid32; 
#endif 
		}; 
		DWORDLONG Lo64;  // The low 64 bits of your number. This is an 
		// _int64. 
	}; 
} DECIMAL; 

#endif //#ifndef tagDEC
typedef int                 BOOL;

template< typename type, int nsize > 
void ZERO( type (&data)[nsize])
{
	for (int i = 0; i < nsize; i++)
	{
		data[nsize] = 0;
	}
}

#endif







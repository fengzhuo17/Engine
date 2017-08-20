#ifndef ENG_TYPES
#define ENG_TYPES

#ifndef _WINDEF_

typedef char CHAR, BYTE, *PCHAR;
typedef unsigned char  UCHAR, *PUCHAR;

typedef long LONG;
typedef unsigned long DWORD;


typedef unsigned char BOOL;

typedef void *HANDLE;
typedef void *PVOID;
typedef short SHORT;
typedef short WORD ;

typedef struct _long64{

	DWORD low;
	DWORD hig;

}LONG64;

#endif

#ifndef NULL
#define NULL ( 0 )
#endif

#define TRUE   1
#define FALSE  0

#endif

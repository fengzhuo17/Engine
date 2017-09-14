#pragma once

#include "engtypes.h"

typedef struct _LogHead{ 
 
    DWORD size; 
    DWORD id; 
 
}LogHead; 
 
typedef struct _Parameter{ 
 
    HANDLE h; 
    DWORD cnt; 
 
}Parameter, *PPara; 


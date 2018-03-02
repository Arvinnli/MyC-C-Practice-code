#ifndef __STDFX_H
#define __STDFX_H

#if defined(c_plusplus)||defined(__cplusplus)
extern "C"{
#endif


#include <stdio.h>
#include <assert.h>
#include <windows.h>
// #include <st\
__FUNCTION__
#ifdef TRACE_INFO_SUPPORT
#define SCI_TRACE_LOW(...) \
printf("%s-%d ret %s(arg):",__FILE__,__LINE__,__FUNCTION__);printf(""__VA_ARGS__);printf("\n");
#else
#define SCI_TRACE_LOW(...)  
#endif






#if defined(c_plusplus)||defined(__cplusplus)
}
#endif

#endif //end of file
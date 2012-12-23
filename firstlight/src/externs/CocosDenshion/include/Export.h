#ifndef __EXPORT_COMMON__
#define __EXPORT_COMMON__

#define IGNORE_EXPORT

#if defined(_WIN32)
    #if defined(_EXPORT_DLL_)
    #define EXPORT_DLL     __declspec(dllexport)
    #elif defined(IGNORE_EXPORT)
    #define EXPORT_DLL
    #else 		/* use a DLL library */
    #define EXPORT_DLL     __declspec(dllimport)
    #endif
#else
    #if defined(_SHARED_)
    #define EXPORT_DLL     __attribute__((visibility("default")))
    #elif defined(IGNORE_EXPORT)
    #define EXPORT_DLL
    #else
    #define EXPORT_DLL
    #endif
#endif 

#endif	// end of __EXPORT_COMMON__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBK811FN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBK811FN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBK811FN_EXPORTS
#define LIBK811FN_API __declspec(dllexport)
#else
#define LIBK811FN_API __declspec(dllimport)
#endif

namespace K811fn {
	extern "C" LIBK811FN_API bool setNormal(void);
	extern "C" LIBK811FN_API bool setSpecial(void);
}



// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

#ifdef _DEBUG
#	pragma comment(lib, "UtilsHelperD.lib")
#	pragma comment(lib, "ProviderHelperD.lib")
#else
#	pragma comment(lib, "UtilsHelper.lib")
#	pragma comment(lib, "ProviderHelper.lib")
#endif

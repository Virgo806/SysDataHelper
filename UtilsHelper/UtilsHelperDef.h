#ifndef _H_UTILSHELPERDEF_H_
#define _H_UTILSHELPERDEF_H_
#pragma once
#include <string>

#ifdef UTILSHELPER_EXPORTS
#	define UTILSHELPER_API __declspec(dllexport)
#else
#	define UTILSHELPER_API __declspec(dllimport)
#endif

#ifndef UH_SAFE_DELETE
#	define UH_SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#endif // UH_SAFE_DELETE

#ifndef UH_SAFE_DELETE_ARRAY
#	define UH_SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#endif // UH_SAFE_DELETE_ARRAY

#define MAX_LOGS_BUF 1024 * 8 // 日志输出最大缓存

#endif // _H_UTILSHELPERDEF_H_

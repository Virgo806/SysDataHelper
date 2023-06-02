#ifndef _H_UTILSHELPER_H_
#define _H_UTILSHELPER_H_
#pragma once
#include "ThreadEx.h"
#include "LoopingBuffer.h"
#include "ListEx.h"

namespace UtilsHelper
{
#ifdef __cplusplus
	extern "C" {
#endif
		/*
		 * 功能：日志信息
		 * 参数：i_pchFormat | 参数
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsInfo(IN const char* pchFormat, ...);

		/*
		 * 功能：调试信息
		 * 参数：i_pchFormat | 参数
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsDebug(IN const char* pchFormat, ...);

		/*
		 * 功能：警告日志
		 * 参数：i_pchFormat | 参数
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsWarn(IN const char* pchFormat, ...);

		/*
		 * 功能：错误日志
		 * 参数：i_pchFormat | 参数
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsError(IN const char* pchFormat, ...);

		/*
		 * 功能：数据日志
		 * 参数：puchData | 数据缓存
		 *       nSize | 数据大小
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * 功能：接收数据日志
		 * 参数：puchData | 数据缓存
		 *       nSize | 数据大小
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsRecvHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * 功能：发送数据日志
		 * 参数：puchData | 数据缓存
		 *       nSize | 数据大小
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsSendHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * 功能：日志写磁盘
		 * 参数：void
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI LogsWriteDisk();

		/*
		 * 功能：获取程序运行路径
		 * 参数：sPath - 路径
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI GetAppsPath(OUT std::string& sPath);

		/*
		 * 功能：获取程序名称
		 * 参数：sName - 应用程序名称
		 *       i_bIsExtend - 是否带扩展名
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI GetAppsName(OUT std::string& sName, IN bool bIsExtend = false);

		/*
		 * 功能：获取程序版本
		 * 参数：o_pchVersions - 版本信息
		 *       io_nSize - 缓存大小
		 *       i_pchName - 程序名称
		 * 返回：TRUE - 成功，FALSE - 失败
		 */
		UTILSHELPER_API BOOL WINAPI GetAppsVersion(OUT std::string& sVersion, IN std::string sName = "");

		/*
		 * 功能：读取INI
		 * 参数：sSec - 项
		 *       sKey - 键
		 *       sDef - 默认值
		 *       sFile - 文件
		 *		 sValue - 值
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI ReadIniKey(IN std::string sSec, IN std::string sKey, IN std::string sDef, IN std::string sFile, OUT std::string& sValue);

		/*
		 * 功能：写入INI
		 * 参数：sSec - 项
		 *       sKey - 键
		 *       sVal - 值
		 *       sFile - 文件
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI WriteIniKey(IN std::string sSec, IN std::string sKey, IN std::string sVal, IN std::string sFile);

		/*
		 * 功能：临界锁
		 * 参数：pcsObj - 对象
		 * 返回：void
		 */
		UTILSHELPER_API void WINAPI CriticalLock(IN CCriticalSection* pcsObj);

		/*
		 * 功能：验证并创建目录
		 * 参数：sDirectory - 目录
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI MakeSureDirectory(IN std::string sDirectory);

		/*
		 * 功能：提取文件信息
		 * 参数：sFile - 文件全路径
		 *       sName - 文件名
		 *       sExtend - 扩展名
		 *       sPath - 路径
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI ExtractFile(IN std::string sFile, OUT std::string &sName, OUT std::string &sExtend, OUT std::string &sPath);

		/*
		 * 功能：获取文件夹剩余空间
		 * 参数：sFloder - 文件夹
		 * *     dFreeSpace - 剩余空间，单位：MB
		 * 返回：true - 成功，false - 失败
		 */
		UTILSHELPER_API bool WINAPI GetFolderFreeSpace(IN std::string sFloder, OUT double &dFreeSpace);
#ifdef __cplusplus
	}
#endif
}
#endif // _H_UTILSHELPER_H_

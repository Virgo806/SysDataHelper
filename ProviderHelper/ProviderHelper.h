#ifndef _H_PROVIDERHELPER_H_
#define _H_PROVIDERHELPER_H_
#pragma once
#include "ProviderDefine.h"

namespace ProviderHelper
{
#ifdef __cplusplus
	extern "C" {
#endif
		/*
		 * 功能：创建MYSQL实例
		 * 参数：pObjSet - 数据对象
		 *		 sHost - 主机
		 *       nPort - 端口
		 *		 sDBName - 数据库名
		 *       sUser - 用户
		 *       sPass - 密码
		 * 返回：ture - 成功 | false - 失败
		 */
		PROVIDERHELPER_API bool WINAPI CreateDataProviderMySQL(IDataObjectSetPtr& pObjSet, std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass);

		/*
		 * 功能：创建SQLITE实例
		 * 参数：pObjSet - 数据对象
		 *		 sDBName - 数据库名
		 * 返回：ture - 成功 | false - 失败
		 */
		PROVIDERHELPER_API bool WINAPI CreateDataProviderSQLite(IDataObjectSetPtr& pObjSet, std::string sDBName);

#ifdef __cplusplus
	}
#endif
}
#endif // _H_PROVIDERHELPER_H_

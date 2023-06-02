#ifndef _H_SYSDATADEFINE_H_
#define _H_SYSDATADEFINE_H_
#pragma once

#ifdef SYSDATAHELPER_EXPORTS
#	define SYSDATAHELPER_API __declspec(dllexport)
#else
#	define SYSDATAHELPER_API __declspec(dllimport)
#endif

namespace SysDataHelper
{
	// 支持数据库类型
	typedef enum E_DATABSE_TYPE
	{
		E_DATABSE_TYPE_NONE = 0, // 未知
		E_DATABSE_TYPE_MYSQL, // MySQL数据库
	}eDatabaseType;

	// 执行结果
	typedef enum E_EXEC_SQL
	{
		E_EXEC_SQL_FAIL = 0, // 失败
		E_EXEC_SQL_SUCC = 1, // 成功
	}eExecSQL;
}
#endif // _H_SYSDATADEFINE_H_
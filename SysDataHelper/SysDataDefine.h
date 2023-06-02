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
	// ֧�����ݿ�����
	typedef enum E_DATABSE_TYPE
	{
		E_DATABSE_TYPE_NONE = 0, // δ֪
		E_DATABSE_TYPE_MYSQL, // MySQL���ݿ�
	}eDatabaseType;

	// ִ�н��
	typedef enum E_EXEC_SQL
	{
		E_EXEC_SQL_FAIL = 0, // ʧ��
		E_EXEC_SQL_SUCC = 1, // �ɹ�
	}eExecSQL;
}
#endif // _H_SYSDATADEFINE_H_
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
		 * ���ܣ�����MYSQLʵ��
		 * ������pObjSet - ���ݶ���
		 *		 sHost - ����
		 *       nPort - �˿�
		 *		 sDBName - ���ݿ���
		 *       sUser - �û�
		 *       sPass - ����
		 * ���أ�ture - �ɹ� | false - ʧ��
		 */
		PROVIDERHELPER_API bool WINAPI CreateDataProviderMySQL(IDataObjectSetPtr& pObjSet, std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass);

		/*
		 * ���ܣ�����SQLITEʵ��
		 * ������pObjSet - ���ݶ���
		 *		 sDBName - ���ݿ���
		 * ���أ�ture - �ɹ� | false - ʧ��
		 */
		PROVIDERHELPER_API bool WINAPI CreateDataProviderSQLite(IDataObjectSetPtr& pObjSet, std::string sDBName);

#ifdef __cplusplus
	}
#endif
}
#endif // _H_PROVIDERHELPER_H_

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
		 * ���ܣ���־��Ϣ
		 * ������i_pchFormat | ����
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsInfo(IN const char* pchFormat, ...);

		/*
		 * ���ܣ�������Ϣ
		 * ������i_pchFormat | ����
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsDebug(IN const char* pchFormat, ...);

		/*
		 * ���ܣ�������־
		 * ������i_pchFormat | ����
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsWarn(IN const char* pchFormat, ...);

		/*
		 * ���ܣ�������־
		 * ������i_pchFormat | ����
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsError(IN const char* pchFormat, ...);

		/*
		 * ���ܣ�������־
		 * ������puchData | ���ݻ���
		 *       nSize | ���ݴ�С
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * ���ܣ�����������־
		 * ������puchData | ���ݻ���
		 *       nSize | ���ݴ�С
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsRecvHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * ���ܣ�����������־
		 * ������puchData | ���ݻ���
		 *       nSize | ���ݴ�С
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsSendHexData(IN const unsigned char* puchData, IN int nSize);

		/*
		 * ���ܣ���־д����
		 * ������void
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI LogsWriteDisk();

		/*
		 * ���ܣ���ȡ��������·��
		 * ������sPath - ·��
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI GetAppsPath(OUT std::string& sPath);

		/*
		 * ���ܣ���ȡ��������
		 * ������sName - Ӧ�ó�������
		 *       i_bIsExtend - �Ƿ����չ��
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI GetAppsName(OUT std::string& sName, IN bool bIsExtend = false);

		/*
		 * ���ܣ���ȡ����汾
		 * ������o_pchVersions - �汾��Ϣ
		 *       io_nSize - �����С
		 *       i_pchName - ��������
		 * ���أ�TRUE - �ɹ���FALSE - ʧ��
		 */
		UTILSHELPER_API BOOL WINAPI GetAppsVersion(OUT std::string& sVersion, IN std::string sName = "");

		/*
		 * ���ܣ���ȡINI
		 * ������sSec - ��
		 *       sKey - ��
		 *       sDef - Ĭ��ֵ
		 *       sFile - �ļ�
		 *		 sValue - ֵ
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI ReadIniKey(IN std::string sSec, IN std::string sKey, IN std::string sDef, IN std::string sFile, OUT std::string& sValue);

		/*
		 * ���ܣ�д��INI
		 * ������sSec - ��
		 *       sKey - ��
		 *       sVal - ֵ
		 *       sFile - �ļ�
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI WriteIniKey(IN std::string sSec, IN std::string sKey, IN std::string sVal, IN std::string sFile);

		/*
		 * ���ܣ��ٽ���
		 * ������pcsObj - ����
		 * ���أ�void
		 */
		UTILSHELPER_API void WINAPI CriticalLock(IN CCriticalSection* pcsObj);

		/*
		 * ���ܣ���֤������Ŀ¼
		 * ������sDirectory - Ŀ¼
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI MakeSureDirectory(IN std::string sDirectory);

		/*
		 * ���ܣ���ȡ�ļ���Ϣ
		 * ������sFile - �ļ�ȫ·��
		 *       sName - �ļ���
		 *       sExtend - ��չ��
		 *       sPath - ·��
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI ExtractFile(IN std::string sFile, OUT std::string &sName, OUT std::string &sExtend, OUT std::string &sPath);

		/*
		 * ���ܣ���ȡ�ļ���ʣ��ռ�
		 * ������sFloder - �ļ���
		 * *     dFreeSpace - ʣ��ռ䣬��λ��MB
		 * ���أ�true - �ɹ���false - ʧ��
		 */
		UTILSHELPER_API bool WINAPI GetFolderFreeSpace(IN std::string sFloder, OUT double &dFreeSpace);
#ifdef __cplusplus
	}
#endif
}
#endif // _H_UTILSHELPER_H_

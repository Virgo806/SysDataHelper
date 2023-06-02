#ifndef _H_SYSDATAHELPER_H_
#define _H_SYSDATAHELPER_H_
#pragma once
#include "SysDataDefine.h"
#include "TableInc.h"

namespace SysDataHelper
{
	class SYSDATAHELPER_API CSysDataHelper
	{
	public:
		CSysDataHelper();
		virtual ~CSysDataHelper();

		// �������ݿ�
		bool Connection(string sHost, int nPort, string sDBName, string sUser, string sPass, eDatabaseType edType = E_DATABSE_TYPE_NONE);
		// �Ͽ����ݿ�
		bool Disconnect(void);
		// ���ݿ��Ƿ�����
		bool IsConnect(void);
		// �޸���
		bool RepaireTable(string sTabName);
		// �Ż���
		bool OptimizeTable(string sTabName);

		///////////////////////tab_user/////////////////////////////////
		int InsterUserRecord(const CTabUserRecordPtr recUser, bool bReturnID = false);
		bool UpdateUserRecord(const CTabUserRecordPtr recUser);
		bool DeleteUserRecord(int nID);

		CTabUserRecordPtr GetUserRecordByID(int nID);
		CTabUserRecordPtr GetUserRecordByName(string sName);
		CTabUserRecordVec GetAllUserRecordToVec(void);
		CTabUserRecordMap GetAllUserRecordToMap(void);

		bool IsExistUserName(int nID, string sName);
		///////////////////////tab_user/////////////////////////////////

	protected:
		bool OnExecSQL(CString strSQL);
		bool OnExecQuery(CString strSQL, ProviderHelper::IDataRecordSetPtr& pRecSet);
		int OnGetMaxRecordID(CString strTabName, CString strField);

	private:
		ProviderHelper::IDataObjectSetPtr m_pObjectSet;
	};
}
#endif // _H_SYSDATAHELPER_H_
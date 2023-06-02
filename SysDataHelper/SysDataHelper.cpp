#include "pch.h"
#include "SysDataHelper.h"

namespace SysDataHelper
{
	CSysDataHelper::CSysDataHelper()
	{
	}

	CSysDataHelper::~CSysDataHelper()
	{
		Disconnect();
	}

	bool CSysDataHelper::Connection(std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass, eDatabaseType edType /*= E_DATABSE_TYPE_NONE*/)
	{
		if (E_DATABSE_TYPE_NONE == edType)
		{
			UtilsHelper::LogsWarn("[%s:%d]数据库类型错误。", __FUNCTION__, __LINE__);
			return false;
		}

		if (E_DATABSE_TYPE_MYSQL == edType)
		{
			if (m_pObjectSet.get())
			{
				if (m_pObjectSet->IsConnection())
				{
					UtilsHelper::LogsDebug("[%s:%d]数据库已经连接。", __FUNCTION__, __LINE__);
					return true;
				}
			}

			if (CreateDataProviderMySQL(m_pObjectSet, sHost, nPort, sDBName, sUser, sPass))
			{
				UtilsHelper::LogsDebug("[%s:%d]连接MySQL数据库成功，参数<%s, %d, %s, %s, %s>", __FUNCTION__, __LINE__, sHost.c_str(), nPort, sDBName.c_str(), sUser.c_str(), sPass.c_str());
			}
			else
			{
				UtilsHelper::LogsError("[%s:%d]连接MySQL数据库失败，参数<%s, %d, %s, %s, %s>", __FUNCTION__, __LINE__, sHost.c_str(), nPort, sDBName.c_str(), sUser.c_str(), sPass.c_str());
				return false;
			}
		}
		else
		{
			UtilsHelper::LogsWarn("[%s:%d]不支持的数据库类型。", __FUNCTION__, __LINE__);
			return false;
		}

		return true;
	}

	bool CSysDataHelper::Disconnect(void)
	{
		if (NULL == m_pObjectSet.get())
		{
			UtilsHelper::LogsDebug("[%s:%d]数据库未连接。", __FUNCTION__, __LINE__);
			return false;
		}

		if (!m_pObjectSet->Disconnect())
		{
			UtilsHelper::LogsError("[%s:%d]断开MySQL数据库失败。", __FUNCTION__, __LINE__);
			return false;
		}
		else
			UtilsHelper::LogsDebug("[%s:%d]断开MySQL数据库成功。", __FUNCTION__, __LINE__);
			return true;
	}

	bool CSysDataHelper::IsConnect(void)
	{
		if (NULL == m_pObjectSet.get())
			return false;
		
		return m_pObjectSet->IsConnection();
	}

	bool CSysDataHelper::RepaireTable(string sTabName)
	{
		if (sTabName.empty())
		{
			UtilsHelper::LogsWarn("[%s:d]表名参数不能为空。", __FUNCTION__, __LINE__);
			return false;
		}

		if (!IsConnect())
		{
			UtilsHelper::LogsWarn("[%s:d]数据库未连接。", __FUNCTION__, __LINE__);
			return false;
		}

		CString strSQL = "";
		strSQL.Format("REPAIR TABLE %s USE_FRM", sTabName.c_str());

		string sSQL = "";
		sSQL.assign((char*)(LPCTSTR)strSQL, strSQL.GetLength());
		if (m_pObjectSet->Execute(sSQL))
		{
			UtilsHelper::LogsDebug("[%s:%d]修复数据表<%s>成功。", __FUNCTION__, __LINE__, sTabName.c_str());
		}
		else
		{
			UtilsHelper::LogsError("[%s:%d]修复数据表<%s>失败。", __FUNCTION__, __LINE__, sTabName.c_str());
			return false;
		}
		
		return true;
	}

	bool CSysDataHelper::OptimizeTable(string sTabName)
	{
		if (sTabName.empty())
		{
			UtilsHelper::LogsWarn("[%s:d]表名参数不能为空。", __FUNCTION__, __LINE__);
			return false;
		}

		if (!IsConnect())
		{
			UtilsHelper::LogsWarn("[%s:d]数据库未连接。", __FUNCTION__, __LINE__);
			return false;
		}

		CString strSQL = "";
		strSQL.Format("OPTIMIZE TABLE %s", sTabName.c_str());

		string sSQL = "";
		sSQL.assign((char*)(LPCTSTR)strSQL, strSQL.GetLength());
		if (m_pObjectSet->Execute(sSQL))
		{
			UtilsHelper::LogsDebug("[%s:%d]优化数据表<%s>成功。", __FUNCTION__, __LINE__, sTabName.c_str());
		}
		else
		{
			UtilsHelper::LogsError("[%s:%d]优化数据表<%s>失败。", __FUNCTION__, __LINE__, sTabName.c_str());
			return false;
		}

		return true;
	}

	int CSysDataHelper::InsterUserRecord(const CTabUserRecordPtr recUser, bool bReturnID /*= false*/)
	{
		if (!recUser.get())
			return E_EXEC_SQL_FAIL;
		
		CString strSQL = "";
		strSQL.Format("INSERT INTO tab_user(user_name, user_pw, role_id, level, unit_id, comment) VALUES('%s', '%s', %d, %d, %d, '%s')", 
			recUser->user_name.c_str(), recUser->user_pw.c_str(), recUser->role_id, recUser->level, recUser->unit_id, recUser->comment.c_str());

		if (OnExecSQL(strSQL))
		{
			if (bReturnID)
				return OnGetMaxRecordID("tab_user", "user_id");
		}
		else
			return E_EXEC_SQL_FAIL;

		return E_EXEC_SQL_SUCC;
	}

	bool CSysDataHelper::UpdateUserRecord(const CTabUserRecordPtr recUser)
	{
		if (!recUser.get())
			return E_EXEC_SQL_FAIL;

		CString strSQL = "";
		strSQL.Format("UPDATE tab_user SET user_name = '%s', user_pw = '%s', role_id = %d, level = %d, unit_id = %d, comment = '%s' WHERE user_id = %d",
			recUser->user_name.c_str(), recUser->user_pw.c_str(), recUser->role_id, recUser->level, recUser->unit_id, recUser->comment.c_str(), recUser->user_id);

		if (!OnExecSQL(strSQL))
			return E_EXEC_SQL_FAIL;

		return E_EXEC_SQL_SUCC;
	}

	bool CSysDataHelper::DeleteUserRecord(int nID)
	{
		CString strSQL = "";
		strSQL.Format("DELETE FROM tab_user WHERE user_id = %d", nID);

		if (!OnExecSQL(strSQL))
			return E_EXEC_SQL_FAIL;

		return E_EXEC_SQL_SUCC;
	}

	CTabUserRecordPtr CSysDataHelper::GetUserRecordByID(int nID)
	{
		CTabUserRecordPtr pUserRec;
		CString strSQL = "";
		strSQL.Format("SELECT * FROM tab_user WHERE user_id = %d", nID);

		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			if (pRecSet->GetRecordCount() > 0)
			{
				pRecSet->MoveFirst();
				pUserRec.reset(new CTabUserRecord);
				pUserRec->SetContent(pRecSet);
			}
			pRecSet->CloseRecord();
		}
		
		return pUserRec;
	}

	CTabUserRecordPtr CSysDataHelper::GetUserRecordByName(string sName)
	{
		CTabUserRecordPtr pUserRec;
		CString strSQL = "";
		strSQL.Format("SELECT * FROM tab_user WHERE user_name = '%s'", sName.c_str());

		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			if (pRecSet->GetRecordCount() > 0)
			{
				pRecSet->MoveFirst();
				pUserRec.reset(new CTabUserRecord);
				pUserRec->SetContent(pRecSet);
			}
			pRecSet->CloseRecord();
		}

		return pUserRec;
	}

	CTabUserRecordVec CSysDataHelper::GetAllUserRecordToVec(void)
	{
		CTabUserRecordVec vecUser;
		CString strSQL = "SELECT * FROM tab_user ORDER BY user_id";

		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			pRecSet->MoveFirst();
			while (!pRecSet->IsEof())
			{
				CTabUserRecordPtr pRec(new CTabUserRecord);
				pRec->SetContent(pRecSet);
				vecUser.push_back(pRec);
				pRecSet->MoveNext();
			}
			pRecSet->CloseRecord();
		}

		return vecUser;
	}

	CTabUserRecordMap CSysDataHelper::GetAllUserRecordToMap(void)
	{
		CTabUserRecordMap mapUser;
		CString strSQL = "SELECT * FROM tab_user ORDER BY user_id";

		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			pRecSet->MoveFirst();
			while (!pRecSet->IsEof())
			{
				CTabUserRecordPtr pRec(new CTabUserRecord);
				pRec->SetContent(pRecSet);
				mapUser.insert(make_pair(pRec->user_id, pRec));
				pRecSet->MoveNext();
			}
			pRecSet->CloseRecord();
		}

		return mapUser;
	}

	bool CSysDataHelper::IsExistUserName(int nID, string sName)
	{
		CTabUserRecordPtr pUserRec;
		CString strSQL = "";
		bool bRet = false;

		if (nID > 0)
			strSQL.Format("SELECT * FROM tab_user WHERE user_name = '%s'AND user_id <> %d", sName.c_str(), nID);
		else
			strSQL.Format("SELECT * FROM tab_user WHERE user_name = '%s'", sName.c_str());

		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			if (pRecSet->GetRecordCount() > 0)
				bRet = true;
			else
				bRet = false;
			pRecSet->CloseRecord();
		}

		return bRet;
	}

	bool CSysDataHelper::OnExecSQL(CString strSQL)
	{
		if (strSQL.IsEmpty())
			return false;
		
		if (IsConnect())
		{
			string sSQL = "";
			sSQL.assign((const char*)(LPCTSTR)strSQL, strSQL.GetLength());
			return m_pObjectSet->Execute(sSQL);
		}
		else
		{
			UtilsHelper::LogsWarn("[%s:d]数据库未连接。", __FUNCTION__, __LINE__);
			return false;
		}
	}

	bool CSysDataHelper::OnExecQuery(CString strSQL, ProviderHelper::IDataRecordSetPtr &pRecSet)
	{
		if (strSQL.IsEmpty())
			return false;

		if (IsConnect())
		{
			string sSQL = "";
			sSQL.assign((const char*)(LPCTSTR)strSQL, strSQL.GetLength());
			return m_pObjectSet->Execute(sSQL, pRecSet);
		}
		else
		{
			UtilsHelper::LogsWarn("[%s:d]数据库未连接。", __FUNCTION__, __LINE__);
			return false;
		}
	}

	int CSysDataHelper::OnGetMaxRecordID(CString strTabName, CString strField)
	{
		int nRetID = -1;
		CString strSQL = "";

		strSQL.Format("SELECT max(%s) AS ID FROM %s", strField, strTabName);
		ProviderHelper::IDataRecordSetPtr pRecSet;
		if (OnExecQuery(strSQL, pRecSet))
		{
			if (pRecSet->GetRecordCount() > 0)
			{
				pRecSet->MoveFirst();
				pRecSet->GetFieldValue("ID", nRetID);
			}
			pRecSet->CloseRecord();
		}

		return nRetID;
	}

}
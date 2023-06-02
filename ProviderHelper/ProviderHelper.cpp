#include "pch.h"
#include "ProviderHelper.h"
#include "DataObjectMysql.h"
#include "DataObjectSqlite.h"

namespace ProviderHelper
{
	PROVIDERHELPER_API bool WINAPI CreateDataProviderMySQL(IDataObjectSetPtr &pObjSet, std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass)
	{
		CDataObjectMysql* pObject = new CDataObjectMysql();
		if (NULL == pObject)
		{
			UtilsHelper::LogsError("Failure to create a database instance.");
			return false;
		}

		if (!pObject->Connection(sHost, nPort, sDBName, sUser, sPass))
			return false;

		pObjSet.reset(pObject);

		return true;
	}

	PROVIDERHELPER_API bool WINAPI CreateDataProviderSQLite(IDataObjectSetPtr& pObjSet, std::string sDBName)
	{
		CDataObjectSqlite* pObject = new CDataObjectSqlite();
		if (NULL == pObject)
		{
			UtilsHelper::LogsError("Failure to create a database instance.");
			return false;
		}

		std::string sPath = "";
		if (UtilsHelper::GetAppsPath(sPath))
		{
			if (!pObject->Connection(sPath + sDBName))
				return false;
		}
		else
		{
			UtilsHelper::LogsError("Failure to obtain a run path.");
			return false;
		}

		pObjSet.reset(pObject);

		return true;
	}

}

#ifndef _H_DATAOBJECTMYSQL_H_
#define _H_DATAOBJECTMYSQL_H_
#pragma once
#include "DataRecordMysql.h"

class CDataObjectMysql : public ProviderHelper::IDataObjectSet
{
public:
	CDataObjectMysql();
	virtual ~CDataObjectMysql();

	bool Connection(std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass);

	virtual bool Disconnect();
	virtual bool IsConnection();

	virtual bool IsExistTable(std::string sTable);
	virtual bool Execute(std::string sSQL);
	virtual bool Execute(std::string sSQL, ProviderHelper::IDataRecordSetPtr& pRecSet);

protected:
	// Çý¶¯ÊÇ·ñ´æÔÚ
	bool OnIsExistDirver(QString qsDriver);

private:
	QSqlDatabase m_qsDatabase;
};
#endif // _H_DATAOBJECTMYSQL_H_

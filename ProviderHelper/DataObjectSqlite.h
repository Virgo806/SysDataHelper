#ifndef _H_DATAOBJECTSQLITE_H_
#define _H_DATAOBJECTSQLITE_H_
#pragma once
#include "DataRecordSqlite.h"

class CDataObjectSqlite : public ProviderHelper::IDataObjectSet
{
public:
	CDataObjectSqlite();
	virtual ~CDataObjectSqlite();

	bool Connection(std::string sDbPath);

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

#endif // _H_DATAOBJECTSQLITE_H_

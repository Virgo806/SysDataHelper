#ifndef _H_DATARECORDSQLITE_H_
#define _H_DATARECORDSQLITE_H_
#pragma once
#include "ProviderDefine.h"
#include "QtPlugLib.h"

class CDataRecordSqlite : public ProviderHelper::IDataRecordSet
{
public:
	CDataRecordSqlite(QSqlDatabase* pqsDB);
	virtual ~CDataRecordSqlite(void);

	virtual bool GetFieldValue(int nIndex, int& nValue);
	virtual bool GetFieldValue(std::string sField, int& nValue);
	virtual bool GetFieldValue(int nIndex, unsigned int& unValue);
	virtual bool GetFieldValue(std::string sField, unsigned int& unValue);
	virtual bool GetFieldValue(int nIndex, bool& bValue);
	virtual bool GetFieldValue(std::string sField, bool& bValue);
	virtual bool GetFieldValue(int nIndex, float& fValue);
	virtual bool GetFieldValue(std::string sField, float& fValue);
	virtual bool GetFieldValue(int nIndex, double& dValue);
	virtual bool GetFieldValue(std::string sField, double& dValue);
	virtual bool GetFieldValue(int nIndex, std::string& sValue);
	virtual bool GetFieldValue(std::string sField, std::string& sValue);

	virtual int GetRecordCount();
	virtual bool IsEof();
	virtual bool MoveFirst();
	virtual bool MoveLast();
	virtual bool MovePrev();
	virtual bool MoveNext();
	virtual bool SetSeek(int nRow, bool bIsCurPos = false);

	virtual bool IsFieldNull(int nIndex);
	virtual bool IsFieldNull(std::string sField);

	virtual bool IsActive();
	virtual void CloseRecord();

	bool ExecuteSQL(std::string sSQL);

protected:
	bool OnIsOpenDatabase();
	bool OnIsValidField(int nField, QVariant& qVar);
	bool OnIsValidField(std::string sField, QVariant& qVar);

private:
	QSqlQuery m_qsQuery;
	QSqlDatabase* m_pqsDatabase;
	int m_nRows;
	int m_nTotalRows;
	bool m_bIsHasQuerySize;
};

#endif // _H_DATARECORDSQLITE_H_

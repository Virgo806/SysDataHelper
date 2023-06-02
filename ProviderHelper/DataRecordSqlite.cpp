#include "pch.h"
#include "DataRecordSqlite.h"

CDataRecordSqlite::CDataRecordSqlite(QSqlDatabase* pqsDB) :
	m_pqsDatabase(pqsDB),
	m_nRows(0),
	m_nTotalRows(0)
{
	m_bIsHasQuerySize = pqsDB->driver()->hasFeature(QSqlDriver::QuerySize);
	m_qsQuery = QSqlQuery(*pqsDB);
}

CDataRecordSqlite::~CDataRecordSqlite()
{
	CloseRecord();
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, int& nValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	nValue = qVar.toInt();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, int& nValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	nValue = qVar.toInt();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, unsigned int& unValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	unValue = qVar.toUInt();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, unsigned int& unValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	unValue = qVar.toUInt();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, bool& bValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	bValue = qVar.toBool();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, bool& bValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	bValue = qVar.toBool();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, float& fValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	fValue = qVar.toFloat();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, float& fValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	fValue = qVar.toFloat();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, double& dValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	dValue = qVar.toDouble();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, double& dValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	dValue = qVar.toDouble();
	return true;
}

bool CDataRecordSqlite::GetFieldValue(int nIndex, std::string& sValue)
{
	QVariant qVar;

	if (!OnIsValidField(nIndex, qVar))
		return false;

	sValue.append(qVar.toString().toLocal8Bit().data());
	return true;
}

bool CDataRecordSqlite::GetFieldValue(std::string sField, std::string& sValue)
{
	QVariant qVar;

	if (!OnIsValidField(sField, qVar))
		return false;

	sValue.append(qVar.toString().toLocal8Bit().data());
	return true;
}

int CDataRecordSqlite::GetRecordCount()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return 0;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return 0;
	}

	return m_nTotalRows;
}

bool CDataRecordSqlite::IsEof()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return true;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return true;
	}

	return m_nRows >= m_nTotalRows ? true : false;
}

bool CDataRecordSqlite::MoveFirst()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	m_nRows = 0;
	return m_qsQuery.first();
}

bool CDataRecordSqlite::MoveLast()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	m_nRows = m_nTotalRows; - 1;
	return m_qsQuery.last();
}

bool CDataRecordSqlite::MovePrev()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	m_nRows -= 1;
	if (m_nRows < 0)
		m_nRows = 0;
	return m_qsQuery.previous();
}

bool CDataRecordSqlite::MoveNext()
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	m_nRows += 1;
	if (m_nRows >= m_nTotalRows)
		m_nRows = m_nTotalRows;
	return m_qsQuery.next();
}

bool CDataRecordSqlite::SetSeek(int nRow, bool bIsCurPos /*= false*/)
{
	if (nRow <= 0 || nRow > GetRecordCount())
	{
		UtilsHelper::LogsError("Set seek rows Invalid.");
		return false;
	}

	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	if (bIsCurPos)
		m_nRows += nRow;
	else
		m_nRows = nRow - 1;

	if (m_nRows < 0)
		m_nRows = 0;
	if (m_nRows >= m_nTotalRows)
		m_nRows = m_nTotalRows - 1;
	return m_qsQuery.seek(nRow, bIsCurPos);
}

bool CDataRecordSqlite::IsFieldNull(int nIndex)
{
	QVariant qVar;
	return OnIsValidField(nIndex, qVar);
}

bool CDataRecordSqlite::IsFieldNull(std::string sField)
{
	QVariant qVar;
	return OnIsValidField(sField, qVar);
}

bool CDataRecordSqlite::IsActive()
{
	return m_qsQuery.isActive();
}

void CDataRecordSqlite::CloseRecord()
{
	if (IsActive())
	{
		m_qsQuery.clear();
		m_qsQuery.finish();
	}
}

bool CDataRecordSqlite::ExecuteSQL(std::string sSQL)
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if (m_qsQuery.exec(QString::fromLocal8Bit(sSQL.c_str(), sSQL.length())))
	{
		if (m_bIsHasQuerySize)
		{
			m_nTotalRows = m_qsQuery.size();
		}
		else
		{
			while (m_qsQuery.next())
			{
				m_nTotalRows += 1;
			}
		}
	}
	else
		return false;

	return true;
}

bool CDataRecordSqlite::OnIsOpenDatabase()
{
	if (m_pqsDatabase)
		return m_pqsDatabase->isOpen();

	return false;
}

bool CDataRecordSqlite::OnIsValidField(int nField, QVariant& qVar)
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	if (m_qsQuery.isNull(nField))
	{
		UtilsHelper::LogsError("Recordset field index invalid.");
		return false;
	}

	qVar = m_qsQuery.value(nField);
	if (!qVar.isValid())
	{
		UtilsHelper::LogsError("Recordset field value invalid.");
		return false;
	}

	return true;
}

bool CDataRecordSqlite::OnIsValidField(std::string sField, QVariant& qVar)
{
	if (!OnIsOpenDatabase())
	{
		UtilsHelper::LogsError("Database not connected.");
		return false;
	}

	if ((!IsActive()))
	{
		UtilsHelper::LogsError("Database Recordset Invalid.");
		return false;
	}

	qVar = m_qsQuery.value(QString::fromStdString(sField));
	if (!qVar.isValid())
	{
		UtilsHelper::LogsError("Recordset field value invalid.");
		return false;
	}

	return true;
}

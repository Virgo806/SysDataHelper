#include "pch.h"
#include "DataObjectSqlite.h"

CDataObjectSqlite::CDataObjectSqlite()
{

}

CDataObjectSqlite::~CDataObjectSqlite()
{
	Disconnect();
}

bool CDataObjectSqlite::Connection(std::string sDbPath)
{
	QString qsDriver = "QSQLITE";

	// 检查输入参数
	if (sDbPath.empty())
	{
		UtilsHelper::LogsWarn("Connect provider parameter error.");
		return false;
	}

	// 检测数据库驱动
	if (!OnIsExistDirver(qsDriver))
	{
		UtilsHelper::LogsWarn("SQLite database driver does not exist.");
		return false;
	}

	// 加载SQLite驱动
	QString qsConnect = QString::asprintf("SQLite<%d>", this);
	m_qsDatabase = QSqlDatabase::addDatabase(qsDriver, qsConnect);

	// 设置数据库链接参数
	m_qsDatabase.setDatabaseName(QString::fromStdString(sDbPath));

	// 打开数据库链接
	if (!m_qsDatabase.open())
	{
		UtilsHelper::LogsError("Connect SQLite database failed.");
		return false;
	}

	UtilsHelper::LogsDebug("Connect SQLite database successful.");
	return true;
}

bool CDataObjectSqlite::Disconnect()
{
	QString qsDriver = "QSQLITE";

	if (m_qsDatabase.isOpen())
	{
		m_qsDatabase.close();
		QSqlDatabase::removeDatabase(qsDriver);
	}

	return true;
}

bool CDataObjectSqlite::IsConnection()
{
	return m_qsDatabase.isOpen();
}

bool CDataObjectSqlite::IsExistTable(std::string sTable)
{
	if (!IsConnection())
		return false;

	QString qsSQL = QString("SELECT * FROM %1").arg(sTable.c_str());
	CDataRecordSqlite drRecord(&m_qsDatabase);

	return drRecord.ExecuteSQL(qsSQL.toStdString());
}

bool CDataObjectSqlite::Execute(std::string sSQL)
{
	if (!IsConnection())
		return false;

	CDataRecordSqlite drRecord(&m_qsDatabase);
	return drRecord.ExecuteSQL(sSQL);
}

bool CDataObjectSqlite::Execute(std::string sSQL, ProviderHelper::IDataRecordSetPtr& pRecSet)
{
	if (!IsConnection())
		return false;

	CDataRecordSqlite* pdrRecord = new CDataRecordSqlite(&m_qsDatabase);
	if (NULL == pdrRecord)
		return false;

	if (pdrRecord->ExecuteSQL(sSQL))
	{
		pRecSet.reset(pdrRecord);
		return true;
	}

	return false;
}

bool CDataObjectSqlite::OnIsExistDirver(QString qsDriver)
{
	QStringList qslDriList = QSqlDatabase::drivers();
	foreach(QString qsDriItem, qslDriList)
	{
		if (0 == qsDriItem.compare(qsDriver, Qt::CaseInsensitive))
			return true;
	}
	return false;
}

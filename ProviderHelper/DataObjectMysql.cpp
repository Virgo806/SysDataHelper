#include "pch.h"
#include "DataObjectMysql.h"

CDataObjectMysql::CDataObjectMysql()
{

}

CDataObjectMysql::~CDataObjectMysql()
{
	Disconnect();
}

bool CDataObjectMysql::Connection(std::string sHost, int nPort, std::string sDBName, std::string sUser, std::string sPass)
{
	QString qsDriver = "QMYSQL";

	// 检查输入参数
	if (sHost.empty() || nPort <= 0 || sDBName.empty() || sUser.empty() || sPass.empty())
	{
		UtilsHelper::LogsWarn("Connect provider parameter error.");
		return false;
	}

	// 检测数据库驱动
	if (!OnIsExistDirver(qsDriver))
	{
		UtilsHelper::LogsWarn("MySQL database driver does not exist.");
		return false;
	}

	// 加载MySQL驱动
	QString qsConnect = QString::asprintf("MySQL<%d>", this);
	m_qsDatabase = QSqlDatabase::addDatabase(qsDriver, qsConnect);

	// 设置数据库链接参数
	m_qsDatabase.setHostName(QString::fromStdString(sHost));
	m_qsDatabase.setPort(nPort);
	m_qsDatabase.setDatabaseName(QString::fromStdString(sDBName));

	// 打开数据库链接
	if (!m_qsDatabase.open(QString::fromStdString(sUser), QString::fromStdString(sPass)))
	{
		UtilsHelper::LogsError("Connect MySQL database failed.");
		return false;
	}

	UtilsHelper::LogsDebug("Connect MySQL database successful.");
	return true;
}

bool CDataObjectMysql::Disconnect()
{
	QString qsDriver = "QMYSQL";

	if (m_qsDatabase.isOpen())
	{
		m_qsDatabase.close();
		QSqlDatabase::removeDatabase(qsDriver);
	}

	return true;
}

bool CDataObjectMysql::IsConnection()
{
	return m_qsDatabase.isOpen();
}

bool CDataObjectMysql::IsExistTable(std::string sTable)
{
	if (!IsConnection())
		return false;

	QString qsSQL = QString("SELECT COUNT(*) FROM %1").arg(sTable.c_str());
	CDataRecordMysql drRecord(&m_qsDatabase);

	return drRecord.ExecuteSQL(qsSQL.toStdString());
}

bool CDataObjectMysql::Execute(std::string sSQL)
{
	if (!IsConnection())
		return false;
	
	CDataRecordMysql drRecord(&m_qsDatabase);
	return drRecord.ExecuteSQL(sSQL);
}

bool CDataObjectMysql::Execute(std::string sSQL, ProviderHelper::IDataRecordSetPtr &pRecSet)
{
	if (!IsConnection())
		return false;

	CDataRecordMysql* pdrRecord = new CDataRecordMysql(&m_qsDatabase);
	if (NULL == pdrRecord)
		return false;
	
	if (pdrRecord->ExecuteSQL(sSQL))
	{
		pRecSet.reset(pdrRecord);
		return true;
	}

	return false;
}

bool CDataObjectMysql::OnIsExistDirver(QString qsDriver)
{
	QStringList qslDriList = QSqlDatabase::drivers();
	foreach(QString qsDriItem, qslDriList)
	{
		if (0 == qsDriItem.compare(qsDriver, Qt::CaseInsensitive))
			return true;
	}
	return false;
}

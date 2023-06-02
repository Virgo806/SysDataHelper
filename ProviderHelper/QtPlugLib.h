#ifndef _H_QTPLUGLIB_H_
#define _H_QTPLUGLIB_H_
#pragma once
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#ifdef _DEBUG
#	pragma comment(lib, "Qt5Cored.lib")
#	pragma comment(lib, "Qt5Sqld.lib")
#else
#	pragma comment(lib, "Qt5Core.lib")
#	pragma comment(lib, "Qt5Sql.lib")
#endif

#endif // _H_QTPLUGLIB_H_
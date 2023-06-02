#include "pch.h"
#include "UtilsHelper.h"
#include "OutputFunc.h"

namespace UtilsHelper
{
	UTILSHELPER_API void WINAPI LogsInfo(IN const char* pchFormat, ...)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 解析格式信息
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		try
		{
			va_list argptr;
			va_start(argptr, pchFormat);
			if (_vscprintf(pchFormat, argptr) >= MAX_LOGS_BUF)
			{
				int nFmtLen = (int)strlen(pchFormat);
				if (nFmtLen >= MAX_LOGS_BUF)
					memcpy_s(chLog, MAX_LOGS_BUF - 1, pchFormat, MAX_LOGS_BUF - 1);
			}
			else
				_vsnprintf_s(chLog, MAX_LOGS_BUF - 1, MAX_LOGS_BUF, pchFormat, argptr);
			va_end(argptr);
		}
		catch (...)
		{
			return;
		}

		// 输出信息
		string sLog = "";
		sLog.assign(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsDebug(IN const char* pchFormat, ...)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 解析格式信息
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		try
		{
			va_list argptr;
			va_start(argptr, pchFormat);
			if (_vscprintf(pchFormat, argptr) >= MAX_LOGS_BUF)
			{
				int nFmtLen = (int)strlen(pchFormat);
				if (nFmtLen >= MAX_LOGS_BUF)
					memcpy_s(chLog, MAX_LOGS_BUF - 1, pchFormat, MAX_LOGS_BUF - 1);
			}
			else
				_vsnprintf_s(chLog, MAX_LOGS_BUF - 1, MAX_LOGS_BUF, pchFormat, argptr);
			va_end(argptr);
		}
		catch (...)
		{
			return;
		}

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  DEBUG ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsWarn(IN const char* pchFormat, ...)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 解析格式信息
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		try
		{
			va_list argptr;
			va_start(argptr, pchFormat);
			if (_vscprintf(pchFormat, argptr) >= MAX_LOGS_BUF)
			{
				int nFmtLen = (int)strlen(pchFormat);
				if (nFmtLen >= MAX_LOGS_BUF)
					memcpy_s(chLog, MAX_LOGS_BUF - 1, pchFormat, MAX_LOGS_BUF - 1);
			}
			else
				_vsnprintf_s(chLog, MAX_LOGS_BUF - 1, MAX_LOGS_BUF, pchFormat, argptr);
			va_end(argptr);
		}
		catch (...)
		{
			return;
		}

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  WARN ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsError(IN const char* pchFormat, ...)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 解析格式信息
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		try
		{
			va_list argptr;
			va_start(argptr, pchFormat);
			if (_vscprintf(pchFormat, argptr) >= MAX_LOGS_BUF)
			{
				int nFmtLen = (int)strlen(pchFormat);
				if (nFmtLen >= MAX_LOGS_BUF)
					memcpy_s(chLog, MAX_LOGS_BUF - 1, pchFormat, MAX_LOGS_BUF - 1);
			}
			else
				_vsnprintf_s(chLog, MAX_LOGS_BUF - 1, MAX_LOGS_BUF, pchFormat, argptr);
			va_end(argptr);
		}
		catch (...)
		{
			return;
		}

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  ERROR ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsHexData(IN const unsigned char* puchData, IN int nSize)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 转换数据
		CString strPacket = "";
		CString strTemp = "";
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		for (int i = 0; i < nSize; i++)
		{
			strTemp.Format("%02X ", *(puchData + i));
			strPacket += strTemp;
		}
		int nLen = strPacket.GetLength() > MAX_LOGS_BUF ? (MAX_LOGS_BUF - (MAX_LOGS_BUF % 3)) : strPacket.GetLength();
		memcpy_s(chLog, MAX_LOGS_BUF, (const char*)(LPCTSTR)strPacket, nLen);

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  HEX ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsRecvHexData(IN const unsigned char* puchData, IN int nSize)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 转换数据
		CString strPacket = "";
		CString strTemp = "";
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		for (int i = 0; i < nSize; i++)
		{
			strTemp.Format("%02X ", *(puchData + i));
			strPacket += strTemp;
		}
		int nLen = strPacket.GetLength() > MAX_LOGS_BUF ? (MAX_LOGS_BUF - (MAX_LOGS_BUF % 3)) : strPacket.GetLength();
		memcpy_s(chLog, MAX_LOGS_BUF, (const char*)(LPCTSTR)strPacket, nLen);

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  RECV ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsSendHexData(IN const unsigned char* puchData, IN int nSize)
	{
		// 初始化控制台
		if (!COutputFunc::GetInstance()->GetConsoleInitState())
			COutputFunc::GetInstance()->InitConsole();

		// 转换数据
		CString strPacket = "";
		CString strTemp = "";
		TCHAR chLog[MAX_LOGS_BUF] = { 0 };
		for (int i = 0; i < nSize; i++)
		{
			strTemp.Format("%02X ", *(puchData + i));
			strPacket += strTemp;
		}
		int nLen = strPacket.GetLength() > MAX_LOGS_BUF ? (MAX_LOGS_BUF - (MAX_LOGS_BUF % 3)) : strPacket.GetLength();
		memcpy_s(chLog, MAX_LOGS_BUF, (const char*)(LPCTSTR)strPacket, nLen);

		// 获取输出时间
		SYSTEMTIME syTime;
		GetLocalTime(&syTime);
		char chDate[MAX_PATH];
		ZeroMemory(chDate, MAX_PATH);
		_snprintf_s(chDate, MAX_PATH, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d.%03d  SEND ", syTime.wYear, syTime.wMonth, syTime.wDay, syTime.wHour, syTime.wMinute, syTime.wSecond, syTime.wMilliseconds);

		// 输出信息
		string sLog = "";
		sLog.assign(chDate);
		sLog.append(chLog);
		sLog.append("\r\n");
		if (sLog.length() > 0)
		{
			if (COutputFunc::GetInstance()->GetConsoleOutState())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sLog.c_str(), (DWORD)sLog.length(), NULL, NULL);
			}
			if (COutputFunc::GetInstance()->GetLogFileOutState())
				COutputFunc::GetInstance()->WriteLogsToFile(sLog);
		}
	}

	UTILSHELPER_API void WINAPI LogsWriteDisk()
	{
		COutputFunc::GetInstance()->SaveLogsToDisk();
	}

	UTILSHELPER_API bool WINAPI GetAppsPath(OUT std::string& sPath)
	{
		sPath = COutputFunc::GetInstance()->GetRunPath();
		
		return sPath.empty() ? false : true;
	}

	UTILSHELPER_API bool WINAPI GetAppsName(OUT std::string& sName, IN bool bIsExtend /*= false*/)
	{
		sName = COutputFunc::GetInstance()->GetAppName(bIsExtend);

		return sName.empty() ? false : true;
	}

	UTILSHELPER_API BOOL WINAPI GetAppsVersion(OUT std::string& sVersion, IN std::string sName /*= ""*/)
	{
		sVersion = COutputFunc::GetInstance()->GetAppVersion(sName);

		return sVersion.empty() ? false : true;
	}

	UTILSHELPER_API bool WINAPI ReadIniKey(IN std::string sSec, IN std::string sKey, IN std::string sDef, IN std::string sFile, OUT std::string& sValue)
	{
		sValue =  COutputFunc::GetInstance()->ReadFileFromIni(sSec, sKey, sDef, sFile, false);

		return !sValue.empty();
	}

	UTILSHELPER_API void WINAPI WriteIniKey(IN std::string sSec, IN std::string sKey, IN std::string sVal, IN std::string sFile)
	{
		COutputFunc::GetInstance()->WriteFileToIni(sSec, sKey, sVal, sFile);
	}

	UTILSHELPER_API void WINAPI CriticalLock(IN CCriticalSection* pcsObj)
	{
		CSingleLock Lock(pcsObj, TRUE);
	}

	UTILSHELPER_API bool WINAPI MakeSureDirectory(IN std::string sDirectory)
	{
		if (sDirectory.empty())
			return false;

		if (!::PathIsDirectory(sDirectory.c_str()))
		{
			char chDirName[MAX_PATH] = { 0 };
			const char* pchDir = sDirectory.c_str();
			char* pchName = chDirName;

			while (*pchDir)
			{
				if (('\\' == *pchDir) || ('/' == *pchDir))
				{
					if (':' != *(pchDir - 1))
					{
						::CreateDirectory(chDirName, NULL);
					}
				}
				*pchName++ = *pchDir++;
				*pchName = '\0';
			}
			::CreateDirectory(chDirName, NULL);

			return ::PathIsDirectory(pchDir) ? true : false;
		}

		return true;
	}

	UTILSHELPER_API bool WINAPI ExtractFile(IN std::string sFile, OUT std::string& sName, OUT std::string& sExtend, OUT std::string& sPath)
	{
		if (sFile.empty())
			return false;
		
		// 提取文件信息
		TCHAR szName[MAX_PATH + 1] = { 0 };
		TCHAR szExtend[_MAX_EXT + 1] = { 0 };
		TCHAR szDirectory[MAX_PATH + 1] = { 0 };
		TCHAR szDrive[MAX_PATH + 1] = { 0 };
		_tsplitpath_s(sFile.c_str(), szDrive, MAX_PATH, szDirectory, MAX_PATH, szName, MAX_PATH, szExtend, _MAX_EXT);

		sName.assign(szName);
		sExtend.assign(szExtend);
		sPath.assign(szDrive);
		sPath.append(szDirectory);

		return true;
	}

	UTILSHELPER_API bool WINAPI GetFolderFreeSpace(IN std::string sFloder, OUT double& dFreeSpace)
	{
		if (sFloder.empty())
			return false;

		ULARGE_INTEGER nFree;
		nFree.QuadPart = -1;
		if (GetDiskFreeSpaceEx(sFloder.c_str(), &nFree, NULL, NULL) <= 0)
			return FALSE;

		dFreeSpace = (double)(nFree.QuadPart / (1024.0 * 1024.0));

		return true;
	}

}
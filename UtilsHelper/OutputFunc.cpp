#include "pch.h"
#include "OutputFunc.h"
#include "FastAccess.h"
#include "UtilsHelper.h"
#include "tlhelp32.h"

#pragma comment(lib, "version.lib")

COutputFunc* COutputFunc::m_pInstance = NULL;

COutputFunc* COutputFunc::GetInstance(void)
{
	if (NULL == m_pInstance)
		m_pInstance = new COutputFunc();

	return m_pInstance;
}

void COutputFunc::ReleaseInstance(void)
{
	if (m_pInstance)
		UH_SAFE_DELETE(m_pInstance);
}

string COutputFunc::GetRunPath(void)
{
	TCHAR szPath[MAX_PATH + 1] = { 0 };
	string sPath = "";

	GetModuleFileName(NULL, szPath, MAX_PATH);
	// 提取程序路径
	(_tcsrchr(szPath, '\\'))[1] = 0; //删除文件名，只获得路径字串
	sPath.assign(szPath);

	return sPath;
}

string COutputFunc::GetAppName(bool bIsExtend)
{
	TCHAR szPath[_MAX_PATH + 1] = { 0 };
	string sName = "";

	GetModuleFileName(NULL, szPath, _MAX_PATH);
	// 提取程序名、扩展名
	TCHAR szName[_MAX_PATH + 1] = { 0 };
	TCHAR szExtend[_MAX_EXT + 1] = { 0 };
	_tsplitpath_s(szPath, NULL, 0, NULL, 0, szName, _MAX_PATH, szExtend, _MAX_EXT);

	sName.assign(szName);

	if (bIsExtend)
		sName.append(szExtend);

	return sName;
}

std::string COutputFunc::GetAppVersion(string sName /*= ""*/)
{
	string sVers = "";

	if (sName.empty())
		sName = GetAppName(true);

	DWORD dwVerSize = 0;
	DWORD dwVerHwnd = 0;
	dwVerSize = GetFileVersionInfoSize(sName.c_str(), &dwVerHwnd);
	if (dwVerSize)
	{
		HANDLE hMem;
		LPVOID lpMem;
		unsigned int uiSize = 0;
		VS_FIXEDFILEINFO* pFileInfo;

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerSize);
		lpMem = GlobalLock(hMem);
		GetFileVersionInfo(sName.c_str(), dwVerHwnd, dwVerSize, lpMem);
		::VerQueryValue(lpMem, "\\", (void**)&pFileInfo, &uiSize);
		WORD wVer[4];
		wVer[0] = HIWORD(pFileInfo->dwProductVersionMS);
		wVer[1] = LOWORD(pFileInfo->dwProductVersionMS);
		wVer[2] = HIWORD(pFileInfo->dwProductVersionLS);
		wVer[3] = LOWORD(pFileInfo->dwProductVersionLS);

		char chBuf[64];
		ZeroMemory(chBuf, 64);
		_snprintf_s(chBuf, 64, 64, "Ver %d.%d.%d.%d", wVer[0], wVer[1], wVer[2], wVer[3]);
		sVers.assign(chBuf);

		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}

	return sVers;
}

void COutputFunc::InitConsole(void)
{
	if (m_bInitState)
		return;

	// 加载配置文件
	OnLoadConfige();
	m_bInitState = true;

	// 启动控制台
	if (!m_bConsoleOut)
		return;
	DWORD dwProID = GetRunProcessID(GetAppName(true));
	if (!AttachConsole(dwProID))
	{
		if (!AllocConsole())
		{
			m_bConsoleOut &= false;
			return;
		}
	}
	m_bConsoleOut &= true;

	// 控制按钮
	HWND hWnd = GetConsoleWindow();
	LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (!m_bMinEnable && !m_bMaxEnable)
		lStyle &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	else if (m_bMinEnable && !m_bMaxEnable)
		lStyle &= ~(WS_MAXIMIZEBOX);
	else if (!m_bMinEnable && m_bMaxEnable)
		lStyle &= ~(WS_MINIMIZEBOX);
	SetWindowLong(hWnd, GWL_STYLE, lStyle);
	if (!m_bExitEnable)
	{
		DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
		DrawMenuBar(GetConsoleWindow());
	}

	// 设置标题
	string sTitle = "";
	char chBuf[MAX_PATH];
	ZeroMemory(chBuf, MAX_PATH);
	_snprintf_s(chBuf, MAX_PATH, MAX_PATH, "%s", GetAppName(false).c_str());
	sTitle.assign(chBuf);
	SetConsoleTitle(sTitle.c_str());

	// 显示日志开始信息
	UtilsHelper::LogsInfo("================================Start New Log Record================================");
}

void COutputFunc::UnInitConsole(void)
{
	if (m_bInitState)
		FreeConsole();
}

string COutputFunc::ReadFileFromIni(string sApp, string sKey, string sDef, string sFile, bool bWrite /*= false*/)
{
	string sVal = "";
	char chVal[MAX_PATH];

	ZeroMemory(chVal, MAX_PATH);
	::GetPrivateProfileString(sApp.c_str(), sKey.c_str(), sDef.c_str(), chVal, MAX_PATH, sFile.c_str());
	sVal.assign(chVal);

	if (bWrite)
		WriteFileToIni(sApp, sKey, sDef, sFile);

	return sVal;
}

void COutputFunc::WriteFileToIni(string sApp, string sKey, string sVal, string sFile)
{
	::WritePrivateProfileString(sApp.c_str(), sKey.c_str(), sVal.c_str(), sFile.c_str());
}

void COutputFunc::WriteLogsToFile(string sLog)
{
	SYSTEMTIME syTime;
	string sFile = "";
	char chData[MAX_PATH];

	GetLocalTime(&syTime);
	ZeroMemory(chData, MAX_PATH);
	_snprintf_s(chData, MAX_PATH, MAX_PATH, "%sOutLogs(%04d%02d%02d).log", GetRunPath().c_str(), syTime.wYear, syTime.wMonth, syTime.wDay);
	sFile.assign(chData);

	if (!PathFileExists(sFile.c_str()))
	{
		if (m_pfLogs)
		{
			FastWrite::Close(m_pfLogs);
			m_pfLogs = NULL;
		}
	}

	if (NULL == m_pfLogs)
		m_pfLogs = FastWrite::Init(sFile);

	if (m_pfLogs)
		FastWrite::Write(sLog, m_pfLogs);
}

void COutputFunc::SaveLogsToDisk(void)
{
	if (m_pfLogs)
	{
		FastWrite::Close(m_pfLogs);
		m_pfLogs = NULL;
	}
}

DWORD COutputFunc::GetRunProcessID(string sProName)
{
	DWORD dwProID = 0;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return dwProID;

	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
	{
		if (0 == strcmp(pe.szExeFile, sProName.c_str()))
		{
			dwProID = pe.th32ProcessID;
			break;
		}
	}
	CloseHandle(hSnapshot);

	return dwProID;
}

COutputFunc::COutputFunc(void)
{
	m_bInitState = false; // 初始化状态
	m_bConsoleOut = true; // 输出控制台
	m_bLogFileOut = false; // 输出文件
	m_bMinEnable = false; // 最小化按钮
	m_bMaxEnable = false; // 最大化按钮
	m_bExitEnable = false; // 关闭按钮;

	m_pfLogs = NULL;
}

COutputFunc::~COutputFunc(void)
{
	SaveLogsToDisk();

	// 释放控制台
	UnInitConsole();
}

void COutputFunc::OnLoadConfige(void)
{
	char chFile[MAX_PATH];
	string sFile = "";
	string sVal = "";

	ZeroMemory(chFile, MAX_PATH);
	_snprintf_s(chFile, MAX_PATH, MAX_PATH, "%sDebugPara.ini", GetRunPath().c_str());
	sFile.assign(chFile);
	if (PathFileExists(chFile))
	{
		sVal = ReadFileFromIni("LogsParam", "OutConsole", "0", sFile);
		m_bConsoleOut = atoi(sVal.c_str()) > 0 ? true : false;
		sVal = ReadFileFromIni("LogsParam", "OutLogFile", "0", sFile);
		m_bLogFileOut = atoi(sVal.c_str()) > 0 ? true : false;
		sVal = ReadFileFromIni("ConsoleBtn", "MinEnable", "0", sFile);
		m_bMinEnable = atoi(sVal.c_str()) > 0 ? true : false;
		sVal = ReadFileFromIni("ConsoleBtn", "MaxEnable", "0", sFile);
		m_bMaxEnable = atoi(sVal.c_str()) > 0 ? true : false;
		sVal = ReadFileFromIni("ConsoleBtn", "ExitEnable", "0", sFile);
		m_bExitEnable = atoi(sVal.c_str()) > 0 ? true : false;
	}
	else
	{
		WriteFileToIni("LogsParam", ";控制台输出，1-输出，0-不输出\r\nOutConsole", "1", sFile);
		m_bConsoleOut = true;
		WriteFileToIni("LogsParam", ";日志文件输出，1-输出，0-不输出\r\nOutLogFile", "0", sFile);
		m_bLogFileOut = false;
		WriteFileToIni("ConsoleBtn", ";最小化禁用，1-不禁用，0-禁用\r\nMinEnable", "0", sFile);
		m_bMinEnable = false;
		WriteFileToIni("ConsoleBtn", ";最大化禁用，1-不禁用，0-禁用\r\nMaxEnable", "0", sFile);
		m_bMaxEnable = false;
		WriteFileToIni("ConsoleBtn", ";关闭禁用，1-不禁用，0-禁用\r\nExitEnable", "0", sFile);
		m_bExitEnable = false;
	}
}
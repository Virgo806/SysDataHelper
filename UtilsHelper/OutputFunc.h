#ifndef _H_OUTPUTFUNC_H_
#define _H_OUTPUTFUNC_H_
#pragma once
#include <string>

using namespace std;
class COutputFunc
{
public:
	static COutputFunc* GetInstance(void);
	static void ReleaseInstance(void);

public:
	// 获取运行路径
	string GetRunPath(void);
	// 获取应用名称
	string GetAppName(bool bIsExtend);
	// 获取应用版本
	string GetAppVersion(string sName = "");

	// 初始化控制台
	void InitConsole(void);
	// 卸载控制台
	void UnInitConsole(void);

	// 获取控制台初始化
	bool GetConsoleInitState(void) { return m_bInitState; };
	// 获取控制台输出
	bool GetConsoleOutState(void) { return m_bConsoleOut; };
	// 获取日志文件输出
	bool GetLogFileOutState(void) { return m_bLogFileOut; };

	// 读/写INI文件
	string ReadFileFromIni(string sApp, string sKey, string sDef, string sFile, bool bWrite = false);
	void WriteFileToIni(string sApp, string sKey, string sVal, string sFile);

	//  写日志到文件
	void WriteLogsToFile(string sLog);
	// 保存日志到磁盘
	void SaveLogsToDisk(void);

	DWORD GetRunProcessID(string sProName);

protected:
	COutputFunc(void);
	virtual ~COutputFunc(void);
	void OnLoadConfige(void);

private:
	static COutputFunc* m_pInstance;

	bool m_bInitState; // 初始化状态
	bool m_bConsoleOut; // 控制台输出
	bool m_bLogFileOut; // 日志文件输出
	bool m_bMinEnable; // 最小化按钮
	bool m_bMaxEnable; // 最大化按钮
	bool m_bExitEnable; // 关闭按钮

	FILE* m_pfLogs; // 日志输出文件
};

#endif // _H_OUTPUTFUNC_H_

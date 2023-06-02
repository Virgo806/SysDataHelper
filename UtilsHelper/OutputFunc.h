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
	// ��ȡ����·��
	string GetRunPath(void);
	// ��ȡӦ������
	string GetAppName(bool bIsExtend);
	// ��ȡӦ�ð汾
	string GetAppVersion(string sName = "");

	// ��ʼ������̨
	void InitConsole(void);
	// ж�ؿ���̨
	void UnInitConsole(void);

	// ��ȡ����̨��ʼ��
	bool GetConsoleInitState(void) { return m_bInitState; };
	// ��ȡ����̨���
	bool GetConsoleOutState(void) { return m_bConsoleOut; };
	// ��ȡ��־�ļ����
	bool GetLogFileOutState(void) { return m_bLogFileOut; };

	// ��/дINI�ļ�
	string ReadFileFromIni(string sApp, string sKey, string sDef, string sFile, bool bWrite = false);
	void WriteFileToIni(string sApp, string sKey, string sVal, string sFile);

	//  д��־���ļ�
	void WriteLogsToFile(string sLog);
	// ������־������
	void SaveLogsToDisk(void);

	DWORD GetRunProcessID(string sProName);

protected:
	COutputFunc(void);
	virtual ~COutputFunc(void);
	void OnLoadConfige(void);

private:
	static COutputFunc* m_pInstance;

	bool m_bInitState; // ��ʼ��״̬
	bool m_bConsoleOut; // ����̨���
	bool m_bLogFileOut; // ��־�ļ����
	bool m_bMinEnable; // ��С����ť
	bool m_bMaxEnable; // ��󻯰�ť
	bool m_bExitEnable; // �رհ�ť

	FILE* m_pfLogs; // ��־����ļ�
};

#endif // _H_OUTPUTFUNC_H_

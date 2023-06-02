#ifndef _H_THREADEX_H_
#define _H_THREADEX_H_
#pragma once
#include "UtilsHelperDef.h"

namespace UtilsHelper
{
	class UTILSHELPER_API CThreadEx
	{
		friend UINT __cdecl ThreadFuncHolder(void* pPara);
	public:
		CThreadEx(void);
		virtual ~CThreadEx(void);

		virtual BOOL StartThread(const char* pchName = NULL);
		virtual BOOL StopThread(int nWaitSec = 10);
		virtual BOOL IsThreadCancel(void) const;
		virtual void CancelThread(void);
		virtual DWORD WaitThread(int nWaitSec = 10);
		virtual BOOL SleepThread(DWORD dwMillSec, DWORD dwGap = 100);

	protected:
		virtual UINT ThreadFunc(void);

	private:
		UINT ThreadFuncAbstract(void); // �̳߳���

		HANDLE m_hThread; // �߳̾��
		DWORD m_dwThreadID; // �߳�ID
		LONG m_lIsCancelFlag; // ȡ����־ 
		char m_chThreadName[MAX_PATH]; // �߳���
	};
}
#endif // _H_THREADEX_H_
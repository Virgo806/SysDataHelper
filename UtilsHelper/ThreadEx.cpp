#include "pch.h"
#include "ThreadEx.h"
#include "UtilsHelper.h"

namespace UtilsHelper
{
	UINT __cdecl ThreadFuncHolder(void* pPara)
	{
		CThreadEx* pThread = (CThreadEx*)pPara;

		if (NULL != pThread)
			return pThread->ThreadFuncAbstract();

		return -1;
	}

	CThreadEx::CThreadEx(void)
	{
		m_hThread = NULL;
		m_dwThreadID = 0;
		::InterlockedExchange(&m_lIsCancelFlag, TRUE);
		ZeroMemory(m_chThreadName, MAX_PATH);
	}

	CThreadEx::~CThreadEx(void)
	{
		if (m_dwThreadID == GetCurrentThreadId())
			CancelThread();
		else
			StopThread();
	}

	BOOL CThreadEx::StartThread(const char* pchName /*= NULL*/)
	{
		if (NULL == pchName)
			return FALSE;

		strncpy_s(m_chThreadName, pchName, MAX_PATH);
		m_lIsCancelFlag = FALSE;

		CWinThread* pThread = NULL;
		for (int i = 0; i < 10; i++)
		{
			// 创建挂起线程
			pThread = AfxBeginThread(ThreadFuncHolder, (void*)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
			if (NULL != pThread)
			{
				m_hThread = pThread->m_hThread;
				m_dwThreadID = pThread->m_nThreadID;
				break;
			}
			else
			{
				LogsDebug("StartThread Thread Error, Name = %s", pchName);
				SleepThread(1000);
			}
		}

		if (NULL == pThread)
		{
			m_lIsCancelFlag = TRUE;
			return FALSE;
		}

		//唤醒线程
		pThread->ResumeThread();

		return TRUE;
	}

	BOOL CThreadEx::StopThread(int nWaitSec /*= 10*/)
	{
		if (m_dwThreadID == GetCurrentThreadId())
		{
			CancelThread();
			return TRUE;
		}

		::InterlockedExchange(&m_lIsCancelFlag, TRUE);
		if (NULL != m_hThread)
		{
			LogsDebug("<<< Stop Thread Begin TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());

			DWORD dwRet = WaitThread(nWaitSec);

			if (dwRet == WAIT_TIMEOUT)
				dwRet = WaitThread(nWaitSec);

			if (dwRet == WAIT_TIMEOUT)
			{
				LogsDebug("TerminateThread");
				::TerminateThread(m_hThread, -1);
			}

			LogsDebug(">>> Stop Thread End TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());

			CloseHandle(m_hThread);
			::InterlockedExchange((LONG*)&m_hThread, 0);
			::InterlockedExchange((LONG*)&m_dwThreadID, 0);

			return TRUE;
		}
		return FALSE;
	}

	BOOL CThreadEx::IsThreadCancel(void) const
	{
		return m_lIsCancelFlag == TRUE ? TRUE : FALSE;
	}

	void CThreadEx::CancelThread(void)
	{
		::InterlockedExchange(&m_lIsCancelFlag, TRUE);
	}

	DWORD CThreadEx::WaitThread(int nWaitSec /*= 10*/)
	{
		int nMillSec = 0;

		if (INFINITE == nWaitSec)
			nMillSec = INFINITE;
		else
			nMillSec = nWaitSec * 1000; // 转换为毫秒

		if (NULL == m_hThread)
			return WAIT_FAILED;

		DWORD dwRet = WaitForSingleObject(m_hThread, nMillSec);
		if (WAIT_OBJECT_0 == dwRet)
			LogsDebug("Thread Exit Success TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());
		else if (WAIT_TIMEOUT == dwRet)
			LogsDebug("Wait Thread Timeout TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());
		else if (WAIT_FAILED == dwRet)
			LogsDebug("Wait Thread Failed TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());
		else if (WAIT_ABANDONED == dwRet)
			LogsDebug("Wait Thread Abandoned TID = %d,TName = %s Timeout = %d CurTID = %d", m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());
		else
			LogsDebug("Wait Thread Return %d TID = %d,TName = %s Timeout = %d CurTID = %d", dwRet, m_dwThreadID, m_chThreadName, nWaitSec, GetCurrentThreadId());

		return dwRet;
	}

	BOOL CThreadEx::SleepThread(DWORD dwMillSec, DWORD dwGap /*= 100*/)
	{
		if (INFINITE == dwMillSec)
			Sleep(INFINITE);
		else
		{
			for (DWORD dw = 0; dw < dwMillSec;)
			{
				if (IsThreadCancel())
					return FALSE;

				Sleep(dwGap);
				dw += dwGap;
			}
		}

		return TRUE;
	}

	UINT CThreadEx::ThreadFunc(void)
	{
		return -1;
	}

	UINT CThreadEx::ThreadFuncAbstract(void)
	{
		LogsDebug("Start Thread %s,TID = %d", m_chThreadName, GetCurrentThreadId());
		UINT nRet = ThreadFunc();
		LogsDebug("Stop Thread %s,TID = %d", m_chThreadName, GetCurrentThreadId());

		try
		{
			::InterlockedExchange((LONG*)&m_hThread, 0);
			::InterlockedExchange((LONG*)&m_dwThreadID, 0);
			::InterlockedExchange(&m_lIsCancelFlag, TRUE);
		}
		catch (...)
		{
		}

		return nRet;
	}
}
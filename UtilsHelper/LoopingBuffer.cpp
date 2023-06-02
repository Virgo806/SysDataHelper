#include "pch.h"
#include "LoopingBuffer.h"
#include "UtilsHelper.h"

namespace UtilsHelper
{
	CLoopingBuffer::CLoopingBuffer(void)
	{
		m_nBufferSize = 0;
		m_nUseSize = 0;
		m_pchDataBuf = NULL;
	}

	CLoopingBuffer::~CLoopingBuffer(void)
	{
		UnInitBuffer();
	}

	bool CLoopingBuffer::InitBuffer(int nSize)
	{
		if (m_pchDataBuf)
			OnDeleteBuffer();
		
		CriticalLock(&m_csBuffer);
		m_pchDataBuf = new char[nSize];
		if (NULL == m_pchDataBuf)
		{
			LogsError("分配缓存失败！");
			return false;
		}

		m_nBufferSize = nSize;
		ZeroMemory(m_pchDataBuf, nSize);
		m_nUseSize = 0;

		return true;
	}

	bool CLoopingBuffer::UnInitBuffer(void)
	{
		return OnDeleteBuffer();
	}

	bool CLoopingBuffer::PushData(void* pData, int nLen)
	{
		if (NULL == pData || nLen <= 0)
		{
			LogsError("压栈数据信息错误，数据长度：%d。", nLen);
			return false;
		}

		int nUnuseSize = GetUnuseSize();
		if (nLen > nUnuseSize)
		{
			LogsError("剩余缓存空间不够，剩余大小：%d，压栈长度：%d。", nUnuseSize, nLen);
			return false;
		}

		UtilsHelper::CriticalLock(&m_csBuffer);
		CopyMemory((m_pchDataBuf + m_nUseSize), (char*)pData, nLen);
		m_nUseSize += nLen;

		return true;
	}

	bool CLoopingBuffer::TrimUseData(int nTrimLen)
	{
		if (NULL == m_pchDataBuf || nTrimLen <= 0)
		{
			LogsError("剪裁长度或缓存错误，剪裁长度：%d。", nTrimLen);
			return false;
		}
		
		UtilsHelper::CriticalLock(&m_csBuffer);
		int nReserve = m_nUseSize - nTrimLen;
		if (nReserve > 0)
		{
			memcpy(m_pchDataBuf, (m_pchDataBuf + nTrimLen), nReserve);
			m_nUseSize = nReserve;
		}
		else
			m_nUseSize = 0;

		return true;
	}

	void CLoopingBuffer::EmptyBuffer(void)
	{
		if (m_pchDataBuf)
		{
			UtilsHelper::CriticalLock(&m_csBuffer);
			m_nUseSize = 0;
			ZeroMemory(m_pchDataBuf, m_nBufferSize);
		}
	}

	bool CLoopingBuffer::OnDeleteBuffer(void)
	{
		if (m_pchDataBuf)
		{
			UtilsHelper::CriticalLock(&m_csBuffer);
			UH_SAFE_DELETE_ARRAY(m_pchDataBuf);
		}
		else
			return false;
		
		return true;
	}
}

#ifndef _H_LOOPINGBUFFER_H_
#define _H_LOOPINGBUFFER_H_
#pragma once
#include "UtilsHelperDef.h"

namespace UtilsHelper
{
	class UTILSHELPER_API CLoopingBuffer
	{
	public:
		CLoopingBuffer(void);
		virtual ~CLoopingBuffer(void);

		// ��ʼ������
		bool InitBuffer(int nSize);
		// ����ʼ������
		bool UnInitBuffer(void);
		// ѹջ����
		bool PushData(void* pData, int nLen);
		// ����ʹ������
		bool TrimUseData(int nTrimLen);
		// ��ջ���
		void EmptyBuffer(void);

		// ��ȡ�����С
		inline int GetBufferSize() { return m_nBufferSize; }
		// ��ȡʹ�ô�С
		inline int GetUseSize() { return m_nUseSize; }
		// ��ȡδʹ�ô�С
		inline int GetUnuseSize() { return (m_nBufferSize - m_nUseSize); }
		// ��ȡ��������
		inline void* GetBufferData() { return m_pchDataBuf; }

	protected:
		bool OnDeleteBuffer(void);

	private:
		int m_nBufferSize; // �����С
		int m_nUseSize; // ʹ�ô�С
		char* m_pchDataBuf; // ���ݻ���
		CCriticalSection m_csBuffer;
	};
}
#endif // _H_LOOPINGBUFFER_H_

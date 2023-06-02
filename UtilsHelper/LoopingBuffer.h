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

		// 初始化缓存
		bool InitBuffer(int nSize);
		// 反初始化缓存
		bool UnInitBuffer(void);
		// 压栈数据
		bool PushData(void* pData, int nLen);
		// 剪裁使用数据
		bool TrimUseData(int nTrimLen);
		// 清空缓存
		void EmptyBuffer(void);

		// 获取缓存大小
		inline int GetBufferSize() { return m_nBufferSize; }
		// 获取使用大小
		inline int GetUseSize() { return m_nUseSize; }
		// 获取未使用大小
		inline int GetUnuseSize() { return (m_nBufferSize - m_nUseSize); }
		// 获取缓存数据
		inline void* GetBufferData() { return m_pchDataBuf; }

	protected:
		bool OnDeleteBuffer(void);

	private:
		int m_nBufferSize; // 缓存大小
		int m_nUseSize; // 使用大小
		char* m_pchDataBuf; // 数据缓存
		CCriticalSection m_csBuffer;
	};
}
#endif // _H_LOOPINGBUFFER_H_

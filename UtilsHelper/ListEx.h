#ifndef _H_LISTEX_H_
#define _H_LISTEX_H_
#pragma once
#include <list>

namespace UtilsHelper
{
	template <class T>
	class CListEx
	{
	public:
		CListEx(void)
		{
		}

		virtual ~CListEx(void)
		{
		}

		typedef std::list<T> TListItem;

		BOOL PopItem(T &tItem)
		{
			BOOL bPopFlag = FALSE;
			CSingleLock QueLock(&m_csQue);

			QueLock.Lock();
			if (QueLock.IsLocked())
			{
				if (m_tlsQue.size() > 0)
				{
					tItem = m_tlsQue.front();
					m_tlsQue.pop_front();
					bPopFlag = TRUE;
				}
			}
			QueLock.Unlock();

			return bPopFlag;
		}

		int PushItem(T &tItem)
		{
			CSingleLock QueLock(&m_csQue);

			QueLock.Lock();
			if (QueLock.IsLocked())
			{
				m_tlsQue.push_back(tItem);
			}

			QueLock.Unlock();
			return m_tlsQue.size();
		}

		int SetCashItem(T &tItem)
		{
			CSingleLock CasLock(&m_csCash);

			CasLock.Lock();
			if (CasLock.IsLocked())
			{
				m_tlsCash.push_back(tItem);
			}
			CasLock.Unlock();

			return m_tlsCash.size();
		}

		BOOL GetCashItem(T &tItem)
		{
			BOOL bGetFlag = FALSE;
			CSingleLock CasLock(&m_csCash);

			CasLock.Lock();
			if (CasLock.IsLocked())
			{
				if (m_tlsCash.size() > 0)
				{
					tItem = m_tlsCash.front();
					m_tlsCash.pop_front();
					bGetFlag = TRUE;
				}
			}
			CasLock.Unlock();

			return bGetFlag;
		}

		int GetQueCount(void)
		{
			return m_tlsQue.size();
		}

		int GetCashCount(void)
		{
			return m_tlsCash.size();
		}

		void ClearAll(void)
		{
			T tItem;
			PopItem(tItem);
		}
	protected:
		TListItem m_tlsQue;
		TListItem m_tlsCash;
		CCriticalSection m_csQue;
		CCriticalSection m_csCash;
	};
}
#endif // _H_LISTEX_H_
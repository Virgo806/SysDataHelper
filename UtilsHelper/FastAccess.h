#ifndef _H_FASTACCESS_H_
#define _H_FASTACCESS_H_
#pragma once
#include <string>

#define WRITE_BUF_SIZE 1024 * 1024 * 1 // Ð´»º³åÇø´óÐ¡1M

namespace FastWrite
{
	char chWriteBuf[WRITE_BUF_SIZE];
	char* pchBegPos = NULL;
	char* pchEndPos = NULL;
	int nItmeSize = 0;
	int nMaxCount = 0;

	inline FILE* Init(const char* pchPath, const char* pchMode = "at+", const int nElemSize = 1)
	{
		FILE* pfWrite = NULL;

		if (0 != fopen_s(&pfWrite, pchPath, pchMode))
			return NULL;

		nItmeSize = nElemSize;
		nMaxCount = (WRITE_BUF_SIZE / nElemSize) * nElemSize;
		pchBegPos = chWriteBuf;
		pchEndPos = chWriteBuf + nMaxCount;

		return pfWrite;
	}

	inline FILE* Init(const std::string& sPath, const char* pchMode = "at+", const int nElemSize = 1)
	{
		return Init(sPath.c_str(), pchMode, nElemSize);
	}

	inline void Flush(FILE* pfWrite)
	{
		if (NULL == pfWrite)
			return;

		fwrite(chWriteBuf, nItmeSize, (pchBegPos - chWriteBuf) / nItmeSize, pfWrite);
		pchBegPos = chWriteBuf;
		fflush(pfWrite);
	}

	inline void Write(const char& chWord, FILE* pfWrite)
	{
		if (NULL == pfWrite)
			return;

		if (pchBegPos >= pchEndPos)
			Flush(pfWrite);
		*pchBegPos++ = chWord;
	}

	inline void Write(const char* pchStr, FILE* pfWrite)
	{
		if (NULL == pfWrite)
			return;

		for (; *pchStr; pchStr++)
		{
			Write(*pchStr, pfWrite);
		}
	}

	inline void Write(const std::string& sStr, FILE* pfWrite)
	{
		if (NULL == pfWrite)
			return;

		Write(sStr.c_str(), pfWrite);
	}

	inline int Close(FILE* pfWrite)
	{
		if (NULL == pfWrite)
			return 0;

		if (pchBegPos > chWriteBuf)
			Flush(pfWrite);

		int nRet = fclose(pfWrite);
		pchBegPos = NULL;
		pchEndPos = NULL;

		return nRet;
	}
}
#endif // _H_FASTACCESS_H_

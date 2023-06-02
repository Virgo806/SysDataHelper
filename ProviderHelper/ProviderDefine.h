#ifndef _H_PROVIDERDEFINE_H_
#define _H_PROVIDERDEFINE_H_
#pragma once
#include "TableDefine.h"
#include <string>
#include <memory>

#ifdef PROVIDERHELPER_EXPORTS
#	define PROVIDERHELPER_API __declspec(dllexport)
#else
#	define PROVIDERHELPER_API __declspec(dllimport)
#endif

namespace ProviderHelper
{
	// 数据记录集
	interface IDataRecordSet
	{
		// 字段索引从0开始
		virtual bool GetFieldValue(int nIndex, int& nValue) { return false; }
		virtual bool GetFieldValue(std::string sField, int& nValue) { return false; }
		virtual bool GetFieldValue(int nIndex, unsigned int& unValue) { return false; }
		virtual bool GetFieldValue(std::string sField, unsigned int& unValue) { return false; }
		virtual bool GetFieldValue(int nIndex, bool& bValue) { return false; }
		virtual bool GetFieldValue(std::string sField, bool& bValue) { return false; }
		virtual bool GetFieldValue(int nIndex, float& fValue) { return false; }
		virtual bool GetFieldValue(std::string sField, float& fValue) { return false; }
		virtual bool GetFieldValue(int nIndex, double& dValue) { return false; }
		virtual bool GetFieldValue(std::string sField, double& dValue) { return false; }
		virtual bool GetFieldValue(int nIndex, std::string& sValue) { return false; }
		virtual bool GetFieldValue(std::string sField, std::string& sValue) { return false; }

		virtual int GetRecordCount() { return 0; }
		virtual bool IsEof() { return false; }
		virtual bool MoveFirst() { return false; }
		virtual bool MoveLast() { return false; }
		virtual bool MovePrev() { return false; }
		virtual bool MoveNext() { return false; }
		virtual bool SetSeek(int nRow, bool bIsCurPos = false) { return false; }

		virtual bool IsFieldNull(int nIndex) { return false; }
		virtual bool IsFieldNull(std::string sField) { return false; }

		virtual bool IsActive() { return false; }
		virtual void CloseRecord() { return; }
	};
	typedef std::shared_ptr<IDataRecordSet> IDataRecordSetPtr;

	// 数据对象接口
	interface IDataObjectSet
	{
		virtual bool Disconnect() { return false; }
		virtual bool IsConnection() { return false; }

		virtual bool IsExistTable(std::string sTable) { return false; }
		virtual bool Execute(std::string sSQL) { return false; }
		virtual bool Execute(std::string sSQL, ProviderHelper::IDataRecordSetPtr& pRecSet) { return false; }
	};
	typedef std::shared_ptr<IDataObjectSet> IDataObjectSetPtr;
}
#endif // _H_PROVIDERDEFINE_H_
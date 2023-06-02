#ifndef _H_TABLERECORD_H_
#define _H_TABLERECORD_H_
#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../ProviderHelper/TableDefine.h"
#include "../ProviderHelper/ProviderDefine.h"

using namespace std;

interface ITableRecord
{
	virtual void SetContent(ProviderHelper::IDataRecordSetPtr pRecSet) = 0;
};

#endif // _H_TABLERECORD_H_

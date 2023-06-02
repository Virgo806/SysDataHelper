#ifndef _H_TABUSER_H_
#define _H_TABUSER_H_
#pragma once
#include "TableRecord.h"

#pragma pack(4)
DBTS_TABLE7(tab_user,
	int, user_id,
	string, user_name,
	string, user_pw,
	int, role_id,
	int, level,
	int, unit_id,
	string, comment);
#pragma pack()

class CTabUserRecord : public tab_user, public ITableRecord
{
public:
	CTabUserRecord()
	{
		user_id = 0;
		user_name = "";
		user_pw = "";
		role_id = 0;
		level = 0;
		unit_id = 0;
		comment = "";
	}
	virtual ~CTabUserRecord() {}

	virtual void SetContent(ProviderHelper::IDataRecordSetPtr pRecSet)
	{
		if (pRecSet)
		{
			pRecSet->GetFieldValue("user_id", user_id);
			pRecSet->GetFieldValue("user_name", user_name);
			pRecSet->GetFieldValue("user_pw", user_pw);
			pRecSet->GetFieldValue("role_id", role_id);
			pRecSet->GetFieldValue("level", level);
			pRecSet->GetFieldValue("unit_id", unit_id);
			pRecSet->GetFieldValue("comment", comment);
		}
	}
};

typedef shared_ptr<CTabUserRecord> CTabUserRecordPtr;
typedef map<int, CTabUserRecordPtr> CTabUserRecordMap;
typedef map<int, CTabUserRecordPtr>::iterator CTabUserRecordMapIterator;
typedef vector<CTabUserRecordPtr> CTabUserRecordVec;
typedef vector<CTabUserRecordPtr>::iterator CTabUserRecordVecIterator;
#endif // _H_TABUSER_H_
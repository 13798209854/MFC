#pragma once
class PersonInfo
{
public:
	PersonInfo()
	{
		per_Name = _T("δ֪");
		per_Sex = _T("δ֪");
		per_Tel = _T("δ֪");
		per_Email = _T("δ֪");
		per_Group = _T("�ҵĺ���");
	}
	~PersonInfo(void);
public:
	CString per_Name;
	CString per_Sex;
	CString per_Tel;
	CString per_Email;
	CString per_Group;
};
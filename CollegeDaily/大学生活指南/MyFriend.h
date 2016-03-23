#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMyFriend �Ի���
#define MaxGroupNumber 50 //���ѷ����������,Ϊ�˼���TreeControl�����ݿ⽻��ʱ��������ʱ�����Ŀ���
class CMyFriend : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFriend)

public:
	CMyFriend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyFriend();

// �Ի�������
	enum { IDD = IDD_MYFRIEND_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedAddperson();
	CTreeCtrl m_Tree;
//	CListBox m_List;

public:
	HTREEITEM m_DefalutFocus;
	HTREEITEM m_CurrentFocus;

	CString str_Name;                               //��ȡ������,�����������б�
	CString str_TargetGroup;                        //ѡ�е�Ŀ�����       
	HTREEITEM m_Group[50];                          //��������,���ڴ洢HTREEITEM�ڵ����ͱ���
	int GroupNumber;                                //��ǰ��������

	void ShowAllPerson();
	void ShowAllPeronTree();
	void RemovePerson_CListControl(long pos);
	void RemovePerson_CTreeControl(HTREEITEM Remove_CTreeControl);
	void RemoveGroup(CString str_RemoveGroup);
	void RefreshData();
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedMoreinfo();
	afx_msg void OnClickedRemove();
	afx_msg void OnClickedRewrite();
	afx_msg void OnClickedSelect();
	afx_msg void OnClickedAddgroup();
	afx_msg void OnClickedRefresh();
	afx_msg void OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
};

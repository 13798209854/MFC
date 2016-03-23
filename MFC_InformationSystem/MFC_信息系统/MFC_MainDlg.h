
// MFC_MainDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#define MaxGroupNumber 50                      //���ѷ����������,Ϊ�˼���TreeControl�����ݿ⽻��ʱ��������ʱ�����Ŀ���
// CMFC_MainDlg �Ի���
class CMFC_MainDlg : public CDialogEx
{
// ����
public:
	CMFC_MainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedMoreinfo();
	afx_msg void OnClickedAdd();

	HTREEITEM m_DefalutFocus;
	HTREEITEM m_CurrentFocus;

    CString str_Name;                               //��ȡ������,�����������б�
	CString str_TargetGroup;                        //ѡ�е�Ŀ�����
	CTreeCtrl m_TreeControl;
	CListCtrl m_ListCtrl;                          
	HTREEITEM m_Group[50];                               //��������,���ڴ洢HTREEITEM�ڵ����ͱ���
 	int GroupNumber;                                      //��ǰ��������

	afx_msg void OnClickedRemove();
	afx_msg void OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);

	void ShowAllPerson();
	void ShowAllPeronTree();
	void RemovePerson_CListControl(long pos);
	void RemovePerson_CTreeControl(HTREEITEM Remove_CTreeControl);
	void RemoveGroup(CString str_RemoveGroup);
	void RefreshData();       

	afx_msg void OnClickedAddgroup();
	afx_msg void OnClickedAlter();
	afx_msg void OnClickedSelect();
	afx_msg void OnClickedRefresh();
};
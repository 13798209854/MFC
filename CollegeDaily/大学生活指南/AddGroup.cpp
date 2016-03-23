// AddGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "AddGroup.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "MyFriend.h"

// CAddGroup �Ի���

IMPLEMENT_DYNAMIC(CAddGroup, CDialogEx)

CAddGroup::CAddGroup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddGroup::IDD, pParent)
{

}

CAddGroup::~CAddGroup()
{
}

void CAddGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddGroup, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CAddGroup::OnClickedAdd)
END_MESSAGE_MAP()

// CAddGroup ��Ϣ�������

void CAddGroup::OnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_GrouopName;
	CMyFriend *p = (CMyFriend*)this->GetParent();
	GetDlgItemText(IDC_EDIT_GROUP,str_GrouopName);                     //��ȡ������ı�
	ADO sql;
	sql.OnInitADOConn();												   //��ʼ�����ݿ�����	
	sql.initRecordset();												   //������¼��ʵ��
	_bstr_t sql_DDL_GroupList = "select * from GroupList";				   //sql���
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic,adLockOptimistic,adCmdText);   //��GroupList��¼��
	try
	{
		sql.m_pReset->AddNew();														 //�������
		sql.m_pReset->PutCollect("������",(char*)(_bstr_t)str_GrouopName);           //����õ��ı��������ݿ�
		p->m_Tree.InsertItem(str_GrouopName);                                 //��������б�(CTreeControl)
		sql.m_pReset->Update();														 //�������ݿ�
		sql.CloseConn();															 //�ر����ݿ�����
	}
	catch(...)
	{
		MessageBox(_T("������ѷ����������(���n��) "));
		return;
	}
	CAddGroup::OnCancel();                            //Ĭ�ϰ���ȡ����ť�����ԹرնԻ���
}

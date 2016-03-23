// MyStudy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "MyStudy.h"
#include "afxdialogex.h"
#include "ADO.h"


// CMyStudy �Ի���

IMPLEMENT_DYNAMIC(CMyStudy, CDialogEx)

CMyStudy::CMyStudy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyStudy::IDD, pParent)
{

}

CMyStudy::~CMyStudy()
{
}

void CMyStudy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_studyTree);
}


BEGIN_MESSAGE_MAP(CMyStudy, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON1, &CMyStudy::OnBnClickedButton1)
//	ON_EN_CHANGE(IDC_EDIT2, &CMyStudy::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_ADD_STUDY, &CMyStudy::OnClickedAddStudy)
	ON_BN_CLICKED(IDC_REMOVE, &CMyStudy::OnClickedRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CMyStudy::OnDblclkTree)
END_MESSAGE_MAP()


// CMyStudy ��Ϣ�������

void CMyStudy::OnClickedAddStudy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString course_name;
	CString xueyuan_name;
	CString myStudy;
	GetDlgItemText(IDC_EDIT_COURSE,course_name);
	GetDlgItemText(IDC_EDIT_STUDY,myStudy);
	xueyuan_name = m_studyTree.GetItemText(m_studyTree.GetParentItem(m_studyTree.GetSelectedItem()));
	if (myStudy.IsEmpty())
	{
		myStudy = _T("����");
	}
	ADO sql;
	sql.OnInitADOConn();
	sql.initRecordset();
	CString sql_DDL;
	sql_DDL.Format(_T("update �ص�γ� set ѧϰ�ƻ� = '%s' where �γ���='%s' and ѧԺ�� = '%s'"),\
		                                                       myStudy,course_name,xueyuan_name);
	sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),    \
		                adOpenDynamic,adLockOptimistic,adCmdText);
	sql.CloseConn();
}

void CMyStudy::OnClickedRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_STUDY,_T(""));
}

void CMyStudy::OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	xueyuan = m_studyTree.GetSelectedItem();
	if (!m_studyTree.ItemHasChildren(xueyuan) && \
		!m_studyTree.GetItemText(m_studyTree.GetParentItem(xueyuan)).IsEmpty()) 
	{	
		CString xueyuan_name;
		CString course_name;
		CString myStudy;
		xueyuan_name = m_studyTree.GetItemText(m_studyTree.GetParentItem(xueyuan));
		course_name = m_studyTree.GetItemText(xueyuan);
		SetDlgItemText(IDC_EDIT_COURSE,course_name);
		ADO sql;
		sql.OnInitADOConn();
		sql.initRecordset();
		CString sql_DDL;
		sql_DDL.Format(_T("select ѧϰ�ƻ� from �ص�γ� where �γ��� = '%s' and ѧԺ�� = '%s'"),course_name,xueyuan_name);
		sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),   \
			adOpenDynamic,adLockOptimistic,adCmdText);
		myStudy = (char*)(_bstr_t)sql.m_pReset->GetCollect("ѧϰ�ƻ�");
		sql.CloseConn();
		SetDlgItemText(IDC_EDIT_STUDY,myStudy);
	}
}

BOOL CMyStudy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString temp_course;
	CString temp_name;
	int count = 0;

	ADO sql;
	_bstr_t sql_DDL_GroupList = "select * from ѧԺ order by ID";        //sql���
	sql.OnInitADOConn();                                                 //��ʼ�����ݿ�����
	sql.initRecordset();                                                 //������¼��ʵ��
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(),    \
		adOpenDynamic,adLockOptimistic,adCmdText);
	while (!sql.m_pReset->adoEOF)                                         //����¼��ָ�벻����ĩβ��ִ��ѭ��
	{                                                                     //����Ҫ�Ȳ������з���	
		temp_name = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("ѧԺ��");
		temp_xuyuan[count] = m_studyTree.InsertItem(temp_name); 
		count++;
		sql.m_pReset->MoveNext();                                         //��¼������һλ
	}
	sql.CloseRecordset();                                                 //�رռ�¼��                   
	_bstr_t sql_DDL_PersonInfo = "select * from �ص�γ� order by ID";  //SQL���
	sql.m_pReset->Open(sql_DDL_PersonInfo,sql.m_pConn.GetInterfacePtr(),   \
		adOpenDynamic,adLockOptimistic,adCmdText);
	while (!sql.m_pReset->adoEOF)                                         //��¼��ָ�벻����ĩβʱִ��ѭ��
	{                                                                     //��ѭ�������з����в����������
		temp_course = (char*)(_bstr_t)sql.m_pReset->GetCollect("�γ���");      //������е�����
	    temp_name = (char*)(_bstr_t)sql.m_pReset->GetCollect("ѧԺ��"); //����˺��ѵ����ڷ�����
		for (int i = 0; i < count; ++i)                                  //ѭ�����������
		{
			if (m_studyTree.GetItemText(temp_xuyuan[i]) == temp_name) //����������ڷ���������ѭ�����÷�����
			{
				m_studyTree.InsertItem(temp_course,temp_xuyuan[i]);                     
				break;                                //�������ܿ���һ��Ҫbreakһ�£���Ȼ�������ѭ��
			}
		}
		sql.m_pReset->MoveNext();                                       //��¼����
	}
	sql.CloseConn();   //�Ͽ����ݿ�����
	return TRUE;
}

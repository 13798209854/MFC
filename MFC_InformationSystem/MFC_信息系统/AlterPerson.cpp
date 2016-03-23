// AlterPerson.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_ѧ����Ϣ����ϵͳ.h"
#include "AlterPerson.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "MFC_MainDlg.h"
// CAlterPerson �Ի���

IMPLEMENT_DYNAMIC(CAlterPerson, CDialogEx)

CAlterPerson::CAlterPerson(CWnd* pParent/* =NULL */)
	: CDialogEx(CAlterPerson::IDD, pParent)
{
	
}

CAlterPerson::~CAlterPerson()
{
}

void CAlterPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALTER_BOY, Boy_Selected);
	//  DDX_Control(pDX, IDCANCEL, Girl_Selected);
	DDX_Control(pDX, IDC_ALTER_NAME, CEdit_Name);
	DDX_Control(pDX, IDC_ALTER_TEL, CEdit_Tel);
	DDX_Control(pDX, IDC_ALTER_EMAIL, CEdit_Email);
	DDX_Control(pDX, IDC_ALTER_GIRL, Girl_Selected);
}


BEGIN_MESSAGE_MAP(CAlterPerson, CDialogEx)
	ON_BN_CLICKED(IDC_ENSURE_ALTER, &CAlterPerson::OnClickedEnsureAlter)
END_MESSAGE_MAP()


// CAlterPerson ��Ϣ�������

BOOL CAlterPerson::OnInitDialog()         //��д��ʼ���Ի����麯��  Ŀ�����ڳ�ʼ��ʱ����ʾԭ������Ϣ
{
	CDialogEx::OnInitDialog();

	CMFC_MainDlg *p = (CMFC_MainDlg*)AfxGetApp()->m_pMainWnd;                                 //���������Ӧ��ʵ��
	CString TargetName = p->m_TreeControl.GetItemText(p->m_TreeControl.GetSelectedItem());    //����ѡ�к��ѵ��ı���Ϣ(����)
	CString sql_DDL;
	sql_DDL.Format(_T("select * from PersonInfo Where ����='%s'"),TargetName);				  //sql��䣬��ѯѡ�еĺ�����Ϣ
	try
	{
		ADO sql;
		sql.OnInitADOConn();													        //��ʼ�����ݿ�����
		sql.initRecordset();															//������¼��ʵ��
		sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),
			                                adOpenDynamic,adLockOptimistic,adCmdText);	//�����ü�¼��
		Alter_Name = sql.m_pReset->GetCollect("����");									//�õ���������
		Alter_Sex = sql.m_pReset->GetCollect("�Ա�");									//�õ������Ա�
		Alter_Tel = sql.m_pReset->GetCollect("�绰");									//�õ����ѵ绰
		Alter_Email = sql.m_pReset->GetCollect("����");									//�õ���������
		sql.CloseConn();																//�ر����ݿ�����
	}
	catch(...)
	{
		MessageBox(_T("��ʼ���޸ĶԻ���ʱ��������(���n��) "),_T("��ʼ���޸ĶԻ���"),MB_OK|MB_ICONERROR);
		return FALSE;
	}
	CEdit_Name.SetWindowText(Alter_Name);		//��EditControl����ʾ����
	CEdit_Tel.SetWindowText(Alter_Tel);		//��EditControl����ʾ�绰
	CEdit_Email.SetWindowText(Alter_Email);	//��EditControl����ʾ����
	if (Alter_Sex == "��")						//�Ա�Ϊ��
	{
		Boy_Selected.SetCheck(BST_CHECKED);		//����RadioButton��Ϊѡ��
	}
	if (Alter_Sex == "Ů")						//�Ա�ΪŮ
	{
		Girl_Selected.SetCheck(BST_CHECKED);    //����RadioButtonŮΪѡ��
	}
	return TRUE;
}

void CAlterPerson::OnClickedEnsureAlter()                 //�޸Ĺ���ʵ�ֺ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMFC_MainDlg *p = (CMFC_MainDlg*)AfxGetApp()->m_pMainWnd;			//��ȡ������Ӧ��ʵ��
	CString TargetName = p->m_TreeControl.GetItemText(p->m_TreeControl.GetSelectedItem());  //���ڱ���ѡ�еĺ�����
	GetDlgItemText(IDC_ALTER_NAME,Alter_Name);		  //�õ�����������ı�
	GetDlgItemText(IDC_ALTER_TEL,Alter_Tel);		  //�õ�����ĵ绰�ı�
	GetDlgItemText(IDC_ALTER_EMAIL,Alter_Email);      //�õ�����������ı�
	if (Alter_Name.IsEmpty())                         //���ں������ܿ���,��������Ϊ��,��Ϊ������ֹ�޸�,
	{
		MessageBox(_T("���ں������ܵĿ���,��������Ϊ��Ӵ~(�s3�t) "),_T("�޸ĺ�����Ϣ"),MB_OK|MB_ICONERROR);
		return;
	}
	if (Alter_Tel.IsEmpty())                          //���绰Ϊ������Ϊ"δ֪"
	{
		Alter_Tel = "δ֪";
	}
	if (Alter_Email.IsEmpty())                        //������Ϊ������Ϊ"δ֪"
	{
		Alter_Email = "δ֪";
	}
	if (Boy_Selected.GetCheck() == 1)                //��ѡ��"��"
	{
		Alter_Sex = "��";
	}
	if (Girl_Selected.GetCheck() == 1)               //��ѡ��"Ů"
	{
		Alter_Sex = "Ů";
	}
	try
	{
		ADO sql;
		sql.OnInitADOConn();		//��ʼ�����ݿ�����
		sql.initRecordset();		//������¼��ʵ��
		CString sql_DDL_ensure;
		sql_DDL_ensure.Format(_T("select * from PersonInfo where ����='%s'"),Alter_Name);//��֤sql���,����޸ĺ��������������ֹ�޸�
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure,sql.m_pConn.GetInterfacePtr(),\
			                          adOpenStatic,adLockOptimistic,adCmdText);//����֤sql����ҵ��ļ�¼��,ע�������Ǿ�̬��,
		                                                                       //���������������ado����ڿͻ���ʹ�õ�ǰ��ֻ���α꣬
		                                                                       //���޷����ؽ������������ֻ�ܷ��أ�1
		if (sql.m_pReset->GetRecordCount() != 0)							   //�ж�sql������ü�¼���Ƿ��м�¼
		{
			MessageBox(_T("�������Ѵ���,Ϊ�����ϱ�Ż��ǲ����ѡ��O(��_��)O"),_T("�޸ĺ�����Ϣ"),MB_OK|MB_ICONERROR);
			sql.CloseConn();
			return;
		}
		else
		{
			sql.CloseRecordset();                                                         //�ر���֤��¼�� 
			CString sql_DDL;
			sql_DDL.Format(_T("update PersonInfo set ����='%s',�Ա�='%s',�绰='%s',����='%s' where ����='%s'"),\
													 Alter_Name,Alter_Sex,Alter_Tel,Alter_Email,TargetName);    //�޸���Ϣ�� sql���
			sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),\
												adOpenDynamic,adLockOptimistic,adCmdText);           //ִ��sql���
			sql.CloseConn();       //�ر����ݿ�����
			p->RefreshData();	   //ˢ��������
		}

	}
	catch(...)
	{
		MessageBox(_T("�޸ĺ�����Ϣ������~(���n��) "),_T("�޸ĺ�����Ϣ"),MB_OK|MB_ICONERROR);
		return;
	}
	CAlterPerson::OnCancel();                                       //Ĭ�ϰ���ȡ����ť���ԹرնԻ���
}
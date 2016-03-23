// MyFriend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "MyFriend.h"
#include "afxdialogex.h"
#include "AddPerson.h"
#include "ADO.h"
#include "ReWrite.h"
#include "SelectPerson.h"
#include "AddGroup.h"
#include "ShowInfo.h"
// CMyFriend �Ի���

IMPLEMENT_DYNAMIC(CMyFriend, CDialogEx)

CMyFriend::CMyFriend(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyFriend::IDD, pParent)
{

}

CMyFriend::~CMyFriend()
{
}

void CMyFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	//  DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CMyFriend, CDialogEx)
	ON_BN_CLICKED(IDC_ADDPERSON, &CMyFriend::OnClickedAddperson)
	ON_BN_CLICKED(IDC_MOREINFO, &CMyFriend::OnClickedMoreinfo)
	ON_BN_CLICKED(IDC_REMOVE, &CMyFriend::OnClickedRemove)
	ON_BN_CLICKED(IDC_REWRITE, &CMyFriend::OnClickedRewrite)
	ON_BN_CLICKED(IDC_SELECT, &CMyFriend::OnClickedSelect)
	ON_BN_CLICKED(IDC_ADDGROUP, &CMyFriend::OnClickedAddgroup)
	ON_BN_CLICKED(IDC_REFRESH, &CMyFriend::OnClickedRefresh)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CMyFriend::OnDblclkTree)
END_MESSAGE_MAP()


// CMyFriend ��Ϣ�������


void CMyFriend::ShowAllPerson()                //��ʾ���к��ѵ���ϸ��Ϣ����
{  
	ADO sql;  
	sql.OnInitADOConn();                             //��ʼ�����ݿ�����
	sql.initRecordset();                             //������¼������ָ��ʵ��  
	_bstr_t sql_DDL = "select * from PersonInfo order by ID desc";           //sql���
	sql.m_pReset->Open(sql_DDL,sql.m_pConn.GetInterfacePtr(),\
		adOpenDynamic,adLockOptimistic,adCmdText);   //�򿪼�¼��
	while (!sql.m_pReset->adoEOF)                                           //��¼��������ĩβʱִ��ѭ��
	{
		m_List.InsertItem(0,_T(""));                                                      //����һ��
		m_List.SetItemText(0,0,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����"));     //�����е�1�и�ֵ
		m_List.SetItemText(0,1,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("�Ա�"));     //�����е�2�и�ֵ
		m_List.SetItemText(0,2,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("�绰"));     //�����е�3�и�ֵ
		m_List.SetItemText(0,3,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����"));     //�����е�4�и�ֵ
		m_List.SetItemText(0,4,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("���ڷ���")); //�����е�5�и�ֵ
		sql.m_pReset->MoveNext();                                                         //��¼��ָ�����һλ
	}
	sql.CloseConn();                                                                      //�ر����ݿ�����
}

void CMyFriend::ShowAllPeronTree()                         //��ʾ�����б���
{
	GroupNumber = 0;                                          //��ʼʱĬ��û����
	ADO sql;
	_bstr_t sql_DDL_GroupList = "select * from GroupList order by ID";   //sql���
	sql.OnInitADOConn();                                                 //��ʼ�����ݿ�����
	sql.initRecordset();                                                 //������¼��ʵ��
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(),    \
		adOpenDynamic,adLockOptimistic,adCmdText);//��GroupList��¼��
	while (!sql.m_pReset->adoEOF)                                         //����¼��ָ�벻����ĩβ��ִ��ѭ��
	{                                                                     //����Ҫ�Ȳ������з���
		if ((int)sql.m_pReset->GetCollect("ID") <= (MaxGroupNumber + 1))  //�жϷ����ID���Ƿ񳬹����������(50��)AccessID�Ǵ�1��ʼ��
		{                                                                 //��MaxGroupNumberҪ��1
			m_Group[GroupNumber] = m_Tree.InsertItem((LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("������")); //������б����÷�����
			GroupNumber++;                                                //��������1
			sql.m_pReset->MoveNext();                                     //��¼������һλ
		}
	}
	m_DefalutFocus = m_Group[0];                                          //��һ��������ΪĬ��ѡ�н���,
																		  //Ϊ��û��ѡ���κ������Ӻ����ṩĬ����Ϊ
	sql.CloseRecordset();                                                 //�رռ�¼��                   

	_bstr_t sql_DDL_PersonInfo = "select * from PersonInfo order by ID";  //SQL���
	sql.m_pReset->Open(sql_DDL_PersonInfo,sql.m_pConn.GetInterfacePtr(),   \
		adOpenDynamic,adLockOptimistic,adCmdText);//��GroupList��¼��
	while (!sql.m_pReset->adoEOF)                                         //��¼��ָ�벻����ĩβʱִ��ѭ��
	{                                                                     //��ѭ�������з����в����������
		str_Name = (char*)(_bstr_t)sql.m_pReset->GetCollect("����");      //������е�����
		str_TargetGroup = (char*)(_bstr_t)sql.m_pReset->GetCollect("���ڷ���"); //����˺��ѵ����ڷ�����
		for (int i = 0; i <= GroupNumber; ++i)                                  //ѭ�����������
		{
			if (m_Tree.GetItemText(m_Group[i]) == (CString)str_TargetGroup) //����������ڷ���������ѭ�����÷�����
			{
				m_Tree.InsertItem(str_Name,m_Group[i]);                     //������в����������
				break;                                                             //�������ܿ���һ��Ҫbreakһ�£���Ȼ�������ѭ��
			}
		}
		sql.m_pReset->MoveNext();                                       //��¼����
	}
	sql.CloseConn();   //�Ͽ����ݿ�����
}

void CMyFriend::RefreshData()                      //ˢ��������ʵ�ֺ���
{
	m_List.DeleteAllItems();                  //ɾ��ĿǰCListControl(��ϸ��Ϣ)������
	m_Tree.DeleteAllItems();               //ɾ��ĿǰCTreeControl(�����б�)������
	ShowAllPerson();                              //���²������к�����ϸ��Ϣ
	ShowAllPeronTree();                           //���²������к����б�
} 

void CMyFriend::RemoveGroup(CString str_RemoveGroup)        //ɾ�������¼���Ӧ����
{
	CString Target;                      //Ҫɾ����Ŀ�������
	ADO sql;     
	sql.OnInitADOConn();                 //��ʼ�����ݿ�����
	sql.initRecordset();                 //�������ݼ�ʵ��
	_bstr_t sql_DDL_GroupList = "select * from GroupList";     //sql���
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(),\
		adOpenDynamic,adLockOptimistic,adCmdText);            //��GroupList��¼��
	try
	{
		while (!sql.m_pReset->adoEOF)     //������¼��ָ�벻����ĩβ��ִ��ѭ��
		{
			Target = (char*)(_bstr_t)sql.m_pReset->GetCollect("������");    //����ô�ѭ�����õķ�����
			if (str_RemoveGroup == (CString)Target)                         //��Ҫɾ���ķ��������ڸ�ѭ�����õķ�����
			{
				sql.m_pReset->Delete(adAffectCurrent);                      //ɾ�����ݿ��еĸ÷�����
				sql.m_pReset->Update();                                     //�������ݿ�
			}   
			sql.m_pReset->MoveNext();                                       //���ݼ�ָ�����
		}  
		sql.CloseConn();                                                    //�Ͽ����ݿ�����
	}
	catch(...)
	{
		MessageBox(_T("ɾ�����ѷ���ʧ������(���n��)"),_T("ɾ�����ѷ���"),MB_OK);
		return;
	}
}

void CMyFriend::RemovePerson_CTreeControl(HTREEITEM Remove_CTreeControl)                    //ΪCTreeControl����ɾ������
{
	ADO sql;
	sql.OnInitADOConn();                      //��ʼ�����ݿ�����
	sql.initRecordset();                      //�������ݼ�ʵ��
	_bstr_t sql_DDL_DELETE = "select * from PersonInfo";    //Ҫִ�е�sql���
	sql.m_pReset->Open(sql_DDL_DELETE,sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic,adLockOptimistic,adCmdText);             //��PersonInfo��¼��
	CString Target_Name;                        //���ѭ�����ú�����
	CString Delete_Name = m_Tree.GetItemText(Remove_CTreeControl);                    //���ѡ�еĽ�Ҫɾ���ĺ�����
	try  
	{
		while (!sql.m_pReset->adoEOF)                                   //������¼��ָ�벻����ĩβ��ִ��ѭ��
		{  
			Target_Name = (CString)sql.m_pReset->GetCollect("����");    //����ѭ�����õĺ�����
			if (Delete_Name == Target_Name)                             //�ж�ѭ�����ú������Ƿ�ͽ�Ҫɾ���ĺ��������
			{
				sql.m_pReset->Delete(adAffectCurrent);                  //ɾ����ǰ��
				sql.m_pReset->Update();                                 //�������ݿ�
				sql.CloseConn();                                        //�ر�����
				break;                                                  //Ϊ������,�ǵ�break;��ֹ����ѭ��
			}
			sql.m_pReset->MoveNext();                                   //��¼��ָ�����һλ
		}
		sql.CloseConn();                                                //�ر����ݿ�����
	}
	catch(...)
	{
		MessageBox(_T("ɾ�������˳�������CTreeControl����(���n��)"),_T("ɾ������"),MB_OK);
		return;
	}
}

void CMyFriend::OnClickedAddperson()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������              
	m_CurrentFocus = m_Tree.GetSelectedItem();     //���õ�ǰѡ�еĽ���
	if (!m_Tree.GetItemText(m_Tree.GetParentItem(m_CurrentFocus)).IsEmpty())    //����Ƿ��ڷ�������ӷ���
	{
		MessageBox(_T("��Ӻ���ֻ��ѡ�������Ӵ����~~�r(�s���t)�q "),_T("��Ӻ���"),MB_OK);
		return;
	}
	else
	{
		CAddPerson addpersonDlg;
		addpersonDlg.DoModal();           //����ģ̬�Ի���
	}
}

BOOL CMyFriend::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnClickedMoreinfo();                                      //��ʼ��ʱ�Զ�������ϸ��Ϣ��ť,Ϊ��������,��ʼ���滹��С�ɵ��
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);            //����CListControl���,�ܱ�����ѡ��
	m_List.InsertColumn(0,_T("����"),LVCFMT_CENTER,80);       //����������
	m_List.InsertColumn(1,_T("�Ա�"),LVCFMT_CENTER,50);       //�����Ա���
	m_List.InsertColumn(2,_T("�绰"),LVCFMT_CENTER,105);      //����绰������
	m_List.InsertColumn(3,_T("����"),LVCFMT_CENTER,140);      //����������
	m_List.InsertColumn(4,_T("���ڷ���"),LVCFMT_CENTER,110);  //�������ڷ�����	
	ShowAllPerson();                                          //��ʾ������ϸ��Ϣ
	ShowAllPeronTree();
	return TRUE;
}

void CMyFriend::OnClickedMoreinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	if (GetDlgItemText(IDC_MOREINFO,str),str == "��ϸ��Ϣ >>")
	{
		SetDlgItemText(IDC_MOREINFO,_T("��ϸ��Ϣ<<"));  //�ı䰴ť�ı�
	}
	else
	{
		SetDlgItemText(IDC_MOREINFO,_T("��ϸ��Ϣ >>")); //����� >>ǰ��һ���ո񡣡�����Ȼ��Ҳ��֪����ô��ʽ��ʾ������0-0
	}
	static CRect rectNormal;              //����������С��Ϣ
	static CRect rectSmaller;             //������С��Ĵ�С��Ϣ

	if (rectNormal.IsRectNull())          //���������С����Χ��ΪNULL�������
	{
		CRect rectSeparator;              //�ٴ���һ����Ž�Ҫ�����µľ���Χ����
		GetWindowRect(&rectNormal);       //��ʼ��������С�ľ�����Ϣ
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator); //��ò�ֶԻ�������Image������
		rectSmaller.left = rectNormal.left;                       //��С��ľ�����󲻱�
		rectSmaller.top = rectNormal.top;                         //��Ҳ����
		rectSmaller.right = rectSeparator.right;                  //�ұ�������ڷָ���Image������y
		rectSmaller.bottom = rectNormal.bottom;                   //�ײ�����Ҳ����
	}
	if (str == "��ϸ��Ϣ<<")
	{
		SetWindowPos(NULL,0,0,rectSmaller.Width(),rectSmaller.Height(),SWP_NOMOVE | SWP_NOZORDER);    //����չ������С
	}
	if (str == "��ϸ��Ϣ >>")
	{
		SetWindowPos(NULL,0,0,rectNormal.Width(),rectNormal.Height(),SWP_NOMOVE | SWP_NOZORDER);      //����С������չ
	}
}

void CMyFriend::OnClickedRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM m_Remove = m_Tree.GetSelectedItem();
	CString TargetRemove = m_Tree.GetItemText(m_Remove);                           //ѡ�е�Ŀ�����ı�
	if (m_Remove == NULL && m_List.GetSelectionMark() == -1)                          //(1).��δѡ���κ�
	{
		MessageBox(_T("��δѡ���κ��˻���Ӵ~"),_T("ɾ������"),MB_OK);
		return;
	}
	if (m_Remove == m_DefalutFocus)                                                       //(2).��ѡ��"�ҵĺ���"����
	{
		MessageBox(_T("���ǰ����飬����ɾ��Ӵ�r(�s���t)�q "),_T("ɾ������"),MB_OK);
		return;
	}
	else                                                                                  //ѡ��������ɾ�������
	{
		if (!m_Tree.GetItemText(m_Tree.GetParentItem(m_Remove)).IsEmpty())               //(3).��ѡ��ɾ������Ƿ���
		{
			RemovePerson_CTreeControl(m_Remove);                                                     //ɾ��ѡ�еĺ���
			RefreshData();                                                                           //ˢ��������
			return;
		}
		if (!m_Tree.ItemHasChildren(m_Remove) && \
			m_Tree.GetItemText(m_Tree.GetParentItem(m_Remove)).IsEmpty())                //(4).ѡ��û���˵ķ���ʱ
		{
			RemoveGroup(TargetRemove);                                                                  //ɾ������
			RefreshData();                                                                              //ˢ��������
			return;
		}
		if (m_Tree.GetItemText(m_Tree.GetParentItem(m_Remove)).IsEmpty() && \
			m_Tree.ItemHasChildren(m_Remove))                                                  //(5).ѡ���к��ѵķ���ʱ
		{
			int temp = MessageBox(_T("��ѡ�е�һ�����飬ȷ��Ҫɾ��������鼰�������г�Ա��"),\
				_T("ɾ�����鼰��Ա"),MB_OKCANCEL);                                  //�ж��Ƿ�ѡ��ȷ����ť
			if (temp == IDCANCEL)
			{
				return;
			}
			else
			{
				CString Dele_GroupName = m_Tree.GetItemText(m_Remove);                        //���ѡ�з�����ı�
				CString Target_GroupName;                                                            //����ѭ�����÷�����
				ADO sql;
				sql.OnInitADOConn();                                                                 //��ʼ�����ݿ�����
				sql.initRecordset();																 //������¼��ʵ��
				_bstr_t sql_DDL_DELETE_Person = "select * from PersonInfo";							 //sql���
				sql.m_pReset->Open(sql_DDL_DELETE_Person,sql.m_pConn.GetInterfacePtr(),
					adOpenDynamic,adLockOptimistic,adCmdText);  //��PersonInfo��¼��
				try
				{
					while (!sql.m_pReset->adoEOF)												     //��¼��ָ�벻����ĩβ��¼ʱִ��ѭ��
					{
						Target_GroupName = (char*)(_bstr_t)sql.m_pReset->GetCollect("���ڷ���");     //����ѭ�����÷�����
						if (Dele_GroupName == (CString)Target_GroupName)				//�ж�Ҫɾ���������ڷ����Ƿ����ѡ�еķ���
						{
							sql.m_pReset->Delete(adAffectCurrent);									//ɾ������
						}												    
						sql.m_pReset->MoveNext();													//��¼��ָ�����һλ
					}
					sql.CloseConn();										//�Ͽ����ݿ�����
					RemoveGroup(Dele_GroupName);							//ɾ����ѡ���������ݿ��еļ�¼
					RefreshData();											//ˢ��������
					return;
				}
				catch(...)
				{
					MessageBox(_T("����ɾ�����ѳ�����(���n��)"),_T("����ɾ������"),MB_OK);
					return;
				}
			}
		}
	}
}

void CMyFriend::OnClickedRewrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CReWrite m_AlterPerson;
	HTREEITEM Selected_TreeItem = m_Tree.GetSelectedItem();		//����ѡ�еĽڵ���Ϣ
	if (Selected_TreeItem == NULL)										//�ж��Ƿ���ѡ���κνڵ�
	{
		MessageBox(_T("�㻹û��ѡ���޸�˭��~O(��_��)O~"),_T("�޸ĺ�����Ϣ"),MB_OK);
		return;
	}
	if (!m_Tree.ItemHasChildren(Selected_TreeItem) && \
		!m_Tree.GetItemText(m_Tree.GetParentItem(Selected_TreeItem)).IsEmpty())  //�ж��Ƿ�ѡ����Ǻ��ѣ������Ƿ���
	{																							
		m_AlterPerson.DoModal();	//����ģ̬�Ի���
	}
	else
	{
		MessageBox(_T("������������,�r(�s���t)�q,����ѡ����飬ֻ��ѡ�����"),_T("�޸ĺ�����Ϣ"),MB_OK);
		return;
	}
}

void CMyFriend::OnClickedSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSelectPerson m_SelectDlg;
	m_SelectDlg.DoModal();
}

void CMyFriend::OnClickedAddgroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddGroup m_AddGroupDlg;
	m_AddGroupDlg.DoModal();
}

void CMyFriend::OnClickedRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RefreshData();
}

void CMyFriend::OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShowInfo m_ShowDlg;
	m_ShowDlg.DoModal();
}

// AddGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "大学生活指南.h"
#include "AddGroup.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "MyFriend.h"

// CAddGroup 对话框

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

// CAddGroup 消息处理程序

void CAddGroup::OnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_GrouopName;
	CMyFriend *p = (CMyFriend*)this->GetParent();
	GetDlgItemText(IDC_EDIT_GROUP,str_GrouopName);                     //获取输入的文本
	ADO sql;
	sql.OnInitADOConn();												   //初始化数据库连接	
	sql.initRecordset();												   //创建记录集实例
	_bstr_t sql_DDL_GroupList = "select * from GroupList";				   //sql语句
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic,adLockOptimistic,adCmdText);   //打开GroupList记录集
	try
	{
		sql.m_pReset->AddNew();														 //添加新行
		sql.m_pReset->PutCollect("分组名",(char*)(_bstr_t)str_GrouopName);           //将获得的文本插入数据库
		p->m_Tree.InsertItem(str_GrouopName);                                 //插入好友列表(CTreeControl)
		sql.m_pReset->Update();														 //更新数据库
		sql.CloseConn();															 //关闭数据库连接
	}
	catch(...)
	{
		MessageBox(_T("插入好友分组出错啦！(＞﹏＜) "));
		return;
	}
	CAddGroup::OnCancel();                            //默认按下取消按钮，用以关闭对话框
}

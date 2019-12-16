// CLoginDig.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "CLoginDig.h"
#include "afxdialogex.h"
#include "InfoFile.h"

// CLoginDig 对话框

IMPLEMENT_DYNAMIC(CLoginDig, CDialogEx)

CLoginDig::CLoginDig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLogin, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDig::~CLoginDig()
{
}

void CLoginDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDig::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDig::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDig 消息处理程序

//确认登陆
void CLoginDig::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//登陆按钮，点击事件
	UpdateData(true);
	if (m_user.IsEmpty() || m_pwd.IsEmpty()) {
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	//获取正确的账号密码
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (name == m_user) {
		if (pwd == m_pwd) {
			//关闭当前对话框
			CDialog::OnCancel();
		}
		else {
			MessageBox(TEXT("用户名或密码错误"));
		}
	}
	else {
		MessageBox(TEXT("用户名或密码错误"));
	}
}


BOOL CLoginDig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//默认登录信息显示
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_user = name;
	m_pwd = pwd;
	//同步到控件中
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//取消登陆
void CLoginDig::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

//重写函数
void CLoginDig::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDig::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//关闭当前对话框
	//CDialogEx::OnClose();
	exit(0);
}

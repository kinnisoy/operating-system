// Distrbute.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "Distrbute.h"
#include "afxdialogex.h"


// Distrbute 对话框

IMPLEMENT_DYNAMIC(Distrbute, CDialogEx)

Distrbute::Distrbute(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GetMem, pParent)
	, m_zoom(_T(""))
{

}

Distrbute::~Distrbute()
{
}

void Distrbute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_zoom);
}


BEGIN_MESSAGE_MAP(Distrbute, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Distrbute::OnBnClickedButton1)
END_MESSAGE_MAP()


// Distrbute 消息处理程序

//确认按钮
void Distrbute::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

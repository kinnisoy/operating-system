// MemRC.cpp: 内存回收实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "MemRC.h"
#include "afxdialogex.h"


// MemRC 对话框

IMPLEMENT_DYNAMIC(MemRC, CDialogEx)

MemRC::MemRC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Recov, pParent)
	, m_num(_T(""))
{

}

MemRC::~MemRC()
{
}

void MemRC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_num);
}


BEGIN_MESSAGE_MAP(MemRC, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MemRC::OnBnClickedButton1)
END_MESSAGE_MAP()


// MemRC 消息处理程序


void MemRC::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

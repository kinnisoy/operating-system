// CInsertPro.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "CInsertPro.h"
#include "afxdialogex.h"

using namespace std;
// CInsertPro 对话框

IMPLEMENT_DYNAMIC(CInsertPro, CDialogEx)

CInsertPro::CInsertPro(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT, pParent)
	, m_pid()
	, m_priority()
	, m_arrivetime()
	, m_servertime()
{

}

CInsertPro::~CInsertPro()
{
}

void CInsertPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_pid);
	DDX_Control(pDX, IDC_EDIT2, m_priority);
	DDX_Control(pDX, IDC_EDIT3, m_arrivetime);
	DDX_Control(pDX, IDC_EDIT4, m_servertime);
	DDX_Control(pDX, IDC_EDIT1, m_pid);
}


BEGIN_MESSAGE_MAP(CInsertPro, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CInsertPro::OnBnClickedButton3)
END_MESSAGE_MAP()


// CInsertPro 消息处理程序
//添加进程主函数
void CInsertPro::insert_process()
{
	//获取窗口中内容
	CString pid,priority,arrivetime,servertime;
	m_pid.GetWindowTextW(pid);
	m_priority.GetWindowTextW(priority);
	m_arrivetime.GetWindowTextW(arrivetime);
	m_servertime.GetWindowTextW(servertime);
	ofstream file;
	file.open(_F_PROCESS, ios::app);
	if (!file) {
		//abort();//打開失敗，結束程序
	}
	else {
		file <<_ttoi(pid) << "|" << _ttoi(priority) << "|" << _ttoi(arrivetime) << "|" << _ttoi(servertime) << endl;
		file.close();
	}
}

//确认添加进程按钮
void CInsertPro::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加进程
	insert_process();
	//关闭当前对话框
	CDialog::OnCancel();
}

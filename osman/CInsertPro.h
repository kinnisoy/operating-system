#pragma once
#include <fstream>
#include"CDprocess.h"
#define _F_PROCESS "./process.ini"
// CInsertPro 对话框

class CInsertPro : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertPro)

public:
	CInsertPro(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInsertPro();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_pid;
	CEdit m_priority;
	CEdit m_arrivetime;
	CEdit m_servertime;
	void insert_process();
public:
	afx_msg void OnBnClickedButton3();
	
	afx_msg void OnEnChangeEdit1();
};

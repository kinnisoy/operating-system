
// osmanDlg.h: 头文件
//

#pragma once
#include "TabSheet.h"
#include "CDprocess.h"
#include "CDmemory.h"
#include "CDISK.h"
// CosmanDlg 对话框
class CosmanDlg : public CDialogEx
{
// 构造
public:
	CosmanDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OSMAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CTabSheet m_tab;
	CDprocess dl_proc;
	CDmemory dl_memo;
	CDISK dl_hand;
};

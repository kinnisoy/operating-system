#pragma once


// MemRC 对话框

class MemRC : public CDialogEx
{
	DECLARE_DYNAMIC(MemRC)

public:
	MemRC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MemRC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Recov };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_num;
	afx_msg void OnBnClickedButton1();
};

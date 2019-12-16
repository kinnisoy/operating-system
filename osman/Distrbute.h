#pragma once


// Distrbute 对话框

class Distrbute : public CDialogEx
{
	DECLARE_DYNAMIC(Distrbute)

public:
	Distrbute(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Distrbute();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GetMem };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_zoom;
	afx_msg void OnBnClickedButton1();
};

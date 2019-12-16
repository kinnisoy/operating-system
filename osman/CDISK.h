#pragma once
#define _F_ORDER "order.ini"
#define MAX 20
#include"sstream"  //字符串流


// CDhandle 对话框
using namespace std;
class CDISK : public CDialogEx
{
	DECLARE_DYNAMIC(CDISK)

public:
	CDISK(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDISK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DISK};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	
	CEdit m_num;
	CEdit m_curr;
	
	CComboBox m_algorithm;
	CString m_show;
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	void get_order();
	void print_order();
	void FIFO(int array[], int m);
	void SSTF(int array[], int m);
	void SCAN(int array[], int m);
	void CSCAN(int array[], int m);
	//int m_order[MAX];
	int a;//表示当前的算法
private:
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
private:
//	CEdit m_text;
	CString m_text;
};

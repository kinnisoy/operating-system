#pragma once
#include "Distrbute.h"
#include"MemRC.h"
#define OK 1//完成
#define ERROR 0 //出错
typedef int Status;


// CDmemory 对话框

class CDmemory : public CDialogEx
{
	DECLARE_DYNAMIC(CDmemory)

public:
	CDmemory(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDmemory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int request = 0;//申请的大小
private:
	typedef struct free_table {//空闲区说明表结构 
		int num;//分区号
		long address;//地址
		long length; //分区大小
		int state;//分区状态

	}ElemType;


	typedef struct Node {//线性表的双向链表存储结构
		ElemType data;
		struct Node* prior;
		struct Node* next;

	} Node, *LinkList;

	LinkList first;//头节点
	LinkList end;//尾节点
	int flag; //记录要删除的分区号

	Status Initblock();//开创带头节点的内存空间链表
	void sort();//分区序号重新排序
	  //显示主存分配情况
	void show();
	//首次适应算法
	Status First_fit(int request);
	Status Worst_fit(int request);
	Status Best_fit(int request);
	//分配主存
	Status allocation(int a);
	Status deal1(Node *p);//处理回收空间
	Status deal2(Node *p);//处理回收空间
	  //主存回收
	Status recovery(int flag);
	CListCtrl m_list;
	int a;//使用的算法
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
private:
	INT m_choose;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};



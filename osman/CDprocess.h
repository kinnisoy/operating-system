#pragma once
//#include "process.h"  //包含全局变量，引用引起连接错误
#pragma warning(disable:4996)
#include"sstream"  //字符串流
#include <string.h>
#include <list>
#include <fstream>
#include <iostream>
#include <queue>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include"CInsertPro.h"
#define NUM 10

#define _F_PROCESS "./process.ini"
using namespace std;
// CDprocess 对话框
//class PCB; //前置声明，防止报错

class CDprocess : public CDialogEx
{
	DECLARE_DYNAMIC(CDprocess)

public:
	CDprocess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDprocess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();


	//从文件获取进程信息
	void get_process(int id[], int prority[], int atime[], int stime[]);
	//显示在list控件
	void print_process();

private:
	CListCtrl m_protext;
	int id[NUM], prority[NUM], atime[NUM], stime[NUM];
public:
	virtual BOOL OnInitDialog();
private:
//	CString m_showstr;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();

private:
	//进程有三种状态，这里增加一种，表示虽然输入，但还没有到达进入系统时刻
	typedef enum ProcessState { Executing, Ready, Finish, Unarrive } STATE;

	//进程控制块PCB的定义
	typedef struct process_pcb {
		int ID;//进程标识
		int priority;//进程优先数，值越大，优先级越高
		int arrive_time;//进程到达时间，以时间片为单位
		int service_time;//进程需要总的服务时间，以时间片为单位
		int start_time;//进程开始执行时间，以时间片为单位
		int end_time;//进程结束时间，以时间按片为单位
		int all_time;//进程仍然需要的运行时间，以时间片为单位
		int cpu_time;//进程已占用CPU时间，以时间片为单位
		STATE state;//进程状态
	}PCB;

	const char* StateString[4] = { "Executing","Ready", "Finish", "--" };//用于打印三种状态
	PCB * running_process = NULL;//当前运行任务
	vector<PCB>input_queue;//输入队列，存放到达时刻大于当前时刻的进程
	vector<PCB>ready_queue;//就绪队列
	vector<PCB>finish_queue;//完成队列
	list<PCB> pcb_list;  //存储进程容器
static bool cmp_arrive_time(const PCB a, const PCB b);//输入队列按进程到达时间排序函数
static bool cmp_priority(const PCB a, const PCB b);//就绪队列按进程优先数排序函数
	void input_process();//输入进程信息
	int select_policy();//选择进程调度策略
	void print_all(int current);//打印所有进程信息

	void FCFS();//先来先服务算法
	void round_robin();//时间片轮转算法
	void dynamic_prio();//动态优先级算法
	//显示单个进程信息
	void print_one(PCB *pro);

	
	
public:
	int num;//进程数量
	CString m_showstr;
	afx_msg void OnBnClickedButton2();
};

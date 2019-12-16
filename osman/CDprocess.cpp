// CDprocess.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "CDprocess.h"
#include "afxdialogex.h"



// CDprocess 对话框

IMPLEMENT_DYNAMIC(CDprocess, CDialogEx)

CDprocess::CDprocess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PRO, pParent)
	, m_showstr(_T(""))
{

}

CDprocess::~CDprocess()
{
}

void CDprocess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_protext);
	DDX_Text(pDX, IDC_EDIT1, m_showstr);
	//DDX_Control(pDX, IDC_EDIT1, m_showstr);
}


BEGIN_MESSAGE_MAP(CDprocess, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDprocess::OnBnClickedButton1)
	
	ON_EN_CHANGE(IDC_EDIT1, &CDprocess::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDprocess::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDprocess::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDprocess 消息处理程序

//点击加载进程信息按钮，从文本读取进程信息并输出到列表控件
void CDprocess::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空当前列表
	m_protext.DeleteAllItems();
	//清空當前隊列
	input_queue.clear();
	ready_queue.clear();
	finish_queue.clear();
	//设置显示进程管理窗口的编辑框
	input_process();//从文件读取写入数组
	print_process();//将数组输出
	/*CString str;
	str.Format(TEXT("%d"), num);
	MessageBox(str);*/
	//同步更新数据
	UpdateData(FALSE);

}
//输出文件中进程信息到列表控件框
void CDprocess::print_process()
{
		//if (pro == NULL)
		//{
		//	return;
		//}
		//ostringstream cout;
		//cout << pro->ID<< "\t" << "."<<endl;
		//cout << "\n"<<"2";
		//string str = cout.str();
		////m_protext = (CString)str.c_str();
	CString str;
	/*str.Format(TEXT("%d"), num);
	MessageBox(str);*/
	   //int j=0;
	   for (int i = 0;i < num;i++) {
		   //设置正文
		   str.Format(TEXT("%d"), id[i]);
		   //MessageBox(str);
			m_protext.InsertItem(i,str );
			
			//给一行其他列添加内容
			str.Format(TEXT("%d"), prority[i]);
			m_protext.SetItemText(i,1,str);
			str.Format(TEXT("%d"), atime[i]);
			m_protext.SetItemText(i, 2, str);
			str.Format(TEXT("%d"), stime[i]);
			m_protext.SetItemText(i, 3, str);

	   }
	   
	   
}
//从process.ini读取初始化进程信息，写入数组
void CDprocess::get_process(int id[], int prority[], int atime[], int stime[])
{
	ifstream ifs;
	ifs.open(_F_PROCESS);	//输入方式打开文件

	char buf[1024] = { 0 };
	int numb = 0;	//初始化进程数量为0
	num = 0;
	//取出表头   
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())	//没到文件结尾
	{
		//PCB tmp;//建立临时PCB

		ifs.getline(buf, sizeof(buf));	//读取一行


		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|");	//以"|"分隔
		if (sst != NULL)
		{
			id[numb] = atoi(sst);	//进程	id
			
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		prority[numb] = atoi(sst);	//进程优先级

		sst = strtok(NULL, "|");
		atime[numb] = atoi(sst);	//到达时间

		sst = strtok(NULL, "|");
		stime[numb] = atoi(sst);	//服务时间
		numb++;	//进程数量加一

	}
	
	num = numb;
	ifs.close();	//关闭文件
}
//将数组内容变量写入PCB
void CDprocess::input_process()
{
	get_process(id, prority, atime, stime);
	int numb;
	numb = num;
	PCB pro;//定义进程的进程控制块
	for (int i = 0; i < numb;i++) {
		pro.arrive_time = atime[i];
		pro.service_time = stime[i];
		pro.priority = prority[i];
		pro.ID = id[i];
		pro.all_time = pro.service_time;
		pro.cpu_time = 0;
		pro.start_time = -1;//开始及几万数时间默认wier-1,表示进程尚未被调度过
		pro.end_time = -1;
		pro.state = Unarrive;//初始化为尚未进入系统
		input_queue.push_back(pro);
	}
	sort(input_queue.begin(), input_queue.end(),cmp_arrive_time);//按到达时间升序排队
	//默认升序
	//sort(input_queue.begin(), input_queue.end());
}



//对话框初始化函数
BOOL CDprocess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置网格属性
	m_protext.SetExtendedStyle(m_protext.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//设置表头
	CString str[] = { TEXT("PID"),TEXT("优先级"),TEXT("到达时间"),TEXT("服务时间") };
	for(int i = 0;i < 4;i++) {
		m_protext.InsertColumn(i, str[i],LVCFMT_CENTER,100);
	}
	//设置正文
	//m_protext.InsertItem(0, TEXT("1") );
	//给一行其他列添加内容
	//m_protext.SetItemText(0, 1, TEXT("3"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDprocess::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//调度进程按钮，点击后将调度信息显示在edit control
void CDprocess::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//测试样例，输出多行文字
	/*ostringstream cout;
		cout << "111"<< "\t" << "."<<endl;
		cout << "\r\n"<<"2";
		string str = cout.str();
		m_showstr = (CString)str.c_str();*/
	
	//进行调度
	//dynamic_prio();
	//vector<PCB>::iterator it;
	//it = input_queue.begin();
	//print_one(&input_queue.front());
	//print_all(0);
	dynamic_prio();
	//同步更新数据
	UpdateData(FALSE);//将变量中的内容同步到控件中，

}

void CDprocess::dynamic_prio()
{
	int chip = 0;//初始的时间片为0
	bool need_schedule = true;//需要调度的标志，默认为true
	print_all(chip);//test
	while (1) {//如果当前没有正在运行进程，并且输入队列和就绪队列都为空，则所有进程完成
		if (!running_process && input_queue.empty() && ready_queue.empty())
			break;
		
		while (!input_queue.empty()) {//将到达时间小于等于当前时间片的进程从输入队列移到就绪队列中
			PCB pro = input_queue[0];
			if (pro.arrive_time <= chip) {
				pro.state = Ready;
				ready_queue.push_back(pro);//放入就绪列队尾
				input_queue.erase(input_queue.begin() + 0);//从输入队列中删除
			}
			else {
				break;
			}
		}
		if (!ready_queue.empty()) {
			sort(ready_queue.begin(), ready_queue.end(), cmp_priority);//按优先级降序排列
		}
		
		if (need_schedule && !ready_queue.empty()) {//判断是否需要调度，如果需要就从就绪队列取出队首进程进行调度
			running_process = new PCB;
			*running_process = ready_queue[0];//取出就绪队首进程
			ready_queue.erase(ready_queue.begin() + 0);//从就绪队列中删除之

			running_process->start_time = chip;//调度进程开始运行
			running_process->state = Executing;
			need_schedule = false;
		}

		print_all(chip);//打印当前时刻所有进程的信息

		if (running_process) {//当前运行任务完成一个时间片，判断任务是否完成，更改其信息
			running_process->cpu_time += 1;
			running_process->all_time -= 1;
			if (running_process->all_time == 0) {//任务运行结束
				running_process->end_time = chip + 1;
				running_process->state = Finish;
				finish_queue.push_back(*running_process);//将其放入完成队列
				delete running_process;
				running_process = NULL;
				need_schedule = true;
			}
			else {//任务未完成，如果就绪队列仍有任务，且优先级大于本任务优先级，则轮转调度，否则不调度
				if (running_process->priority > 1) {
					running_process->priority -= 1;
				}
				if (!ready_queue.empty() && ready_queue.begin()->priority > running_process->priority) {
					running_process->state = Ready;
					ready_queue.push_back(*running_process);//将其放回就绪队列
					delete running_process;
					running_process = NULL;
					need_schedule = true;
				}
				else {
					need_schedule = false;
				}
			}
		}
		chip += 1;
	}
	print_all(chip);

}

void CDprocess::print_one(PCB * pro)
{
	if (pro == NULL) {
		return;
	}
	ostringstream cout;
	//cout << "PID\t" << "优先级\t" << "到达时间\t" << "服务时间"<<"\r\n";
	cout << setw(8) << pro->ID << setw(12) << pro->arrive_time << setw(18) << pro->service_time << setw(18) << pro->priority <<setw(14)<<StateString[pro->state] ;
	//string str = cout.str();
	//m_showstr = (CString)str.c_str();
	//printf("%4d%10d%10d%6d%15s", pro->ID, pro->arrive_time, pro->service_time, pro->priority, StateString[pro->state]);
	//如果进程尚未开始，则开始时间、结束时间以及剩余时间以”--“来表示
	//如果进程已经开始，但尚未结束，则其时间以”--“表示
	if (pro->start_time == -1) {
		cout << setw(15) << "--" << setw(18) << "--" << setw(18) << "--" ;
	}
	else {
		if (pro->end_time == -1) {			
			cout << setw(15) << pro->start_time << setw(18) << "--" << setw(18) << pro->all_time ;
		}
		else {
			cout << setw(15) << pro->start_time << setw(18) << pro->end_time << setw(18) << pro->all_time ;
		}
	}

	if (pro->state == Finish) {//进程结束，统计其周转时间及加权周转时间
		cout << setw(18) << pro->end_time - pro->start_time << setw(18) << (float)(pro->end_time - pro->arrive_time) / (float)pro->service_time << "\r\n";
	}
	else {
		cout << setw(18) << "--" << setw(18) << "--" << "\r\n";
	}
	string str = cout.str();
	m_showstr.Append((CString)str.c_str());
}


bool CDprocess::cmp_arrive_time(const PCB a, const PCB b)
{
	return a.arrive_time < b.arrive_time;
}

bool CDprocess::cmp_priority(const PCB a, const PCB b)
{
	if (a.priority != b.priority) {
		return a.priority > b.priority;
	}
	else {
		return a.arrive_time < b.arrive_time;
	}
}



void CDprocess::print_all(int current)
{
	m_showstr = _T("");
	UpdateData(FALSE);
	ostringstream cout;
	string str;
	if (current == -1) {
		cout << "\n进程初始状态： \r\n";
		//str = cout.str();
		//m_showstr = (CString)str.c_str();
		//cout.clear();//清除流中数据
	}
	else {
		cout << "\n当前时刻为： " << current << "\r\n";
		//str = cout.str();
		//m_showstr = (CString)str.c_str();
		//cout.clear();//清除流中数据
	}
	//cout.str("");
	cout<<"进程号 | 到达时间 | 服务时间 | 优先级 |  状态  | 开始时间 | 结束时间 | 剩余时间 | 周转时间 | 带权周转时间\t\r\n";
	str = cout.str();
	m_showstr = (CString)str.c_str();
	//cout.clear();//清除流中数据

	//打印正在运行的进程
	if (running_process != NULL) {
		print_one(running_process);
	}
	vector<PCB>::iterator it;

	for (it = ready_queue.begin();it != ready_queue.end();it++) {//打印就绪队列中的进程
		print_one(&(*it));
	}

	for (it = finish_queue.begin();it != finish_queue.end();it++) {//打印完成队列中的进程
		print_one(&(*it));
	}

	for (it = input_queue.begin();it != input_queue.end();it++) {//打印仍然在输入队列中的进程
		print_one(&(*it));
	}
	cout.clear();//清除流中数据(标志位)
	cout.str("");
	cout << "============================================================================\r\n";
	str = cout.str();
	m_showstr.Append((CString)str.c_str());

}

//新建进程按钮
void CDprocess::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示出弹窗
	//num++;
	CInsertPro pro;
	pro.DoModal();
}

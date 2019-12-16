// CDhandle.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "CDISK.h"
#include "afxdialogex.h"
#include "InfoFile.h"
int m_order[MAX];
// CDhandle 对话框

IMPLEMENT_DYNAMIC(CDISK, CDialogEx)

CDISK::CDISK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DISK, pParent)
	, m_show(_T(""))
	, m_text(_T(""))
{

}

CDISK::~CDISK()
{
}

void CDISK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_num);
	DDX_Control(pDX, IDC_EDIT2, m_curr);
	DDX_Control(pDX, IDC_COMBO1, m_algorithm);
	//DDX_String(pDX, IDC_EDIT3, m_show);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//  DDX_Control(pDX, IDC_EDIT3, m_text);
	DDX_Text(pDX, IDC_EDIT3, m_text);
}


BEGIN_MESSAGE_MAP(CDISK, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDISK::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDISK::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDISK::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDISK::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CDhandle 消息处理程序


void CDISK::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CInfoFile file;
	//CString name;
	//CString pwd;
	//file.ReadLogin(name,pwd);
	//MessageBox(name);
	//MessageBox(pwd);
	
	//CDialogEx::OnOK();
}

//磁盘调度按钮
void CDISK::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_show = _T("");
	UpdateData(FALSE);
	//获取当前磁道位置
	CString str;
	int curr,num;
	m_curr.GetWindowTextW(str);
	if (str.GetLength() == 0) {
		MessageBox(_T("输入当前磁道位置！"), _T("提示！"));
		return;
	}
	curr = _ttoi(str);
	m_num.GetWindowTextW(str);
	num = _ttoi(str);
	switch (a+1) {
	//算法选择
		
		case 1:
			FIFO(m_order, num);//先进先出算法
			//MessageBox(TEXT("111111"));
			break;
		case 2:
			SSTF(m_order, num);//最短服务时间优先算法
			break;
		case 3:
			SCAN(m_order,num);//扫描算法
			break;
		case 4:
			CSCAN(m_order, num);//循环扫描算法
			break;
	}
	
	//m_text = TEXT("222");
	UpdateData(FALSE);
}


BOOL CDISK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//下拉框添加
	m_algorithm.AddString(TEXT("先来先服务(FCFS)"));
	m_algorithm.AddString(TEXT("最短寻道时间优先(SSTF)"));
	m_algorithm.AddString(TEXT("电梯算法（SCAN)"));
	m_algorithm.AddString(TEXT("循环扫描算法(CSCAN)"));
	//设置默认显示
	m_algorithm.SetCurSel(0);
	//输入序列框属性设置
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, TEXT("序列"), LVCFMT_CENTER, 190);
	a = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




//从order.ini读取磁道序列信息，写入数组
void CDISK::get_order()
{
	ifstream ifs;
	ifs.open(_F_ORDER);	//输入方式打开文件
	int i = 0;
	char buf[1024] = { 0 };
	while (!ifs.eof())	//没到文件结尾
	{
		ifs.getline(buf, sizeof(buf));	//读取一行
		char *sst = buf;
		if (sst != NULL)
		{
			m_order[i] = atoi(sst);	
		}
		else
		{
			break;
		}
		i++;
	}
	ifs.close();	//关闭文件
}
//输出文件中进程信息到列表控件框
void CDISK::print_order()
{
	CString str;
	int num;
	m_num.GetWindowTextW(str);
	if (str.GetLength()==0)//字符串长度为0，没有输入磁道数量
	{
		MessageBox(_T("请先输入磁道数量"), _T("提示"));
		return;
	}
	num = _ttoi(str);
	for (int i = 0;i < num;i++) {
		//设置正文
		str.Format(TEXT("%d"), m_order[i]);
		//MessageBox(str);
		m_list.InsertItem(i, str);
	}
	//当前磁道默认显示磁道序列的第一个
	/*str.Format(TEXT("%d", m_order[0]));
	m_curr.SetWindowText(str);*/
}
//确认按钮,显示磁道信息
void CDISK::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断是否输入磁道数量和当前磁道
	CString str;
	m_num.GetWindowTextW(str);
	if (str.GetLength() == 0)//字符串长度为0，没有输入磁道数量
	{
		MessageBox(_T("请先输入磁道数量"), _T("提示"));
		return;
	}
	m_curr.GetWindowTextW(str);
	if (str.GetLength() == 0)//字符串长度为0，没有输入当前磁道位置
	{
		MessageBox(_T("开始调度之前记得确认当前磁道"), _T("提示"));
	}
	//清空当前列表信息
	m_list.DeleteAllItems();
	get_order();
	print_order();

}
//先进先出调度算法
void CDISK::FIFO(int array[], int m)
{	
	CString str;
	int sum = 0, j, i, now;
	float avg;
	//获取当前的磁道号： 
	m_curr.GetWindowTextW(str);
	now = _ttoi(str);
	// FIFO 调度结果: 
	ostringstream cout;
	
	cout << "当前磁道号：" << now << "\r\n"<<"FIFO 调度结果:";
	cout << now;
	for (i = 0; i < m; i++) 
		cout<< array[i]<<" ";
	sum = abs(now - array[0]);
	for (j = 1; j < m; j++) 
		sum += abs(array[j] - array[j - 1]); //累计总的移动距离
	avg = (float)sum / m;//计算平均寻道长度
	cout<<"\r\n移动的总道数： "<<sum<<"\r\n";
	cout<<"平均寻道长度： "<< avg<<"\r\n";
	string str1;
	str1 = cout.str();
	m_text = (CString)str1.c_str();
	//m_show.Append((CString)str1.c_str());
}
//最短服务时间优先调度算法
void CDISK::SSTF(int array[], int m)
{
	CString str;
	int temp;
	int k = 1;
	int now, l, r;
	int i, j, sum = 0;
	float avg;
	m_curr.GetWindowTextW(str);
	now = _ttoi(str);
	ostringstream cout;
	for (i = 0; i < m; i++)
	{
		for (j = i + 1; j < m; j++) //对磁道号进行从小到大排列
		{
			if (array[i] > array[j])//两磁道号之间比较
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	for (i = 0; i < m; i++) //输出排序后的磁道号数组
		cout<< array[i]<<" ";
	cout<<"\r\nSSTF 调度结果: ";
	if (array[m - 1] <= now)//判断整个数组里的数是否都小于当前磁道号
	{
		for (i = m - 1; i >= 0; i--) //将数组磁道号从大到小输出
			cout<<array[i]<<" ";
		sum = now - array[0];//计算移动距离
	}
	else if (array[0] >= now)//判断整个数组里的数是否都大于当前磁道号
	{
		for (i = 0; i < m; i++) //将磁道号从小到大输出
			cout << array[i] << " ";
		sum = array[m - 1] - now;//计算移动距离
	}
	else
	{
		while (array[k] < now)//逐一比较以确定 K 值
		{
			k++;
		}
		l = k - 1;
		r = k;
		//确定当前磁道在已排的序列中的位置
		while ((l >= 0) && (r < m))
		{
			if ((now - array[l]) <= (array[r] - now))//判断最短距离
			{
				cout<< array[l]<<" ";
				sum += now - array[l];//计算移动距离
				now = array[l];
				l = l - 1;
			}
			else
			{
				cout<<array[r]<<" ";
				sum += array[r] - now;//计算移动距离
				now = array[r];
				r = r + 1;
			}
		}
		if (l = -1)
		{
			for (j = r; j < m; j++)
			{
				cout<<array[j]<<" ";
			}
			sum += array[m - 1] - array[0];//计算移动距离
		}
		else
		{
			for (j = l; j >= 0; j--)
			{
				cout << array[j]<<" ";
			}
			sum += array[m - 1] - array[0];//计算移动距离
		}
	}
	avg = (float)sum / m;
	cout<<"\r\n移动的总道数： "<<sum<<"\r\n";
	cout<<"平均寻道长度："<< avg<<"\r\n";
	string str1;
	str1 = cout.str();
	m_text = (CString)str1.c_str();
}
///扫描算法
void CDISK::SCAN(int array[], int m)
{
	
	int now;
	int sum = 0;
	CString str;
	m_curr.GetWindowTextW(str);
	now = _ttoi(str);
	ostringstream cout;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++) //对磁道号进行从小到大排列
		{
			if (array[i] > array[j])//两磁道号之间比较
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		cout<< array[i]<<" ";
	}
	
	
	
	cout<<"\r\nSCAN 调度结果：";
	int pos;
	for (int i = 0; i < m; i++)
	{
		if (array[i] >= now)
		{
			pos = i;
			sum += abs(array[i] - now);
			break;
		}
	}
	for (int i = pos; i < m; i++)
	{
		if (i != pos)
			sum += abs(array[i] - array[i - 1]);
		cout<<array[i]<<" ";
	}
	if (pos >= 1)
		sum += abs(array[m - 1] - array[pos - 1]);
	for (int i = pos - 1; i >= 0; i--)
	{
		if (i)
			sum += abs(array[i] - array[i - 1]);
		cout << array[i] << " ";
	}
	cout<<"\r\n移动的总道数："<<sum<<"\r\n平均寻道长度："<< 1.0*sum / m<<"\r\n";
	string str1;
	str1 = cout.str();
	m_text = (CString)str1.c_str();
}
///循环扫描算法
void CDISK::CSCAN(int array[], int m)
{	
	int now;
	int sum = 0;
	CString str;
	m_curr.GetWindowTextW(str);
	now = _ttoi(str);
	ostringstream cout;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++) //对磁道号进行从小到大排列
		{
			if (array[i] > array[j])//两磁道号之间比较
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		cout<<array[i]<<" ";
	}
	
	
	
	cout<<"\r\nC-SCAN 调度结果："<<" ";
	int pos=0;
	for (int i = 0; i < m; i++)
	{
		if (array[i] >= now)
		{
			pos = i;
			sum += abs(array[i] - now);
			break;
		}
	}
	for (int i = pos; i < m; i++)
	{
		if (i != pos)
			sum += abs(array[i] - array[i - 1]);
		cout << array[i] << " ";
	}
	if (pos >= 1)
		sum += abs(array[m - 1] - array[0]);
	for (int i = 0; i < pos; i++)
	{
		if (i)
			sum += abs(array[i] - array[i - 1]);
		cout << array[i] << " ";
	}
	cout<<"\r\n移动的总道数："<<sum<<"\r\n平均寻道长度："<< 1.0*sum / m<<"\r\n";
	string str1;
	str1 = cout.str();
	m_text = (CString)str1.c_str();
}

void CDISK::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//拿到索引位置
	int index = m_algorithm.GetCurSel();
	CString str;
	m_algorithm.GetLBText(index, str);
	//str中为当前使用的调度算法
	//MessageBox(str,TEXT("提示"));
	a = index;
}

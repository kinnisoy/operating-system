// CDmemory.cpp: 实现文件
//

#include "stdafx.h"
#include "osman.h"
#include "CDmemory.h"
#include "afxdialogex.h"


// CDmemory 对话框

IMPLEMENT_DYNAMIC(CDmemory, CDialogEx)

CDmemory::CDmemory(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MEM, pParent)
	, m_choose(0)
{

}

CDmemory::~CDmemory()
{
}

void CDmemory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Radio(pDX, IDC_RADIO1, m_choose);
}


BEGIN_MESSAGE_MAP(CDmemory, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDmemory::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDmemory::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDmemory::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDmemory::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &CDmemory::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDmemory::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDmemory::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CDmemory 消息处理程序


BOOL CDmemory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//设置表头
	CString str[] = { TEXT("分区号"),TEXT("开始地址"),TEXT("结束地址"),TEXT("分区大小"),TEXT("分配状态") };
	for (int i = 0;i < 5;i++) {
		m_list.InsertColumn(i, str[i], LVCFMT_CENTER, 90);
	}
	Initblock();
	show();
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDmemory::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

Status CDmemory::Initblock()
{
	first = (LinkList)malloc(sizeof(Node));
	end = (LinkList)malloc(sizeof(Node));
	first->prior = NULL;
	first->next = end;
	end->prior = first;
	end->next = NULL;
	end->data.num = 1;
	end->data.address = 40;
	end->data.length = 600;
	end->data.state = 0;

	return OK;
}

void CDmemory::sort()
{
	Node *p = first->next, *q;
	q = p->next;
	for (;p != NULL;p = p->next)
	{
		for (q = p->next;q;q = q->next)
		{
			if (p->data.num >= q->data.num)
				q->data.num += 1;
		}
	}
}

void CDmemory::show()
{
	//清空当前列表
	m_list.DeleteAllItems();
	//开始显示
	int flag = 0;//记录分区序号
	Node *p = first;
	p->data.num = 0;
	p->data.address = 0;
	p->data.length = 40;
	p->data.state = 1;
	sort();
	//while (p)
	//{
	//	printf("%d\t\t%d\t\t%d", p->data.num, p->data.address, p->data.length);
	//	if (p->data.state == 0)  printf("\t\t空闲\n\n");
	//	else printf("\t\t已分配\n\n");
	//	p = p->next;
	//}

	CString str;
	//int i = 0;

	for (int i = 0;p;i++,p=p->next) {
		//设置正文
		str.Format(TEXT("%d"), p->data.num);
		//MessageBox(str);
		m_list.InsertItem(i, str);

		//给一行其他列添加内容
		str.Format(TEXT("%d"), p->data.address);
		m_list.SetItemText(i, 1, str);
		str.Format(TEXT("%d"), p->data.length+p->data.address);
		m_list.SetItemText(i, 2, str);
		str.Format(TEXT("%d"), p->data.length );
		m_list.SetItemText(i, 3, str);
		str.Format(TEXT("%d"), p->data.state);
		m_list.SetItemText(i, 4, str);
	}
}

Status CDmemory::First_fit(int request)
{
	//为作业开辟新空间且初始化
	Node *p = first->next;
	LinkList temp = (LinkList)malloc(sizeof(Node));
	temp->data.length = request;
	temp->data.state = 1;
	p->data.num = 1;
	while (p)
	{
		if ((p->data.state == 0) && (p->data.length == request))
		{//有大小恰好合适的空闲块
			p->data.state = 1;
			return OK;
			break;
		}

		else if ((p->data.state == 0) && (p->data.length > request))
		{
			//有空闲块能满足需求且有剩余
			temp->prior = p->prior;
			temp->next = p;
			temp->data.address = p->data.address;
			temp->data.num = p->data.num;
			p->prior->next = temp;
			p->prior = temp;
			p->data.address = temp->data.address + temp->data.length;
			p->data.length -= request;
			p->data.num += 1;
			return OK;
			break;
		}
		p = p->next;
	}
	return ERROR;
}

// 最差算法
Status CDmemory::Worst_fit(int request) {
	int ch;//记录最da剩余空间
	Node *p = first->next;
	Node *q = NULL;//记录最佳插入位置
	LinkList temp = (LinkList)malloc(sizeof(Node));
	temp->data.length = request;
	temp->data.state = 1;
	p->data.num = 1;
	while (p) { //初始化最大空间和最佳位置 
		if (p->data.state == 0 && p->data.length >= request)
		{
			if (q == NULL) {
				q = p;
				ch = p->data.length - request;
			}
			else if (q->data.length < p->data.length) {
				q = p;
				ch = p->data.length - request;
			}
		}
		p = p->next;
	}
	if (q == NULL) return ERROR;//没有找到空闲块
	else if (q->data.length == request) {
		q->data.state = 1;
		return OK;
	}
	else {
		temp->prior = q->prior;
		temp->next = q;
		temp->data.address = q->data.address;
		temp->data.num = q->data.num;
		q->prior->next = temp;
		q->prior = temp;
		q->data.address += request;
		q->data.length = ch;
		q->data.num += 1;
		return OK;
	}
	return OK;
}

//最佳适应算法
Status CDmemory::Best_fit(int request) {
	int ch;//记录最小剩余空间
	Node *p = first;
	Node *q = NULL;//记录最佳插入位置
	LinkList temp = (LinkList)malloc(sizeof(Node));
	temp->data.length = request;
	temp->data.state = 1;
	p->data.num = 1;
	while (p) { //初始化最小空间和最佳位置 
		if (p->data.state == 0 && p->data.length >= request)
		{
			if (q == NULL) {
				q = p;
				ch = p->data.length - request;
			}
			else if (q->data.length > p->data.length) {
				q = p;
				ch = p->data.length - request;
			}
		}
		p = p->next;
	}
	if (q == NULL) return ERROR;//没有找到空闲块
	else if (q->data.length == request) {
		q->data.state = 1;
		return OK;
	}
	else {
		temp->prior = q->prior;
		temp->next = q;
		temp->data.address = q->data.address;
		temp->data.num = q->data.num;
		q->prior->next = temp;
		q->prior = temp;
		q->data.address += request;
		q->data.length = ch;
		q->data.num += 1;
		return OK;
	}
	return OK;

}
Status CDmemory::allocation(int a)
{
	if (request < 0 || request == 0)
	{
		MessageBoxW(_T("分配大小不合适,请重试！"), _T("提示"));
		return ERROR;
	}
	switch (a)
	{
	case 1: //默认首次适应算法
		if (First_fit(request) == OK) MessageBoxW(_T("分配成功"), _T("提示"));
		else MessageBoxW(_T("内存不足，分配失败!"), _T("提示"));
		return OK;
		break;
	case 2: //最佳算法
		if (Best_fit(request) == OK) printf("*******分配成功********");
		else printf("*****内存不足，分配失败!*****");
		return OK;
		break;
	case 3: //最差算法
		if (Worst_fit(request) == OK) printf("*******分配成功********");
		else printf("*****内存不足，分配失败!*****");
		return OK;
		break;
	}
}

Status CDmemory::deal1(Node * p)
{
	Node *q = first;
	for (;q != NULL;q = q->next)
	{
		if (q == p)
		{
			if (q->prior->data.state == 0 && q->next->data.state != 0)
			{
				q->prior->data.length += q->data.length;
				q->prior->next = q->next;
				q->next->prior = q->prior;
				q = q->prior;
				q->data.state = 0;
				q->data.num = flag - 1;
			}
			if (q->prior->data.state != 0 && q->next->data.state == 0)
			{
				q->data.length += q->next->data.length;
				q->next = q->next->next;
				q->next->next->prior = q;
				q->data.state = 0;
				q->data.num = flag;
			}
			if (q->prior->data.state == 0 && q->next->data.state == 0)
			{
				q->prior->data.length += q->data.length;
				q->prior->next = q->next;
				q->next->prior = q->prior;
				q = q->prior;
				q->data.state = 0;
				q->data.num = flag - 1;
			}
			if (q->prior->data.state != 0 && q->next->data.state != 0)
			{
				q->data.state = 0;
			}
		}
	}
	return OK;
}//合并相邻空闲区

Status CDmemory::deal2(Node * p)
{
	Node *q = first;
	for (;q != NULL;q = q->next)
	{
		if (q == p)
		{
			if (q->prior->data.state == 0 && q->next->data.state != 0)
			{
				q->prior->data.length += q->data.length;
				q->prior->next = q->next;
				q->next->prior = q->prior;
				q = p->prior;
				q->data.state = 0;
				q->data.num = flag - 1;
			}
			if (q->prior->data.state != 0 && q->next->data.state == 0)
			{
				q->data.state = 0;
			}
			if (q->prior->data.state == 0 && q->next->data.state == 0)
			{
				q->prior->data.length += q->data.length;
				q->prior->next = q->next;
				q->next->prior = q->prior;
				q = q->prior;
				q->data.state = 0;
				q->data.num = flag - 1;
			}
			if (q->prior->data.state != 0 && q->next->data.state != 0)
			{
				q->data.state = 0;
			}
		}
	}
	return OK;
}//前面的节点不是first，后面的节点不是end

Status CDmemory::recovery(int flag)
{
	Node *p = first;
	for (;p != NULL;p = p->next)
	{
		if (p->data.num == flag)
		{
			if (p->prior == first)//第二个分区域 
			{
				if (p->next != end&&p->next!=nullptr)//当前p指向的下一个不是最后一个
				{
					if (p->next->data.state == 0) //与后面的 空闲块相连
					{
						p->data.length += p->next->data.length;
						p->next->next->prior = p;
						p->next = p->next->next;
						p->data.state = 0;
						p->data.num = flag;
					}
					else p->data.state = 0;
				}
				if (p->next == end) //当前p指向下一个是最后一个时
				{
					p->data.state = 0;
					p->next->prior = p->prior;
					p->prior->next = p->next;
					p->next->data.num = flag;
					p->next->data.length += p->data.length;
					p->next->data.address = p->data.address;
				}
			}//结束 if（p->prior == block_first）的情况 
			else if (p->prior != first)
			{
				if (p->next != end)
				{
					deal1(p);
				}
				else {
					deal2(p);
				}
			}//结束 if（p->prior != block_first）的情况 

		}//结束 if（p->data.num ==flag）的情况 
	}
	MessageBoxW(_T("回收成功"), _T("提示"));
	return OK;
}

//分配内存
void CDmemory::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Distrbute dis;
	if (dis.DoModal() != IDOK) {
		return;
	}
	request = _ttoi(dis.m_zoom);
	allocation(a);
	show();
}

//显示内存信息
void CDmemory::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//显示
	show();
}

//回收内存
void CDmemory::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MemRC mem;
	if (mem.DoModal() != IDOK) {
		return;
	}
	flag = _ttoi(mem.m_num);
	recovery(flag);
	show();
}

//点击首次适应算法
void CDmemory::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	a = 1;
}


void CDmemory::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	a = 2;
}


void CDmemory::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	a = 3;
}

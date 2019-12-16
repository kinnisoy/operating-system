#include "stdafx.h"
#include "InfoFile.h"
#pragma warning(disable:4996)
CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//读取登录信息
void CInfoFile::ReadLogin( CString &name, CString &pwd )
{
	ifstream ifs;	//创建文件输入对象
	ifs.open(_F_LOGIN);

	char buf[1024] ={0};

	ifs.getline(buf, sizeof(buf));	//读取一行内容
	name = CString(buf);	//将char* 转换为CString

	ifs.getline(buf, sizeof(buf));	//读取一行内容
	pwd = CString(buf);	//将char* 转换为CString

	ifs.close();	//关闭文件
}

//修改密码
void CInfoFile::WritePwd( char* name, char* pwd )
{
	ofstream ofs;	//创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件
	
	ofs<< name <<endl;	//name写入文件
	ofs<< pwd <<endl;	//pwd写入文件
	
	ofs.close();	//关闭文件
}

//读取商品的信息 
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK);	//输入方式打开文件

	char buf[1024] = {0};
	num = 0;	//初始化商品数量为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while(!ifs.eof())	//没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf));	//读取一行
		num++;	//商品数量加一

		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|");	//以"|"分隔
		if(sst != NULL)
		{
			tmp.id = atoi(sst);	//商品id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//商品名称

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);	//商品价格

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//商品数目

		ls.push_back(tmp);	//放在链表的后面
	}

	ifs.close();	//关闭文件
}

//商品写入文件
void CInfoFile::WriteDocline()
{
	ofstream ofs(_F_STOCK);	//输出方式打开文件
	string bt = "商品id|商品名|单价|库存";

	if(ls.size()>0)	//商品链表有内容才执行
	{
		ofs<< bt << endl;	//写入表头

		//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it!=ls.end(); it++)
		{
			ofs << it->id <<"|";
			ofs << it->name <<"|";
			ofs << it->price <<"|";
			ofs << it->num <<endl;
		}
	}
	ofs.close();
}

//添加新商品
//name:商品名称，num:库存，price:价格
void CInfoFile::Addline( CString name, int num, int price )
{
	msg tmp;

	if (ls.size() >0)
	{
		//商品名称，库存，价格有效
		if (!name.IsEmpty() && num>0 && price>0)
		{
			tmp.id = ls.size() + 1;	//id自动加1
			CStringA str;
			str = name;					//CString 转CStringA
			tmp.name=str.GetBuffer();//CString 转为char *, 商品名称
			tmp.num = num;			//库存
			tmp.price = price;		//价格
		
			ls.push_back(tmp);			//放在链表的后面
		}
	}
}


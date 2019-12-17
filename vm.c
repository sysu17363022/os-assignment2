#include<iostream>
using namespace std;

#define N 20 //访问序列数组大小
#define M 10  //内存块表数组大小

struct pt {
	int pno;	//页号
	int bno;	//块号
	int flag;	//状态位，为0时在不内存，为1时在内存
	int order;	//优先序列
};

/*------------------------------------------*/
/*输入函数*/
/*------------------------------------------*/
void input(int *a, int n)
{
	for (int i = 0; i < n; i++) { cin >> *a; a++; }
}

/*------------------------------------------*/
/*输出函数*/
/*------------------------------------------*/
void output(int *a, int n)
{
	for (int i = 0; i < n; i++) { cout << *a << '\t'; a++; }
	cout << '\n';
}

/*------------------------------------------*/
/*算法fifo && LRU函数*/
/*------------------------------------------*/
void fifo(int*vp_list, int*bs, int n, int m)
{
	pt ptlist[N];//定义结构数组


	int k = 0, flag, cn = 0, i, j;//cn——统计缺页数
	for (j = 0; j < m; j++)//赋初值
	{
		bs[j] = 0;
	}

	for (i = 0; i < n; i++)// 访问序列循环
	{
		flag = 0;
		for (j = 0; j < m; j++)
			if (vp_list[i] == bs[j]) { flag = 1; break; }
		if (flag == 1)//命中
		{
			ptlist[i].bno = j + 1;
			ptlist[i].flag = 1;
			ptlist[i].pno = vp_list[i];
		}
		else {
			ptlist[i].flag = 0;
			ptlist[i].pno = vp_list[i];

			bs[k] = vp_list[i];
			ptlist[i].bno = k + 1;
			k = (k + 1) % m;//取模——循环队列
			cn++;
		}
	}
	cout << "FIFO算法：\n";
	cout << "----------------------------------**\n";
	cout << "缺页率为：" << '\t' << (float)cn / n << '\n';
	cout << "-------------------------------------------------------------------**\n";
	cout << "序列号\n";
	cout << "-------------------------------------------------------------------**\n";
	for (i = 0; i < m; i++)
	{
		cout << vp_list[i] << "\t缺页!\t" << "直接存入内存块!\n";
		cout << "-------------------------------------------------------------------**\n";
	}
	for (i = m; i < n; i++)
	{
		if (ptlist[i].flag == 0)
			cout << vp_list[i] << "\t缺页!\t" << "调出------块号为" << ptlist[i].bno << "--页号为" << ptlist[i].pno << '\n';
		else cout << vp_list[i] << "\t命中!" << "\t位置------块号为" << ptlist[i].bno << "--页号为" << ptlist[i].pno << '\n';;
		cout << "-------------------------------------------------------------------**\n";
	}
}
void LRU(int*vp_list, int*bs, int n, int m)
{
	//----------------------------------------------------------------------------------------------**
	pt ptlist_LRU[N];
	int k = 0, flag, cn = 0, i, j;//cn——统计缺页数
	int com;
	for (j = 0; j < m; j++)//赋初值
	{
		bs[j] = 0;
	}
	for (j = 0; j < n; j++)ptlist_LRU[j].order = 0;

	for (i = 0; i < n; i++)// 访问序列循环
	{
		flag = 0;
		for (j = 0; j < m; j++)
			if (vp_list[i] == bs[j]) { flag = 1; break; }
		if (flag == 1)//命中
		{
			ptlist_LRU[i].bno = j + 1;
			ptlist_LRU[i].flag = 1;
			ptlist_LRU[i].pno = vp_list[i];
			ptlist_LRU[i].order--;
			com = ptlist_LRU[i].order;
			for (j = 0; j < m; j++)
				if (ptlist_LRU[j].order < com)
				{
					com = ptlist_LRU[j].order; k = ptlist_LRU[j].bno;
				}
		}

		else {
			ptlist_LRU[i].flag = 0;
			ptlist_LRU[i].pno = vp_list[i];

			bs[k] = vp_list[i];
			ptlist_LRU[i].bno = k + 1;

			if (i < m)k = (k + 1) % m;
			cn++;
		}
	}
	cout << "LRU*算法：\n";
	cout << "----------------------------------**\n";
	cout << "缺页率为：" << '\t' << (float)cn / n << '\n';
	cout << "-------------------------------------------------------------------**\n";
	cout << "序列号\n";
	cout << "-------------------------------------------------------------------**\n";
	for (i = 0; i < m; i++)
	{
		cout << vp_list[i] << "\t缺页!\t" << "直接存入内存块!\n";
		cout << "-------------------------------------------------------------------**\n";
	}
	for (i = m; i < n; i++)
	{
		if (ptlist_LRU[i].flag == 0)
			cout << vp_list[i] << "\t缺页!\t" << "调出------块号为" << ptlist_LRU[i].bno << "--页号为" << ptlist_LRU[i].pno << '\n';
		else cout << vp_list[i] << "\t命中!" << "\t位置------块号为" << ptlist_LRU[i].bno << "--页号为" << ptlist_LRU[i].pno << '\n';;
		cout << "-------------------------------------------------------------------**\n";
	}
}

/*------------------------------------------*/
/*主函数*/
/*------------------------------------------*/
void main()
{
	int vp_list[N], bs[M];//定义访问序列数组和内存块表数组
	int n, m, choose;
	cout << "输入序列个数：\n";
	cin >> n;
	cout << "输入内存块大小：\n";
	cin >> m;
	cout << "请输入访问序列：\n";
	input(vp_list, n);
	cout << "选FIFO算法输入1，选LRU*算法输入2：";
	cin >> choose;

	cout << "访问序列：" << endl;
	output(vp_list, n);
	cout << "**----------------------------------------**";
	cout << '\n';
	if (choose == 1)
		fifo(vp_list, bs, n, m);//调用fifo函数
	if (choose == 2)
		LRU(vp_list, bs, n, m);
}
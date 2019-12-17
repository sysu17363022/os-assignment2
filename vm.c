#include<iostream>
using namespace std;

#define N 20 //�������������С
#define M 10  //�ڴ��������С

struct pt {
	int pno;	//ҳ��
	int bno;	//���
	int flag;	//״̬λ��Ϊ0ʱ�ڲ��ڴ棬Ϊ1ʱ���ڴ�
	int order;	//��������
};

/*------------------------------------------*/
/*���뺯��*/
/*------------------------------------------*/
void input(int *a, int n)
{
	for (int i = 0; i < n; i++) { cin >> *a; a++; }
}

/*------------------------------------------*/
/*�������*/
/*------------------------------------------*/
void output(int *a, int n)
{
	for (int i = 0; i < n; i++) { cout << *a << '\t'; a++; }
	cout << '\n';
}

/*------------------------------------------*/
/*�㷨fifo && LRU����*/
/*------------------------------------------*/
void fifo(int*vp_list, int*bs, int n, int m)
{
	pt ptlist[N];//����ṹ����


	int k = 0, flag, cn = 0, i, j;//cn����ͳ��ȱҳ��
	for (j = 0; j < m; j++)//����ֵ
	{
		bs[j] = 0;
	}

	for (i = 0; i < n; i++)// ��������ѭ��
	{
		flag = 0;
		for (j = 0; j < m; j++)
			if (vp_list[i] == bs[j]) { flag = 1; break; }
		if (flag == 1)//����
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
			k = (k + 1) % m;//ȡģ����ѭ������
			cn++;
		}
	}
	cout << "FIFO�㷨��\n";
	cout << "----------------------------------**\n";
	cout << "ȱҳ��Ϊ��" << '\t' << (float)cn / n << '\n';
	cout << "-------------------------------------------------------------------**\n";
	cout << "���к�\n";
	cout << "-------------------------------------------------------------------**\n";
	for (i = 0; i < m; i++)
	{
		cout << vp_list[i] << "\tȱҳ!\t" << "ֱ�Ӵ����ڴ��!\n";
		cout << "-------------------------------------------------------------------**\n";
	}
	for (i = m; i < n; i++)
	{
		if (ptlist[i].flag == 0)
			cout << vp_list[i] << "\tȱҳ!\t" << "����------���Ϊ" << ptlist[i].bno << "--ҳ��Ϊ" << ptlist[i].pno << '\n';
		else cout << vp_list[i] << "\t����!" << "\tλ��------���Ϊ" << ptlist[i].bno << "--ҳ��Ϊ" << ptlist[i].pno << '\n';;
		cout << "-------------------------------------------------------------------**\n";
	}
}
void LRU(int*vp_list, int*bs, int n, int m)
{
	//----------------------------------------------------------------------------------------------**
	pt ptlist_LRU[N];
	int k = 0, flag, cn = 0, i, j;//cn����ͳ��ȱҳ��
	int com;
	for (j = 0; j < m; j++)//����ֵ
	{
		bs[j] = 0;
	}
	for (j = 0; j < n; j++)ptlist_LRU[j].order = 0;

	for (i = 0; i < n; i++)// ��������ѭ��
	{
		flag = 0;
		for (j = 0; j < m; j++)
			if (vp_list[i] == bs[j]) { flag = 1; break; }
		if (flag == 1)//����
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
	cout << "LRU*�㷨��\n";
	cout << "----------------------------------**\n";
	cout << "ȱҳ��Ϊ��" << '\t' << (float)cn / n << '\n';
	cout << "-------------------------------------------------------------------**\n";
	cout << "���к�\n";
	cout << "-------------------------------------------------------------------**\n";
	for (i = 0; i < m; i++)
	{
		cout << vp_list[i] << "\tȱҳ!\t" << "ֱ�Ӵ����ڴ��!\n";
		cout << "-------------------------------------------------------------------**\n";
	}
	for (i = m; i < n; i++)
	{
		if (ptlist_LRU[i].flag == 0)
			cout << vp_list[i] << "\tȱҳ!\t" << "����------���Ϊ" << ptlist_LRU[i].bno << "--ҳ��Ϊ" << ptlist_LRU[i].pno << '\n';
		else cout << vp_list[i] << "\t����!" << "\tλ��------���Ϊ" << ptlist_LRU[i].bno << "--ҳ��Ϊ" << ptlist_LRU[i].pno << '\n';;
		cout << "-------------------------------------------------------------------**\n";
	}
}

/*------------------------------------------*/
/*������*/
/*------------------------------------------*/
void main()
{
	int vp_list[N], bs[M];//�����������������ڴ�������
	int n, m, choose;
	cout << "�������и�����\n";
	cin >> n;
	cout << "�����ڴ���С��\n";
	cin >> m;
	cout << "������������У�\n";
	input(vp_list, n);
	cout << "ѡFIFO�㷨����1��ѡLRU*�㷨����2��";
	cin >> choose;

	cout << "�������У�" << endl;
	output(vp_list, n);
	cout << "**----------------------------------------**";
	cout << '\n';
	if (choose == 1)
		fifo(vp_list, bs, n, m);//����fifo����
	if (choose == 2)
		LRU(vp_list, bs, n, m);
}
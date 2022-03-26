#include <stdio.h>
#include <stdlib.h>
 
typedef struct bucket
{
	int number;    //����1�ĸ���
	int timestamp;    //����ʱ���
	struct bucket *next;
}bucket,*pbucket;
 
int window = 10000;    //���ڴ�С
int count[1000001];      //��ȷ���� 
int printFreq = 100000; //��ӡƵ�� 
 
int judge(pbucket h,int n);
 
int DGIM(pbucket h, int time, int window)
{
	pbucket q = h;
	int sum = 0;
	while(q)
	{
		if(q->timestamp <= (time - window))
		{
			break;
		}
		int toAdd = q->number;
		if(q->next && q->next->timestamp <= (time - window)) //�������Ͱ��ɾ������� 
		{
			toAdd /= 2;
		}
		
		/*
		if(deletedTime  <= (time - window)) //���Ͱɾ�����������Ҫά����ɾ����Ͱ��timestamp������ΪdeletedTime����ó�ʼ��deletedTimeΪһ���ϴ��ֵ����deletedTime = 9999999999999�� 
		{
			toAdd /= 2;
		}
		*/
		
		sum += toAdd;

		q = q->next;
	}
	return sum;
}
 
pbucket memory()
{
	int sign;       //���ڱ������������
	int time = 1;	//ע��ʱ�����1��ʼ����ͳ�ƴ��ڷ�ΧΪ(time - window, time] 
	count[0] = 0;
 
	FILE *fp;
 
	pbucket p, h = NULL;
 
	fp = fopen("01stream.txt","r");
 
	while((feof(fp) == 0))    
	{
		fscanf(fp,"%d",&sign);
 
		if(sign == 1)    //������Ϊ1������
		{
			count[time] = count[time - 1] + 1;
			p = (pbucket)malloc(sizeof(bucket));   //�����������һ���ڵ�
			p->timestamp = time;
			p->number = 1;
			if(h)
			{
				p->next = h;    
			}
			if(!h)
			{
				p->next = NULL;
			}
			h = p;
			judge(h,1);
		}
		else
		{
			count[time] = count[time - 1];
		}
 
		if(time % printFreq == 0)
		{
			int prediction = DGIM(h, time, window);
			printf("Timestamp = %d\n", time);
			printf("\testimate: %d\n", prediction);
			printf("\ttruth: %d\n", count[time] - count[time - window]);
			printf("\n");
		}
		
		time++;    //ʱ������
	}
 
	return h;
}
 
 
int judge(pbucket h,int n)
{
	pbucket p,q,r;
	int i = 0;
	p = q = h;
 
//	r = p->next;
	while(p)
	{
		if(q)
		{
			if(q->number == n)
			{
				i++;
				if(i == 3)    //��������Ͱ�������һ��ʱ�����кϲ�
				{
					r->number = n * 2;    //Ͱ�������*2
					r->next = q->next;    //ɾ���ڵ�
					free(q);    //�ͷſռ�
					n *= 2;
					p = p->next;
					judge(p,n);
					break;
				}
				else
				{
					r = q;
					q = q->next;
				}
			}
			else
				break;
		}
		else
			break;
	}
	return 0;
}
 
void destory(pbucket *h)    //��������
{
	pbucket p,q;
	p=*h;
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	*h=NULL;
}
 
int main()
{
	pbucket h,q;
	h = memory();
	destory(&h);
 
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
 
typedef struct bucket
{
	int number;    //����1�ĸ���
	int timestamp;    //����ʱ���
	struct bucket *next;
}bucket,*pbucket;
 
int windows;    //���ڴ�С
int buckets;    //Ͱ����
int time;       //����ʱ��
int numbers;    //������
int count;      //��ȷ����
 
int judge(pbucket h,int n);
 
pbucket memory()
{
	int sign;    //���ڱ������������
	int i = 1;
 
	FILE *fp;
 
	pbucket p,q;
	pbucket h = NULL;
 
//	windows = 1000;
	count = 0;
	numbers = 0;
 
	printf("�����봰�ڵĴ�С\n");
	scanf("%d",&windows);
	printf("������鿴��ʱ��\n");
	scanf("%d",&time);
 
	fp = fopen("E:\\������\\ʵ��1\\01stream.txt","r");
 
	while((feof(fp) == 0) && (numbers < time))    //��ȡ�鿴ʱ��֮ǰ��������
	{
		fscanf(fp,"%d",&sign);
//	    printf("sign = %d\n",sign);
 
		if(sign == 1)    //������Ϊ1������
		{
			if(numbers > (time - windows))    //���ھ�ȷͳ��
			{
				count++;
			}
 
			p = (pbucket)malloc(sizeof(bucket));    //�����������һ���ڵ�
			p->timestamp = i;
			p->number = 1;
			q = p;
			if(h)
			{
				q->next = h;    //��һ��ֱ�Ӳ���h���棬����ʹ��ͷ�巨
			}
			if(!h)
			{
				p->next = NULL;
			}
			h = q;
			judge(h,1);
		}
 
		i++;    //���ڼ�¼ʱ���
		numbers++;
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
	int sum = 0;
 
	pbucket h,q;
	h = memory();
	q = h;
 
	buckets = 0;
 
	while(q)
	{
		if(q->timestamp > (time - windows))
		{
			if(q->next->timestamp <= (time - windows))
			{
				q->number /= 2;
			}
			sum += q->number;
			if(q->next->timestamp < (time - windows))
			{
				q->number *= 2;
			}
			printf("q->timestamp = %d\n",q->timestamp);
			printf("bucket = %d\n",q->number);
		    buckets++;
		}
		q = q->next;
	}
 
	printf("sum = %d\n",sum);
	printf("buckets = %d\n",buckets);
	printf("windows = %d\n",windows);
	printf("count = %d\n",count);
 
	destory(&h);
 
	return 0;
}

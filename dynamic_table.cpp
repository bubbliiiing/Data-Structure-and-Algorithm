#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MaxSize 10
typedef int Ele;

typedef struct
{
	Ele *data;
	int length;
	int listSize;
}sqList;


void init(sqList *L)	//初始化一个顺序表，length代表当前顺序表长度，listSize表示最大长度
{
	L->data = (Ele *)malloc(MaxSize * sizeof(Ele));

	if (!L->data){
		printf("内存分配失败\n");
		exit(0);
	}
	L->length = 0;
	L->listSize = MaxSize;
}

void Insertdata(sqList *L, int i, Ele x) //向顺序表中插入元素，i代表插入元素的位置，x代表待插入的元素值。
{
	Ele *base;

	int p, insertPtr;

	if (i<1 || i>L->length + 1)
	{
		printf("插入位置错误\n");
		exit(0);
	}

	if (L->length >= L->listSize)	//顺序表长度不足，调用realloc()函数重新分配空间
	{
		base = (Ele *)realloc(L->data, (L->listSize + MaxSize)*sizeof(Ele));
		L->data = base;
		L->listSize = L->listSize + MaxSize;
	}

	insertPtr = i - 1;						//找到指定索引

	for (p = L->length - 1; p >= i - 1; p--)	//位置i后所有数据向后移动一格
	{
		L->data[p] = L->data[p - 1];
	}
	L->data[insertPtr] = x;					//指定位置						
	L->length++;							//表长加1
}



void Deldata(sqList *L, int i)// 在顺序表中删除元素，i代表要删除的元素位置
{
	int delItem;

	if (i<1 || i>L->length)
		exit(0);

	for (delItem = i - 1; delItem < L->length-1; ++delItem)	// 每个数据向前移一格
	{
		L->data[delItem] = L->data[delItem+1];
	}

	L->length--;
}

int main()
{
	sqList l;
	int i,num;
	Ele e;

	init(&l);
	printf("当前表的数据个数是：%d,最大容量是：%d\n", l.length, l.listSize);
	printf("向顺序表插入11个元素\n");
	for (i = 0; i < 11; i++)
	{
		scanf("%d", &e);
		Insertdata(&l, i + 1, e);
	}
	printf("\n\n");
	printf("完成插入后，表中的内容是：");
	for (i = 0; i < l.length; i++)
	{
		printf("%d ", l.data[i]);
	}
	printf("\n\n");
	printf("请指定要删除的元素的位置\n");
	scanf("%d", &num);
	Deldata(&l, num);

	printf("完成删除后，表中的内容是：");
	for (i = 0; i < l.length; i++)
	{
		printf("%d ", l.data[i]);
	}
	printf("\n\n");
	printf("当前表的数据个数是：%d,最大容量是：%d\n", l.length, l.listSize);

	return 0;
}

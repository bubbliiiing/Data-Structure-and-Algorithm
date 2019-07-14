#include <stdio.h>
#include <stdlib.h>

struct Node{ //定义结构体
	int data;
	struct Node* Next;
};

typedef struct Node* Linked_List;	//将结构体指针定义成另外的名称Linked_List
//如果使用一个*传入的是结构体的指针，其可以改变内部元素,data,Next

void getNode(Linked_List p){		//用于获得Node的data值，被addNode调用
	printf("请输入数字：");
	scanf("%d", &p->data);
}

void addNode(Linked_List* library, Linked_List* tail){
	Linked_List p;

	p = (Linked_List)malloc(sizeof(Linked_List));
	if (p == NULL)
	{
		printf("error");
		exit(1);
	}

	getNode(p);

	if (*library == NULL){	//如果头结点为空，将头结点指针的对应的地址改为p，因此要用到指针的指针。
		p->Next = NULL;
		*library = p;

		*tail = *library;	//此时尾节点等于头结点
		
	}
	else{
		p->Next = NULL;
		(*tail)->Next = p;
		*tail = p;			//尾节点更新
	}
	
}

void scanLibrary(Linked_List library){
	int i = 0;
	Linked_List p;

	p = (Linked_List)malloc(sizeof(Linked_List));
	p = library;

	while (p != NULL){
		printf("数字%d是%d\n", i, p->data);
		p = p->Next;
		i++;
	}
	free(p);
}

void release(Linked_List library){
	Linked_List temp = library->Next;
	while (library != NULL){
		free(temp);
		library = library->Next;
	}
	free(library);
}

void main()
{
	Linked_List head = NULL,tail = NULL;
	int num;
	printf("请问要输入几个数字：");
	scanf("%d", &num);
	for (int i = 0; i<num; i++){
		addNode(&head,&tail);
	}
	scanLibrary(head);
}
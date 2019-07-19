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

void addNode(Linked_List* library, Linked_List* tail){		//尾插法生成
	Linked_List p;

	p = (Linked_List)malloc(sizeof(struct Node));
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

void scanLibrary(Linked_List library){		//遍历整个链表
	int i = 0;
	Linked_List p;

	p = (Linked_List)malloc(sizeof(struct Node));
	p = library;

	while (p != NULL){
		printf("数字%d是%d\n", i, p->data);
		p = p->Next;
	}
}

void release(Linked_List library){
	Linked_List temp = library->Next;
	while (library != NULL){
		free(temp);
		library = library->Next;
	}
	free(library);
}

void getElem(Linked_List library, int num, int* e){
	int i = 0;
	while (i < num - 1){
		library = library->Next;
		if (library == NULL){
			printf("超出链表索引范围。\n");
			exit(1);
		}
		i++;
	}
	*e = library->data;
}

void addElem(Linked_List* library, int num, int* e){ //在特定位置插入元素
	int i = 0;
	Linked_List p, s;
	p = (Linked_List)malloc(sizeof(struct Node));
	if (p == NULL)
	{
		printf("内存分配ERROR");
		exit(1);
	}
	p->data = *e;
	if (num == 1){					//如果在第一个节点插入
		p->Next = *library;
		*library = p;
	}
	else{
		s = *library;
		while (i < num - 2){		//找到特定位置
			s = s->Next;
			i++;
		}
		p->Next = s->Next;
		s->Next = p;
	}
}

void delElem(Linked_List* library, int num, int* e){	//删除特定位置节点
	int i = 0;
	Linked_List p, s;
	if (*library == NULL){
		printf("这是一个空表\n");
		exit(1);
	}
	if (num == 1){
		p = *library;
		*library = (*library)->Next;
		free(p);
	}
	else{
		s = *library;
		while (i < num - 2){
			s = s->Next;
			i++;

		}
		p = s->Next;
		*e = p->data;
		s->Next = p->Next;
	}
	free(p);
}

void main()
{
	Linked_List head = NULL, tail = NULL;
	int e, num;

	printf("请问你要输入几个数字：");
	scanf("%d", &num);
	for (int i = 0; i<num; i++){
		addNode(&head, &tail);
	}

	printf("请输入你需要取得第几个数：");
	scanf("%d", &num);
	getElem(head, num, &e);
	printf("你取得的数是%d\n", e);

	printf("请输入你需要加入的数：");
	scanf("%d", &e);

	printf("请输入你需要加入的位置：");
	scanf("%d", &num);
	addElem(&head, num, &e);
	scanLibrary(head);

	printf("请输入你需要删除的位置：");
	scanf("%d", &num);
	delElem(&head, num, &e);
	printf("你删除的数是%d\n", e);
	scanLibrary(head);
}
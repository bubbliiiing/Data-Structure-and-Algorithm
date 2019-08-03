#include <stdio.h>
#include <stdlib.h>

typedef int Ele;

struct Node{
	Ele data;
	struct Node* Next;		//data用于存储信息，Next用于存储下一个队列下一个元素的地址。
};

typedef struct Node* LinkedList;

struct Queue{
	LinkedList head;
	LinkedList tail;		//head为队头，tail为队尾。
};

typedef struct Queue QueueList;

void init(QueueList* q){
	q->head = q->tail = (LinkedList)malloc(sizeof(struct Node));
	if (q->head == NULL){
		printf("内存空间分配失败");
		exit(1);
	}
	q->head->Next = NULL;
}

void push(QueueList* q,Ele e){
	LinkedList p;
	p = (LinkedList)malloc(sizeof(struct Node));
	if (p == NULL){
		printf("内存空间分配失败");
		exit(1);
	}
	p->Next = NULL;
	p->data = e;

	q->tail->Next = p;	//将元素压入队列、将队尾指针指向新节点
	q->tail = p;
}

void pop(QueueList* q, Ele* e){
	LinkedList p;
	if (q->head == q->tail){
		printf("队列已空");
		exit(1);
	}
	p = q->head->Next;
	q->head->Next = p->Next;	//利用p取出队头
	*e = p->data;				//信息存入元素e
	if (q->tail == p){
		q->tail = q->head;		//判断是否取出所有元素，如果取出所有元素，队头指向队尾
	}
	free(p);					//释放中间节点
}

void release(QueueList* q){
	LinkedList p;
	p = q->head;
	while (p){
		q->head = q->head->Next;
		free(p);
		
		p = q->head;
	}
}

int main(){
	QueueList q;
	int num,i;
	Ele e;
	init(&q);
	printf("请输入你要输入几个数字：");
	scanf("%d", &num);
	for (i = 0; i < num; i++){
		scanf("%d", &e);
		push(&q, e);
	}
	for (i = 0; i < num; i++){
		pop(&q, &e);
		printf("%d\n", e);
	}



	return 0;
}
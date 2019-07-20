#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node *Next;
};
typedef int c;
typedef struct Node* RoL;

RoL getRol(int n){
	RoL s, p;
	RoL tail;			//指向尾节点，用于添加元素
	int i = 1;
	p = (RoL)malloc(sizeof(struct Node));
	p->data = i;
	p->Next = p;
	tail = p;
	while (i < n){
		i++;
		s = (RoL)malloc(sizeof(struct Node));
		s->data = i;
		s->Next = tail->Next;
		tail->Next = s;			//重新指向尾节点
		tail = s;
	}
	return p;					//返回头指针
}

int main(void){
	RoL s, p;
	int i = 0;
	p = getRol(41);	//生成41位的循环链表，p指向表头
	while (p->Next != p){
		p = p->Next;	//第一轮：此时p指向第二个人；第二轮：此时p指向第五个人；
		printf("%d->", p->Next->data);

		if (15 == i){		//每15轮进行两次换行，结果更清晰。
			printf("\n\n");
			i = 0;
		}

		s = p->Next;	//第一轮：此时s指向第三个人；第二轮：此时s指向第六个人；
		p->Next = s->Next;	
		free(s);		//第一轮：第三个人自刎；第二轮：第六个人自刎；
		p = p->Next;	//第一轮：此时p指向第四个人；第二轮：此时s指向第七个人；
		i++;
	}
	printf("%d", p->data);
	return 0;

}

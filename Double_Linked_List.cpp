#include <stdio.h>
#include <stdlib.h>

struct Node{
	char c;
	struct Node* Next;
	struct Node* Before;
};

typedef struct Node* List;

//声明函数
List createList();
void ScanList(List list);
void mission(int num, List list);

int main(void){
	List ok;
	int num;
	ok = createList();
	printf("请输入一个数字：");
	scanf("%d", &num);
	mission(num, ok);
}

List createList(){
	List s, p;
	List Head;
	char c = 'A';
	
	int i;
	Head= (List)malloc(sizeof(struct Node));
	s = Head;				//头结点节点初始化
	s->c = c;
	s->Next = s;		
	s->Before = s;
	for (i = 1; i < 26; i++){	
		c = c + 1;
		p = (List)malloc(sizeof(struct Node));
		s->Next = p;		//此处一共具有三个List节点，head始终指向头部
		p->Before = s;		//p节点是临时节点，用作每一次插入新节点。
		Head->Before = p;	//s节点每次都进行s=s->Next更新，始终指向尾节点。
		p->Next = Head;
		s = s->Next;
		p->c = c;
	}
	return Head;
}

void ScanList(List list){
	List s = list;
	printf("%c ", s->c);	//从头到尾遍历链表
	s = s->Next;
	while (s != list){
		printf("%c ", s->c);
		s = s->Next;
	}
}

void mission(int num, List list){
	List s = list;
	if (num > 0)
	{
		for (int i = 0; i < num; i++){	//num代表输入的数字
			s = s->Next;
		}
	}
	else{
		for (int i = 0; i < -num; i++){	//num代表输入的数字
			s = s->Before;
		}
	}
	ScanList(s);
}
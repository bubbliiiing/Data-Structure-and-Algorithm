#include <stdio.h>
#include <stdlib.h>

typedef char Ele;

//Link代表0，表示此时指向左右孩子
//Thread代表1，表示此时指向前驱后继的指针
typedef enum {Link,Thread} PointerTag;

struct Node{
	Ele data;		//data用于存储信息
	struct Node* LeftChild;
	struct Node* RightChild;
	PointerTag ltag;
	PointerTag rtag;
};

typedef struct Node Node, *Tree;

Tree pre;

void init(Tree* t){	//当输入的字符为空格的时候，代表叶子结点
	//输入其它的字符代表当前结点的data值
	//输入顺序为当前结点、左结点、右结点。
	Ele c;
	scanf("%c", &c);
	if (' ' == c){
		*t = NULL;
	}
	else{
		*t = (Tree)malloc(sizeof(Node));
		if (*t == NULL){
			printf("内存分配失败");
			exit(1);
		}
		(*t)->data = c;
		(*t)->ltag = Link;
		(*t)->rtag = Link;
		init(&(*t)->LeftChild);		//生成左结点
		init(&(*t)->RightChild);	//生成右结点
	}
}

void Threading(Tree t){
	if (t != NULL){
		Threading(t->LeftChild);
		if (!t->LeftChild){			//如果没有左孩子，则将左孩子指向上一个访问的结点
			t->ltag = Thread;
			t->LeftChild = pre;
		}
		if (!pre->RightChild){			//如果没有左孩子，则将左孩子指向上一个访问的结点
			pre->rtag = Thread;
			pre->RightChild = t;
		}
		pre = t;

		Threading(t->RightChild);
	}
}

void InitThreading(Tree *p, Tree T){
	*p = (Tree)malloc(sizeof(Node));
	(*p)->ltag = Link;
	(*p)->rtag = Thread;		
	(*p)->RightChild = *p;		//p结点右子树指向自身
	if (!T){
		(*p)->LeftChild = *p;	//当树为空时，p结点的左右子树都指向自身
	}
	else{
		(*p)->LeftChild = T;	//p结点左子树指向根节点
		pre = *p;				//在最初情况下pre指向p
		Threading(T);
		pre->RightChild = *p;
		pre->rtag = Thread;		//使得中序遍历最后一个结点的右子树指向结点p
		(*p)->RightChild = pre;		//使得结点p的右子树指向中序遍历最后一个结点。

	}  
}
void visit(Ele e){
	printf("%c", e);
}

void scan(Tree p){
	Tree temp;
	temp = p->LeftChild;		//取得根节点
	while (temp != p){
		while (temp->ltag == Link){		//取得线索二叉树遍历的第一个结点
			temp = temp->LeftChild;
		}
		visit(temp->data);
		while (temp->rtag == Thread && temp->RightChild != p){
			temp = temp->RightChild;

			visit(temp->data);
		}
		temp = temp->RightChild;
	}
}
int main(){
	Tree p,BiTree = NULL;
	init(&BiTree);
	InitThreading(&p,BiTree);
	printf("中序遍历的结果为：");
	scan(p);
	printf("\n");
	return 0;
}



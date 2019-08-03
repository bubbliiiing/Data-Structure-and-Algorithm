#include <stdio.h>
#include <stdlib.h>

typedef char Ele;

struct Node{
	Ele data;		//data用于存储信息
	struct Node* LeftChild;
	struct Node* RightChild;
};

typedef struct Node Node, *Tree;

void init(Tree* t){	//当输入的字符为空格的时候，代表叶子结点
					//输入其它的字符代表当前结点的data值
					//输入顺序为当前结点、左结点、右结点。
	Ele c;
	scanf("%c", &c);
	if (' '== c){
		*t = NULL;
	}
	else{
		*t = (Tree)malloc(sizeof(Node));
		if (*t == NULL){
			printf("内存分配失败");
			exit(1);
		}
		(*t)->data = c;
		init(&(*t)->LeftChild);		//生成左结点
		init(&(*t)->RightChild);	//生成右结点
	}
}


void visit(Tree t, int level){
	printf("%c位于第%d层\n", t->data, level);
}

void scan(Tree t,int level){
	if (t != NULL){
		scan(t->LeftChild, level + 1);
		scan(t->RightChild, level + 1);
		visit(t, level);
	}
}

int main(){
	Tree BiTree = NULL;
	init(&BiTree);
	scan(BiTree,1);
	return 0;
}



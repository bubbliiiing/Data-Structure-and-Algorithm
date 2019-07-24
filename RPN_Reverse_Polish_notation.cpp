#include <stdio.h>
#include <stdlib.h>
#define Maxsize 10
typedef double Ele;

struct stack
{
	Ele* top;
	Ele* bottom;
	int stacksize;
};

typedef struct stack* Stack;

void init(Stack s){
	Ele *p;
	p = (Ele*)malloc(Maxsize * sizeof(Ele));
	if (p == NULL){
		printf("error");
		exit(1);
	}
	s->top = s->bottom = p;
	s->stacksize = Maxsize;
}

void PUSH(Stack s, Ele data){
	int length;
	length = s->top - s->bottom;
	if (length >= s->stacksize){
		s->bottom = (Ele*)realloc(s->bottom,(s->stacksize + Maxsize) * sizeof(Ele));
		if (s->bottom == NULL){
			printf("内存分配失败\n");
			exit(1);
		}
	}
	*(s->top) = data;
	s->top++;
}
Ele POP(Stack s){
	Ele num;
	if (s->top == s->bottom){
		printf("栈内没有元素了！\n");
		exit(1);
	}
	s->top--;
	num = *(s->top);
	return num;
}

int main(){
	struct stack s;			//定义栈
	char c = 0,str[10];		//c用于从键盘获取字符，str用于存储每一轮输入的数字，之后会转化成double类型
	Ele a1, a2, num;		//a1，a2用于栈的运算
	int i = 0;				//temp量


	init(&s);				//初始化栈
	printf("请输入一个算式：");		

	scanf("%c", &c);		//输入一个字符
	while (c != '#')
	{
		while ((c <= '9' && c >= '1') || c == '.'){	//该部分用于获取一个double类型的数字
			str[i++] = c;
			str[i] = '\0';
			if (i >= 10){
				printf("输入数据过大");
				exit(1);
			}
			scanf("%c", &c);
			if (!(c <= '9' && c >= '1') && !(c == '.')){
				a1 = atof(str);						//该函数用于将字符串转化位double
				PUSH(&s, a1);
				i = 0;
				break;
			}
		}
		switch (c)								//判断是否属于加减乘除
		{
		case '+': 
			a1 = POP(&s);
			a2 = POP(&s); 
			PUSH(&s, a2 + a1);
			break;
		case '-': 
			a1 = POP(&s);
			a2 = POP(&s); 
			PUSH(&s, a2 - a1);
			break;
		case '*': 
			a1 = POP(&s);
			a2 = POP(&s); 
			PUSH(&s, a2 * a1);
			break;
		case '/': 
			a1 = POP(&s);
			a2 = POP(&s); 
			PUSH(&s, a2 / a1);
			break;
		case ' ':
			break;
		case '#':
			break;
		default:
			printf("输入符号错误！\n");
			break;
		}
		scanf("%c", &c);
	}
	num = POP(&s);
	printf("%.3f\n", num);

	return 0;
}
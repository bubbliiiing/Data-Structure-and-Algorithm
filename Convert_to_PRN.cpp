#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Initsize 30
#define Newsize 30

typedef char Ele;

struct Stack{
	Ele* Top;
	Ele* Base;
	int Stacksize;
};
typedef struct Stack* stk;


void init(stk);				//函数声明
void push(stk p, Ele e);	
Ele pop(stk p);

void init(stk p){			//初始化函数
	p->Base = (Ele*)malloc(Initsize*sizeof(Ele));
	if (p->Base == NULL){
		printf("内存分配失败。");
		exit(1);
	}
	p->Top = p->Base;
	p->Stacksize = Initsize;
}

void push(stk p, Ele e){	//入栈
	int len;
	len	= p->Top - p->Base;
	if ( len >= p->Stacksize)
	{	//动态分配空间
		p->Base = (Ele*)realloc(p->Base, (p->Stacksize + Newsize)*sizeof(Ele));
		if (p->Base == NULL){
			printf("内存分配失败。");
			exit(1);
		}
		p->Stacksize = p->Stacksize + Newsize;
		p->Top = p->Base + len;
	}
	*(p->Top) = e;
	p->Top++;
}

Ele pop(stk p){		//出栈
	Ele e;
	if (p->Top == p->Base){
		printf("已经到达底端");
		exit(0);
	}
	(p->Top)--;
	e = *(p->Top);
	return e;
}

int main(){
	struct Stack p;		//定义栈
	Ele c,e[3]="0 ";		//c用于接收键盘字符
	//定义e[]是因为使用strcat函数要求两个输入量都是字符串，需要以\0结尾，不可以直接加入一个字符
	Ele str[10],all[200]="";	//str用于保存输入小鼠，all用于存储得到的输出后缀表达式。
	int i = 0;					//temp量

	init(&p);					//初始化

	printf("请输入一个算式：");
	scanf("%c", &c);
	while (c != '#')
	{
		while ((c <= '9' && c >= '0') || c == '.'){		//输入一个小数
			str[i++] = c;
			if (i >= 10){
				printf("输入数据过大");
				exit(1);
			}
			scanf("%c", &c);
			if (!(c <= '9' && c >= '0') && c != '.'){
				str[i++] = ' ';
				str[i] = '\0';
				strcat(all, str);
				i = 0;
				break;
			}
		}
		if (c == '#')
			break;
		switch (c)								//操作符判断
		{
		case '(':
		case '*':
		case '/':
			//如果遇到操作符'('、'*'、'/'，由于其优先级较高，直接进行入栈。
			push(&p, c);
			break;
		case '+':
		case '-':
			//如果是+号或者-号，如果之前曾经将'('压入栈，则取出其与'('之间的所有操作符，不取出'('；
			//如果之前未将'('压入栈，则取出所有操作符，因为在栈中的所有操作符的优先级都比最后一个'+'、'-'高。
			while (p.Base != p.Top){		
				e[0] = pop(&p);
				if (e[0] == '*' || e[0] == '/' || e[0] == '+' || e[0] == '-'){
					strcat(all, e);
				}
				else{
					push(&p, e[0]);
					break;
				}
			}
			push(&p, c);
			break;
		case')':
			//如果遇到操作符')'，则取出其与'('之间的所有操作符，同时取出'('。
			while ((e[0] = pop(&p)) != '('){
				strcat(all, e);
			}
		default:
			break;
		}
		scanf("%c", &c);
	}
	//如果输入到达末尾，弹出所有操作符。
	while (p.Base != p.Top){
		e[0] = pop(&p);
		strcat(all, e);
	}
	printf("%s", all);
	return 0;
}
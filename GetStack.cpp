#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define maxsize 100 //最大size为100
typedef char EleType; //这个地方要用typedef，不可以用define
struct stack{		//stacksize是整型。
	int stacksize;  //指的是这个栈的最大size
	EleType* top;	//top指的指针是最后一位数据的后一个
	EleType* base;  //base指的指针是最低位的指针。
};

void init(struct stack* STA){
	STA->base = (EleType *)malloc(maxsize * sizeof(EleType));	//为base申请内存空间。
	if (!STA->base){											//如果没有申请上，则推出
		exit(1);
	}
	STA->stacksize = maxsize;	//更改stacksize的大小；
	STA->top = STA->base;		//初始化的时候顶端指向尾端
}

void insert(struct stack* STA, EleType e){	//插入数据
	int len;
	EleType* m;
	len = STA->top - STA->base;				//计算总体长度
	if (len >= STA->stacksize){ //如果

		m = (EleType *)realloc(STA->base, (STA->stacksize + maxsize)*sizeof(EleType));
		if (!m){
			exit(1);
		}
		STA->stacksize = STA->stacksize + maxsize;//更新stacksize的值
		STA->base = m; //更新base的值
		STA->top = m + len; //更新top的值
	}
	*(STA->top) = e; //STA->top的值更新，更新后top++
	(STA->top)++;
}

EleType pop(struct stack* STA){
	char c;
	if (STA->top == STA->base){
		exit(1);	//非法访问，异常退出
	}
	STA->top--;		//应当先将top--，再进行取值
	c = *(STA->top);	//top为指针
	return c;

}

int main(void){

	struct stack STA, STA_8; //这个地方不能直接定义指针，指针要要指向。
	EleType a;

	init(&STA); //使用地址
	init(&STA_8);

	printf("请输入一段字符串：");
	scanf("%c", &a); //不要使用字符串，效果不好。
	while (a != '#'){
		insert(&STA, a);
		scanf("%c", &a);
	}
	while (STA.top != STA.base){
		a = pop(&STA);
		printf("%c", a);
	}
	printf("\n");
	return 0;
}
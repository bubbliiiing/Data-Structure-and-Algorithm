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

char pop(struct stack* STA){
	char c;
	if (STA->top == STA->base){
		exit(1);	//非法访问，异常退出
	}
	STA->top--;		//应当先将top--，再进行取值
	c = *STA->top;	//top为指针
	return c;

}

void count(struct stack* STA, struct stack* STA_8){
	int len,signal=0;
	int num = 0;
	char c;
	len = STA->top - STA->base;

	for (int i = 0; i < len; i++){
		c = pop(STA);	//取出STA内的值
		if (c == '1')	//当c=='1'的时候计算num
		{
			num = num + (int)pow(2.0, i%3);
		}
		else if (c == '0'){	//当c=='0'的时候num不变
			num = num;
		}
		else				//弹出您输入的数据有误，退出
		{
			printf("您输入的数据有误\n");
			return;
		}
		signal++;
		if (signal == 3 || i == len-1){ //当信号量为3或者到达结尾的时候，记录当时的num值，压栈，初始化signal和num
			signal = 0;
			insert(STA_8, (char)(num + 48));
			num = 0;
		}
	}

}

void getanswer(struct stack* STA_8){
	char c;
	while (STA_8->top != STA_8->base){	//判断时候栈顶到栈底，到达的话则退出循环
		STA_8->top--;
		c = *STA_8->top;
		printf("%c", c);
	}
	printf("\n", c);
}


int main(void){

	struct stack STA,STA_8; //这个地方不能直接定义指针，指针要要指向。
	EleType a;
	
	init(&STA); //使用地址
	init(&STA_8);

	printf("请输入一段二进制数：");
	scanf("%c", &a); //不要使用字符串，效果不好。
	while (a != '#'){
		insert(&STA, a);
		scanf("%c", &a);
	}

	count(&STA,&STA_8);
	getanswer(&STA_8);
	return 0;
}

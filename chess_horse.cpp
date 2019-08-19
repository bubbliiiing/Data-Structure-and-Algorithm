#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define X 8
#define Y 8

int chess[X][Y];

//找到当马位于(x，y)位置的时候，下一个可走的位置
int nextxy(int *x, int *y, int count)
{
	switch (count){

	case 0:
		if (*x + 2 < X && *y - 1 >= 0 && !chess[*x + 2][*y - 1]){
			*x += 2;
			*y -= 1;
			return 1;
		}
		return 0;
		break;
	case 1:
		if (*x + 2 < X && *y + 1 < Y && !chess[*x + 2][*y + 1]){
			*x += 2;
			*y += 1;
			return 1;
		}
		return 0;
		break;
	case 2:
		if (*x + 1 < X && *y - 2 >= 0 && !chess[*x + 1][*y - 2]){
			*x += 1;
			*y -= 2;
			return 1;
		}
		return 0;
		break;
	case 3:
		if (*x + 1 < X && *y + 2 < Y && !chess[*x + 1][*y + 2]){
			*x += 1;
			*y += 2;
			return 1;
		}
		return 0;
		break;
	case 4:
		if (*x - 2 >= 0 && *y - 1 >= 0 && !chess[*x - 2][*y - 1]){
			*x -= 2;
			*y -= 1;
			return 1;
		}
		return 0;
		break;
	case 5:
		if (*x - 2 >= 0 && *y + 1 <Y && !chess[*x - 2][*y + 1]){
			*x -= 2;
			*y += 1;
			return 1;
		}
		return 0;
		break;
	case 6:
		if (*x - 1 >= 0 && *y - 2 >= 0 && !chess[*x - 1][*y - 2]){
			*x -= 1;
			*y -= 2;
			return 1;
		}
		return 0;
		break;
	case 7:
		if (*x - 1 >= 0 && *y + 2 < Y && !chess[*x - 1][*y + 2]){
			*x -= 1;
			*y += 2;
			return 1;
		}
		return 0;
		break;
	default :
		return 0;
		break;
	}
}

// 深度优先遍历
// (x,y)为位置坐标
// tag是一个标记变量，每走一步，tag+1
int travel(int x,int y,int tag){
	int x1 = x, y1 = y, flag = 0, count = 0;
	chess[x][y] = tag;

	if (tag == X*Y){ //当棋盘已经布满的时候
		// 打印棋盘
		for (int i = 0; i < X; i++){
			for (int j = 0; j < Y; j++){
				printf("%2d ", chess[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		return 1;
	}
	//尝试8个位置
	flag = nextxy(&x1, &y1, count);
	while (0 == flag&&count < 7){
		count++;
		flag = nextxy(&x1, &y1, count);
	}

	while (flag){
		if(travel(x1, y1, tag + 1)){
			return 1;
		}
		//返回上一个点，重试。
		x1 = x;
		y1 = y;
		count++;
		flag = nextxy(&x1, &y1, count);
		while (0 == flag && count < 7){
			count++;
			flag = nextxy(&x1, &y1, count);
		}
		//找到马的下一步可走坐标，则flag = 1，否则为0。
	}
	if (flag == 0){
		chess[x][y] = 0;
	}
	return 0;
}

void main(){
	clock_t start, finish;
	start = clock();
	for (int i = 0; i < X; i++){
		for (int j = 0; j < Y; j++){
			chess[i][j] = 0;
		}
	}
	if (!travel(2, 0, 1)){
		printf("该起始点无法遍历全局。");
	}
	for (int i = 0; i < X; i++){
		for (int j = 0; j < Y; j++){
			printf("%2d ", chess[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	finish = clock();
	printf("本次计算共用%f", double(finish-start)/CLOCKS_PER_SEC);

}
#include<stdio.h>

int count = 0;

int noDanger(int row, int col, int (*chess)[8]){
	int i,j,flag1 = 0,flag2 = 0,flag3 = 0,flag4 = 0,flag5=0;
	for (i = 0; i < 8; i++){			//判断该列是否有其它皇后
		if (chess[i][col] != 0){	
			flag1 = 1;
			break;
		}
	}
	for (i = row, j = col; i >= 0 && j >= 0; i--,j--){		//判断左上角是否有其它皇后
		if (chess[i][j] != 0){
			flag2 = 1;
			break;
		}
	}
	for (i = row, j = col; i < 8 && j < 8; i++, j++){		//判断右下角是否有其它皇后
		if (chess[i][j] != 0){
			flag3 = 1;
			break;
		}
	}
	for (i = row, j = col; i >= 0 && j < 8; i--, j++){		//判断左下角是否有其它皇后
		if (chess[i][j] != 0){
			flag4 = 1;
			break;
		}
	}	
	for (i = row, j = col; i < 8 && j >= 0; i++, j--){		//判断右上角是否有其它皇后
		if (chess[i][j] != 0){
			flag5 = 1;
			break;
		}
	}
	if (flag1 || flag2 || flag3 || flag4 || flag5){			//如果有其它皇后则不满足条件。return 0；
		return 0;
	}
	else{
		return 1;
	}
}

void EightQueen(int row,int chess[][8]){
	int chess2[8][8],i,j;
	for (i = 0; i < 8; i++){		//将所有chess赋予局部棋盘chess2，这样可以不改变原chess的值
		for (j = 0; j < 8; j++){
			chess2[i][j] = chess[i][j];
		}
	}
	if (8 == row){					//如果到达row = 8 则代表第八行的棋盘都已经放上皇后，则所有行都放上了皇后。打印棋盘出来
		printf("第%d种：\n", ++count);
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				
				printf("%d ", chess2[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else{
		for (j = 0; j < 8; j++){
			if (noDanger(row, j, chess2))	//判断是否有危险，没有危险则进行下一步
			{
				for (i = 0; i < 8; i++)		//清除当前行，上一次循环留下的影响，如j=0对j=1的影响。
					chess2[row][i] = 0;		
				chess2[row][j] = 1;				//该位置安全，放下一个皇后
				EightQueen(row + 1, chess2);	//查询下一行情况
			}
		}
	}

}

void main(){
	int chess[8][8], i, j;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			chess[i][j] = 0;				//赋予棋盘初值，全是0；
		}
	}
	EightQueen(0,chess);
}
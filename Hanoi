#include <stdio.h>
void hannuota(int,char,char,char);

void hannuota(int n,char A,char B,char C){
	if (n == 1){
		printf("%c --> %c\n", A, C);
	}
	else{
		hannuota(n - 1, A, C, B);
		printf("%c --> %c\n", A, C);
		hannuota(n - 1, B, A, C);
	}
}

int main(){
	int layer;
	printf("请输入汉诺塔的层数：");
	scanf("%d", &layer);
	hannuota(layer, 'A', 'B', 'C');
	return 0;
}

#include<stdio.h>
void quick_sort(int array[], int low, int high){
	int medium;
	int i = low , j = high;
	int temp;
	medium = array[(i + j) / 2];
	while (i <= j){	
		while (array[i] < medium){
			i++;
		}
		while (array[j] > medium){
			j--;
		}
		if (i <= j){
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (low < j){
		quick_sort(array, low, j);
	}
	if (high > i){
		quick_sort(array, i, high);
	}
}
int main()
{
	int array[] = { 78, 108, 111, 118, 101, 70, 105, 115, 104, 67, 46, 99, 111, 109 };
	int i, length;
	length = sizeof(array) / sizeof(array[0]);
	quick_sort(array,0,length - 1);
	for (i = 0; i < length; i++){
		printf("%d\n", array[i]);
	}
	return 0;
}
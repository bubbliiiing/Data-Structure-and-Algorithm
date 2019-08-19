#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"huffman.h"
#include"queue.h"

htTree *buildTree(char *inputString)
{
	int *probility = (int*)malloc(sizeof(int)* 256);	//申请256个空间用于存放每个ascii码的数量

	for (int i = 0; i < 256; i++){
		probility[i] = 0;
	}

	for (int j = 0; inputString[j] != '\0'; j++){
		probility[(unsigned char)inputString[j]]++;		//利用char和0~256的转换完成计数
	}

	pQueue * huffmanqueue;								//定义队列
	initpQueue(&huffmanqueue);							//初始化队列

	for (int k = 0; k < 256; k++){
		if (probility[k] != 0)							//遍历所有ascii码，如果某个ascii码的数量不为0
		{												//按照数量从小到大排列
			htNode* aux = (htNode*)malloc(sizeof(htNode));
			aux->left = NULL;							
			aux->right = NULL;
			aux->symbol = (char)k;						
			addpQueue(&huffmanqueue, aux, probility[k]);
		}
	}

	free(probility);									//在数据存入队列后，释放数组

	while (huffmanqueue->size!=1){
		int priority = huffmanqueue->first->priority;	//取出队列中前两个ascii码
		priority += huffmanqueue->first->Next->priority;

		htNode* left = getQueue(&huffmanqueue);
		htNode* right = getQueue(&huffmanqueue);

		htNode* newNode = (htNode*)malloc(sizeof(htNode));	//生成新结点，左右子树分别为前两个ascii码
		newNode->left = left;
		newNode->right = right;
		addpQueue(&huffmanqueue, newNode, priority);		//将新结点加入队列
	}
	htTree *tree = (htTree *)malloc(sizeof(htTree));		
	tree->root = getQueue(&huffmanqueue);					//根节点为队列仅剩的最后一个结点
	return tree;
}

void traverseTree(htNode* node, hlTable** table, int k, char code[256]){
	if (node->left == NULL&&node->right == NULL){		//当是根节点的时候
		code[k] = '\0';									//为末尾加上停止符号
		hlNode *aux = (hlNode*)malloc(sizeof(hlNode));	//申请Table结点的空间
		aux->core = (char *)malloc(sizeof(char)*(strlen(code) + 1));	//aux->core指的是某一个字母的编码结果
		strcpy(aux->core, code);										//将编码结果存入aux->core
		aux->symbol = node->symbol;										//将ascii码存入aux->symbol
		aux->next = NULL;
		if ((*table)->first == NULL){									//如果是Table的开头，则初始化
			(*table)->first = aux;
			(*table)->last = aux;
		}
		else{
			(*table)->last->next = aux;									//否则在末尾添加
			(*table)->last = aux;
		}
	}
	if (node->left != NULL){											//在左边则为编码添加上一个0
		code[k] = '0';
		traverseTree(node->left, table, k + 1, code);
	}		
	if (node->right != NULL){											//在右边则为编码添加上一个1
		code[k] = '1';
		traverseTree(node->right, table, k + 1, code);
	}

}

hlTable* buildTable(htTree *huffmanTree){
	hlTable* table = (hlTable*)malloc(sizeof(hlTable));		//申请hlTable的空间
	table->first = NULL;									//first和last都为空
	table->last = NULL;

	char code[256];											//初始化code
	int k = 0;												//初始化k为0
	traverseTree(huffmanTree->root, &table, k, code);		//生成哈夫曼编码
	return table;
}

void encode(hlTable* huffmanTable, char* stringToEncode){
	hlNode *traversal;

	printf("\n\nEncoding……\n\nInput string:\n%s\n\nDecoded string:\n", stringToEncode);
	for (int i = 0; stringToEncode[i] != '\0'; i++){
		traversal = huffmanTable->first;			//如果在Table中找到对应的ascii码，则打印编码结果。
		while (traversal->symbol != stringToEncode[i]){
			traversal = traversal->next;
		}
		printf("%s ", traversal->core);
	}
	printf("\n");
}

void decode(htTree* huffmanTree, char* stringToDecode){
	htNode *traversal = huffmanTree->root;
	printf("\n\nDecoding……\n\nInput string:\n%s\n\nDecoded string:\n",stringToDecode);
	for (int i = 0; stringToDecode[i] != '\0'; i++){
		if (traversal->left == NULL&&traversal->right == NULL){		//如果抵达叶子结点，则打印ascii码
			printf("%c", traversal->symbol);
			traversal = huffmanTree->root;
		}
		if (stringToDecode[i] == '0')		//如果编码内容为0，向左子树寻找
			traversal = traversal->left;
		if (stringToDecode[i] == '1')		//如果编码内容为1，向右子树寻找
			traversal = traversal->right;
		if (stringToDecode[i] != '0'&&stringToDecode[i] != '1'){
			return;
		}
	}
	if (traversal->left == NULL&&traversal->right == NULL){
		printf("%c", traversal->symbol);
		traversal = huffmanTree->root;
	}
	printf("\n");
	
}



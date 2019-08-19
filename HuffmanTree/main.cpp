#include<stdio.h>
#include<stdlib.h>
#include"huffman.h"

void visit(htNode* t, int level){
	if (t->left == NULL&&t->right == NULL)
		printf("%cÎ»ÓÚµÚ%d²ã\n", t->symbol, level);
}

void scan(htNode* t, int level){
	if (t != NULL){
		scan(t->left, level + 1);
		scan(t->right, level + 1);
		visit(t, level);
	}
}

int main(){
	htTree* tree = buildTree("abbcccddddeeeee");
	hlTable* Table = buildTable(tree);
	encode(Table, "abbcccddddeeeee");
	decode(tree, "0011111000111");
	scan(tree->root, 0);
	return 0;
}
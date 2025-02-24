#include "tree.h"
#include <stdio.h>

int cmp_int(void const * a, void const * b)
{
	if (*(int *)a > *(int *)b)
		return 1;
	if (*(int *)a < *(int *)b)
		return -1;
	else /*if ==*/
		return 0;
}

void printIntTree_(struct TreeNode * pNode)
{
	if (!pNode)
		return;

	if (pNode->l != NULL)
		printf("%d", *(int *)pNode->l->data);
	printf(" - %d - ", *(int *)pNode->data);
	if (pNode->r != NULL)
		printf("%d", *(int *)pNode->r->data);
	putc('\n', stdout);

	printf("l:\n");
	printIntTree_(pNode->l);
	printf("r:\n");
	printIntTree_(pNode->r);
}

void printIntTree(Tree * pTree)
{
	printIntTree_(pTree->root);
}

int main()
{
	int a[] = {1, 4, 7, 2, 3, -8, 0};
	/*Потеряны 2 и -8*/

	Tree * mt = TreeInit(sizeof(int), cmp_int);

	TreeInsertArray(mt, a, sizeof(a) / sizeof(*a));
	do {
		printIntTree(mt);
		int guess;
		fputs("Введите число: ", stdout);
		if (scanf("%d", &guess) < 1)
			break;
		// if(TreeBelongs(mt, &guess)){
		if (TreeRemove(mt, &guess)) {
			puts("Вы угадали!");
			if (mt->root == NULL)
				break;
			else
				continue;
		}
		puts("Попробуйте снова");

	} while (1);

	TreeFree(mt);
	return 0;
}

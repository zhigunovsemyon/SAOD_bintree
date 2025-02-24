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

int main()
{
	int a[] = {1, 4, 7, 2, 3, -8, 0};

	Tree * mt = TreeInit(sizeof(int), cmp_int);

	TreeInsertArray(mt, a, sizeof(a)/sizeof(*a));

	do {
		int guess;
		fputs("Введите число: ",stdout);
		if (scanf("%d", &guess) < 1)
			break;
		if(TreeBelongs(mt, &guess)){
			puts("Вы угадали!");
			break;
		}
		puts("Попробуйте снова");

	}while (1);

	TreeFree(mt);
	return 0;
}

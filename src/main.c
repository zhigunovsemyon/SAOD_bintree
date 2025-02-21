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

	for (size_t i = 0; i < (sizeof(a) / sizeof(*a)); ++i)
		TreeInsert(mt, a + i);

	TreeFree(mt);
	return 0;
}

#include "tree.h"
#include <malloc.h> /*malloc*/

static struct TreeNode **
TreeFind_(struct TreeNode ** tree, compar_fn compar, void const * key)
{
	if (*tree == NULL)
		return tree;

	/*Сохранение результата сравения*/
	int cmp_res = compar(key, *tree);

	if (cmp_res == 0)
		return tree;
	/*Если ключ меньше ячейки, поиск продолжается в левой части,
	 * если больше -- в правой*/
	return TreeFind_(cmp_res < 0 ? &((*tree)->l) : &((*tree)->r), compar,
			 key);
}

static void TreeFree_(struct TreeNode ** node)
{
	/*Если передана пустая ячейка*/
	if ((*node) == NULL)
		return;

	/*Если ячейка является листом (не имеет потомков)*/
	if ((*node)->l == NULL || (*node)->r == NULL) {
		free(*node);
		*node = NULL;
		return;
	}

	TreeFree_(&((*node)->l));
	TreeFree_(&((*node)->r));
}

/*Инициализация дерева. Принимает функцию распределения и размер данных*/
Tree * TreeInit(size_t esize, int (*compar)(void const *, void const *))
{
	if (esize == 0 || compar == NULL)
		return NULL;

	Tree * pTree = (Tree *)malloc(sizeof(Tree));
	if (!pTree)
		return NULL;

	pTree->esize = esize;
	pTree->compar = compar;
	pTree->root = NULL;

	return pTree;
}

/*Уничтожение дерева*/
void TreeFree(Tree * pTree)
{
	TreeFree_(&(pTree->root));
	free(pTree);
}

/*Вставка элемента данных*/
int TreeInsert(Tree * pTree, void * const src) {}

/*Удаление элемента с переданным ключом*/
int TreeRemove(Tree * pTree, void * const key) {}

/*Копирование элемента по ключу key из дерева в dest*/
int TreeCopy(Tree * pTree, void * const key, void * dest) {}

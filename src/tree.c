#include "tree.h"
#include <assert.h>
#include <malloc.h>  /*malloc(), free()*/
#include <stdbool.h> /*memcpy()*/
#include <string.h>  /*memcpy()*/

static inline bool NodeIsLeaf(struct TreeNode * node)
{
	return !(node->l && node->r);
}

/*
static struct TreeNode * TreeRightmostNode_(struct TreeNode * tree)
{
	while (tree->r != NULL)
		tree = tree->r;
	return tree;
}

static struct TreeNode * TreeLeftmostNode_(struct TreeNode * tree)
{
	while (tree->l != NULL)
		tree = tree->l;
	return tree;
}
*/

static void TreeFree_(struct TreeNode ** node)
{
	/*Если передана пустая ячейка*/
	if ((*node) == NULL)
		return;

	/*Если ячейка не является листом (не имеет потомков)*/
	if (!NodeIsLeaf(*node)) {
		TreeFree_(&((*node)->l));
		TreeFree_(&((*node)->r));
	}
	free(*node);
	*node = NULL;
	return;
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

static struct TreeNode *
NodeNew_(struct TreeNode * p, void * const src, size_t esize)
{
	struct TreeNode * pNode =
		(struct TreeNode *)malloc(sizeof(struct TreeNode) + esize);
	if (pNode == NULL)
		return pNode /*NULL*/;

	pNode->p = p;
	pNode->r = pNode->l = NULL;
	pNode->data = pNode + 1;

	memcpy(pNode->data, src, esize);
	return pNode;
}

static int TreeInsert_(struct TreeNode ** pNode,
		       struct TreeNode * pParentNode,
		       void * const src,
		       compar_fn compar,
		       size_t esize)
{
	if (*pNode == NULL) {
		*pNode = NodeNew_(pParentNode, src, esize);
		return (*pNode) ? 1 : 0; /*true при удачной записи, false при
					    ошибке malloc*/
	}
	/*Здесь и далее pNode не указывает на null-указатель*/
	assert(*pNode != NULL);

	int cmp_res = compar((*pNode)->data, src);

	/*Если под pNode находится элемент, равный источнику*/
	if (cmp_res == 0) {
		memcpy((*pNode)->data, src, esize); /*он перезаписывается*/
		return 1;
	}
	/*else*/
	return (cmp_res > 0)
		       ? TreeInsert_(&(*pNode)->l, *pNode, src, compar, esize)
		       : TreeInsert_(&(*pNode)->r, *pNode, src, compar, esize);
}

/*Вставка элемента данных*/
int TreeInsert(Tree * pTree, void * const src)
{
	return TreeInsert_(&pTree->root, NULL, src, pTree->compar,
			   pTree->esize);
}

/*Удаление элемента с переданным ключом*/
// int TreeRemove(Tree * pTree, void * const key) {}

/*Копирование элемента по ключу key из дерева в dest*/
// int TreeCopy(Tree * pTree, void * const key, void * dest) {}

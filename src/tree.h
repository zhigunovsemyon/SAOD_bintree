#include <cstddef> /*size_t*/

typedef struct {
	int (*compar)(void const *, void const *); /*Функция сортировки*/
	size_t esize;				   /*Размер данных в элементе*/
	struct TreeNode * root;			   /*Указатель на корень*/
} Tree;

struct TreeNode {
	struct TreeNode *l, *r, *p;
	void * data;
};

/*Инициализация дерева. Принимает функцию распределения и размер данных*/
Tree * TreeInit(size_t esize, int (*)(void const *, void const *));

/*Уничтожение дерева*/
void TreeFree(Tree *);

/*Вставка элемента данных*/
int TreeInsert(Tree *, void * const src);

/*Удаление элемента с переданным ключом*/
int TreeRemove(Tree *, void * const key);

/*Копирование элемента по ключу key из дерева в dest*/
int TreeCopy(Tree *, void * const key, void * dest);

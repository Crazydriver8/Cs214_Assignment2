#include <sorted-list.h>
#include <stdlib.h>

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
	SortedList* list = (SortedList*)calloc(1, sizeOf(SortedList));
	list->CompareFuncT = cf;
	list->DestructFuncT = df;
	return list;
}
void SLDestroy(SortedListPtr list) {
	while (list != NULL) {
		df(list->data);
		list = list->next;
	}
	free(list);
}
int SLInsert(SortedListPtr list, void *newObj){
	void* dat;
	while (list != NULL) {
		if (list->CompareFuncT(list->data, *newObj) == 0 || list->CompareFuncT(list->data, *newObj) > 0) {
			list
			return 1;
		}
		list = list->next;
	}
	return 0;
}
int SLRemove(SortedListPtr list, void *newObj){
	while (list != NULL) {
		if (list->data == *newObj) {
			free(list->data);
			return 1;
		}
		list = list->next;
	}
	return 0;
}
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIterator* iter = (SortedListIterator*)calloc(1, sizeOf(SortedListIterator);
	
	if (iter != NULL) {
		return iter;
	}
	return NULL;
}
void SLDestroyIterator(SortedListIteratorPtr iter) {
	free(iter);
}
void * SLGetItem(SortedListIteratorPtr iter) {
	if (iter->data != NULL) {
		return iter->data;
	} else {
		return 0;
	}
}
void * SLNextItem(SortedListIteratorPtr iter) {
	if (iter->next != NULL) {
		iter = iter->next;
		return iter->data;
	} else {
		return NULL;
	}
}

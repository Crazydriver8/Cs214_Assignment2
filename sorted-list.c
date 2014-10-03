#include "sorted-list.h"
#include <stdlib.h>

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
	SortedListPtr list = (SortedListPtr)calloc(1, sizeof(struct SortedList)); 
	list->head = NULL;
	list->CompareFuncT = cf; 
	list->DestructFuncT = df; 
	if (list != NULL) {
		return list; 
	}
	return NULL;
}
void SLDestroy(SortedListPtr list) {
	if (list->head == NULL) {
		free(list);
		return;
	}
	while (list->head != NULL) {
		ListNode *test = NULL; 
		test = list->head; 
		list->head = list->head->next; /*problem area*/
		list->DestructFuncT(test->data); 
		free(test);
	}
	free(list);
}
int SLInsert(SortedListPtr list, void *newObj){
	ListNode *temp = (ListNode*)calloc(1,sizeof(struct Node)); 
	temp->data = newObj;
	if (list->head == NULL) {
		list->head = temp;
		list->head->next = NULL;
		list->head->refC++;
		return 1;
	}
	ListNode* previous = list->head;
	if (previous != NULL && previous->next == NULL) {
		int a = list->CompareFuncT(previous->data, newObj);
		if (a < 0) {
			temp->next = list->head;
			list->head = temp;
			return 1;
		}
		if (a > 0 || a == 0) {
			list->head->next = temp;
			temp->refC++;
			temp->next = NULL;
			return 1;
		}
		return 0;
	}
	ListNode* current = previous->next;
	while (current != NULL) {
		int a = list->CompareFuncT(current->data, newObj);
		if (a < 0) {
			temp->next = current;
			previous->next = temp;
			temp->refC++;
			return 1;
		}
		if (a > 0 || a == 0) {
			if (current->next != NULL) {
				temp->next = current->next;
				current->next = temp;
			} 
			if (current->next == NULL) {
				current->next = temp;
				temp->next = NULL;
			}
			temp->refC++;
			return 1;
		}
		temp->next = current->next;
		return 0;
	}
	return 0;
}
int SLRemove(SortedListPtr list, void *newObj){
	ListNode* previous = list->head;
	ListNode* current = list->head->next;
	ListNode* temp = NULL;
	while (current != NULL) {
		if (list->CompareFuncT(current->data, newObj) == 0) {
			temp = current;
			current = current->next;
			previous->next = current;
			if (temp->refC == 0) {
				free(temp);
			}
			return 1;
		}
		current = current->next;
	}
	return 0; 
}
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr iter = (SortedListIteratorPtr)calloc(1, sizeof(SortedListIteratorPtr));
	iter->head = list->head;
	if (list->head == NULL) {
		return NULL;
	}
	list->head->refC++; 
	if (iter != NULL) { 
		return iter; 
	}
	return NULL; 
}
void SLDestroyIterator(SortedListIteratorPtr iter) {
	if (iter->head == NULL || iter == NULL) {
		free(iter);
		return;
	}
	if (!iter->head->refC) {
		iter->head->refC--;
	} else {
		return;
	}
	if (iter->head->refC == 1) {
		free(iter->head);
		free(iter);
		return;
	}
	ListNode *current = iter->head;
	ListNode *previous = NULL;
	while (iter->head->next->refC == 0 || iter->head->next->refC < 0) {
		ListNode *delete = current;
		current = current->next;
		previous->next = current;
		free(delete);
	}
	free(iter->head); 
	free(iter); 
}
void * SLGetItem(SortedListIteratorPtr iter) {
	if (iter->head->data != NULL) { 
		return iter->head->data; 
	} else {
		return 0; 
	}
}
void * SLNextItem(SortedListIteratorPtr iter) {
	if (iter->head->next != NULL) { 
		iter->head->refC--;
		iter->head = iter->head->next; 
		iter->head->refC++;
		return iter->head->data; 
	} else {
		return NULL; 
	}
}

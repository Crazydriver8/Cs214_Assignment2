/*
 * sorted-list.c
 */

#include	<stdio.h>
#include	<string.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}


int main()
{
	double da = 3.94;
	double db = 4.80;
	double dc = 1.337;
	char* sa = "hello";
	char* sb = "world";
	char* sc = "leaders";
	int ia = 2;
	int ib = 6;
	int ic = 3;
	SortedListPtr test1 = SLCreate(compareDoubles, destroyBasicTypeNoAlloc);
	SLInsert(test1, (void*)&da);
	printf("%i is the list refC\n", test1->head->refC);
	SLInsert(test1, (void*)&db);
	SLInsert(test1, (void*)&dc);
	SortedListIteratorPtr tp1 = SLCreateIterator(test1);
	printf("%i is the iterator refC\n", tp1->head->refC);
	printf("%f is the data\n", *(double*)SLGetItem(tp1));
	printf("%f is the next data\n", *(double*)SLNextItem(tp1));
	printf("%f is the third data\n", *(double*)SLNextItem(tp1));
	SLRemove(test1, (void*)&da);
	SLRemove(test1, (void*)&db);
	SLRemove(test1, (void*)&dc);
	SLDestroy(test1);
	SLDestroyIterator(tp1);
	test1 = SLCreate(compareStrings, destroyBasicTypeNoAlloc);
	SLInsert(test1, (void*)sa);
	SLInsert(test1, (void*)sb);
	SLInsert(test1, (void*)sc);
	tp1 = SLCreateIterator(test1);
	printf("%s is the data\n", (char*)SLGetItem(tp1));
	printf("%s is the next data\n", (char*)SLNextItem(tp1));
	printf("%s is the third data\n", (char*)SLNextItem(tp1));
	SLDestroy(test1);
	SLDestroyIterator(tp1);
	test1 = SLCreate(compareStrings, destroyBasicTypeNoAlloc);
	SLInsert(test1, (void*)&ia);
	SLInsert(test1, (void*)&ib);
	SLInsert(test1, (void*)&ic);
	tp1 = SLCreateIterator(test1);
	printf("%i is the data\n", *(int*)SLGetItem(tp1));
	printf("%i is the next data\n", *(int*)SLNextItem(tp1));
	printf("%i is the third data\n", *(int*)SLNextItem(tp1));
	SLDestroy(test1);
	SLDestroyIterator(tp1);
	

	return 1;
}

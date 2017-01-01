#ifndef __fold_h_
#define __fold_h_

/**
- freeElement(void * a, void*e)
- a is irrelevant and should be passed NULL.
- a is returned unchanged
- free(e) is called, so we are assuming e is in the heap
*/
void * freeElement(void * a, void *e);

/****
- printIntegerList(void * a,void *e)
- e is assumed to point to an integer
- a holds the value of the index, assumes initial a = 0
- a is incremented when returned.  
*/
void * printIntegerList(void * a, void *e);

/****
- sumIntegerList(void * a,void *e)
- e is assumed to point to an integer
- a points to an integer that holds the accumulated sum
- a is returned after adding the value of *e to *a 
*/
void * sumIntegerList(void * a, void *e);

/***
- copyList(void *a, void*e)
- a is assumed to be a pointer to a list
- e is appended to the list in *a;
- a is returned after appending e;
*/
void * copyList(void *a, void * e);



#endif

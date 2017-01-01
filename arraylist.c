#include"arraylist.h"
#include"trackedmemory.h"
#include<stdio.h>

typedef struct _arraylist AL;
struct _arraylist{
  List li;
  void ** A;
  size_t max;
  size_t size;
  size_t start;
};

List * ALprepend(List*, void*);
List * ALappend(List*, void*);
List * ALremovefirst(List*, void**);
List * ALremovelast(List*, void**);
List * ALset(List*, size_t, void*);
List * ALget(List*, size_t, void**);
List * ALinsert(List*, size_t, void*);
List * ALremove(List*, size_t, void**);
size_t ALsize(List*);
List * ALsort(List*, int (*comp)(void*, void*));
void * ALfold(List*, void*, void* (*f)(void*,void*));
void ALdestroy(List*);

List * ArrayList(size_t max){
  AL * al = (AL*) MALLOC(sizeof(AL));
  al->li.prepend = ALprepend;
  al->li.append = ALappend;
  al->li.removefirst = ALremovefirst;
  al->li.removelast = ALremovelast;
  al->li.set = ALset;
  al->li.get = ALget;
  al->li.insert = ALinsert;
  al->li.remove = ALremove;
  al->li.size = ALsize;
  al->li.sort = ALsort;
  al->li.fold = ALfold;
  al->li.destroy = ALdestroy;
  al->max = max;
  al->A = (void **)CALLOC(sizeof(void*),al->max);
  al->size = 0;
  al->start = 0;
  return (List*)al;
}

size_t alindex(AL * al, size_t i){ return (al->start + i)% al->max;}

void resize(AL *al){
  if(al->size == al->max){
    size_t newmax = al->max *2;
    printf("resizing from %lu to %lu\n", al->max, newmax);
    void ** newA = (void **)CALLOC(sizeof(void*),newmax);
    int i;
    for(i = 0; i < al->size; i++)
      newA[i] = al->A[alindex(al,i)];
    FREE(al->A);
    al->A = newA;
    al->max = newmax;
    al->start = 0;
  }
}

List * ALprepend(List*l, void*e){
  AL * al = (AL *) l;
  resize(al);
  al->start = alindex(al, -1);
  al->A[al->start] = e;
  al->size++;
  return l;
}

List * ALappend(List*l, void*e){
  AL * al = (AL *) l;
  resize(al);
  al->A[alindex(al, al->size)] = e;
  al->size++;
  return l;
}

List * ALremovefirst(List*l, void**e){
  AL * al = (AL *) l;
  if(al->size == 0)
    *e = NULL;
  else {
    *e = al->A[al->start];
    al->start = alindex(al, 1);
    al->size--;
  }
  return l;
}

List * ALremovelast(List*l, void**e){
  AL * al = (AL *) l;
  if(al->size == 0)
    *e = NULL;
  else {
    *e = al->A[alindex(al, al->size-1)];
    al->size--;
  }
  return l;
}

List * ALset(List*l, size_t i, void*e){
  AL * al = (AL *) l;
  if(i >= al->size) return ALappend(l, e);
  al->A[alindex(al, i)] = e;
  return l;
}

List * ALget(List*l, size_t i, void**e){
  AL * al = (AL *) l;
  if(i >= al->size)
    *e = NULL;
  else 
    *e = al->A[alindex(al, i)];
  return l;
}

List * ALinsert(List*l, size_t i, void*e){
  AL * al = (AL *) l;
  resize(al);
  int j;
  for(j = al->size; j > i; j--)
     al->A[alindex(al, j)] = al->A[alindex(al, j-1)];
  al->A[alindex(al, i)] = e;
  al->size++;
  return l;
}

List * ALremove(List*l, size_t i, void**e){
  AL * al = (AL *) l;
  if(i >= al->size)
    *e = NULL;
  else {
    *e = al->A[alindex(al, i)];
    al->size--;
    int j;
    for(j = i; j < al->size; j++)
      al->A[alindex(al, j)] = al->A[alindex(al, j+1)];
  }
  return l;
}

size_t ALsize(List* l){
  AL * al = (AL *) l;
  return al->size;
}

List * ALsort(List*l, int (*comp)(void*, void*)){
  AL * al = (AL *) l;
  return l;
}

void * ALfold(List*l, void*a, void* (*f)(void*,void*)){
  AL * al = (AL *) l;
  int i;
  for(i = 0; i < al->size; i++){
    a  = f(a, al->A[alindex(al,i)]);
  }
  return a;
}

void ALdestroy(List*l){
  AL * al = (AL *) l;
  FREE(al->A);
  FREE(al);
}



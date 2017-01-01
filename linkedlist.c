#include "linkedlist.h"
#include "trackedmemory.h"
#include <stdio.h>


typedef struct _nodeStruct nodeType;
typedef struct _nodeStruct* node;

struct _nodeStruct{
	void* e;
	node next;
};

typedef struct _linkedList SLLType;
typedef struct _linkedList* SLL;

struct _linkedList{
	List li;
	node head;
	node tail;
	int size;
};


List * SLLprepend(List*, void*);
List * SLLappend(List*, void*);
List * SLLremovefirst(List*, void**);
List * SLLremovelast(List*, void**);
List * SLLset(List*, size_t, void*);
List * SLLget(List*, size_t, void**);
List * SLLinsert(List*, size_t, void*);
List * SLLremove(List*, size_t, void**);
size_t SLLsize(List*);
void * SLLfold(List*, void*, void* (*f)(void*,void*));
void SLLdestroy(List*);


List * LinkedList(){
	SLL L = (SLL)MALLOC(sizeof(SLLType));
	L -> head = NULL;
	L -> tail = NULL;
	L -> size = 0;
	L -> li.prepend = SLLprepend;
  L -> li.append = SLLappend;
  L -> li.removefirst = SLLremovefirst;
  L -> li.removelast = SLLremovelast;
  L -> li.set = SLLset;
  L -> li.get = SLLget;
  L -> li.insert = SLLinsert;
  L -> li.remove = SLLremove;
  L -> li.size = SLLsize;
  L -> li.fold = SLLfold;
  L -> li.destroy = SLLdestroy;
	return (List*)L;
}

node SLLgetNode(node n, size_t i){
	if(n == NULL) return NULL;
	if(i == 0) return n;
	return SLLgetNode(n -> next, i - 1);
}

node newNode(void* d){
	node n = (node)MALLOC(sizeof(node));
	n -> next = NULL;
	n -> e = d;
	return n;
}

List * SLLprepend(List* l, void* d){
	SLL ll = (SLL) l;
	//create a new node
	//point the head to that node
	//Make next go to null
	//size++
	//save previous next
	//if not empty, save next into a temp and point the head -> next -> next to it.
	node n = newNode(d);
	if(ll -> size > 0){
			node temp = ll -> head;
			ll -> head = n;
			n -> next = temp;
	}else{
		ll -> head = n;
		ll -> tail = n;
	}
	ll -> size++;
	return l;
}

List * SLLappend(List* l, void * d){
	SLL ll = (SLL) l;
	//if empty, just add to the List
	//otherwise
	//walk to the end of the List, and have that n -> next =
	node n = newNode(d);
	if(ll -> size != 0){
		ll -> tail -> next = n;
		ll -> tail = n;
	}else{
		ll -> head = n;
		ll -> tail = n;
	}
	 ll -> size++;
	return l;
}

void removeNode(node temp){
	FREE(temp -> e);
	FREE(temp);
	return;
}

/*
List * SLLremovefirst(List * l, void ** e){
	//save the position of the head, to free later
	//save the contents of the first node
	//have the head point to head -> next
	//free the old head
	//decrement size
	SLL ll = (SLL) l;
	if(ll -> size == 0){
		*e = NULL;
		return l;
	}
	node temp = ll -> head;
	*e = temp -> e;
	int d = (int)**e;
	printf("%d\n",d);
	ll -> head = ll -> head -> next;
	removeNode(temp);
	ll -> size--;
	return l;
}
*/
List * SLLremovefirst(List *l, void**e)
{
    SLL ll = (SLL) l;
    node current;
    if( ll -> size == 0 ){
        *e = NULL;
    }
    else{
        *e = ll->head->e;
        current = ll->head;
        ll->head = ll->head->next;
        FREE(current);
        ll->size--;
        if(ll->size == 0)
        {
            ll->tail = NULL;
						ll->head = NULL;
        }
    }
return l;
}

/*List * SLLremovelast(List* l, void** e){
	SLL ll = (SLL) l;

	if(ll -> size == 0){
		*e = NULL;
		return l;
	}
	if(ll -> size == 1){
		SLLremovefirst(l, e);
		return l;
	}
	*e = ll -> tail -> e;
	node temp = ll -> tail;
	ll -> tail = SLLgetNode(ll->head, ll -> size-1);
	removeNode(temp);
	return l;
}
*/
List * SLLremovelast(List *l, void**e)
 {
     SLL ll = (SLL) l;
     node current;
     if( ll -> size == 0 )
        {
            *e = NULL;
        }
     else
        {
            *e = ll->tail->e;
            if(ll->size == 1)
            {
                FREE(ll->head);
                ll->head = ll->tail = NULL;
            }
            else
            {
            current = SLLgetNode(ll->head, ll->size-2);
            current->next = NULL;
            FREE(ll->tail);
            ll->tail = current;
            }
        ll->size--;
        }

     return l;
 }

List* SLLinsert(List * l, size_t index, void * e){
	SLL ll = (SLL) l;
	if(index >= ll -> size) return SLLappend(l, e);
	if(index == 0) return SLLprepend(l, e);
	node prev = SLLgetNode(ll -> head, index - 1);
	node nxt = SLLgetNode(ll -> head, index);
	node temp = newNode(e);
	prev -> next = temp;
	temp -> next = nxt;
	ll -> size++;
	return l;
}

List* SLLremove(List* l, size_t index, void ** e){
	SLL ll = (SLL) l;
	if(index >= ll -> size) return l;
	if(index == ll -> size) return SLLremovelast(l, e);
	if(index == 0) return SLLremovefirst(l, e);
	node prior = SLLgetNode(ll -> head, index -1);
	node n = prior -> next;
	*e = n -> e;
	prior -> next = n -> next;
	FREE(n);
	ll->size--;
	return l;
}

size_t SLLsize(List* l){
	SLL ll = (SLL) l;
	return ll -> size;
}

List * SLLset(List* l, size_t index, void* e){
	SLL ll = (SLL) l;
	if(index >= ll -> size) SLLappend(l, e);
	node temp = SLLgetNode(ll -> head, index);
	temp  -> e = e;
	return l;
}

List * SLLget(List* l, size_t index, void** e){
	SLL ll = (SLL) l;
	if(index > ll -> size-1) *e = NULL;
	node temp = SLLgetNode(ll -> head, index);
	*e = temp -> e;
	return l;
}

void * SLLfold(List* l, void* a, void* (*f)(void*,void*)){
	SLL ll = (SLL) l;
	int i = 0;
	void* element;
	node n;

	for(i = 0; i < ll->size; i++){
		n = SLLgetNode(ll -> head, i);
		element = n -> e;
		a  = f(a,element);
        }
    return a;

}
void SLLdestroy(List* l){
	SLL ll = (SLL) l;
	node temp;
	while(ll -> head != NULL){
		temp = ll -> head -> next;
		FREE(ll -> head);
		ll -> head = temp;
	}
	FREE(ll);
}

#include"queuelistwrapper.h"
#include"trackedmemory.h"

struct _queueWrap{
  Queue q;
  List *li;
};

typedef struct _queueWrap QType;
typedef struct _queueWrap* Q; //named so because the queue.h contains the queue

Queue* QEnqueue(Queue *q, void *e){
  Q qlist = (Q) q;
  qlist -> li->append(qlist->li,e);
  return q;
}

Queue* QDequeue(Queue* q, void** e){
  Q qlist = (Q) q;
  qlist -> li->removefirst(qlist->li, e);
  return q;
}

Queue* QPeek(Queue* q, void ** e){
  Q qlist = (Q) q;
  qlist -> li -> get(qlist->li, 0, e);
  return q;
}

size_t QSize(Queue* q){
  Q qlist = (Q) q;

  return qlist->li->size(qlist->li);
}

void QDestroy(Queue * q){
  Q qlist = (Q) q;
  free(qlist);
}

Queue* QueueListWrapper(List *l){
  Q qlist = (Q) malloc(sizeof(QType));
  qlist -> li = l;
  qlist->q.enqueue = QEnqueue;
  qlist->q.dequeue = QDequeue;
  qlist->q.peek = QPeek;
  qlist->q.size = QSize;
  qlist->q.destroy = QDestroy;
  return (Queue *) qlist;
}

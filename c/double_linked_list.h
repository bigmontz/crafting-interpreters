#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct DoubleLinkedListItem
{
  struct DoubleLinkedListItem *next;
  struct DoubleLinkedListItem *previous;
  const char *value;
} DoubleLinkedListItem;

typedef struct DoubleLinkedList
{
  DoubleLinkedListItem *first;
  DoubleLinkedListItem *last;
} DoubleLinkedList;

typedef int (*Predicate)(const char *);
typedef int (*Consumer)(const char *);

DoubleLinkedList *newDoubleLinkedList();
void deleteDoubleLinkedList(DoubleLinkedList **theList);


void appendItemToTheList(DoubleLinkedList *theList, const char *value);
void forEach(DoubleLinkedList *theList, Consumer consumer);
DoubleLinkedListItem *findFirst(DoubleLinkedList *theList, Predicate predicate);
int filter(DoubleLinkedList *theList, Predicate predicate);
void deleteItemFromLinkedList(DoubleLinkedList *theList, DoubleLinkedListItem **theItem);

#endif

#include "double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

void deleteItemFromLinkedList(DoubleLinkedList *theList, DoubleLinkedListItem **theItem)
{
  if (theItem == NULL || *theItem == NULL)
  {
    return;
  }

  DoubleLinkedListItem *item = *theItem;

  if (theList != NULL)
  {
    if (item->next == NULL)
    { // is the last
      theList->last = item->previous;
    }
    else
    {
      item->next->previous = item->previous;
    }

    if (item->previous == NULL)
    { // is the first
      theList->first = item->next;
    }
    else
    {
      item->previous->next = item->next;
    }
  }

  free(item);
  *theItem = NULL;
}

DoubleLinkedList *newDoubleLinkedList()
{
  DoubleLinkedList *theList = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
  theList->first = NULL;
  theList->last = NULL;
  return theList;
}

void appendItemToTheList(DoubleLinkedList *theList, const char *value)
{
  DoubleLinkedListItem *item = (DoubleLinkedListItem *)malloc(sizeof(DoubleLinkedListItem));
  item->next = NULL;
  item->previous = NULL;
  item->value = value;
  if (theList->first == NULL)
  {
    theList->first = item;
  }
  if (theList->last != NULL)
  {
    theList->last->next = item;
    item->previous = theList->last;
  }
  theList->last = item;
}

DoubleLinkedListItem *findFirst(DoubleLinkedList *theList, Predicate predicate)
{
  DoubleLinkedListItem *candidate = theList->first;
  while (candidate != NULL)
  {
    if (predicate(candidate->value))
    {
      break;
    }
    candidate = candidate->next;
  }
  return candidate;
}

int filter(DoubleLinkedList *theList, Predicate predicate)
{
  int destroyed = 0;
  DoubleLinkedListItem *it = theList->first;
  while (it != NULL)
  {
    DoubleLinkedListItem *candidate = it;
    it = it->next;
    if (!predicate(candidate->value))
    {
      destroyed++;
      deleteItemFromLinkedList(theList, &candidate);
    }
  }
  return destroyed;
}

void forEach(DoubleLinkedList *theList, Consumer consumer)
{
  for (DoubleLinkedListItem *item = theList->first; item != NULL; item = item->next)
  {
    consumer(item->value);
  }
}

void deleteDoubleLinkedList(DoubleLinkedList **theList)
{
  if (*theList != NULL)
  {
    while ((*theList)->first != NULL)
    {
      deleteItemFromLinkedList(*theList, &((*theList)->first));
    }
    free(*theList);
    *theList = NULL;
  }
}

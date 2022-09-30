#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"

#define EQUALS_TO(name, str)               \
  int equalsTo##name(const char *otherStr) \
  {                                        \
    return equals(str, otherStr);          \
  }

#define NOT_EQUALS_TO(name, str)               \
  int notEqualsTo##name(const char *otherStr) \
  {                                        \
    return !equals(str, otherStr);          \
  }


int equals(const char *str, const char *otherStr)
{
  return strcmp(str, otherStr) == 0;
}

EQUALS_TO(Leticia, "Leticia")
NOT_EQUALS_TO(Leticia, "Leticia")

int main(void)
{
  printf("Hello World!\n");
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "Antonio");
  appendItemToTheList(list, "Leticia");
  appendItemToTheList(list, "Henrique");

  puts("Print all Items");
  forEach(list, puts);

  DoubleLinkedListItem *leticia = findFirst(list, equalsToLeticia);

  if (leticia != NULL)
  {
    printf("Found: ");
    puts(leticia->value);
    filter(list, notEqualsToLeticia);
  }
  else
  {
    puts("Leticia was not found!");
  }

  forEach(list, puts);

  deleteDoubleLinkedList(&list);
  return 0;
}

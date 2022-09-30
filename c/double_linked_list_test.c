#include "vendor/minunit.h"
#include "double_linked_list.h"
#include <stdlib.h>
#include <string.h>

static char *newDoubleLinkedList_should_create_empty_list()
{
  DoubleLinkedList *list = newDoubleLinkedList();

  mu_assert("newDoubleLinkedList -> created list should not be NULL", list != NULL);
  mu_assert("newDoubleLinkedList -> created list fist item should be NULL", list->first == NULL);
  mu_assert("newDoubleLinkedList -> created list last item should be NULL", list->last == NULL);
  return 0;
}

static char *deleteDoubleLinkedList_should_delete_empty_list()
{
  DoubleLinkedList *list = newDoubleLinkedList();

  deleteDoubleLinkedList(&list);

  mu_assert("deleteDoubleLinkedList -> deleted list pointer should be NULL", list == NULL);
  return 0;
}

static char *deleteDoubleLinkedList_should_list_with_one_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first value");

  deleteDoubleLinkedList(&list);

  mu_assert("deleteDoubleLinkedList -> deleted list pointer should be NULL", list == NULL);
  return 0;
}

static char *deleteDoubleLinkedList_should_list_with_two_items()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first value");
  appendItemToTheList(list, "last value");

  deleteDoubleLinkedList(&list);

  mu_assert("deleteDoubleLinkedList -> deleted list pointer should be NULL", list == NULL);
  return 0;
}

static char *deleteDoubleLinkedList_should_list_with_n_items()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  for (int i = 0; i < 100; i++)
  {
    appendItemToTheList(list, "n-sime item");
  }

  deleteDoubleLinkedList(&list);

  mu_assert("deleteDoubleLinkedList -> deleted list pointer should be NULL", list == NULL);
  return 0;
}

static char *appendItemToTheList_should_append_in_empty_list()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  const char *expectedValue = "expected item";

  appendItemToTheList(list, expectedValue);

  mu_assert("appendItemToTheList -> first item should not be null", list->first != NULL);
  mu_assert("appendItemToTheList -> last item should not be null", list->last != NULL);
  mu_assert("appendItemToTheList -> first item should be equals last", list->first == list->last);
  mu_assert("appendItemToTheList -> last item should have expected value", list->last->value == expectedValue);
  mu_assert("appendItemToTheList -> last item should have next equals NULL", list->last->next == NULL);
  mu_assert("appendItemToTheList -> last item should have previous equals NULL", list->last->previous == NULL);
  return 0;
}

static char *appendItemToTheList_should_append_in_a_list_with_one_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "previous");
  const DoubleLinkedListItem *expectedPreviousItem = list->last;
  const char *expectedValue = "expected item";

  appendItemToTheList(list, expectedValue);

  mu_assert("appendItemToTheList -> last item should not be null", list->last != NULL);
  mu_assert("appendItemToTheList -> last item should have expected value", list->last->value == expectedValue);
  mu_assert("appendItemToTheList -> last item should have next equals NULL", list->last->next == NULL);
  mu_assert("appendItemToTheList -> last item should have previous should be set", list->last->previous == expectedPreviousItem);
  return 0;
}

static char *appendItemToTheList_should_append_in_a_list_with_two_items()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "does not matter");
  appendItemToTheList(list, "previous");
  const DoubleLinkedListItem *expectedPreviousItem = list->last;
  const char *expectedValue = "expected item";

  appendItemToTheList(list, expectedValue);

  mu_assert("appendItemToTheList -> last item should not be null", list->last != NULL);
  mu_assert("appendItemToTheList -> last item should have expected value", list->last->value == expectedValue);
  mu_assert("appendItemToTheList -> last item should have next equals NULL", list->last->next == NULL);
  mu_assert("appendItemToTheList -> last item should have previous should be set", list->last->previous == expectedPreviousItem);
  return 0;
}

static char *appendItemToTheList_should_append_in_a_list_with_n_items()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  for (int i = 0; i < 100; i++)
  {
    appendItemToTheList(list, "n-sime item");
  }
  appendItemToTheList(list, "previous");
  const DoubleLinkedListItem *expectedPreviousItem = list->last;
  const char *expectedValue = "expected item";

  appendItemToTheList(list, expectedValue);

  mu_assert("appendItemToTheList -> last item should not be null", list->last != NULL);
  mu_assert("appendItemToTheList -> last item should have expected value", list->last->value == expectedValue);
  mu_assert("appendItemToTheList -> last item should have next equals NULL", list->last->next == NULL);
  mu_assert("appendItemToTheList -> last item should have previous should be set", list->last->previous == expectedPreviousItem);
  return 0;
}

static char *deleteItemFromLinkedList_should_not_fail_deleting_null_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  DoubleLinkedListItem *item = NULL;

  deleteItemFromLinkedList(list, &item);

  return 0;
}

static char *deleteItemFromLinkedList_should_not_fail_deleting_item_from_null_list()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "new item");
  DoubleLinkedListItem *item = list->first;

  deleteItemFromLinkedList(NULL, &item);

  mu_assert("deleteItemFromLinkedList -> item should be NULL", item == NULL);

  return 0;
}

static char *deleteItemFromLinkedList_should_be_able_to_delete_from_list_with_a_single_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "new item");
  DoubleLinkedListItem *item = list->first;

  deleteItemFromLinkedList(list, &item);

  mu_assert("deleteItemFromLinkedList -> item should be NULL", item == NULL);
  mu_assert("deleteItemFromLinkedList -> list first should be NULL", list->first == NULL);
  mu_assert("deleteItemFromLinkedList -> list last should be NULL", list->last == NULL);

  return 0;
}

static char *deleteItemFromLinkedList_should_be_able_to_delete_first_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  DoubleLinkedListItem *first = list->last;
  appendItemToTheList(list, "second");
  DoubleLinkedListItem *second = list->last;
  appendItemToTheList(list, "last");
  DoubleLinkedListItem *last = list->last;

  deleteItemFromLinkedList(list, &first);

  mu_assert("deleteItemFromLinkedList -> item should be NULL", first == NULL);
  mu_assert("deleteItemFromLinkedList -> list first should be the second", list->first == second);
  mu_assert("deleteItemFromLinkedList -> list last should be the last", list->last == last);
  mu_assert("deleteItemFromLinkedList -> second previous should be NULL", second->previous == NULL);

  return 0;
}

static char *deleteItemFromLinkedList_should_be_able_to_delete_second_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  DoubleLinkedListItem *first = list->last;
  appendItemToTheList(list, "second");
  DoubleLinkedListItem *second = list->last;
  appendItemToTheList(list, "last");
  DoubleLinkedListItem *last = list->last;

  deleteItemFromLinkedList(list, &second);

  mu_assert("deleteItemFromLinkedList -> item should be NULL", second == NULL);
  mu_assert("deleteItemFromLinkedList -> list first should be the fist", list->first == first);
  mu_assert("deleteItemFromLinkedList -> list last should be the last", list->last == last);
  mu_assert("deleteItemFromLinkedList -> first next should be the last", first->next == last);
  mu_assert("deleteItemFromLinkedList -> last previous should be the first", last->previous == first);

  return 0;
}

static char *deleteItemFromLinkedList_should_be_able_to_delete_last_item()
{
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  DoubleLinkedListItem *first = list->last;
  appendItemToTheList(list, "second");
  DoubleLinkedListItem *second = list->last;
  appendItemToTheList(list, "last");
  DoubleLinkedListItem *last = list->last;

  deleteItemFromLinkedList(list, &last);

  mu_assert("deleteItemFromLinkedList -> item should be NULL", last == NULL);
  mu_assert("deleteItemFromLinkedList -> list first should be the fist", list->first == first);
  mu_assert("deleteItemFromLinkedList -> list last should be the second", list->last == second);
  mu_assert("deleteItemFromLinkedList -> first next should be the second", first->next == second);
  mu_assert("deleteItemFromLinkedList -> second next should be NULL", second->next == NULL);

  return 0;
}

const char** capturedValues = NULL;
int capturedValuesIndex = 0;

int consumer(const char* value) {
  capturedValues[capturedValuesIndex++] = value;
  return 0;
}

static char * forEach_should_iterate_over_all_the_values () {
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  appendItemToTheList(list, "second");
  appendItemToTheList(list, "last");
  capturedValuesIndex = 0;
  capturedValues = (const char**) malloc(3 * sizeof(char*));

  forEach(list, consumer);

  mu_assert("forEach -> should correct first value", strcmp(capturedValues[0], "first") == 0);
  mu_assert("forEach -> should correct second value", strcmp(capturedValues[1], "second") == 0);
  mu_assert("forEach -> should correct last value", strcmp(capturedValues[2], "last") == 0);
  return 0;
}

int notEqualsToFirstOrLast (const char* value) {
  return strcmp(value, "first") != 0 && strcmp(value, "last") != 0;
}

int equalsToTarget (const char* value) {
  return strcmp(value, "target") == 0;
}

static char * filter_should_remove_items_which_doesnt_satisfies_the_predicate() {
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  appendItemToTheList(list, "second");
  DoubleLinkedListItem* second = list->last;
  appendItemToTheList(list, "third");
  DoubleLinkedListItem* third = list->last;
  appendItemToTheList(list, "last");

  int removed = filter(list, notEqualsToFirstOrLast);

  mu_assert("filter -> should remove 2 items", removed == 2);
  mu_assert("filter -> list first should be the second", list->first == second);
  mu_assert("filter -> list last should be the third", list->last == third);
  mu_assert("filter -> second next should be third", second->next == third);
  mu_assert("filter -> second previous should be NULL", second->previous == NULL);
  mu_assert("filter -> third next should be NULL", third->next == NULL);
  mu_assert("filter -> third previous should be second", third->previous == second);
  return 0;
}

static char* findFirst_should_return_null_if_value_is_not_found() {
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  appendItemToTheList(list, "second");
  appendItemToTheList(list, "third");
  appendItemToTheList(list, "last");

  DoubleLinkedListItem* found = findFirst(list, equalsToTarget);

  mu_assert("findFirst -> should return NULL", found == NULL);
  return 0;
}

static char* findFirst_should_return_the_first_item_found() {
  DoubleLinkedList *list = newDoubleLinkedList();
  appendItemToTheList(list, "first");
  appendItemToTheList(list, "target");
  DoubleLinkedListItem* firstTarget = list->last;
  appendItemToTheList(list, "second");
  appendItemToTheList(list, "third");
  appendItemToTheList(list, "target");
  DoubleLinkedListItem* secondTarget = list->last;
  appendItemToTheList(list, "last");

  DoubleLinkedListItem* found = findFirst(list, equalsToTarget);

  mu_assert("findFirst -> should return the first item found", found == firstTarget);
  return 0;
}

static char *run_all()
{
  mu_run_test(newDoubleLinkedList_should_create_empty_list);

  mu_run_test(deleteDoubleLinkedList_should_delete_empty_list);
  mu_run_test(deleteDoubleLinkedList_should_list_with_one_item);
  mu_run_test(deleteDoubleLinkedList_should_list_with_two_items);
  mu_run_test(deleteDoubleLinkedList_should_list_with_n_items);

  mu_run_test(appendItemToTheList_should_append_in_empty_list);
  mu_run_test(appendItemToTheList_should_append_in_a_list_with_one_item);
  mu_run_test(appendItemToTheList_should_append_in_a_list_with_two_items);

  mu_run_test(deleteItemFromLinkedList_should_not_fail_deleting_null_item);
  mu_run_test(deleteItemFromLinkedList_should_not_fail_deleting_item_from_null_list);
  mu_run_test(deleteItemFromLinkedList_should_be_able_to_delete_from_list_with_a_single_item);
  mu_run_test(deleteItemFromLinkedList_should_be_able_to_delete_first_item);
  mu_run_test(deleteItemFromLinkedList_should_be_able_to_delete_second_item);
  mu_run_test(deleteItemFromLinkedList_should_be_able_to_delete_last_item);

  mu_run_test(forEach_should_iterate_over_all_the_values);

  mu_run_test(filter_should_remove_items_which_doesnt_satisfies_the_predicate);

  mu_run_test(findFirst_should_return_null_if_value_is_not_found);

  return 0;
}

mu_test_suite("DoubleLinkedList", run_all);

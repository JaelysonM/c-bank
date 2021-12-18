#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

const size_t ARRAY_LIST_CHUNCK_SIZE = 128;
#define ARRAYLIST_INITIAL_CAPACITY 4

ArrayList *new_array_list()
{
  ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));
  arrayList->size = 0;
  arrayList->capacity = ARRAYLIST_INITIAL_CAPACITY;
  arrayList->data = calloc(sizeof(void *), ARRAYLIST_INITIAL_CAPACITY);
  return arrayList;
}

void realloc_array_list(ArrayList *arrayList, int size)
{
  if (size > arrayList->capacity)
  {
    unsigned int new_capacity = arrayList->capacity;
    while (new_capacity < size)
    {
      new_capacity *= 2;
    }
    arrayList->data = realloc(arrayList->data, sizeof(void *) * new_capacity);
    arrayList->capacity = new_capacity;
  }
}
void destroy_value_array_list(ArrayList *arrayList, int index)
{

  if (index > arrayList->size - 1)
  {
    free(arrayList->data[index]);
    arrayList->data = realloc(arrayList->data, sizeof(void *) * arrayList->capacity - 1);
  }
}
ArrayList *add_array_list(ArrayList *arrayList, void *value)
{
  realloc_array_list(arrayList, arrayList->size + 1);
  arrayList->data[arrayList->size++] = value;
  return arrayList;
}
int size_array_list(ArrayList *arrayList)
{
  return arrayList->size;
}
void **iterator_array_list(ArrayList *arrayList)
{
  return arrayList->data;
}
ArrayList *remove_array_list(ArrayList *arrayList, unsigned int index)
{
  destroy_value_array_list(arrayList, index);
  arrayList->size--;
  return arrayList;
}

int remove_value_array_list(ArrayList *arrayList, void *value)
{
  unsigned int searchIndex = -1;
  for (int x = 0; x < arrayList->size; x++)
  {
    void **k = arrayList->data[x];
    if (k == value)
    {
      remove_array_list(arrayList, x);
      searchIndex = x;
      break;
    }
  }
  return searchIndex >= 0 ? 1 : 0;
}
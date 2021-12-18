/* TAD: ArrayList */
/* Tipo exportado */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

typedef struct
{
  unsigned int size;
  unsigned int capacity;
  void **data;
} ArrayList;

ArrayList *new_array_list();

void realloc_array_list(ArrayList *arrayList, int size);

void destroy_value_array_list(ArrayList *arrayList, int index);
ArrayList *add_array_list(ArrayList *arrayList, void *value);

int size_array_list(ArrayList *arrayList);

void **iterator_array_list(ArrayList *arrayList);

ArrayList *remove_array_list(ArrayList *arrayList, unsigned int index);

int remove_value_array_list(ArrayList *arrayList, void *value);

#endif /* ARRALIST_H_ */
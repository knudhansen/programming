#include <stdlib.h>
#include <iostream>



template<typename T>
struct chained_list {
  T element;
  struct chained_list<T> *next;
  struct chained_list<T> *previous;
};

template<typename T>
void chained_list_init(struct chained_list<T> *list, T value) {
  list->element = value;
  list->next = NULL;
  list->previous = NULL;
}

template<typename T>
void chained_list_print(struct chained_list<T> *list) {
  while (list != NULL) {
    std::cout << list << "::" << list->element << "\n";
    list = list->next;
  }
}

template<typename T>
void chained_list_append(struct chained_list<T> **list, struct chained_list<T> *list_to_append) {
  struct chained_list<T> **temp = list;
  
  while (*temp != NULL) {
    temp = &((*temp)->next);
  }

  *temp = list_to_append;

}

template<typename T>
void chained_list_prepend(struct chained_list<T> **list, struct chained_list<T> *list_to_prepend) {
  chained_list_append(&list_to_prepend, *list);
  *list = list_to_prepend;
}

int main() {
  struct chained_list<int> element0;
  chained_list_init(&element0, 0);
  struct chained_list<int> element1;
  chained_list_init(&element1, 1);

  chained_list_print(&element0);
  chained_list_print(&element1);

  struct chained_list<int> *list_p;

  list_p = NULL;

  chained_list_prepend(&list_p, &element0);
  chained_list_print(list_p);
  chained_list_prepend(&list_p, &element1);
  chained_list_print(list_p);
  
}


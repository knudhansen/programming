#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

template <class T> class LinkedListElement;

template <class T>
class LinkedListElement {

 private:
  LinkedListElement<T> *previous;
  LinkedListElement<T> *next;
  T *value;

 public:
  LinkedListElement(T *value) {
    this->value = value;
    this->previous = NULL;
    this->next = NULL;
  }
  T *getValue(void) {
    return this->value;
  }
  LinkedListElement<T> *getNext(void) {
    return this->next;
  }
  int countAll(void) {
    if (this->next == NULL) {
      return 1;
    }
    return 1 + this->next->countAll();
  }
  void addLast(LinkedListElement<T> *lle) {
    if (this->next == NULL) {
      this->next = lle;
      this->next->previous = this;
    } else {
      this->next->addLast(lle);
    }
  }
  void print(void) {
    char *string = this->value->toString();
    printf("element: value=%s\n", string);
    free(string);
  }
  void printAll(void) {
    this->print();
    if (this->next != NULL) {
      this->next->printAll();
    }
  }
};

template <class T> class LinkedListIterator;

template <class T>
class LinkedList {
  friend class LinkedListIterator<T>;

 private:
  LinkedListElement<T> *firstElement;

 public:
  typedef LinkedListIterator<T> iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef T value_type;
  typedef T * pointer;
  typedef T & reference;

  LinkedList(void) {
    this->firstElement = NULL;
  }
  int getSize(void) {
    if (this->firstElement == NULL) {
      return 0;
    } else {
      return this->firstElement->countAll();
    }
  }
  void append(T *elementValue) {
    LinkedListElement<T> *lle = new LinkedListElement<T>(elementValue);
    if (this->firstElement == NULL) {
      this->firstElement = lle;
    } else {
      this->firstElement->addLast(lle);
    }
  }
  iterator begin(void) {
    return iterator(*this, 0);
  }
  iterator end(void) {
    return iterator(*this, getSize());
  }
  void print(void) {
    if (this->firstElement != NULL) {
      printf("printing linked list:\n");
      this->firstElement->printAll();
      printf("done printing linked list.\n");
    } else {
      printf("empty linked list\n");
    }
  }
};

template <class T>
class LinkedListIterator {
 private:
  LinkedList<T> &list;
  LinkedListElement<T> *currentElement;

 public:
  LinkedListIterator(LinkedList<T> &linkedList, int position)
    : list (linkedList) {
    currentElement = list.firstElement;
    while (position > 0 && currentElement != NULL) {
      currentElement = currentElement->getNext();
    }
  }
  T & operator *(void) {
    return *(currentElement->getValue());
  }
  bool operator==(const LinkedListIterator &b) {
    return (currentElement == b.currentElement);
  }
  bool operator!=(const LinkedListIterator &b) {
    return (currentElement != b.currentElement);
  }
  // prefix ++ opertor
  LinkedListIterator<T> operator++(void) {
    currentElement = currentElement->getNext();
    return *this;
  }
  // postfix ++ operator
  LinkedListIterator<T> operator++(int) {
    LinkedListIterator<T> clone( *this ); // the iterator returned must be before increment.
    currentElement = currentElement->getNext();
    return clone;
  }
};

#endif

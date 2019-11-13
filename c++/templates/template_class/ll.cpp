#include <stdio.h>

template <class eltType>
class LlElt {
private:
  LlElt *prev;
  LlElt *next;
  eltType elt;
public:
  LlElt(eltType elt);

  int getElementCountAfter(void);

  void addBefore(LlElt *llelt);
  void addAfter(LlElt *llelt);
  void show(void);
};

template <class eltType>
class ll {
private:
  LlElt<eltType> *first;
  LlElt<eltType> *last;
public:
  ll(void);
  int getElementCount(void);
  void addFront(eltType elt);
  void addBack(eltType elt);
  void show(void);
};

template <class eltType> LlElt<eltType>::LlElt(eltType elt) {
  this->prev = NULL;
  this->next = NULL;
  this->elt = elt;
}

template <class eltType> void LlElt<eltType>::addBefore(LlElt *llelt) {
  printf("adding %016lx before %016lx\n", (unsigned long)llelt, (unsigned long)this);

  llelt->next = this;
  llelt->prev = this->prev;
  if (this->prev != NULL) {
    this->prev->next = llelt;
  }
  this->prev = llelt;
}

template <class eltType> void LlElt<eltType>::addAfter(LlElt *llelt) {
  printf("adding %016lx after %016lx\n", (unsigned long)llelt, (unsigned long)this);

  llelt->next = this->next;
  llelt->prev = this;
  if (this->next != NULL) {
    this->next->prev = llelt;
  }
  this->next = llelt;
}

template <class eltType> int LlElt<eltType>::getElementCountAfter(void) {
  int returnValue;
  if (this->next == NULL) {
    returnValue = 0;
  } else {
    returnValue = this->next->getElementCountAfter() + 1;
  }
  return returnValue;
}

template <class eltType> void LlElt<eltType>::show(void) {
  printf("%016lx\n", (unsigned long)this);
  if (this->next != NULL) {
    this->next->show();
  }
}

template <class eltType> ll<eltType>::ll(void) {
  this->first = NULL;
  this->last = NULL;
}

template <class eltType> int ll<eltType>::getElementCount() {
  if (this->first ==  NULL) {
    return 0;
  } else {
    return this->first->getElementCountAfter() + 1;
  }
}

template <class eltType> void ll<eltType>::addFront(eltType elt) {
  // creating new list element
  LlElt<eltType> *llelt = new LlElt<eltType>(elt);
  // adding the list element at the front of the list
  if (this->first != NULL) {
    this->first->addBefore(llelt);
  } else {
    this->last = llelt;
  }
  this->first = llelt;
}

template <class eltType> void ll<eltType>::addBack(eltType elt) {
  // creating new list element
  LlElt<eltType> *llelt = new LlElt<eltType>(elt);
  // adding the list element at the front of the list
  if (this->last != NULL) {
    this->last->addAfter(llelt);
  } else {
    this->first = llelt;
  }
  this->last = llelt;
}

template <class eltType> void ll<eltType>::show(void) {
  if (this->first != NULL) {
    this->first->show();
  }
}

int main(int argc, char *argv[]){
  ll<int> *list = new ll<int>();
  printf("showing list before add\n");
  list->show();
  list->addFront(5);
  printf("showing list after add\n");
  list->show();
  printf("the list now has %d elements\n", list->getElementCount());
  list->addFront(6);
  printf("showing list after add\n");
  list->show();
  printf("the list now has %d elements\n", list->getElementCount());
  list->addFront(7);
  printf("showing list after add\n");
  list->show();
  printf("the list now has %d elements\n", list->getElementCount());
  printf("the list now has %d elements\n", list->getElementCount());
  list->addBack(8);
  printf("showing list after add\n");
  list->show();
  printf("the list now has %d elements\n", list->getElementCount());
}

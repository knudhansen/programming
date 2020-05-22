#include "linked_list.h"
#include "math.h"

class Int {
private:
  int value;
public:
  Int(int value) {
    this->value = value;
  }
  char* toString(void) {
    char *rv = (char*)malloc((log10(value) + 1) * sizeof(char));
    sprintf(rv, "%d", this->value);
    return rv;
  }
};

int main (int argc, char *argv[]) {
  LinkedListElement<Int> *lleInt = new LinkedListElement<Int>(new Int(5));
  LinkedList<Int> *llInt = new LinkedList<Int>();
  llInt->print();
  llInt->append(new Int(5));
  llInt->print();

  printf("printing list using iterator...\n");
  for (LinkedList<Int>::iterator it = llInt->begin(); it != llInt->end(); it++) {
    printf ("%s\n", (*it).toString());
  }
  printf("...done printing list using iterator\n");
}

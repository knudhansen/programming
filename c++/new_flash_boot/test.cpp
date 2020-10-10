#include "status.h"

extern "C" {
  status_t boot_from_nvram();
}

int main(int argc, char *argv[]) {
  boot_from_nvram();
}

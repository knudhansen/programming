#include <stdlib.h>
#include <stdbool.h>
#include <vector>

extern "C" {
#include "partition_handler.h"
}
bool parthdlstub_header_ok;

typedef struct partition_struct {
  bool partition_entry_ok;
  parthdl_type_t partition_type;
} partition_t;

std::vector<partition_t> partitions;

void parthdlstub_init(bool header_ok) {
  parthdlstub_header_ok = header_ok;
}

void parthdlstub_add_partition(bool partition_entry_ok,
			       parthdl_type_t partition_type) {
  partition_t *partition = (partition_t*)malloc(sizeof(partition_t));
  partition->partition_entry_ok = partition_entry_ok;
  partition->partition_type = partition_type;
}

status_t parthdl_read_partition_table(parthdl_partition_table_header_t *partition_table_header) {
  partition_table_header->partition_table_header_ok = true;
  return SUCCESS;
}

uint32_t parthdl_get_partition_count(const parthdl_partition_table_header_t *partition_table_header) {
  return partitions.size();
}

//  "_parthdl_get_partition_entry", referenced from:
//      _boot_from_nvram in boot.o
//  "_parthdl_get_partition_type", referenced from:


   

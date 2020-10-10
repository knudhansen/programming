#ifndef PARTITION_HANDLER_H
#define PARTITION_HANDLER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "status.h"

#define PRINTF printf

typedef enum parthdl_type_enum {
  BOOT,
  NORMAL
} parthdl_type_t;

struct parthdl_partition_table_header_struct;
struct parthdl_partition_entry_struct;

status_t parthdl_read_partition_table(struct parthdl_partition_table_header_struct *partition_table_header);
uint32_t parthdl_get_partition_count(struct parthdl_partition_table_header_struct *partition_table_header);
status_t parthdl_get_partition_entry(struct parthdl_partition_entry_struct *partition_entry, const struct parthdl_partition_table_header_struct *partition_table_header, uint32_t i);
parthdl_type_t parthdl_get_partition_type(const struct parthdl_partition_entry_struct *partition_entry);

#endif

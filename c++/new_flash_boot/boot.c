#include "partition_handler.h"
#include "status.h"

status_t boot_from_nvram() {
  uint32_t i;

  status_t status;

  status = parthdl_read_partition_table();
  if (status != SUCCESS) {
    return status;
  }

  for (i=0; i<parthdl_get_partition_count(&partition_table_header); i++) {
    parthdl_partition_entry_t partition_entry;
    status = parthdl_get_partition_entry(&partition_entry, &partition_table_header, i);
    if (status != SUCCESS) {
      return status;
    }

    if (parthdl_get_partition_type(&partition_entry) == BOOT) {
      PRINTF("Booting from partition %d\n",i);
    }
  }

  PRINTF("No boot partition found");  
  return FAILURE;
}

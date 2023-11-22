
// include guards to prevent double declaration of any identifiers 
// such as types, enums and static variables
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "../headers/cpu.h"

/*======================================*/
/*      physical memory on dram chips   */
/*======================================*/

// physical memory space is decided by the physical address
// in this simulator, there are 4 + 6 + 6 = 16 bit physical adderss
// then the physical space is (1 << 16) = 65536
// total 16 physical memory
#define PHYSICAL_MEMORY_SPACE   65536
#define MAX_INDEX_PHYSICAL_PAGE 15

// physical memory
// 16 physical memory pages
extern uint8_t phy_mem[PHYSICAL_MEMORY_SPACE];

/*======================================*/
/*      memory R/W                      */
/*======================================*/

// used by instructions: read or write uint64_t to DRAM
uint64_t read64bits_dram(uint64_t phy_addr, core_t *core);
void write64bits_dram(uint64_t phy_addr, uint64_t data, core_t *core);
void readinst_dram(uint64_t phy_addr, char *buf, core_t *core);
void writeinst_dram(uint64_t phy_addr, const char *str, core_t *core);

#endif
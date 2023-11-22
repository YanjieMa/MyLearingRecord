
// Memory Management Unit 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../headers/cpu.h"
#include "../../headers/memory.h"
#include "../../headers/common.h"

uint64_t virAddr2phyAddr(uint64_t vir_addr, core_t *core)
{
    return vir_addr % PHYSICAL_MEMORY_SPACE;
}



// Dynamic Random Access Memory
#include <string.h>
#include <assert.h>
#include "../headers/cpu.h"
#include "../headers/memory.h"
#include "../headers/common.h"

/*  
Be careful with the x86-64 little endian integer encoding
e.g. write 0x00007fd357a02ae0 to cache, the memory lapping should be:
    e0 2a a0 57 d3 7f 00 00
*/

uint8_t phy_mem[PHYSICAL_MEMORY_SPACE];

// memory accessing used in instructions
uint64_t read64bits_dram(uint64_t phy_addr, core_t *cr)
{
    if (DEBUG_ENABLE_SRAM_CACHE == 1)
    {
        // try to load uint64_t from SRAM cache
        // little-endian
    }
    else
    {
        // read from DRAM directly
        // little-endian
        uint64_t val = 0x0;

        for(int i=0; i<8; i++){
            val += (((uint64_t)phy_mem[phy_addr + i ]) << ((1<<3)*i));

        }
        return val;
    }
}

void write64bits_dram(uint64_t phy_addr, uint64_t data, core_t *cr)
{
    if (DEBUG_ENABLE_SRAM_CACHE == 1)
    {
        // try to write uint64_t to SRAM cache
        // little-endian
    }
    else
    {
        // write to DRAM directly
        // little-endian
        for(int i=0; i<8; i++){
            phy_mem[phy_addr + i] = (data >> (8*i) ) & 0xff;
        }
    }
}

void readinst_dram(uint64_t phy_addr, char *buf, core_t *core)
{
    for (int i = 0; i < MAX_INSTRUCTION_CHAR; ++ i)
    {
        buf[i] = (char)phy_mem[phy_addr + i];
    }
}

void writeinst_dram(uint64_t phy_addr, const char *str, core_t *core)
{
    int len = strlen(str);
    assert(len < MAX_INSTRUCTION_CHAR);

    for (int i = 0; i < MAX_INSTRUCTION_CHAR; ++ i)
    {
        if (i < len)
        {
            phy_mem[phy_addr + i] = (uint8_t)str[i];
        }
        else
        {
            phy_mem[phy_addr + i] = 0;
        }
    }
}
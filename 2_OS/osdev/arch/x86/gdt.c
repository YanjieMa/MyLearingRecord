#include <osdev/arch/x86/gdt.h>

#define GDT_ENTRY (4+1)

unsigned long long _gdt[GDT_ENTRY];
unsigned short _gdt_limit = sizeof(_gdt) - 1;

void _set_gdt_entry(unsigned int index, unsigned int base, unsigned int limit, unsigned int flags)
{
	_gdt[index] = SEG_BASE_H(base) | flags | SEG_LIM_H(limit) | SEG_BASE_M(base);
    _gdt[index] = _gdt[index] << 32;
    _gdt[index] |= SEG_BASE_L(base) | SEG_LIM_L(limit);
}


void _init_gdt()
{
	_set_gdt_entry(0, 0, 0, 0);
	_set_gdt_entry(1, 0, 0xfffff, SEG_R0_CODE);
	_set_gdt_entry(2, 0, 0xfffff, SEG_R0_DATA);
	_set_gdt_entry(3, 0, 0xfffff, SEG_R3_CODE);
	_set_gdt_entry(4, 0, 0xfffff, SEG_R3_DATA);

}

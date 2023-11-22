#include <osdev/tty/tty.h>
#include <osdev/arch/x86/gdt.h>
void _kernel_init()
{
	_init_gdt();
}

void _kernel_main(void *info_table)
{
	unsigned long i = (unsigned long) info_table;
	i++;
	tty_set_theme(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	tty_put_str("hello kernel!\n");
}


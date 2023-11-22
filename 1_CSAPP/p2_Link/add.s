	.file	"add.c"
	.text
	.data
	.align 4
	.type	_ZZ5myaddiiE3tmp, @object
	.size	_ZZ5myaddiiE3tmp, 4
_ZZ5myaddiiE3tmp:
	.long	16
	.text
	.globl	_Z5myaddii
	.type	_Z5myaddii, @function
_Z5myaddii:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	_ZZ5myaddiiE3tmp(%rip), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, _ZZ5myaddiiE3tmp(%rip)
	movl	_ZZ5myaddiiE3tmp(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5myaddii, .-_Z5myaddii
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

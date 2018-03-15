	.file	"test.c"
	.intel_syntax noprefix
	.globl	accum
	.bss
	.align 4
accum:
	.space 4
	.text
	.globl	sum
	.def	sum;	.scl	2;	.type	32;	.endef
	.seh_proc	sum
sum:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 16
	.seh_stackalloc	16
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	mov	DWORD PTR 24[rbp], edx
	mov	edx, DWORD PTR 16[rbp]
	mov	eax, DWORD PTR 24[rbp]
	add	eax, edx
	mov	DWORD PTR -4[rbp], eax
	mov	edx, DWORD PTR accum[rip]
	mov	eax, DWORD PTR -4[rbp]
	add	eax, edx
	mov	DWORD PTR accum[rip], eax
	mov	eax, DWORD PTR -4[rbp]
	add	rsp, 16
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 5.1.0"

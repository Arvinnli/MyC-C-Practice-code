; // %rax 作为函数返回值使用。
; // %rsp 栈指针寄存器，指向栈顶
; // %rdi，%rsi，%rdx，%rcx，%r8，%r9 用作函数参数，依次对应第1参数，第2参数。。。
; // %rbx，%rbp，%r12，%r13，%14，%15 用作数据存储，遵循被调用者使用规则，简单说就是随便用，
; // 调用子函数之前要备份它，以防他被修改
; // %r10，%r11 用作数据存储，遵循调用者使用规则，简单说就是使用之前要先保存原值



; // 函数 开始
; // 无参数 无局部变量

; // phshhq rbp 
	pushq	%rbp ;保存 rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp ;栈顶指针 赋值给rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	nop
	popq	%rbp        ;取出rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 5.1.0"


;函数开始 无参数 有局部变量 int [10]
	pushq	%rbp            ;rbp入栈 保存   
	.seh_pushreg	%rbp
	movq	%rsp, %rbp      ;栈顶指针 存入 rbp  假设rsp =128 
	.seh_setframe	%rbp, 0
	subq	$48, %rsp       ;栈顶指针 - 48  rsp = 80
	.seh_stackalloc	48      ;从栈中分配 48 个字节
	.seh_endprologue
	movq	$0, -48(%rbp)   ;rbp 调用函数开始时的 栈顶指针.  80
	movq	$0, -40(%rbp)   ;
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
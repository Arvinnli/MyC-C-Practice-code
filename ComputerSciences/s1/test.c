// #define src_t char
// #define dest_t  int


// %rax 作为函数返回值使用。
// %rsp 栈指针寄存器，指向栈顶
// %rdi，%rsi，%rdx，%rcx，%r8，%r9 用作函数参数，依次对应第1参数，第2参数。。。
// %rbx，%rbp，%r12，%r13，%14，%15 用作数据存储，遵循被调用者使用规则，简单说就是随便用，
// 调用子函数之前要备份它，以防他被修改
// %r10，%r11 用作数据存储，遵循调用者使用规则，简单说就是使用之前要先保存原值

	// push	rbp                     rbp 入展
	// .seh_pushreg	rbp
	// mov	rbp, rsp
	// .seh_setframe	rbp, 0
	// sub	rsp, 16
	// .seh_stackalloc	16
	// .seh_endprologue
	// movsx	edx, BYTE PTR -1[rbp]
	// mov	rax, QWORD PTR -16[rbp]
	// mov	DWORD PTR [rax], edx
	// nop
	// add	rsp, 16

void fun(){
    int a[10] = {0};
}
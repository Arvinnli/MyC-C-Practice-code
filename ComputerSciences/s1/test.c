// #define src_t char
// #define dest_t  int


// %rax ��Ϊ��������ֵʹ�á�
// %rsp ջָ��Ĵ�����ָ��ջ��
// %rdi��%rsi��%rdx��%rcx��%r8��%r9 �����������������ζ�Ӧ��1��������2����������
// %rbx��%rbp��%r12��%r13��%14��%15 �������ݴ洢����ѭ��������ʹ�ù��򣬼�˵��������ã�
// �����Ӻ���֮ǰҪ���������Է������޸�
// %r10��%r11 �������ݴ洢����ѭ������ʹ�ù��򣬼�˵����ʹ��֮ǰҪ�ȱ���ԭֵ

	// push	rbp                     rbp ��չ
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
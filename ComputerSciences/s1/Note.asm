; // %rax ��Ϊ��������ֵʹ�á�
; // %rsp ջָ��Ĵ�����ָ��ջ��
; // %rdi��%rsi��%rdx��%rcx��%r8��%r9 �����������������ζ�Ӧ��1��������2����������
; // %rbx��%rbp��%r12��%r13��%14��%15 �������ݴ洢����ѭ��������ʹ�ù��򣬼�˵��������ã�
; // �����Ӻ���֮ǰҪ���������Է������޸�
; // %r10��%r11 �������ݴ洢����ѭ������ʹ�ù��򣬼�˵����ʹ��֮ǰҪ�ȱ���ԭֵ



; // ���� ��ʼ
; // �޲��� �޾ֲ�����

; // phshhq rbp 
	pushq	%rbp ;���� rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp ;ջ��ָ�� ��ֵ��rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	nop
	popq	%rbp        ;ȡ��rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 5.1.0"


;������ʼ �޲��� �оֲ����� int [10]
	pushq	%rbp            ;rbp��ջ ����   
	.seh_pushreg	%rbp
	movq	%rsp, %rbp      ;ջ��ָ�� ���� rbp  ����rsp =128 
	.seh_setframe	%rbp, 0
	subq	$48, %rsp       ;ջ��ָ�� - 48  rsp = 80
	.seh_stackalloc	48      ;��ջ�з��� 48 ���ֽ�
	.seh_endprologue
	movq	$0, -48(%rbp)   ;rbp ���ú�����ʼʱ�� ջ��ָ��.  80
	movq	$0, -40(%rbp)   ;
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
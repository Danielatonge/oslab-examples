	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 4
	.globl	_func                   ## -- Begin function func
	.p2align	4, 0x90
_func:                                  ## @func
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	$0, -20(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$150000, -20(%rbp)      ## imm = 0x249F0
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	_counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, _counter(%rip)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB0_1
LBB0_4:
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	xorl	%eax, %eax
	movl	%eax, %ecx
	movl	$0, -4(%rbp)
	leaq	-16(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_func(%rip), %rdx
	callq	_pthread_create
	xorl	%r8d, %r8d
	movl	%r8d, %ecx
	leaq	-24(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_func(%rip), %rdx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pthread_create
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-16(%rbp), %rdi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-24(%rbp), %rdi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	movl	_counter(%rip), %esi
	leaq	L_.str(%rip), %rdi
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_counter                ## @counter
.zerofill __DATA,__common,_counter,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Value of counter: %d\n"


.subsections_via_symbols

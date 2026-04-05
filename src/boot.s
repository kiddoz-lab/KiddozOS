.set MAGIC, 0x1BADB002
.set FLAGS, 3
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global start
start:
    mov $stack_top, %esp
    push %eax
    push %ebx
    call kernel_main

hang:
    hlt
    jmp hang

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:
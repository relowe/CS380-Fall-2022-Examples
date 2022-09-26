# Hello world in x86_64 linux assembly
# to compile:
#      as hello.S -o hello.o
#      gcc -nostdlib -static hello.o -o hello
.section text
.global _start
_start:
    # write(1, msg, 13)
    mov $1, %rax        # Systemcall 1 (write)
    mov $1, %rdi        #   stdout
    mov msg, %rsi       #   buf = msg
    mov $13, %rdx       #   count = 13
    syscall             # Invoke the kernel


.section data
msg: .ascii "Hello, world\n"

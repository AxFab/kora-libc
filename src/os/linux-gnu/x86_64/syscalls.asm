use64

global __syscall
global __syscall0
global __syscall1
global __syscall2
global __syscall3
global __syscall4
global __syscall5
global __syscall6
global __syscall7
extern __errno_location
extern _GLOBAL_OFFSET_TABLE_

%macro  get_GOT 0
        call    %%getgot
  %%getgot:
        pop     rbx
        add     rbx,_GLOBAL_OFFSET_TABLE_+$$-%%getgot wrt ..gotpc
%endmacro

%macro SAVE_ARGS_IRQ 0
    ; cld
    ; start from rbp in pt_regs and jump over
    mov [rbp + 0], rdi
    mov [rbp + 8], rsi
    mov [rbp + 16], rdx
    mov [rbp + 24], rcx
    mov [rbp + 32], r8
    mov [rbp + 40], r9
    mov [rbp + 48], r10
    mov [rbp + 56], r11
    sub rsp, 64
%endmacro

%macro RESTORE_ARGS_IRQ 0
    ; cld
    ; start from rbp in pt_regs and jump over
    add rsp, 64
    mov rdi, [rbp + 0]
    mov rsi, [rbp + 8]
    mov rdx, [rbp + 16]
    mov rcx, [rbp + 24]
    mov r8, [rbp + 32]
    mov r9, [rbp + 40]
    mov r10, [rbp + 48]
    mov r11, [rbp + 56]
%endmacro
align 64

__syscall0:
__syscall1:
__syscall2:
__syscall3:
__syscall4:
__syscall5:
__syscall6:
__syscall7:
__syscall:
    push rbp
    mov rbp, rsp
    SAVE_ARGS_IRQ
    mov rsi, [rbp + 48]
    mov rdi, [rbp + 40]
    mov rbx, [rbp + 32]
    mov rdx, [rbp + 24]
    mov rcx, [rbp + 16]
    mov rax, [rbp + 8]
    int 0x80
    mov rdi, rax

    get_GOT
    mov rax,[rbx + __errno_location wrt ..got]
    call rax

    mov [rax], rdx
    mov rax, rdi
    RESTORE_ARGS_IRQ
    leave
    ret

use32

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
        pop     ebx
        add     ebx,_GLOBAL_OFFSET_TABLE_+$$-%%getgot wrt ..gotpc
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
    push ebp
    mov ebp, esp
    pusha
    mov esi, [ebp + 48]
    mov edi, [ebp + 40]
    mov ebx, [ebp + 32]
    mov edx, [ebp + 24]
    mov ecx, [ebp + 16]
    mov eax, [ebp + 8]
    int 0x40
    mov edi, eax

    get_GOT
    mov eax,[ebx + __errno_location wrt ..got]
    call eax

    mov [eax], edx
    mov eax, edi
    popa
    leave
    ret

;      This file is part of the KoraOS project.
;  Copyright (C) 2015-2021  <Fabien Bavent>
;
;  This program is free software: you can redistribute it and/or modify
;  it under the terms of the GNU Affero General Public License as
;  published by the Free Software Foundation, either version 3 of the
;  License, or (at your option) any later version.
;
;  This program is distributed in the hope that it will be useful,
;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;  GNU Affero General Public License for more details.
;
;  You should have received a copy of the GNU Affero General Public License
;  along with this program.  If not, see <http://www.gnu.org/licenses/>.
; -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
use64

global _start
extern __libc_init, __libc_fini, main, exit
extern _GLOBAL_OFFSET_TABLE_

%macro  get_GOT 0
        push    rbx
        call    %%getgot
  %%getgot:
        pop     rbx
        add     rbx,_GLOBAL_OFFSET_TABLE_+$$-%%getgot wrt ..gotpc
%endmacro

%macro PI_CALL 1
    get_GOT
    mov rax,[rbx + %1 wrt ..got]
    call rax
%endmacro


_start:
    mov rbp, rsp
    and rsp, ~0xF

    PI_CALL __libc_init

    mov rax, [rbp + 4] ; argc
    mov [rsp], rax
    mov rax, [rbp + 8] ; argv
    mov [rsp + 4], rax
    mov rax, [rbp + 12] ; env
    mov [rsp + 8], rax
    call main
    mov [rsp], rax

    PI_CALL __libc_fini
    PI_CALL exit

    jmp $

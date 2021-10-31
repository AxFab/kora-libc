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
use32

global _start
extern __libc_init, __libc_fini, main, exit
extern _GLOBAL_OFFSET_TABLE_

%macro  get_GOT 0
        push    ebx
        call    %%getgot
  %%getgot:
        pop     ebx
        add     ebx,_GLOBAL_OFFSET_TABLE_+$$-%%getgot wrt ..gotpc

%endmacro

%macro PI_CALL 1
    get_GOT
    mov eax,[ebx + %1 wrt ..got]
    call eax
%endmacro


_start:
    mov ebp, esp
    and esp, ~0xF

    get_GOT
    mov eax,[ebx + __libc_init wrt ..got]
    call eax

    mov eax, [ebp + 4] ; argc
    mov [esp], eax
    mov eax, [ebp + 8] ; argv
    mov [esp + 4], eax
    mov eax, [ebp + 12] ; env
    mov [esp + 8], eax
    call main
    mov [esp], eax

    get_GOT
    mov eax,[ebx + __libc_fini wrt ..got]
    call eax

    get_GOT
    mov eax,[ebx + exit wrt ..got]
    call eax

    jmp $

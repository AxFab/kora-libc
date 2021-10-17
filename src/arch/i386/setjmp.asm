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

global setjmp, longjmp

setjmp:
    mov eax, [esp + 4] ; Get buffer
    mov [eax], ebx ; Store EBX
    mov [eax + 4], esi ; Store ESI
    mov [eax + 8], edi ; Store EDI
    mov [eax + 12], ebp ; Store EBP
    lea ecx, [esp + 4] ; ESP
    mov [eax + 16], ecx ; Store ESP
    mov ecx, [esp] ; EIP
    mov [eax + 20], ecx ; Store EIP
    xor eax, eax
    ret

longjmp:
    mov edx, [esp + 4] ; Get buffer
    mov eax, [esp + 8] ; Get value
    test eax, eax
    jnz .n
    inc eax ; Be sure we don't return zero!
.n:
    mov ebx, [edx] ; Restore EBX
    mov esi, [edx + 4] ; Restore ESI
    mov edi, [edx + 8] ; Restore EDI
    mov ebp, [edx + 12] ; Restore EBP
    mov ecx, [edx + 16] ; Restore ESP
    mov esp, ecx
    mov ecx, [edx + 20] ; Restore EIP
    jmp ecx

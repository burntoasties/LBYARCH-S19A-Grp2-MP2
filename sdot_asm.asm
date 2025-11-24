%include "io64.inc"

section .text
global sdot_asm

sdot_asm:
    xor     r9, r9
    pxor    xmm0, xmm0

.loop:
    cmp     r9, r8
    jge     .done

    movss   xmm1, [rcx + r9*4]
    movss   xmm2, [rdx + r9*4]
    mulss   xmm1, xmm2
    addss   xmm0, xmm1

    inc     r9
    jmp     .loop

.done:
    ret

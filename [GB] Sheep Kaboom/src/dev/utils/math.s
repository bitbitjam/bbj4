; Math functions
; Light Games 2017

.globl _div8
; @input:
;   E - Numerator
;   D - Denominator
; @output:
;   D - Result
;   E - Mod
_div8:
    lda     hl, 2(sp)
    ld      a,  (hli)
    ld      e,  a
    ld      a,  (hli)
    ld      d,  a
    ld      l,  #8
    xor     a
_div8_0:
    sla     e
    rla
    cp      d
    jr      c,  _div8_1
    inc     e
    sub     d
_div8_1: 
    dec     l
    jr      nz, _div8_0
    ld      d,  a
    ret
    
.globl  _mul8
; @input:
;   E - Factor 1
;   D - Factor 2
; @output:
;   E - Result
_mul8:
    lda     hl, 2(sp)
    ld      a,  (hli)
    ld      e,  a
    ld      a,  (hli)
    ld      d,  a
    ld      l,  #8
    xor     a
_mul8_0:
    rlca
    rlc     e
    jr      nc, _mul8_1
    add     a,  d
_mul8_1:
    dec     l
    jr      nz, _mul8_0
    ld      e,  a
    ret

.globl  _mul16
; @input:
;   1 (UWORD) - Factor 1
;   2 (UBYTE) - Factor 2
; @output
;   DE - Resultado
_mul16:
    lda     hl, 2(sp)
    ld      a,  (hli)
    ld      e,  a
    ld      a,  (hli)
    ld      d,  a
    ld      a,  (hl)
    ld      b,  #8
    ld      hl, #0
_mul16_0:
    add     hl, hl
    rlca
    jr      nc, _mul16_1
    add     hl, de
_mul16_1:
    dec     b
    jr      nz, _mul16_0
    ld      d,  h
    ld      e,  l
    ret

.globl  _div16
; @input:
;   1 (UWORD) - Numerator
;   2 (UBYTE) - Denominator
;   3 (UWORD) - Result address
; @output
;   E - Remainder
;   (Result address) - Result
_div16:
    lda     hl, 2(sp)
    push    bc
    ld      a,  (hli)
    ld      c,  a
    ld      a,  (hli)
    ld      b,  a
    ld      a,  (hli)
    ld      d,  a
    ld      a,  (hli)
    ld      e,  a
    ld      a,  (hli)
    ld      h,  b
    ld      l,  c       ; HL: Numerator
    ld      c,  d       ; C: Denominator
    ld      d,  a       ; DE: Result adress
    ld      b,  #16
    xor     a
_div16_0:
    add     hl, hl
    rla
    cp      c
    jr      c,  _div16_1
    inc     l
    sub     c
_div16_1: 
    dec     b
    jr      nz, _div16_0
    ld      c,  a
    ld      a,  l
    ld      (de),   a
    inc     de
    ld      a,  h
    ld      (de),   a
    ld      d,  #0
    ld      e,  c          ; E - Remainder
    pop     bc
    ret
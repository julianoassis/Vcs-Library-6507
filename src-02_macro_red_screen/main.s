
.INCLUDE "../lib/6507mapping.s"
.INCLUDE "macros.s"

.BANK 0 .SLOT ROM
.ORGA $f000           ; F000-FFFF  Cartridge Memory (4 Kbytes area)
.SECTION "ROM" FORCE

Start:

    jsr VerticalScan
    ;
    ldx #SCANLINE_NTSC

    lda #$40
    sta COLUBK
    ;
    jsr End_VerticalScan

Screen1_scanloop1:
    dex                         ; decrement SCANLINE
    sta WSYNC                   ; sync w/ scanline
    bne Screen1_scanloop1       ;

    jsr Overscan
    ;
    ; nothing here for now
    ;
    jsr End_Overscan



    jmp Start
    
.ENDS


.ORGA $fffc
.SECTION "ENDROM" FORCE

.EMPTYFILL $FF
.dw Start
.dw Start

.ENDS

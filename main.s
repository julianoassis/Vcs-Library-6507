
.INCLUDE "6507mapping.s"

.BANK 0 .SLOT ROM
.ORGA $f000           ; F000-FFFF  Cartridge Memory (4 Kbytes area)
.SECTION "ROM" FORCE

Start:

    ;
    lda #90
    sta COLUBK    
    ;

    jmp Start
    
.ENDS


.ORGA $fffc
.SECTION "ENDROM" FORCE

.EMPTYFILL $FF
.dw Start
.dw Start

.ENDS

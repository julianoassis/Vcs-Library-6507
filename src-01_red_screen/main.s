
.INCLUDE "../lib/6507mapping.s"

.BANK 0 .SLOT ROM
.ORGA $f000           ; F000-FFFF  Cartridge Memory (4 Kbytes area)
.SECTION "ROM" FORCE

Start:

    ; Vertical Sync
    lda %00001110          ; each '1' bits generate a VSYNC ON line (bits 1..3)
WAIT_VSYNC:
    sta WSYNC              ; 1st '0' bit resets Vsync, 2nd '0' bit exit loop
    sta VSYNC
    lsr
    bne WAIT_VSYNC         ; branch until VYSNC has been reset;

    ; Enable VBLANK (disable output)
    lda $2
    sta VBLANK

    ldx #36
VERTICALSCAN:
    sta WSYNC              ; wait for next scanline
    dex
    bne VERTICALSCAN

    ; Enable VBLANK (enable output)
    lda $0
    sta VBLANK

    lda #$40              ; Background Color ($40 = red)
    sta COLUBK

    ldx #192              ; Draw the 192 scanlines
SCREEN1_SCANLOOP1:
    sta WSYNC
    dex
    bne SCREEN1_SCANLOOP1

    ; Enable VBLANK (disable output)
    lda $2
    sta VBLANK

    ldx #30                ; 30 lines of overscan
OVERSCAN:
    sta WSYNC
    dex
    bne OVERSCAN

    jmp Start
    
.ENDS


.ORGA $fffc
.SECTION "ENDROM" FORCE

.EMPTYFILL $FF
.dw Start
.dw Start

.ENDS

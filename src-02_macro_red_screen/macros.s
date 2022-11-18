; 
;  
;
; Note: Algumas MACROS originalmente escritas por Andrew Davie adaptadas em artigos de Duane Alan Hahn, a.k.a. Random Terrain,
; encontrado em  https://www.randomterrain.com/atari-2600-memories.html 
;
; Author: https://github.com/julianoassis
; 
; Mais Infos:
; https://problemkaputt.de/2k6specs.htm
; https://www.atariarchives.org/alp/
;
; 2021

.MACRO "CLEAN_START"

    sei     
    cld
   
    ldx $0
    txa
    tay

CLEAR_STACK:
    dex
    txs
    pha
    bne CLEAR_STACK

.ENDM
 

.MACRO "VERTICALSCAN"
                      
                      ; Vertical Sync 
    lda %00001110     ; each '1' bits generate a VSYNC ON line (bits 1..3)
WAIT_VSYNC:
    sta WSYNC         ; 1st '0' bit resets Vsync, 2nd '0' bit exit loop
    sta VSYNC
    lsr
    bne WAIT_VSYNC    ; branch until VYSNC has been reset;
    
    lda #43           ; (37 lines x 76 cycles) / 64 clocks = 43.93
    sta TIM64T

; Enable VBLANK (disable output)
    lda $2
    sta VBLANK    
    
.ENDM


.MACRO "END_VERTICALSCAN"

WAIT_VSCAN:
    lda INTIM        
    bne WAIT_VSCAN

    sta WSYNC         ; line 37

; Enable VBLANK (enable output)
    lda #0
    sta VBLANK

.ENDM


.MACRO "OVERSCAN"

    lda #35          ; (30 lines x 76 cycles) / 64 clocks = 35.625
    sta TIM64T
    
; Enable VBLANK (disable output)
    lda $2
    sta VBLANK

 .ENDM   
 

.MACRO "END_OVERSCAN"

WAIT_OSCAN:
    lda INTIM
    bne WAIT_OSCAN
    
    sta WSYNC          ; line 30
     
.ENDM


; ROTINES - APPEND TO ROM
;
;  Rotinas para facilitar o as chamadas de MACROS, não precisa utilizá-las 
; se não quiser.
;

.SECTION "SCREEN_SCAN" FREE APPENDTO "ROM"

.DEFINE SCANLINE_NTSC  192 


VerticalScan:
    VERTICALSCAN
    rts    
    
End_VerticalScan:
    END_VERTICALSCAN   
    rts

Overscan:
    OVERSCAN
    rts

End_Overscan:
    END_OVERSCAN    
    rts
    
.ENDS






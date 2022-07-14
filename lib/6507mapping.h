; 
;  Baseado na biblioteca vcs.h originalmente desenvolvido para o compilador Dasm, traduzido
; para utilização nos compiladores wla-dx para processadores 6502(6507).
;
; Author: https://github.com/julianoassis
; 
; More Info:
; https://problemkaputt.de/2k6specs.htm
; https://www.atariarchives.org/alp/
; https://www.randomterrain.com/atari-2600-memories.html 
;
; 2021



.8BIT

.MEMORYMAP
    DEFAULTSLOT 4
    SLOT 0 START $0000 SIZE $002C NAME "TIAw"   ; 0000-002C  TIA Write
    SLOT 1 START $0030 SIZE $000D NAME "TIAr"   ; 0000-000D  TIA Read (sometimes mirrored at 0030-003D)
    SLOT 2 START $0080 SIZE $007F NAME "RAM"    ; 0080-00FF  PIA RAM (128 bytes)
    SLOT 3 START $0297 SIZE $0017 NAME "PIA"    ; 0280-0297  PIA Ports and Timer
    SLOT 4 START $F000 SIZE $1000 NAME "ROM"    ; F000-FFFF  Cartridge Memory (4 Kbytes area)
.ENDME


.ROMBANKMAP
    BANKSTOTAL 1
    BANKSIZE $1000
    BANKS 1
.ENDRO

; TIA - WRITE ADDRESS SUMMARY (Write only)
.BANK 0 .SLOT TIAw

.ENUMID $0
.ENUMID VSYNC   ;   00   ......1.  vertical sync set-clear
.ENUMID VBLANK  ;   01   11....1.  vertical blank set-clear
.ENUMID WSYNC   ;   02   <strobe>  wait for leading edge of horizontal blank
.ENUMID RSYNC   ;   03   <strobe>  reset horizontal sync counter
.ENUMID NUSIZ0  ;   04   ..111111  number-size player-missile 0
.ENUMID NUSIZ1  ;   05   ..111111  number-size player-missile 1
.ENUMID COLUP0  ;   06   1111111.  color-lum player 0 and missile 0
.ENUMID COLUP1  ;   07   1111111.  color-lum player 1 and missile 1
.ENUMID COLUPF  ;   08   1111111.  color-lum playfield and ball
.ENUMID COLUBK  ;   09   1111111.  color-lum background
.ENUMID CTRLPF  ;   0A   ..11.111  control playfield ball size & collisions
.ENUMID REFP0   ;   0B   ....1...  reflect player 0
.ENUMID REFP1   ;   0C   ....1...  reflect player 1
.ENUMID PF0     ;   0D   1111....  playfield register byte 0
.ENUMID PF1     ;   0E   11111111  playfield register byte 1
.ENUMID PF2     ;   0F   11111111  playfield register byte 2
.ENUMID RESP0   ;   10   <strobe>  reset player 0
.ENUMID RESP1   ;   11   <strobe>  reset player 1
.ENUMID RESM0   ;   12   <strobe>  reset missile 0
.ENUMID RESM1   ;   13   <strobe>  reset missile 1
.ENUMID RESBL   ;   14   <strobe>  reset ball
.ENUMID AUDC0   ;   15   ....1111  audio control 0
.ENUMID AUDC1   ;   16   ....1111  audio control 1
.ENUMID AUDF0   ;   17   ...11111  audio frequency 0
.ENUMID AUDF1   ;   18   ...11111  audio frequency 1
.ENUMID AUDV0   ;   19   ....1111  audio volume 0
.ENUMID AUDV1   ;   1A   ....1111  audio volume 1
.ENUMID GRP0    ;   1B   11111111  graphics player 0
.ENUMID GRP1    ;   1C   11111111  graphics player 1
.ENUMID ENAM0   ;   1D   ......1.  graphics (enable) missile 0
.ENUMID ENAM1   ;   1E   ......1.  graphics (enable) missile 1
.ENUMID ENABL   ;   1F   ......1.  graphics (enable) ball
.ENUMID HMP0    ;   20   1111....  horizontal motion player 0
.ENUMID HMP1    ;   21   1111....  horizontal motion player 1
.ENUMID HMM0    ;   22   1111....  horizontal motion missile 0
.ENUMID HMM1    ;   23   1111....  horizontal motion missile 1
.ENUMID HMBL    ;   24   1111....  horizontal motion ball
.ENUMID VDELP0  ;   25   .......1  vertical delay player 0
.ENUMID VDELP1  ;   26   .......1  vertical delay player 1
.ENUMID VDELBL  ;   27   .......1  vertical delay ball
.ENUMID RESMP0  ;   28   ......1.  reset missile 0 to player 0
.ENUMID RESMP1  ;   29   ......1.  reset missile 1 to player 1
.ENUMID HMOVE   ;   2A   <strobe>  apply horizontal motion
.ENUMID HMCLR   ;   2B   <strobe>  clear horizontal motion registers
.ENUMID CXCLR   ;   2C   <strobe>  clear collision latches

; TIA - READ ADDRESS SUMMARY (Read only)
.BANK 0 .SLOT TIAr

.ENUMID $30
.ENUMID CXM0P   ;   30   11......  read collision M0-P1, M0-P0 (Bit 7,6)
.ENUMID CXM1P   ;   31   11......  read collision M1-P0, M1-P1
.ENUMID CXP0FB  ;   32   11......  read collision P0-PF, P0-BL
.ENUMID CXP1FB  ;   33   11......  read collision P1-PF, P1-BL
.ENUMID CXM0FB  ;   34   11......  read collision M0-PF, M0-BL
.ENUMID CXM1FB  ;   35   11......  read collision M1-PF, M1-BL
.ENUMID CXBLPF  ;   36   1.......  read collision BL-PF, unused
.ENUMID CXPPMM  ;   37   11......  read collision P0-P1, M0-M1
.ENUMID INPT0   ;   38   1.......  read pot port
.ENUMID INPT1   ;   39   1.......  read pot port
.ENUMID INPT2   ;   3A   1.......  read pot port
.ENUMID INPT3   ;   3B   1.......  read pot port
.ENUMID INPT4   ;   3C   1.......  read input
.ENUMID INPT5   ;   3D   1.......  read input

; PIA 6532 - RAM, Switches, and Timer (Read/Write)
;.BANK 0 .SLOT RAM
; 11111111  128 bytes RAM (in PIA chip) for variables and stack


; PIA 6532 - RAM, Switches, and Timer (Read/Write)
.BANK 0 .SLOT PIA

.ENUMID $0280
.ENUMID SWCHA   ;   0280   11111111  Port A; input or output  (read or write)
.ENUMID SWACNT  ;   0281   11111111  Port A DDR, 0= input, 1=output
.ENUMID SWCHB   ;   0282   11111111  Port B; console switches (read only)
.ENUMID SWBCNT  ;   0283   11111111  Port B DDR (hardwired as input)
.ENUMID INTIM   ;   0284   11111111  Timer output (read only)
.ENUMID INSTAT  ;   0285   11......  Timer Status (read only, undocumented)

.ENUMID $0294
.ENUMID TIM1T   ;   0294   11111111  set 1 clock interval (838 nsec/interval)
.ENUMID TIM8T   ;   0295   11111111  set 8 clock interval (6.7 usec/interval)
.ENUMID TIM64T  ;   0296   11111111  set 64 clock interval (53.6 usec/interval)
.ENUMID T1024T  ;   0297   11111111  set 1024 clock interval (858.2 usec/interval)

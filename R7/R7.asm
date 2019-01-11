; Recitation 7
; Author: <Logan>
; Date:   <Oct 5 2016>
; Email:  <email>
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR mirror           ; call function
                HALT

; Parameter and return value
Param           .FILL 0x1234              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                               ; Mirrors bits 7:0 to 15:8
                                     ; ~20 lines of assembly code
 
                LD R0,Param          ; load pattern
                .COPY R1, R0         ; your code here
                LD R2, Mask
                AND R1, R1, R2
                LD R2, One
                LD R3, One
                LD R4, Eight
        Loop    ADD R3, R3, R3      ; Left shift r3 by 8 bits
                ADD R4, R4, #-1
                Brp Loop
                LD R4, Eight        ; reset r4 to 8
        Loop2   AND R5, R0, R2 
                Brz Step3
                ADD R1, R1, R3      ;Step 2
        Step3   ADD R2, R2, R2
                ADD R3, R3, R3      ;Step 4
                ADD R4, R4, #-1     ;Step 5
                Brp Loop2
                ST R1,Result         ; store result
                RET
;--------------------------------------------------------------------------
               .END


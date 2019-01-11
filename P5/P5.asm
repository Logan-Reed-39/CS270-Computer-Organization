; P5 Assignment
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL intAdd         ; (option 0)
                .FILL intSub         ; (option 1)
                .FILL intMul         ; (option 2)
                .FILL binaryOr       ; (option 3)
                .FILL leftShift      ; (option 4)
                .FILL rightShift     ; (option 5)

Main            LEA R0,Functions     ; get base of jump table
                LD  R1,Option        ; get option to use, no error checking
                ADD R0,R0,R1         ; add index of array
                LDR R0,R0,#0         ; get address of function
                JSRR R0              ; call selected function
                HALT

; Parameters and return values for all functions
Option          .FILL #5             ; which function to call
Param1          .FILL #5             ; space to specify first parameter
Param2          .FILL #2             ; space to specify second parameter
Result          .BLKW 1              ; space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
intAdd          LD R1, Param1        ; Result is Param1 + Param2
                LD R2, Param2        ; your code goes here (~4 lines)
                ADD R1, R1, R2
                ST R1, Result
                RET
;------------------------------------------------------------------------------
intSub          LD R1, Param1        ; Result is Param1 - Param2
                LD R2, Param2        ; your code goes here (~6 lines)
                NOT R2, R2
                ADD R2, R2, #1
                ADD R1, R1, R2
                ST R1, Result
                RET
;------------------------------------------------------------------------------
intMul          .zero R3
                LD R1, Param1        ; Result is Param1 * Param2
                BRz Store
                LD R2, Param2        ; your code goes here (~9 lines)
                BRz Store
           Loop ADD R3, R3, R1
                ADD R2, R2, #-1     ;Decrement R2
                BRp Loop
          Store ST R3, Result
                
                RET
;------------------------------------------------------------------------------
binaryOr        LD R1, Param1        ; Result is Param1 | Param2
                LD R2, Param2        ; your code goes here (~7 lines)
                NOT R1, R1
                NOT R2, R2
                AND R3, R1, R2
                NOT R3, R3
                ST R3, Result
                RET
;------------------------------------------------------------------------------
leftShift       LD R1, Param1        ; Result is Param1 << Param2
                LD R2, Param2        ; your code goes here (~7 lines)

          Loop2 ADD R1, R1, R1
                ADD R2, R2, #-1
                Brp Loop2
                ST R1, Result
                RET
;------------------------------------------------------------------------------
rightShift      LD R1, Param1        ; Result is Param1 >> Param2
                LD R2, Param2        ; your code goes here (~16 lines)
                AND R4, R4, #0       ; R4 made to 0
                ADD R4, R4, #1       ; mask
                NOT R4, R4 
                ADD R2, R2, #0       ;Needed a checker there 
                
                
         Loop3  BRz done
                AND R1, R1, R4       
                AND R3, R3, #0       ;counter
                ADD R2, R2, #0
                BRp Loop4
                
        Loop4  Brnz shift1
               ADD R3, R3, #1
               ADD R1, R1, #-2
               Brp Loop4
               
        shift1 ADD R1, R3, #0
               ADD R2, R2, #-1
               Brp Loop3
        
        done   ST R1, Result 
               RET
;------------------------------------------------------------------------------
                .END



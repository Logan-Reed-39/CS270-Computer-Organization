; Begin reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------
; Author: Fritz Sieker
;
; Description: Tests the implementation of a simple string library and I/O
;
; The ONLY exception to this is that you MAY change the .FILL values for
; Option, Value1 and Value2. this makes it easy to initialze the values in the
; program, so that you do not need to continually re-enter them. This
; makes debugging easier as you need only change your code and re-assemble.
; Your test value(s) will already be set.

            .ORIG x3000
            BR Main
Functions
            .FILL Test_pack         ; (option 0)
            .FILL Test_unpack       ; (option 1)
            .FILL Test_printCC      ; (option 2)
            .FILL Test_strlen       ; (option 3)
            .FILL Test_strcpy       ; (option 4)
            .FILL Test_strcat       ; (option 5)
            .FILL Test_strcmp       ; (option 6)

; Parameters and return values for all functions
Option      .FILL 6                 ; which function to call
String1     .FILL x4000             ; default location of 1st string
String2     .FILL x4100             ; default location of 2nd string
Result      .BLKW 1                 ; space to store result
Value1      .FILL x3478             ; used for testing pack/unpack
Value2      .FILL x5678             ; used for testing pack/unpack
lowerMask   .FILL 0x00FF            ; mask for lower 8 bits
upperMask   .FILL 0xFF00            ; mask for upper 8 bits

Main        LEA R0,Functions        ; get base of jump table
            LD  R1,Option           ; get option to use, no error checking
            ADD R0,R0,R1            ; add index of array
            LDR R0,R0,#0            ; get address to test
            JMP R0                  ; execute test

Test_pack   
            LD R0,Value1            ; load first character
            LD R1,Value2            ; load second character
            JSR pack                ; pack characters
            ST R0,Result            ; save packed result
            HALT                    ; done - examine Result

Test_unpack 
            LD R0,Value1            ; value to unpack
            JSR unpack              ; test unpack
            ST R0,Value1            ; save upper 8 bits
            ST R1,Value2            ; save lower 8 bits
            HALT                    ; done - examine Value1 and Value2

Test_printCC    
            LD R0,Value1            ; get the test value
            .ZERO R1                ; reset condition codes
            JSR printCC             ; print condition code
            HALT                    ; done - examine output

Test_strlen 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String1           ; load string pointer
            JSR strlen              ; calculate length
            ST R0,Result            ; save result
            HALT                    ; done - examine memory[Result]

Test_strcpy 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String2           ; R0 is dest
            LD R1,String1           ; R1 is src
            JSR strcpy              ; copy string
            PUTS                    ; print result of strcpy
            NEWLN                   ; add newline
            HALT                    ; done - examine output

Test_strcat 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcat              ; concatenate string
            PUTS                    ; print result of strcat
            NEWLN                   ; add newline
            HALT                    ; done - examine output

Test_strcmp 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcmp              ; compare strings
            JSR printCC             ; print result of strcmp
            HALT                    ; done - examine output

;------------------------------------------------------------------------------
; End of reserved section
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; on entry R0 contains first value, R1 contains second value
; on exit R0 = (R0 << 8) | (R1 & 0xFF)

pack        ; fill in your code, ~12 lines of code
             LD R0, value1
             LD R1, value2
             LD R4, lowerMask
             AND R3, R3, 0
             ADD R3, R3, #8
        Loop ADD R0, R0, R0
             ADD R3, R3, #-1
             Brp Loop
             AND R1, R1, R4
             ADD R0, R0, R1 
            RET

;------------------------------------------------------------------------------
; on entry R0 contains a value
; on exit R0 contains upper 8 bits, R1 contains lower 8 bits (see instructions
; for more details)

unpack      ; fill in your code, ~15 lines of code
            LD R0, value1
            LD R2, lowerMask
            AND R1, R0, R2      ;gets R1 value
            AND R4, R4, 0       ;counter
    Loop2   ADD R4, R4, #1
            ADD R0, R0, #-4
            Brp Loop2          ;Counter determines how many times need to right shift, count is 2 shift
            AND R0, R2, R4 
    
            
            RET

;------------------------------------------------------------------------------
; on entry R0 contains value
; on exit "NEGATIVE/ZERO/POSITIVE" printed, followed by newline (see
; instructions for more details)

StringNEG   .STRINGZ "NEGATIVE\n"   ; output strings
StringZERO  .STRINGZ "ZERO\n"
StringPOS   .STRINGZ "POSITIVE\n"

printCC    ; fill in your code, ~12 lines of code
			.SETCC R0
			Brp positive
			Brn negative
			Brz zero
StringLine  PUTS
			RET 
positive	LEA R0, StringPos
			Brnzp StringLine
negative 	LEA R0, StringNEG
			Brnzp StringLine
zero		LEA R0, StringZERO
			Brnzp StringLine
			
			RET

;------------------------------------------------------------------------------
; size_t strlen(char *s)
; on entry R0 contains pointer to string
; on exit R0 contains length of string (see instructions for more details)

strlen      ; fill in your code, ~8 lines of code
            .COPY R1, R0
            .ZERO R0
    Loop4    LDR R2, R1, #0
            Brz Done
            ADD R1, R1, #1
            ADD R0, R0, #1
            Brnp Loop4
    Done    RET    
    
        

;------------------------------------------------------------------------------
; char *strcpy(char *dest, char *src)
; on entry R0 contains dest, R1 contains src
; on exit  R0 contains dest (see instructions for more details)

strcpy      ; fill in your code, ~9 lines of code
            .ZERO R2
            .ZERO R3
            .COPY R2, R0
            
    Loop5   LDR R3, R1, #0      ;the character
            Brz Done2
            STR R3, R0, #0      ;Store R3 into R0        
            ADD R0, R0, #1
            ADD R1, R1, #1
            Br Loop5

    Done2  STR R3, R0, #0
			
            RET 
            

;------------------------------------------------------------------------------
; char *strcat(char *dest, char *src)
; on entry R0 contains dest, R1 contains src
; on exit R0 contains dest (see instructions for more details)

strcat_RA   .BLKW 1                 ; space for return address
strcat_dest .BLKW 1                 ; space for dest
strcat_src  .BLKW 1                 ; space for src

strcat      ST R7,strcat_RA         ; save return address
            ST R0,strcat_dest       ; save dest
            ST R1,strcat_src        ; save src

            ; fill in your code, ~5 lines of code
            ; HINT: call strlen and strcpy
            JSR strlen
			LD R1, strcat_dest
			ADD R0, R0, R1			;Gets address to start copy
			LD R1, strcat_src
			JSR strcpy
			

            LD R0,strcat_dest       ; restore dest
            LD R7,strcat_RA         ; restore return address
            RET

;------------------------------------------------------------------------------
; int strcmp(char *s1, char *s2)
; on entry R0 contains s1, R1 contains s2
; on exit R0 contains the result of the comparison (see instructions for more
; details)

strcmp      ; fill in your code, ~13 lines of code
    Loop6   LDR R2, R0, #0               ;Points to first character in string1
            LDR R3, R1, #0               ;Points to first character in string2
            
            ADD R4, R2, R3
            Brz Store1                   ;If both characters are null
            NOT R3, R3                  ;Getting two's comp of String2
            ADD R3, R3, #1              ;Getting two's comp of String2
            ADD R2, R2, R3              ;Subtract string2 from string1
            Brnp Store1                 ;If positive or negative go to store branch
            ADD R0, R0, #1              ;Increment to next character in R0
            ADD R1, R1, #1              ;Increment to next character in R1
            .SETCC R2                   ;Set condition code to R2
            Brz Loop6                   ;If zero loop through again
  
  Store1   .COPY R0, R2                 ;Store result 
  
            RET

;------------------------------------------------------------------------------
                .END


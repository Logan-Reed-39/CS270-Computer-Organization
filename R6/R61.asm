        .ORIG x3000
    
        BR Main
    
Result  .BLKW 1         ;Storing the result
Counter .FILL #5        ;Counter init

Main    LD R0, Counter

Loop    ST R0, Result
        ADD R0, R0, #-1 ;Reduce the counter every loop
        BRp Loop ;As long as the result of the previous instruction is positive, go through loop
        HALT

        .END

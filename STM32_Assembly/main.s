    AREA StartAssembly, CODE, READONLY
    ENTRY
    EXPORT __main

__main
    LDR R0, =1       ; Load immediate value 1 into register R0
    LDR R1, =2       ; Load immediate value 2 into register R1

    ADD R3, R0, R1   ; Add the values in R0 and R1, store the result in R3

STOP    B STOP       ; Infinite loop

    end

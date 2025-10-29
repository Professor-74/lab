DATA SEGMENT
    MSG1 DB 0AH,0DH,"Enter the string:$"
    MSG2 DB 0AH,0DH,"String is Palindrome$"
    MSG3 DB 0AH,0DH,"String is not Palindrome$"
    MSG4 DB 0AH,0DH,"Length of the string is: $"
    STR1 DB 50 DUP(0)
DATA ENDS 

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX


    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA SI, STR1
    LEA DI, STR1
    MOV AH, 01H      
    XOR CX, CX   

NEXT:
    INT 21H           
    CMP AL, 0DH       
    JE TERMINATE
    MOV [DI], AL
    INC DI
    INC CX           
    JMP NEXT

TERMINATE:
    MOV AL, '$'
    MOV [DI], AL      
    DEC DI              


    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

    MOV AX, CX         
    CALL PRINT_NUM     


    LEA SI, STR1      


CHECK_LOOP:
    MOV AL, [SI]
    CMP AL, [DI]
    JNE NOTPALINDROME
    INC SI
    DEC DI
    CMP SI, DI
    JLE CHECK_LOOP

PALINDROME:
    MOV AH, 09H
    LEA DX, MSG2
    INT 21H
    JMP EXIT

NOTPALINDROME:
    MOV AH, 09H
    LEA DX, MSG3
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H 

PRINT_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    XOR CX, CX       
    MOV BX, 10

NEXT_DIGIT:
    XOR DX, DX
    DIV BX         
    PUSH DX           
    INC CX
    CMP AX, 0
    JNE NEXT_DIGIT

PRINT_LOOP:
    POP DX
    ADD DL, 30H       
    MOV AH, 02H
    INT 21H
    LOOP PRINT_LOOP

    POP DX
    POP CX
    POP BX
    POP AX
    RET
PRINT_NUM ENDP

CODE ENDS
END START

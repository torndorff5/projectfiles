A1 .INT 1
A2 .INT 2
A3 .INT 3
A4 .INT 4
A5 .INT 5
A6 .INT 6
ARESULT .INT 0
B1 .INT 300
B2 .INT 150
B3 .INT 50
B4 .INT 20
B5 .INT 10
B6 .INT 5
BRESULT .INT 0
C1 .INT 500
C2 .INT 2
C3 .INT 5
C4 .INT 10
T .BYT 'T'
A .BYT 'A'
N .BYT 'N'
E .BYT 'E'
R .BYT 'R'
O .BYT 'O'
D .BYT 'D'
F .BYT 'F'
COM .BYT ','
SPACE .BYT 32
NL .BYT 10
START   LDB R3, O       ;the start of the program
        TRP 3           ; load my last name and print
        LDB R3, R
        TRP 3
        LDB R3, N
        TRP 3
        LDB R3, D
        TRP 3
        LDB R3, O
        TRP 3
        LDB R3, R
        TRP 3
        LDB R3, F
        TRP 3
        TRP 3
        LDB R3, COM
        TRP 3
        LDB R3, SPACE
        TRP 3
        LDB R3, T       ; load my first name and print
        TRP 3
        LDB R3, A
        TRP 3
        LDB R3, N
        TRP 3
        TRP 3
        LDB R3, E
        TRP 3
        LDB R3, R
        TRP 3
        LDB R3, NL
        TRP 3
        LDR R1, B1      ; add up all the b variables
        LDR R2, B2
        ADD R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, B3
        ADD R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, B4
        ADD R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, B5
        ADD R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, B6
        ADD R1, R2
        MOV R3, R1
        TRP 1
        STR R3, BRESULT ; store result to be used later
        LDB R3, NL
        TRP 3
        LDR R1, A1      ; multiply all the A variables
        LDR R2, A2
        MUL R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, A3
        MUL R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, A4
        MUL R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, A5
        MUL R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R2, A6
        MUL R1, R2
        MOV R3, R1
        TRP 1
        STR R3, ARESULT     ; store result to be used later
        LDB R3, NL
        TRP 3
        LDR R1, BRESULT     ; pull in b result and divde each member of b
        LDR R2, B1
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3 SPACE
        TRP 3
        TRP 3
        LDR R1, BRESULT
        LDR R2, B2
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3 SPACE
        TRP 3
        TRP 3
        LDR R1, BRESULT
        LDR R2, B3
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3 SPACE
        TRP 3
        TRP 3
        LDR R1, BRESULT
        LDR R2, B4
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R1, BRESULT
        LDR R2, B5
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R1, BRESULT
        LDR R2, B6
        DIV R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDB R3, NL
        TRP 3
        LDR R1, ARESULT     ; load Aresult and subtract each memeber of c from it
        LDR R2, C1
        SUB R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R1, ARESULT
        LDR R2, C2
        SUB R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R1, ARESULT
        LDR R2, C3
        SUB R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDR R1, ARESULT
        LDR R2, C4
        SUB R1, R2
        MOV R3, R1
        TRP 1
        LDB R3, SPACE
        TRP 3
        TRP 3
        LDB R3, NL
        TRP 3
; int SIZE = 10;
; int ARR[] = { 10, 2, 3, 4, 15, -6, 7, 8, 9, 10 };
; int i = 0;
; int sum = 0;
; int temp;
; int result;
; while (i < SIZE) {
;   sum += ARR[i];
;   result = ARR[i] % 2; \\ Do this using simple algebra
;   if (result == 0)
;       printf("%d is even\n", ARR[i]);
;   else
;       printf("%d is odd\n", ARR[i]);
;   i++;
; }
;   printf("Sum is %d\n", sum);
;
; place dags into gads
; place g into d spot
; place d into g spot
; char rel;
; for (i = 0; i < 4; i++) {
; if (DAGS[i] < GADS[i]) rel = ‘<’;
; else if (DAGS[i] > GADS[i]) rel = ‘>’
; else rel = ‘=’;
; printf("%c %c %c--", DAGS[i], rel, GADS[i]);
; }






SIZE .INT 10
SIZE2 .INT 4
ARR .INT 10, 2, 3, 4, 15, -6, 7, 8, 9, 10
I .INT 0
SUM .INT 0
TEMP .INT 0
RESULT .INT 0
INTEGER .INT 4
BYTE .INT 1
EVEN .INT 2
DAGS .BYT 'D'
.BYT 'A'
.BYT 'G'
.BYT 'S'
GADS .INT -99
LT .BYT '<'
GT .BYT '>'
EQ .BYT '='
REL .BYT '>'
DASH .BYT '-'
S .BYT 'S'
u .BYT 'u'
m .BYT 'm'
SPACE .BYT 32
i .BYT 'i'
s .BYT 's'
e .BYT 'e'
v .BYT 'v'
n .BYT 'n'
o .BYT 'o'
d .BYT 'd'
NL .BYT 10
WHILE       LDR R1, I
LDR R2, SIZE
CMP R1, R2
BRZ R1, ENDWHILE
LDR R1, SUM
LDA R2, ARR         ; Put array address into r9
LDR R3, I           ; Put index value into r3
LDR R4, INTEGER
MUL R3, R4
ADD R2, R3          ; add index value to address to get specifc array value
LDR R6, R2
ADD R1, R6
STR R1, SUM
STR R6, RESULT
LDR R7, EVEN        ; see if current value is even or odd
DIV R6, R7
MUL R6, R7
LDR R7, RESULT      ; See if r6 is equal to result
CMP R6, R7
BNZ R6, ELSE
MOV R3, R7          ; Print out even
TRP 1
LDB R3, SPACE
TRP 3
LDB R3, i
TRP 3
LDB R3, s
TRP 3
LDB R3, SPACE
TRP 3
LDB R3, e
TRP 3
LDB R3, v
TRP 3
LDB R3, e
TRP 3
LDB R3, n
TRP 3
LDB R3, NL
TRP 3
JMP ENDELSE
ELSE        MOV R3, R7          ; Print out odd
TRP 1
LDB R3, SPACE
TRP 3
LDB R3, i
TRP 3
LDB R3, s
TRP 3
LDB R3, SPACE
TRP 3
LDB R3, o
TRP 3
LDB R3, d
TRP 3
TRP 3
LDB R3, NL
TRP 3
ENDELSE     LDR R3, I           ; Increment I
ADI R3, 1
STR R3, I
JMP WHILE
ENDWHILE    MOV R3, R2
LDB R3, S
TRP 3
LDB R3, u
TRP 3
LDB R3, m
TRP 3
LDB R3, SPACE
TRP 3
LDB R3, i
TRP 3
LDB R3, s
TRP 3
LDB R3, SPACE
TRP 3
LDR R3, SUM
TRP 1
LDB R3, NL
TRP 3
TRP 3               ; End of Part 1 ****************************************
LDR R1, DAGS
STR R1, GADS
LDA R1, DAGS       ; Load address of DAGS into R1
ADI R1, 2
LDB R3, R1          ; load single byte located at adresss + offset (R1)
LDA R4, GADS
STB R3, R4          ; Store 'G' located in R3 into the first byte of GADS
LDB R1, DAGS        ; Get 'D' and put it in the third byte of GADS
ADI R4, 2
STB R1, R4
LDR R1, I           ; Set I back to 0
LDR R2, I
SUB R1, R2
STR R1, I
WHILE2      LDR R1, I
LDR R2, SIZE2     ; (4, the size of the words)
CMP R1, R2
BRZ R1, ENDWHILE2   ; WHile i is not equal to 4
LDA R4, DAGS
LDA R5, GADS
LDR R6, I
ADD R4, R6
ADD R5, R6
LDB R1, R4
LDB R2, R5
CMP R1, R2
BRZ R1, ELSE3
BGT R1, ELSE2
LDB R1, LT
STB R1, REL
JMP ENDELSE2
ELSE2       LDB R1, GT
STB R1, REL
JMP ENDELSE2
ELSE3       LDB R1, EQ
STB R1, REL
ENDELSE2    LDB R3, R4
TRP 3
LDB R3, SPACE
TRP 3
LDB R3, REL
TRP 3
LDB R3, SPACE
TRP 3
LDB R3, R5
TRP 3
LDB R3, DASH
TRP 3
TRP 3
LDR R3, I           ; Increment I
ADI R3, 1
STR R3, I
JMP WHILE2
ENDWHILE2   LDB R3, NL
TRP 3
TRP 3
LDR R1, DAGS
MOV R3, R1
TRP 1
LDB R3, SPACE
TRP 3
LDB R3, DASH
TRP 3
LDB R3, SPACE
TRP 3
LDR R2, GADS
MOV R3, R2
TRP 1
LDB R3, SPACE
TRP 3
LDB R3, EQ
TRP 3
LDB R3, SPACE
TRP 3
SUB R1, R2
MOV R3, R1
TRP 1
LDB R3, NL
TRP 3
TRP 0


clc
%Problem A
m = [2,-2,-1
    4,1,-2
    -2,1,-1];
x = [-1
    1
    -3];
y = gaussian(x,m,3)
%Problem B
m = [1,2,-1
    0,3,1
    2,-1,1];
x = [2
    4
    2];
y = gaussian(x,m,3)
%Problem c 
m = [2,1,-4
    1,-1,1
    -1,3,-2];
x = [-7
    -2
    6];
y = gaussian(x,m,3)
clc
%Exercise 2.2 1
A = [3,1,2
    6,3,4
    3,1,5];
[l,u]=LU(A,3)


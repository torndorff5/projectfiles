%2.24
n= [3,-1,0,0,0,.5
    -1,3,-1,0,.5,0
    0,-1,3,-1,0,0
    0,0,-1,3,-1,0
    0,.5,0,-1,3,-1
    .5,0,0,0,-1,3];
[a,b] = sparsesetup(n);
x = gausseidel(a,b,5);


func =@(x,v) x^3 - v^3 + x;
x0 = [1,1];
newtmult(func,x0)
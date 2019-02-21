clc
f=@(x) x^5+x-1;

xc = round(bisect(f,0,1,.0000000005),8)

f=@(x) (6*x) + 5 - sin(x);

xc = round(bisect(f,-1,0,.0000000005),8)

f=@(x) log(x) + x^2 - 3;

xc = round(bisect(f,1,2,.0000000005),8)

g=@(x) ((2*x) + 2)^(1/3) ;

xc = round(fpi(g,1/2,20),8)

g=@(x) log(7-x) ;

xc = round(fpi(g,1/2,20),8)

g=@(x) log(4-sin(x)) ;

xc = round(fpi(g,1/2,20),8)
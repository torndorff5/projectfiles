clc
%Computer Problem 1.3, 1 
Xa1 = fzero('sin(x)-x',.1)
FE1 = abs(0 - fzero('sin(x)-x',.1))
BE1 = sin(Xa) - Xa
%Computer Problem 1.3, 3a
rootA = fzero('(2*x)*cos(x)-(2*x)+sin(x.^3)',[-.1,.2])
FE3 = abs(0 - fzero('(2*x)*cos(x)-(2*x)+sin(x.^3)',[-.1,.2]))
BE3 = (2*rootA)*cos(rootA)-(2*rootA)+sin(rootA.^3)
%%Computer Problem 1.3, 3b
BM3 = bisect(@(x) (2*x)*cos(x)-(2*x)+sin(x.^3), -.1,.2,.00001)
%Computer Problem 1.4, 1a 
NEW = newtons(@(x) exp(x) + sin(x) - 4, @(x) exp(x) - cos(x), 1,8)
%computer Problem 1.5, 1
SecA = secantm(@(x) -x^3 + (2*x) + 2,1,2)
SecB = secantm(@(x) exp(x) + x - 7, 1, 2)
SecC = secantm(@(x) exp(x) + sin(x) - 4, 1, 2)

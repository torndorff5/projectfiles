%Program 1.5 Secant method 
function x=secantm(f,xa,xi)
for i = 0:5
    temp = xi;
    xi=xi-((f(xi)*(xi-xa))/(f(xi)-f(xa)));
    xa = temp;
end
format long
x = xi;
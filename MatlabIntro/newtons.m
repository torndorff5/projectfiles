%Program 1.4 Newton Method
function x=newtons(f,fp,xi,iter)
for i=0:iter
    xi=xi-(f(xi)/fp(xi));
end
format long
x = xi;
x = round(x,8);
    

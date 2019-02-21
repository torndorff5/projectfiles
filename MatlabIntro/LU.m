function [l,u]=LU(A,r)
%A is input matrix and r is row number 
u=A;
for j = 1: r-1
    for i = j+1 : r
        u(i,j) = 0;
    end
end
l=A;
for j =1: r-1
    if abs(l(j,j))<eps 
        error('zero pivot encountered') 
    end
    for i = j+1: r
        mult = l(i,j)/l(j,j);
        for k = j+1:r
            l(i,k) = l(i,k) - mult*l(j,k);
        end
    end  
end
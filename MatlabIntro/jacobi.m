function x = jacobi(a,b,k)
n = length(b);
d=diag(a);
r=a-diag(d);
x=zeros(n,1);
for j=1:k
    x = (b-r*x)./d;
end
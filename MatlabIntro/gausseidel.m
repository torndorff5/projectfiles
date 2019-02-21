function x = gaussseidel(a,b,k)
n=length(b);         % find n
d=diag(diag(a)); u=triu(a,1);l=tril(a,-1);
x=zeros(n,1);        % Initialize vector x
for j=1:k            % loop for GS iteration
  b1=b-u*x;
  for i=1:n
      x(i)=(b1(i)-l(i,:)*x)/d(i,i);
  end
end
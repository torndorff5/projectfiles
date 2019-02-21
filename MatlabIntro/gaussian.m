function x=gaussian(b,m,r)
%m is a matrix representing a system and x a matrix with the answers 
%r is the number of rows in the matrix 
for j = 1: r-1
    for i = j+1 : r
        m(i,j) = 0;
    end
end
x = zeros(1,r);
for j =1: r-1
    if abs(m(j,j))<eps 
        error('zero pivot encountered') 
    end
    for i = j+1: r
        mult = m(i,j)/m(j,j);
        for k = j+1:r
            m(i,k) = m(i,k) - mult*m(j,k);
        end
        b(i) = b(i) - mult*b(j);
    end  
end
for i = r: -1 : 1
    for j = i+1:r
        b(i) = b(i) - m(i,j) * b(j);
    end
    b(i)=b(i)/m(i,i);
        
end
x=b;
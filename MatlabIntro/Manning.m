function [B] = Manning(A)
%UNTITLED4 Summary of this function goes here
%   Input A is a matrix where is column is a parameter and each
%   row is a channel. The output is a matrix that adds a 5th column
%   that includes a calculated velocity. 
U = @(x) (sqrt(x(2))/x(1))*(x(3)*x(4)/(x(3)+2*x(4)))^(2/3);

C = [];
    for r = 1:5
        x = U(A(r,:));
        C = [C x];
    end
C = C';
B = [A C];
end


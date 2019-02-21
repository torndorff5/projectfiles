% ProgrammingWithMatLab: UVU 2019Spring/MatlabIntro/ProgrammingWithMatLab.m

clc

x=3  % to demonstrate where we are in the script

freefall(12,68.1,0.25)

pause

help freefall

pause

lookfor bungee

pause

% anonymous functions

% functionHandle = @(arglist) expression

f1 = @(x,y) x^2 + y^2;

f1(3,4)

pause

f2 = @(x) exp(sin(x*pi))

% function functions
fplot(f2,[1 4])

pause

f3 = @(m)freefall(12,m,0.25) % this is poor technique -- see warnings
fplot(f3,[.1,100])
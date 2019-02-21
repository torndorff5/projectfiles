% MatLab Fundamentals: UVU 2019Spring/MatlabIntro/MatLabFuntamnentals.m
clc % clear command window

% You may use MatLab as a calculator, but most users realize, that 
% scripts are a better choice.

% MatLab has two types of scripts 'called M-files'

%--- 1. Script files -- this is an example of a script file
%
%       a series of MatLab commands that are saved in a file
%
%--- 2. Function files -- we explore these later
%
%       start with the word 'function' and accept input arguments
%       and return outputs.
%
%       simular to user defined functions in C#, C++, Java, python , etc
pause

56 - 33 % use MatLab as a calculator

pause

% assignment
a=4,A=6;x=1 % ; suppresses printing

pause

format long
pi
format
pi

pause

a=[1 2 3 4 5]
b= 2*a'

pause

% most matlab operations are 'vector' operations
% use a dot to make them 'element by element' operations

a*b % vector inner product or 'dot' product
a.*b % element by element product

pause

b*a

b.*a

pause
%a^b  % causes error must be commented out to continue
a.^b

pause

A = [1 2 3; 4 5 6; 7 8 9]
A(3,3)
A(2,1)

pause

% colon operator
t = 1:5
t = 1:0.03:5
t = 5:-.33:1

pause

% linspace
linspace(1,5)  % generates 100 data points
linspace(1,5,6) % generates 6 data points
pause
% logspace generates logariathimally equally spaced points
logspace(1,5) % generates 50 data points
logspace(1,5,6) % generates 6 data points
format long
logspace(-1,5,6) % generates 6 data points
format
pause

% continuation ... ellipsis at end of line -- can't be used inside of
% a string but can be between 2 strings being concatenated.


% strings concatenate with a space eg,
x = ['fish' ...
    ' or fowl']

pause

% create vectors t and v chapra pp 41-42 (time and velocity)
t = [0:2:20] % time in seconds

g=9.81; m =68.1; cd = 0.25; % constants for velocity formula
v= sqrt(g*m/cd)*tanh(sqrt(g*cd/m)*t)

% plot v versus t
pause

plot(t,v,'*')

title('Plot of velocity versus time')
xlabel("Time (seconds)")
ylabel("Velocity(meters/second)")
grid


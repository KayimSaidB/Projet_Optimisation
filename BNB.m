function [X,S] = BNB(fun,x0,a,b,c,B,lb,ub,nonlcon)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

X = [];
S = 0;

xstatue = zeros(size(x0));
S = fun(x0);

%1er Relaxation

[x,z,exitflag] = fmincon(fun,x0,a,b,B,lb,ub,nonlcon);

for i=1:size(x)
    if isnumeric(x(i))
        xstatue(i)=1;
    end
end

K = find(min(x) & xstatue==1);

if exitflag > 0 && all(xstatue)
    X=x;
    S=z;
    disp('Solution Valeur entiere');
    disp('x =',X);
    disp('S=',S);
    %break le while

elseif S>z && exitflag >0
    S = z;
    
    %Cas x(K) = 0
    x1=x0;
    x1(K)=0;
    
    %Cas x(K) = 1
    x2=x0;
    x2(K)=1;
    
    
    
end






end


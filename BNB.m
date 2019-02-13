function [X,S,x] = BNB(fun,x0,lb,ub,nonlcon)
%UNTITLED3 Summary of this funn goes here
%   Detailed explanation goes here

X = [];
S = 0;

xstatue = zeros(size(x0));
S = fun(x0);

%1er Relaxation

[x,z,exitflag] = fmincon(fun,zeros(15,1),[],[],[],[],lb,ub,nonlcon);

for i=1:size(x)
    if isinteger(x(i))
        xstatue(i)=1;
        g=5
    end
end
    Aeq=zeros(length(x0));
    beq=zeros(length(x0),1);
%while(all(xstatue)==0)    
%K = find(min(x) & xstatue==0);
min=1000
indice=1
n=length(x)
for i=1:n
   if( min>x(i) & xstatue(i)==0 & x(i)>0.1)
       min=x(i)
       indice=i
   end
end
K=indice;
if exitflag > 0 && all(xstatue)
    X=x;
    S=z;
   
else %Cas x(K) = 0 arrondi inf
    K
    Aeq(K,K)=1;
    beq(K)=round(min);
    [X,z,exitflag] = fmincon(@mafonction,zeros(15,1),[],[],Aeq',beq,lb,ub,@contrainte);
    %Cas x(K) = 1 arrondi sup
    
    
    
end




%end

end

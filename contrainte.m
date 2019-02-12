function [con,ceq]=contrainte(x)
 b =         [4.852;
             0.269;
             7.663;
             8.293;
             1.355;
            19.863;
             9.686;
            15.307;
             0.637;
            0.619;
           18.653;
           17.758;
         11.827;
          9.576;
          16.667];
 c =  [1.780;
             2.603;
             1.673;
             2.548;
             2.033;
             2.457;
             2.862;
             1.941;
             1.897;
            2.066;
            2.312;
            1.514;
            2.999;
            1.519;
            2.764];
        n=length(c);
        con=0;
        for i=1:1:n
            con=con+power(c(i),-x(i))*b(i);
        end
         B =     68291518464.0000;
        ceq=[]
        con =con-B
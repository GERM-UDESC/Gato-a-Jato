%dados do problema% 
sigma1=0;
Er1=9;
ur1=1;
uo=4*pi*1e-7;
u1=ur1*uo;
P=10;
f=10e6;
w= 2*pi*f;
Eo= 8.85e-12;
ur2=1;
z=1;
 
j=complex(0,1);
 
Z1=sqrt((j*w*ur1*uo)/(sigma1+j*w*Er1*Eo));% Impedância meio 2
 Z2=100 + j*20;
 %teta_i=teta_0=0;
 r=(Z2-Z1)/(Z2+Z1);
 t= 2*Z2/(Z2+Z1);
%P=0.5* abs(Ei)/(Z2)
 Ei=sqrt(2*P*Z2);
 E_i=abs(Ei);
 Hi= E_i/Z2;
 Et=t*Ei;
 Ht=t*Hi;
 
sigma2= real((j*w*uo)/(Z2^2));
Er2=imag((j*w*u1)/(Z2^2))/(w*Eo);
E2=Er2*Eo;
k2=sqrt(j*w*u1*(sigma2+j*w*E2));
alfa2=real(k2);
beta2=imag(k2);
Etfinal = abs(Et)*exp(-alfa2*z);
Htfinal=abs(Ht)*exp(-alfa2*z);

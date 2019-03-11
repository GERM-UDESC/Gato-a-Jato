close all
clear all
clc

%COLOCAR CARGA NO MOTOR

max_pwm = 3599;
Ts = 10e-3;
To = 2;
steps = 9; %but there is 2 seconds with 0

dados1 = importdata('hexdump.txt');
dados1 = dados1(1:(steps+1)*To/Ts)';

t1 = 0:1e-3:(length(dados1)-1)/1000; 

pwm1 = zeros(1,length(dados1));
for j = 0:steps
    for i = 1:To/Ts
        pwm1(i+To/Ts*j) = j*10;
    end   
end

delta = 0;
max_delta = 0;
    for i = 650:length(dados1)
    delta = dados1(i) - dados1(i-1);
    if (delta > max_delta)
        max_delta = delta;        
    end 
    
end
% pwm1 = [0.7*max_pwm*ones(1,To/Ts) 0.3*max_pwm*ones(1,To/Ts) 1.0*max_pwm*ones(1,To/Ts) 0.5*max_pwm*ones(1,To/Ts)];  
plot(t1, dados1, t1, pwm1)
hold on
scatter(t1, dados1)

%% 
% systemIdentification
% sisotool

%%
s = tf('s');

K = max_pwm/100+3.2;

M1 = K*18.13/(s + 20.1);      %esse veio do systemIdentification
% M2 = 568.3/(s + 16.2);
M2 = 570/(s + 16.2);
M3 = 1.156e5/((s + 17.86)*(s + 182.8));
M4 = 865.2/(s + 24.4);

KP1 = 4/(K*18.13*0.1);
KI1 = 20.1*KP1;

C1 = KP1*(s+KI1/KP1)/s;

T = feedback(C1*M1,1);

figure
plot(t1, dados1)
hold on
lsim(M1,'-c',M2,'--b',M3,'-.k',M4,'-.r', pwm1,t1)

%% 
% u(k) = erro(k)*C(k)
% erro(k) = ref(k) - y(k)

K = 865.2;
P = 24.4;

ts = 0.15; %tempo de assentamento
KP = 4/(K*ts);
KI = P*KP;

max_ref = 3000;
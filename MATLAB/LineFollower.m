close all
clear all
clc

%COLOCAR CARGA NO MOTOR

max_pwm = 3599;
Ts = 10e-3;
To = 2;
steps = 9; %but there is 2 seconds with 0

dados1 = importdata('hexdump.txt');
% dados1 = dados1(1:(steps+1)*To/Ts)';


%%
t1 = 0:1e-3:(length(dados1)-1)/1000; 

pwm1 = zeros(1,length(dados1));
for j = 0:steps
    for i = 1:To/Ts
        pwm1(i+To/Ts*j) = j*10;
    end   
end

delta = 0;
max_delta = 0;
for i = 2:length(dados1)
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

ref = [zeros(1,200) 2500*ones(1,200) 800*ones(1,200) 1500*ones(1,200) 500*ones(1,200) 2500*ones(1,200) 300*ones(1,200) 800*ones(1,200) zeros(1,200)]; 
dados1 = x;
t2 = 0:10e-3:(length(ref)-1)/100;

plot(t2,dados1,t2,ref)


%% 
% systemIdentification
% sisotool
%%
% K = 1014;
% P = 28.66;

% K = 570;
% P = 16.2;
s = tf('s');

K = 792.7;
P = 22.82;

ts = 0.15; %tempo de assentamento
KP = 4/(K*ts);
KI = P*KP;

max_ref = 3000;

Modelo = K/(s + P);

Controlador = KP*(s+KI/KP)/s;

T = feedback(Controlador*Modelo,1);

figure
plot(t2,dados1,t2,ref)
hold on
lsim(T,'-c', ref,t2)


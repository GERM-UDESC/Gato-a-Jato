close all
clear all
clc

number_of_steps = 9;
bits_to_receive = 50;
baud_rate = 1e6;
Ts = 10e-3;

seguidor = serial('com3','BaudRate',baud_rate,'Parity','none'); 
fopen(seguidor);
fwrite(seguidor, bits_to_receive/10, 'uint8');
fclose(seguidor);

%%
x = colect_data(0, bits_to_receive, baud_rate);
x = [x colect_data(1000, bits_to_receive, baud_rate)];
x = [x colect_data(2000, bits_to_receive, baud_rate)];
x = [x colect_data(1500, bits_to_receive, baud_rate)];
x = [x colect_data(1200, bits_to_receive, baud_rate)];
x = [x colect_data(2500, bits_to_receive, baud_rate)];
x = [x colect_data(1600, bits_to_receive, baud_rate)];
x = [x colect_data(1000, bits_to_receive, baud_rate)];
x = [x colect_data(2500, bits_to_receive, baud_rate)];
x = [x colect_data(0, bits_to_receive, baud_rate)];

ref = [zeros(1,bits_to_receive) 1000*ones(1,bits_to_receive) 2000*ones(1,bits_to_receive) 1500*ones(1,bits_to_receive) 1200*ones(1,bits_to_receive) 2500*ones(1,bits_to_receive) 1600*ones(1,bits_to_receive) 1000*ones(1,bits_to_receive) 2500*ones(1,bits_to_receive) zeros(1,bits_to_receive)]; 
t = 0:Ts:((length(ref)-1)/100);

simulink_ref = [t; ref]';

speed1 = x(1, :);
simulink_speed_ref1 = [t; speed1]';
u1 = 10*x(2, :);
simulink_u_ref1 = [t; u1]';

speed2 = x(3, :);
simulink_speed_ref2 = [t; speed2]';
u2 = 10*x(4, :);
simulink_u_ref2 = [t; u2]';

s = tf('s');

K = 792.7;
P = 22.82;

ts = 0.15; %tempo de assentamento
KP = 4/(K*ts);
KI = P*KP;

Modelo = K/(s + P);
Controlador = KP*(s+KI/KP)/s;

T = feedback(Controlador*Modelo,1);  % Malha fechada

figure
plot(t,speed1,'b', t,u1,'b', t,ref,'-k')
hold on
plot(t,speed2,'r', t,u2,'r')
lsim(T,':c', ref,t)

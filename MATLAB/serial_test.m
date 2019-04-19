close all
clear all
clc

bits_to_receive = 2500;
baud_rate = 250e3;
Ts = 1e-3;
% rpmToV = 596.83;

seguidor = serial('com3','BaudRate',baud_rate,'Parity','none', 'InputBufferSize', 15000); 
fopen(seguidor);
fwrite(seguidor, bits_to_receive/10, 'uint8');
fclose(seguidor);

%%
x = colect_data(0, bits_to_receive, baud_rate);
x = [x colect_data(10, bits_to_receive, baud_rate)];
x = [x colect_data(20, bits_to_receive, baud_rate)];
x = [x colect_data(30, bits_to_receive, baud_rate)];
x = [x colect_data(40, bits_to_receive, baud_rate)];
x = [x colect_data(50, bits_to_receive, baud_rate)];
x = [x colect_data(60, bits_to_receive, baud_rate)];
x = [x colect_data(70, bits_to_receive, baud_rate)];
x = [x colect_data(80, bits_to_receive, baud_rate)];
x = [x colect_data(90, bits_to_receive, baud_rate)];
x = [x colect_data(0, bits_to_receive, baud_rate)];

ref = x(1, :);
speed1 = x(2, :);
speed2 = x(3, :);
save('ref')
save('speed1')
%%

t = 0:Ts:((length(ref)-1)*Ts);

simulink_ref = [t; ref]';

simulink_speed_ref1 = [t; speed1]';
u1 = 10*x(3, :);
simulink_u_ref1 = [t; u1]';

% speed2 = x(4, :);
% simulink_speed_ref2 = [t; speed2]';
% u2 = 10*x(5, :);
% simulink_u_ref2 = [t; u2]';

%% 
s = tf('s');

% sem roda
% K = 792.7; 
% P = 22.82;

% com roda
K = 455.5;
P = 12.97;

ts = 0.2; %tempo de assentamento
KP = 4/(K*ts);
KI = P*KP;

Modelo = K/(s + P);
Controlador = KP*(s+KI/KP)/s;

T = feedback(Controlador*Modelo,1);  % Malha fechada

for i = 1: length(u1)-1
    u1(i+1) = u1(i+1) - u1(1);
    u1(i+1) = u1(i+1)/1e6;
end
u1 = u1(1, 2:length(u1));
speed1 = speed1(1, 2:length(speed1));
ref = ref(1, 2:length(ref));
t = t(1, 2:length(t));

figure
plot(t,speed1,'b', t,ref,'-k')
hold on
% plot(t,speed2,'r', t,u2,'r')
lsim(T,':c', ref,t)

%%

speed1 = x(2, :);
speed1 = speed1(1,1000:16000);
figure
plot(speed1)


figure
periodogram(speed1)
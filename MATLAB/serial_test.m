close all
clear all
clc

bits_to_receive = 2500;
baud_rate = 1e6;
Ts = 1e-3;

seguidor = serial('com3','BaudRate',baud_rate,'Parity','none', 'InputBufferSize', 25000); 
fopen(seguidor);

flushinput(seguidor);
fwrite(seguidor, 0, 'uint8');
temp = fread(seguidor, 5000,'float');
dados = [temp(1:2:length(temp))'; temp(2:2:length(temp))'];
for i = 1:12
    flushinput(seguidor);
    fwrite(seguidor, 5*i, 'uint8');
    temp = fread(seguidor, 5000,'float');
    dados = [dados(1,:) temp(1:2:length(temp))'; dados(2,:) temp(2:2:length(temp))'];
end
flushinput(seguidor);
fwrite(seguidor, 0, 'uint8');
temp = fread(seguidor, 5000,'float');
dados = [dados(1,:) temp(1:2:length(temp))'; dados(2,:) temp(2:2:length(temp))'];

fclose(seguidor);

ref = dados(1, :);
speed1 = dados(2, :);
save('refw')
save('speedw')
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

% sem roda
% K = 792.7; 
% P = 22.82;

% com roda
K = 455.5;
P = 12.97;

ts = 0.2; %tempo de assentamento
KP = 4/(K*ts);
KI = P*KP;

s = tf('s');
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

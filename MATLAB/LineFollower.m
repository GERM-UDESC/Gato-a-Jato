close all
clear all
clc

% systemIdentification
% sisotool

load('malhaA.txt');
ref = malhaA(:,1);
RPM = malhaA(:,2);
t = 0:1e-3:((length(ref)/1000) - 1e-3);
input_simulink = [t' ref];
data_to_simulink = [t' RPM];

%% Dados do robô
Ts = 1e-3;
r = 16e-3;      % Raio da roda
l = 69e-3;      % Distância do centro do robô até o centro das rodas

s = tf('s');
%% Controlador de velocidade dos motores
% Modelo do motor com roda
% Km = 455.5;
Km = 460;
Pm = 12.97;

Modelo = Km/(s + Pm);

% Parâmetros do controlador
ts_m = 0.15; %tempo de assentamento
KPm = 4/(Km*ts_m);
KIm = Pm*KPm;

Controlador = KPm*(s+KIm/KPm)/s;

Tm = feedback(Modelo*Controlador, 1);

%% Controlador Kanayama
% Referência de velocidades
v_r = 1.5;
w_r = 0;
Qr = [v_r; w_r];

% determinação das constantes
% Kx
Ts_x = 0.05;
Kx = 4/Ts_x;

% Ky e Kteta
Ts_y_teta = 0.1;
qsi = 1;
wn = 4/(qsi*Ts_y_teta);
Tp = pi/(wn*sqrt(1-qsi^2));

Ky = (wn/v_r)^2;
Kteta = 2*qsi*sqrt(Ky);
% Kteta = 2*sqrt(Ky);

%% Plot
close all
clc

figure
subplot(2,1,1)
plot(t,ref)
legend('Razão Cíclica - PWM(%)');
ylabel('Entrada');
xlabel('Tempo');
axis([0 11 -1 110]);
subplot(2,1,2)
plot(t,RPM,t,resp_modelo(1:11000,1))
legend('Resposta experimental', 'Resposta simulada');
ylabel('Velocidade Angular (RPM)');
xlabel('Tempo');
close all
clear all
clc

% systemIdentification
% sisotool

%% Dados do robô
r = 16e-3;      % Raio da roda
l = 69e-3;      % Distância do centro do robô até o centro das rodas

s = tf('s');
%% Controlador de velocidade dos motores
% Modelo do motor com roda
Km = 455.5;
Pm = 12.97;

Modelo = Km/(s + Pm);

% Parâmetros do controlador
ts_m = 0.15; %tempo de assentamento
KPm = 4/(Km*ts_m);
KIm = Pm*KPm;

Controlador = KPm*(s+KIm/KPm)/s;

Tm = feedback(Modelo*Controlador, 1);

%% Controlador de angulo
% Modelo da resposta a entrada de velocidade angular
Kw = 24.86;
Pw = 24.89;

Modelo_w = Kw/(s + Pw);

% Parâmetros do controlador
ts_w = 0.05; %tempo de assentamento
KDw = 4/(Kw*ts_w);
KPw = Pw*KDw;

Controlador_w = KDw*(s+KPw/KDw);

Tw = feedback(Modelo_w*Controlador_w, 1);

%% Controlador Kanayama
% Referência de velocidades
v_r = 1;
w_r = 0;
Qr = [v_r; w_r];

% determinação das constantes
% Kx
Ts_x = 0.05;
Kx = 4/Ts_x;

% Ky e Kteta
Ts_y_teta = 0.05;
qsi = 1;
wn = 4/(qsi*Ts_y_teta);
Tp = pi/(wn*sqrt(1-qsi^2));

Ky = (wn/v_r)^2;
Kteta = 2*qsi*sqrt(Ky);
% Kteta = 2*sqrt(Ky);















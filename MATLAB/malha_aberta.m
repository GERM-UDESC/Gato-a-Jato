close all
% clear all
clc

% systemIdentification
% sisotool

load('malhaAbertaModelo.txt');
ref = malhaAbertaModelo(:,1);
RPM = malhaAbertaModelo(:,2);
t = 0:1e-3:((length(ref)/1000) - 1e-3);
input_simulink = [t' ref];
data_to_simulink = [t' RPM];

%% Dados do robô
Ts = 1e-3;
r = 16e-3;      % Raio da roda
l = 69e-3;      % Distância do centro do robô até o centro das rodas

s = tf('s');

% Modelo do motor com roda
Km = 455.5;
% Km = 460;
Pm = 12.97;

Modelo = Km/(s + Pm);

%% Plot
close all
clc

%deverá ser aberto o arquivo malha_aberta do simulink para obter os dados
%resp_modelo

figure
% subplot(2,1,1)
% plot(t,ref)
% legend('Razão Cíclica - PWM(%)');
% ylabel('Entrada');
% xlabel('Tempo');
% axis([0 11 -1 110]);
% subplot(2,1,2)
plot(t,RPM,t,resp_modelo(1:11000,1))
legend('Resposta experimental', 'Resposta simulada');
ylabel('Velocidade Angular (RPM)');
xlabel('Tempo');
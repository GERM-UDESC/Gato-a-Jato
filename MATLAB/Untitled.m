close all
clear all
clc

bits_to_receive = 2500;
baud_rate = 1382400;
Ts = 1e-3;

teste1 = linspace(0, 1500, bits_to_receive);
teste2 = linspace(1500, 0, bits_to_receive);

t = 0:Ts:((bits_to_receive-1)*Ts);

% data = [temp(1:2:length(temp))'; temp(2:2:length(temp))'];

figure
subplot(2,1,1)
plot(t,teste1,'b-');
hold on
subplot(2,1,2)
plot(t,teste2,'k-.');
subplot(2,1,1)
legend('Velocidade Linear / Motor esquerdo','Velocidade Angular / Motor direito');
% ylabel('Velocidade (m/s, rad/s, rpm)');
ylabel({'Velocidade Linear (m/s)';'Velocidade Angular (rad/s)';'Velocidade Motor (RPM)'});
xlabel('Tempo');

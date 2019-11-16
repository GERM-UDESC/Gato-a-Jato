close all
clear all
clc

erro = load('erros1art.txt');
n = 10;
Ts = 1e-3;
t = 0:Ts:((length(erro(:,2))-1)*Ts);
erro(:,2) = filter(ones(1,n), n, erro(:,2));

figure
subplot(2,1,1)
plot(t,erro(:,1));
subplot(2,1,2)
plot(t,erro(:,2))

erroRMS = sqrt(mean((erro).^2))
erroMax = max(abs(erro))

figure
plot(t,erro(:,1)*erroMax(2)/erroMax(1));
hold on 
plot(t,erro(:,2))
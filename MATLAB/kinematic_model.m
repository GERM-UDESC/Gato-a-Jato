close all
clear all
clc

L = 10e-2; % Distância do centro até a roda
r = 16e-3; % Raio das rodas
tetad = 0;
tetae = pi;
teta = (r/2*L)*(tetad-tetae);
vmd = 2;
vme = 2;

Vx = 2;
Vy = 0;
Vteta = 0;
v = 2;
w = 0;
P = [v w]';
T = [1/r L/r; 1/r -L/r];
vm = T*P

J1f = [1 0 L; 1 0 -L];
C1f = [0 1 0];
JC1f = [J1f ; C1f];
JC1finv = inv(JC1f);
R = [cos(teta) sin(teta) 0; -sin(teta) cos(teta) 0; 0 0 1];
Rinv = inv(R);
qsip = [Vx Vy Vteta]';
% J2 = [r*vmd r*vme 0]';
J2 = [r*vm' 0]';

%%
qsip_ = Rinv*JC1finv*J2;

%%
J2_ = (1/r)*JC1f*R*qsip_

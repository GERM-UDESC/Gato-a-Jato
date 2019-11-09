clc
close all

% A  = rand(1,10);
% C = (1:10);
% fid=fopen('MyFile.txt','w');
% fprintf(fid, '%f %f \n', [A; C]);
% fclose(fid);

A  = rand(1,10)';
C = (1:10)';
fid=fopen('MyFile.txt','w');
fprintf(fid, '%f %f \n', [A C]');
fclose(fid);
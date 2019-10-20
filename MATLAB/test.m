clc
clear all
close all

A  = rand(1,10);
B = rand(1,10);
C = (1:10);
fid=fopen('MyFile.txt','w');
fprintf(fid, '%f %f %f \n', [A' B' C']');
fclose(fid);true
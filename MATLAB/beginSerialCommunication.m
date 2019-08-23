function [] = beginSerialCommunication(comPort)
% This function starts the communication with the robot.
% It takes the com port as input as 'com1', 'com4', 'com...' depending on
% wich 'com' port windows has recognized
% It also has some fixed parameters that are also fixed in robot code. If
% you want to change anything here, please change also in robot code, at
% USART driver.
close all
clear all
clc

bits_to_receive = 2500;
baud_rate = 1e6;


seguidor = serial(comPort,'BaudRate',baud_rate,'Parity','none', 'InputBufferSize', 25000); 
fopen(seguidor);
end


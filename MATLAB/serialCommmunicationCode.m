% This script makes the communications with the robot using these
% functions:

% beginSerialCommunication:
% This function starts the communication with the robot.
% It takes the com port as input as 'com1', 'com4', 'com...' depending on
% wich 'com' port windows has recognized

% endSerialCommunication:
% This function just end the communication between matlab and the 'com'
% port. It has to run at the end of the code.

% serialCommands:
% send the wanted command to the robot. The allowed commands are:
% robotStop(0) - make the robot stop
% robotRun(1) - make the robot start to run;
% sendV_W(2) - make the robot send to matlab the actual linear(V) and
% angular(w) speeds.
% sendV_Wcontrol(3) - make the robot send to matlab the control signal of linear(V) and
% angular(w) speeds.
% sendV_W_and_V_Wcontrol(4) - make the robot send to matlab the actual linear(V) and
% angular(w) speeds and the control signal of linear(V) and angular(w)
% speeds.
% sendLineReading(5) - make the robot send the y_error and angle error.
% sendMotorsSpeed(6) - make the robot send the right and left motors speed (RPM).

% beginSerialCommunication:
close all
clear all
clc

baud_rate = 1382400;
Ts = 1e-3;
TempoTotal = 15;
bits_to_receive = (TempoTotal)/(Ts);
bufferSize = 2*bits_to_receive*32*6;

seguidor = serial('com5','BaudRate',baud_rate,'Parity','none', 'InputBufferSize', bufferSize); 
fopen(seguidor);

%%
close all
clc
command = 10;
flushinput(seguidor);
fwrite(seguidor, command, 'uint8');

plotRobotData(command,seguidor,bits_to_receive,Ts);


%%
fclose(seguidor);
close all
clear all
clc
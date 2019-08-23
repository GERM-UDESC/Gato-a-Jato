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
% start - make the robot start to run;
% stop - make the robot stop
% sendV_W - make the robot send to matlab the actual linear(V) and
% angular(w) speeds.
% sendV_Wcontrol - make the robot send to matlab the control signal of linear(V) and
% angular(w) speeds.
% sendMotorsSpeed - make the robot send the right and left motors speed (RPM).

beginSerialCommunication();
serialCommands(start);

%%
endSerialCommunication();







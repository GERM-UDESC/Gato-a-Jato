function [] = endSerialCommunication()
% This function just end the communication between matlab and the 'com'
% port. It has to run at the end of the code.
fclose(seguidor);
end


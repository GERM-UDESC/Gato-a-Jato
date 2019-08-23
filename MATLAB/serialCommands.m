function [dataRequested] = serialCommands(command)

switch command
    case start
        code = 0;
    case stop
        code = 1;
    case sendV_W
        code = 2;
    case sendV_Wcontrol
        code = 3;
    case sendMotorsSpeed
        code = 4;
end
        
flushinput(seguidor);
fwrite(seguidor, code, 'uint8');
temp = fread(seguidor, 5000,'float');
dataRequested = [temp(1:2:length(temp))'; temp(2:2:length(temp))'];

end


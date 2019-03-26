function [data] = colect_data(speed_ref, number_of_points, baud_rate)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
seguidor = serial('com3','BaudRate',baud_rate,'Parity','none'); 
fopen(seguidor);
fwrite(seguidor, speed_ref/10, 'uint8');
flushinput(seguidor);
data1 = zeros(1,number_of_points);
u1 = zeros(1,number_of_points);
% data2 = zeros(1,number_of_points);
% u2 = zeros(1,number_of_points);
ref = zeros(1,number_of_points);

for i = 1:number_of_points
    while (seguidor.BytesAvailable == 0)
    end
    ref(i) = fread(seguidor,1,'float');
    while (seguidor.BytesAvailable == 0)
    end
    data1(i) = fread(seguidor,1,'float');
    while (seguidor.BytesAvailable == 0)
    end
    u1(i) = fread(seguidor,1,'float');
%     while (seguidor.BytesAvailable == 0)
%     end
%     data2(i) = fread(seguidor,1,'float');
%     while (seguidor.BytesAvailable == 0)
%     end
%     u2(i) = fread(seguidor,1,'float');
end

fclose(seguidor);

% data = [ref; data1; u1; data2; u2];
data = [ref; data1; u1];

end


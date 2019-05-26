function [data] = colect_data(speed_ref, number_of_points, baud_rate)

seguidor = serial('com3','BaudRate',baud_rate,'Parity','none','InputBufferSize', 25000); 
ref = zeros(1,number_of_points);
data1 = zeros(1,number_of_points);
fopen(seguidor);
fwrite(seguidor, speed_ref, 'uint8');
flushinput(seguidor);

ref = fread(seguidor,5000,'uint16');

% for i = 1:number_of_points
%     while (seguidor.BytesAvailable == 0)
%     end
%     ref(i) = fread(seguidor,1,'uint8');
%     while (seguidor.BytesAvailable == 0)
%     end
%     data1(i) = fread(seguidor,1,'uint16');
% end

fclose(seguidor);

data = [ref; data1];

end


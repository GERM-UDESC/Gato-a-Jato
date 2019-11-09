function [] = plotRobotData(command,seguidor,bits_to_receive,Ts)

t = 0:Ts:((bits_to_receive-1)*Ts);
receive_time = 1.5*Ts*bits_to_receive;
pause(receive_time);
if (command == 2) || (command == 3) || (command == 6)
    temp = fread(seguidor, 2*bits_to_receive,'float');
    data1 = temp(1:2:length(temp));
    data2 = temp(2:2:length(temp));
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f \n', [data1' data2']');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    subplot(2,1,2)
    plot(t,data2,'k-.');
end
if (command == 4) || (command == 7)
    temp = fread(seguidor, 4*bits_to_receive,'float');
    data1 = temp(1:4:length(temp));
    data2 = temp(2:4:length(temp));
    data3 = temp(3:4:length(temp));
    data4 = temp(4:4:length(temp));
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f %f %f \n', [data1' data2' data3' data4']');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    hold on
    plot(t,data3,'k-');
    subplot(2,1,2)
    plot(t,data2,'g-.');
    hold on
    plot(t,data4,'r-.');
end
if (command == 5)
    temp = fread(seguidor, 2*bits_to_receive,'float');
    data1 = temp(1:2:length(temp));
    data2 = 180*temp(2:2:length(temp))/pi;
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f \n', [data1' data2']');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    subplot(2,1,2)
    plot(t,data2,'k-.');
end
if (command == 8)
    temp = fread(seguidor, 6*bits_to_receive,'float');
    data1 = temp(1:6:length(temp));
    data2 = temp(2:6:length(temp));
    data3 = temp(3:6:length(temp));
    data4 = temp(4:6:length(temp));
    data5 = temp(5:6:length(temp));
    data6 = temp(6:6:length(temp));
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f %f %f %f %f \n', [data1' data2' data3' data4' data5' data6']');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    hold on
    plot(t,data3,'k-');
    plot(t,data5,'r-');
    subplot(2,1,2)
    plot(t,data2,'b-');
    hold on
    plot(t,data4,'k-');
    plot(t,data6,'r-');
end
if (command == 9)
    temp = fread(seguidor, 12*bits_to_receive,'float');
    data1 = temp(1:12:length(temp));
    data2 = temp(2:12:length(temp));
    data3 = temp(3:12:length(temp));
    data4 = temp(4:12:length(temp));
    data5 = temp(5:12:length(temp));
    data6 = 180*temp(6:12:length(temp))/pi;
    data7 = temp(7:12:length(temp));
    data8 = temp(8:12:length(temp));
    data9 = temp(9:12:length(temp));
    data10 = temp(10:12:length(temp));
    data11 = temp(11:12:length(temp));
    data12 = temp(12:12:length(temp));
    
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f %f %f %f %f %f %f %f %f %f %f \n', [data1' data2' data3' data4' data5' data6' data7' data8' data9' data10' data11' data12']');
    fclose(fid);
    
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    hold on
    plot(t,data3,'k-');
    legend('Velocidade Linear atual', 'Velocidade Linear - Controle');
    ylabel('Velocidade Linear (m/s)');
    xlabel('Tempo');
    
    subplot(2,1,2)
    plot(t,data2,'b-.');
    hold on
    plot(t,data4,'k-.');
    legend('Velocidade Angular atual', 'Velocidade Angular - Controle');
    ylabel('Velocidade Angular (rad/s)');
    xlabel('Tempo');
    
    
    figure
    subplot(2,1,1)
    plot(t,data5,'b-');
    subplot(2,1,2)
    plot(t,data6,'k-.');
    subplot(2,1,1)
    legend('Erro em y');
    ylabel('Erro em y (m)');
    xlabel('Tempo');
    subplot(2,1,2)
    legend('Erro na orientação');
    ylabel('Erro na orientação (graus)');
    xlabel('Tempo');
    
    figure
    subplot(2,1,1)
    plot(t,data7,'b-');
    hold on
    plot(t,data9,'k-');
    plot(t,data11,'r-');
    subplot(2,1,2)
    plot(t,data8,'b-');
    hold on
    plot(t,data10,'k-');
    plot(t,data12,'r-');
    subplot(2,1,1)
    legend('Velocidade atual Motor Direito', 'Motor Direito - Controle (%)', 'erro');
    ylabel('Velocidade angular (RPM)');
    xlabel('Tempo');
    subplot(2,1,2)
    legend('Velocidade atual Motor Esquerdo', 'Motor Esquerdo - Controle (5)', 'erro');
    ylabel('Velocidade angular (RPM)');
    xlabel('Tempo');
end
if (command == 10)
    temp = fread(seguidor, 3*bits_to_receive,'float');
    data1 = temp(1:3:length(temp));
    data2 = temp(2:3:length(temp));
    data3 = 180*temp(3:3:length(temp))/pi;
    
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f %f \n', [data1' data2' data3']');
    fclose(fid);
    
    figure
    subplot(2,1,1)
    plot(data1,data2,'b');
    subplot(2,1,2)
    plot(t,data3,'r-');
end

if (command == 11)
    temp = fread(seguidor, 2*bits_to_receive,'float');
    data1 = temp(1:2:length(temp));
    data2 = temp(2:2:length(temp));
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f \n', [data1 data2]');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    subplot(2,1,2)
    plot(t,data2,'k-');
end

if (command == 12)
    temp = fread(seguidor, 4*bits_to_receive,'float');
    data1 = temp(1:4:length(temp));
    data2 = temp(2:4:length(temp));
    data3 = temp(3:4:length(temp));
    data4 = temp(4:4:length(temp));
    fid=fopen('data.txt','w');
    fprintf(fid, '%f %f %f %f \n', [data1 data2 data3 data4]');
    fclose(fid);
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    hold on
    plot(t,data4,'k-');
    subplot(2,1,2)
    plot(t,data2,'g-.');
%     hold on
%     plot(t,data3,'r-.');
end

switch command
    case 2
        subplot(2,1,1)
        legend('Velocidade Linear atual');
        ylabel('Velocidade Linear (m/s)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade Angular atual');
        ylabel('Velocidade Angular (rad/s)');
        xlabel('Tempo');
    case 3
        subplot(2,1,1)
        legend('Velocidade Linear - Controle');
        ylabel('Velocidade Linear (m/s)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade Angular - Controle');
        ylabel('Velocidade Angular (rad/s)');
        xlabel('Tempo');
    case 4
        subplot(2,1,1)
        legend('Velocidade Linear atual', 'Velocidade Linear - Controle');
        ylabel('Velocidade Linear (m/s)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade Angular atual', 'Velocidade Angular - Controle');
        ylabel('Velocidade Angular (rad/s)');
        xlabel('Tempo');
    case 5
        subplot(2,1,1)
        legend('Erro em y');
        ylabel('Erro em y (m)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Erro na orientação');
        ylabel('Erro na orientação (rad)');
        xlabel('Tempo');
    case 6
        subplot(2,1,1)
        legend('Velocidade atual Motor Direito');
        ylabel('Velocidade angular (RPM)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade atual Motor Esquerdo');
        ylabel('Velocidade Angular (RPM)');
        xlabel('Tempo');
    case 7
        subplot(2,1,1)
        legend('Velocidade atual Motor Direito', 'Velocidade Motor Direito - Controle');
        ylabel('Velocidade angular (RPM)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade atual Motor Esquerdo', 'Velocidade Motor Esquerdo - Controle');
        ylabel('Velocidade angular (RPM)');
        xlabel('Tempo');
        
    case 8
        subplot(2,1,1)
        legend('Velocidade atual Motor Direito', 'Velocidade Motor Direito - Controle (%)', 'erro');
        ylabel('Velocidade angular (RPM)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Velocidade atual Motor Esquerdo', 'Velocidade Motor Esquerdo - Controle (5)', 'erro');
        ylabel('Velocidade angular (RPM)');
        xlabel('Tempo');
        
    case 10
        subplot(2,1,1)
        legend('posição');
        ylabel('Y');
        xlabel('X');
        subplot(2,1,2)
        legend('angulo');
        ylabel('angulo(rad)');
        xlabel('Tempo');
        
    case 11
        subplot(2,1,1)
        legend('Entrada');
        ylabel('Razão cíclica (%)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Resposta do Motor');
        ylabel('Velocidade Angular (RPM)');
        xlabel('Tempo');
    case 12
        subplot(2,1,1)
        legend('Entrada');
        ylabel('Razão cíclica (%)');
        xlabel('Tempo');
        subplot(2,1,2)
        legend('Entrada');
        ylabel('Razão cíclica (%)');
        xlabel('Tempo');
        
    otherwise
        
end

end


function [] = plotRobotData(command,seguidor,bits_to_receive,Ts)

t = 0:Ts:((bits_to_receive-1)*Ts);
if (command == 2) || (command == 3) || (command == 5) || (command == 6)
    pause(Ts*2*bits_to_receive);
    temp = fread(seguidor, 2*bits_to_receive,'float');
    data1 = temp(1:2:length(temp)); 
    data2 = temp(2:2:length(temp)); 
    figure
    subplot(2,1,1)
    plot(t,data1,'b-');
    subplot(2,1,2)
    plot(t,data2,'k-.');
else
    if (command == 4) || (command == 7)
        pause(Ts*4*bits_to_receive);
        temp = fread(seguidor, 4*bits_to_receive,'float');
        data1 = temp(1:4:length(temp)); 
        data2 = temp(2:4:length(temp));
        data3 = temp(3:4:length(temp)); 
        data4 = temp(4:4:length(temp)); 
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
    otherwise
        
end

end


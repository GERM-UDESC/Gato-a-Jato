EESchema Schematic File Version 4
LIBS:Placa-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5300 4950 5150 4950
Wire Wire Line
	5150 5050 5300 5050
Wire Wire Line
	5300 5150 5150 5150
Wire Wire Line
	5150 5250 5300 5250
Wire Wire Line
	5300 5350 5150 5350
Wire Wire Line
	5150 5450 5300 5450
Wire Wire Line
	5300 5550 5150 5550
Wire Wire Line
	5150 5650 5300 5650
$Comp
L Placa-rescue:PW_Slinha U10
U 1 1 5B0060DA
P 6000 6050
F 0 "U10" H 6000 5850 60  0000 C CNN
F 1 "PW_Slinha" H 6050 6250 60  0000 C CNN
F 2 "FootLibAlan:PW_Slinha" H 6000 6300 60  0001 C CNN
F 3 "" H 6000 6300 60  0001 C CNN
	1    6000 6050
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:stm32 U8
U 1 1 5B006218
P 4650 5200
F 0 "U8" H 4800 6250 60  0000 C CNN
F 1 "stm32" H 4500 6250 60  0000 C CNN
F 2 "FootLibAlan:stm32" V 4650 4600 60  0001 C CNN
F 3 "" V 4650 4600 60  0001 C CNN
	1    4650 5200
	1    0    0    -1  
$EndComp
Text Label 5750 6150 2    60   ~ 0
GND
$Comp
L Placa-rescue:tb6612fng U7
U 1 1 5B00644E
P 2550 5200
F 0 "U7" H 2550 4600 60  0000 C CNN
F 1 "tb6612fng" H 2550 5600 60  0000 C CNN
F 2 "FootLibAlan:tb6612fng" H 2550 5600 60  0001 C CNN
F 3 "" H 2550 5600 60  0001 C CNN
	1    2550 5200
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Encoder Enc1
U 1 1 5B0064FB
P 1350 6950
F 0 "Enc1" H 1350 6550 60  0000 C CNN
F 1 "Encoder" H 1350 7300 60  0000 C CNN
F 2 "FootLibAlan:Encoder" H 1350 7150 60  0001 C CNN
F 3 "" H 1350 7150 60  0001 C CNN
	1    1350 6950
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Encoder Enc2
U 1 1 5B006651
P 2400 6900
F 0 "Enc2" H 2400 6500 60  0000 C CNN
F 1 "Encoder" H 2400 7250 60  0000 C CNN
F 2 "FootLibAlan:Encoder" H 2400 7100 60  0001 C CNN
F 3 "" H 2400 7100 60  0001 C CNN
	1    2400 6900
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Regulador_3.3V Reg3.1
U 1 1 5B0067C7
P 2500 3450
F 0 "Reg3.1" H 2600 3050 60  0000 C CNN
F 1 "Regulador_3.3V" H 2600 3650 60  0000 C CNN
F 2 "FootLibAlan:Regulador_3.3V" H 2500 3300 60  0001 C CNN
F 3 "" H 2500 3300 60  0001 C CNN
	1    2500 3450
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:barra2pins U1
U 1 1 5B006ADC
P 1150 3350
F 0 "U1" H 1200 3350 60  0000 C CNN
F 1 "barra2pins" H 1050 3500 60  0000 C CNN
F 2 "FootLibAlan:barra2pins" H 1150 3350 60  0001 C CNN
F 3 "" H 1150 3350 60  0001 C CNN
	1    1150 3350
	1    0    0    -1  
$EndComp
Text Label 2250 3700 2    60   ~ 0
V3.3
Text Label 2050 4950 2    60   ~ 0
V12
Text Label 1100 3600 0    60   ~ 0
VBat
Text Label 1800 3550 3    60   ~ 0
VCC
Text Label 1300 2950 2    60   ~ 0
VBat
Text Label 1000 3600 2    60   ~ 0
GND
Text Label 1250 7250 2    60   ~ 0
GND
Text Label 2300 7200 2    60   ~ 0
GND
Text Label 850  5450 2    60   ~ 0
GND
Text Label 850  5250 2    60   ~ 0
GND
Text Label 850  5350 2    60   ~ 0
VCC
Text Label 2250 3500 2    60   ~ 0
VCC
Text Label 2250 3400 2    60   ~ 0
VCC
Text Label 2250 3600 2    60   ~ 0
GND
Text Label 5150 4450 0    60   ~ 0
V3.3
Text Label 5750 6050 2    60   ~ 0
V3.3
Text Label 5750 5950 2    60   ~ 0
V3.3
Text Label 4100 6050 2    60   ~ 0
GND
Text Label 5150 4250 0    60   ~ 0
GND
Text Label 5150 4350 0    60   ~ 0
GND
Text Label 2300 6900 2    60   ~ 0
V3.3
Text Label 1250 6950 2    60   ~ 0
V3.3
Text Label 2050 5050 2    60   ~ 0
V3.3
Text Label 2050 5150 2    60   ~ 0
GND
Text Label 2050 5650 2    60   ~ 0
GND
Text Label 3050 5650 0    60   ~ 0
GND
Text Label 2050 5550 2    60   ~ 0
B1
Text Label 2050 5450 2    60   ~ 0
B2
Text Label 2050 5350 2    60   ~ 0
A2
Text Label 2050 5250 2    60   ~ 0
A1
Text Label 3050 4950 0    60   ~ 0
PWM_E
Text Label 3050 5050 0    60   ~ 0
Ain2
Text Label 3050 5150 0    60   ~ 0
Ain1
Text Label 3050 5350 0    60   ~ 0
Bin1
Text Label 3050 5450 0    60   ~ 0
Bin2
Text Label 3050 5550 0    60   ~ 0
PWM_D
Text Label 1250 6750 2    60   ~ 0
A1
Text Label 1250 6850 2    60   ~ 0
A2
Text Label 2300 6700 2    60   ~ 0
B1
Text Label 2300 6800 2    60   ~ 0
B2
Text Label 1250 7050 2    60   ~ 0
ENC_E_A
Text Label 1250 7150 2    60   ~ 0
ENC_E_B
Text Label 2300 7000 2    60   ~ 0
ENC_D_A
Text Label 2300 7100 2    60   ~ 0
ENC_D_B
Text Label 4100 4650 2    60   ~ 0
ENC_E_A
Text Label 4100 4750 2    60   ~ 0
ENC_E_B
Text Label 4100 5450 2    60   ~ 0
PWM_E
Text Label 4100 4850 2    60   ~ 0
Ain2
Text Label 4100 4950 2    60   ~ 0
Ain1
Text Label 3050 5250 0    60   ~ 0
STBY
Text Label 4100 5050 2    60   ~ 0
STBY
Text Label 4100 5150 2    60   ~ 0
Bin1
Text Label 4100 5250 2    60   ~ 0
Bin2
Text Label 4100 5350 2    60   ~ 0
PWM_D
Text Label 4100 5650 2    60   ~ 0
ENC_D_A
Text Label 4100 5550 2    60   ~ 0
ENC_D_B
Text Label 850  5550 2    60   ~ 0
V12
$Comp
L Placa-rescue:Borne U3
U 1 1 5B00A670
P 850 5250
F 0 "U3" H 850 5150 60  0000 C CNN
F 1 "Borne" H 850 5350 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 850 5250 60  0001 C CNN
F 3 "" H 850 5250 60  0001 C CNN
	1    850  5250
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Borne U4
U 1 1 5B00A717
P 850 5350
F 0 "U4" H 850 5250 60  0000 C CNN
F 1 "Borne" H 850 5450 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 850 5350 60  0001 C CNN
F 3 "" H 850 5350 60  0001 C CNN
	1    850  5350
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Borne U5
U 1 1 5B00A74E
P 850 5450
F 0 "U5" H 850 5350 60  0000 C CNN
F 1 "Borne" H 850 5550 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 850 5450 60  0001 C CNN
F 3 "" H 850 5450 60  0001 C CNN
	1    850  5450
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Borne U6
U 1 1 5B00A792
P 850 5550
F 0 "U6" H 850 5450 60  0000 C CNN
F 1 "Borne" H 850 5650 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 850 5550 60  0001 C CNN
F 3 "" H 850 5550 60  0001 C CNN
	1    850  5550
	1    0    0    -1  
$EndComp
$Comp
L Placa-rescue:Desenho_placa_seguidor U13
U 1 1 5B05DBF9
P 10000 6150
F 0 "U13" H 10000 6150 60  0000 C CNN
F 1 "Desenho_placa_seguidor" H 10050 6300 60  0000 C CNN
F 2 "FootLibAlan:Desenho_Nova_Placa_Seguidor" H 9950 6400 60  0001 C CNN
F 3 "" H 9950 6400 60  0001 C CNN
	1    10000 6150
	1    0    0    -1  
$EndComp
Text Label 4100 6150 2    60   ~ 0
V3.3
Wire Wire Line
	5300 5750 5150 5750
Wire Wire Line
	5150 4850 5300 4850
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5C10524D
P 5500 4850
F 0 "J1" H 5527 4826 50  0000 L CNN
F 1 "Conn_01x02_Female" H 5527 4735 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 5500 4850 50  0001 C CNN
F 3 "~" H 5500 4850 50  0001 C CNN
	1    5500 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J2
U 1 1 5C1052D3
P 5500 5350
F 0 "J2" H 5527 5326 50  0000 L CNN
F 1 "Conn_01x08_Female" H 5527 5235 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5500 5350 50  0001 C CNN
F 3 "~" H 5500 5350 50  0001 C CNN
	1    5500 5350
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 Reg_5V1
U 1 1 5D2217A8
P 3500 3500
F 0 "Reg_5V1" H 3500 3742 50  0000 C CNN
F 1 "LM7805" H 3500 3651 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3500 3725 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 3500 3450 50  0001 C CNN
	1    3500 3500
	1    0    0    -1  
$EndComp
Text Label 3200 3500 2    60   ~ 0
VCC
Text Label 3500 3800 2    60   ~ 0
GND
Text Label 3800 3500 0    60   ~ 0
V5
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 5D2239CA
P 4800 3500
F 0 "J3" H 4828 3476 50  0000 L CNN
F 1 "Conn_01x06_Female" H 4828 3385 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4800 3500 50  0001 C CNN
F 3 "~" H 4800 3500 50  0001 C CNN
	1    4800 3500
	1    0    0    -1  
$EndComp
Text Label 4600 3300 2    60   ~ 0
State
Text Label 4600 3400 2    60   ~ 0
RX_module
Text Label 4600 3500 2    60   ~ 0
TX_module
Text Label 4600 3600 2    60   ~ 0
GND
Text Label 4600 3700 2    60   ~ 0
V5
Text Label 4600 3800 2    60   ~ 0
EN
Text Label 5150 4750 0    60   ~ 0
RX_module
Text Label 5150 4650 0    60   ~ 0
TX_module
$Comp
L Placa-rescue:barra2pins U2
U 1 1 5D66E07C
P 1850 3300
F 0 "U2" H 1900 3300 60  0000 C CNN
F 1 "barra2pins" H 1750 3450 60  0000 C CNN
F 2 "FootLibAlan:barra2pins" H 1850 3300 60  0001 C CNN
F 3 "" H 1850 3300 60  0001 C CNN
	1    1850 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse_Small F1
U 1 1 5D67C310
P 1400 2950
F 0 "F1" H 1400 3135 50  0000 C CNN
F 1 "Fuse_Small" H 1400 3044 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P5.08mm_Vertical" H 1400 2950 50  0001 C CNN
F 3 "~" H 1400 2950 50  0001 C CNN
	1    1400 2950
	1    0    0    -1  
$EndComp
Text Label 1500 2950 0    50   ~ 0
Vfuse
Text Label 1700 3550 3    50   ~ 0
Vfuse
$EndSCHEMATC

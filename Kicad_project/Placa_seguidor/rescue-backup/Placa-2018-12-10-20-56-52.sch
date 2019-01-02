EESchema Schematic File Version 2
LIBS:LibAlan
LIBS:Placa-cache
EELAYER 25 0
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
$Comp
L barra10pins U5
U 1 1 5B005A2C
P 6350 3850
F 0 "U5" H 6000 4050 60  0000 C CNN
F 1 "barra10pins" H 6350 4050 60  0000 C CNN
F 2 "FootLibAlan:barra10pin" H 6100 3850 60  0001 C CNN
F 3 "" H 6100 3850 60  0001 C CNN
	1    6350 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 3400 6000 3400
Wire Wire Line
	6000 3500 6150 3500
Wire Wire Line
	6150 3600 6000 3600
Wire Wire Line
	6000 3700 6150 3700
Wire Wire Line
	6150 3800 6000 3800
Wire Wire Line
	6000 3900 6150 3900
Wire Wire Line
	6150 4000 6000 4000
Wire Wire Line
	6000 4100 6150 4100
Wire Wire Line
	6150 4200 6000 4200
Wire Wire Line
	6000 4300 6150 4300
$Comp
L PW_Slinha U6
U 1 1 5B0060DA
P 6850 4600
F 0 "U6" H 6850 4400 60  0000 C CNN
F 1 "PW_Slinha" H 6900 4800 60  0000 C CNN
F 2 "FootLibAlan:PW_Slinha" H 6850 4850 60  0001 C CNN
F 3 "" H 6850 4850 60  0001 C CNN
	1    6850 4600
	1    0    0    -1  
$EndComp
$Comp
L stm32 U4
U 1 1 5B006218
P 5500 3750
F 0 "U4" H 5650 4800 60  0000 C CNN
F 1 "stm32" H 5350 4800 60  0000 C CNN
F 2 "FootLibAlan:stm32" V 5500 3150 60  0001 C CNN
F 3 "" V 5500 3150 60  0001 C CNN
	1    5500 3750
	1    0    0    -1  
$EndComp
Text Label 6600 4700 2    60   ~ 0
GND
$Comp
L tb6612fng U3
U 1 1 5B00644E
P 3600 3550
F 0 "U3" H 3600 2950 60  0000 C CNN
F 1 "tb6612fng" H 3600 3950 60  0000 C CNN
F 2 "FootLibAlan:tb6612fng" H 3600 3950 60  0001 C CNN
F 3 "" H 3600 3950 60  0001 C CNN
	1    3600 3550
	1    0    0    -1  
$EndComp
$Comp
L Encoder Enc1
U 1 1 5B0064FB
P 3750 2350
F 0 "Enc1" H 3750 1950 60  0000 C CNN
F 1 "Encoder" H 3750 2700 60  0000 C CNN
F 2 "FootLibAlan:Encoder" H 3750 2550 60  0001 C CNN
F 3 "" H 3750 2550 60  0001 C CNN
	1    3750 2350
	1    0    0    -1  
$EndComp
$Comp
L Encoder Enc2
U 1 1 5B006651
P 3800 4850
F 0 "Enc2" H 3800 4450 60  0000 C CNN
F 1 "Encoder" H 3800 5200 60  0000 C CNN
F 2 "FootLibAlan:Encoder" H 3800 5050 60  0001 C CNN
F 3 "" H 3800 5050 60  0001 C CNN
	1    3800 4850
	1    0    0    -1  
$EndComp
$Comp
L Regulador_3.3V Reg3.31
U 1 1 5B0067C7
P 6200 5250
F 0 "Reg3.31" H 6300 4850 60  0000 C CNN
F 1 "Regulador_3.3V" H 6300 5450 60  0000 C CNN
F 2 "FootLibAlan:Regulador_3.3V" H 6200 5100 60  0001 C CNN
F 3 "" H 6200 5100 60  0001 C CNN
	1    6200 5250
	1    0    0    -1  
$EndComp
$Comp
L barra3pins U2
U 1 1 5B006A71
P 1950 2800
F 0 "U2" H 2150 2800 60  0000 C CNN
F 1 "barra3pins" H 1950 2950 60  0000 C CNN
F 2 "FootLibAlan:barra3pins" H 1950 2800 60  0001 C CNN
F 3 "" H 1950 2800 60  0001 C CNN
	1    1950 2800
	1    0    0    -1  
$EndComp
$Comp
L barra2pins U1
U 1 1 5B006ADC
P 1450 4000
F 0 "U1" H 1500 4000 60  0000 C CNN
F 1 "barra2pins" H 1350 4150 60  0000 C CNN
F 2 "FootLibAlan:barra2pins" H 1450 4000 60  0001 C CNN
F 3 "" H 1450 4000 60  0001 C CNN
	1    1450 4000
	1    0    0    -1  
$EndComp
Text Label 5950 5500 2    60   ~ 0
V3.3
Text Label 3100 3300 2    60   ~ 0
V12
Text Label 1400 4250 0    60   ~ 0
VBat
Text Label 1950 3050 3    60   ~ 0
VCC
Text Label 1850 3050 3    60   ~ 0
VBat
Text Label 1300 4250 2    60   ~ 0
GND
Text Label 3650 2650 2    60   ~ 0
GND
Text Label 3700 5150 2    60   ~ 0
GND
Text Label 2350 4350 2    60   ~ 0
GND
Text Label 2350 4150 2    60   ~ 0
GND
Text Label 2350 4250 2    60   ~ 0
VCC
Text Label 5950 5300 2    60   ~ 0
VCC
Text Label 5950 5200 2    60   ~ 0
VCC
Text Label 5950 5400 2    60   ~ 0
GND
Text Label 6000 3000 0    60   ~ 0
V3.3
Text Label 6600 4600 2    60   ~ 0
V3.3
Text Label 6600 4500 2    60   ~ 0
V3.3
Text Label 4950 4600 2    60   ~ 0
GND
Text Label 6000 2800 0    60   ~ 0
GND
Text Label 6000 2900 0    60   ~ 0
GND
Text Label 3700 4850 2    60   ~ 0
V3.3
Text Label 3650 2350 2    60   ~ 0
V3.3
Text Label 3100 3400 2    60   ~ 0
V3.3
Text Label 3100 3500 2    60   ~ 0
GND
Text Label 3100 4000 2    60   ~ 0
GND
Text Label 4100 4000 0    60   ~ 0
GND
Text Label 3100 3900 2    60   ~ 0
B1
Text Label 3100 3800 2    60   ~ 0
B2
Text Label 3100 3700 2    60   ~ 0
A2
Text Label 3100 3600 2    60   ~ 0
A1
Text Label 4100 3300 0    60   ~ 0
PWM_E
Text Label 4100 3400 0    60   ~ 0
Ain2
Text Label 4100 3500 0    60   ~ 0
Ain1
Text Label 4100 3700 0    60   ~ 0
Bin1
Text Label 4100 3800 0    60   ~ 0
Bin2
Text Label 4100 3900 0    60   ~ 0
PWM_D
Text Label 3650 2150 2    60   ~ 0
A1
Text Label 3650 2250 2    60   ~ 0
A2
Text Label 3700 4650 2    60   ~ 0
B1
Text Label 3700 4750 2    60   ~ 0
B2
Text Label 3650 2450 2    60   ~ 0
ENC_E_A
Text Label 3650 2550 2    60   ~ 0
ENC_E_B
Text Label 3700 4950 2    60   ~ 0
ENC_D_A
Text Label 3700 5050 2    60   ~ 0
ENC_D_B
Text Label 4950 3200 2    60   ~ 0
ENC_E_A
Text Label 4950 3300 2    60   ~ 0
ENC_E_B
Text Label 4950 4000 2    60   ~ 0
PWM_E
Text Label 4950 3400 2    60   ~ 0
Ain2
Text Label 4950 3500 2    60   ~ 0
Ain1
Text Label 4100 3600 0    60   ~ 0
STBY
Text Label 4950 3600 2    60   ~ 0
STBY
Text Label 4950 3700 2    60   ~ 0
Bin1
Text Label 4950 3800 2    60   ~ 0
Bin2
Text Label 4950 3900 2    60   ~ 0
PWM_D
Text Label 4950 4200 2    60   ~ 0
ENC_D_A
Text Label 4950 4100 2    60   ~ 0
ENC_D_B
Text Label 2350 4450 2    60   ~ 0
V12
$Comp
L Borne U9
U 1 1 5B00A670
P 2350 4150
F 0 "U9" H 2350 4050 60  0000 C CNN
F 1 "Borne" H 2350 4250 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 2350 4150 60  0001 C CNN
F 3 "" H 2350 4150 60  0001 C CNN
	1    2350 4150
	1    0    0    -1  
$EndComp
$Comp
L Borne U10
U 1 1 5B00A717
P 2350 4250
F 0 "U10" H 2350 4150 60  0000 C CNN
F 1 "Borne" H 2350 4350 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 2350 4250 60  0001 C CNN
F 3 "" H 2350 4250 60  0001 C CNN
	1    2350 4250
	1    0    0    -1  
$EndComp
$Comp
L Borne U11
U 1 1 5B00A74E
P 2350 4350
F 0 "U11" H 2350 4250 60  0000 C CNN
F 1 "Borne" H 2350 4450 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 2350 4350 60  0001 C CNN
F 3 "" H 2350 4350 60  0001 C CNN
	1    2350 4350
	1    0    0    -1  
$EndComp
$Comp
L Borne U12
U 1 1 5B00A792
P 2350 4450
F 0 "U12" H 2350 4350 60  0000 C CNN
F 1 "Borne" H 2350 4550 60  0000 C CNN
F 2 "FootLibAlan:Borne" H 2350 4450 60  0001 C CNN
F 3 "" H 2350 4450 60  0001 C CNN
	1    2350 4450
	1    0    0    -1  
$EndComp
$Comp
L Desenho_placa_seguidor U13
U 1 1 5B05DBF9
P 7950 3250
F 0 "U13" H 7950 3250 60  0000 C CNN
F 1 "Desenho_placa_seguidor" H 8000 3400 60  0000 C CNN
F 2 "FootLibAlan:Desenho_Placa_Seguidor" H 7900 3500 60  0001 C CNN
F 3 "" H 7900 3500 60  0001 C CNN
	1    7950 3250
	1    0    0    -1  
$EndComp
Text Label 4950 4700 2    60   ~ 0
V3.3
$EndSCHEMATC

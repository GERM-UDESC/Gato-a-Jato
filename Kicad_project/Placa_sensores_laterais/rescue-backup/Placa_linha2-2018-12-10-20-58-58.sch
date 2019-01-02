EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Placa_linha2-cache
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
L QRE1113 U1
U 1 1 5B6DFB36
P 6400 2250
F 0 "U1" H 6450 2050 60  0001 C CNN
F 1 "QRE1113" H 6450 2350 39  0000 C CNN
F 2 "FootLibAlan:QRE1113_SMD" H 6150 2250 60  0001 C CNN
F 3 "" H 6150 2250 60  0001 C CNN
	1    6400 2250
	1    0    0    -1  
$EndComp
$Comp
L QRE1113 U3
U 1 1 5B6DFB5E
P 6400 2950
F 0 "U3" H 6450 2750 60  0001 C CNN
F 1 "QRE1113" H 6450 3050 39  0000 C CNN
F 2 "FootLibAlan:QRE1113_SMD" H 6150 2950 60  0001 C CNN
F 3 "" H 6150 2950 60  0001 C CNN
	1    6400 2950
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Female J1
U 1 1 5B6DFC83
P 4800 2350
F 0 "J1" H 4800 2550 50  0000 C CNN
F 1 "Conn_01x03_Female" H 4800 2150 50  0000 C CNN
F 2 "FootLibAlan:barra3pins" H 4800 2350 50  0001 C CNN
F 3 "" H 4800 2350 50  0001 C CNN
	1    4800 2350
	1    0    0    -1  
$EndComp
Text Label 4600 2250 2    60   ~ 0
VCC
Text Label 4600 2350 2    60   ~ 0
GND
Text Label 4600 2450 2    60   ~ 0
Out
Text Label 5900 2350 2    60   ~ 0
VCC
Wire Wire Line
	6950 2450 6950 2350
Wire Wire Line
	6350 2450 6950 2450
Wire Wire Line
	6350 2450 6350 3000
Wire Wire Line
	6350 3000 5900 3000
Wire Wire Line
	5900 3000 5900 3050
$Comp
L R R2
U 1 1 5B6DFD73
P 7100 3050
F 0 "R2" V 7180 3050 50  0000 C CNN
F 1 "R" V 7100 3050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 7030 3050 50  0001 C CNN
F 3 "" H 7100 3050 50  0001 C CNN
	1    7100 3050
	0    1    1    0   
$EndComp
Text Label 7250 3050 0    60   ~ 0
GND
Text Label 6950 2250 0    60   ~ 0
VCC
Text Label 6950 2950 0    60   ~ 0
VCC
Text Label 5900 2250 2    60   ~ 0
Out
Text Label 5900 2950 1    60   ~ 0
Out
$Comp
L R R1
U 1 1 5B6DFE82
P 5750 2950
F 0 "R1" V 5830 2950 50  0000 C CNN
F 1 "R" V 5750 2950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5680 2950 50  0001 C CNN
F 3 "" H 5750 2950 50  0001 C CNN
	1    5750 2950
	0    1    1    0   
$EndComp
Text Label 5600 2950 2    60   ~ 0
GND
$EndSCHEMATC

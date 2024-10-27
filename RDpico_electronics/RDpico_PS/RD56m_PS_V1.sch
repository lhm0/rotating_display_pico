EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "RD40_PS_V1"
Date "2021-01-03"
Rev "V1"
Comp "Ludwin Monz"
Comment1 "you may not use the material for commercial purposes"
Comment2 "you may use non-commercially, adapt, share alike"
Comment3 "https://creativecommons.org/licenses/by-nc-sa/4.0/"
Comment4 "License: Creative Commons Attribution-Non-Commercial (CC BY-NC-SA)"
$EndDescr
$Comp
L Device:CP C1
U 1 1 5FF1AA83
P 1800 1900
F 0 "C1" H 1918 1946 50  0000 L CNN
F 1 "100µ" H 1918 1855 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 1838 1750 50  0001 C CNN
F 3 "~" H 1800 1900 50  0001 C CNN
	1    1800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 5FF1B60F
P 1800 1400
F 0 "#PWR01" H 1800 1250 50  0001 C CNN
F 1 "+12V" H 1815 1573 50  0000 C CNN
F 2 "" H 1800 1400 50  0001 C CNN
F 3 "" H 1800 1400 50  0001 C CNN
	1    1800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1400 1800 1600
Wire Wire Line
	2350 1600 2150 1600
Connection ~ 1800 1600
Wire Wire Line
	1800 1600 1800 1750
Wire Wire Line
	4000 1300 4000 1600
Wire Wire Line
	4450 2700 4450 2600
Wire Wire Line
	3550 2700 3550 2600
$Comp
L Device:C C2
U 1 1 5FF40853
P 4000 1750
F 0 "C2" V 4250 1750 50  0000 C CNN
F 1 "33nF" V 4150 1750 50  0000 C CNN
F 2 "my_footprints:MKP10_630V" H 4038 1600 50  0001 C CNN
F 3 "~" H 4000 1750 50  0001 C CNN
	1    4000 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 1300 4000 1300
Connection ~ 4000 1300
Wire Wire Line
	4000 1300 4050 1300
Wire Wire Line
	1800 2050 1800 2700
$Comp
L Device:R R1
U 1 1 5FF48CA5
P 2800 2400
F 0 "R1" V 2593 2400 50  0000 C CNN
F 1 "2k2" V 2684 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2730 2400 50  0001 C CNN
F 3 "~" H 2800 2400 50  0001 C CNN
	1    2800 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 2400 2150 2400
Wire Wire Line
	2150 2400 2150 1600
Connection ~ 2150 1600
Wire Wire Line
	2150 1600 1800 1600
Wire Wire Line
	4450 1300 4450 1400
Wire Wire Line
	3550 1300 3550 1400
Wire Wire Line
	4150 1750 4450 1750
Connection ~ 4450 1750
Wire Wire Line
	4450 1750 4450 2200
Wire Wire Line
	3850 1750 3550 1750
Connection ~ 3550 1750
Wire Wire Line
	3550 1750 3550 2200
Wire Wire Line
	4000 2100 4000 2400
Wire Wire Line
	4000 2400 4150 2400
Wire Wire Line
	3450 2100 4000 2100
$Comp
L Connector:Barrel_Jack_Switch_Pin3Ring J1
U 1 1 6018B346
P 1100 1050
F 0 "J1" H 1157 1367 50  0000 C CNN
F 1 "Barrel_Jack_Switch_Pin3Ring" H 1157 1276 50  0000 C CNN
F 2 "my_footprints:GRAVITECH_CON-SOCJ-2155" H 1150 1010 50  0001 C CNN
F 3 "~" H 1150 1010 50  0001 C CNN
	1    1100 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR02
U 1 1 6018CE52
P 1950 700
F 0 "#PWR02" H 1950 550 50  0001 C CNN
F 1 "+12V" H 1965 873 50  0000 C CNN
F 2 "" H 1950 700 50  0001 C CNN
F 3 "" H 1950 700 50  0001 C CNN
	1    1950 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1150 1500 1150
Wire Wire Line
	1500 1150 1500 1300
Wire Wire Line
	1400 950  1950 950 
Wire Wire Line
	1950 950  1950 700 
NoConn ~ 1400 1050
$Comp
L Device:Q_NPN_CBE Q1
U 1 1 5FF33556
P 3450 2400
F 0 "Q1" H 3641 2446 50  0000 L CNN
F 1 "BC337" H 3641 2355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3650 2500 50  0001 C CNN
F 3 "~" H 3450 2400 50  0001 C CNN
	1    3450 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_CBE Q2
U 1 1 5FF38022
P 4350 2400
F 0 "Q2" H 4541 2446 50  0000 L CNN
F 1 "BC337" H 4541 2355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 4550 2500 50  0001 C CNN
F 3 "~" H 4350 2400 50  0001 C CNN
	1    4350 2400
	1    0    0    -1  
$EndComp
$Comp
L my_symbols:coil_2size L1
U 1 1 5FF3D135
P 2550 1500
F 0 "L1" H 2858 1534 50  0000 L CNN
F 1 "330µH" H 2500 1700 50  0000 L CNN
F 2 "my_footprints:L_vertical12" H 2850 1650 50  0001 C CNN
F 3 "" H 2850 1650 50  0001 C CNN
	1    2550 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1600 2450 1600
Connection ~ 2350 1600
$Comp
L power:GND #PWR0118
U 1 1 61019679
P 1500 1300
F 0 "#PWR0118" H 1500 1050 50  0001 C CNN
F 1 "GND" H 1505 1127 50  0000 C CNN
F 2 "" H 1500 1300 50  0001 C CNN
F 3 "" H 1500 1300 50  0001 C CNN
	1    1500 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 6101AAA6
P 1800 2700
F 0 "#PWR0119" H 1800 2450 50  0001 C CNN
F 1 "GND" H 1805 2527 50  0000 C CNN
F 2 "" H 1800 2700 50  0001 C CNN
F 3 "" H 1800 2700 50  0001 C CNN
	1    1800 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 6101B2C7
P 3550 2700
F 0 "#PWR0120" H 3550 2450 50  0001 C CNN
F 1 "GND" H 3555 2527 50  0000 C CNN
F 2 "" H 3550 2700 50  0001 C CNN
F 3 "" H 3550 2700 50  0001 C CNN
	1    3550 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 6101BAD2
P 4450 2700
F 0 "#PWR0121" H 4450 2450 50  0001 C CNN
F 1 "GND" H 4455 2527 50  0000 C CNN
F 2 "" H 4450 2700 50  0001 C CNN
F 3 "" H 4450 2700 50  0001 C CNN
	1    4450 2700
	1    0    0    -1  
$EndComp
Connection ~ 2150 2400
Wire Wire Line
	3450 1300 3450 1400
Wire Wire Line
	3050 2400 3250 2400
Wire Wire Line
	4000 1600 2800 1600
Wire Wire Line
	3050 2400 2950 2400
Connection ~ 3050 2400
$Comp
L Device:R R2
U 1 1 646AA940
P 4200 4350
F 0 "R2" H 4270 4396 50  0000 L CNN
F 1 "100" H 4270 4305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 4350 50  0001 C CNN
F 3 "~" H 4200 4350 50  0001 C CNN
	1    4200 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 646B4429
P 4200 4750
F 0 "RV1" H 4050 4650 50  0000 C CNN
F 1 "1k" H 4050 4750 50  0000 C CNN
F 2 "my_footprints:Poti_10mm" H 4200 4750 50  0001 C CNN
F 3 "~" H 4200 4750 50  0001 C CNN
	1    4200 4750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 646B8BAE
P 5500 3600
F 0 "C3" H 5250 3550 50  0000 L CNN
F 1 "100nF" H 5200 3450 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 5538 3450 50  0001 C CNN
F 3 "~" H 5500 3600 50  0001 C CNN
	1    5500 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 646B9E07
P 4200 4900
F 0 "#PWR0101" H 4200 4650 50  0001 C CNN
F 1 "GND" H 4205 4727 50  0000 C CNN
F 2 "" H 4200 4900 50  0001 C CNN
F 3 "" H 4200 4900 50  0001 C CNN
	1    4200 4900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPDT_x2 SW1
U 1 1 646D02D8
P 5150 3250
F 0 "SW1" H 5150 3535 50  0000 C CNN
F 1 "SW_DPDT_x2" H 5150 3444 50  0000 C CNN
F 2 "my_footprints:Switch1" H 5150 3250 50  0001 C CNN
F 3 "~" H 5150 3250 50  0001 C CNN
	1    5150 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 646D6F27
P 5950 3900
F 0 "#PWR0104" H 5950 3650 50  0001 C CNN
F 1 "GND" H 5955 3727 50  0000 C CNN
F 2 "" H 5950 3900 50  0001 C CNN
F 3 "" H 5950 3900 50  0001 C CNN
	1    5950 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 646D75F6
P 4200 3900
F 0 "R3" H 4270 3946 50  0000 L CNN
F 1 "270" H 4270 3855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 3900 50  0001 C CNN
F 3 "~" H 4200 3900 50  0001 C CNN
	1    4200 3900
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M1
U 1 1 646D956B
P 6250 3550
F 0 "M1" H 6408 3546 50  0000 L CNN
F 1 "Motor_DC" H 6408 3455 50  0000 L CNN
F 2 "my_footprints:motor" H 6250 3460 50  0001 C CNN
F 3 "~" H 6250 3460 50  0001 C CNN
	1    6250 3550
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D1
U 1 1 646DC461
P 5950 3600
F 0 "D1" V 5450 3550 50  0000 L CNN
F 1 "1N4001" V 5600 3500 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5950 3425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5950 3600 50  0001 C CNN
	1    5950 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 3450 5950 3350
Wire Wire Line
	5950 3350 6250 3350
Wire Wire Line
	5950 3750 5950 3850
$Comp
L my_symbols:Pin-Connector U1
U 1 1 64691A8A
P 2950 1400
F 0 "U1" H 2950 1400 50  0001 C CNN
F 1 "Pin-Connector" V 3096 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 2950 1400 50  0001 C CNN
F 3 "" H 2950 1400 50  0001 C CNN
	1    2950 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 1300 3050 1400
Connection ~ 3050 1400
Wire Wire Line
	3050 1400 3050 2400
$Comp
L my_symbols:Pin-Connector U2
U 1 1 6469A86F
P 3350 1400
F 0 "U2" H 3350 1400 50  0001 C CNN
F 1 "Pin-Connector" V 3496 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 3350 1400 50  0001 C CNN
F 3 "" H 3350 1400 50  0001 C CNN
	1    3350 1400
	0    -1   -1   0   
$EndComp
Connection ~ 3450 1400
Wire Wire Line
	3450 1400 3450 2100
$Comp
L my_symbols:Pin-Connector U3
U 1 1 6469DA7F
P 3450 1400
F 0 "U3" H 3450 1400 50  0001 C CNN
F 1 "Pin-Connector" V 3596 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 3450 1400 50  0001 C CNN
F 3 "" H 3450 1400 50  0001 C CNN
	1    3450 1400
	0    -1   -1   0   
$EndComp
Connection ~ 3550 1400
Wire Wire Line
	3550 1400 3550 1750
$Comp
L my_symbols:Pin-Connector U4
U 1 1 6469EE39
P 3850 1400
F 0 "U4" H 3850 1400 50  0001 C CNN
F 1 "Pin-Connector" V 3996 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 3850 1400 50  0001 C CNN
F 3 "" H 3850 1400 50  0001 C CNN
	1    3850 1400
	0    -1   -1   0   
$EndComp
$Comp
L my_symbols:Pin-Connector U5
U 1 1 646A0B50
P 3950 1400
F 0 "U5" H 3950 1400 50  0001 C CNN
F 1 "Pin-Connector" V 4096 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 3950 1400 50  0001 C CNN
F 3 "" H 3950 1400 50  0001 C CNN
	1    3950 1400
	0    -1   -1   0   
$EndComp
$Comp
L my_symbols:Pin-Connector U6
U 1 1 646A1FF4
P 4350 1400
F 0 "U6" H 4350 1400 50  0001 C CNN
F 1 "Pin-Connector" V 4496 1222 50  0000 R CNN
F 2 "my_footprints:Pin_2mm" H 4350 1400 50  0001 C CNN
F 3 "" H 4350 1400 50  0001 C CNN
	1    4350 1400
	0    -1   -1   0   
$EndComp
Connection ~ 4450 1400
Wire Wire Line
	4450 1400 4450 1750
Wire Wire Line
	4450 1400 4050 1400
Wire Wire Line
	3950 1400 3550 1400
Wire Wire Line
	3450 1400 3050 1400
Wire Wire Line
	4050 1400 4050 1300
Connection ~ 4050 1400
Wire Wire Line
	3950 1400 3950 1300
Connection ~ 3950 1400
Text Notes 3100 1050 0    50   ~ 0
Royer\nsekundär
Text Notes 3650 1050 0    50   ~ 0
Royer 1\nprimär
Text Notes 4150 1050 0    50   ~ 0
Royer 2\nprimär
Wire Wire Line
	5500 3450 5500 3350
Wire Wire Line
	5500 3350 5950 3350
Connection ~ 5950 3350
Wire Wire Line
	5350 3350 5500 3350
Connection ~ 5500 3350
Wire Wire Line
	5500 3750 5500 3850
Wire Wire Line
	5500 3850 5950 3850
Connection ~ 5950 3850
Wire Wire Line
	5950 3850 5950 3900
Wire Wire Line
	5950 3850 6250 3850
Wire Wire Line
	4050 4750 4050 4600
Wire Wire Line
	4050 4600 4200 4600
Wire Wire Line
	4200 4600 4200 4500
Connection ~ 4200 4600
Wire Wire Line
	4200 4200 4200 4100
Wire Wire Line
	4200 3750 4200 3650
Wire Wire Line
	4200 3250 4650 3250
$Comp
L Regulator_Linear:LM317_TO-220 U10
U 1 1 64D17ECB
P 3700 3650
F 0 "U10" H 3700 3892 50  0000 C CNN
F 1 "LM317_TO-220" H 3700 3801 50  0000 C CNN
F 2 "my_footprints:TO220_horizontal" H 3700 3900 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 3700 3650 50  0001 C CNN
	1    3700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3650 4200 3650
Connection ~ 4200 3650
Wire Wire Line
	4200 3650 4200 3250
Wire Wire Line
	3700 3950 3700 4100
Wire Wire Line
	3700 4100 4200 4100
Connection ~ 4200 4100
Wire Wire Line
	4200 4100 4200 4050
Wire Wire Line
	2150 3650 3150 3650
Wire Wire Line
	2150 2400 2150 3650
$Comp
L Diode:1N4001 D2
U 1 1 64D1CDCE
P 3700 3250
F 0 "D2" H 3650 3500 50  0000 L CNN
F 1 "1N4001" H 3550 3400 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3700 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3700 3250 50  0001 C CNN
	1    3700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3250 4200 3250
Connection ~ 4200 3250
Wire Wire Line
	3550 3250 3150 3250
Wire Wire Line
	3150 3250 3150 3650
Connection ~ 3150 3650
Wire Wire Line
	3150 3650 3400 3650
$Comp
L Device:C C5
U 1 1 64D2164C
P 3150 4050
F 0 "C5" H 2900 4000 50  0000 L CNN
F 1 "100nF" H 2850 3900 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 3188 3900 50  0001 C CNN
F 3 "~" H 3150 4050 50  0001 C CNN
	1    3150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3650 3150 3900
$Comp
L power:GND #PWR0102
U 1 1 64D236D4
P 3150 4900
F 0 "#PWR0102" H 3150 4650 50  0001 C CNN
F 1 "GND" H 3155 4727 50  0000 C CNN
F 2 "" H 3150 4900 50  0001 C CNN
F 3 "" H 3150 4900 50  0001 C CNN
	1    3150 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4200 3150 4900
$Comp
L Device:CP C4
U 1 1 64D25526
P 4650 3400
F 0 "C4" H 4768 3446 50  0000 L CNN
F 1 "100µ" H 4768 3355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 4688 3250 50  0001 C CNN
F 3 "~" H 4650 3400 50  0001 C CNN
	1    4650 3400
	1    0    0    -1  
$EndComp
Connection ~ 4650 3250
Wire Wire Line
	4650 3250 4950 3250
$Comp
L power:GND #PWR0103
U 1 1 64D25CE4
P 4650 3900
F 0 "#PWR0103" H 4650 3650 50  0001 C CNN
F 1 "GND" H 4655 3727 50  0000 C CNN
F 2 "" H 4650 3900 50  0001 C CNN
F 3 "" H 4650 3900 50  0001 C CNN
	1    4650 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3900 4650 3550
$Comp
L Device:C C6
U 1 1 648F108D
P 3800 4700
F 0 "C6" H 3550 4650 50  0000 L CNN
F 1 "100nF" H 3500 4550 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 3838 4550 50  0001 C CNN
F 3 "~" H 3800 4700 50  0001 C CNN
	1    3800 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 648F1E9F
P 3800 4900
F 0 "#PWR0105" H 3800 4650 50  0001 C CNN
F 1 "GND" H 3805 4727 50  0000 C CNN
F 2 "" H 3800 4900 50  0001 C CNN
F 3 "" H 3800 4900 50  0001 C CNN
	1    3800 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4900 3800 4850
Wire Wire Line
	3800 4550 3800 4500
Wire Wire Line
	3800 4500 4200 4500
Connection ~ 4200 4500
$EndSCHEMATC

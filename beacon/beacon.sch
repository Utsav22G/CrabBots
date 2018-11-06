EESchema Schematic File Version 4
LIBS:beacon-cache
EELAYER 26 0
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
L MCU_Microchip_ATtiny:ATtiny45-20PU U1
U 1 1 5BDF6537
P 4950 3650
F 0 "U1" H 4600 4200 50  0000 R CNN
F 1 "ATtiny45-20PU" V 4350 3900 50  0000 R CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_Socket" H 4950 3650 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 4950 3650 50  0001 C CNN
	1    4950 3650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5BDF6B40
P 2600 3450
F 0 "SW1" V 2554 3598 50  0000 L CNN
F 1 "SW_Push" V 2645 3598 50  0000 L CNN
F 2 "footprints:push_button" H 2600 3650 50  0001 C CNN
F 3 "" H 2600 3650 50  0001 C CNN
	1    2600 3450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5BDF6F68
P 4950 4250
F 0 "#PWR0101" H 4950 4000 50  0001 C CNN
F 1 "GND" H 4955 4077 50  0000 C CNN
F 2 "" H 4950 4250 50  0001 C CNN
F 3 "" H 4950 4250 50  0001 C CNN
	1    4950 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5BDF7055
P 5600 3250
F 0 "#PWR0102" H 5600 3100 50  0001 C CNN
F 1 "+5V" H 5615 3423 50  0000 C CNN
F 2 "" H 5600 3250 50  0001 C CNN
F 3 "" H 5600 3250 50  0001 C CNN
	1    5600 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5BDF70B0
P 4950 3050
F 0 "#PWR0103" H 4950 2900 50  0001 C CNN
F 1 "+5V" H 4965 3223 50  0000 C CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	1    0    0    -1  
$EndComp
$Comp
L formula:R_200 R2
U 1 1 5BDF762D
P 5850 3450
F 0 "R2" V 5643 3450 50  0000 C CNN
F 1 "R_200" V 5734 3450 50  0000 C CNN
F 2 "footprints:R_0805_OEM" H 5780 3450 50  0001 C CNN
F 3 "https://www.seielect.com/Catalog/SEI-RMCF_RMCP.pdf" H 5930 3450 50  0001 C CNN
F 4 "DK" H 5850 3450 60  0001 C CNN "MFN"
F 5 "RMCF0805JT200RCT-ND" H 5850 3450 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=RMCF0805JT200RCT-ND" H 6330 3850 60  0001 C CNN "PurchasingLink"
	1    5850 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 3350 5600 3350
Wire Wire Line
	5600 3350 5600 3250
NoConn ~ 10300 4500
$Comp
L power:+5V #PWR0104
U 1 1 5BDF7EBD
P 2600 3250
F 0 "#PWR0104" H 2600 3100 50  0001 C CNN
F 1 "+5V" H 2615 3423 50  0000 C CNN
F 2 "" H 2600 3250 50  0001 C CNN
F 3 "" H 2600 3250 50  0001 C CNN
	1    2600 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5BDF7ED6
P 2600 4050
F 0 "#PWR0105" H 2600 3800 50  0001 C CNN
F 1 "GND" H 2605 3877 50  0000 C CNN
F 2 "" H 2600 4050 50  0001 C CNN
F 3 "" H 2600 4050 50  0001 C CNN
	1    2600 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3650 2600 3700
NoConn ~ 5550 3650
NoConn ~ 5550 3750
NoConn ~ 5550 3850
Text Label 2700 3700 0    50   ~ 0
PB2
Wire Wire Line
	2700 3700 2600 3700
Wire Wire Line
	2600 3750 2600 3700
Connection ~ 2600 3700
Text Label 5550 3550 0    50   ~ 0
PB2
$Comp
L formula:R_10K R1
U 1 1 5BDF8DC0
P 2600 3900
F 0 "R1" H 2670 3946 50  0000 L CNN
F 1 "R_10K" H 2670 3855 50  0000 L CNN
F 2 "footprints:R_0805_OEM" H 2530 3900 50  0001 C CNN
F 3 "http://www.bourns.com/data/global/pdfs/CRS.pdf" H 2680 3900 50  0001 C CNN
F 4 "DK" H 2600 3900 60  0001 C CNN "MFN"
F 5 "CRS0805-FX-1002ELFCT-ND" H 2600 3900 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=CRS0805-FX-1002ELFCT-ND" H 3080 4300 60  0001 C CNN "PurchasingLink"
	1    2600 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J1
U 1 1 5BDFA0D8
P 8650 3650
F 0 "J1" H 8677 3676 50  0000 L CNN
F 1 "Conn_01x03_Female" H 8677 3585 50  0000 L CNN
F 2 "footprints:Connector" H 8650 3650 50  0001 C CNN
F 3 "~" H 8650 3650 50  0001 C CNN
	1    8650 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5BDFA26D
P 8350 3400
F 0 "#PWR0106" H 8350 3250 50  0001 C CNN
F 1 "+5V" H 8365 3573 50  0000 C CNN
F 2 "" H 8350 3400 50  0001 C CNN
F 3 "" H 8350 3400 50  0001 C CNN
	1    8350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3450 5700 3450
Text Label 8350 3650 2    50   ~ 0
Data_In
Wire Wire Line
	8350 3550 8350 3450
Wire Wire Line
	8350 3550 8450 3550
Wire Wire Line
	8350 3650 8450 3650
Text Label 6200 3450 0    50   ~ 0
Data_In
Wire Wire Line
	6000 3450 6200 3450
Wire Wire Line
	8450 3750 8350 3750
$Comp
L power:GND #PWR0107
U 1 1 5BDFAAF0
P 8350 3900
F 0 "#PWR0107" H 8350 3650 50  0001 C CNN
F 1 "GND" H 8355 3727 50  0000 C CNN
F 2 "" H 8350 3900 50  0001 C CNN
F 3 "" H 8350 3900 50  0001 C CNN
	1    8350 3900
	1    0    0    -1  
$EndComp
$Comp
L beacon-rescue:C_0.1uF-formula C1
U 1 1 5BDFAE6F
P 7900 3650
F 0 "C1" H 8015 3696 50  0000 L CNN
F 1 "C_0.1uF" H 8015 3605 50  0000 L CNN
F 2 "footprints:C_0805_OEM" H 7938 3500 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 7925 3750 50  0001 C CNN
F 4 "DK" H 7900 3650 60  0001 C CNN "MFN"
F 5 "478-3352-1-ND" H 7900 3650 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=478-3352-1-ND" H 8325 4150 60  0001 C CNN "PurchasingLink"
	1    7900 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 3500 7900 3450
Wire Wire Line
	7900 3450 8350 3450
Connection ~ 8350 3450
Wire Wire Line
	8350 3450 8350 3400
Wire Wire Line
	8350 3750 8350 3850
Wire Wire Line
	7900 3800 7900 3850
Wire Wire Line
	7900 3850 8350 3850
Connection ~ 8350 3850
Wire Wire Line
	8350 3850 8350 3900
Wire Notes Line
	3950 2450 6650 2450
Wire Notes Line
	6650 2450 6650 4700
Wire Notes Line
	6650 4700 3950 4700
Wire Notes Line
	3950 2450 3950 4700
Text Notes 4850 2700 0    118  ~ 24
ATtiny 45
Text Notes 7350 2950 0    118  ~ 24
Connector to NeoPixels
Wire Notes Line
	6950 2700 6950 4250
Wire Notes Line
	6950 4250 9850 4250
Wire Notes Line
	9850 4250 9850 2700
Wire Notes Line
	9850 2700 6950 2700
Text Notes 2150 2800 0    118  ~ 24
Push Button
Wire Notes Line
	1950 2500 3550 2500
Wire Notes Line
	3550 2500 3550 4600
Wire Notes Line
	3550 4600 1950 4600
Wire Notes Line
	1950 4600 1950 2500
$EndSCHEMATC

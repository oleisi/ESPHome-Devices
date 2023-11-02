Register	Beschrieb	0	1	2	3	4	5	6	7	R/W	ESPHome Bemerkung
0x01	Firmware	8-Bit								R	Setup
0x02	Setup	Pin_Edge_Falling	Pin_Edge_Rising	Pin_Edge_Both	Clock_Wakeup	Clock_Sleep	I2C_Sleep			W	Setup
0x03	Sleep Time	16-Bit in Minutes								W	Setup
0x04	Sleep Time										
0x05	Wake Time	16-Bit in Seconds								W	Setup
0x06	Wake Time										
0x07	Voltage	16-Bit in mV								R	Loop/Polling
0x08	Voltage										
0x09	Pin Status	Enable_Pin	Int_Pin							R	Loop/Polling
0x0A	Pin Control	Reset_Enable								W	Loop/Polling
![image](https://github.com/oleisi/ESPHome-Devices/assets/56506925/52be987b-8980-4583-a321-1f8eb4df17b9)

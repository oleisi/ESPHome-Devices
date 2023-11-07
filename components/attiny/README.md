Yaml:
i2c:
  sda: 4
  scl: 5

attiny:
  id: attiny
# Setup Parameter
  address: 0x42         # optional
  WakeUpRising: True    # optional, bool
  WakeUpFalling: True   # optional, bool
  WakeUpClock: True     # optional, bool
  SleepI2C: True        # optional, bool
  SleepClock: True      # optional, bool
  SleepTime: 10         # optonal, int 16-Bit 0-65535sek  
  WakeTime: 10         # optonal, int 16-Bit 0-65535sek

# Inputs, from Attiny
  Voltage:              # optional, sensor
    name: Voltage
    id: voltage
  Sensor:               # optional, binary_sensor
    name: Sensor
    id: sensor
  Enabled:              # optional, binary_sensor
    name: Enabled
    id: enabled

# Outputs, to Attiny
  DeepSleep:            # optional, switch
    
# ------------------------
# i2C Register
0x00.0  WakeUpRising
0x00.1  WakeUpFalling
0x00.2  WakeUpClock
0x00.3  SleepClock
0x00.4  SleepI2C
0x00.5  empty
0x00.6  empty
0x00.7  empty

0x01    SleepTime [s] lsb uint16_t
0x02    SleepTime [s] msb uint16_t
0x03    SleepTime [s] lsb uint16_t
0x04    SleepTime [s] msb uint16_t
0x05    Voltage [mV] lsb uint16_t
0x06    Voltage [mV]  msb uint16_t

0x07.0  Status Enable Pin
0x07.1  Status Interrupt Pin    
0x07.2  empty    
0x07.3  empty    
0x07.4  empty    
0x07.5  empty    
0x07.6  empty    
0x07.7  empty

0x08.0  Reset Enable    
0x08.1  empty         
0x08.2  empty     
0x08.3  empty     
0x08.4  empty     
0x08.5  empty     
0x08.6  empty     
0x08.7  empty   


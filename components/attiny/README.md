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
    


[12:37:33][D][attiny:080]: Data[0]: 26
[12:37:33][D][attiny:081]: Data[1]: 7
[12:37:33][D][attiny:082]: Data[2]: 4
[12:37:33][D][attiny:083]: Data[3]: 3
[12:37:33][D][attiny:084]: Data[4]: 2




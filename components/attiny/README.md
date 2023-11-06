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
  DeepSleep:            @ optional, switch
    







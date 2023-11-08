import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c, binary_sensor, button, output, sensor, switch, text_sensor
from esphome.const import CONF_ID, CONF_STATE, DEVICE_CLASS_VOLTAGE, ICON_FLASH, UNIT_VOLT

MULTI_CONF = True
DEPENDENCIES = ['i2c']

AUTO_LOAD = ['binary_sensor', 'button', 'output', 'sensor', 'switch', 'text_sensor']



CONF_I2C_ADDR = 0x42

attiny_ns = cg.esphome_ns.namespace('attiny')
attiny = attiny_ns.class_('attiny', i2c.I2CDevice, cg.Component)
attinyDeepSleep = attiny_ns.class_("attinyDeepSleep", switch.Switch, cg.Component)

CONF_I2C_ADDR = 0x42
CONF_VOLTAGE = "Voltage"
CONF_SENSOR = "Sensor"
CONF_ENABLED = "Enabled"
CONF_DEEPSLEEP = "DeepSleep"
CONF_DEEPSLEEP_STATUS = "DeepSleepStatus"
PAR_WAKE_UP_RISING = "WakeUpRising"
PAR_WAKE_UP_FALLING = "WakeUpFalling"
PAR_WAKE_UP_CLOCK = "WakeUpClock"
PAR_SLEEP_I2C = "SleepI2C"
PAR_SLEEP_CLOCK = "SleepClock"
PAR_SLEEP_TIME   = "SleepTime"
PAR_WAKE_TIME = "WakeTime"


CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(attiny),
        cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_FLASH,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_VOLTAGE
            ),
        cv.Optional(PAR_WAKE_UP_RISING, default=True): cv.boolean,
        cv.Optional(PAR_WAKE_UP_FALLING, default=True): cv.boolean,
        cv.Optional(PAR_WAKE_UP_CLOCK, default=True): cv.boolean,
        cv.Optional(PAR_SLEEP_I2C, default=True): cv.boolean,
        cv.Optional(PAR_SLEEP_CLOCK, default=True): cv.boolean,
        cv.Optional(PAR_SLEEP_TIME, default=1): cv.int_range(min=0, max=65535),
        cv.Optional(PAR_WAKE_TIME, default=1): cv.int_range(min=0, max=65535),
        cv.Optional(CONF_SENSOR): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_ENABLED): binary_sensor.binary_sensor_schema(),
        #cv.Optional(CONF_DEEPSLEEP_STATUS): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_DEEPSLEEP): switch.SWITCH_SCHEMA.extend({cv.GenerateID(): cv.declare_id(attinyDeepSleep)}),
    }
).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    
    cg.add(var.set_WakeUpRising(config[PAR_WAKE_UP_RISING]))
    cg.add(var.set_WakeUpFalling(config[PAR_WAKE_UP_FALLING]))    
    cg.add(var.set_WakeUpClock(config[PAR_WAKE_UP_CLOCK]))    
    cg.add(var.set_SleepI2C(config[PAR_SLEEP_I2C]))    
    cg.add(var.set_SleepClock(config[PAR_SLEEP_CLOCK]))  
    cg.add(var.set_SleepTime(config[PAR_SLEEP_TIME]))  
    cg.add(var.set_WakeTime(config[PAR_WAKE_TIME]))    

    if CONF_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_VOLTAGE])
        cg.add(var.set_voltage(sens))

    if CONF_SENSOR in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR])
        cg.add(var.set_sensor(sens))   

    if CONF_ENABLED in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_ENABLED])
        cg.add(var.set_enabled(sens))
        
    #if CONF_DEEPSLEEP_STATUS in config:
    #    sens = await binary_sensor.new_binary_sensor(config[CONF_DEEPSLEEP_STATUS])
    #    cg.add(var.set_sleep_status(sens))
    
    if CONF_DEEPSLEEP in config:
        sw = await switch.new_switch(config[CONF_DEEPSLEEP])
        cg.add(sw.set_parent(var))
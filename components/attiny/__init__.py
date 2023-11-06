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
attinyDeepSleep = attiny_ns.class_("Deep Sleep", switch.Switch, cg.Component)

CONF_I2C_ADDR = 0x42
CONF_VOLTAGE = "Voltage"
CONF_SENSOR = "Sensor"
CONF_ENABLED = "Enabled"
CONF_DEEPSLEEP = "DeepSleep"


CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(attiny),
        cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_FLASH,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE
            ),

    }
).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    if CONF_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_VOLTAGE])
        cg.add(var.set_voltage(sens))

    if CONF_SENSOR in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR])
        cg.add(var.set_sensor(sens))   

    if CONF_ENABLED in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_ENABLED])
        cg.add(var.set_enabled(sens))

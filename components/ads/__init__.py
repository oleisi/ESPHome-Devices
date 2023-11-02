import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, i2c, sensor
from esphome.const import (
    CONF_ID, 
    CONF_TRIGGER_ID
)


MULTI_CONF = True

AUTO_LOAD = [ "binary_sensor", "sensor" ]

DEPENDENCIES = ['i2c']

miniencoderc_ns = cg.esphome_ns.namespace('ads')
ads = miniencoderc_ns.class_('ads', i2c.I2CDevice, cg.Component)
CONF_BUTTON = "button"




CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ads),
        cv.Optional(CONF_BUTTON): binary_sensor.binary_sensor_schema(),
    }
).extend(i2c.i2c_device_schema(0x42))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_BUTTON in config:
        button = await binary_sensor.new_binary_sensor(config[CONF_BUTTON])
        cg.add(var.set_button(button))
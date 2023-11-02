import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, i2c, sensor, switch
from esphome.const import (
    CONF_ID, 
    CONF_TRIGGER_ID
)


MULTI_CONF = True

AUTO_LOAD = [ "binary_sensor", "sensor", "switch"]

DEPENDENCIES = ['i2c']

miniencoderc_ns = cg.esphome_ns.namespace('ads')
ads = miniencoderc_ns.class_('ads', i2c.I2CDevice, cg.Component)
CONF_BUTTON_IN = "Input"
CONF_BUTTON_OUT = "Output"
CONF_SWITCH = "Reset"



CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ads),
        cv.Optional(CONF_BUTTON_IN): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_BUTTON_OUT): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_SWITCH): switch.switch_schema(),
    }
).extend(i2c.i2c_device_schema(0x42))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_BUTTON_IN in config:
        button_in = await binary_sensor.new_binary_sensor(config[CONF_BUTTON_IN])
        cg.add(var.set_button(button_in))
    if CONF_BUTTON_OUT in config:
        button_out = await binary_sensor.new_binary_sensor(config[CONF_BUTTON_OUT])
        cg.add(var.set_button(button_out))
    if CONF_SWITCH in config:
        switch = await switch.new_switch(config[CONF_SWITCH])
        cg.add(var.set_button(button_out))
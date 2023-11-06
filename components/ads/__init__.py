import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, i2c, sensor, switch, output
from esphome.const import (
    CONF_ID, 
    CONF_TRIGGER_ID
)


MULTI_CONF = True

AUTO_LOAD = [ 'binary_sensor', 'sensor', 'switch', 'output']

DEPENDENCIES = ['i2c']

ads_ns = cg.esphome_ns.namespace('ads')
ads = ads_ns.class_('ads', i2c.I2CDevice, cg.Component)
adsOutput = ads_ns.class_("adsOutput", output.BinaryOutput)
adsSwitch = ads_ns.class_("adsSwitch", switch.Switch, cg.Component)

CONF_BUTTON_IN = "Input"
CONF_BUTTON_OUT = "Output"
CONF_OUTPUT = "adsOutput"
CONF_SWITCH = "adsSwitch"
CONF_I2C_ADDR = 0x42
CONF_INT_POS = "Interupt positiv Edge"
CONF_INT_NEG = "Interupt negativ Edge"
CONF_CLOCK_WAKEUP = "Clock Wakeup"
CONF_CLOCK_SLEEP = "Clock Sleep"
CONF_I2C_SLEEP = "I2C Sleep"



CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ads),
        cv.Optional(CONF_INT_POS, default=True): cv.boolean,
        cv.Optional(CONF_INT_NEG, default=True): cv.boolean,
        cv.Optional(CONF_CLOCK_WAKEUP, default=True): cv.boolean,
        cv.Optional(CONF_CLOCK_SLEEP, default=True): cv.boolean,
        cv.Optional(CONF_I2C_SLEEP, default=True): cv.boolean,
        cv.Optional(CONF_BUTTON_IN): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_BUTTON_OUT): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_OUTPUT): output.BINARY_OUTPUT_SCHEMA.extend({cv.GenerateID(): cv.declare_id(adsOutput)}),
        cv.Optional(CONF_SWITCH): switch.SWITCH_SCHEMA.extend({cv.GenerateID(): cv.declare_id(adsSwitch)}),
    }
).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

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
    if CONF_OUTPUT in config:
        conf = config[CONF_OUTPUT]
        out = cg.new_Pvariable(conf[CONF_ID])
        await output.register_output(out, conf)
        cg.add(out.set_parent(var))
    if CONF_SWITCH in config:
        sw = await switch.new_switch(config[CONF_SWITCH])
        cg.add(sw.set_parent(var))


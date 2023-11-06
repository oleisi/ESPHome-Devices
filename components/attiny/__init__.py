import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c, binary_sensor, output, sensor, switch
from esphome.const import CONF_ID, CONF_STATE, DEVICE_CLASS_VOLTAGE, ICON_FLASH, UNIT_VOLT

MULTI_CONF = True
DEPENDENCIES = ['i2c']
AUTO_LOAD = ['binary_sensor', 'output', 'sensor', 'switch']

attiny_ns = cg.esphome_ns.namespace('attiny')

attiny = attiny_ns.class_('attiny', cg.Component, uart.UARTDevice)
attinyBOutput = attiny_ns.class_("attinyBOutput", output.BinaryOutput)
attinyFOutput = attiny_ns.class_("attinyFOutput", output.FloatOutput)
attinySwitch = attiny_ns.class_("attinySwitch", switch.Switch, cg.Component)


CONF_THE_SENSOR = "the_sensor"
CONF_THE_BIN_OUTPUT = "the_bin_output"
CONF_THE_FLT_OUTPUT = "the_flt_output"
CONF_THE_BINSENSOR = "the_binsensor"
CONF_THE_SWITCH = "the_switch"
CONF_I2C_ADDR = 0x42

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(attiny),
    cv.Optional(CONF_THE_SENSOR): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        icon=ICON_FLASH,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_VOLTAGE
    ),
    cv.Optional(CONF_THE_BIN_OUTPUT): output.BINARY_OUTPUT_SCHEMA.extend({cv.GenerateID(): cv.declare_id(attinyBOutput)}),
    cv.Optional(CONF_THE_FLT_OUTPUT): output.FLOAT_OUTPUT_SCHEMA.extend({cv.GenerateID(): cv.declare_id(attinyFOutput)}),
    cv.Optional(CONF_THE_BINSENSOR): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_THE_SWITCH): switch.SWITCH_SCHEMA.extend({cv.GenerateID(): cv.declare_id(attinySwitch)}),
}).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_THE_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_THE_SENSOR])
        cg.add(var.set_the_sensor(sens))

    if CONF_THE_BIN_OUTPUT in config:
        conf = config[CONF_THE_BIN_OUTPUT]
        out = cg.new_Pvariable(conf[CONF_ID])
        await output.register_output(out, conf)
        cg.add(out.set_parent(var))

    if CONF_THE_FLT_OUTPUT in config:
        conf = config[CONF_THE_FLT_OUTPUT]
        out = cg.new_Pvariable(conf[CONF_ID])
        await output.register_output(out, conf)
        cg.add(out.set_parent(var))

    if CONF_THE_BINSENSOR in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_THE_BINSENSOR])
        cg.add(var.set_the_binsensor(sens))

    if CONF_THE_SWITCH in config:
        sw = await switch.new_switch(config[CONF_THE_SWITCH])
        cg.add(sw.set_parent(var))


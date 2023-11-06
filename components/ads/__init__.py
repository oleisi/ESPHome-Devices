import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, i2c, sensor, switch, output
from esphome.const import CONF_ID, CONF_STATE, DEVICE_CLASS_VOLTAGE, ICON_FLASH, UNIT_VOLT


MULTI_CONF = True

AUTO_LOAD = [ 'binary_sensor', 'sensor', 'switch', 'output']

DEPENDENCIES = ['i2c']

ads_ns = cg.esphome_ns.namespace('ads')
ads = ads_ns.class_('ads', i2c.I2CDevice, cg.Component)
adsFOutput = ads_ns.class_("adsFOutput", output.FloatOutput)
adsBOutput = ads_ns.class_("adsBOutput", output.BinaryOutput)

CONF_SETUP_BOOl = "Setup Bool"
CONF_SETUP_INT = "Setup INT"
CONF_THE_SENSOR = "the_sensor"
CONF_THE_BIN_OUTPUT = "the_bin_output"
CONF_THE_FLT_OUTPUT = "the_flt_output"
CONF_THE_BINSENSOR = "the_binsensor"
CONF_I2C_ADDR = 0x42





CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ads),
        cv.Optional(CONF_SETUP_BOOl, default=True): cv.boolean,
        cv.Optional(CONF_SETUP_INT, default=1): cv.cv.int_range(min=1, max=65536),
        cv.Optional(CONF_THE_SENSOR): sensor.sensor_schema(
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


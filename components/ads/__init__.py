MULTI_CONF = True

AUTO_LOAD = [ "binary_sensor", "sensor" ]

DEPENDENCIES = ['i2c']

ads_ns = cg.esphome_ns.namespace('ads')
ads = ads_ns.class_('ads', i2c.I2CDevice, cg.Component)
CONF_BUTTON = "Enable"
CONF_Int = "Int"

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ads),
        cv.Optional(CONF_Enable): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_Int): binary_sensor.binary_sensor_schema(),
    }
).extend(i2c.i2c_device_schema(0x42))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_Enable in config:
        button = await binary_sensor.new_binary_sensor(config[CONF_Enable])
        cg.add(var.set_Int(Enable))

    if CONF_Int in config:
        button = await binary_sensor.new_binary_sensor(config[CONF_Int])
        cg.add(var.set_Enable(Enable))
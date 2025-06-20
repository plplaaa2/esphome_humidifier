import esphome.codegen as cg

humidifier_ns = cg.esphome_ns.namespace("humidifier")
Humidifier = humidifier_ns.class_("Humidifier", cg.Component)

import esphome.config_validation as cv
from esphome.components import climate, sensor
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_SENSOR,
)

custom_humidifier_ns = cg.esphome_ns.namespace("custom_humidifier")
CustomHumidifier = custom_humidifier_ns.class_("CustomHumidifier", cg.Component)

CONF_FAN_MODES = "fan_modes"
CONF_MIN_HUMIDITY = "min_humidity"
CONF_MAX_HUMIDITY = "max_humidity"

CONFIG_SCHEMA = climate.climate_schema(
    {
        cv.GenerateID(): cv.declare_id(CustomHumidifier),
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_FAN_MODES, default=["OFF", "LOW", "MEDIUM", "HIGH"]): cv.ensure_list(cv.string),
        cv.Optional(CONF_MIN_HUMIDITY, default=30): cv.int_range(min=0, max=100),
        cv.Optional(CONF_MAX_HUMIDITY, default=80): cv.int_range(min=0, max=100),
    }
).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield climate.register_climate(var, config)
    sens = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_humidity_sensor(sens))
    cg.add(var.set_supported_fan_modes(config[CONF_FAN_MODES]))
    cg.add(var.set_min_humidity(config[CONF_MIN_HUMIDITY]))
    cg.add(var.set_max_humidity(config[CONF_MAX_HUMIDITY]))
    yield cg.register_component(var, config)

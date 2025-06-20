import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, sensor
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_SENSOR,
)

# 고정 팬모드 목록
DEFAULT_FAN_MODES = ["OFF", "LOW", "MEDIUM", "HIGH"]

CONF_MIN_HUMIDITY = "min_humidity"
CONF_MAX_HUMIDITY = "max_humidity"

humidifier_ns = cg.esphome_ns.namespace("humidifier")
Humidifier = humidifier_ns.class_("Humidifier", cg.Component)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(Humidifier),
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_MIN_HUMIDITY, default=30): cv.int_range(min=0, max=100),
        cv.Optional(CONF_MAX_HUMIDITY, default=80): cv.int_range(min=0, max=100),
    }
).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield climate.register_climate(var, config)
    sens = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_humidity_sensor(sens))
    cg.add(var.set_supported_fan_modes(DEFAULT_FAN_MODES))  # 팬모드 고정
    cg.add(var.set_min_humidity(config[CONF_MIN_HUMIDITY]))
    cg.add(var.set_max_humidity(config[CONF_MAX_HUMIDITY]))
    yield cg.register_component(var, config)

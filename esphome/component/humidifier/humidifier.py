import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate
from esphome.const import CONF_ID, CONF_NAME, CONF_FAN_MODES

from . import humidifier_ns, Humidifier

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(Humidifier),
        cv.Required(CONF_NAME): cv.string,
        cv.Optional(CONF_FAN_MODES, default=["OFF", "LOW", "MEDIUM", "HIGH"]): cv.ensure_list(cv.string),
    }
).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield climate.register_climate(var, config)
    cg.add(var.set_supported_fan_modes(config[CONF_FAN_MODES]))
    yield cg.register_component(var, config)

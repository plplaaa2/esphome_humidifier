
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_SENSOR

from . import humidifier_ns, Humidifier

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(Humidifier),
        cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
    }
)

def to_code(config):
    par = yield cg.get_variable(config[CONF_ID])
    sens = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(par.set_humidity_sensor(sens))

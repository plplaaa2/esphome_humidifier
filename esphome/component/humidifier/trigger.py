import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_ON_TURN_ON,
    CONF_ON_TURN_OFF,
    CONF_ON_FAN_MODE,
    CONF_ON_TARGET_HUMIDITY,
)
import esphome.config_validation as cv
from esphome.automation import build_automation

from . import humidifier_ns, Humidifier

def register_humidifier_triggers(config, var):
    if CONF_ON_TURN_ON in config:
        yield build_automation(var.get_turn_on_trigger(), [], config[CONF_ON_TURN_ON])
    if CONF_ON_TURN_OFF in config:
        yield build_automation(var.get_turn_off_trigger(), [], config[CONF_ON_TURN_OFF])
    if CONF_ON_FAN_MODE in config:
        yield build_automation(var.get_fan_mode_trigger(), [(cg.std_string, "x")], config[CONF_ON_FAN_MODE])
    if CONF_ON_TARGET_HUMIDITY in config:
        yield build_automation(var.get_target_humidity_trigger(), [(cg.float_, "x")], config[CONF_ON_TARGET_HUMIDITY])

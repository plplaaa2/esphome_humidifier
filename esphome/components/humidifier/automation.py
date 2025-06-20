import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_FAN_MODE, CONF_TARGET_HUMIDITY
from esphome.automation import register_action

from . import humidifier_ns, Humidifier

HumidifierSetFanModeAction = humidifier_ns.class_(
    "HumidifierSetFanModeAction", cg.Action
)

SET_FAN_MODE_ACTION_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(Humidifier),
        cv.Required(CONF_FAN_MODE): cv.templatable(cv.string),
    }
)

@register_action(
    "humidifier.set_fan_mode",
    HumidifierSetFanModeAction,
    SET_FAN_MODE_ACTION_SCHEMA,
)
async def humidifier_set_fan_mode_action_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    parent = await cg.get_variable(config[CONF_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_fan_mode(config[CONF_FAN_MODE]))
    return var

HumidifierSetTargetHumidityAction = humidifier_ns.class_(
    "HumidifierSetTargetHumidityAction", cg.Action
)

SET_TARGET_HUMIDITY_ACTION_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(Humidifier),
        cv.Required(CONF_TARGET_HUMIDITY): cv.templatable(cv.float_),
    }
)

@register_action(
    "humidifier.set_target_humidity",
    HumidifierSetTargetHumidityAction,
    SET_TARGET_HUMIDITY_ACTION_SCHEMA,
)
async def humidifier_set_target_humidity_action_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    parent = await cg.get_variable(config[CONF_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_target_humidity(config[CONF_TARGET_HUMIDITY]))
    return var

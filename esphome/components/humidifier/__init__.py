import esphome.codegen as cg
from .humidifier import CONFIG_SCHEMA, to_code

CODEOWNERS = ["@plplaaa2"]

humidifier_ns = cg.esphome_ns.namespace("humidifier")
Humidifier = humidifier_ns.class_("Humidifier", cg.Component)

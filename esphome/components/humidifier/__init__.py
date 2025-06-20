import esphome.codegen as cg

CODEOWNERS = ["@plplaaa2"]

humidifier_ns = cg.esphome_ns.namespace("humidifier")
Humidifier = humidifier_ns.class_("Humidifier", cg.Component)

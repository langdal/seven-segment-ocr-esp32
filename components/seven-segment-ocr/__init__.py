import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID, CONF_LAMBDA, CONF_TEXT_SENSORS
import esphome.codegen as cg
custom_ns = cg.esphome_ns.namespace("custom")

SevenSegmentOCRConstructor = custom_ns.class_("SevenSegmentOCRConstructor")

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SevenSegmentOCRConstructor),
        cv.Required(CONF_LAMBDA): cv.returning_lambda,
        cv.Required(CONF_TEXT_SENSORS): cv.ensure_list(
            text_sensor.text_sensor_schema()
        ),
    }
)


async def to_code(config):
    template_ = await cg.process_lambda(
        config[CONF_LAMBDA],
        [],
        return_type=cg.std_vector.template(text_sensor.TextSensorPtr),
    )

    rhs = SevenSegmentOCRConstructor(template_)
    var = cg.variable(config[CONF_ID], rhs)

    for i, conf in enumerate(config[CONF_TEXT_SENSORS]):
        text = cg.Pvariable(conf[CONF_ID], var.get_text_sensor(i))
        await text_sensor.register_text_sensor(text, conf)

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor

seven_segment_ocr_ns = cg.esphome_ns.namespace("seven_segment_ocr")
SevenSegmentOCR = seven_segment_ocr_ns.class_(
    "SevenSegmentOCR", text_sensor.TextSensor, cg.Component
)

CONFIG_SCHEMA = text_sensor.text_sensor_schema(SevenSegmentOCR).extend(
    cv.COMPONENT_SCHEMA
)

async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
    await cg.add_library("vshymanskyy/TinyGSM@0.12.0")

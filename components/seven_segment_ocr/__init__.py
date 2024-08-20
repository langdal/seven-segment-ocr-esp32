import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

CODEOWNERS = ["@langdal"]
DEPENDENCIES = ["esp32_camera"]
MULTI_CONF = True

seven_segment_ocr_ns = cg.esphome_ns.namespace("seven_segment_ocr")
SevenSegmentLCDOCR = seven_segment_ocr_ns.class_("SevenSegmentLCDOCR", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SevenSegmentLCDOCR),
    },
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    server = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(server, config)

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PORT

DEPENDENCIES = ["lvgl"]

lvgl_screenshot_ns = cg.esphome_ns.namespace("lvgl_screenshot")
LvglScreenshot = lvgl_screenshot_ns.class_("LvglScreenshot", cg.Component)

# 定义字节序枚举，对应 C++ 侧的枚举类型
ByteOrder = lvgl_screenshot_ns.enum("ByteOrder")

BYTE_ORDER_OPTIONS = {
    "little_endian": ByteOrder.BYTE_ORDER_LITTLE_ENDIAN,
    "big_endian":    ByteOrder.BYTE_ORDER_BIG_ENDIAN,
}

CONF_BYTE_ORDER = "byte_order"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(LvglScreenshot),
        cv.Optional(CONF_PORT, default=8080): cv.port,
        cv.Optional(CONF_BYTE_ORDER, default="little_endian"): cv.enum(
            BYTE_ORDER_OPTIONS, lower=True
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_port(config[CONF_PORT]))
    cg.add(var.set_byte_order(config[CONF_BYTE_ORDER]))

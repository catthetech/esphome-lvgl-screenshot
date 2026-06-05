#pragma once

#include "esphome/core/component.h"

#ifdef USE_ESP_IDF
#include <esp_http_server.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "lvgl.h"

namespace esphome {
namespace lvgl_screenshot {

// 与 __init__.py 中 BYTE_ORDER_OPTIONS 对应的枚举
enum ByteOrder {
  BYTE_ORDER_LITTLE_ENDIAN,
  BYTE_ORDER_BIG_ENDIAN,
};

class LvglScreenshot : public Component {
 public:
  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::LATE - 10.0f; }
  void set_port(uint16_t port) { port_ = port; }
  void set_byte_order(ByteOrder byte_order) { byte_order_ = byte_order; }  // ✅ 新增

 protected:
  void start_server_();
  void do_capture_();
  static void jpeg_write_cb_(void *ctx, void *data, int size);
  static esp_err_t handle_screenshot_(httpd_req_t *req);

  /// 临时替换的 flush 回调，在此拷贝像素
  static void capture_flush_cb_(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

  static LvglScreenshot *instance_;

  uint16_t port_{8080};
  ByteOrder byte_order_{BYTE_ORDER_LITTLE_ENDIAN};  // ✅ 新增，默认小端
  httpd_handle_t server_{nullptr};
  SemaphoreHandle_t capture_requested_{nullptr};
  SemaphoreHandle_t capture_done_{nullptr};
  volatile bool in_progress_{false};

  uint8_t *rgb_buf_{nullptr};
  uint8_t *jpeg_buf_{nullptr};
  size_t jpeg_capacity_{0};
  size_t jpeg_size_{0};
  uint32_t width_{0};
  uint32_t height_{0};

  // flush 拦截相关
  lv_display_flush_cb_t orig_flush_cb_{nullptr};
  bool flush_captured_{false};
};

}  // namespace lvgl_screenshot
}  // namespace esphome

#endif

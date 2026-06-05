# esphome-lvgl-screenshot
 
## ESPHome LVGL 截图工具组件
- Fork自https://github.com/dcgrove/esphome-lvgl-screenshot
- 修复了原分支在部分界面截图输出花屏的问题
- 针对esphome lvgl 9 适配，不支持旧版lvgl 8
- 内存懒分配，不截图时不占用额外PSRAM
- 全部为 AI Coding
## 使用要求
- 在ESP32-P4+MIPI_DSI 与 ESP32-S3+MIPI_RGB显示器上测试通过
- esphome ver >= 2026.4.0
- LVGL 100% buffer_size
- 截图时帧缓冲拷贝可能占用数MB PSRAM （1280x800分辨率上为4~5M）
- ## 内存余量不足时谨慎使用

## yaml配置

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/gasment/esphome-lvgl-screenshot
      ref: main
    components: [lvgl_screenshot]
    refresh: 24h

lvgl_screenshot:
  port: 8080
  byte_order: little_endian  #如颜色异常，切换到big_endian
```

## 获取截图

访问http 端点
```
http://<device-ip>:8080/screenshot
```


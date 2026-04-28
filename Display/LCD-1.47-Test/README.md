# LCD 1.47英寸 ST7789T 显示测试项目

> 🖥️ 基于 ESP32-C6 的 1.47 英寸 LCD 屏幕驱动与 LVGL 图形界面演示

---

## 📋 项目简介

本项目是一个完整的 ESP32-C6 LCD 显示解决方案，集成了以下功能：

- ✅ **LCD 驱动**: ST7789T 控制器，1.47 英寸 IPS 屏幕
- ✅ **LVGL GUI**: 轻量级图形库，支持按钮、标签、图表等控件
- ✅ **RGB LED**: WS2812 灯带控制，支持多种特效
- ✅ **SD 卡存储**: SPI 接口 SD 卡读写
- ✅ **无线通信**: WiFi/BLE 基础框架

---

## 🎯 硬件需求

### 核心开发板
- **芯片型号**: ESP32-C6
- **Flash**: 4MB
- **PSRAM**: 无（或 2MB）

### 显示模块
- **屏幕尺寸**: 1.47 英寸
- **分辨率**: 172 × 320 像素
- **驱动 IC**: ST7789T (Vernon 定制版本)
- **接口**: SPI (4-line)
- **颜色**: 16-bit RGB (65K colors)

### 其他外设
- **RGB LED**: WS2812B 或兼容型号
- **SD 卡**: MicroSD 卡（SPI 模式）
- **按键**: 可选，用于 UI 交互

---

## 🔌 引脚连接

### LCD 屏幕连接

| LCD 引脚 | ESP32-C6 GPIO | 说明 |
|---------|---------------|------|
| VCC     | 3.3V          | 电源正极 |
| GND     | GND           | 电源地 |
| CS      | GPIO 10       | 片选信号 |
| RESET   | GPIO 8        | 复位信号 |
| DC      | GPIO 9        | 数据/命令选择 |
| SDA(MOSI)| GPIO 6       | SPI 数据输入 |
| SCK     | GPIO 7        | SPI 时钟 |
| LED     | GPIO 5        | 背光控制（PWM） |

### RGB LED 连接

| LED 引脚 | ESP32-C6 GPIO | 说明 |
|---------|---------------|------|
| VCC     | 3.3V / 5V     | 电源 |
| GND     | GND           | 地 |
| DIN     | GPIO 2        | 数据输入 |

### SD 卡连接（SPI 模式）

| SD 卡引脚 | ESP32-C6 GPIO | 说明 |
|----------|---------------|------|
| VCC      | 3.3V          | 电源 |
| GND      | GND           | 地 |
| CS       | GPIO 11       | 片选 |
| MOSI     | GPIO 6        | SPI 数据（与 LCD 共享） |
| MISO     | GPIO 12       | SPI 数据输出 |
| CLK      | GPIO 7        | SPI 时钟（与 LCD 共享） |

> ⚠️ **注意**: LCD 和 SD 卡共享 SPI 总线（MOSI 和 CLK），通过不同的 CS 引脚区分。

---

## 🛠️ 快速开始

### 1. 环境准备

确保已安装 ESP-IDF v5.0+：

```bash
# 检查 ESP-IDF 版本
idf.py --version
```

### 2. 克隆仓库

```bash
git clone https://github.com/FukunHennan/ESP32.git
cd ESP32/Display/LCD-1.47-Test
```

### 3. 设置目标芯片

```bash
idf.py set-target esp32c6
```

### 4. 配置项目（可选）

```bash
idf.py menuconfig
```

常用配置项：
- `Component config → LVGL configuration` - LVGL 参数调整
- `Serial flasher config → Default serial port` - 串口端口设置

### 5. 编译项目

```bash
idf.py build
```

### 6. 烧录固件

```bash
# Windows（替换 COM3 为你的实际端口）
idf.py -p COM3 flash monitor

# Linux/Mac
idf.py -p /dev/ttyUSB0 flash monitor
```

### 7. 查看输出

烧录成功后，你将看到：
- LCD 屏幕点亮并显示 LVGL 示例界面
- 串口输出详细的硬件信息和日志

---

## 📊 项目结构

```
LCD-1.47-Test/
├── main/                    # 应用程序主目录
│   ├── main.c              # 程序入口
│   ├── main_new.c          # 新版主程序（推荐使用）
│   │
│   ├── LCD_Driver/         # LCD 驱动层
│   │   ├── Vernon_ST7789T/ # Vernon 定制驱动
│   │   │   ├── ST7789.c    # 驱动实现
│   │   │   └── ST7789.h    # 驱动头文件
│   │   └── ...
│   │
│   ├── LVGL_Driver/        # LVGL 适配层
│   │   ├── LVGL_Driver.c   # 显示刷新回调
│   │   └── LVGL_Driver.h
│   │
│   ├── LVGL_UI/            # UI 界面逻辑
│   │   ├── LVGL_Example.c  # 示例界面
│   │   └── LVGL_Example.h
│   │
│   ├── RGB/                # RGB LED 控制
│   │   ├── RGB.c
│   │   └── RGB.h
│   │
│   ├── SD_Card/            # SD 卡驱动
│   │   ├── SD_SPI.c
│   │   └── SD_SPI.h
│   │
│   ├── Wireless/           # 无线通信
│   │   ├── Wireless.c
│   │   └── Wireless.h
│   │
│   └── CMakeLists.txt      # 组件构建配置
│
├── components/             # 第三方组件
│   ├── espressif__led_strip/  # LED 灯带驱动
│   └── lvgl__lvgl/            # LVGL 图形库
│
├── CMakeLists.txt          # 项目构建配置
├── sdkconfig.defaults      # 默认配置
├── partitions_singleapp.csv # 分区表
├── README.md               # 本文件
├── build.bat               # 一键编译脚本
└── flash.bat               # 一键烧录脚本
```

---

## 💻 代码示例

### 初始化 LCD 屏幕

```c
#include "ST7789.h"

void app_main(void)
{
    // 初始化 LCD
    ST7789_Init();
    
    // 清屏为黑色
    ST7789_Clear(BLACK);
    
    // 绘制矩形
    ST7789_DrawRectangle(10, 10, 100, 50, RED, true);
    
    // 显示字符串
    ST7789_ShowString(20, 30, "Hello ESP32!", WHITE, BLACK, 16, 0);
}
```

### 使用 LVGL 创建按钮

```c
#include "lvgl.h"

void create_button_example(void)
{
    // 创建按钮
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 120, 50);
    lv_obj_center(btn);
    
    // 添加标签
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Click Me");
    lv_obj_center(label);
    
    // 添加事件回调
    lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED, NULL);
}

static void button_event_handler(lv_event_t *e)
{
    ESP_LOGI(TAG, "Button clicked!");
}
```

### 控制 RGB LED

```c
#include "RGB.h"

void led_demo(void)
{
    // 设置红色
    RGB_SetColor(255, 0, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // 设置绿色
    RGB_SetColor(0, 255, 0);
    vTaskDelay(pdMS_TO_Ticks(1000));
    
    // 设置蓝色
    RGB_SetColor(0, 0, 255);
    vTaskDelay(pdMS_TO_Ticks(1000));
    
    // 彩虹渐变效果
    RGB_RainbowEffect();
}
```

---

## 🔧 常见问题

### Q1: 屏幕不亮怎么办？

**检查清单：**
1. ✅ 确认电源连接正确（3.3V）
2. ✅ 检查 SPI 引脚连接是否正确
3. ✅ 确认 CS、DC、RESET 引脚配置与代码一致
4. ✅ 查看串口日志是否有初始化错误
5. ✅ 尝试调整 SPI 时钟频率（降低速度）

### Q2: LVGL 界面卡顿或刷新慢？

**优化建议：**
- 减小 LVGL 缓冲区大小（在 `lv_conf.h` 中调整）
- 提高 SPI 时钟频率（最高 40MHz）
- 减少同时显示的控件数量
- 使用 DMA 传输（如果硬件支持）

### Q3: SD 卡无法识别？

**排查步骤：**
1. 确认 SD 卡格式化为 FAT32
2. 检查 CS 引脚是否正确（GPIO 11）
3. 确认 MISO 引脚连接（GPIO 12）
4. 查看串口日志中的 SD 卡初始化信息
5. 尝试更换 SD 卡

### Q4: RGB LED 不工作？

**检查要点：**
- 确认数据引脚连接（GPIO 2）
- 检查电源电压（WS2812 需要 5V 或 3.3V）
- 确认 led_strip 组件已正确安装
- 查看日志中是否有 RMT 通道分配错误

---

## 📈 性能指标

| 指标 | 数值 | 说明 |
|-----|------|------|
| SPI 时钟频率 | 40 MHz | LCD 通信速度 |
| LVGL 刷新率 | ~30 FPS | 典型 UI 场景 |
| 内存占用 | ~150 KB | LVGL + 缓冲区 |
| Flash 使用 | ~1.2 MB | 固件大小 |
| RGB LED 数量 | 最多 256 | 受 RMT 内存限制 |

---

## 🔄 更新日志

### v1.0.0 (2026-04-28)
- ✅ 初始版本发布
- ✅ ST7789T LCD 驱动完成
- ✅ LVGL 图形库移植成功
- ✅ RGB LED 控制功能实现
- ✅ SD 卡 SPI 驱动集成
- ✅ WiFi/BLE 基础框架搭建

---

## 📚 相关资源

### 技术文档
- [ST7789T 数据手册](docs/datasheets/ST7789T.pdf)
- [ESP32-C6 技术参考](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_cn.pdf)
- [LVGL 官方文档](https://docs.lvgl.io/)

### 教程链接
- [ESP-IDF 入门指南](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32c6/get-started/index.html)
- [LVGL 快速上手](https://docs.lvgl.io/master/get-started/index.html)

---

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

---

## 📄 许可证

本项目采用 MIT 许可证，详见 [LICENSE](../../LICENSE) 文件。

---

## 📞 联系方式

- **作者**: FukunHennan
- **GitHub**: [https://github.com/FukunHennan](https://github.com/FukunHennan)
- **问题反馈**: [Issues](https://github.com/FukunHennan/ESP32/issues)

---

**祝你使用愉快！** 🎉

*最后更新时间：2026-04-28*

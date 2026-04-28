# ESP32-C6 LCD 1.47 测试项目

## 📋 项目概述

本项目是基于 **ESP32-C6** 芯片的 LCD 显示系统测试平台，集成了 1.47 英寸 ST7789T 驱动液晶显示屏、LVGL 图形库、SD 卡存储、RGB LED 和无线通信功能。

## 🔧 硬件配置

### 核心组件
- **主控芯片**: ESP32-C6（RISC-V 架构）
- **显示屏**: 1.47 英寸 LCD，ST7789T 驱动芯片
- **存储设备**: 
  - SPI Flash（板载）
  - SD 卡（SPI 接口）
- **LED**: WS2812 RGB LED 灯带
- **无线通信**: WiFi 6 + Bluetooth 5 (LE)

### 引脚连接
详见各驱动模块头文件中的引脚定义注释

## 📁 项目结构

```
ESP32-C6-LCD-1.47-Test/
├── main/                      # 主应用程序
│   ├── main_new.c            # 主入口文件（当前使用）
│   ├── main.c                # 旧版主文件（已废弃）
│   ├── LCD_Driver/           # LCD 驱动层
│   │   ├── ST7789.c/h        # ST7789 通用驱动
│   │   └── Vernon_ST7789T/   # Vernon 定制驱动
│   ├── LVGL_Driver/          # LVGL 移植层
│   │   └── LVGL_Driver.c/h   # LVGL 显示和输入驱动
│   ├── LVGL_UI/              # LVGL 用户界面
│   │   └── LVGL_Example.c/h  # UI 示例代码
│   ├── SD_Card/              # SD 卡驱动
│   │   └── SD_SPI.c/h        # SPI 接口 SD 卡驱动
│   ├── RGB/                  # RGB LED 驱动
│   │   └── RGB.c/h           # WS2812 LED 控制
│   └── Wireless/             # 无线通信
│       └── Wireless.c/h      # WiFi 和 BLE 初始化
├── components/               # ESP-IDF 组件
│   ├── espressif__led_strip/ # LED 灯带组件
│   └── lvgl__lvgl/           # LVGL 图形库
├── CMakeLists.txt            # 顶层构建配置
├── sdkconfig                 # ESP-IDF 配置
└── partitions.csv            # 分区表
```

## 🚀 快速开始

### 环境要求
- ESP-IDF v5.0 或更高版本
- Python 3.8+
- CMake 3.16+

### 编译和烧录

```bash
# 设置 ESP-IDF 环境
. $IDF_PATH/export.sh

# 配置项目
idf.py menuconfig

# 编译
idf.py build

# 烧录（替换 PORT 为实际串口）
idf.py -p /dev/ttyUSB0 flash

# 监视输出
idf.py -p /dev/ttyUSB0 monitor
```

## 📝 主要功能

### 1. 系统初始化流程
程序按照以下顺序初始化各模块：
1. **Flash 检测** - 获取 Flash 容量信息
2. **无线模块** - 初始化 WiFi 和 BLE（并行扫描）
3. **RGB LED** - 初始化并运行示例效果
4. **SD 卡** - 初始化 SPI 接口 SD 卡
5. **LCD 显示** - 初始化 ST7789T 液晶屏
6. **LVGL** - 初始化图形库并创建 UI

### 2. LVGL 界面
- 默认显示绿色背景
- 可启用多种演示模式：
  - `Lvgl_Example1()` - 自定义示例（当前启用）
  - `lv_demo_widgets()` - 控件演示
  - `lv_demo_benchmark()` - 性能基准测试
  - `lv_demo_stress()` - 压力测试
  - `lv_demo_music()` - 音乐播放器演示

### 3. 信息显示
UI 实时显示以下信息：
- SD 卡容量
- Flash 容量
- WiFi 扫描结果数量
- BLE 扫描结果数量

## ⚙️ 配置说明

### SPI 总线共享
SD 卡和 LCD 共用同一 SPI 总线，通过不同的片选引脚（CS）区分：
- **LCD CS**: 见 `ST7789.h` 定义
- **SD CS**: 见 `SD_SPI.h` 定义

⚠️ **注意**: SPI 总线只初始化一次，避免资源冲突。

### LVGL 性能优化
如需提高 UI 响应速度：
- 提高 LVGL 任务优先级
- 减少 `lv_timer_handler()` 调用周期（当前为 10ms）

## 📌 注意事项

1. **主文件选择**: 当前使用 `main_new.c` 作为入口，`main.c` 已废弃但保留用于参考
2. **背光控制**: 初始背光亮度设置为 50%，可通过 `BK_Light()` 函数调整
3. **无线扫描**: WiFi 和 BLE 扫描在后台异步进行，`Scan_finish` 标志表示扫描完成
4. **中文日志**: 系统启动时会以中文打印详细硬件信息

## 🔍 调试技巧

### 查看日志
```bash
idf.py monitor
```

### 关键日志标签
- `MAIN` - 主程序启动信息
- `LCD` - LCD 驱动日志
- `LVGL` - 图形库日志
- `WIRELESS` - 无线通信日志
- `SD_CARD` - SD 卡操作日志

## 📖 相关文档

- [ESP-IDF 个人规则](ESP-IDF个人规则.md)
- [ESP-IDF 开发规则](ESP-IDF开发规则.md)
- [优化指南](OPTIMIZATION_GUIDE.md)
- [LVGL 官方文档](https://docs.lvgl.io/)
- [ESP32-C6 技术参考手册](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_cn.pdf)

## 📄 许可证

本项目遵循 CC0-1.0 许可证（参见源文件头部声明）

---

**最后更新**: 2026-04-28

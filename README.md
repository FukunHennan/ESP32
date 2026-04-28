# ESP32 项目开发集合

> 📚 基于 ESP32 系列芯片的学习、实验和开发项目集合

---

## 🎯 项目概览

本仓库包含多个 ESP32 相关的实验项目和开发示例，涵盖显示、无线通信、传感器、物联网等多个领域。所有项目均基于 **ESP-IDF** 框架开发。

### 📊 统计信息
- **项目总数**: 1
- **芯片型号**: ESP32-C6
- **最后更新**: 2026-04-28

---

## 📂 项目分类

### 🖥️ 显示类项目 (Display)

| 项目名称 | 芯片 | 屏幕类型 | 特性 | 状态 |
|---------|------|---------|------|------|
| [LCD-1.47-Test](Display/LCD-1.47-Test/) | ESP32-C6 | ST7789T 1.47" | LVGL GUI, RGB LED, SD卡 | ✅ 完成 |

**快速开始：**
```bash
cd Display/LCD-1.47-Test
idf.py set-target esp32c6
idf.py build flash monitor
```

---

### 📡 无线通信项目 (Wireless) - _待添加_

计划中的项目：
- [ ] WiFi Station 模式连接
- [ ] WiFi AP 热点模式
- [ ] BLE 心率服务
- [ ] BLE Mesh 组网
- [ ] MQTT 客户端

---

### 🌡️ 传感器项目 (Sensors) - _待添加_

计划中的项目：
- [ ] DHT11/DHT22 温湿度
- [ ] BMP280 气压温度
- [ ] MPU6050 六轴陀螺仪
- [ ] BH1750 光照强度

---

### 🏠 物联网应用 (IoT) - _待添加_

计划中的项目：
- [ ] HTTP Web Server
- [ ] MQTT 智能家居
- [ ] OTA 远程升级
- [ ] NTP 时间同步

---

### 🔊 音频项目 (Audio) - _待添加_

计划中的项目：
- [ ] I2S 音频播放
- [ ] 语音录音
- [ ] MP3 解码

---

## 🛠️ 开发环境

### 必需工具
- **ESP-IDF**: v5.0+ （推荐最新稳定版）
- **CMake**: >= 3.16
- **Python**: >= 3.8
- **Git**: >= 2.0

### 环境搭建

1. **安装 ESP-IDF**
   ```bash
   # Windows
   git clone --recursive https://github.com/espressif/esp-idf.git
   cd esp-idf
   install.bat
   export.bat
   ```

2. **克隆本仓库**
   ```bash
   git clone https://github.com/FukunHennan/ESP32.git
   cd ESP32
   ```

3. **选择并编译项目**
   ```bash
   cd Display/LCD-1.47-Test
   idf.py set-target esp32c6
   idf.py build flash monitor
   ```

---

## 📋 通用构建流程

### 编译项目
```bash
# 进入项目目录
cd <分类>/<项目名>

# 设置目标芯片（首次编译需要）
idf.py set-target esp32c6    # 或 esp32s3, esp32c3 等

# 配置项目（可选）
idf.py menuconfig

# 编译
idf.py build
```

### 烧录固件
```bash
# 烧录并监控串口
idf.py -p COM3 flash monitor

# 仅烧录
idf.py -p COM3 flash
```

### 清理构建
```bash
idf.py fullclean
```

---

## 🗂️ 仓库结构

```
ESP32/
├── Display/                 # 显示类项目
│   └── LCD-1.47-Test/      # LCD 1.47英寸测试
│       ├── main/           # 应用程序代码
│       ├── components/     # 项目组件
│       ├── CMakeLists.txt  # 构建配置
│       └── README.md       # 项目说明
│
├── Wireless/                # 无线通信项目（待创建）
├── Sensors/                 # 传感器项目（待创建）
├── IoT/                     # 物联网应用（待创建）
├── Audio/                   # 音频项目（待创建）
│
├── Common/                  # 共享资源（待创建）
│   ├── drivers/            # 通用驱动
│   ├── utils/              # 工具函数
│   └── configs/            # 配置模板
│
├── docs/                    # 文档（待创建）
│   ├── tutorials/          # 教程
│   └── notes/              # 学习笔记
│
├── tools/                   # 工具脚本（待创建）
│   ├── build_all.bat       # 批量编译
│   └── flash_selector.bat  # 烧录选择器
│
├── .gitignore              # Git 忽略规则
├── README.md               # 本文件
└── PROJECT_CLEANUP.md      # 项目整理记录
```

---

## 💡 最佳实践

### 1. 项目管理
- ✅ 每个项目独立在子目录中
- ✅ 每个项目有自己的 README 说明
- ✅ 使用分类目录组织不同类型项目
- ✅ 定期更新总览文档

### 2. 代码规范
- ✅ 遵循 ESP-IDF 编码规范
- ✅ 关键注释使用中文
- ✅ 打印详细的硬件信息（符合用户偏好）
- ✅ 合理的错误处理和日志输出

### 3. Git 工作流
- ✅ 每个功能修改单独提交
- ✅ 清晰的提交信息
- ✅ 定期推送到远程仓库
- ✅ 重要更改创建分支

### 4. 硬件适配
- ✅ 明确标注使用的芯片型号
- ✅ 详细列出引脚连接
- ✅ 提供电路图和接线说明
- ✅ 记录 SPI/I2C 总线使用情况

---

## 📝 添加新项目指南

### 步骤 1: 创建项目目录
```bash
mkdir -p <分类>/<项目名>
cd <分类>/<项目名>
```

### 步骤 2: 初始化 ESP-IDF 项目
```bash
idf.py create-project .
idf.py set-target <芯片型号>
```

### 步骤 3: 编写代码
- 在 `main/` 目录下编写主程序
- 添加必要的组件依赖
- 创建项目 README

### 步骤 4: 提交到 Git
```bash
cd ../../..  # 回到根目录
git add <分类>/<项目名>/
git commit -m "添加新项目：<项目名>"
git push
```

### 步骤 5: 更新总览文档
编辑根目录的 `README.md`，在对应分类中添加新项目信息。

---

## 🔗 相关资源

### 官方文档
- [ESP-IDF 编程指南](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32c6/index.html)
- [ESP32-C6 技术参考手册](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_cn.pdf)
- [LVGL 文档](https://docs.lvgl.io/)

### 学习资源
- [ESP32 官方示例](https://github.com/espressif/esp-idf/tree/master/examples)
- [LVGL 示例集合](https://github.com/lvgl/lv_examples)
- [Arduino ESP32](https://github.com/espressif/arduino-esp32)

### 社区支持
- [ESP32 中文论坛](https://www.esp32.com/)
- [GitHub Issues](https://github.com/FukunHennan/ESP32/issues)

---

## 📞 联系方式

- **GitHub**: [FukunHennan](https://github.com/FukunHennan)
- **仓库**: [ESP32 Projects](https://github.com/FukunHennan/ESP32)

---

## 📄 许可证

本项目采用 MIT 许可证，详见 [LICENSE](LICENSE) 文件。

---

**祝你开发愉快！** 🚀

*最后更新时间：2026-04-28*

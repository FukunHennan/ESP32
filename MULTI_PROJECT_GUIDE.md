# ESP32 多项目管理完整指南

> 📚 如何在一个仓库中高效管理多个 ESP32 项目

---

## ✅ 已完成的重构

我们已经成功将你的 ESP32 仓库重构为**分类目录结构**，现在可以轻松地管理多个项目！

### 📊 当前结构

```
ESP32/
├── Display/                    # 🖥️ 显示类项目
│   └── LCD-1.47-Test/         #   ├─ LCD 1.47英寸测试（已完成）
│       ├── main/              #   │  ├─ 应用程序代码
│       ├── components/        #   │  ├─ 第三方组件
│       ├── CMakeLists.txt     #   │  ├─ 构建配置
│       └── README.md          #   │  └─ 项目说明
│
├── Wireless/                   # 📡 无线通信项目（待创建）
├── Sensors/                    # 🌡️ 传感器项目（待创建）
├── IoT/                        # 🏠 物联网应用（待创建）
├── Audio/                      # 🔊 音频项目（待创建）
│
├── Common/                     # 📦 共享资源（待创建）
│   ├── drivers/               #   ├─ 通用驱动
│   ├── utils/                 #   ├─ 工具函数
│   └── configs/               #   └─ 配置模板
│
├── tools/                      # 🛠️ 工具脚本
│   └── project_selector.bat   #   └─ 智能项目选择器
│
├── docs/                       # 📖 文档（待创建）
├── README.md                   # 📋 总览文档
└── .gitignore                  # ⚙️ Git 忽略规则
```

---

## 🎯 多项目管理的核心优势

### 1️⃣ **清晰的分类组织**
- ✅ 按功能类型分组（Display、Wireless、Sensors 等）
- ✅ 每个项目独立在子目录中
- ✅ 易于查找和导航

### 2️⃣ **统一的文档系统**
- ✅ 根目录 README：总览所有项目
- ✅ 项目级 README：详细说明每个项目
- ✅ 标准化的文档格式

### 3️⃣ **便捷的构建工具**
- ✅ 智能项目选择器（`tools/project_selector.bat`）
- ✅ 一键编译、烧录、监控
- ✅ 自动扫描可用项目

### 4️⃣ **高效的 Git 管理**
- ✅ 单一仓库，统一版本控制
- ✅ 清晰的提交历史
- ✅ 支持分支策略

---

## 🚀 添加新项目的标准流程

### 步骤 1: 确定项目分类

根据你的项目类型，选择合适的分类目录：

| 分类 | 目录 | 示例项目 |
|-----|------|---------|
| 显示类 | `Display/` | LCD、OLED、ePaper |
| 无线通信 | `Wireless/` | WiFi、BLE、LoRa |
| 传感器 | `Sensors/` | 温湿度、气压、陀螺仪 |
| 物联网 | `IoT/` | MQTT、HTTP、OTA |
| 音频 | `Audio/` | I2S、MP3、录音 |

如果没有合适的分类，可以创建新的分类目录。

### 步骤 2: 创建项目目录

```bash
# 示例：创建 WiFi 连接测试项目
mkdir -p Wireless/WiFi-Connect-Test
cd Wireless/WiFi-Connect-Test
```

### 步骤 3: 初始化 ESP-IDF 项目

```bash
# 方法 A：使用 ESP-IDF 命令
idf.py create-project .

# 方法 B：手动创建基本结构
mkdir main
touch main/main.c
touch main/CMakeLists.txt
touch CMakeLists.txt
```

### 步骤 4: 编写项目代码

在 `main/` 目录下编写你的应用程序：

```c
// main/main.c
#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "WiFi-Connect";

void app_main(void)
{
    ESP_LOGI(TAG, "================================");
    ESP_LOGI(TAG, "  WiFi 连接测试项目");
    ESP_LOGI(TAG, "  芯片型号: ESP32-C6");
    ESP_LOGI(TAG, "================================");
    
    // 你的代码...
}
```

### 步骤 5: 创建项目 README

在项目根目录创建 `README.md`：

```markdown
# WiFi 连接测试项目

## 项目简介
测试 ESP32-C6 的 WiFi Station 模式连接功能。

## 硬件需求
- ESP32-C6 开发板

## 功能特性
- WiFi 扫描
- 连接到指定 AP
- 获取 IP 地址

## 编译烧录
```bash
cd Wireless/WiFi-Connect-Test
idf.py set-target esp32c6
idf.py build flash monitor
```
```

### 步骤 6: 提交到 Git

```bash
# 回到仓库根目录
cd ../..

# 添加新项目
git add Wireless/WiFi-Connect-Test/

# 提交
git commit -m "添加新项目：WiFi 连接测试

- 实现 WiFi Station 模式
- 支持自动重连
- 详细的日志输出"

# 推送
git push
```

### 步骤 7: 更新总览文档

编辑根目录的 `README.md`，在对应分类中添加新项目：

```markdown
### 📡 无线通信项目 (Wireless)

| 项目名称 | 芯片 | 功能 | 状态 |
|---------|------|------|------|
| [WiFi-Connect-Test](Wireless/WiFi-Connect-Test/) | ESP32-C6 | WiFi Station 连接 | ✅ 完成 |
```

---

## 🛠️ 使用项目选择器工具

我们创建了智能项目选择器，让你无需手动切换目录：

### 运行选择器

```bash
# 在仓库根目录执行
tools\project_selector.bat
```

### 功能特性

选择器会自动：
1. ✅ 扫描所有分类目录下的项目
2. ✅ 以编号列表形式展示
3. ✅ 支持多种操作：
   - 编译项目
   - 烧录固件
   - 烧录并监控
   - 清理构建
   - 查看 README

### 使用示例

```
📂 可用项目列表：

【🖥️ 显示类项目】
  [1] LCD-1.47-Test

【📡 无线通信项目】
  [2] WiFi-Connect-Test

────────────────────────────────────────
请输入项目编号进行选择: 1
✅ 已选择: Display/LCD-1.47-Test

🔧 请选择操作：
  [1] 编译项目 (build)
  [2] 烧录固件 (flash)
  [3] 烧录并监控 (flash + monitor)
  [4] 清理构建 (clean)
  [5] 查看项目 README

请输入操作编号: 3
```

---

## 💡 最佳实践建议

### 1. 项目命名规范

**推荐格式：** `<功能>-<具体描述>`

✅ 好的命名：
- `LCD-1.47-Test`
- `WiFi-Station-Mode`
- `DHT11-Temperature`
- `MQTT-SmartHome`

❌ 避免的命名：
- `test1`
- `my_project`
- `new_lcd`
- `wifi`

### 2. 目录结构规范

每个项目应包含：

```
项目名/
├── main/                # 必须：应用程序代码
│   ├── main.c          # 必须：主程序入口
│   ├── CMakeLists.txt  # 必须：组件配置
│   └── ...             # 其他源文件
├── components/          # 可选：项目专属组件
├── CMakeLists.txt       # 必须：项目构建配置
├── sdkconfig.defaults   # 可选：默认配置
├── README.md            # 强烈建议：项目说明
└── ...                  # 其他配置文件
```

### 3. README 编写要点

每个项目的 README 应包含：

- ✅ **项目简介**：一句话说明项目功能
- ✅ **硬件需求**：列出所需的开发板和外设
- ✅ **引脚连接**：详细的接线表格
- ✅ **快速开始**：编译和烧录步骤
- ✅ **代码示例**：关键功能的代码片段
- ✅ **常见问题**：FAQ 和故障排查

### 4. Git 提交规范

**提交信息格式：**

```
<类型>: <简短描述>

<详细说明>
- 功能点 1
- 功能点 2

相关 Issue: #123
```

**类型说明：**
- `feat`: 新功能
- `fix`: 修复 bug
- `docs`: 文档更新
- `style`: 代码格式
- `refactor`: 重构
- `test`: 测试相关
- `chore`: 构建/工具

**示例：**

```bash
git commit -m "feat: 添加 WiFi 自动重连功能

- 实现断线检测
- 支持指数退避重连
- 添加重连次数统计

相关 Issue: #5"
```

### 5. 分支管理策略

**简单项目（单人开发）：**
```
main          # 主分支，稳定版本
└── dev       # 开发分支，日常开发
```

**复杂项目（多人协作）：**
```
main                    # 主分支
├── feature/wifi-mgr    # 功能分支
├── feature/lcd-driver  # 功能分支
└── bugfix/spi-issue   # Bug 修复分支
```

---

## 📈 扩展建议

随着项目数量增加，可以考虑以下增强：

### 1. 创建共享组件库

```
Common/
├── drivers/
│   ├── lcd/              # 通用 LCD 驱动框架
│   │   ├── st7789/
│   │   ├── ili9341/
│   │   └── ssd1306/
│   └── sensors/          # 通用传感器驱动
│       ├── dht/
│       └── bmp280/
└── utils/
    ├── log_helper.c      # 日志辅助
    └── gpio_helper.c     # GPIO 辅助
```

**项目引用方式：**

```cmake
# 在项目的 CMakeLists.txt 中
set(EXTRA_COMPONENT_DIRS
    ../../Common/drivers/lcd/st7789
    ../../Common/utils
)
```

### 2. 自动化测试框架

```
tests/
├── run_all_tests.bat     # 批量测试
├── test_template.py      # 测试模板
└── results/              # 测试结果
```

### 3. CI/CD 集成

创建 `.github/workflows/build.yml`：

```yaml
name: Build ESP32 Projects

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Build projects
        run: |
          for project in Display/*/ Wireless/*/; do
            cd $project
            idf.py build
            cd ../..
          done
```

### 4. 文档站点

使用 MkDocs 或 GitBook 创建在线文档：

```
docs/
├── index.md              # 首页
├── getting-started.md    # 入门指南
├── projects/             # 项目文档
│   ├── lcd-1.47.md
│   └── wifi-connect.md
└── api-reference.md      # API 参考
```

---

## 🔍 常见问题解答

### Q1: 项目太多，根目录 README 太长怎么办？

**解决方案：**
- 使用折叠区块（GitHub 支持 HTML details 标签）
- 创建分类索引页面
- 使用表格代替详细列表

### Q2: 不同项目使用不同的 ESP-IDF 版本怎么办？

**解决方案：**
- 在每个项目中添加 `.esp-idf-version` 文件
- 使用 Docker 容器隔离环境
- 在 README 中明确标注所需版本

### Q3: 如何在项目间共享代码？

**解决方案：**
- 使用 `Common/` 目录存放共享代码
- 通过 `EXTRA_COMPONENT_DIRS` 引用
- 或者创建独立的 Git 子模块

### Q4: 编译某个项目时影响其他项目吗？

**不会！** 每个项目的构建产物都在各自的 `build/` 目录中，完全独立。

### Q5: 如何备份整个仓库？

```bash
# 方法 1：推送到 GitHub（推荐）
git push

# 方法 2：创建压缩包
tar -czf esp32-backup.tar.gz ESP32/

# 方法 3：克隆到另一个位置
git clone ESP32 ESP32-backup
```

---

## 📊 项目统计模板

你可以在根目录 README 中添加统计信息：

```markdown
## 📊 项目统计

- **总项目数**: 1
- **已完成**: 1
- **进行中**: 0
- **计划中**: 5

### 按分类统计

| 分类 | 项目数 | 完成率 |
|-----|--------|--------|
| Display | 1 | 100% |
| Wireless | 0 | 0% |
| Sensors | 0 | 0% |
| IoT | 0 | 0% |
| Audio | 0 | 0% |
```

---

## 🎓 学习路径建议

基于多项目管理，建议的学习顺序：

### 初级阶段（1-2 个月）
1. ✅ LCD 显示基础（已完成）
2. 📝 LED 控制（RGB、PWM）
3. 📝 GPIO 输入输出
4. 📝 UART 串口通信

### 中级阶段（2-3 个月）
5. 📝 WiFi Station/AP 模式
6. 📝 BLE 基础通信
7. 📝 SPI/I2C 外设驱动
8. 📝 SD 卡文件系统

### 高级阶段（3-6 个月）
9. 📝 LVGL 高级 UI 设计
10. 📝 MQTT 物联网协议
11. 📝 OTA 远程升级
12. 📝 低功耗优化

---

## 🎉 总结

通过采用**分类目录结构**，你现在可以：

✅ **轻松管理**数十个 ESP32 项目  
✅ **快速查找**特定类型的项目  
✅ **高效复用**共享组件和代码  
✅ **清晰记录**每个项目的细节  
✅ **便捷构建**使用智能选择器  

**下一步：**
1. 尝试添加你的第二个项目
2. 使用 `tools/project_selector.bat` 体验便捷的项目切换
3. 按照本指南的标准流程创建新项目

---

**祝你项目开发顺利！** 🚀

*最后更新：2026-04-28*

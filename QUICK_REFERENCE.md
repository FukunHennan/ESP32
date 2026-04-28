# ⚡ ESP32 多项目管理 - 快速参考

> 📌 常用命令和操作流程速查表

---

## 🎯 核心目录结构

```
ESP32/
├── Display/          # 显示类项目
├── Wireless/         # 无线通信项目
├── Sensors/          # 传感器项目
├── IoT/              # 物联网应用
├── Audio/            # 音频项目
├── Common/           # 共享资源
├── tools/            # 工具脚本
└── README.md         # 总览文档
```

---

## 🚀 快速开始新项目

### 1️⃣ 创建项目目录
```bash
mkdir -p <分类>/<项目名>
cd <分类>/<项目名>
```

### 2️⃣ 初始化项目
```bash
idf.py create-project .
idf.py set-target esp32c6
```

### 3️⃣ 编写代码
```
main/
├── main.c
└── CMakeLists.txt
```

### 4️⃣ 创建 README
```bash
echo "# 项目名" > README.md
```

### 5️⃣ 提交到 Git
```bash
cd ../..
git add <分类>/<项目名>/
git commit -m "feat: 添加新项目 <项目名>"
git push
```

---

## 🛠️ 常用命令

### 编译项目
```bash
cd <分类>/<项目名>
idf.py build
```

### 烧录固件
```bash
idf.py -p COM3 flash monitor
```

### 清理构建
```bash
idf.py fullclean
```

### 使用项目选择器（推荐）
```bash
tools\project_selector.bat
```

---

## 📝 Git 工作流

### 日常提交
```bash
git add .
git commit -m "fix: 修复 LCD 驱动问题"
git push
```

### 查看状态
```bash
git status
git log --oneline
```

### 创建分支
```bash
git checkout -b feature/new-project
# 开发...
git commit -m "feat: 完成新功能"
git checkout main
git merge feature/new-project
git push
```

---

## 📋 项目命名规范

**格式：** `<功能>-<描述>`

✅ **推荐：**
- `LCD-1.47-Test`
- `WiFi-Station-Mode`
- `DHT11-Temp-Sensor`
- `MQTT-SmartHome`

❌ **避免：**
- `test1`
- `my_project`
- `new`

---

## 📖 README 模板

```markdown
# 项目名称

## 简介
一句话说明项目功能。

## 硬件需求
- ESP32-C6 开发板
- 外设列表

## 引脚连接
| 外设 | GPIO | 说明 |
|-----|------|------|
| LED | 2    | RGB LED |

## 快速开始
```bash
idf.py set-target esp32c6
idf.py build flash monitor
```

## 功能特性
- ✅ 功能 1
- ✅ 功能 2
```

---

## 🔧 故障排查

### 编译失败
```bash
# 清理后重新编译
idf.py fullclean
idf.py build
```

### 烧录失败
```bash
# 检查端口
# Windows: 设备管理器 → 端口
# 更换端口重试
idf.py -p COM4 flash
```

### Git 推送失败
```bash
# 临时禁用代理
git -c http.proxy= -c https.proxy= push
```

---

## 📊 项目统计

更新根目录 README 中的统计信息：

```markdown
- **总项目数**: X
- **已完成**: Y
- **进行中**: Z
```

---

## 💡 最佳实践

### ✅ 要做的事
- 每个项目都有 README
- 详细的引脚连接表格
- 清晰的提交信息
- 定期推送到 GitHub
- 使用中文注释

### ❌ 避免的事
- 在项目间硬编码路径
- 忽略 .gitignore
- 提交 build/ 目录
- 模糊的提交信息
- 缺少文档

---

## 🔗 相关链接

- **仓库地址**: https://github.com/FukunHennan/ESP32
- **ESP-IDF 文档**: https://docs.espressif.com/projects/esp-idf/
- **LVGL 文档**: https://docs.lvgl.io/
- **完整指南**: [MULTI_PROJECT_GUIDE.md](MULTI_PROJECT_GUIDE.md)

---

**快速上手，高效开发！** 🚀

*最后更新：2026-04-28*

# ESP-IDF 开发规则

## 环境配置

### ESP-IDF 版本
- ESP-IDF 6.0：`D:\esp\v6.0\esp-idf`
- ESP-IDF 5.5：`D:\esp5.5\v5.5\esp-idf`

### 环境激活
```powershell
# 激活 ESP-IDF 6.0
& "D:\esp\v6.0\esp-idf\export.ps1"

# 激活 ESP-IDF 5.5
& "D:\esp5.5\v5.5\esp-idf\export.ps1"
```

## 开发流程

### 1. 检查串口设备
```powershell
mode
```

### 2. 进入项目目录
```powershell
cd C:\Users\chen1\Desktop\ESP32-C6-LCD-1.47-Test
```

### 3. 设置目标芯片
```powershell
idf.py set-target esp32c6
```

### 4. 编译项目
```powershell
idf.py build
```

### 5. 烧录项目
```powershell
# 替换 COM42 为实际串口
idf.py -p COM42 flash
```

### 6. 打开监视器
```powershell
idf.py -p COM42 monitor
```

## 一键编译和烧录
```powershell
& "D:\esp\v6.0\esp-idf\export.ps1" ; idf.py -p COM42 flash
```

## 常用命令

| 命令 | 说明 |
|------|------|
| `idf.py set-target esp32c6` | 设置目标芯片为 ESP32-C6 |
| `idf.py build` | 编译项目 |
| `idf.py clean` | 清理编译文件 |
| `idf.py fullclean` | 完全清理 |
| `idf.py menuconfig` | 打开配置菜单 |
| `idf.py -p COM42 flash` | 烧录到 COM42 |
| `idf.py -p COM42 monitor` | 打开串口监视器 |
| `idf.py -p COM42 flash monitor` | 一键烧录+监视 |

## 注意事项

1. **必须使用 PowerShell**，CMD 不支持此配置
2. **每次打开新窗口需要重新激活**环境
3. **路径不要有中文或空格**
4. **切换版本前建议关闭之前的编译窗口**，避免环境变量冲突
5. **烧录前确保设备已连接**并识别到正确的串口

## 设备信息

- 芯片类型：ESP32-C6FH8 (QFN32)
- 特性：Wi-Fi 6, BT 5 (LE), IEEE802.15.4
- 嵌入式闪存：8MB

## 故障排除

### 常见错误
1. **idf.py 命令未找到**：环境未激活
2. **串口连接失败**：检查设备连接和驱动
3. **编译错误**：检查代码语法和依赖

### 解决方案
- 确保正确激活 ESP-IDF 环境
- 使用 `mode` 命令确认串口设备
- 检查项目配置和依赖

---

*创建时间：2026-04-04*
*更新时间：2026-04-04*

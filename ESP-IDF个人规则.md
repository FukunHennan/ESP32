# ESP-IDF 开发规则

## 环境配置
- ESP-IDF 6.0：`D:\esp\v6.0\esp-idf`
- ESP-IDF 5.5：`D:\esp5.5\v5.5\esp-idf`

## 环境激活
```powershell
# 激活 ESP-IDF 6.0
& "D:\esp\v6.0\esp-idf\export.ps1"

# 激活 ESP-IDF 5.5
& "D:\esp5.5\v5.5\esp-idf\export.ps1"
```

## 开发流程
1. **检查串口**：`mode`
2. **进入项目**：`cd 项目路径`
3. **设置芯片**：`idf.py set-target [芯片型号]`
4. **编译**：`idf.py build`
5. **烧录**：`idf.py -p [串口] flash`
6. **监视**：`idf.py -p [串口] monitor`

## 一键操作
```powershell
& "D:\esp\v6.0\esp-idf\export.ps1" ; idf.py -p [串口] flash
```

## 常用命令
- `idf.py set-target [芯片型号]`：设置芯片
- `idf.py build`：编译
- `idf.py clean`：清理
- `idf.py fullclean`：完全清理
- `idf.py menuconfig`：配置菜单
- `idf.py -p [串口] flash`：烧录
- `idf.py -p [串口] monitor`：监视
- `idf.py -p [串口] flash monitor`：烧录+监视

## 注意事项
1. **使用 PowerShell**，CMD 不支持
2. **每次新窗口需重新激活**环境
3. **路径不要有中文或空格**
4. **切换版本前关闭之前窗口**
5. **烧录前确保设备已连接**

## 故障排除
- **idf.py 未找到**：环境未激活
- **串口连接失败**：检查连接和驱动
- **编译错误**：检查代码语法和依赖

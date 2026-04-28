@echo off
echo ========================================
echo ESP32-C6 LCD 项目烧录脚本
echo ========================================
echo.

REM 检查参数
if "%1"=="" (
    echo [错误] 请指定串口端口号
    echo.
    echo 用法: flash.bat COM_PORT
    echo 示例: flash.bat COM3
    echo.
    echo 可用的串口端口:
    mode
    echo.
    pause
    exit /b 1
)

REM 检查 ESP-IDF 环境
where idf.py >nul 2>&1
if %errorlevel% neq 0 (
    echo [错误] 未检测到 ESP-IDF 环境
    echo.
    echo 请先运行 ESP-IDF 命令提示符，或执行:
    echo   call %IDF_PATH%\export.bat
    echo.
    pause
    exit /b 1
)

set COM_PORT=%1

echo [信息] 使用串口: %COM_PORT%
echo.

REM 烧录固件
echo [步骤 1/2] 正在烧录固件...
idf.py -p %COM_PORT% flash
if %errorlevel% neq 0 (
    echo.
    echo [错误] 烧录失败！请检查:
    echo   1. 串口端口号是否正确
    echo   2. 开发板是否已连接
    echo   3. 驱动程序是否已安装
    pause
    exit /b 1
)
echo.

REM 启动监视器
echo [步骤 2/2] 启动串口监视器...
echo 按 Ctrl+] 退出监视器
echo.
idf.py -p %COM_PORT% monitor

@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: ========================================
:: ESP32 项目烧录选择器
:: ========================================

echo.
echo ╔════════════════════════════════════════╗
echo ║     ESP32 项目构建与烧录工具          ║
echo ╚════════════════════════════════════════╝
echo.

:: 扫描并列出所有项目
echo 📂 可用项目列表：
echo.

set project_count=0

:: 显示类项目
if exist "Display" (
    echo 【🖥️ 显示类项目】
    for /d %%i in (Display\*) do (
        set /a project_count+=1
        echo   [!project_count!] %%~nxi
        set "project_!project_count!=%%i"
    )
    echo.
)

:: 无线类项目
if exist "Wireless" (
    echo 【📡 无线通信项目】
    for /d %%i in (Wireless\*) do (
        set /a project_count+=1
        echo   [!project_count!] %%~nxi
        set "project_!project_count!=%%i"
    )
    echo.
)

:: 传感器项目
if exist "Sensors" (
    echo 【🌡️ 传感器项目】
    for /d %%i in (Sensors\*) do (
        set /a project_count+=1
        echo   [!project_count!] %%~nxi
        set "project_!project_count!=%%i"
    )
    echo.
)

:: IoT 项目
if exist "IoT" (
    echo 【🏠 物联网项目】
    for /d %%i in (IoT\*) do (
        set /a project_count+=1
        echo   [!project_count!] %%~nxi
        set "project_!project_count!=%%i"
    )
    echo.
)

:: 音频项目
if exist "Audio" (
    echo 【🔊 音频项目】
    for /d %%i in (Audio\*) do (
        set /a project_count+=1
        echo   [!project_count!] %%~nxi
        set "project_!project_count!=%%i"
    )
    echo.
)

if !project_count! equ 0 (
    echo ❌ 未找到任何项目！
    pause
    exit /b 1
)

echo ────────────────────────────────────────
echo.

:: 选择项目
set /p choice="请输入项目编号进行选择: "

if "!project_%choice%!"=="" (
    echo ❌ 无效的项目编号！
    pause
    exit /b 1
)

set selected_project=!project_%choice%!
echo ✅ 已选择: %selected_project%
echo.

:: 选择操作
echo 🔧 请选择操作：
echo   [1] 编译项目 (build)
echo   [2] 烧录固件 (flash)
echo   [3] 烧录并监控 (flash + monitor)
echo   [4] 清理构建 (clean)
echo   [5] 查看项目 README
echo.

set /p action="请输入操作编号: "

echo.
echo ⏳ 正在执行，请稍候...
echo.

cd "%selected_project%"

if "%action%"=="1" (
    echo 📦 正在编译项目...
    idf.py build
    
) else if "%action%"=="2" (
    set /p port="请输入串口端口 (例如 COM3): "
    echo 🔥 正在烧录固件到 !port!...
    idf.py -p !port! flash
    
) else if "%action%"=="3" (
    set /p port="请输入串口端口 (例如 COM3): "
    echo 🔥 正在烧录并监控 !port!...
    echo 💡 提示: 按 Ctrl+] 退出监控
    timeout /t 2 /nobreak >nul
    idf.py -p !port! flash monitor
    
) else if "%action%"=="4" (
    echo 🧹 正在清理构建文件...
    idf.py fullclean
    
) else if "%action%"=="5" (
    if exist "README.md" (
        start "" "README.md"
        echo 📖 已打开项目说明文档
    ) else (
        echo ⚠️  该项目没有 README.md 文件
    )
    
) else (
    echo ❌ 无效的操作编号！
)

echo.
cd ..\..
pause

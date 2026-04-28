@echo off
echo ========================================
echo ESP32-C6 LCD 项目编译脚本
echo ========================================
echo.

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

echo [信息] ESP-IDF 环境检测通过
echo.

REM 清理构建目录（可选）
echo [步骤 1/3] 清理旧的构建文件...
idf.py fullclean
echo.

REM 编译项目
echo [步骤 2/3] 开始编译项目...
idf.py build
if %errorlevel% neq 0 (
    echo.
    echo [错误] 编译失败！请检查错误信息
    pause
    exit /b 1
)
echo.

REM 显示成功信息
echo [步骤 3/3] 编译完成！
echo.
echo ========================================
echo 编译成功！
echo ========================================
echo.
echo 烧录命令:
echo   idf.py -p COM_PORT flash monitor
echo.
echo 请将 COM_PORT 替换为实际的串口端口号
echo.
pause

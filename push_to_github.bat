@echo off
echo ========================================
echo 推送代码到 GitHub
echo ========================================
echo.

REM 检查参数
if "%1"=="" (
    echo [错误] 请提供 GitHub 仓库 URL
    echo.
    echo 用法: push_to_github.bat REPOSITORY_URL
    echo.
    echo 示例:
    echo   push_to_github.bat https://github.com/username/ESP32-C6-LCD-1.47-Test.git
    echo   push_to_github.bat git@github.com:username/ESP32-C6-LCD-1.47-Test.git
    echo.
    echo 提示:
    echo   1. 先在 GitHub 上创建新仓库
    echo   2. 复制仓库的 HTTPS 或 SSH URL
    echo   3. 运行此脚本并粘贴 URL
    echo.
    pause
    exit /b 1
)

set REPO_URL=%1

echo [信息] 目标仓库: %REPO_URL%
echo.

REM 添加远程仓库
echo [步骤 1/3] 添加远程仓库...
git remote add origin %REPO_URL%
if %errorlevel% neq 0 (
    echo.
    echo [警告] 远程仓库 'origin' 可能已存在
    echo 尝试更新远程 URL...
    git remote set-url origin %REPO_URL%
)
echo.

REM 重命名分支为 main
echo [步骤 2/3] 设置主分支名称...
git branch -M main
echo.

REM 推送到 GitHub
echo [步骤 3/3] 推送代码到 GitHub...
echo.
git push -u origin main
if %errorlevel% neq 0 (
    echo.
    echo [错误] 推送失败！可能的原因:
    echo   1. 仓库 URL 不正确
    echo   2. 没有推送权限
    echo   3. 网络连接问题
    echo   4. 需要先进行身份验证
    echo.
    echo 建议:
    echo   - 检查 GitHub 个人访问令牌(PAT)配置
    echo   - 确认 SSH 密钥已添加到 GitHub
    echo   - 使用 git push -u origin main 手动推送
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo 推送成功！
echo ========================================
echo.
echo 你的代码已成功上传到 GitHub！
echo.
pause

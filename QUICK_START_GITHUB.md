# ⚡ GitHub 上传 - 快速操作指南

## 🎯 三步完成上传

### 第 1 步：创建 GitHub 仓库
1. 访问 [https://github.com/new](https://github.com/new)
2. 填写仓库名称（如 `ESP32-C6-LCD-1.47-Test`）
3. 选择 Public 或 Private
4. **不要** 勾选 "Initialize with README"
5. 点击 "Create repository"

### 第 2 步：复制仓库 URL
从创建的页面复制 HTTPS URL，格式类似：
```
https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
```

### 第 3 步：运行推送命令
在项目目录打开命令行，执行：

```bash
push_to_github.bat https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
```

或者手动执行：
```bash
git remote add origin https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
git branch -M main
git push -u origin main
```

---

## 🔑 身份验证

### 首次推送需要登录

**HTTPS 方式**：
- 用户名：你的 GitHub 用户名
- 密码：使用 [Personal Access Token](https://github.com/settings/tokens)（不是账号密码）

**SSH 方式**（推荐）：
- 需要先配置 SSH 密钥
- 详见 [GITHUB_UPLOAD_GUIDE.md](GITHUB_UPLOAD_GUIDE.md)

---

## ✅ 验证成功

推送完成后，刷新 GitHub 页面，应该能看到所有文件！

---

## 📖 详细文档

完整的上传指南、常见问题解答请参考：
👉 [GITHUB_UPLOAD_GUIDE.md](GITHUB_UPLOAD_GUIDE.md)

---

**准备好了吗？开始上传吧！** 🚀

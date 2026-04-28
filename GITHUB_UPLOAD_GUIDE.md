# GitHub 上传指南

## 📋 前置准备

在上传代码到 GitHub 之前，请确保：
- ✅ 已安装 Git
- ✅ 已注册 GitHub 账号
- ✅ 已配置 Git 用户信息（用户名和邮箱）

## 🚀 快速上传步骤

### 方法一：使用推送脚本（推荐）

#### 1. 在 GitHub 上创建新仓库

1. 访问 [https://github.com/new](https://github.com/new)
2. 填写仓库信息：
   - **Repository name**: `ESP32-C6-LCD-1.47-Test`（或其他你喜欢的名称）
   - **Description**: ESP32-C6 based LCD display system with LVGL GUI
   - **Public/Private**: 根据需要选择
   - ⚠️ **不要** 勾选 "Initialize this repository with a README"
3. 点击 "Create repository"

#### 2. 复制仓库 URL

创建成功后，GitHub 会显示仓库页面。复制以下两种 URL 之一：

- **HTTPS URL**（推荐新手）: 
  ```
  https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
  ```

- **SSH URL**（需要配置 SSH 密钥）:
  ```
  git@github.com:你的用户名/ESP32-C6-LCD-1.47-Test.git
  ```

#### 3. 运行推送脚本

在项目根目录打开命令行，执行：

```bash
# 替换为你的实际仓库 URL
push_to_github.bat https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
```

脚本会自动完成：
- 添加远程仓库
- 设置主分支为 main
- 推送所有代码

---

### 方法二：手动命令行操作

如果你更喜欢手动操作，可以执行以下命令：

```bash
# 1. 添加远程仓库（替换为你的实际 URL）
git remote add origin https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git

# 2. 重命名分支为 main
git branch -M main

# 3. 推送到 GitHub
git push -u origin main
```

---

## 🔐 身份验证

### 使用 HTTPS（需要个人访问令牌）

如果使用 HTTPS URL，GitHub 不再支持密码认证，需要使用 **Personal Access Token (PAT)**：

#### 创建 Personal Access Token

1. 访问 [https://github.com/settings/tokens](https://github.com/settings/tokens)
2. 点击 "Generate new token" → "Generate new token (classic)"
3. 填写信息：
   - **Note**: ESP32-C6 Project
   - **Expiration**: 根据需要选择（建议 90 天或更长）
   - **Scopes**: 勾选 `repo`（完整仓库权限）
4. 点击 "Generate token"
5. **重要**: 复制并保存生成的 token（只显示一次！）

#### 使用 Token 推送

当提示输入密码时，粘贴你的 Personal Access Token：

```
Username: 你的 GitHub 用户名
Password: 粘贴你的 Personal Access Token
```

或者直接在 URL 中包含 token（不推荐，不安全）：
```bash
git remote add origin https://你的用户名:你的token@github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git
```

### 使用 SSH（推荐长期使用）

#### 生成 SSH 密钥

```bash
# 在 Git Bash 或命令行中执行
ssh-keygen -t ed25519 -C "你的邮箱@example.com"
```

按提示操作，通常直接按回车使用默认设置即可。

#### 添加 SSH 密钥到 GitHub

1. 复制公钥内容：
   ```bash
   # Windows
   type %USERPROFILE%\.ssh\id_ed25519.pub
   
   # Linux/Mac
   cat ~/.ssh/id_ed25519.pub
   ```

2. 访问 [https://github.com/settings/keys](https://github.com/settings/keys)
3. 点击 "New SSH key"
4. 粘贴公钥内容，添加标题（如 "ESP32-C6 Laptop"）
5. 点击 "Add SSH key"

#### 使用 SSH URL

```bash
git remote add origin git@github.com:你的用户名/ESP32-C6-LCD-1.47-Test.git
git push -u origin main
```

---

## ✅ 验证上传

推送成功后，刷新 GitHub 仓库页面，你应该能看到：

- ✅ 所有源代码文件
- ✅ README.md 项目说明
- ✅ PROJECT_CLEANUP.md 整理记录
- ✅ build.bat 和 flash.bat 工具脚本
- ✅ 完整的提交历史

---

## 📝 常见问题

### Q1: 推送时提示 "Authentication failed"

**解决方案**:
- 检查用户名和密码/token 是否正确
- 确认 Personal Access Token 未过期
- 尝试重新生成 token

### Q2: 提示 "remote origin already exists"

**解决方案**:
```bash
# 更新现有远程 URL
git remote set-url origin https://github.com/你的用户名/ESP32-C6-LCD-1.47-Test.git

# 然后重新推送
git push -u origin main
```

### Q3: 推送失败，提示 "non-fast-forward"

**解决方案**:
```bash
# 先拉取远程更改
git pull origin main --allow-unrelated-histories

# 解决冲突后再次推送
git push -u origin main
```

### Q4: 文件大小限制

GitHub 单个文件限制为 100MB。如果遇到大文件：

```bash
# 检查大文件
git rev-list --objects --all | grep "$(git verify-pack -v .git/objects/pack/*.idx | sort -k 3 -n | tail -5 | awk '{print$1}')"

# 从 Git 历史中移除大文件（谨慎操作）
git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch 大文件路径' --prune-empty HEAD
```

### Q5: 不想上传某些文件

编辑 `.gitignore` 文件，添加要忽略的文件或目录：

```gitignore
# 示例
build/
*.log
secrets.h
```

然后执行：
```bash
git rm -r --cached build/
git commit -m "移除构建目录"
git push
```

---

## 🎯 后续维护

### 日常提交流程

```bash
# 1. 查看修改
git status

# 2. 添加修改
git add .

# 3. 提交
git commit -m "描述你的修改"

# 4. 推送
git push
```

### 同步他人修改

```bash
# 拉取最新代码
git pull origin main
```

### 查看提交历史

```bash
# 简洁视图
git log --oneline

# 图形化视图
git log --graph --oneline --all
```

---

## 📚 相关资源

- [GitHub 官方文档](https://docs.github.com/)
- [Git 官方文档](https://git-scm.com/doc)
- [Personal Access Token 指南](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
- [SSH 密钥配置指南](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)

---

**祝你上传顺利！** 🎉

如有问题，欢迎随时咨询。

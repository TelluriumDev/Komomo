# Komomo

Komomo 基于 ScriptX 和 NodeJs 实现，支持在 LeviLamina 中运行 JavaScript 插件。

## 安装

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

1. 下载对应平台的 `Komomo-full.zip` 文件，如: `Komomo-windows-full-x64.zip`

> full 为完整包，包含 LibNodeJs 和 Komomo 的依赖库

2. 将 `Komomo-full.zip`内的`Komomo/`文件夹解压到`BDS`根目录的`./plugins/`文件夹下

> 示例结构

```tree
.
├── 📁 bedrock_server
│   ├── 📄 bedrock_server_mod.exe
│   └── 📁 plugins
│       ├── 📁 Komomo
│       │   ├── 📄 Komomo.dll
│       │   ├── 📄 manifest.json
│       │   ├── 📄 node.exe
│       │   ├── 📄 libnode.dll
│       │   └── 📁 npm/
└── ...
```

3. 启动你的 LeviLamina 服务器

## 开发

~~目前项目没有任何开发文档，您可以阅读 `lib/dts` 目录下的类型定义文件，了解 Komomo 的 API。~~
假的，[Komomo文档（在建）](https://komomo.top)

## 关于项目

### 支持平台

目前 LeviLamina 仅支持 Windows 平台，故本插件也仅支持 Windows 平台。

| Backend | Version  | Support | CommonJs | ESM | package manager |
| :------ | :------- | :------ | :------- | :-- | :-------------- |
| NodeJs  | v22.12.0 | y       | y        | y   | npm             |

### 从源码编译

在编译之前，确保您已经安装了以下工具/工具链：

- xmake
- MSVC 2019 或更高版本 (仅限 Windows)

```bash
git clone --depth=1 https://github.com/TelluriumDev/Komomo.git
cd Komomo
git submodule update --init --recursive
xmake -y
```

## 贡献

欢迎提交 Issue 和 Pull Request。

# Komomo

| 中文 |

Komomo 基于 ScriptX 和 NodeJs 实现，支持在 LeviLamina 中运行 JavaScript 插件。

## 安装

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

1. 下载对应平台的 Komomo-full.zip 文件，如: `Komomo-windows-full-x64.zip`

> full 为完整包，包含 LibNodeJs 和 Komomo 的依赖库

1. 将 Komomo-full.zip 解压，将压缩包内 libnode.dll 和 plugins 目录复制到 bedrock_server 的根目录下

> 示例结构

```tree
.
├── bedrock_server
│   ├── bedrock_server_mod.exe
│   ├── libnode.dll
│   └── plugins
│       ├── Komomo
│       │   ├── Komomo.dll
│       │   ├── manifest.json
└── ...
```

1. 启动你的 LeviLamina 服务器

## 开发

目前项目没有任何开发文档，您可以阅读 `lib/dts` 目录下的类型定义文件，了解 Komomo 的 API。

## 关于项目

### 支持平台

| Platform | Backend | Version | Support | CommonJs | ESM | package manager |
| :------- | :------ | :------ | :------ | :------- | :-- | :-------------- |
| Windows  | NodeJs  | v23.5.0 | y       | y        | y   | npm             |
| Linux    | NodeJs  | v23.5.0 | x       | x        | x   | npm             |

### 从源码编译

在编译之前，确保您已经安装了以下工具链：

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

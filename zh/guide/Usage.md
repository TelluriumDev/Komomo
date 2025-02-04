# 🛠️ 安装与使用

## 🎓 前置知识要求

在使用 `Komomo` 前，请确保您已掌握以下技能：

- **❗ 计算机基础操作**  
  包括文件解压缩、路径管理等基本技能
- **🌐 GitHub 基础操作**  
  能够进行仓库克隆、Release 文件下载等操作
- **🐉 LeviLamina 使用经验**  
  熟悉使用 `LeviLamina` 的 `BDS` 服务器的搭建与运行

**若您不符合上述要求，建议先学习相关基础知识后再进行安装**，否则。我们不推荐您使用`Komomo`。

## 💽 安装依赖

对于`LeviLamina`，我们推荐通过官方文档完成安装：
**[![LeviLamina 安装指南](https://img.shields.io/badge/点击查看-LeviLamina%20安装指南-blue?style=flat-square)](https://lamina.levimc.org/zh/quickstart/)**

之后，您需要安装`iListenAttentively`，这是一个出色的事件库，为其他插件提供了更多可被监听的事件。

你可以点击此处进行下载：
[![下载iListenAttentively](https://img.shields.io/badge/点击下载-iListenAttentively-blue?style=flat-square)](https://github.com/MiracleForest/iListenAttentively-Release)

**`Komomo`依托于这些依赖，您必须在安装`Komomo`之前确保这些依赖已经被正确安装。**

## 📦 安装 Komomo

### 💾 下载 Komomo

<!-- tabs:start -->

#### **🛡️ 稳定版**

**适合人群:** 大多数普通用户

**下载文件:** 前往 [**Releases**](https://github.com/TelluriumDev/Komomo/releases) 页面下载。

下载界面存在两个文件可供下载：

- `Komomo.zip`
- `lib.zip`

`Komomo.zip`包含插件本体，`lib.zip`包含`Node.js`和相关依赖库。

**全新安装:** 下载并安装`Komomo.zip`和`lib.zip`。

**升级安装:** 下载并安装`Komomo.zip`。

#### **🚀 快照版**

**适合人群:** 开发者/尝鲜用户

**下载文件:** 登录您的 GitHub 账号，并[**点击这里**](https://github.com/TelluriumDev/Komomo/actions/workflows/build.yml)来获取快照版。

下载界面存在两个文件可供下载：

- `Komomo-windows-latest-full-x64-[hash].zip`
- `Komomo-windows-latest-x64-[hash].zip`

标记`-full-`的压缩包为完整版，包含`Node.js`和`Node.js`的依赖库。

只标记`-x64-`的压缩包为核心版本，只包含`Komomo`本体。

**全新安装:** 下载并安装`Komomo-windows-latest-full-x64-[hash].zip`。

**升级安装:** 下载并安装`Komomo-windows-latest-x64-[hash].zip`。

<!-- tabs:end -->

### 📂 安装 Komomo

<!-- tabs:start -->

#### **🛡️ 稳定版**

1. 解压您下载的`Komomo.zip`，将内部的`./Komomo/`文件夹放置在`BDS`目录下的`./plugins/`内
2. 解压您下载的`lib.zip`，将内部的所有文件放置在`./BDS/plugins/`内的`./Komomo/`文件夹内
3. 重启`BDS`，等待类似这样的控制台输出：

```log
INFO [LeviLamina] 正在加载 Komomo v0.0.0
INFO [LeviLamina] Komomo 已加载
```

即为安装成功。

#### **🚀 快照版**

无论您下载的是哪个压缩包，仅需要把内部的`./Komomo/`文件夹放置在`BDS`目录下的`./plugins/`内即可。

重启`BDS`，等待类似这样的控制台输出：

```log
INFO [LeviLamina] 正在加载 Komomo v0.0.0
INFO [LeviLamina] Komomo 已加载
```

即为安装成功。

<!-- tabs:end -->

### 📂 目录结构验证

安装完成后，请检查目录结构是否符合以下规范：

```tree
bds_root/  // BDS 根目录
├── 📄 bedrock_server_mod.exe
└── 📁 plugins/
    ├── 📁 Komomo/
    |    ├── 📁 node_modules/ // Node.js 依赖库
    |    |   └── 📁 ......
    |    ├── 📄 Komomo.dll    // Komomo  核心文件
    |    ├── 📄 libnode.dll   // Node.js 核心文件
    |    ├── 📄 manifest.json // Komomo  清单文件
    |    ├── 📄 node.exe      // Node.js 核心文件
    └── 📁 ......             // 其他插件 (如LeviLamina)
```

!> 若标记注释的文件不存在或位置不符，请**重新执行安装流程**

---

### 更新 Komomo

当新的`Minecraft 基岩版`发布时，`LeviLamina`会发布新的适配版本，`Komomo`也会发布新的适配版本。

在更新`Komomo`之前，请确保您已经更新了`LeviLamina`，否则`Komomo`将可能无法正常运行。

更新`Komomo`的操作和安装`Komomo`的操作相同，只需遵照安装步骤，下载所需要的文件，并完成替换。

!> 注意：如果 Node.js 发生变动，您就需要按照全新安装的步骤，删除 `Komomo` 和 `Node.js` 的所有残留文件，重新进行安装程序。

## 🎯 安装脚本插件

脚本插件依赖`Komomo`，在进行此步操作之前请检查`Komomo`是否正确安装。

一般而言，如要安装脚本插件，仅需把脚本插件的文件夹直接拖进`./plugins/`目录下即可。

之后重启`BDS`，`Komomo`将会视情况补全脚本插件的依赖库，并自动加载脚本插件。

### 寻找 Komomo 脚本插件

你可以在[MineBBS](https://www.minebbs.net/resources/)上寻找 Komomo 的脚本插件。

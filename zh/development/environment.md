# 🚀 环境配置

## 📋 前言

`Komomo`是一个运行在`Minecraft 基岩版专属服务端`(以下简称为`BDS`)的脚本插件引擎。

依托于`LeviLamina`，`Komomo`可以轻松地实现`Minecraft`基岩版插件的开发。

使用 Komomo 进行开发，那么我们就需要配置好开发环境和运行环境。

## 🏃‍♂️ 运行环境配置

我们在对`BDS`进行开发，所以首先我们需要一个安装好`LeviLamina`的`BDS`。

如果您还没有准备好一个`LeviLaminaBDS`环境，请前往[LeviLamina 文档](https://lamina.levimc.org/zh/quickstart/)来完成安装。

安装好`LeviLamina`之后，请前往用户指南的[安装与使用](/zh/guide/Usage.md)部分，完成`Komomo`的安装。

当一切准备妥当之后，我们就可以开始准备插件的编写环境了。

## ⚙️ 开发环境配置

`Komomo`的开发者们为需要编写插件的开发者准备好了一个模板项目，您可以在[这里](https://github.com/TelluriumDev/Komomo-JavaScript-Template)找到它。

您可以在 GitHub 上直接使用这个模板建立一个您自己的仓库。

如果您不需要版本管理，也可以直接克隆这个仓库到本地。

```bash
git clone https://github.com/your-username/komomo-js-template.git
cd komomo-js-template
git submodule update --remote --recursive
npm install
```

?> 此处的`git submodule update --remote --recursive`用来从 Github 获取补全库。  
如果不进行这一步，tsc 的编译将无法通过，您也会失去编写代码时的自动补全能力。

克隆完成后，我们就可以开始编写我们的第一个插件了。

关于如何编写属于您的第一个插件，请阅读[快速入门](/zh/development/firstmod.md)。

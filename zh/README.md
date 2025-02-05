# Komomo

**Komomo**是一个依托于[**`LeviLamina`**](https://github.com/LiteLDev/LeviLamina)的脚本语言加载器，旨在允许开发者以更加简便灵活的方式为 Minecraft 基岩版专属服务端（BDS）开发脚本插件，增添额外功能。

## 🧐 为什么选择 Komomo？

| 特性        | LL 原生插件            | Komomo 插件         |
| ----------- | ---------------------- | ------------------- |
| ⏰ 开发效率 | ⏳ 需编译/重启         | 🚀 热加载/即时生效  |
| 📖 学习曲线 | 📈 需掌握 C++/底层技术 | 📉 只需 JS/TS 基础  |
| 💡 功能扩展 | 🔧 依赖逆向工程        | 🧩 模块化 API 生态  |
| ⌛ 性能表现 | ⚡ 原生级速度          | 🚄 Node.js 优化引擎 |

从表格来看，对于**未接触过**`C/C++`**程序编写的开发者**，

或者**对于实现相对于简单，无太大性能需求的插件**，

`Komomo`无疑是上好的选择。

## ⚽ 如何使用？

1. 安装[**`LeviLamina`**](https://github.com/LiteLDev/LeviLamina)和[**`iListenAttentively`**](https://github.com/MiracleForest/iListenAttentively-Release)。
2. 在 Komomo 的 [Releases](https://github.com/LiteLDev/Komomo/releases) 界面下载并最新版的 Komomo。
3. 以同样的方式安装依赖于 Komomo 的脚本插件。
4. 启动服务器！你将会看到 Komomo 和脚本插件被顺利加载。

请转到[**用户指南**](./zh/guide/Usage.md)获取更多关于安装和使用 `Komomo` 的信息。

## 📑 如何编写脚本插件?

请前往[**开发者指南**](./zh/development/README.md)获取关于编写脚本插件的帮助。

## 💊 我遇到了问题，怎么办?

如果安装或开发时遇到了问题，您可以[**点击此处**](/zh/FAQ.md)查看常见问题。

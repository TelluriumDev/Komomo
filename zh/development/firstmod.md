# 🚪 快速入门

## 📋 前言

此教程将使用 `Komomo` 提供的插件模板，教您一步步创建一个属于您的简单插件。

此教程假设您对`TypeScript`有一定的了解，如果您还不了解`TypeScript`，请先学习`TypeScript`。

示例插件将会在玩家进入服务器时对该玩家发送欢迎信息。

## 📓 准备工作

俗话说，工欲善其事，必先利其器。编写代码需要一个趁手的工具。

此教程推荐使用 `Visual Studio Code` 作为开发工具，您可前往[Visual Studio Code 官网](https://code.visualstudio.com/)下载安装。

当然，其他代码编辑器也可以，不过为了方便，我们还是使用 `VS Code`。

关于运行环境和开发环境的配置教程，请前往[环境配置](/zh/development/environment.md)获取。

## ✒️ 编写代码

当做完了准备工作，我们就可以开始编写代码了。

首先，使用您的编辑器打开模板文件夹，您会看到这些文件：

```tree
📁 template-root // 模板根目录
├── 📁 KomomoHelperLib/ // 插件开发辅助库
├── 📁 scripts/         // 脚本目录
├── 📁 src/             // 源代码目录
|    └── 📄 test.ts
├── 📄 index.ts         // 插件入口文件
├── 📄 .gitignore
├── 📄 manifest.json    // 插件清单文件
└── 📄 package.json     // npm依赖管理文件
```

本教程将专注于`index.ts`和`manifest.json`两个文件。

首先，我们需要更改`manifest.json`:

```json
{
  "entry": "index.js", // 插件入口文件
  "type": "KomomoJS", // 插件类型，不应更改
  "version": "1.0.0", // 插件版本
  "name": "JoinWelcome", // 插件名称
  "dependencies": [
    {
      "name": "Komomo" // 插件依赖的库，不应更改
    }
  ]
}
```

对于本教程，`src/`文件夹对我们没有意义，所以请删掉它。

然后，我们打开`index.ts`，您会看到以下代码：

```typescript
/// <reference path="./KomomoHelperLib/index.d.ts" />

import("./src/test");
```

由于我们刚刚删除掉了`src/`文件夹，所以我们删除掉`import("./src/test")`这行代码。

现在，让我们回顾一下我们的需求：当玩家进入服务器时，向玩家发送欢迎信息。

那么，如何获知玩家进入服务器呢？我们可以使用`Komomo`提供的`PlayerJoinEvent`事件。

监听`PlayerJoinEvent`事件的原型如下：

```typescript
function emplaceListener(
  event: "PlayerJoinEvent",
  callback: (player: Player) => boolean,
  priority?: EventEnum.EventPriority
): Listener;
```

`emplaceListener`函数接受三个参数：

1. 事件名称，本例中为`PlayerJoinEvent`。
2. 回调函数，当事件触发时，该函数将被调用。回调函数接受一个`Player`对象作为参数，该对象表示触发事件的玩家。
3. 事件优先级，可选参数，用于指定事件的优先级。默认为`EventEnum.EventPriority.NORMAL`。

对于欢迎玩家，我们不需要优先级，所以我们可以省略第三个参数。

现在，我们可以在`index.ts`中添加以下代码：
```typescript
/// <reference path="./KomomoHelperLib/index.d.ts" />
function onPlayerJoin(player: Player): boolean {
  player.sendMessage("欢迎加入服务器！")
  return true;
}
EventBus.emplaceListener("PlayerJoinEvent", onPlayerJoin);
```

现在，当玩家进入服务器时，`onPlayerJoin`函数将被调用，并向玩家发送欢迎信息。

当然，为了代码的紧凑性，我们可以将`onPlayerJoin`函数直接作为回调函数传递给`emplaceListener`函数:

```typescript
/// <reference path="./KomomoHelperLib/index.d.ts" />
EventBus.emplaceListener("PlayerJoinEvent", (player: Player) => {
  player.sendMessage("欢迎加入服务器！")
  return true;
});
```

这样，我们就完成了插件的编写。

## ⚙️ 编译代码

现在，我们已经完成了代码的编写，接下来我们需要编译代码。

在命令行中，进入模板根目录，然后运行以下命令：

```bash
npm run build
```

之后命令行会出现`Build successful`的消息，表示编译成功。

## 🗳️ 运行插件

编译成功后，脚本已经把所需文件拷贝到了`bin/`文件夹中。

我们只需要把`bin/`文件夹复制到`BDS`根目录的`plugins/`文件夹中，将文件夹的名字改成`JoinWelcome`，即可完成安装。

然后启动服务器，当玩家进入服务器时，玩家将会收到欢迎信息。

## 📦 分发插件

您可能希望把插件分发给其他人使用，那么您需要把插件打包成`.zip`文件。

您只需要把`bin/`文件夹内的文件打包成zip归档，然后分发给其他人即可。

## 📖 总结

通过本教程，您已经学会了如何创建一个简单的`Komomo`插件，并且学会了如何编译和运行插件。

不过，此插件的功能非常简单，您可以根据自己的需求，编写更复杂的插件。

利用您的发散性思维，仔细考虑一下这个插件：

- 也许可以增加逻辑，实现一个签到功能?
- 也许可以把发送消息改动成发送一个表单?
- 也许可以增加一个配置文件，让用户可以自定义欢迎信息?

若您想进阶您的开发技能，请阅读[API文档](/zh/development/api/README.md)，了解`Komomo`提供的API。


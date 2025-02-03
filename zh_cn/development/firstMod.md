# 使用JavaScript创造你的首个脚本插件

> 本指南旨在展示创建你的第一个插件的非常简单和直接的过程--以及在考虑做什么和如何做时的一些最佳做法。建议有使用JavaScript的经验，但不是必须的。JavaScript是一种对初学者非常友好的语言，所以不要被淹没了!

## 先决条件

在开发你的第一个插件之前，我们需要设置你的开发环境。你用来编程的软件由你自己选择，但建议使用可信和可靠的软件。

- [VSCode](https://code.visualstudio.com/) 也是一个广泛使用的编辑器，具有很多强大的功能

你还需要建立一个干净的 LeviLamina 安装，关于如何安装 LeviLamina 的细节可以在[这里](/zh_cn/Usage.md)找到。这个服务器将被用来测试你的插件。

有了你的开发环境，并完成了服务器的安装，你就可以开始了!

## 我现在该做什么？

开发一个脚本插件，首先要创建你的插件文件。这个文件应该命名为 "mymod.js"，将 "mymod" 替换为你想要的插件名称。它应该被放在你的服务器安装的插件文件夹中。有些开发环境会允许你创建一个新文件并选择一个位置，而其他开发环境则允许你在点击 "另存为" 后才选择。

如果您精通 TypeScript 您可以直接使用我们的 TS 插件模板库 [这里](https://github.com/TelluriumDev/Komomo-JavaScript-Template)

另外 JavaScript 分支为开发者提供了 JS 插件模板库

统一脚本插件 manifest.json type: “KomomoJS“ (不知道怎么用的看 LeviLamina 插件加载机制)

> 请详细了解 LeviLamina 的插件加载机制 以上插件模板可以帮助你大致了解

现在我们已经创建了我们的.js文件，并注册了插件，我们要做的就是创建一个事件监听器。我们通过使用`EventBus`来实现。

```js
EventBus.emplaceListener("PlayerJoinEvent", (player) => {
    player.sendMessage("欢迎加入服务器！")
});
```

<!-- > 参考资料: https://docs.litebds.com/zh-Hans/#/LLSEPluginDevelopment/EventAPI/Listen -->

为了测试你的插件，只需启动服务器，服务器应该能够识别你的插件并成功加载它。LeviLamina 控制台将记录您创建的任何日志，以及您的插件或API失败时的任何错误。开发时的迭代很重要。经常测试，每一步都要确保当问题出现时，你清楚地知道你改变了什么，并能想出解决方案来解决它。

你可以引用类，以及其他特殊的类和构造函数。这些类你的插件的面包和黄油，将允许你做很多很酷的事情。游戏内容接口有所有的方法和属性供你使用。
<!-- >参考：https://docs.litebds.com/en/#/LLSEPluginDevelopment/GameAPI/Basic -->

例如，我们可以使用玩家对象并直接对其采取行动，以发送信息/操纵玩家。

```js
EventBus.emplaceListener("PlayerJoinEvent", (player) => {
    player.sendMessage("欢迎加入服务器！")
});
```

我们可以引用玩家对象的属性，并使用它来执行其他动作。

<!-- ```js
EventBus.emplaceListener("PlayerJoinEvent",(player) => {
    player.sendToast('欢迎！', '感谢您游玩本服！');
    let loginReward = mc.newItem('minecraft:diamond', 1);
    mc.spawnItem(loginReward, player.pos)。
});
``` -->

这给我们带来了最后的考虑。在制作插件时，尽量想一些简单的、自我封闭的东西。每个开发者都想建立一个具有大量功能的大型插件，但这样的项目很容易被放弃，因为它们从未真正完成。做一系列有特定目的的小插件。为这些插件添加功能，以实现配置和定制。找到你希望游戏拥有的功能或事物，并使用Komomo中的方法来实现它们。使用Komomo的API确实有无限可能。

## 🎯 命令相关 API <!-- {docsify-ignore-all} -->

下面这些API提供了在游戏中注册、监听自定义命令的接口

Komomo 提供了强大的命令注册接口 以便开发者可以迅速的注册命令

示例:

```ts
let cmd = Command.newCommand("test", "test", CommandEnum.CommandPermissionLevel.Admin, CommandEnum.CommandFlagValue.None)

cmd.setAlias("t")

cmd.optional("optional", CommandEnum.ParamKindKind.String, CommandEnum.CommandParameterOption.None).text("test").overload()

cmd.required("required", CommandEnum.ParamKindKind.Int, CommandEnum.CommandParameterOption.None).overload()

cmd.setCallback((command, commandOrigin, commandOutput, args) => {
    let logger = Logger.getLogger("Command Logger")
    if (args["optional"]) {
        logger.info("Optional Argument: " + args["optional"])
    }
    if (args["required"]) {
        logger.info("Required Argument: " + args["required"])
    }
    return true
})
```

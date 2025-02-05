# 🎯 命令系统

命令系统是 Minecraft 中的一个重要功能，它允许通过执行指令的方式实现各种各样的功能。

在 Komomo API 中，你可以实现运行一个命令，或是创建一个你自己的命令。

## 🏃‍♂️ 运行命令

**函数原型:**

```ts
Command::run(command: string): boolean
```

运行一个命令。

**参数**: `command`: 要执行的命令  
**返回**: `boolean`: 命令是否执行成功

**使用示例:**

```ts
Command.run("say Hello, World!");
```

此示例会运行一条`say`命令，输出`Hello, World!`。

## ✒️ 注册命令

要想注册一个命令，我们需要先注册一个顶层命令。

注册顶层命令后，我们会得到一个`Command`对象，我们可以通过这个对象来进行更多操作。

### 注册顶层命令

顶层命令是所有命令的起点。  
例如命令`/home`，`home`就是一个顶层命令。

**函数原型:**

```ts
Command.newCommand(
    name: string,
    description?: string,
    permissionLevel?: CommandEnum.CommandPermissionLevel,
    flags?: CommandEnum.CommandFlagValue): Command
```

**参数**:

- `name`: 将要注册的命令名称，也是玩家输入的命令名称
- `description`: [可选]对此命令的描述，在玩家输入命令时可见
- `permissionLevel`: [可选]命令权限等级
- `flags`: [可选]命令标志位

?> 关于`CommandPermissionLevel`和`CommandFlagValue`的更多信息，请参考[枚举](/zh/development/api/GameAPI/Command/enum.md)部分。

**返回**: `Command` 命令对象

**使用示例:**

```ts
let cmd = Command.newCommand(
  "test",
  "This is a test command",
  CommandEnum.CommandPermissionLevel.GameDirectors,
  CommandEnum.CommandFlagValue.NotCheat
);
```

此示例创建一条名为`test`的命令，命令描述为`This is a test command`，  
权限等级为`GameDirectors`，标志位为`NotCheat`，  
`cmd`即为注册后返回的`Command`对象。

?> 创建`Command`对象后，您可以在[对象信息](/zh/development/api/GameAPI/Command/object.md)中查看更多操作。  
包括设置别名，设置参数，设置命令回调等。

### 命令注册示例

```ts
let cmd = Command.newCommand( // 创建顶层命令
  "test", // name
  "test", // description
  CommandEnum.CommandPermissionLevel.Admin, // permissionLevel
  CommandEnum.CommandFlagValue.None // flags
);
cmd.setAlias("t"); // 设置别名
cmd
  .optional( // 设置可选参数
    "optional",
    CommandEnum.ParamKindKind.String, // 字符串参数
    CommandEnum.CommandParameterOption.None
  )
  .text("test") // 添加文字参数
  .overload();
cmd
  .required( // 设置必选参数
    "required",
    CommandEnum.ParamKindKind.Int, // 整数参数
    CommandEnum.CommandParameterOption.None
  )
  .overload();
cmd.setCallback((command, commandOrigin, commandOutput, args) => {
  let logger = Logger.getLogger("Command Logger");
  if (args["optional"]) { // 判断重载类型
    logger.info("Optional Argument: " + args["optional"]);
  }
  if (args["required"]) {
    logger.info("Required Argument: " + args["required"]);
  }
  return true;
});
```

此示例创建了一条名为`test`的命令，设置了别名`t`，  
设置了两条重载，一条有可选参数，一条有必选参数，  
在回调函数中，函数将根据调用重载的类型，把传入的参数输出出来。

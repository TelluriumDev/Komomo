# 🔮 对象信息

本节记录了命令系统相关的对象信息。

## 🎯 `Command`

此类代表一个命令对象，用于创建和管理命令。

### 设置命令别名

命令别名相当于命令的快捷方式，通过设置命令别名，我们可以简化命令的输入。  
实际上两个命令的功能是一样的。

**函数原型**:

```ts
setAlias(alias: string): boolean
```

**参数**: `alias`: 命令别名  
**返回**: `boolean`: 是否设置成功

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.setAlias("t");
```

在这个例子中，`t`即为命令`test`的别名。

### 设置必选参数

必选参数即为使用时必须输入的参数。  
若执行命令时未输入，命令将不会被执行并抛出错误。

**函数原型**:

```ts
required(
    name: string,
    type: CommandEnum.ParamKindKind,
    option: CommandEnum.CommandParameterOption,
    enumName?: string
): this
```

**参数**: 
- `name`: 参数名
- `type`: 参数类型
- `option`: 参数选项
- `enumName`: 枚举名，仅在参数类型为枚举时需要

**返回**: `this`

> 关于`CommandEnum.ParamKindKind`和`CommandEnum.CommandParameterOption`，请参考[枚举](/development/api/GameAPI/Command/enum)部分

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.required(
    "player",
    CommandEnum.ParamKindKind.Player,
    CommandEnum.CommandParameterOption.None
);
```
在这个例子中，`player`即为命令`test`的必选参数，类型为玩家，参数选项为无。

### 设置可选参数

可选参数即为使用时可以输入也可以不输入的参数。  

**函数原型**:

```ts
optional(
    name: string,
    type: CommandEnum.ParamKindKind,
    option: CommandEnum.CommandParameterOption,
    enumName?: string
): this
```

**参数**: 
- `name`: 参数名
- `type`: 参数类型
- `option`: 参数选项
- `enumName`: [可选]枚举名，仅在参数类型为枚举时需要

**返回**: `this`

> 关于`CommandEnum.ParamKindKind`和`CommandEnum.CommandParameterOption`，请参考[枚举](/development/api/GameAPI/Command/enum)部分

**使用示例:**

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.optional(
    "player",
    CommandEnum.ParamKindKind.Player,
    CommandEnum.CommandParameterOption.None
);
```
在这个例子中，`player`即为命令`test`的可选参数，类型为玩家，参数选项为无。

### 添加文字参数

文字参数即为字符串参数。  
在命令执行时，文字参数会被解析为字符串。

**函数原型**:

```ts
text(name: string): this
```

**参数**: `name`: 参数名  
**返回**: `this`

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.text("text");
```

此示例为命令`test`添加了一个字符串参数。

### 添加枚举

为命令添加可以在创建参数时选择的枚举。
通常与`required`或`optional`函数一起使用。

**函数原型**:

```ts
addEnum(
    name: string,
    values: string[]
): void
```

**参数**: 
- `name`: 参数名
- `enumName`: 枚举名

**返回**: `this`

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.addEnum("mode", ["mode1", "mode2"]);
```

此示例为命令`test`添加了一个枚举，枚举名为`mode`，枚举值为`mode1`和`mode2`。
之后在创建必选参数或可选参数时，可以选择`mode`作为传入的枚举。

### 添加动态枚举

动态枚举可以在运行时动态更改枚举值。  
其余特性与[添加枚举](#添加枚举)相同。

**函数原型**:

```ts
addSoftEnum(name: string, values: string[]): void
```

**参数**: 
- `name`: 参数名
- `enumName`: 枚举名

**返回**: `this`

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
cmd.addSoftEnum("mode", ["mode1", "mode2"]);
```

此示例为命令`test`添加了一个动态枚举，枚举名为`mode`，枚举值为`mode1`和`mode2`。
之后在创建必选参数或可选参数时，可以选择`mode`作为传入的枚举。
当此枚举被更改时，所有使用此枚举的参数都会被更新。

### 设置动态枚举

当一个动态枚举被创建，您可以使用此函数来设置动态枚举的值。

**函数原型**:

```ts
setSoftEnum(name: string, values: string[]): void
```

**参数**: 
- `name`: 参数名
- `enumName`: 枚举名

**返回**: `this`

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
// 并且添加了一个名为`mode`的动态枚举
cmd.setSoftEnum("mode", ["mode1", "mode2"]);
```

此示例为命令`test`的动态枚举`mode`设置了新的枚举值。

### 移除动态枚举

出于某种原因，您可能需要移除一个动态枚举。  
此函数可以实现此功能。

**函数原型**:

```ts
removeSoftEnum(
    name: string,
    values: string[]
): void
```

**参数**: `name`: 参数名  
**返回**: `void`

**使用示例**:

```ts
// 假设有一个命令对象cmd，顶层命令为test
// 并且添加了一个名为`mode`的动态枚举
cmd.removeSoftEnum("mode");
```

此示例为命令`test`移除了动态枚举`mode`。

### 设置命令重载

> 什么是命令重载?  
> 举个例子，Minecraft 内置了`tp`命令，它可以这样使用:  
> `/tp <destination: target>`  
> `/tp <destination: x y z> [checkForBlocks: Boolean]`  
> `/tp <destination: x y z> [yRot: value] [xRot: value] [checkForBlocks: Boolean]`  
> `......`  
> 每一条都是一个命令重载，**它们共享同一个命令名，但是参数不同**。  
> 通过命令重载，我们可以实现一个命令拥有多种使用方式。

当完成了命令参数的设置后，您可以使用此函数完成一个重载的创建。

**函数原型**:

```ts
overload(): void
```

**参数**: 无  
**返回**: `void`

**使用示例**:

```ts
// 假设有一个命令对象cmd，并且一个重载的参数设置完毕
cmd.overload()
```

此示例为命令`test`添加了一个新的命令重载。


### 设置命令回调

命令回调是命令的功能实现，命令被执行时，会调用回调函数。
您需在此函数中实现命令的具体功能。

函数原型:

```ts
setCallback(callback: (
  command: Command,
  commandOrigin: CommandOrigin,
  commandOutput: CommandOutput,
  args: Record<string, any>
) => void): boolean
```

**参数**: 
- `callback`: 回调函数
  - `command`: 命令对象
  - `commandOrigin`: 命令来源
  - `commandOutput`: 命令输出
  - `args`: 命令参数
- `return`: `boolean` 表示命令是否成功执行

**使用示例**:

```ts
// 假设有一个命令对象cmd，并且一个重载的参数设置完毕
cmd.setCallback((command, commandOrigin, commandOutput, args) => {
    // 在这里实现命令的功能
})
```
由于命令回调的示例太过于复杂，故请移步[命令系统](/zh/development/api/GameAPI/Command/README.md)查看详细的示例。


## 📦 `CommandOrigin`

### 获取名字

**函数原型**:

```ts
getName(): string
```

**参数**: 无  
**返回**: `string` 命令来源的名字

### 获取坐标

**函数原型**:

```ts
getWorldPosition(): Vec3
```

**参数**: 无  
**返回**: `Vec3` 命令来源的坐标

### 获取维度

**函数原型**:

```ts
getDimension(): Dimension
```

**参数**: 无  
**返回**: `string` 命令来源的维度

### 获取权限

**函数原型**:

```ts
getPermissionsLevel(): CommandEnum.CommandPermissionLevel
```

**参数**: 无  
**返回**: `enum` 命令来源的权限

?> 关于CommandPermissionLevel，请前往[命令权限](/zh/development/api/GameAPI/Command/enum.md#命令权限级别)查看详细说明。


### 是否有聊天权限

**函数原型**:

```ts
hasChatPerms(): boolean
```

**参数**: 无  
**返回**: `boolean` 命令来源是否有聊天权限

### hasTellPerms

**函数原型**:

```ts
hasTellPerms(): boolean
```

**参数**: 无  
**返回**: `boolean`

### 是否有特定能力

**函数原型**:

```ts
canUseAbility(abilitiesIndex: PlayerEnum.AbilitiesIndex): boolean
```

**参数**: `enum` 特定的能力
**返回**: `boolean` 是否有此能力

?> 关于PlayerEnum.AbilitiesIndex，请前往[玩家能力](/zh/development/api/GameAPI/Player/enum.md#玩家能力)查看详细说明。

### isWorldBuilder

**函数原型**:

```ts
isWorldBuilder(): boolean
```

**参数**: 无  
**返回**: `boolean`

### 是否有无作弊使用命令权限

**函数原型**:

```ts
canUseCommandsWithoutCheatsEnabled(): boolean
```

**参数**: 无  
**返回**: `boolean`

!> 警告: 未记录的API！

### isSelectorExpansionAllowed

**函数原型**:

```ts
isSelectorExpansionAllowed(): boolean
```

**参数**: 无  
**返回**: `boolean`

### getOutputReceiver

**函数原型**:

```ts
getOutputReceiver(): CommandOutput
```

**参数**: 无  
**返回**: `CommandOutput` 类

### handleCommandOutputCallback

**函数原型**:

```ts
handleCommandOutputCallback(int: number, string: string): void
```

**参数**: 无  
**返回**: `void`

### updateValues

**函数原型**:

```ts
updateValues(): void
```

**参数**: 无  
**返回**: `void`

### isValid

**函数原型**:

```ts
isValid(): boolean
```

**参数**: 无  
**返回**: `boolean`

### requiresValidLevel

**函数原型**:

```ts
requiresValidLevel(): boolean
```

**参数**: 无  
**返回**: `boolean`

### sUnknownSource

**函数原型**:

```ts
sUnknownSource(): NetworkIdentifier
```

**参数**: 无  
**返回**: `NetworkIdentifier` 类


## 📢 `CommandOutput`

### 发送成功消息

当操作成功完成时，可使用此函数发送一条消息。

**函数原型**:

```ts
success(): void
success(msg: string): void
```

**参数**: `string` [可选]消息内容  
**返回**: `void`

**示例**:

```ts
// 假设有一个命令对象cmd，并且一个重载的参数设置完毕
cmd.setCallback((command, commandOrigin, commandOutput, args) => {
    commandOutput.success("操作成功")
})
```

### 发送错误消息

当操作失败时，可使用此函数发送错误消息。

**函数原型**:

```ts
error(): void
error(msg: string): void
```

**参数**: `string` [可选]消息内容  
**返回**: `void`

**示例**:

```ts
// 假设有一个命令对象cmd，并且一个重载的参数设置完毕
cmd.setCallback((command, commandOrigin, commandOutput, args) => {
    commandOutput.error("操作失败")
})
```

!> 警告: 未记录的API！

### addToResultList

**函数原型**:

```ts
addToResultList(msg: string, element: string): void
```

**参数**: 
- `msg`  
- `element`  
**返回**: `void`

### addResultList

**函数原型**:

```ts
addResultList(msg: string, element: Actor): void
```

**参数**: 
- `msg`  
- `element`  
**返回**: `void`

### empty

**函数原型**:

```ts
empty(): boolean
```

**参数**: 无  
**返回**: `boolean`

### setHasPlayerText

**函数原型**:

```ts
setHasPlayerText(): void
```

**参数**: 无  
**返回**: `void`

### wantsData

**函数原型**:

```ts
wantsData(): boolean
```

**参数**: 无  
**返回**: `boolean`

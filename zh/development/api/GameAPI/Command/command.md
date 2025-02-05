# Command 类

这里提供了注册自定义命令的接口。通过对接 BDS 内置的命令系统，你注册的命令可以由玩家、控制台、命令方块、NPC等各种游戏中可以执行命令的对象所使用，在 addon 中，也可以使用这里所注册的命令

## 注册一条顶层命令(Command 静态方法)

```ts
Command.newCommand(name: string, description?: string, permissionLevel?: CommandEnum.CommandPermissionLevel, flag?: CommandEnum.CommandFlagValue): Command
```

- 参数：

  - cmd: `string`  
    待注册的命令

  - description: `string`  
    命令描述文本  

  - permissionLevel: `CommandEnum.CommandPermissionLevel`  
    （可选参数）指令执行所需权限  

    | 执行权限                                           | 含义 |
    | -------------------------------------------------- | ---- |
    | `CommandEnum.CommandPermissionLevel.Any`           |      |
    | `CommandEnum.CommandPermissionLevel.GameDirectors` |      |
    | `CommandEnum.CommandPermissionLevel.Admin`         |      |
    | `CommandEnum.CommandPermissionLevel.Host`          |      |
    | `CommandEnum.CommandPermissionLevel.Owner`         |      |
    | `CommandEnum.CommandPermissionLevel.Internal`      |      |

  - flag: `CommandEnum.CommandFlagValue`  
    （可选参数）

    | 命令标志                                                    | 含义 |
    | ----------------------------------------------------------- | ---- |
    | `CommandEnum.CommandFlagValue.None`                         |      |
    | `CommandEnum.CommandFlagValue.UsageTest`                    |      |
    | `CommandEnum.CommandFlagValue.HiddenFromCommandBlockOrigin` |      |
    | `CommandEnum.CommandFlagValue.HiddenFromPlayerOrigin`       |      |
    | `CommandEnum.CommandFlagValue.SyncLocal`                    |      |
    | `CommandEnum.CommandFlagValue.ExecuteDisallowed`            |      |
    | `CommandEnum.CommandFlagValue.TypeMessage`                  |      |
    | `CommandEnum.CommandFlagValue.NotCheat`                     |      |
    | `CommandEnum.CommandFlagValue.Async`                        |      |
    | `CommandEnum.CommandFlagValue.NoEditor`                     |      |
    | `CommandEnum.CommandFlagValue.Hidden`                       |      |
    | `CommandEnum.CommandFlagValue.Removed`                      |      |

- 返回值：`Command` 命令对象

> 以下方法都是实例方法

## 设置指令别名

```ts
Command.setAlias(name)
```

- 参数：
  - alias: `string`  
    指令别名

- 返回值：`Boolean` 是否成功设置

## 设置可选参数

```ts
Command.optional(name: string, type: CommandEnum.ParamKindKind, option: CommandEnum.CommandParameterOption, enumName?: string): Command
```

- 参数：
  - name: `string`  
    参数名
  
  - type: `CommandEnum.ParamKindKind`  
    参数类型
  
  - option: `CommandEnum.CommandParameterOption`  
    参数枚举类型
  
  - enumName: `string`  
    枚举名

- 返回值：`Command` 命令对象(链式调用)

## 设置必选参数

```ts
Command.required(name: string, type: CommandEnum.ParamKindKind, option: CommandEnum.CommandParameterOption, enumName?: string): Command
```

- 参数：
  - name: `string`  
    参数名
  
  - type: `CommandEnum.ParamKindKind`  
    参数类型
  
  - option: `CommandEnum.CommandParameterOption`  
    参数枚举类型
  
  - enumName: `string`  
    枚举名

- 返回值：`Command` 命令对象(链式调用)

 | 参数类型                                  | 含义 |
 | ----------------------------------------- | ---- |
 | `CommandEnum.ParamKindKind.Int`           |      |
 | `CommandEnum.ParamKindKind.Bool`          |      |
 | `CommandEnum.ParamKindKind.Float`         |      |
 | `CommandEnum.ParamKindKind.Dimension`     |      |
 | `CommandEnum.ParamKindKind.String`        |      |
 | `CommandEnum.ParamKindKind.Enum`          |      |
 | `CommandEnum.ParamKindKind.SoftEnum`      |      |
 | `CommandEnum.ParamKindKind.Actor`         |      |
 | `CommandEnum.ParamKindKind.Player`        |      |
 | `CommandEnum.ParamKindKind.BlockPos`      |      |
 | `CommandEnum.ParamKindKind.Vec3`          |      |
 | `CommandEnum.ParamKindKind.RawText`       |      |
 | `CommandEnum.ParamKindKind.Message`       |      |
 | `CommandEnum.ParamKindKind.JsonValue`     |      |
 | `CommandEnum.ParamKindKind.Item`          |      |
 | `CommandEnum.ParamKindKind.BlockName`     |      |
 | `CommandEnum.ParamKindKind.BlockState`    |      |
 | `CommandEnum.ParamKindKind.Effect`        |      |
 | `CommandEnum.ParamKindKind.ActorType`     |      |
 | `CommandEnum.ParamKindKind.Command`       |      |
 | `CommandEnum.ParamKindKind.RelativeFloat` |      |
 | `CommandEnum.ParamKindKind.IntegerRange`  |      |
 | `CommandEnum.ParamKindKind.FilePath`      |      |
 | `CommandEnum.ParamKindKind.WildcardInt`   |      |

  | 参数枚举类型                                                   | 含义 |
  | -------------------------------------------------------------- | ---- |
  | `CommandEnum.CommandParameterOption.None`                      |      |
  | `CommandEnum.CommandParameterOption.EnumAutocompleteExpansion` |      |
  | `CommandEnum.CommandParameterOption.HasSemanticConstraint`     |      |
  | `CommandEnum.CommandParameterOption.EnumAsChainedCommand`      |      |

## 添加文本

```ts
Command.text(name: string): Command
```

- 参数
  
  - name: `string`  
    文本

- 返回值：`Command` 命令对象(链式调用)

## 命令重载

```ts
Command.overload(): void
```

- 返回值：`void`

## 设置命令回调

```ts
Command.setCallback(callback: (command: Command, commandOrigin: CommandOrigin, commandOutput: CommandOutput, args: Record<string, any>) => void): boolean
```

- 参数
  
  - callback: `(command: Command, commandOrigin: CommandOrigin, commandOutput: CommandOutput, args: Record<string, any>) => void`  
  回调函数

    - command: `Command`  
     当前命令对象

    - commandOrigin: `CommandOrigin`  
      命令来源对象

    - commandOutput: `CommandOutput`  
      命令输出对象

    - args: `Record<string, any>`  
      参数对象

- 返回值：`void`

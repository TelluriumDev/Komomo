# 枚举信息

以下列出了关于`Command`的一些枚举信息:

## ⚖️ 命令权限级别

```ts
enum CommandPermissionLevel {
  Any = 0, // 玩家，例如/list
  GameDirectors = 1, // 管理员，例如/tp
  Admin = 2, // 管理员，例如/op
  Host = 3, // 房主，例如/setmaxplayers
  Owner = 4, // 控制台，例如/stop
  Internal = 5, // 仅内部使用
}
```

## 🚩 命令标志位

```ts
enum CommandFlagValue {
  None = 0,
  UsageTest = 1 << 0,
  HiddenFromCommandBlockOrigin = 1 << 1,
  HiddenFromPlayerOrigin = 1 << 2,
  HiddenFromAutomationOrigin = 1 << 3,
  SyncLocal = 1 << 4,
  ExecuteDisallowed = 1 << 5,
  TypeMessage = 1 << 6,
  NotCheat = 1 << 7, // LLSE Default
  Async = 1 << 8,
  NoEditor = 1 << 9,
  // Hidden = HiddenFromPlayerOrigin | HiddenFromCommandBlockOrigin,
  // Removed = Hidden | HiddenFromAutomationOrigin,
}
```

## 📋 参数类型

```ts
enum ParamKindKind {
  Int = 0,
  Bool,
  Float,
  Dimension,
  String,
  Enum,
  SoftEnum,
  Actor,
  Player,
  BlockPos,
  Vec3,
  RawText,
  Message,
  JsonValue,
  Item,
  BlockName,
  BlockState,
  Effect,
  ActorType,
  Command,
  RelativeFloat,
  IntegerRange,
  FilePath,
  WildcardInt,
  WildcardActor,
  // New types can only be added here, to keep the ABI stable.
  Count,
}
```

## 🛠️ 参数选项

```ts
enum CommandParameterOption {
  // bitfield representation
  None = 0,
  EnumAutocompleteExpansion = 1 << 0,
  HasSemanticConstraint = 1 << 1,
  EnumAsChainedCommand = 1 << 2,
}
```

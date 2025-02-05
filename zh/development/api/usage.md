# 📜 API 使用说明

## 📀 基本数据类型

虽然说 Javascript 是动态类型语言，但是为了方便与脚本引擎对接，我们定义了一些基本数据类型:

| 引擎数据类型 | JavaScript 数据类型 | 数据类型说明 |
| ------------ | ------------------- | ------------ |
| `undefined`  | `undefined`         | 空           |
| `Integer`    | `Number`            | 整数         |
| `Float`      | `Number`            | 浮点数       |
| `String`     | `String`            | 字符串       |
| `Boolean`    | `Boolean`           | 布尔型       |
| `Function`   | `Function`          | 函数         |
| `Array`      | `Array`             | 数组         |
| `Object`     | `Object`            | 对象         |
| `ByteBuffer` | `ArrayBuffer`       | 字节数组     |

?> 感谢LiteLoader Script Engine，LLSE的文档对编写此文档起到了很大的帮助。

这些基本类型将会经常出现在 API 文档中。

## ❓ 未记录的API

在开发中，您可能会遇到实际存在，但未记录在文档的API。  
也可能遇到了文档未给出实际说明和示例，仅有函数声明和参数说明的API。

!> 这些API来源于BDS内部，我们无法得知这些API被用来做什么，  
**也无法得知使用这些API会产生什么样的后果**。  
笔者在此警告所有使用了这种API的开发者，**你最好知道你在做什么**。

# 安装和使用

## 🍳 我需要掌握什么技能？

如果你认为你自己具备基本的计算机使用能力、互联网使用能力和简单的日常英语水平，我们非常欢迎且推荐你使用Komomo。

如果你在使用中遇到任何问题，请仔细阅读本文档和LeviLamina文档。你遇到的大部分问题应该都可以在文档中找到。如果出现任何报错，请仔细阅读报错信息，并尝试移除插件直到所有插件都被移除。如果问题依然存在，请在GitHub提出issue或帮我们修复问题并发起pull request。

Komomo开发团队大多为学生，不是专职维护者，也不是客服，有较大的学业压力，因此，请不要以除issue外的方式向我们报告任何问题。此外，请不要催促我们做任何事情。

## 安装BDS

你可以跳过这一步，因为LeviLamina安装过程中会自动安装BDS。

当你的服务器的IP归属地是中国大陆时，bdsdown会自动为你配置镜像站，当然，你也可以通过定义`BDSDOWN_MIRROR_URL`环境变量来自定义镜像站，例如: `https://mcdl.bibk.top`

你也可以手动在Minecraft官网下载BDS，然后把压缩文件丢到`.cache/bdsdown`目录下，如果该目录不存在请手动创建。  
> 该目录基于您安装BDS的路径，例如`C:\Users\YourName\BDS\.cache\bdsdown`

## 💻 安装 LeviLamina

我们推荐在以下平台安装，对于其它版本的Windows，我们不保证兼容性。

* Windows Server 2019或更新版本
* Windows 10 21H2或更新版本
* Windows 11

首先，创建一个新目录用于您的 Minecraft 服务器，并进入该目录：

```sh
mkdir myserver
cd myserver
```

然后，使用 lip 安装捆绑了 Minecraft Bedrock Server 的 LeviLamina：

```sh
lip install github.com/LiteLDev/LeviLamina
```

## 安装 Komomo

> 目前项目处于开发阶段，请手动前往 Actions 查看最新版本。

下载对应平台的 Komomo-full.zip 文件，如: `Komomo-windows-full-x64.zip`

> full 为完整包，包含 LibNodeJs 和 Komomo 的依赖库

将 Komomo-windows-full-x64.zip 解压，将压缩包内 libnode.dll 和 plugins 目录复制到 bedrock_server 的根目录下

> 示例结构

```tree
├── bedrock_server
│   ├── bedrock_server_mod.exe
│   ├── node.exe
│   ├── libnode.dll
│   └── plugins
│       ├── Komomo
│       │   ├── Komomo.dll
│       │   ├── manifest.json
│       │   ├── node_modules
└──
```

启动你的 LeviLamina 服务器

## 🚅 更新 LeviLamina

当新的Minecraft基岩版发布时，你需要更新以使得服务端适配最新的客户端。

> [!WARNING]
> 请注意，部分插件、地图等对更新操作有额外要求，若按照以下步骤操作，可能导致数据损坏。请做好数据备份工作。

### 在Windows上更新BDS

更新时，请按照以下步骤操作：

1. 将服务端所在目录内，除 `allowlist.json` 、 `permissions.json` 、 `server.properties` 、 `plugins` 、 `worlds` 外所有文件删除。
2. 将新版LeviLamina适配的适用于 Minecraft 的 Bedrock 版专属服务端软件（BDS）压缩包中，除 `allowlist.json` 、 `permissions.json` 、 `server.properties` 外所有内容解压到服务端所在目录。此步骤不应出现覆盖提示。
3. 安装新版LeviLamina。
4. 将备份的文件放回到服务端所在目录，并覆盖同名文件。

### 在Windows上更新LeviLamina

如果BDS没有更新，但是LeviLamina有更新，你可以使用Lip进行更新。

不要在同一位置更新 LeviLamina，这样做会影响数据安全。相反，我们建议创建一个新目录，在那里安装 LeviLamina 的新版本，并随后将 `worlds` 目录从旧位置复制到新位置。然后，按照模组开发者提供的说明迁移您正在使用的模组的配置文件和数据文件

## 🎯 安装插件

插件分为原生插件和脚本插件两种。原生插件是经过编译的本地插件，具有更好的性能，但服务器启动后不能再启用或禁用。脚本插件由JavaScript编写，可以灵活地管理，具有更好的安全性

> [!WARNING]
> 为了保证大部分插件能够正常运行，请在 `server.properties` 中将 `online-mode` 设为 `true` ，并将 `server-authoritative-movement` 设为 `server-auth` 或 `server-auth-with-rewind` 。

### 寻找您喜爱的插件

你可以在这些网站上寻找插件：

* [MineBBS](https://www.minebbs.net/resources/)
* [Bedrinth](https://bedrinth.com)

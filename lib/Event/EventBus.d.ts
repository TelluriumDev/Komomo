/// <reference path="../Event/Listener.d.ts" />
/// <reference path="../Event/EventEnum.d.ts" />
/// <reference path="../Player/Player.d.ts" />
/// <reference path="../Actor/Actor.d.ts" />

declare namespace EventBus {
    function emplaceListener(event: "ServerStartedEvent", callback: () => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "ServerStoppingEvent", callback: () => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerAddExperienceEvent", callback: (player: Player, experience: number) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerAttackEvent", callback: (player: Player, actor: Actor, actorDamageCause: PlayerEnum.ActorDamageCause) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerChangePermEvent", callback: (player: Player, newPerm: PlayerEnum.CommandPermissionLevel) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerChatEvent", callback: (player: Player, message: string) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerConnectEvent", callback: (networkIdentifier: any, connectionRequest: any) => boolean, priority?: EventEnum.EventPriority): Listener; // TODO
    function emplaceListener(event: "PlayerDestroyBlockEvent", callback: (player: Player, blockpos: BlockPos) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerDieEvent", callback: (player: Player, source: ActorDamageSource) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerDisconnectEvent", callback: (player: Player) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerInteractBlockEvent", callback: (player: Player, blockpos: BlockPos, face: CommonEnum.FacingID, vec3: Vec3, block: Block) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerJumpEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerJoinEvent", callback: (player: Player) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerPickUpItemEvent", callback: (player: Player, itemActor: ItemActor, orgCount: number, favoredSlot: number) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerPlacingBlockEvent", callback: (player: Player, blockpos: BlockPos, face: CommonEnum.FacingID) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerPlacedBlockEvent", callback: (player: Player, blockpos: BlockPos, Block: Block) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerRespawnEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerSneakingEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerSneakedEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerSprintingEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerSprintedEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerSwingEvent", callback: (player: Player) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "PlayerUseItemEvent", callback: (player: Player, itemStack: ItemStack) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "BlockChangedEvent", callback: (blockSource: BlockSource, layer: number, previousBlock: Block, newBlock: Block, blockPos: BlockPos) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "FireSpreadEvent", callback: (blockSource: BlockSource, blockPos: BlockPos) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "LevelTickEvent", callback: (level: Level) => void, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "SpawningMobEvent", callback: (blockSource: BlockSource, identifier: ActorDefinitionIdentifier, actor: Actor, vec3: Vec3, naturalSpawn: boolean, surface: boolean, fromSpawner: boolean) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "SpawnedMobEvent", callback: (mob: Mob, blockSource: BlockSource, identifier: ActorDefinitionIdentifier, actor: Actor, vec3: Vec3, naturalSpawn: void, surface: boolean, fromSpawner: boolean) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "ActorHurtEvent", callback: (actor: Actor, actorDamageSource: ActorDamageSource, damage: number, knock: boolean, ignite: boolean) => boolean, priority?: EventEnum.EventPriority): Listener;
    function emplaceListener(event: "MobDieEvent", callback: (mob: Mob, actorDamageSource: ActorDamageSource) => void, priority?: EventEnum.EventPriority): Listener;
    // function emplaceListener(event: "ExecutingCommandEvent", callback: (mob: Mob, blockSource: BlockSource, identifier: ActorDefinitionIdentifier, actor: Actor, vec3: Vec3, naturalSpawn: boolean, surface: boolean, fromSpawner: boolean) => boolean, priority?: EventEnum.EventPriority): Listener; // TODO


    function removeListener(listener: Listener): boolean;

}
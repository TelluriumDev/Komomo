/// <reference path="../../src/API/Player/Player.h" />

/// <reference path="../Math/Vec3.d.ts" />

/// <reference path="../Player/LayeredAbilities.d.ts" />
/// <reference path="../Container/Container.d.ts" />

/// <reference path="../Actor/Actor.d.ts" />
/// <reference path="../Actor/Agent.d.ts" />
/// <reference path="../Actor/ActorUniqueID.d.ts" />

/// <reference path="../Item/Item.d.ts" />
/// <reference path="../Item/ItemStack.d.ts" />

/// <reference path="../Block/Block.d.ts" />
/// <reference path="../Block/BlockSource.d.ts" />
/// <reference path="../Block/BlockPos.d.ts" />

declare class PlayerClass {
    xuid: string | undefined;
    uuid: string | undefined;
    realName: string | undefined;
    name: string | undefined;
    IPAndPort: string | undefined;
    localeCode: string | undefined;
    shadowRadius: number | undefined;
    speed: number | undefined;
    userId: number | undefined;
    itemUseDuration: number | undefined;
    itemUseStartupProgress: number | undefined;
    itemUseIntervalProgress: number | undefined;
    maxChunkBuildRadius: number | undefined;
    blockedUsingDamagedShieldTimeStamp: number | undefined;
    blockedUsingShieldTimeStamp: number | undefined;
    blockingStartTimeStamp: number | undefined;
    chunkRadius: number | undefined;
    direction: number | undefined;
    enchantmentSeed: number | undefined;
    luck: number | undefined;
    mapIndex: number | undefined;
    maxItemCooldownLeft: number | undefined;
    interactText: string | undefined;
    playerIndex: number | undefined;
    playerLevel: number | undefined;
    selectedItemSlot: number | undefined;
    playerSessionId: string;
    platformOnlineId: string;
    serverId: string | undefined;
    sleepRotation: number | undefined;
    usedPotion: number | undefined;
    xpEarnedAtCurrentLevel: number | undefined;
    xpNeededForNextLevel: number | undefined;
    isLoading: boolean | undefined;
    isPlayerInitialized: boolean | undefined;
    isImmobile: boolean | undefined;
    isSleeping: boolean | undefined;
    isTeacher: boolean | undefined;
    isSimulated: boolean | undefined;
    isFireImmune: boolean | undefined;
    isInTrialMode: boolean | undefined;
    isBlocking: boolean | undefined;
    isSilentObserver: boolean | undefined;
    isEmoting: boolean | undefined;
    isFlying: boolean | undefined;
    isForcedRespawn: boolean | undefined;
    isHostingPlayer: boolean | undefined;
    isHungry: boolean | undefined;
    isHurt: boolean | undefined;
    isInRaid: boolean | undefined;
    isRespawningFromTheEnd: boolean | undefined;
    isSleepingLongEnough: boolean | undefined;
    isSpawned: boolean | undefined;
    isUsingItem: boolean | undefined;
    isValidSpawn: boolean | undefined;
    canStartSleepInBed: boolean | undefined;
    canExistWhenDisallowMob: boolean | undefined;
    canFreeze: boolean | undefined;
    canChangeDimensionsUsingPortal: boolean | undefined;
    canInteractWithOtherEntitiesInGame: boolean | undefined;
    canObstructSpawningAndBlockPlacement: boolean | undefined;
    canBeSeenOnMap: boolean | undefined;
    canJump: boolean | undefined;
    canOpenContainerScreen: boolean | undefined;
    canSleep: boolean | undefined;
    canUseOperatorBlocks: boolean | undefined;
    hasDiedBefore: boolean | undefined;
    hasBedPosition: boolean | undefined;
    hasOpenContainer: boolean | undefined;
    hasOwnedChunkSource: boolean | undefined;
    hasRespawnAnchorPosition: boolean | undefined;
    hasRespawnPosition: boolean | undefined;

    disconnect(reason: string): boolean | undefined;
    sendMessage(msg: string): boolean | undefined;
    setAbility(index: number, value: boolean): boolean | undefined;
    addAndRefresh(item: ItemStack): boolean | undefined;
    broadcastPlayerSpawnedMobEvent(spawnedType: number, spawnMethod: number): void;
    canUseAbility(abilityIndex: number): boolean | undefined;
    causeFoodExhaustion(exhaustionAmount: number): boolean | undefined;
    checkBed(spawnBlockSource: BlockSource, positionToCheck: Vec3): boolean | undefined;
    checkNeedAutoJump(inputMoveX: number, inputMoveZ: number): boolean | undefined;
    checkSpawnBlock(region: BlockSource): boolean | undefined;
    clearRespawnPosition(): boolean | undefined;
    completeUsingItem(): boolean | undefined;
    eat(instance: ItemStack): boolean | undefined;
    eat(hungerValue: number, saturationModifier: number): boolean | undefined;
    equippedArmorItemCanBeMoved(item: ItemStack): boolean | undefined;
    fireDimensionChangedEvent(fromDimension: any, toDimension: any): any;// TODO
    forceAllowEating(): boolean;
    getAbilities(): LayeredAbilities | undefined;
    getAgent(): Agent | undefined;
    getAgentID(): ActorUniqueID | undefined; // TODO
    getAgentIfAllowed(callerCanAccessOtherAgents: boolean, callerAgentID: ActorUniqueID): Agent | undefined;
    getBedPosition(): BlockPos;
    getCapePos(a: number): Vec3 | undefined;
    getContainerManager(): any;
    getContainerRegistryAccess(): any;
    getContainerRegistryTracker(): any;
    getCurrentActiveShield(): ItemStack | undefined;
    getDestroyProgress(): any;
    getDynamicContainerSerialization(): any;
    getExpectedSpawnDimensionId(): any;
    getExpectedSpawnPosition(): BlockPos;
    getGameMode(): GameMode | undefined;
    getInventory(): Container | undefined;
    getItemCooldownLeft(typeHash: number): number;
    getItemInUse(): ItemStack | undefined;
    getItemInteractText(item: Item): string | undefined;
    getItemStackNetManager(): any;
    getPlatform(): any;
    getItemStackNetManager(): any;
    getPlayerGameType(): any;
    getPlayerPermissionLevel(): any;
    getPlayerUIItem(playerUISlot: any): any;
    getRespawnAnchorPosition(): BlockPos;
    getSelectedItem(): ItemStack | undefined;
    getSkin(): any;
    getSpawnDimension(): any;
    getSpawnPosition(): BlockPos;
    getSupplies(): any;
    getTrackedBosses(): ActorUniqueID[] | undefined;
    getXpNeededForLevelRange(startlevel: number, endlevel: number): number | undefined;
    hasOpenContainerOfContainerType(containerType: any): any;
    hasResource(resource: any): any;
    interact(actor: Actor, location: Vec3): boolean | undefined;
    inventoryChanged(container: Container, slot: number, oldItem: ItemStack, newItem: ItemStack, forceBalanced: boolean): void;
    is2DPositionRelevant(dimension: any, position: BlockPos): any;
    isHiddenFrom(target: any): any;
    isItemOnCooldown(type: any): any;
    passengerCheckMovementStats(): boolean | undefined;
    playPredictiveSynchronizedSound(type: any, pos: Vec3, block: Block, entityType: any, isGlobal: boolean): void;
    playPredictiveSynchronizedSound(type: any, pos: Vec3, entityType: any, data: number, isGlobal: boolean): void;
    recheckRespawnPosition(): boolean | undefined;
    registerTrackedBoss(mob: ActorUniqueID): void;
    releaseUsingItem(): boolean | undefined;
    resendAllChunks(): boolean | undefined;
    resetPlayerLevel(): boolean | undefined;
    resetPublisherInitialSpawn(): boolean | undefined;
    resetToDefaultGameMode(): boolean | undefined;
    saveLastDeathLocation(tag: any): boolean | undefined;
    sendEventPacket(packet: any): boolean | undefined;
    sendPlayerTeleported(): boolean | undefined;
    sendSpawnExperienceOrbPacketToServer(): boolean | undefined;
    setAgent(agent: Agent): boolean | undefined;
    setBedRespawnPosition(bedPosition: BlockPos): boolean | undefined;
    setBlockRespawnUntilClientMessage(val: boolean): boolean | undefined;
    setChunkRadius(chunkRadius: number): boolean | undefined;
    setContainerManagerModel(manager: any): boolean;
    setCursorSelectedItem(item: ItemStack): boolean | undefined;
    setCursorSelectedItemGroup(itemGroup: any): boolean | undefined;
    setEmotingStatus(emoteTicks: number): boolean | undefined;
    setEnchantmentSeed(newSeed: number): boolean | undefined;
    setHasDied(hasDied: boolean): boolean | undefined;
    setHasSeenCredits(value: boolean): boolean | undefined;
    setInventoryOptions(options: any): boolean | undefined;
    setLastDeathDimension(dimension: any): boolean | undefined;
    setLastDeathPos(pos: BlockPos): boolean | undefined;
    setMapIndex(mapIndex: number): boolean | undefined;
    setName(newName: string): boolean | undefined;
    setPermissions(permissions: any): boolean | undefined;
    setPlatformOnlineId(platformOnlineId: string): boolean | undefined;
    setPlayerIndex(index: number): boolean | undefined;
    setPlayerUIItem(slot: any, item: ItemStack, forceBalance: boolean): boolean | undefined;
    setRespawnPosition(inRespawnPosition: BlockPos, dimension: any): boolean | undefined;
    setRespawnPositionCandidate(): boolean | undefined;
    setRespawnReady(respawnPosition: Vec3): boolean | undefined;
    setSelectedItem(item: ItemStack): boolean | undefined;
    setSelectedSlot(slot: number): any;
    setSpawnBlockRespawnPosition(spawnBlockPosition: BlockPos, dimension: any): any;
    setUsedPotion(used: boolean): boolean | undefined;
    shouldShowCredits(): boolean | undefined;
    startCooldown(item: Item, updateClient: boolean): any;
    startCooldown(type: any, tickDuration: number, updateClient: boolean): any;
    startDestroying(): boolean | undefined;
    startItemUseOn(face: any, blockPos: BlockPos, buildBlockPos: BlockPos, item: ItemStack): any;
    startUsingItem(instance: ItemStack, duration: number): any | undefined;
    stopDestroying(): boolean | undefined;
    stopGliding(): boolean | undefined;
    stopItemUseOn(blockPos: BlockPos, item: ItemStack): boolean | undefined;
    stopUsingItem(): boolean | undefined;
    take(): any;
    tickArmor(): boolean | undefined;
    tryDisableShield(): boolean | undefined;
    tryStartGliding(): boolean | undefined;
    tryStartSleeping(blockPos: BlockPos): boolean | undefined;
    unRegisterTrackedBoss(mob: ActorUniqueID): any;
    updateBlockSourceTick(): boolean | undefined;
    updateInventoryTransactions(): boolean | undefined;
    updateSkin(skin: any, clientSubID: number): boolean | undefined;
    updateTouch(): boolean | undefined;
    updateTrackedBosses(): boolean | undefined;
    useSelectedItem(itemUseMethod: any, consumeItem: boolean): any;

    static checkAndFixSpawnPosition_DEPRECATED(spawnPosition: Vec3, regions: BlockSource[], aabb: any, adjustYToSolidGround: boolean, _: boolean, searchUp: boolean, positionFromSave: boolean, spawningAtForcedSpawn: boolean, dimensionHeight: number): any;
    static checkNeedAutoJump(region: any, aabbShape: any, actorRotation: any, movementSpeed: number, stateVector: any, collisionShapeInterface: any, inputMoveX: number, inputMoveZ: number): any;
    static getCustomHurtSound(mob: any, cause: any): any;
    static isDangerousVolumeForSpawn(region: any, centeredAABB: any): any;
    static tryGetFromComponent(playerComponent: any, actorOwnerComponent: any, includeRemoved: boolean): any;
    static tryGetFromEntity(entity: any, includeRemoved: boolean): any;
    static updatePlayerGameTypeEntityData(entity: any, gameType: any, defaultGameType: any): any;
}
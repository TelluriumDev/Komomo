#include "Loader/Mod.h"
#include "Entry.h"
#include "Loader/ModManager.h"
#include "Manager/EngineData.h"

#include <ll/api/mod/Manifest.h>
#include <ll/api/mod/Mod.h>


namespace Komomo {

KomomoMod::KomomoMod(const ll::mod::Manifest& manifest) : ll::mod::Mod(std::move(manifest)) {}

KomomoMod::~KomomoMod() { release(); }

std::shared_ptr<ll::mod::Mod> KomomoMod::current() {
    return Komomo::getKomomoModManager().getMod(ENGINE_DATA()->mMod->getName());
}
} // namespace Komomo
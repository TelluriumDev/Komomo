#include "ExtraAPI/KeyValueDb/KeyValueDB.h"

ClassDefine<KeyValueDBClass> keyValueDBClassBuilder = defineClass<KeyValueDBClass>("KeyValueDB")
                                                          .constructor(nullptr)

                                                          .function("newKeyValueDB", &KeyValueDBClass::newKeyValueDB)

                                                          .instanceFunction("get", &KeyValueDBClass::get)
                                                          .instanceFunction("set", &KeyValueDBClass::set)
                                                          .instanceFunction("del", &KeyValueDBClass::del)
                                                          .instanceFunction("has", &KeyValueDBClass::has)
                                                          .instanceFunction("iter", &KeyValueDBClass::iter)
                                                          .instanceFunction("empty", &KeyValueDBClass::empty)
                                                          .instanceFunction("release", &KeyValueDBClass::release)

                                                          .build();

KeyValueDBClass::KeyValueDBClass(std::filesystem::path const& path) : ScriptClass(ConstructFromCpp<KeyValueDBClass>{}) {
    db = std::make_unique<ll::data::KeyValueDB>(path);
}

KeyValueDBClass::KeyValueDBClass(
    std::filesystem::path const& path,
    bool                         createIfMiss,
    bool                         fixIfError,
    int                          bloomFilterBit
)
: ScriptClass(ConstructFromCpp<KeyValueDBClass>{}) {
    db = std::make_unique<ll::data::KeyValueDB>(path, createIfMiss, fixIfError, bloomFilterBit);
}

Local<Object> KeyValueDBClass::newKeyValueDB(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Object::newObject());
    CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());

    if (args.size() == 1) {
        return (new KeyValueDBClass(args[0].asString().toString()))->getScriptObject();
    } else if (args.size() >= 4) {
        CheckArgTypeReturn(args[1], ValueKind::kBoolean, Object::newObject());
        CheckArgTypeReturn(args[2], ValueKind::kBoolean, Object::newObject());
        CheckArgTypeReturn(args[3], ValueKind::kNumber, Object::newObject());
        return (new KeyValueDBClass(
                    args[0].asString().toString(),
                    args[1].asBoolean().value(),
                    args[2].asBoolean().value(),
                    args[3].asNumber().toInt32()
                ))
            ->getScriptObject();
    }
    PrintArgsTooFew();
    return Object::newObject();
}
Local<Value> KeyValueDBClass::get(const Arguments& args) {
    CheckArgsCountReturn(args, 1, String::newString(""));
    CheckArgTypeReturn(args[0], ValueKind::kString, String::newString(""));

    if (!db) return String::newString("");

    try {
        return String::newString(db->get(args[0].asString().toString()).value_or(""));
    }
    CatchReturn(String::newString(""));
}

Local<Value> KeyValueDBClass::set(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kString, Boolean::newBoolean(false));

    if (!db) return Boolean::newBoolean(false);

    try {
        return Boolean::newBoolean(db->set(args[0].asString().toString(), args[1].asString().toString()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> KeyValueDBClass::del(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));

    if (!db) return Boolean::newBoolean(false);
    try {
        return Boolean::newBoolean(db->del(args[0].asString().toString()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> KeyValueDBClass::has(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));

    if (!db) return Boolean::newBoolean(false);

    try {
        return Boolean::newBoolean(db->has(args[0].asString().toString()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> KeyValueDBClass::empty(const Arguments& args) {
    if (!db) return Boolean::newBoolean(true);

    try {
        return Boolean::newBoolean(db->empty());
    }
    CatchReturn(Boolean::newBoolean(true));
}

Local<Value> KeyValueDBClass::iter(const Arguments& args) {
    auto object = Object::newObject();
    if (!db) return object;

    auto it = db->iter();
    for (auto [key, value] : it) {
        object.set(String::newString(key), String::newString(value));
    }
    return object;
}
Local<Value> KeyValueDBClass::release() {
    db.reset();
    return Local<Value>();
}
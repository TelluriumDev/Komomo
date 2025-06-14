#include "API/Nbt/Tag.h"
#include "API/APIHelper.h"
#include "Converter/Convert.h"
#include "mc/nbt/Tag.h"

ClassDefine<TagClass> tagClassBuilder = defineClass<TagClass>("Tag").constructor(nullptr).build();

Local<Object> TagClass::newTagClass(Tag* tag) { return (new TagClass(tag))->getScriptObject(); }

Local<Value> TagClass::toSnbt() { return String::newString(mTag->toSnbt()); }

Local<Value> TagClass::toString() { return String::newString(mTag->toString()); }

Local<Value> TagClass::getId() { return ConvertToScriptX<Tag::Type>(mTag->getId()); }

Local<Value> TagClass::deleteChildren() {
    mTag->deleteChildren();
    return Boolean::newBoolean(true);
}

Local<Value> TagClass::hash() { return ConvertToScriptX<>(mTag->hash()); }

Local<Value> TagClass::getTagName(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        return ConvertToScriptX<>(Tag::getTagName(ConvertFromScriptX<Tag::Type>(args[0])));
    }
    CatchReturn(String::newString(""))
}
Local<Value> TagClass::NullString() { return String::newString(Tag::NullString()); }

Local<Value> TagClass::getData() { return String::newString("此Tag无数据"); }

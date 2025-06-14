#include "API/Nbt/ByteArrayTag.h"
#include "API/APIHelper.h"
#include "Converter/Convert.h"
#include "mc/nbt/UniqueTagPtr.h"
#include <vector>


Local<Object> ByteArrayTagClass::newByteArrayTagClass(ByteArrayTag* byteArrayTag) {
    return (new ByteArrayTagClass(byteArrayTag))->getScriptObject();
}

Local<Object> ByteArrayTagClass::createByteArrayTagClass(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Object::newObject());
    CheckArgTypeReturn(args[0], ValueKind::kByteBuffer, Object::newObject());
    try {
        std::vector<uchar> vec;
        for (uchar c : args[0].asByteBuffer().describeUtf8()) {
            vec.push_back(c);
        }
        return newByteArrayTagClass(new ByteArrayTag(vec));
    }
    CatchReturn(Object::newObject());
}

Local<Value> ByteArrayTagClass::toString() { return String::newString(mByteArrayTag->toString()); }

Local<Value> ByteArrayTagClass::getId() { return ConvertToScriptX(mByteArrayTag->getId()); }

Local<Value> ByteArrayTagClass::getData() {
    try {
        auto& data = *mByteArrayTag;
        char  buf[1024];
        for (unsigned int i = 0; i < data.size(); ++i) {
            buf[i] = data[i];
        }
        return ByteBuffer::newByteBuffer(buf, data.size());
    }
    Catch;
}

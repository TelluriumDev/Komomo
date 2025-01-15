#include "API/Form/Form.h"


ClassDefine<FormClass> formClassBuilder = defineClass<FormClass>("Form")
                                              .constructor(nullptr)

                                              .function("newCustomForm", &FormClass::newCustomForm)
                                              .function("newSimpleForm", &FormClass::newSimpleForm)
                                              .function("newModalForm", &FormClass::newModalForm)

                                              .build();

FormClass::FormClass() : ScriptClass(ConstructFromCpp<FormClass>{}) {}

Local<Object> FormClass::newCustomForm(std::string title) { return CustomFormClass::newCustomForm(title); }

Local<Object> FormClass::newSimpleForm(std::string title, std::string content) {
    return SimpleFormClass::newSimpleForm(title, content);
}

Local<Object>
FormClass::newModalForm(std::string title, std::string content, std::string upperButton, std::string lowerButton) {
    return ModalFormClass::newModalForm(title, content, upperButton, lowerButton);
}

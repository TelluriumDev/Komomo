#pragma once

#include "API/APIHelper.h"       // IWYU pragma: keep
#include "API/Form/CustomForm.h" // IWYU pragma: keep
#include "API/Form/ModalForm.h"  // IWYU pragma: keep
#include "API/Form/SimpleForm.h" // IWYU pragma: keep


class FormClass : public ScriptClass {

public:
    FormClass();

public:
    static Local<Object> newCustomForm(std::string title);
    static Local<Object> newSimpleForm(std::string title, std::string content);

    static Local<Object>
    newModalForm(std::string title, std::string content, std::string upperButton, std::string lowerButton);
};

extern ClassDefine<FormClass> formClassBuilder;
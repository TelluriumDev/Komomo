/// <reference path="../Form/CustomForm.d.ts" />
/// <reference path="../Form/SimpleForm.d.ts" />
/// <reference path="../Form/ModalForm.d.ts" />

declare class Form {
    static newCustomForm(title: string): CustomForm;
    static newSimpleForm(): SimpleForm;
    static newModalForm(): ModalForm;
}
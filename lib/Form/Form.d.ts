/// <reference path="../Form/CustomForm.d.ts" />
/// <reference path="../Form/SimpleForm.d.ts" />
/// <reference path="../Form/ModalForm.d.ts" />



declare namespace Form {
    function newCustomForm(title: string): CustomForm;
    function newSimpleForm(title: string, content: string): SimpleForm;
    function newModalForm(title: string, content: string, upperButton: string, lowerButton: string): ModalForm;
}
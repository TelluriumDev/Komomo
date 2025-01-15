/// <reference path="../Player/Player.d.ts" />
/// <reference path="../Enum/FormEnum.d.ts" />

declare class CustomForm {

    setTitle(title: string): this;

    appendLabel(text: string): this;

    appendInput(name: string, text: string, placeholder?: string, defaultVal?: string): this;

    appendToggle(name: string, text: string, defaultVal?: boolean): this;

    appendDropdown(name: string, text: string, options: Array<string>, defaultVal?: string): this;

    appendSlider(name: string, text: string, min: number, max: number, step?: number, defaultVal?: number): this;

    appendStepSlider(name: string, text: string, steps: Array<string>, defaultVal?: string): this;

    sendTo(player: Player, callback?: (olayer: Player, result: Record<string, any> | ModalFormCancelReason) => void): void;

}


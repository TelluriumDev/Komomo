/// <reference path="./FormEnum.d.ts" />

declare class SimpleForm {

    setTitle(title: string): this;

    setContent(content: string): this;

    appendButton(button: string): this;

    sendTo(player: Player, callback?: (player: Player, id?: number, reason?: FormEnum.ModalFormCancelReason) => void): this;

}
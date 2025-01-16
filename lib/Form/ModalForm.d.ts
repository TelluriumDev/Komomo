/// <reference path="../Player/Player.d.ts" />

declare class ModalForm {

    setTitle(title: string): this;

    setContent(text: string): this;

    setUpperButton(text: string): this;

    setLowerButton(text: string): this;

    sendTo(player: Player, reasen?: (payer: Player, reason: Record<string, any> | FormEnum.ModalFormCancelReason) => {}): this;
}


declare class Listener { }

declare namespace Komomo {
    class EventBusClass {
        emplaceListener: (event: string, callback: Function, priority?: number) => void;
        removeListener: (listener: Listener) => void;
    }
}
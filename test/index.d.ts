export interface Canvas
{
    new (id: number, w: number, h: number): Canvas;
    render(r: number, g: number, b: number): void;
    delete(): void;
}


export interface Module
{
    _malloc(size: number): number;
    getBuffer(ptr: number, size: number): void;
    getBufferVector<T>(arr: ArrayLike<T>): void;
    Canvas: Canvas;
}
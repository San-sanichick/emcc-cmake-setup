export interface Module
{
    _malloc(size: number): number;
    getBuffer(ptr: number, size: number): void;
    getBuffer_(arr: ArrayLike): void;
}
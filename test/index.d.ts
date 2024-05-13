type GLBuffer = unknown;

interface Context
{
    GLctx: WebGL2RenderingContext;
    attributes: WebGLContextAttributes;
    handle: number;
}

export interface GL
{
    buffers: Array<GLBuffer | null>;
    byteSizeByType: Array<number>;
    byteSizeByTypeRoot: number;
    contexts: Array<Context | null>;
    counter: number;
    currentContext: Context;
    textures: Array<unknown>;
    shaders: Array<unknown>;
    calcBufLength: (size: number, type: unknown, stride: unknown, count: number) => unknown;
    createContext: (canvas: HTMLCanvasElement, attrs: WebGLContextAttributes) => number;
    deleteContext: (ctxHandle: number) => void;
    getContext: (ctxHandle: number) => Context | null;
}


export interface Canvas
{
    new (ctx: number, w: number, h: number): Canvas;
    render(r: number, g: number, b: number): void;
    getPixel(x: number, y: number): void;
    delete(): void;
}


export type Pointer = number;

export interface Module
{
    _malloc(size: number): Pointer;
    getBuffer(ptr: number, size: number): void;
    getBufferVector<T>(arr: ArrayLike<T>): void;
    HEAPU8: Uint8Array;
    GL: GL;
    Canvas: Canvas;
}
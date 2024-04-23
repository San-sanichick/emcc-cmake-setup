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
    calcBufLength: (size: number, type: unknown, stride: unknown, count: number) => unknown;
    contexts: Array<Context | null>;
    counter: number;
    createContext: (canvas: HTMLCanvasElement, attrs: WebGLContextAttributes) => number;
    currentContext: Context;
    deleteContext: (ctxHandle: number) => void;
    getContext: (ctxHandle: number) => Context | null;
    textures: Array<unknown>;
    shaders: Array<unknown>;
}


export interface Canvas
{
    new (id: number, w: number, h: number): Canvas;
    render(r: number, g: number, b: number): void;
    delete(): void;
}


export type Pointer = number;

export interface Module
{
    _malloc(size: number): Pointer;
    getBuffer(ptr: number, size: number): void;
    getBufferVector<T>(arr: ArrayLike<T>): void;
    GL: GL;
    Canvas: Canvas;
}
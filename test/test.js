import Module from "./index.mjs";
import Allocator from "./allocator.js";


/**
 * @type {import("./index").Module}
 */
const module = await Module();
// Allocator.init(module);

// const buffer = new Uint8Array(20);

// for (let i = 0; i < buffer.length; i++)
// {
//     buffer[i] = Math.floor(Math.random() * 255);
// }

// console.time("allocator")
// for (let i = 0; i < 20; i++)
// {
//     const [ptr, size] = Allocator.malloc(buffer);
//     module.getBuffer(ptr, size);
// }
// console.timeEnd("allocator")

// console.time("vector")
// for (let i = 0; i < 20; i++)
// {
//     module.getBufferVector(buffer);
// }
// console.timeEnd("vector")

/**
 * @type {WebGLContextAttributes}
 */
const attrs = {
    alpha: false,
    depth: true,
    stencil: true,
    antialias: true,
    premultipliedAlpha: true,
    preserveDrawingBuffer: true,
    failIfMajorPerformanceCaveat: true,
    majorVersion: 2,
    minorVersion: 1
}


/**
 * @see https://github.com/google/skia/blob/main/modules/canvaskit/webgl.js#L14
 * @param {string} id 
 * @returns {HTMLCanvasElement | null}
 */
function getCanvas(id)
{
    return document.querySelector(id);
}

/**
 * @see https://github.com/google/skia/blob/main/modules/canvaskit/webgl.js#L166
 * @param {HTMLCanvasElement} canvas
 * @param {WebGLContextAttributes} attrs
 * @returns {number} 
 */
function makeContext(canvas, attrs)
{
    if (canvas === null) throw new Error("Canvas is null!");
    const handle = module.GL.createContext(canvas, attrs);
    // module.GL.makeContextCurrent(handle);
    return handle;
}

/**
 * 
 * @param {number} ctx 
 */
function destroyContext(ctx)
{
    module.GL.deleteContext(ctx);
}


const canvasEl1 = getCanvas("#canvas-1");
const canvasEl2 = getCanvas("#canvas-2");
const canvasEl3 = getCanvas("#canvas-3");

const ctxHandle1 = makeContext(canvasEl1, attrs);
const ctxHandle2 = makeContext(canvasEl2, attrs);
const ctxHandle3 = makeContext(canvasEl3, attrs);

const canvas1 = new module.Canvas(ctxHandle1, canvasEl1.width, canvasEl1.height);
const canvas2 = new module.Canvas(ctxHandle2, canvasEl2.width, canvasEl2.height);
const canvas3 = new module.Canvas(ctxHandle3, canvasEl3.width, canvasEl3.height);


canvas1.render(1, 0, 0);
canvas2.render(0, 1, 0);
canvas3.render(0, 0, 1);


canvas1.delete();
canvas3.delete();
canvas2.delete();

destroyContext(ctxHandle1);
destroyContext(ctxHandle2);
destroyContext(ctxHandle3);
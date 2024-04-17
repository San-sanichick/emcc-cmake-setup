import Module from "./index.mjs";
import CanvasWrapper from "./canvas.js";
// import Allocator from "./allocator.js";


/**
 * @type {import("./index").Module}
 */
const module = await Module();
CanvasWrapper.init(module);
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

const canvas1 = new CanvasWrapper("#canvas-1", attrs);
// const canvas2 = new CanvasWrapper("#canvas-2", attrs);
// const canvas3 = new CanvasWrapper("#canvas-3", attrs);

canvas1.render(1, 0, 0);
// canvas2.render(0, 1, 0);
// canvas3.render(0, 0, 1);

canvas1.delete();
// canvas2.delete();
// canvas3.delete();
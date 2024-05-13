"use strict";

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
//     const { ptr, size } = Allocator.malloc(buffer);
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
};

const c1 = document.querySelector("#canvas-1");
const c2 = document.querySelector("#canvas-2");

// const c2 = new OffscreenCanvas(800, 600);


// const ctx1 = module.GL.createContext(c1, attrs);
// const ctx2 = module.GL.createContext(c1, attrs);


module.threaded("#canvas-1");
// const c1 = document.querySelector("#canvas-1");
// const canvas1 = new CanvasWrapper(c1, attrs);

// const offscreen = new OffscreenCanvas(canvas1.width, canvas1.height);
// const offscreenCanvas = new CanvasWrapper(offscreen, attrs);

// canvas1.render();
// offscreenCanvas.render();


// c1.addEventListener("click", (/**@type {MouseEvent}*/e) => 
// {
//     const rect = c1.getBoundingClientRect();
//     const { clientX, clientY } = e;
//     offscreenCanvas.getPixel(clientX - rect.left, clientY - rect.top);
// });

// canvas1.delete();
// offscreenCanvas.delete();
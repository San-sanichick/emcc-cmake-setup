"use strict"

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
const offscreen = new OffscreenCanvas(400, 400);
const canvas2 = new CanvasWrapper(offscreen, attrs);

canvas1.render();
canvas2.render();

const image = await offscreen.convertToBlob({ type: "image/png" });
const uri = URL.createObjectURL(image);

const img = document.createElement("img");
img.src = uri;
document.body.appendChild(img);

canvas1.delete();
canvas2.delete();
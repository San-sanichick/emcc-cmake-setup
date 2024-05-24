"use strict";

import Module from "./index.mjs";
import CanvasWrapper from "./canvas.js";
import Allocator from "./allocator.js";


/**
 * @type {import("./index").Module}
 */
const module = await Module();

CanvasWrapper.init(module);
Allocator.init(module);


const res = await fetch("./font.woff2");
const fontBuffer = await res.arrayBuffer();

const heapBuffer = Allocator.malloc(fontBuffer);

// module.test();
module.threaded("#canvas-1", "#canvas-2", heapBuffer.ptr, heapBuffer.size);
import Module from "./index.mjs";
import Allocator from "./allocator";


/**
 * @type {import("./index").Module}
 */
const module = await Module();
const buffer = new Uint8Array(100);


for (let i = 0; i < 100; i++)
{
    buffer[i] = Math.floor(Math.random() * 255);
}

const [ptr, size] = Allocator.malloc(module, buffer);

module.getBuffer(ptr, size);
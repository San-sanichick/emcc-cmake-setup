import Module from "./index.mjs";
import Allocator from "./allocator.js";


/**
 * @type {import("./index").Module}
 */
const module = await Module();
const buffer = new Uint8Array(20);


for (let i = 0; i < buffer.length; i++)
{
    buffer[i] = Math.floor(Math.random() * 255);
}

console.time("allocator")
for (let i = 0; i < 20; i++)
{
    const [ptr, size] = Allocator.malloc(module, buffer);
    module.getBuffer(ptr, size);
}
console.timeEnd("allocator")

console.time("vector")
for (let i = 0; i < 20; i++)
{
    module.getBuffer_(buffer);
}
console.timeEnd("vector")
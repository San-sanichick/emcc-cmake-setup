import Module from "./index.mjs";

const module = await Module();

function malloc(buffer)
{
    const bytes = buffer.length * buffer.BYTES_PER_ELEMENT;
    const ptr = module._malloc(bytes);
    const heapData = new Uint8Array(module.HEAPU8.buffer, ptr, bytes);
    heapData.set(buffer);
    
    return [ptr, buffer.length];
}

// const buffer = new Uint8Array([21, 32]);
const buffer = new Uint8Array(100);

for (let i = 0; i < 100; i++)
{
    buffer[i] = Math.floor(Math.random() * 255);
}

const [ptr, size] = malloc(buffer);

// module.getBuffer(new Uint8Array([21, 32]));
module.getBuffer_(buffer);
module.getBuffer(ptr, size);
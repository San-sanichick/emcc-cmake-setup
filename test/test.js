import Module from "./index.mjs";

/**
 * @typedef {Object} Module
 * @property {(size: number) => number} _malloc
 * @property {(ptr: number, size: number) => void} getBuffer
 */


class Allocator
{
    /**
     * 
     * @param {Module} module 
     * @param {Uint8Array} buffer 
     * @returns {[ number, number ]}
     */
    static malloc(module, buffer)
    {
        const bytes = buffer.length * buffer.BYTES_PER_ELEMENT;
        /**
         * @type {number}
         */
        const ptr = module._malloc(bytes);
        const heapData = new Uint8Array(module.HEAPU8.buffer, ptr, bytes);
        heapData.set(buffer);
        
        return [ptr, buffer.length];
    }
}


/**
 * @type {Module}
 */
const module = await Module();
const buffer = new Uint8Array(100);


for (let i = 0; i < 100; i++)
{
    buffer[i] = Math.floor(Math.random() * 255);
}

const [ptr, size] = Allocator.malloc(module, buffer);

module.getBuffer(ptr, size);
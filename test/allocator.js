/**
 * @typedef {import("./index").Module} Module
 */


export default class Allocator
{
    /** @type {Module} */
    static #module;

    /**
     * 
     * @param {Module} module 
     */
    static init(module)
    {
        Allocator.#module = module;
    }

    /**
     * Allocates
     * @param {Module} module 
     * @param {Uint8Array} buffer 
     * @returns {[ number, number ]}
     */
    static malloc(buffer)
    {
        const bytes = buffer.length * buffer.BYTES_PER_ELEMENT;

        /** @type {number} */
        const ptr = Allocator.#module._malloc(bytes);

        const heapData = new Uint8Array(Allocator.#module.HEAPU8.buffer, ptr, bytes);
        heapData.set(buffer);
        
        return [ptr, buffer.length];
    }
}

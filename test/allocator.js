export default class Allocator
{
    /**
     * 
     * @param {import("./index").Module} module 
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

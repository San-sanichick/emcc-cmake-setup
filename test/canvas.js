/**
 * @typedef {import("./index").Canvas} Canvas
 * @typedef {import("./index").Module} Module
 */



export default class CanvasWrapper
{
    /**
     * @type {Module}
     */
    static #module;
    
    /**
     * 
     * @param {Module} module 
     */
    static init(module)
    {
        CanvasWrapper.#module = module;
    }
    
    /**
     * @type {Canvas}
     */
    #canvasInstance;
    /**
     * @type {number}
     */
    #ctxHandle;

    /**
     * 
     * @param {string} id 
     * @param {WebGLContextAttributes} attrs
     */
    constructor(id, attrs)
    {
        const canvas = this.#getCanvas(id);
        this.#ctxHandle = this.#makeContext(canvas, attrs);
        this.#setContextActive(this.#ctxHandle);

        this.#canvasInstance = new CanvasWrapper.#module.Canvas(this.#ctxHandle, canvas.width, canvas.height);
    }
    
    delete()
    {
        this.#destroyContext();
        this.#canvasInstance.delete();
    }
    
    /**
     * 
     * @param {number} r 
     * @param {number} g 
     * @param {number} b 
     */
    render(r, g, b)
    {
        // set this context to be active, in case we lost it (we probably did)
        this.#setContextActive(this.#ctxHandle);
        this.#canvasInstance.render(r, g, b);
    }

    
    /**
     * @see https://github.com/google/skia/blob/main/modules/canvaskit/webgl.js#L14
     * @param {string} id 
     * @returns {HTMLCanvasElement | null}
     */
    #getCanvas(id)
    {
        return document.querySelector(id);
    }
    
    /**
     * @see https://github.com/google/skia/blob/main/modules/canvaskit/webgl.js#L166
     * @param {HTMLCanvasElement} canvas
     * @param {WebGLContextAttributes} attrs
     * @returns {number} 
     */
    #makeContext(canvas, attrs)
    {
        if (canvas === null) throw new Error("Canvas is null!");
        const handle = CanvasWrapper.#module.GL.createContext(canvas, attrs);
        CanvasWrapper.#module.GL.makeContextCurrent(handle);
        return handle;
    }
    
    /**
     * 
     * @param {number} handle
     * @returns {void} 
     */
    #setContextActive(handle)
    {
        CanvasWrapper.#module.GL.makeContextCurrent(handle)
    }
    
    /**
     * 
     * @param {number} ctx 
     */
    #destroyContext(ctx)
    {
        CanvasWrapper.#module.GL.deleteContext(ctx);
    }
}
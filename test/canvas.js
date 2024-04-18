/**
 * @typedef {import("./index").Canvas} Canvas
 * @typedef {import("./index").Module} Module
 * 
 * @typedef {number} WebGLContextHandle
 */



export default class CanvasWrapper
{
    /**
     * @type {Module}
     */
    static #module;

    /**
     * @param {Module} module 
     * @returns {void}
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
     * @type {WebGLContextHandle}
     */
    #ctxHandle;
    /**
     * @type {HTMLCanvasElement}
     */
    #canvas;


    /**
     * 
     * @param {string} id 
     * @param {WebGLContextAttributes} attrs
     */
    constructor(id, attrs)
    {
        this.#canvas    = this.#getCanvas(id);
        this.#ctxHandle = this.#makeContext(this.#canvas, attrs);
        this.#setContextActive(this.#ctxHandle);
        this.#canvasInstance = new CanvasWrapper.#module.Canvas(this.#ctxHandle, this.#canvas.width, this.#canvas.height);
    }

    /**
     * Destroy the context and the WASM instance
     * @returns {void}
     */
    delete()
    {
        // again, in case we switched contexts, we need to make this one current
        this.#setContextActive(this.#ctxHandle);
        this.#canvasInstance.delete();
        this.#destroyContext();
    }

    /**
     * 
     * @param {number} r 
     * @param {number} g 
     * @param {number} b 
     * @returns {void}
     */
    render(r, g, b)
    {
        // set this context to be active, in case we switched it (we probably did)
        this.#setContextActive(this.#ctxHandle);
        this.#canvasInstance.render(r, g, b);
    }

    /**
     * Get the underlying HTMLCanvasElement
     * @returns {HTMLCanvasElement}
     */
    getHTMLCanvas()
    {
        return this.#canvas;
    }

    /**
     * Get the underlying context handle
     * @returns {WebGLContextHandle}
     */
    getContextHandle()
    {
        return this.#ctxHandle;
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
     * @returns {WebGLContextHandle} 
     */
    #makeContext(canvas, attrs)
    {
        if (!canvas) throw new Error("Canvas is null!");
        const handle = CanvasWrapper.#module.GL.createContext(canvas, attrs);
        CanvasWrapper.#module.GL.makeContextCurrent(handle);
        return handle;
    }

    /**
     * 
     * @param {WebGLContextHandle} handle
     * @returns {void} 
     */
    #setContextActive(handle)
    {
        CanvasWrapper.#module.GL.makeContextCurrent(handle)
    }

    /**
     * 
     * @param {WebGLContextHandle} ctx 
     */
    #destroyContext(ctx)
    {
        CanvasWrapper.#module.GL.deleteContext(ctx);
    }
}
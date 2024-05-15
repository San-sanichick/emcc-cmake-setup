"use strict"

/**
 * @typedef {import("./index").Canvas} Canvas
 * @typedef {import("./index").Module} Module
 * 
 * @typedef {number} WebGLContextHandle
 */


/**
 * Wrapper for a WASM wrapper (lol) around WebGL and Canvas
 */
export default class CanvasWrapper
{
    /** @type {Module} */
    static #module;

    /**
     * @param {Module} module 
     * @returns {void}
     */
    static init(module)
    {
        CanvasWrapper.#module = module;
    }


    /** @type {Canvas} */
    #canvasInstance;
    /** @type {WebGLContextHandle} */
    #ctxHandle;
    /** @type {HTMLCanvasElement | OffscreenCanvas} */
    #canvas;


    /**
     * 
     * @param {string | HTMLCanvasElement | OffscreenCanvas} canvas 
     * @param {WebGLContextAttributes} attrs
     */
    constructor(canvas, attrs)
    {
        if (typeof canvas === "string")
        {
            this.#canvas = this.#getCanvas(canvas);
        }
        else
        {
            this.#canvas = canvas;
        }
        
        //* context has to be made in JS, since in C++ emscripten API only allows
        //* making context based on a HTML selector, which is silly
        this.#ctxHandle = this.#makeContext(this.#canvas, attrs);
        
        this.#canvasInstance = new CanvasWrapper.#module.Canvas(
            this.#ctxHandle,
            this.#canvas.width,
            this.#canvas.height
        );
    }

    /**
     * Destroy the context and the WASM instance
     * @returns {void}
     */
    delete()
    {
        this.#canvasInstance.delete();
        CanvasWrapper.#module.GL.deleteContext(this.#ctxHandle);
    }
    
    get width()
    {
        return this.#canvas.width;
    }
    
    get height()
    {
        return this.#canvas.height;
    }


    /**
     * 
     * @returns {void}
     */
    render()
    {
        this.#canvasInstance.render()
    }
    
    
    /**
     * 
     * @param {number} x 
     * @param {number} y 
    */
    getPixel(x, y)
    {
        this.#canvasInstance.getPixel(x, y);
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
     * @param {HTMLCanvasElement | OffscreenCanvas} canvas
     * @param {WebGLContextAttributes} attrs
     * @returns {WebGLContextHandle} 
     */
    #makeContext(canvas, attrs)
    {
        if (!canvas) throw new Error("Canvas is null!");
        return CanvasWrapper.#module.GL.createContext(canvas, attrs);
    }
}
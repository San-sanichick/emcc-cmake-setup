import Module from "./index.js";

const module = await Module();

const canvas = document.querySelector("#canvas");
module.getCanvas(canvas);
// const v = new module.Vec2(1, 2);
// console.log(v.X, v.Y);


// const v2 = new module.Vec2();
// console.log(v2.X, v2.Y);

// v2.set(v.X, v.Y);
// console.log(v2.X, v2.Y);


// v.set(69, 420);
// const v3 = new module.Vec2(v);
// console.log(v3.X, v3.Y);

// v.delete();
// v2.delete();
// v3.delete();
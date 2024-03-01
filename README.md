# Setup project
## Clone
Clone using

```bash
git clone --recurse-submodules https://github.com/San-sanichick/emcc-cmake-setup.git
```

Then run

```bash
bash setup.sh
```

## Build
To build Release

```bash
bash build.sh
```

To build Debug

```bash
bash build_debug.sh
```


## Test
To test, create an index.html file in the "target" folder, and add these lines into it

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <script type="module">
        import Module from "./index.js";

        const module = await Module();
        console.log(module.lerp(1, 4, 0.8));
    </script>
</body>
</html>
```
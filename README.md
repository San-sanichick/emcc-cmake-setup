# Setup project
This is starter project that can cross-compile both to WASM with Emscripten
and a native Linux executable with gcc.

## Clone
Clone using

```bash
git clone --recursive https://github.com/San-sanichick/emcc-cmake-setup.git
```

Then run

```bash
bash setup.sh
```

## Build WASM

### Build Release

```bash
bash build.sh -r
or
bash build.sh --release
```

### Build Debug

```bash
bash build.sh -d
or
bash build.sh --debug
```

## Build native Linux executable

### Build Release

```bash
bash build.sh -r -n
or
bash build.sh --release --native
```

### Build Debug

```bash
bash build.sh -d -n
or
bash build.sh --debug --native
```

## Clean
Depending on whether or not CMAKE has generated any cache files previously, 
you may have to add -c or --clean flag to clear CMAKE cache.


## Test

### WASM
```bash
bash test.sh
```

### Native executable
Run the "index" executable in the "target/native" directory.
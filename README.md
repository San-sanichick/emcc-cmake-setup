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

## Build WASM
To build Release

```bash
bash build.sh -r
or
bash build.sh --release
```

To build Debug

```bash
bash build.sh -d
or
bash build.sh --debug
```

## Build native Linux binary
To build Release

```bash
bash build.sh -r -n
or
bash build.sh --release --native
```

To build Debug

```bash
bash build.sh -d -n
or
bash build.sh --debug --native
```

Depending on whether or not CMAKE has generated any cache files previously, 
you may have to add -c or --clean flag to clear CMAKE cache.


## Test
To test, run build and run a server in the "test" directory.

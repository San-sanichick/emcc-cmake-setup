#!/bin/bash

# build skia for wasm
cd vendors/skia
cd out
rm -rf wasm/*

cd ..


bin/gn gen out/wasm --args='is_official_build=true target_cpu="wasm" skia_enable_skottie=false skia_enable_pdf=false skia_enable_vulkan_debug_layers=false skia_use_expat=false skia_use_piex=false skia_use_perfetto=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false skia_use_system_icu=false skia_use_system_harfbuzz=false skia_canvaskit_enable_alias_font=false skia_canvaskit_enable_canvas_bindings=false skia_canvaskit_enable_effects_deserialization=false skia_canvaskit_enable_embedded_font=false skia_canvaskit_enable_font=false skia_canvaskit_enable_matrix_helper=false skia_canvaskit_enable_paragraph=false skia_canvaskit_enable_pathops=false skia_canvaskit_enable_rt_shader=false skia_canvaskit_enable_skp_serialization=false skia_canvaskit_enable_sksl_trace=false'
third_party/ninja/ninja -C out/wasm
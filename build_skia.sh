#!/bin/bash

main()
{
    wasm=true
    wasm_thread=false
    native=false

    while [[ $# -gt 0 ]];
    do
        case "$1" in
            -w|--wasm)
                wasm=true
                ;;
            -wpt)
                wasm_thread=true
                wasm=false
                ;;
            -n|--native)
                native=true
                wasm=false
                ;;
        esac
        shift
    done
    
    if ([ "$native" = false ] && [ "$wasm" = false ]); then
        echo "Incorrect flags"     
        exit 1
    fi


    cd vendors/skia
    if [ -d out ]; then
        cd out

        if [ "$wasm" = true ]; then
            rm -rf wasm/*
        elif [ "$wasm_thread" = true ]; then
            rm -rf wasm_thread/* 
        elif [ "$native" = true ]; then
            rm -rf static/*
        fi

        cd ..
    fi


    if [ "$wasm_thread" = true ]; then
        
        line=$(sed -n '1723p' BUILD.gn)
        if [[ "$line" == *"canvaskit"* ]]; then
            echo "Purge the canvaskit dependecy to stop builds from failing"
            sed -i '1722,1724d' BUILD.gn
        fi

        # build skia for wasm
        args=(
            "is_official_build=true"
            "is_debug=false"
            "target_cpu=\"wasm\""
            "extra_cflags=[\"-pthread\"]"
            "skia_enable_tools=false"
            "third_party_isystem=false"
            "skia_use_webgpu=false"
            "skia_enable_skottie=false"
            "skia_enable_pdf=false"
            "skia_enable_vulkan_debug_layers=false"
            "skia_use_expat=false"
            "skia_use_piex=false"
            "skia_use_perfetto=false"
            "skia_use_system_libjpeg_turbo=false"
            "skia_use_system_libpng=false"
            "skia_use_system_libwebp=false"
            "skia_use_system_zlib=false"
            "skia_use_system_icu=false"
            "skia_use_system_harfbuzz=false"
            "skia_canvaskit_enable_alias_font=false"
            "skia_canvaskit_enable_canvas_bindings=false"
            "skia_canvaskit_enable_effects_deserialization=false"
            "skia_canvaskit_enable_embedded_font=false"
            "skia_canvaskit_enable_font=false"
            "skia_canvaskit_enable_matrix_helper=false"
            "skia_canvaskit_enable_paragraph=false"
            "skia_canvaskit_enable_pathops=false"
            "skia_canvaskit_enable_rt_shader=false"
            "skia_canvaskit_enable_skp_serialization=false"
            "skia_canvaskit_enable_sksl_trace=false"
        )
        
        printf -v arg "%s " "${args[@]}"
        echo $arg

        bin/gn gen out/wasm_thread --args="$arg"
        third_party/ninja/ninja -C out/wasm_thread
    elif [ "$wasm" = true ]; then
        
        line=$(sed -n '1723p' BUILD.gn)
        if [[ "$line" == *"canvaskit"* ]]; then
            echo "Purge the canvaskit dependecy to stop builds from failing"
            sed -i '1722,1724d' BUILD.gn
        fi

        # build skia for wasm
        args=(
            "is_official_build=true"
            "is_debug=false"
            "target_cpu=\"wasm\""
            "skia_enable_tools=false"
            "third_party_isystem=false"
            "skia_use_webgpu=false"
            "skia_enable_skottie=false"
            "skia_enable_pdf=false"
            "skia_enable_vulkan_debug_layers=false"
            "skia_use_expat=false"
            "skia_use_piex=false"
            "skia_use_perfetto=false"
            "skia_use_system_libjpeg_turbo=false"
            "skia_use_system_libpng=false"
            "skia_use_system_libwebp=false"
            "skia_use_system_zlib=false"
            "skia_use_system_icu=false"
            "skia_use_system_harfbuzz=false"
            "skia_canvaskit_enable_alias_font=false"
            "skia_canvaskit_enable_canvas_bindings=false"
            "skia_canvaskit_enable_effects_deserialization=false"
            "skia_canvaskit_enable_embedded_font=false"
            "skia_canvaskit_enable_font=false"
            "skia_canvaskit_enable_matrix_helper=false"
            "skia_canvaskit_enable_paragraph=false"
            "skia_canvaskit_enable_pathops=false"
            "skia_canvaskit_enable_rt_shader=false"
            "skia_canvaskit_enable_skp_serialization=false"
            "skia_canvaskit_enable_sksl_trace=false"
        )
        
        printf -v arg "%s " "${args[@]}"
        echo $arg

        bin/gn gen out/wasm --args="$arg"
        third_party/ninja/ninja -C out/wasm
    elif [ "$native" = true ]; then
        args=(
            "is_official_build=true"
            "is_debug=false"
            "extra_cflags=[\"-march=native\"]"
            "skia_enable_tools=false"
            "third_party_isystem=false"
            "skia_use_webgpu=false"
            "skia_enable_skottie=false"
            "skia_enable_pdf=false"
            "skia_enable_vulkan_debug_layers=false"
            "skia_use_expat=false"
            "skia_use_piex=false"
            "skia_use_perfetto=false"
        )
        
        printf -v arg "%s " "${args[@]}"
        echo $arg

        # build skia for native
        bin/gn gen out/static --args="$arg"
        third_party/ninja/ninja -C out/static
    fi
}


time main "$@"

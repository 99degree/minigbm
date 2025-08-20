          meson setup "build-android" \
            --prefix=/tmp/drm-static \
            --cross-file "./build-crossfile-drm" \
            -Ddefault_library=static \
            -Dintel=disabled \
            -Dradeon=disabled \
            -Damdgpu=disabled \
            -Dnouveau=disabled \
            -Dvmwgfx=disabled \
            -Dfreedreno=enabled \
            -Dvc4=disabled \
            -Detnaviv=disabled \
            -Dfreedreno-kgsl=true
          ninja -C "build-android" install

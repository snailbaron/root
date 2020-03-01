set(
    aseprite_assets
        ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps/farmer.aseprite
        ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps/grass.aseprite
)

set(gfx_data_file gfx-data.png)
set(gfx_meta_file gfx-meta.json)

add_custom_command(
    COMMENT "packing aseprite data"
    OUTPUT
        ${gfx_data_file}
        ${gfx_meta_file}
    COMMAND
        $<TARGET_FILE:aseprite>
            --batch
            --data ${gfx_meta_file}
            --filename-format "{title}-{frame}"
            --format json-array
            --sheet ${gfx_data_file}
            --sheet-type packed
    DEPENDS aseprite
)

add_custom_target(
    run-aseprite
    DEPENDS ${gfx_data_file} ${gfx_meta_file}
)

set(
    aseprite_assets
        ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps/farmer.aseprite
        ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps/grass.aseprite
)

set(gfx_data_file ${PROJECT_BINARY_DIR}/data/gfx-data.png)
set(gfx_meta_file ${PROJECT_BINARY_DIR}/data/gfx-meta.json)

add_custom_command(
    COMMENT "packing aseprite data"
    OUTPUT
        ${gfx_data_file}
        ${gfx_meta_file}
    COMMAND
        $<TARGET_FILE:aseprite>
            --batch
            --data ${gfx_meta_file}
            --filename-format "{title}:{tag}:{tagframe}"
            --format json-array
            --sheet ${gfx_data_file}
            --sheet-type packed
            ${aseprite_assets}
    DEPENDS aseprite ${aseprite_assets}
)

add_custom_target(
    run-aseprite
    DEPENDS ${gfx_data_file} ${gfx_meta_file}
)

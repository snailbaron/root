add_executable(
    root
        main.cpp
        player-terminal.cpp
        resources.cpp
        util.cpp
)

set_target_properties(
    root
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_dependencies(root run-aseprite)
target_link_libraries(
    root
        PRIVATE
            sfml-graphics
            nlohmann_json::nlohmann_json

            evening
            root-lib
)

add_executable(
    root
        entity-system.cpp
        main.cpp
        player-terminal.cpp
        resources.cpp
        timers.cpp
        util.cpp
        world.cpp
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
)

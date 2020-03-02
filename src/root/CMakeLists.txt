add_executable(
    root
        entity-system.cpp
        frame_timer.cpp
        main.cpp
        player-terminal.cpp
        world.cpp
)

add_dependencies(root run-aseprite)
target_link_libraries(
    root
        PRIVATE
            SDL2
            SDL2main
            nlohmann_json::nlohmann_json
)

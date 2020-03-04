add_executable(
    root
        camera.cpp
        entity-system.cpp
        main.cpp
        player-terminal.cpp
        resources.cpp
        sprite.cpp
        timers.cpp
        world.cpp
)

add_dependencies(root run-aseprite)
target_link_libraries(
    root
        PRIVATE
            SDL2
            SDL2main
            nlohmann_json::nlohmann_json
            evening
)

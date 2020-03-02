add_executable(
    root
        frame_timer.cpp
        main.cpp
        player-terminal.cpp
)

add_dependencies(root run-aseprite)
target_link_libraries(root PRIVATE SDL2 SDL2main)

add_executable(
    root-server
        main.cpp
)

set_target_properties(
    root-server
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

target_link_libraries(
    root-server
        PRIVATE
            root-lib

            sfml-network
)

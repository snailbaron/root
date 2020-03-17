add_custom_command(
    COMMENT "compiling proto file"
    OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/include/events.pb.h"
        "${CMAKE_CURRENT_BINARY_DIR}/include/events.pb.cc"
    COMMAND
        ${CMAKE_COMMAND} -E
            make_directory "${CMAKE_CURRENT_BINARY_DIR}/include"
    COMMAND
        $<TARGET_FILE:protoc>
            --proto_path "${CMAKE_CURRENT_SOURCE_DIR}"
            --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/events.proto"
    DEPENDS
        protoc
        "${CMAKE_CURRENT_SOURCE_DIR}/events.proto"
)

add_library(
    root-lib
        "${CMAKE_CURRENT_BINARY_DIR}/include/events.pb.cc"

        entity-system.cpp
        events.cpp
        timers.cpp
        world.cpp
)
target_include_directories(
    root-lib PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(root-lib PUBLIC evening libprotobuf)

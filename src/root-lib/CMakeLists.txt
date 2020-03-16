find_package(Protobuf REQUIRED)

add_custom_command(
    COMMENT "compiling proto file"
    OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/root.pb.h"
        "${CMAKE_CURRENT_BINARY_DIR}/root.pb.cc"
    COMMAND
        ${Protobuf_PROTOC_EXECUTABLE}
            --proto_path "${CMAKE_CURRENT_SOURCE_DIR}"
            --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/root.proto"
    COMMAND
        ${CMAKE_COMMAND} -E create_symlink 
            "${CMAKE_CURRENT_BINARY_DIR}/root.pb.cc"
            "${CMAKE_CURRENT_SOURCE_DIR}/root.pb.cc"
    COMMAND
        ${CMAKE_COMMAND} -E create_symlink 
            "${CMAKE_CURRENT_BINARY_DIR}/root.pb.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/root.pb.h"
    DEPENDS
        ${Protobuf_PROTOC_EXECUTABLE}
        "${CMAKE_CURRENT_SOURCE_DIR}/root.proto"
)

add_custom_target(
    run-protoc
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/root.pb.h"
        "${CMAKE_CURRENT_BINARY_DIR}/root.pb.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/root.pb.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/root.pb.cc"
)

add_library(
    root-lib
        dummy.cpp
)
add_dependencies(root-lib run-protoc)

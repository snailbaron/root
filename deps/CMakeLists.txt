set(ENABLE_NEWS OFF CACHE BOOL "")
set(ENABLE_SCRIPTING OFF CACHE BOOL "")
set(ENABLE_UI OFF CACHE BOOL "")
set(ENABLE_UPDATER OFF CACHE BOOL "")
set(WITH_WEBP_SUPPORT OFF CACHE BOOL "")
add_subdirectory(aseprite)

add_subdirectory(SFML)
add_subdirectory(evening)
add_subdirectory(json)

set(protobuf_WITH_ZLIB OFF CACHE BOOL "")
add_subdirectory(protobuf/cmake)


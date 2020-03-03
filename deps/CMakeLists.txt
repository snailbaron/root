set(ENABLE_NEWS OFF CACHE BOOL "")
set(ENABLE_SCRIPTING OFF CACHE BOOL "")
set(ENABLE_UI OFF CACHE BOOL "")
set(ENABLE_UPDATER OFF CACHE BOOL "")
set(WITH_WEBP_SUPPORT OFF CACHE BOOL "")
add_subdirectory(aseprite)

add_subdirectory(evening)
add_subdirectory(json)

include(FetchContent)
FetchContent_Declare(
    SDL2
    URL "https://www.libsdl.org/release/SDL2-2.0.10.tar.gz"
    URL_MD5 "5a2114f2a6f348bdab5bf52b994811db"
)
FetchContent_MakeAvailable(SDL2)

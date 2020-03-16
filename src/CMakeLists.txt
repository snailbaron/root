if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(root-lib)
add_subdirectory(root-server)
add_subdirectory(root)

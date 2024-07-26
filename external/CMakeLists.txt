list(APPEND EXTERNAL_INCLUDES "glfw/include" "stb_image")
set(EXTERNAL_LIBS "glfw/lib/glfw3.lib")
add_subdirectory("glad")


# assimp library set ( ASSIMP_BUILD_TESTS OFF) set( ASSIMP_INSTALL ON)
set ( ASSIMP_WARNINGS_AS_ERRORS OFF)
add_subdirectory("assimp")
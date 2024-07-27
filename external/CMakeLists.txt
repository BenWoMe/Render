list(APPEND EXTERNAL_INCLUDES "glfw/include" "stb_image")
set(EXTERNAL_LIBS "glfw/lib/glfw3.lib")
add_subdirectory("glad")


# assimp library 

set ( ASSIMP_BUILD_TESTS OFF) 
set( ASSIMP_INSTALL OFF)
set ( ASSIMP_WARNINGS_AS_ERRORS OFF)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF)
set(BUILD_SHARED_LIBS OFF)
set(ASSIMp_IFC_BUILD OFF)
add_subdirectory("assimp")
target_include_directories(assimp PUBLIC "${CMAKE_BINARY_DIR}/external/assimp/include")

if(${BUILD_SHARED_LIBS})
    target_compile_definitions(assimp  PRIVATE ASSIMP_BUILD_DLL_EXPORT)
else()
    target_compile_definitions(assimp PRIVATE P2T_STATIC_EXPORTS)
endif()
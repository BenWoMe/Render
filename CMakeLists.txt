cmake_minimum_required(VERSION 3.26.0)

project(opengl LANGUAGES C CXX)
# 设置c++版本和编译器
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_C_COMPILER "D:/software/VisualStudio/VC/Tools/MSVC/14.35.32215/bin/Hostx64/x64/cl.exe")
#set(CMAKE_CXX_COMPILER "D:/software/VisualStudio/VC/Tools/MSVC/14.35.32215/bin/Hostx64/x64/cl.exe")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 只有Makefile 和Ninja支持该选项

if(MSVC)
    add_compile_options(/EHsc)
endif()


add_subdirectory("external")
add_executable(opengl "main.cpp" "vertex.cpp")
target_include_directories(opengl PUBLIC  "external/glfw/include" "external/stb_image" "external/glm" "external/glad/include" "external/assimp/include")
target_include_directories(opengl PUBLIC "${CMAKE_BINARY_DIR}/external/assimp/include")
target_link_directories(opengl PUBLIC "external/glfw/lib")
target_link_libraries(opengl PUBLIC "glfw3" GLAD "opengl32" assimp) # 指定cmake中的库或者第三方库的名字, 注意assimp生成的库的名字是assimpd

target_compile_definitions(opengl PUBLIC _Debug)


# file(COPY build/external/assimp/bin/assimpd.dll DESTINATION build/) # 仅在config阶段进行文件拷贝
if(${BUILD_SHARED_LIBS})
    target_compile_definitions(opengl PUBLIC ASSIMP_DLL)
    set(ASSIMP_DLL_PATH ${CMAKE_BINARY_DIR}/external/assimp/bin/assimp.dll)
    set(ASSIMP_STATIC_PATH ${CMAKE_BINARY_DIR}/external/assimp/lib/assimp.lib)
    set(ASSIMP_PDB_PATH ${CMAKE_BINARY_DIR}/external/assimp/bin/assimp.pdb)
    add_custom_command(
        TARGET opengl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_DLL_PATH} ${CMAKE_BINARY_DIR}/assimp.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_STATIC_PATH} ${CMAKE_BINARY_DIR}/assimp.lib
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_PDB_PATH} ${CMAKE_BINARY_DIR}/assimp.pdb
    )
endif()
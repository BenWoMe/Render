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
add_executable(opengl "main.cpp")
target_include_directories(opengl PUBLIC "external/glfw/include" "external/stb_image" "external/glm")
target_link_directories(opengl PUBLIC "external/glfw/lib")
target_link_libraries(opengl PUBLIC "glfw3" GLAD "opengl32" "assimp") # 指定cmake中的库或者第三方库的名字
target_compile_definitions(opengl PUBLIC _CRT_SECURE_NO_WARNINGS)

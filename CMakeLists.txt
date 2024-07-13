cmake_minimum_required(VERSION 3.2)

project(opengl LANGUAGES C CXX)
# 设置c++版本和编译器
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.34.31933/bin/Hostx64/x64/cl.exe")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/EHsc)
endif()


add_subdirectory("external")
add_executable(opengl "main.cpp")
target_include_directories(opengl PUBLIC "external/glfw/include" "external/stb_image" "external/glm")
target_link_directories(opengl PUBLIC "external/glfw/lib")
target_link_libraries(opengl PUBLIC "glfw3" GLAD "opengl32") # 指定cmake中的库或者第三方库的名字

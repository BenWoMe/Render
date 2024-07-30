# Render
This is a render project based on OpenGL.

## Dependencies
+ glfw
+ glad
+ assimp
+ glm

## build
Suggest using clang to compile this project.Other compiler can't be guranteed to work on.
```cmake
cmake -B build -G Ninja
cmake --build build
```

## to be continued.

1. copy operation of program (consider uniform)
2. texture  
3. a bug of glUseProgram(0)
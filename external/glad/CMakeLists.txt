add_library(GLAD STATIC "src/glad.c")
target_include_directories(GLAD PUBLIC "include")
set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE C)
set_target_properties(GLAD PROPERTIES COMPILER_LANGUAGE C)
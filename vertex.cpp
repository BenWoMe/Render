#include"vertex.hpp"

std::unordered_map<int, std::size_t> g_typeSize={
    {GL_FLOAT, 4},
    {GL_INT, 4},
    {GL_UNSIGNED_INT, 4},
    {GL_UNSIGNED_BYTE, 1}
};
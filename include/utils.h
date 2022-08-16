#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint CompileShader(GLenum aShaderType, const char* aShaderPath);
void ProcessInput(GLFWwindow* window);
//unsigned char* LoadTexture();
#include "utils.h"

GLuint CompileShader(GLenum aShaderType, const char* aShaderPath)
{
	switch (aShaderType)
	{
	case GL_VERTEX_SHADER:
		[[fallthrough]];
	case GL_FRAGMENT_SHADER:
		break;
	default: assert(false && "Unsupported shader type");
	}

	std::ifstream shaderFile(aShaderPath);

	assert(shaderFile.is_open() && "File not exsist");
	std::stringstream codeText;
	codeText << std::ifstream(aShaderPath).rdbuf();
	std::string shaderStr = codeText.str();
	const char* shaderSrc = shaderStr.c_str();

	GLuint shader = glCreateShader(aShaderType);
	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compile error: \n" << infoLog << std::endl;
	}

	return shader;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "shader.h"

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile) {
  program = glCreateProgram();

  addShaderToProgram(GL_VERTEX_SHADER, vertexShaderFile);
  addShaderToProgram(GL_FRAGMENT_SHADER, fragmentShaderFile);

  glLinkProgram(program);
};

void Shader::addShaderToProgram(GLuint type, std::string file) {
  GLuint shader = glCreateShader(type);
  glCompileShader(shader);
  glAttachShader(program, shader);
};

void Shader::bind() {
  glUseProgram(program);
};

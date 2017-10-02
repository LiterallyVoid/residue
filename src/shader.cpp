
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"
#include "file.h"

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile) {
  program = glCreateProgram();

  addShaderToProgram(GL_VERTEX_SHADER, vertexShaderFile);
  addShaderToProgram(GL_FRAGMENT_SHADER, fragmentShaderFile);

  glLinkProgram(program);
};

Shader::~Shader() {
  glDeleteProgram(program);
};

void Shader::addShaderToProgram(GLuint type, std::string file) {
  GLuint shader = glCreateShader(type);
  std::string data = readFile(file);
  const char *cstr = data.c_str();
  glShaderSource(shader, 1, (const GLchar**)&cstr, 0);
  glCompileShader(shader);

  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    printf("%s\n", &errorLog[0]);

    glDeleteShader(shader);
    return;
  }

  glAttachShader(program, shader);
  glDeleteShader(shader);
};

void Shader::bind() {
  glUseProgram(program);
};

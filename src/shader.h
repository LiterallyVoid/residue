/* -*- mode: c++ -*- */

#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Shader {
public:
  Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
  ~Shader();

  void bind();

private:
  void addShaderToProgram(GLuint type, std::string file);

  GLuint program;
  GLuint vertexShader, fragmentShader;
};

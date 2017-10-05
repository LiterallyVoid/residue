/* -*- mode: c++ -*- */

#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Shader {
public:
  /**
     Creates a new shader.
     @param vertexShaderFile The file path of the vertex shader.
     @param fragmentShaderFile The file path of the fragment shader.
  **/
  Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
  ~Shader();

  /**
     Binds the shader.

     This makes it so any subsequent draw calls use this shader.
  **/
  void bind();

private:
  /**
     Add a shader to the shaderProgram.

     @param type GL_FRAGMENT_SHADER or GL_VERTEX_SHADER, depending on if this is a fragment or vertex shader, respectively.
     @param file The filepath to load the shader from.
  **/
  void addShaderToProgram(GLuint type, std::string file);

  /**
     The shaderProgram.
  **/
  GLuint program;

  /**
     The vertex and fragment shader, respectively.
  **/
  GLuint vertexShader, fragmentShader;
};

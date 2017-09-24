/* -*- mode: c++ -*- */

#pragma once

#include <string>

class Texture {
public:
  Texture(std::string filename);
  ~Texture();

  void bind();

private:
  unsigned int gl_id; // OpenGL texture identifier

  unsigned int width;
  unsigned int height;
};

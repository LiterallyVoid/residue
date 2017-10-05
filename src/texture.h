/* -*- mode: c++ -*- */

#pragma once

#include <string>

class Texture {
public:
  /**
     Load a texture.

     @param filename The filename of the texture.
  **/
  Texture(std::string filename);
  ~Texture();

  /**
     Use this texture in subsequent draw calls.
  **/
  void bind();

private:
  /**
     The number OpenGL uses to identify this texture.
  **/
  unsigned int gl_id;

  /**
     The width and height, respectively, of this texture.
  **/
  unsigned int width;
  unsigned int height;
};

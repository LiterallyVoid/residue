
#include <X11/Xlib.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdlib.h>

#include <png.h>

#include "texture.h"

Texture::Texture(std::string filename) {
  png_image img;
  img.version = PNG_IMAGE_VERSION;
  img.opaque = NULL;
  png_image_begin_read_from_file(&img, filename.c_str());
  img.format = PNG_FORMAT_RGBA;

  width = img.width;
  height = img.height;

  unsigned char *imgbuf = new unsigned char[PNG_IMAGE_SIZE(img)];
  png_image_finish_read(&img, NULL, imgbuf, PNG_IMAGE_ROW_STRIDE(img), NULL);

  glGenTextures(1, &gl_id);

  glBindTexture(GL_TEXTURE_2D, gl_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgbuf);

  glBindTexture(GL_TEXTURE_2D, gl_id);

  png_image_free(&img);

  delete imgbuf;
};

void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, gl_id);
};

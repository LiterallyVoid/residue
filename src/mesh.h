/* -*- mode: c++ -*- */

#pragma once

#include <vector>
#include "shader.h"

struct Vertex {
  float x, y, z;
  float u, v;
};

class Mesh {
public:
  Mesh();
  ~Mesh();

  void draw();

  void clear();
  void addVertex(Vertex vert);

private:

  void refresh();

  bool dirty;

  GLuint vbo;
  Shader *shader;

  std::vector<Vertex> vertices;
};

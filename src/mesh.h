/* -*- mode: c++ -*- */

#pragma once

#include <vector>
#include "shader.h"

struct Vertex {
  /**
     The coordinates of the veretx.
  **/
  float x, y, z;
  /**
     The UV coordinates of the veretx.
  **/
  float u, v;
  /**
     The color of the veretx.
  **/
  float r, g, b;
};

class Mesh {
public:
  /**
     Create a new mesh.

     @param shader The shader to use for rendering this mesh.
  **/
  Mesh(Shader *shader);
  ~Mesh();

  /**
     Draw this mesh.
  **/
  void draw();

  /**
     Clear the mesh.

     This simply clears the vertices list and marks the mesh as dirty to be resent to the GPU next frame.
  **/
  void clear();

  /**
     Add a vertex to the mesh.

     This also marks the mesh as dirty.
  **/
  void addVertex(Vertex vert);

private:
  /**
     Resend vertex data to the GPU.
  **/
  void refresh();

  /**
     When this flag is set, `draw` calls `refresh` before drawing.
  **/
  bool dirty;

  GLuint vao;
  GLuint vbo;

  /**
     The shader used for rendering this mesh.
  **/
  Shader *shader;

  /**
     The list of vertices; sent to the GPU when `dirty` is set to true.
  **/
  std::vector<Vertex> vertices;
};

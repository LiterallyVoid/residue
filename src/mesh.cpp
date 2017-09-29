#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "mesh.h"

Mesh::Mesh() {
  glGenBuffers(1, &vbo);
};

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
};

void Mesh::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  if(dirty) {
    refresh();
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, x));
  glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, u));
  glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, r));

  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
};

void Mesh::clear() {
  vertices.clear();
  dirty = true;
};

void Mesh::addVertex(Vertex vert) {
  vertices.push_back(vert);
  dirty = true;
};

void Mesh::refresh() {
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
  dirty = false;
};

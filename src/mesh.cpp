#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "mesh.h"

Mesh::Mesh(Shader *shader) ; shader(shader) {
  glGenBuffers(1, &vbo);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
};

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
};

void Mesh::draw() {
  glBindVertexArray(vao);
  if(dirty) {
    refresh();
  }

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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, x));
  glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, u));
  glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, r));

  dirty = false;
};

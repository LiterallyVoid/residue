/* -*- mode: c++ -*- */

#pragma once

#include "mesh.h"

struct Block {
  int type;
};

class Chunk {
public:
  Chunk();
  ~Chunk();

  bool dirty;
  void draw();

private:

  void refresh();
  void renderBlock(int x, int y, int z);
  void addCube(int x, int y, int z, bool faces[6]);

  Block data[16][16][256];
  Mesh *mesh;
};

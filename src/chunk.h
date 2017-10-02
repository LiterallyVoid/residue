/* -*- mode: c++ -*- */

#pragma once

#include "mesh.h"

#define CHUNK_SIDE_LENGTH 16
#define CHUNK_HEIGHT 256

class World;

struct Block {
  int type;
};

class Chunk {
public:
  Chunk(int x, int y, World *world, Shader *shader);
  ~Chunk();

  bool dirty;
  void draw();

  Block getBlock(int x, int y, int z);
  void setBlock(int x, int y, int z, Block b);

private:

  void refresh();
  void renderBlock(int x, int y, int z);
  void addCube(int x, int y, int z, bool faces[6]);
  Block getSelfBlock(int x, int y, int z);
  bool isFaceShown(int x, int y, int z, int offsetX, int offsetY, int offsetZ);

  float getAO(int x, int y, int z);

  Block data[CHUNK_SIDE_LENGTH][CHUNK_SIDE_LENGTH][CHUNK_HEIGHT];
  Mesh *mesh;

  World *world;

  int chunkX, chunkY; // position, divided by CHUNK_SIDE_LENGTH
};

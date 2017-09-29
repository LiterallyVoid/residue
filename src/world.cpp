#include "world.h"

World::World() {
  for(int i = -16; i < 16; i++) {
    for(int j = -16; j < 16; j++) {
      loadChunk(i, j);
    }
  }
};

World::~World() {
};

void World::draw() {
  for(auto it : chunks) {
    it.second->draw();
  }
};

Block World::getBlock(int x, int y, int z) {
  int chunkX, chunkY;
  Chunk *c = getChunk(x, y, chunkX, chunkY);
  if(c != NULL) {
    return c->getBlock(x - chunkX * CHUNK_SIDE_LENGTH, y - chunkY * CHUNK_SIDE_LENGTH, z);
  }
  Block b;
  b.type = 0;
  return b;
};

void World::setBlock(int x, int y, int z, Block b) {
  int chunkX, chunkY;
  Chunk *c = getChunk(x, y, chunkX, chunkY);
  if(c != NULL) {
    c->setBlock(x + chunkX * CHUNK_SIDE_LENGTH, y + chunkY * CHUNK_SIDE_LENGTH, z, b);
  }
};

Chunk *World::getChunk(int x, int y, int &chunkX, int &chunkY) {
  chunkX = x >> 4;
  chunkY = y >> 4;
  std::array<int, 2> key = {chunkX, chunkY};
  auto c = chunks.find(key);
  if(c == chunks.end()) {
    return NULL;
  }
  return c->second;
};

void World::loadChunk(int x, int y) {
  std::array<int, 2> key = {x, y};

  chunks[key] = new Chunk(x, y, this);

  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      int chunkX, chunkY;
      Chunk *c = getChunk(i, j, chunkX, chunkY);
    }
  }
};

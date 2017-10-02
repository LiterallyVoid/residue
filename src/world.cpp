#include "world.h"

World::World() {
  shader = new Shader("assets/shaders/world.vert", "assets/shaders/world.frag");
};

World::~World() {
  for(auto it : chunks) {
    delete it.second;
  }
  delete shader;
};

void World::draw() {
  for(auto it : chunks) {
    it.second->draw();
  }

  int stop = 1000;
  for(int r = 0; r < 32 && stop != 0; r++) {
    for(int i = -r; i < r && stop != 0; i++) {
      for(int j = -r; j < r && stop != 0; j++) {
	if(loadChunk(i, j)) {
	  stop--;
	}
      }
    }
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
    c->setBlock(x - chunkX * CHUNK_SIDE_LENGTH, y - chunkY * CHUNK_SIDE_LENGTH, z, b);
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

bool World::loadChunk(int x, int y) {
  std::array<int, 2> key = {x, y};

  if(chunks.find(key) != chunks.end()) {
    return false;
  }

  chunks[key] = new Chunk(x, y, this, shader);

  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      std::array<int, 2> key = {x + i, y + j};
      auto c = chunks.find(key);
      if(c != chunks.end()) {
	c->second->dirty = true;
      }
    }
  }
  return true;
};

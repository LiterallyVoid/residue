#include <cmath>

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
  for(int r = 0; r < 16 && stop != 0; r++) {
    for(int i = -r; i < r && stop != 0; i++) {
      for(int j = -r; j < r && stop != 0; j++) {
	if(loadChunk(i, j)) {
	  stop--;
	}
      }
    }
  }
};

std::array<int, 3> World::castRay(float start[3], float direction[3], float maxDistance) {
  int pos[3] = {(int) start[0], (int) start[1], (int) start[2]};
  float deltaDist[3];
  float next[3];
  int step[3];
  for(int i = 0; i < 3; i++) {
    float dX = direction[0] / direction[i];
    float dY = direction[1] / direction[i];
    float dZ = direction[2] / direction[i];
    deltaDist[i] = sqrt(dX * dX + dY * dY + dZ * dZ);
    if(direction[i] < 0.0) {
      step[i] = -1;
      next[i] = (start[i] - pos[i]) * deltaDist[i];
    } else {
      step[i] = 1;
      next[i] = ((pos[i] + 1.0) - start[i]) * deltaDist[i];
    }
  }

  float distance = 0.0;

  while(distance < maxDistance) {
    int side = 0;
    for(int i = 1; i < 3; ++i) {
      if(next[side] > next[i]) {
        side = i;
      }
    }
    next[side] += deltaDist[side];
    pos[side] += step[side];
    distance += deltaDist[side];
    Block b = getBlock(pos[0], pos[1], pos[2]);
    if(b.type != 0) {
      std::array<int, 3> val = {pos[0], pos[1], pos[2]};
      return val;
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

  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      std::array<int, 2> key = {x / CHUNK_SIDE_LENGTH + i, y / CHUNK_SIDE_LENGTH + j};
      printf("%d %d\n", key[0], key[1]);
      auto c = chunks.find(key);
      if(c != chunks.end()) {
	c->second->dirty = true;
      }
    }
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

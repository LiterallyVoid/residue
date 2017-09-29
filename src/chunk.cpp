#include <GLFW/glfw3.h>

#include <noise/noise.h>

#include "world.h"
#include "chunk.h"

Chunk::Chunk(int x, int y, World *world) : mesh(new Mesh()), dirty(true), world(world), chunkX(x), chunkY(y) {

  noise::module::Perlin myModule;

  for(int x = 0; x < CHUNK_SIDE_LENGTH; x++) {
    for(int y = 0; y < CHUNK_SIDE_LENGTH; y++) {
      float m = 0.01;
      int h = myModule.GetValue((CHUNK_SIDE_LENGTH * chunkX + x) * m, (CHUNK_SIDE_LENGTH * chunkY + y) * m, 0.0) * 16 + 64;
      for(int z = 0; z < CHUNK_HEIGHT; z++) {
	data[x][y][z].type = (z < h) ? 1 : 0;
      }
    }
  }
};

Chunk::~Chunk() {
  delete mesh;
};

void Chunk::draw() {
  if(dirty) {
    refresh();
  }
  mesh->draw();
};

Block Chunk::getBlock(int x, int y, int z) {
  return data[x][y][z];
};

void Chunk::setBlock(int x, int y, int z, Block b) {
  data[x][y][z] = b;
};

void Chunk::refresh() {
  dirty = false;
  mesh->clear();
  bool faces[6] = {true, true, true, true, true, true};
  for(int x = 0; x < CHUNK_SIDE_LENGTH; x++) {
    for(int y = 0; y < CHUNK_SIDE_LENGTH; y++) {
      for(int z = 0; z < CHUNK_HEIGHT; z++) {
	renderBlock(x, y, z);
      }
    }
  }
};

Block Chunk::getSelfBlock(int x, int y, int z) {
  if(x >= 0 && y >= 0 && z >= 0 &&
     x < CHUNK_SIDE_LENGTH && y < CHUNK_SIDE_LENGTH && z < CHUNK_HEIGHT) {
    return data[x][y][z];
  }
  if(z >= 0 && z < CHUNK_HEIGHT) {
    return world->getBlock(chunkX * CHUNK_SIDE_LENGTH + x, chunkY * CHUNK_SIDE_LENGTH + y, z);
  }
  Block b;
  b.type = 0;
  return b;
};

bool Chunk::isFaceShown(int x, int y, int z, int offsetX, int offsetY, int offsetZ) {
  x += offsetX;
  y += offsetY;
  z += offsetZ;

  return getSelfBlock(x, y, z).type == 0;
};

void Chunk::renderBlock(int x, int y, int z) {
  if(data[x][y][z].type == 0) {
    return;
  }
  bool facesShown[6] = {
    isFaceShown(x, y, z, 1, 0, 0),
    isFaceShown(x, y, z, 0, 1, 0),
    isFaceShown(x, y, z, 0, 0, 1),
    isFaceShown(x, y, z, -1, 0, 0),
    isFaceShown(x, y, z, 0, -1, 0),
    isFaceShown(x, y, z, 0, 0, -1),
  };
  addCube(x, y, z, facesShown);
};

void Chunk::addCube(int x, int y, int z, bool faces[6]) {

  int directions[6] = {0, 1, 2, 0, 1, 2};

  int min = 0;
  int max = 1;

  int vertices[3][4][3] = {
    {
      {0, min, max},
      {0, min, min},
      {0, max, min},
      {0, max, max}
    },
    {
      {max, 0, max},
      {max, 0, min},
      {min, 0, min},
      {min, 0, max}
    },
    {
      {min, min, 0},
      {max, min, 0},
      {max, max, 0},
      {min, max, 0}
    },
  };

  int uvs[4][2] = {
    {0, 0},
    {0, 1},
    {1, 1},
    {1, 0}
  };

  int indices[2][6] = {
    {0, 1, 2, 2, 3, 0},
    {0, 2, 1, 3, 2, 0},
  };

  float multipliers[6] = {
    0.85,
    0.95,
    1.0,
    0.75,
    0.65,
    0.4
  };

  int rot = 0;

  for(int i = 0; i < 6; i++) {
    if(faces[i]) {
      int direction = directions[i];
      int normal[3] = {0, 0, 0};
      normal[direction] = (i < 3 ? 1 : -1);
      for(int j = 0; j < 6; j++) {
	int index = indices[i < 3 ? 0 : 1][j];
	int uvindex = index + rot;
	if(uvindex > 3) uvindex -= 4;
        int pos[3] = {vertices[direction][index][0], vertices[direction][index][1], vertices[direction][index][2]};
	pos[direction] = (i < 3 ? max : min);
	float light = multipliers[i];
	Vertex vert;
	vert.u = uvs[uvindex][0] * (i < 3 ? 1 : -1);
	vert.v = uvs[uvindex][1];
	vert.x = pos[0] + x + chunkX * CHUNK_SIDE_LENGTH;
	vert.y = pos[1] + y + chunkY * CHUNK_SIDE_LENGTH;
	vert.z = pos[2] + z;
	vert.r = light;
	vert.g = light;
	vert.b = light;
	mesh->addVertex(vert);
      }
    }
  }
};

/* -*- mode: c++ -*- */

#pragma once

#include <unordered_map>
#include <array>
#include "chunk.h"
#include "mesh.h"


namespace std
{
    template<typename T, size_t N>
    struct hash<array<T, N> >
    {
        typedef array<T, N> argument_type;
        typedef size_t result_type;

        result_type operator()(const argument_type& a) const
        {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i)
            {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };
}


class World {
public:
  World();
  ~World();

  void draw();

  std::array<int, 3> castRay(float start[3], float direction[3], float maxDistance, bool &success);

  Block getBlock(int x, int y, int z);
  void setBlock(int x, int y, int z, Block b);

  Chunk *getChunk(int x, int y, int &chunkX, int &chunkY);

private:
  Shader *shader;

  bool loadChunk(int x, int y);
  std::unordered_map<std::array<int, 2>, Chunk*> chunks;
};

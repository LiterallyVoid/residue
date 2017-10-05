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

  /**
     Draw the world.
  **/
  void draw();

  /**
     Cast a ray from `start`, in the direction `direction`, for `maxDistance` blocks.

     @param start Where the ray should start.
     @param direction Which direction the ray should go.
     @param maxDistance The maximum distance the ray should go.
     @param success Whether the raycast hit something or not.

     @return The (x, y, z) coordinates of the block that was hit.
  **/
  std::array<int, 3> castRay(float start[3], float direction[3], float maxDistance, bool &success); // XXX: should probably return the block directly before it too, for placement, etc.

  /**
     Get the block at (x, y, z).

     @param x The x-coordinate of the block.
     @param y Ditto.
     @param z Ditto.

     @return The block at (x, y, z).
  **/
  Block getBlock(int x, int y, int z);

  /**
     Set the block at (x, y, z) to `b`.

     @param x The x-coordinate of the block.
     @param y Ditto.
     @param z Ditto.
     @param b The block to place at (x, y, z).

     @return Nothing.
  **/
  void setBlock(int x, int y, int z, Block b);

  /**
     Get the chunk which contains a block at (x, y).

     @param x The x-coordinate of the block.
     @param y Ditto.
     @param chunkX The x-position of the resultant chunk.
     @param chunkY Ditto.

     @return The chunk at (chunkX, chunkY).
  **/
  Chunk *getChunk(int x, int y, int &chunkX, int &chunkY);

private:
  /**
     Load the chunk at (x, y).

     @param x The x-coordinate of the chunk (divided by CHUNK_SIDE_LENGTH).
     @param y Ditto.

     @return If the chunk was already loaded.
  **/
  bool loadChunk(int x, int y);

  /**
     The shader with which to draw all the chunks.
  **/
  Shader *shader;

  /**
     The map of all the loaded chunks.
   **/
  std::unordered_map<std::array<int, 2>, Chunk*> chunks;
};

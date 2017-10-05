/* -*- mode: c++ -*- */

#pragma once

#include "mesh.h"

#define CHUNK_SIDE_LENGTH 16
#define CHUNK_HEIGHT 256

// Forward declaration: Avoid circular dependencies.
class World;

struct Block {
  int type;
};

class Chunk {
public:
  /**
     Create a new Chunk.

     @param x      The x-coordinate of the chunk (divided by CHUNK_SIDE_LENGTH)
     @param y      The y-coordinate of the chunk (divided by CHUNK_SIDE_LENGTH)
     @param world  The world that this chunk resides in.
     @param shader The shader that this chunk uses for rendering.
  **/
  Chunk(int x, int y, World *world, Shader *shader);
  ~Chunk();

  /**
     Whether the chunk should refresh on the next draw call.
  **/
  bool dirty;

  /**
     Draw the chunk.

     Note that this automatically draws the chunk at (chunkX, chunkY) instead of at the origin.
  **/
  void draw();

  /**
     Get the block at (x, y, z) in local coordinates.

     @param x The x-coordinate of the block. East-west.
     @param y The y-coordinate of the block. North-south.
     @param z The z-coordinate of the block. Up-down.

     @return The block at (x, y, z).
  **/
  Block getBlock(int x, int y, int z);

  /**
     Set the block at (x, y, z) in local coordinates to `b`.

     @param x The x-coordinate of the block. East-west.
     @param y Ditto.
     @param z Ditto.
     @param b The block to replace the old one with.

     @return Nothing.
  **/
  void setBlock(int x, int y, int z, Block b);

private:
  /**
     Clear and refresh the mesh.
  **/
  void refresh();

  /**
     Render the block at (x, y, z).

     This properly takes into account visibility checks, so it only renders outside faces.

     @param x The x-coordinate of this block.
     @param y Ditto.
     @param z Ditto.

     @return Nothing.
  **/
  void renderBlock(int x, int y, int z);

  /**
     Render a cube at (x, y, z) with some faces hidden.

     @param x The x-coordinate of this block.
     @param y Ditto.
     @param z Ditto.

     @param faces A list of six booleans for knowing which faces to show.

     @return Nothing.
   **/
  void renderCube(int x, int y, int z, bool faces[6]);

  /**
     Returns the block at (x, y, z), properly returning blocks outside this chunk.

     @param x The x-coordinate of the block in question, in local coordinates.
     @param y Ditto.
     @param z Ditto.r

     @return The block at (x, y, z), properly handling out-of-bounds values.
   **/
  Block getSelfBlock(int x, int y, int z);

  /**
     Returns if the block at (x, y, z) should show the face in the direction of (offsetX, offsetY, offsetZ).

     @param x The x-coordinate of the block in question.
     @param y Ditto.
     @param z Ditto.

     @return If the face in the direction of (offsetX, offsetY, offsetZ) on the block at (x, y, z) should be shown.
  **/
  bool isFaceShown(int x, int y, int z, int offsetX, int offsetY, int offsetZ);

  /**
     Gets the ambient occlusion factor at (x, y, z).

     @param x The x-coordinate of the vertex in question.
     @param y Ditto.
     @param z Ditto.

     @return The ambient occlusion factor at (x, y, z), ranging from 0.0 to 1.0.
  **/
  float getAO(int x, int y, int z);

  /**
     The raw data for this chunk.
  **/
  Block data[CHUNK_SIDE_LENGTH][CHUNK_SIDE_LENGTH][CHUNK_HEIGHT];

  /**
     The mesh used for this chunk.
  **/
  Mesh *mesh;

  /**
     The world that this chunk resides in.
  **/
  World *world;

  /**
     The chunk coordinates, divided by CHUNK_SIDE_LENGTH.
  **/
  int chunkX, chunkY;
};

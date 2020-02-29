#ifndef BUFFERGENERATOR_H
#define BUFFERGENERATOR_H

#include "AGL.h"
#include "Buffer.h"

#include "Tile.h"

using namespace agl;

class BufferGenerator {
  AGL* gl;
  
  Texture* plain_texture;
//   Texture* wall_texture;
  
//   Buffer* gen_plain_tile_buf(Tile* t);
  
//   Buffer* gen_wall_tile_buf(Tile* t);
  
public:
  BufferGenerator(AGL* gl);
  
  Buffer* gen_tile_buf(Tile* t);
};

#endif

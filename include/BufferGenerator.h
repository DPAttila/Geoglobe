#ifndef BUFFERGENERATOR_H
#define BUFFERGENERATOR_H

#include "AGL.h"
#include "Buffer.h"

#include "Tile.h"

using namespace agl;

class BufferGenerator {
  AGL* gl;
  
  Texture* plain_texture;
  Texture* wall_texture;
  Texture* portal_texture;
  
  Buffer* wizard;
  Buffer* phantom;
  Buffer* blast;
  
//   Buffer* gen_plain_tile_buf(Tile* t);
  
//   Buffer* gen_wall_tile_buf(Tile* t);
  
public:
  BufferGenerator(AGL* gl);
  
  Buffer* gen_tile_buf(Tile* t);
  
  Buffer* get_wizard_buf();
  
  Buffer* get_phantom_buf();
  
  Buffer* get_blast_buf();
};

#endif

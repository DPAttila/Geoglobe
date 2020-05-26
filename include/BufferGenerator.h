#ifndef BUFFERGENERATOR_H
#define BUFFERGENERATOR_H

#include "AGL.h"
#include "Buffer.h"

#include "Tile.h"
#include "TextureManager.h"

using namespace agl;

class BufferGenerator {
  AGL* gl;
  
  TextureManager* texture_manager;
  
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
  
  TextureManager* get_texture_manager();
  
};

#endif

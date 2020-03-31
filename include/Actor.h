#ifndef ACTOR_H
#define ACTOR_H

#include "Buffer.h"

#include "Tile.h"

class Actor {
  Tile* tile;
  Buffer* buf;
  
public:
  Actor(Buffer* buf, Tile* tile);
  
  void draw();
  
  Tile* get_tile();
};

#endif

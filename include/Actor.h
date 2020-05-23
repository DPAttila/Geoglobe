#ifndef ACTOR_H
#define ACTOR_H

#include "Buffer.h"

#include "Tile.h"

class Actor {
  Tile* tile;
  Point pos;
  Buffer* buf;
  
  Point2f angles;
  
  void calculate_angles();
  
public:
  Actor(Buffer* buf, Tile* tile);
  
  void draw();
  
  Tile* get_tile();
  
  void set_tile(Tile* t);
  
  void set_pos(Point p);
  
  Point get_pos();
  
  Point2f get_angles();
};

#endif

#ifndef TILE_H
#define TILE_H

#include "AGL.h"
#include "Buffer.h"

using namespace agl;

class Tile {
  
  Point points[3];
  
  /**
   * Center of the triangle
   */
  Point pos;

  /**
   * Neighbours of the triangle
   */
  Tile* next[3];
  
  /**
   * 0 - plain
   * 1 - wall
   */
  int type;

public:
  Buffer* buf;
  Tile(Point p1, Point p2, Point p3);
  
  ~Tile();
  
  void draw();
  
  void set_neighbours(Tile* t1, Tile* t2, Tile* t3);
  
  void set_buf(Buffer* buf);
  
  Point* get_points();
  
  Tile** get_next();
};

#endif

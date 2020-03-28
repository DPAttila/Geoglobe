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
  
  Buffer* buf;
  
  /**
   * 0 - plain
   * 1 - wall
   */
  int type;

public:
  Tile(Point p1, Point p2, Point p3);
  
  ~Tile();
  
  void draw();
  
  void set_neighbours(Tile* t1, Tile* t2, Tile* t3);
  
  void set_buf(Buffer* buf);
  
  Point* get_points();
  
  Point get_pos();
  
  Tile** get_next();
  
  int get_type();
  
  void set_type(int type);
};

#endif

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
   * Horizontal and vertical angle of
   * the vector drawn between the sphere's center 
   * and the center of the triangle
   * (these angles are used to set the Actors 
   * perpendicular to the tile's plane)
   */
  Point2f angles;
  
  /**
   * Neighbours of the triangle
   */
  Tile* next[3];
  
  ShaderManager* shaderManager;
  
  Buffer* buf;
  
  /**
   * 0 - plain
   * 1 - wall
   */
  int type;
  
  bool highlighted;
  
  bool selected;
  
  bool occupied;

public:
  Tile(Point p1, Point p2, Point p3, ShaderManager* shaderManager);
  
  ~Tile();
  
  void draw();
  
  void set_neighbours(Tile* t1, Tile* t2, Tile* t3);
  
  void set_buf(Buffer* buf);
  
  Point* get_points();
  
  Point get_pos();
  
  /**
   * Returns the h and v angles
   */
  Point2f get_angles();
  
  Tile** get_next();
  
  int get_type();
  
  void set_type(int type);
  
  /**
   * Sets a special highlight shader to be used for the tile
   */
  void highlight();
  
  /**
   * Sets the default shader to be used for the tile
   */
  void dehighlight();
  
  /**
   * Sets a special selection shader to be used for the tile
   * (Only previously highlighted tile can be selected)
   */
  void select();
  
  /**
   * Sets the highlight shader to be used for the tile
   * (Only previously highlighted tile can be selected)
   */
  void deselect();
  
  bool is_occupied();
  
  void occupy();
  
  void unoccupy();
};

#endif

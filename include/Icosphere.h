#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include <vector>

#include "Point.h"

#include "Tile.h"

class Icosphere {
  /**
   * Points of the triangles of the icosphere
   * There are duplicate points at depths more than 0
   */
  vector<Point> points;
  
  /**
   * Indices of the points defining triangles, in sets of three
   */
  vector<vector<int> > indices;
  
  /**
   * Indices of neighbouring triangles of each triangle, in sets of three
   */
  vector<vector<int> > neighbours;
  
  /**
   * Builds an icosahedron, the base of the icosphere
   * It's points, indices and neighbours will be stored in the class' fields
   */
  void build_icosahedron();
  
  /**
   * Divides each triangle of the icosphere into four, increasing it's resoultion
   * Updates all three vectors
   */ 
  void divide();

public:
  /**
   * @param[in] depth Resoultion of the triangle
   */
  Icosphere(int depth = 0);
  
  /**
   * Converts the icosphere to a set of tiles
   * It sets the tiles' coordinates and neighbours
   */
  vector<Tile*> to_tile_set();
};

#endif

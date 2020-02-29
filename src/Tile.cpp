#ifndef TILE_CPP
#define TILE_CPP

#include "Tile.h"

#include <cmath>

#include "Vertex.h"

using namespace agl;

Tile::Tile(Point p1, Point p2, Point p3) {
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;
  
  pos = (p1 + p2 + p3) / 3.0;
}

Tile::~Tile() {
  delete buf;
}

void Tile::draw() {
  buf->draw();
}

void Tile::set_neighbours(Tile* t1, Tile* t2, Tile* t3) {
  next[0] = t1;
  next[1] = t2;
  next[2] = t3;
}

void Tile::set_buf(Buffer* buf) {
  this->buf = buf;
}

Point* Tile::get_points() {
  return points;
}

Tile** Tile::get_next() {
  return next;
}

#endif

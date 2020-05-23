#ifndef TILE_CPP
#define TILE_CPP

#include "Tile.h"

#include <cmath>
#include <iostream>

#include "Vertex.h"

using namespace agl;

Tile::Tile(Point p1, Point p2, Point p3, ShaderManager* shaderManager) {
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;
  
  pos = (p1 + p2 + p3) / 3.0;
  
  angles.x = atan2(-pos.z, -pos.x);
  angles.y = atan2(sqrt(pos.x * pos.x + pos.z * pos.z), pos.y);
  
  type = 0;
  occupied = false;
  
  this->shaderManager = shaderManager;
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

void Tile::highlight() {
  highlighted = true;
  buf->set_shader("highlight");
}

void Tile::dehighlight() {
  highlighted = false;
  selected = false;
  buf->set_shader("default");
}

void Tile::select() {
  if (highlighted) {
    selected = true;
    buf->set_shader("selection");
  } else {
    std::cout << "Can't select tile that is not highlighted";
  }
}

void Tile::deselect() {
  selected = false;
  buf->set_shader("highlight");
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

int Tile::get_type() {
  return type;
}

void Tile::set_type(int type) {
  this->type = type;
}

Point Tile::get_pos() {
  return pos;
}

Point2f Tile::get_angles() {
  return angles;
}

bool Tile::is_occupied() {
  return occupied;
}

void Tile::occupy() {
  occupied = true;
}

void Tile::unoccupy() {
  occupied = false;
}

#endif

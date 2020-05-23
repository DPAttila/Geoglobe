#ifndef ACTOR_CPP
#define ACTOR_CPP

#include <ctime>
#include <cmath>

#include "Actor.h"

Actor::Actor(Buffer* buf, Tile* tile) {
  this->buf = buf;
  this->tile = tile;
  this->pos = tile->get_pos();
  
  tile->occupy();
  
  calculate_angles();
}

void Actor::draw() {
  buf->translate(pos * (1.01 +  0.01 * sin(clock() / 100000.0)));
  buf->rotate(angles.x, angles.y);
  buf->draw();
}

Tile* Actor::get_tile() {
  return tile;
}

void Actor::set_tile(Tile* t) {
  tile->unoccupy();
  this->tile = t;
  tile->occupy();
}

void Actor::set_pos(Point p) {
  this->pos = p;
  calculate_angles();
}


void Actor::calculate_angles() {
    angles = Point2f(atan2(-pos.z, -pos.x), atan2(sqrt(pos.x * pos.x + pos.z * pos.z), pos.y));
}


Point Actor::get_pos() {
  return pos;
}

Point2f Actor::get_angles() {
  return angles;
}

#endif

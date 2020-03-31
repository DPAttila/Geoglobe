#ifndef ACTOR_CPP
#define ACTOR_CPP

#include <ctime>
#include <cmath>

#include "Actor.h"

Actor::Actor(Buffer* buf, Tile* tile) {
  this->buf = buf;
  this->tile = tile;
}

void Actor::draw() {
  buf->translate(tile->get_pos() * (1.01 +  0.01 * sin(clock() / 100000.0)));
  Point2f angles = tile->get_angles();
  buf->rotate(angles.x, angles.y);
  buf->draw();
}

Tile* Actor::get_tile() {
  return tile;
}

#endif

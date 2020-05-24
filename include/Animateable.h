#ifndef ANIMATEABLE_H
#define ANIMATEABLE_H

#include "AGL.h"
#include "Point.h"
#include "Buffer.h"

using namespace agl;

class Animateable {
protected:
  Buffer* buf;
  Point pos;
public:
  virtual void set_pos(Point p) = 0;
  
  virtual void draw() = 0;
  Point get_pos();
};

#endif

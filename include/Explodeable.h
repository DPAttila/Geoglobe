#ifndef EXPLODEABLE_H
#define EXPLODEABLE_H

#include "AGL.h"

using namespace agl;

class Explodeable {
protected:
  Point explosion_pos;
  Point delta_pos;
  
  Point2f explosion_angles;
  Point2f delta_angles;
  
  Explodeable();
  
  void set_delta_pos(Point pos);
  
  void add_delta();
  
public:
  virtual void add_explosion_delta() = 0;
};

#endif

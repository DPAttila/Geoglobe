#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "AGL.h"
#include "Point.h"
#include "Buffer.h"

#include "Actor.h"

using namespace agl;

class Animator {
  Actor* actor;
  Point start, finish;
  
  bool finished;
  
  int resolution = 30;
  int progress;
  
public:
  Animator(Actor* actor, Point finish);
  
  void animate();
  
  bool is_finished();
};

#endif

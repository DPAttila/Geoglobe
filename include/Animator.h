#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Point.h"

#include "Animateable.h"

using namespace agl;

class Animator {
  Animateable* animateable;
  Point start, finish;
  
  bool finished;
  
  int resolution = 30;
  int progress;
  
public:
  Animator(Animateable* animateable, Point finish);
  
  void animate();
  
  bool is_finished();
};

#endif

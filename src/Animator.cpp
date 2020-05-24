#ifndef ANIMATOR_CPP
#define ANIMATOR_CPP

#include "Animator.h"

Animator::Animator(Animateable* animateable, Point finish) {
  this->animateable = animateable;
  this->start = animateable->get_pos();
  this->finish = finish;
  
  progress = 0;
  
  resolution = (start - finish).pyth() * 100.0;
  finished = false;
}

void Animator::animate() {
  if (progress < resolution) {
    Point p = (start * (float)(resolution - progress) + finish * progress) / (float) resolution;
    p.normalize();
    
    animateable->set_pos(p);
    progress++;
  } else 
    finished = true;
}

bool Animator::is_finished() {
  return finished;
}

#endif

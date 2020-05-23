#ifndef ANIMATOR_CPP
#define ANIMATOR_CPP

#include "Animator.h"

Animator::Animator(Actor* actor, Point finish) {
  this->actor = actor;
  this->start = actor->get_pos();
  this->finish = finish;
  
  progress = 0;
  finished = false;
}

void Animator::animate() {
  if (progress < resolution) {
    actor->set_pos((start * (float)(resolution - progress) + finish * progress) / (float) resolution);
    progress++;
  } else 
    finished = true;
}

bool Animator::is_finished() {
  return finished;
}

#endif

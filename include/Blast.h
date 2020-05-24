#ifndef BLAST_H
#define BLAST_H

#include "Actor.h"
#include "Animateable.h"

using namespace agl;

class Blast : public Animateable {
  Actor* source;
  Actor* target;
  
public:
  Blast(Actor* source, Actor* target, Buffer* buf);
  
  void set_pos(Point pos);
  
  void draw();
  
  void blow();
  
  Actor* get_target();
};

#endif

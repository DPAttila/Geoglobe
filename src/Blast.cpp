#ifndef BLAST_CPP
#define BLAST_CPP

#include "Blast.h"

#include "BufferGenerator.h"

using namespace agl;

Blast::Blast(Actor* source, Actor* target, Buffer* buf) {
  this->source = source;
  this->target = target;
  this->pos = source->get_pos();
  this->buf = buf;
}

void Blast::draw() {
  buf->translate(pos * 1.1);
  buf->draw();
}

void Blast::blow() {
  target->deal_dmg(source->get_dmg());
}

void Blast::set_pos(Point pos) {
  this->pos = pos;
}

Actor* Blast::get_target() {
  return target;
}

#endif

#ifndef BUFFERGENERATOR_CPP
#define BUFFERGENERATOR_CPP

#include "BufferGenerator.h"

#include <vector>

using namespace agl;

BufferGenerator::BufferGenerator(AGL* gl) {
  this->gl = gl;
  
  plain_texture = new Texture("../tex.png");
}

Buffer* BufferGenerator::gen_tile_buf(Tile* t) {
  Buffer* buf = new Buffer(gl);
  
  Point *p = t->get_points();
  
  vector<Vertex> v = {
    Vertex(p[0], Point2f(.5, .4), p[0]),
    Vertex(p[1], Point2f(.3, .5), p[1]),
    Vertex(p[2], Point2f(.6, .7), p[2])
  };
  
  vector<unsigned int> i = {0, 1, 2, 0, 2, 1};
  
  buf->add(v, i);
  buf->set_texture(plain_texture);
  
  return buf;
}

#endif

#ifndef BUFFERGENERATOR_CPP
#define BUFFERGENERATOR_CPP

#include "BufferGenerator.h"

#include <vector>
#include <iostream>

using namespace agl;

BufferGenerator::BufferGenerator(AGL* gl) {
  this->gl = gl;
  
  plain_texture = new Texture("../textures/path.png");
  wall_texture = new Texture("../textures/wall.png");
  portal_texture = new Texture("../textures/portal.png");
  
  wizard = new Buffer(gl);
  wizard->load("../models/wizard.obj");
  wizard->scale(.06);
  
  phantom = new Buffer(gl);
  phantom->load("../models/phantom.obj");
  phantom->scale(.06);
  
  blast = new Buffer(gl);
  blast->load("../models/sphere.obj");
  blast->scale(.02);
}

Buffer* BufferGenerator::gen_tile_buf(Tile* t) {
  Buffer* buf = new Buffer(gl);
  
  Point *p = t->get_points();
  
  vector<Vertex> v;
  vector<unsigned int> i;
  
  if (t->get_type() == 0) {
    v = {
      Vertex(p[0], Point2f(0.0, 0.0), p[0]),
      Vertex(p[1], Point2f(0.5, 1.0), p[1]),
      Vertex(p[2], Point2f(1.0, 0.0), p[2])
    };
    
    i = {0, 1, 2, 0, 2, 1};
    buf->set_texture(plain_texture);
  } else if (t->get_type() == 1) {
    float wall_height = 0.2;
    
    Point points[6] = {
      p[0], p[1], p[2],
      p[0] * (1 + wall_height), 
      p[1] * (1 + wall_height), 
      p[2] * (1 + wall_height) 
    };
    
    Point center = t->get_pos() * (1 + wall_height / 2.0);
    Point normals[3]; // normals for the side faces
    normals[0] = ((p[0] + p[1] + p[3] + p[4]) / 4.0 - center) * 1.0;
    normals[1] = ((p[0] + p[2] + p[3] + p[5]) / 4.0 - center) * 1.0;
    normals[2] = ((p[1] + p[2] + p[4] + p[5]) / 4.0 - center) * 1.0;
    
    normals[0].normalize();
    normals[1].normalize();
    normals[2].normalize();
//     std::cout << normals[0].to_string() << '\n';
    
    v = {
      // top face
      Vertex(points[3], Point2f(0.0, 1.0), points[3]),
      Vertex(points[4], Point2f(0.5, 0.0), points[4]),
      Vertex(points[5], Point2f(1.0, 1.0), points[5]),
      // side faces
      Vertex(points[0], Point2f(0.0, 0.0), normals[0]),
      Vertex(points[1], Point2f(1.0, 0.0), normals[0]),
      Vertex(points[3], Point2f(0.0, 1.0), normals[0]),
      Vertex(points[4], Point2f(1.0, 1.0), normals[0]),
      
      Vertex(points[0], Point2f(0.0, 0.0), normals[1]),
      Vertex(points[2], Point2f(1.0, 0.0), normals[1]),
      Vertex(points[3], Point2f(0.0, 1.0), normals[1]),
      Vertex(points[5], Point2f(1.0, 1.0), normals[1]),
      
      Vertex(points[1], Point2f(0.0, 0.0), normals[2]),
      Vertex(points[2], Point2f(1.0, 0.0), normals[2]),
      Vertex(points[4], Point2f(0.0, 1.0), normals[2]),
      Vertex(points[5], Point2f(1.0, 1.0), normals[2]),
    };
    
    i = {
      0, 1, 2, 2, 1, 0,
      3, 4, 5, 3, 5, 4,
      4, 5, 6, 4, 6, 5,
      7, 8, 9, 7, 9, 8,
      8, 9, 10, 8, 10, 9,
      11, 12, 13, 11, 13, 12,
      12, 13, 14, 12, 14, 13
    };
    buf->set_texture(wall_texture);
  } else if (t->get_type() == 2) {
    float wall_height = 0.3;
    
    Point points[6] = {
      p[0], p[1], p[2],
      p[0] * (1 + wall_height), 
      p[1] * (1 + wall_height), 
      p[2] * (1 + wall_height) 
    };
    
    Point center = t->get_pos() * (1 + wall_height / 2.0);
    Point normals[3]; // normals for the side faces
    normals[0] = ((p[0] + p[1] + p[3] + p[4]) / 4.0 - center) * 1.0;
    normals[1] = ((p[0] + p[2] + p[3] + p[5]) / 4.0 - center) * 1.0;
    normals[2] = ((p[1] + p[2] + p[4] + p[5]) / 4.0 - center) * 1.0;
    
    normals[0].normalize();
    normals[1].normalize();
    normals[2].normalize();
//     std::cout << normals[0].to_string() << '\n';
    
    v = {
      // top face
      Vertex(points[3], Point2f(0.0, 1.0), points[3]),
      Vertex(points[4], Point2f(0.5, 0.0), points[4]),
      Vertex(points[5], Point2f(1.0, 1.0), points[5]),
      // side faces
      Vertex(points[0], Point2f(0.0, 0.0), normals[0]),
      Vertex(points[1], Point2f(1.0, 0.0), normals[0]),
      Vertex(points[3], Point2f(0.0, 1.0), normals[0]),
      Vertex(points[4], Point2f(1.0, 1.0), normals[0]),
      
      Vertex(points[0], Point2f(0.0, 0.0), normals[1]),
      Vertex(points[2], Point2f(1.0, 0.0), normals[1]),
      Vertex(points[3], Point2f(0.0, 1.0), normals[1]),
      Vertex(points[5], Point2f(1.0, 1.0), normals[1]),
      
      Vertex(points[1], Point2f(0.0, 0.0), normals[2]),
      Vertex(points[2], Point2f(1.0, 0.0), normals[2]),
      Vertex(points[4], Point2f(0.0, 1.0), normals[2]),
      Vertex(points[5], Point2f(1.0, 1.0), normals[2]),
    };
    
    i = {
      0, 1, 2, 2, 1, 0,
      3, 4, 5, 3, 5, 4,
      4, 5, 6, 4, 6, 5,
      7, 8, 9, 7, 9, 8,
      8, 9, 10, 8, 10, 9,
      11, 12, 13, 11, 13, 12,
      12, 13, 14, 12, 14, 13
    };
    buf->set_texture(portal_texture);
  }
  
  buf->add(v, i);
  
  return buf;
}


Buffer* BufferGenerator::get_wizard_buf() {
  return wizard;
}

Buffer* BufferGenerator::get_phantom_buf() {
  return phantom;
}

Buffer* BufferGenerator::get_blast_buf() {
  return blast;
}

#endif

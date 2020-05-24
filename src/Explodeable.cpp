#ifndef EXPLODDEABLE_CPP
#define EXPLODDEABLE_CPP

#include "Explodeable.h"

Explodeable::Explodeable() {
  explosion_pos = Point(0, 0, 0);
  float speed = .01;
  int res = 1000000;
  delta_pos = Point(
    (rand() % res - res / 2),
    (rand() % res - res / 2),
    (rand() % res - res / 2) 
  );
  
  delta_pos.normalize();
  
  delta_pos *= speed;
  
  explosion_angles = Point2f(0, 0);
  
  delta_angles = Point2f(
    (rand() % res - res / 2) / (float)res * speed,
    (rand() % res - res / 2) / (float)res * speed
  );
  
}

void Explodeable::add_delta() {
  explosion_pos += delta_pos;
  explosion_angles.x += delta_angles.x;
  explosion_angles.y += delta_angles.y;
}

#endif

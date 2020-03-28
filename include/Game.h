#ifndef GAME_H
#define GAME_H

#include <vector>

#include "AGL.h"
#include "Point.h"

#include "Tile.h"
#include "BufferGenerator.h"

using namespace agl;

class Game {
  AGL* gl;
  Camera* gl_camera;
  Input* gl_input;
  
  float viewer_lon, viewer_lat, viewer_dist;
  
  bool game_over;
  
  BufferGenerator *bufferGenerator;
  
  vector<Tile*> tiles;
  vector<Tile*> dbg;
  
  void build_tiles();
public:
  Game(AGL* gl);
  
  void update_camera_pos();
  
  void draw();
  
  void input();
  
  void logic();
  
  void start();
};

#endif

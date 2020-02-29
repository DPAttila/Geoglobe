#ifndef GAME_H
#define GAME_H

#include <vector>

#include "AGL.h"

#include "Tile.h"
#include "BufferGenerator.h"

using namespace agl;

class Game {
  AGL* gl;
  
  bool game_over;
  
  BufferGenerator *bufferGenerator;
  
  vector<Tile*> tiles;
  vector<Tile*> dbg;
  
  void build_tiles();
  
  int r = 0;
int last_r = 0;

Texture* t1 = new Texture("../blue.png");
Texture* t2 = new Texture("../apple.png");
Texture* base = new Texture("../tex.png");

public:
  Game(AGL* gl);
  
  void draw();
  
  void input();
  
  void logic();
  
  void start();
};

#endif

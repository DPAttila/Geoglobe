#include <iostream>

#include "AGL.h"
#include "imgui.h"
#include "Graphics.h"

#include "Game.h"

using namespace agl;

Game* game;

void input() {
  game->input();
}

void draw() {
  game->draw();
}

void logic() {
  game->logic();
}

int main(int argc, char **argv) {
  
  AGL* gl = new AGL();
  gl->init("Geo-globe", draw, input, logic);
    
  game = new Game(gl);
    
  gl->loop();

  delete game;
  
  return 0;
}

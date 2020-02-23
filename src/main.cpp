#include <iostream>

#include "AGL.h"
#include "imgui.h"
#include "Graphics.h"

#include "Game.h"

using namespace agl;

AGL* gl;

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
  gl = new AGL();
  gl->init("Geo-globe", draw, input, logic);
  gl->enable_cursor();
  
  game = new Game(gl);
  
  gl->loop();
  
  return 0;
}

#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"

#include <cmath>
#include <iostream>

#include "Icosphere.h"

using namespace std;
using namespace agl;

Game::Game(AGL* gl) {
  this->gl = gl;
  
  Shader* shader = new Shader(
    "../agl2.0/src/shaders/default.vs", 
    "../agl2.0/src/shaders/default.fs"
  );
  gl->get_graphics()->set_shader(shader);
  
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  
  bufferGenerator = new BufferGenerator(gl);
  
  game_over = false;
  
  build_tiles();
}

void Game::logic() {
  if (last_r != r) {
    
    if (r < tiles.size()) {
      tiles[last_r]->buf->set_texture(base);
      Tile** t = tiles[last_r]->get_next();
      for (int i = 0; i < 3; i++)
        t[i]->buf->set_texture(base);
      
      tiles[r]->buf->set_texture(t1);
      t = tiles[r]->get_next();
      for (int i = 0; i < 3; i++)
        t[i]->buf->set_texture(t2);
      
      last_r = r;
    }
  }
}

void Game::draw() {
  {
    ImGui::Begin("Hello");
    
    ImGui::Text("hello");
    
    ImGui::InputInt("select", &r);
    ImGui::End();
  }
  
  int i = 0;
  for (Tile* t : tiles) {
    t->draw();
  }
}

void Game::input() {
  //TODO: open menu on escape key instead of quitting
  if (gl->get_key(GLFW_KEY_ESCAPE))
    gl->finish();
  
  if (gl->get_key(GLFW_KEY_E)) {
    if (gl->is_cursor_disabled())
      gl->enable_cursor();
    else
      gl->disable_cursor();
  } 
  if (gl->is_cursor_disabled()) {
    if (gl->get_key(GLFW_KEY_W))
      gl->move_camera_forward();
    if (gl->get_key(GLFW_KEY_A))
      gl->move_camera_left();
    if (gl->get_key(GLFW_KEY_S))
      gl->move_camera_backwards();
    if (gl->get_key(GLFW_KEY_D))
      gl->move_camera_right();
    
    Point2f d = gl->get_cursor_delta();
    d.x /= 500.0;
    d.y /= 500.0;
    
    if (d.x != 0 || d.y != 0)
      gl->turn_camera(d.x, d.y);
  }

}

void Game::build_tiles() {
  Icosphere icosphere(2);
  
  tiles = icosphere.to_tile_set();

  for (int i = 0; i < tiles.size(); i++)
    tiles[i]->set_buf(bufferGenerator->gen_tile_buf(tiles[i]));
}

#endif

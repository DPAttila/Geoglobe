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
  this->gl_camera = gl->get_graphics()->get_camera();
  this->gl_input = gl->get_input();
  
  shader_manager = gl->get_graphics()->get_shader_manager();
  shader_manager->add_shader(
    "default", 
    "../shaders/default.vs", 
    "../shaders/default.fs"
  );
  
  shader_manager->add_shader(
    "highlight",
    "../shaders/default.vs", 
    "../shaders/tile_selected.fs"
  );
  
  glClearColor(0.5f, 0.5f, 0.2f, 0.0f);
  
  bufferGenerator = new BufferGenerator(gl);
  
  build_tiles();
  
  hero = new Actor(
    bufferGenerator->get_wizard_buf(), 
    tiles[rand() % tiles.size()]
  );
  
  Tile* hero_tile = hero->get_tile();
  hero_tile->highlight();
  Tile** next_tiles = hero_tile->get_next();
  for (int i = 0; i < 3; i++)
    next_tiles[i]->highlight();
  
  viewer_lon = 0;
  viewer_lat = 0;
  viewer_dist = -2;
  update_camera_pos();
  
  game_over = false;
}

void Game::logic() {
}

void Game::draw() {
  {
    ImGui::Begin("Hello");
    Point2f scroll = gl_input->get_scroll();
    
    ImGui::Text("scroll %f %f", scroll.x, scroll.y);
//     ImGui::Text(
//       "camera pos: %f %f %f",
//       viewer_dist * cos(viewer_lat) * cos(viewer_lon),
//       viewer_dist * sin(viewer_lat),
//       viewer_dist * cos(viewer_lat) * sin(viewer_lon)
//     );
//     
    ImGui::End();
  }
  
  for (Tile* t : tiles) {
    t->draw();
  }
  
  hero->draw();
}

void Game::input() {
  //TODO: open menu on escape key instead of quitting
  if (gl_input->get_key(GLFW_KEY_ESCAPE))
    gl->finish();
  
  if (gl_input->get_key(GLFW_KEY_E)) {
    if (gl_input->is_cursor_disabled())
      gl_input->enable_cursor();
    else
      gl_input->disable_cursor();
  } 
  if (gl_input->is_cursor_disabled()) {
    Point2f d = gl_input->get_cursor_delta();
    d.x /= 500.0;
    d.y /= 500.0;
    
    if (d.x != 0 || d.y != 0) {
      viewer_lon += d.x;
      viewer_lat += d.y;
      update_camera_pos();
    }
    
    Point2f scroll = gl_input->get_scroll();
    
    if (scroll.y != 0) {
      viewer_dist += 0.1 * scroll.y;
      update_camera_pos();
    }
  }

}

void Game::build_tiles() {
  srand(time(NULL));
  Icosphere icosphere(3);
  
  tiles = icosphere.to_tile_set(gl->get_graphics()->get_shader_manager());

  for (int i = 0; i < 10; i++) {
    Tile* ti = tiles[rand() % tiles.size()];
    while (ti->get_type() != 1) {
      ti->set_type(1);
      ti = ti->get_next()[rand() % 3]; 
    }
  }
  
  for (int i = 0; i < tiles.size(); i++)
    tiles[i]->set_buf(bufferGenerator->gen_tile_buf(tiles[i]));
}

void Game::update_camera_pos() {
  if (viewer_lat > M_PI/2)
    viewer_lat = M_PI/2;
  if (viewer_lat < -M_PI/2)
    viewer_lat = -M_PI/2;
  
 gl_camera->orient(-viewer_lon, -viewer_lat);
 gl_camera->set_pos(Point(
    viewer_dist * cos(viewer_lat) * cos(viewer_lon),
    viewer_dist * sin(viewer_lat),
    viewer_dist * cos(viewer_lat) * sin(viewer_lon)
  ));
}

#endif

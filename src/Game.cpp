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
    "../shaders/tile_highlighted.fs"
  );
  
  shader_manager->add_shader(
    "selection",
    "../shaders/default.vs",
    "../shaders/tile_selected.fs"
  );
  
  glClearColor(0.5f, 0.5f, 0.2f, 0.0f);
  
  bufferGenerator = new BufferGenerator(gl);
  
  build_tiles();
  
  hero = new Actor(
    bufferGenerator->get_wizard_buf(), 
    get_unoccupied_tile()
  );
  
  for (int i = 0; i < 10; i++) {
    enemies.push_back(new Actor(
      bufferGenerator->get_phantom_buf(),
      get_unoccupied_tile()
    ));
  }
  
  Point2f hero_angles = hero->get_angles();
  
  viewer_lon = hero_angles.x;
  viewer_lat = hero_angles.y - M_PI/2;
  update_camera_pos();
  
  viewer_dist = -2;
  update_camera_pos();
  
  game_over = false;
  
  player_turn = true;
  animation = false;
  
  animator = nullptr;
}

void Game::logic() {
  
  if (selection_cooldown) selection_cooldown--;
  
  if (!animation) {
    if (player_turn) {
      if (moves.size() == 0) {
        Tile** next_tiles = hero->get_tile()->get_next();
        for (int i = 0; i < 3; i++) {
          if (next_tiles[i]->get_type() == 0 && !next_tiles[i]->is_occupied())
            moves.push_back(next_tiles[i]);
        }
        
        for (int i = 0; i < moves.size(); i++) 
          moves[i]->highlight();
        
        move_selection = 0;
      }
    }
  } else {
    animator->animate();
    
    if (animator->is_finished()) {
      animation = false;
      player_turn = !player_turn;
    }
  }
}

void Game::draw() {
  {
    ImGui::Begin("Hello");
    Point2f scroll = gl_input->get_scroll();
    
    ImGui::Text("scroll %f %f", scroll.x, scroll.y);

    ImGui::End();
  }
  
  for (Tile* t : tiles) {
    t->draw();
  }
  
  hero->draw();
  
  for (Actor* e : enemies) {
    e->draw();
  }
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
  
  if (player_turn && !animation) {
    if (gl_input->get_key(GLFW_KEY_LEFT) || gl_input->get_key(GLFW_KEY_RIGHT)) {
      if (!selection_cooldown) {
        selection_cooldown = SELECTION_COOLDOWN;
        
        moves[move_selection]->deselect();
        
        if (gl_input->get_key(GLFW_KEY_LEFT)) {
          move_selection -= 1;
          if (move_selection < 0) 
            move_selection = moves.size() - 1;
        }
        
        if (gl_input->get_key(GLFW_KEY_RIGHT)) {
          move_selection += 1;
          if (move_selection >= moves.size()) 
            move_selection = 0;
        }
        
        moves[move_selection]->select();
      }
    }
    
    if (gl_input->get_key(GLFW_KEY_ENTER)) {
      player_turn = false;
      animation = true;
      
      if (animator != nullptr) delete animator;
      
      animator = new Animator(hero, moves[move_selection]->get_pos());
      hero->set_tile(moves[move_selection]);
      
      for (int i = 0; i < moves.size(); i++)
        moves[i]->dehighlight();
      moves.clear();
    }
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
  Icosphere icosphere(2);
  
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

Tile* Game::get_unoccupied_tile() {
  Tile* t;
  do {
    t = tiles[rand() % tiles.size()];
  } while (t->get_type() != 0 || t->is_occupied());
  
  return t;
}

#endif

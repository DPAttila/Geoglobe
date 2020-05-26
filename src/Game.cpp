#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"

#include <cmath>
#include <iostream>
#include <algorithm>

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
  
  glClearColor(0.11f, 0.21f, 0.6f, 0.0f);
  
  bufferGenerator = new BufferGenerator(gl);
  
  texture_manager = bufferGenerator->get_texture_manager();
  texture_manager->add_texture("hp", "../textures/hp.png");
  
  init_map();
}

void Game::init_map() {
  build_tiles();
  
  hero = new Actor(
    bufferGenerator->get_wizard_buf(), 
    get_unoccupied_tile(),
    1, 
    3,
    5,
    true
  );
  
  for (int i = 0; i < 30; i++) {
    enemies.push_back(new Actor(
      bufferGenerator->get_phantom_buf(),
      get_unoccupied_tile(),
      5,
      3,
      3,
      false
    ));
  }
  
  vector<Actor*> ai_enemy_vector;
  ai_enemy_vector.push_back(hero);
  
  ai = new AI(&enemies, ai_enemy_vector, this);
  
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
  blast = nullptr;
  
  game_ended = false;
  menu_appear_countdown = MENU_APPEAR_COUNTDOWN;
  
  hero_fov = hero->get_reach();
  for (Tile* t : hero_fov)
    t->highlight();
    
  move_selection = 0;
}

void Game::clear_map() {
  for (Tile* t : tiles) 
    if (t != nullptr) delete t;
  
  tiles.clear();
  
  if (hero != nullptr) 
    delete hero;
  hero = nullptr;
  
  for (Actor* e : enemies) 
    if (e != nullptr) delete e;
  
  enemies.clear();
  
  if (ai != nullptr)
    delete ai;
  ai = nullptr;
  
  if (animator != nullptr)
    delete animator;
  animator = nullptr;
  
  if (blast != nullptr)
    delete blast;
  blast = nullptr;
}

void Game::logic() {
  
  if (game_ended) {
    if (menu_appear_countdown) {
      menu_appear_countdown--;
      explode();
    }
  } else {
    if (selection_cooldown) 
      selection_cooldown--;
    
    if (!animation) {
      if (player_turn) {
        if (hero->get_moves().size() == 0) {
          hero->calculate_moves();
          
          for (Tile* t : hero->get_moves()) 
            t->highlight();
          
          move_selection = 0;
          (hero->get_moves())[move_selection]->select();
        }
      } else {
        ai->move();
        if (ai->is_finished()) {
          player_turn = true;
          hero->calculate_moves();
        } else
          animation = true;
      }
    } else {
      animator->animate();
      
      if (animator->is_finished()) {
        animation = false;
        if (player_turn) {
          if (hero->get_tile()->get_type() == 2)
            game_ended = true;

          player_turn = false;
          ai->start_turn();
        }
        
        if (blast != nullptr) {
          
          blast->blow();
          
          if (!blast->get_target()->is_alive()) {
            if (blast->get_target()->get_side() == 0) {
              enemies.erase(remove(enemies.begin(), enemies.end(), blast->get_target()));
            } else {
              game_ended = true;
            }
          }
          
          delete blast;
          blast = nullptr;
        }
        
        delete animator;
        animator = nullptr;
      } 
    }
  }
}

void Game::draw() {
  
  if (!game_ended) {
    {
      ImGui::Begin("Hello");
      
      for (int i = 0; i < hero->get_hp(); i++) {
        ImGui::SameLine();
        ImGui::Image((void*)texture_manager->get_texture("hp")->get_texture_object_handle(), ImVec2(30, 30));
      }

      ImGui::End();
    }

    if (move_selection < hero->get_moves().size()) {
      Actor* enemy_selected = hero->get_moves()[move_selection]->get_actor();
      
      if (enemy_selected != nullptr) {
        ImGui::Begin("Enemy");
        
        for (int i = 0; i < enemy_selected->get_hp(); i++) {
          ImGui::SameLine();
          ImGui::Image((void*)texture_manager->get_texture("hp")->get_texture_object_handle(), ImVec2(30, 30));
        }
        
        ImGui::End();
      }
    }
    
    {
      ImGui::Begin("Turn");
      
      if (player_turn)
        ImGui::Text("\t\t\tYOUR TURN");
      else
        ImGui::Text("\t\t\tENEMY TURN");
      
      ImGui::End();
    }
  } else if (menu_appear_countdown == 0) {
    ImGui::Begin("Game over");
    ImGui::AlignTextToFramePadding();
    
    static ImVec4 col(rand()%10 / 10.0, rand()%10 / 10.0, rand()%10 / 10.0, 1.0);
    bool restart = false;
    
    if (rand() % 10 == 0) {
      col = ImVec4(rand()%10 / 10.0, rand()%10 / 10.0, rand()%10 / 10.0, 1.0);
    }
    
    if (hero->is_alive())
      ImGui::TextColored(col, "\t\tWIN\t\t");
    else 
      ImGui::TextColored(col, "\t\tLOSE\t\t");
    
    if (ImGui::Button("RESTART")) {
      clear_map();
      init_map();
      restart = true;
    } 
    
    if (ImGui::Button("EXIT")) {
      gl->finish();
    }
    
    ImGui::End();
    
    if (restart) return;
  }
  
  for (Tile* t : tiles) {
    t->draw();
  }
  
  if (hero->is_alive())
    hero->draw();
  
  for (Actor* e : enemies) {
    e->draw();
  }
  
  if (blast != nullptr) {
    blast->draw();
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
        
        vector<Tile*> moves = hero->get_moves();

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
      animation = true;
      
      vector<Tile*> moves = hero->get_moves();
      
      for (int i = 0; i < moves.size(); i++)
        moves[i]->dehighlight();

      execute_move(hero, moves[move_selection]);
      
      for (Tile* t : hero_fov)
        t->dehighlight();
      hero_fov.clear();
      
      hero_fov = hero->get_reach();
      for (Tile* t : hero_fov)
        t->highlight();
        
      move_selection = 0;
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

void Game::shoot_blast(Actor* source, Actor* target) {
  blast = new Blast(source, target, bufferGenerator->get_blast_buf());
  animator = new Animator(blast, target->get_pos());
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
  
 // for (int i = 0; i < 30; i++) 
  get_unoccupied_tile()->set_type(2);
  
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
  } while (!(t->get_type() == 0 && t->get_actor() == nullptr));
  
  return t;
}

void Game::explode() {
  for (Tile* t : tiles) {
    t->add_explosion_delta();
  }
  
  for (Actor* a : enemies) {
    a->add_explosion_delta();
  }
  
  hero->add_explosion_delta();
  
  viewer_dist -= 0.003;
  update_camera_pos();
}

void Game::execute_move(Actor* actor, Tile* move) {
  if (move->get_actor() == nullptr) {
    animator = new Animator(actor, move->get_pos());
    actor->set_tile(move);
  } else {
    shoot_blast(actor, move->get_actor());
  }
}

#endif

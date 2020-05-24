#ifndef GAME_H
#define GAME_H

#include <vector>

#include "AGL.h"
#include "Point.h"

#include "Tile.h"
#include "Blast.h"
#include "Actor.h"
#include "Animator.h"
#include "BufferGenerator.h"

using namespace agl;

#define SELECTION_COOLDOWN 7
#define MENU_APPEAR_COUNTDOWN 400

class Game {
  AGL* gl;
  Camera* gl_camera;
  Input* gl_input;
  ShaderManager* shader_manager;
  
  bool player_turn;
  bool animation;
  
  bool game_ended;
  int menu_appear_countdown;
  
  vector<Tile*> tiles;
  
  /**
   * Index of the currently selected move
   */
  int move_selection;
  
  
  int selection_cooldown;
  
  float viewer_lon, viewer_lat, viewer_dist;
  
  bool game_over;
  
  BufferGenerator *bufferGenerator;
  
  Actor* hero;
  
  vector<Actor*> enemies;

  Blast* blast;
  
  Animator *animator;
  
  vector<Tile*> hero_fov;
  
  void build_tiles();
  
  void shoot_blast(Actor* source, Actor* target);
  
  void explode();
  
  Tile* get_unoccupied_tile();
public:
  Game(AGL* gl);
  
  void update_camera_pos();
  
  void draw();
  
  void input();
  
  void logic();
  
  void start();
};

#endif

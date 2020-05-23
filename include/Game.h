#ifndef GAME_H
#define GAME_H

#include <vector>

#include "AGL.h"
#include "Point.h"

#include "Tile.h"
#include "Actor.h"
#include "Animator.h"
#include "BufferGenerator.h"

using namespace agl;

class Game {
  AGL* gl;
  Camera* gl_camera;
  Input* gl_input;
  ShaderManager* shader_manager;
  
  bool player_turn;
  bool animation;
  
  vector<Tile*> tiles;
  
  vector<Tile*> moves;
  
  /**
   * Index of the currently selected move
   */
  int move_selection;
  
  #define SELECTION_COOLDOWN 7
  int selection_cooldown;
  
  float viewer_lon, viewer_lat, viewer_dist;
  
  bool game_over;
  
  BufferGenerator *bufferGenerator;
  
  Actor* hero;
  
  vector<Actor*> enemies;

  Animator *animator;
  
  void build_tiles();
  
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

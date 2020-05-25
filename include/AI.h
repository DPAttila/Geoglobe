#ifndef AI_H
#define AI_H

#include "Game.h"
#include "Actor.h"

class Game;

class AI {
  vector<Actor*> *units;
  
  vector<Actor*> enemies;
  
  Game* game;
  
  int unit_index;
  
  bool finished_turn;
public:
  
  AI(vector<Actor*> *units, vector<Actor*> enemies, Game* game);
  
  void move();
  
  void start_turn();
  
  bool is_finished();
};

#endif

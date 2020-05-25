#ifndef AI_CPP
#define AI_CPP

#include "AI.h"

#include "Tile.h"

#include <iostream>

AI::AI(vector<Actor*>* units, vector<Actor*> enemies, Game* game) {
  this->units = units;
  this->enemies = enemies;
  this->game = game;
  
  finished_turn = true;
  unit_index = 0;
}

void AI::move() {
  if (unit_index < (*units).size()) {
    (*units)[unit_index]->calculate_moves();
    vector<Tile*> moves = (*units)[unit_index]->get_moves();
    
    Tile* move = nullptr;
    for (Tile* m : moves) {
      if (m->get_actor() != nullptr) {
        move = m;
      }
    }
    if (move == nullptr) move = moves[rand() % moves.size()];
    
    game->execute_move((*units)[unit_index], move);
    unit_index++;
  } else
    finished_turn = true;
}

void AI::start_turn() {
  finished_turn = false;
  unit_index = 0;
}

bool AI::is_finished() {
  return finished_turn;
}

#endif

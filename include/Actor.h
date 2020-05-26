#ifndef ACTOR_H
#define ACTOR_H

#include "Buffer.h"

#include "Tile.h"
#include "Animateable.h"

class Tile;

class Actor : public Animateable, public Explodeable {
  Tile* tile;
  
  Point2f angles;
  
  int hp;
  int dmg;
  int range;
  
  /**
   * true if hero
   * false if enemy
   */
  bool side;
  
  bool alive;
  
  vector<Tile*> moves;
  
  void calculate_angles();
  
  void breadth_first(vector<Tile*> &tiles, vector<int> &dist, bool walls);
  
public:
  Actor(Buffer* buf, Tile* tile, int hp, int dmg, int range, bool side);
  
  void draw();
  
  vector<Tile*> get_reach();
  
  void calculate_moves();
  
  Tile* get_tile();
  
  void set_tile(Tile* t);
  
  void set_pos(Point p);
  
  void deal_dmg(int dmg);
  
  int get_dmg();
  
  int get_hp();
  
  Point get_pos();
  
  Point2f get_angles();
  
  vector<Tile*> get_moves();
  
  bool is_alive();
  
  bool get_side();
  
  void add_explosion_delta();
};

#endif

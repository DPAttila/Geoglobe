#ifndef ACTOR_CPP
#define ACTOR_CPP

#include <ctime>
#include <cmath>
#include <iostream>

#include "Actor.h"

Actor::Actor(Buffer* buf, Tile* tile, int hp, int dmg, int range, bool side) {
  this->buf = buf;
  this->tile = tile;
  this->pos = tile->get_pos();
  this->hp = hp;
  this->dmg = dmg;
  this->range = range;
  this->side = side;
  
  alive = true;
  
  tile->set_actor(this);
  
  calculate_angles();
}

void Actor::draw() {
  buf->translate(pos * (1.01 +  0.01 * sin(clock() / 100000.0)) + explosion_pos);
  buf->rotate(angles.x + explosion_angles.x, angles.y + explosion_angles.y);
  buf->draw();
}

void Actor::breadth_first(vector<Tile*> &tiles, vector<int> &dist, bool walls) {
  struct step {
    Tile* t;
    int d;
  };
  
  vector<step> visited;
  
  vector<step> to_visit;  
  step s0;
  s0.t = tile;
  s0.d = 0;
  to_visit.push_back(s0);
  
  while (to_visit.size()) {
    if (to_visit[0].d < range) {
      Tile** t = to_visit[0].t->get_next();
      for (int i = 0; i < 3; i++) {
        if (t[i] != to_visit[0].t && (t[i]->get_type() == 0 || !walls)) {
          int j = 0;
          bool already_visited = false;
          for (j = 0; j < visited.size(); j++) {
            if (visited[j].t == t[i]) {
              already_visited = true;
              break;
            }
          }
          
          int k = 0;
          bool already_scheduled = false;
          for (k = 0; k < to_visit.size(); k++) {
            if (to_visit[k].t == t[i]) {
              already_scheduled = true;
              break;
            }
          }
          
          bool add = false;
          
          if (already_visited && visited[j].d > to_visit[0].d + 1) {
            visited.erase(visited.begin() + j);
            add = true;
          } else if (already_scheduled && to_visit[k].d > to_visit[0].d + 1) {
            to_visit.erase(to_visit.begin() + k);
            add = true;
          } else if (!already_visited && !already_scheduled) {
            add = true;
          }
          
          if (add) {
            step s;
            s.t = t[i];
            s.d = to_visit[0].d + 1;
            to_visit.push_back(s);
          }
        }
      }
    }
    visited.push_back(to_visit[0]);
    to_visit.erase(to_visit.begin());
  }
  
  for (int i = 0; i < visited.size(); i++) {
    tiles.push_back(visited[i].t);
    dist.push_back(visited[i].d);
  }
}

vector<Tile*> Actor::get_reach() {
  cout << "Entered getreach\n" << flush;
  vector<Tile*> reach_with_walls;
  vector<Tile*> reach_no_walls;
  
  vector<int> dist_with_walls;
  vector<int> dist_no_walls;
  
  breadth_first(reach_no_walls, dist_no_walls, false);
  breadth_first(reach_with_walls, dist_with_walls, true);
  
  vector<Tile*> list;
  
  for (int i = 0; i < reach_with_walls.size(); i++) {
    bool add = true;
    
    int j = 0;
    for (j = 0; j < reach_no_walls.size(); j++) {
      if (reach_with_walls[i] == reach_no_walls[j]) {
        if (dist_with_walls[i] != dist_no_walls[j]) {
          add = false;
          cout << "no add\n";
        }
        break;
      }
    }
    
    if (add) 
      list.push_back(reach_with_walls[i]);
    else {
      dist_no_walls.erase(dist_no_walls.begin() + j);
      reach_no_walls.erase(reach_no_walls.begin() + j);
    }
  }
  
  list.erase(list.begin());
  
  cout << "Finished getreach\n" << flush;
  return list;
}

void Actor::calculate_moves() {
  moves.clear(); 
  Tile** next_tiles = tile->get_next();
  
  for (int i = 0; i < 3; i++) {
    if (next_tiles[i]->get_type() == 0 && next_tiles[i]->get_actor() == nullptr)
      moves.push_back(next_tiles[i]);
    
    if (next_tiles[i]->get_type() == 2 && side == true)
      moves.push_back(next_tiles[i]);
  }
  
  vector<Tile*> reach = get_reach();
  
  for (Tile* t : reach) {
    if (t->get_actor() != nullptr)
      moves.push_back(t);
  }
  
}

vector<Tile*> Actor::get_moves() {
  return moves;
}

Tile* Actor::get_tile() {
  return tile;
}

void Actor::set_tile(Tile* t) {
  tile->set_actor(nullptr);
  this->tile = t;
  tile->set_actor(this);
  calculate_moves();
}

void Actor::set_pos(Point p) {
  this->pos = p;
  calculate_angles();
}


void Actor::calculate_angles() {
  angles = Point2f(atan2(-pos.z, -pos.x), atan2(sqrt(pos.x * pos.x + pos.z * pos.z), pos.y));
}


Point Actor::get_pos() {
  return pos;
}

Point2f Actor::get_angles() {
  return angles;
}

int Actor::get_dmg() {
  return dmg;
}

void Actor::deal_dmg(int dmg) {
  hp -= dmg;
  
  if (hp <= 0) {
    alive = false;
    tile->set_actor(nullptr);
  }
}

bool Actor::is_alive() {
  return alive;
}

bool Actor::get_side() {
  return side;
}

void Actor::add_explosion_delta() {
  add_delta();
}

#endif

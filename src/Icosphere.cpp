#ifndef ICOSPHERE_CPP
#define ICOSPHERE_CPP

#include "ShaderManager.h"

#include "Icosphere.h"

#include <cmath>
#include <iostream>

Icosphere::Icosphere(int depth) {
  // Firstly we generate an icosahedron
  build_icosahedron();
  
  // then we divide it as many times as neeeded
  for (int d = 0; d < depth; d++)
    divide();
}

void Icosphere::build_icosahedron() {
  points.push_back(Point(0, 1, 0)); // north pole
  
  points.push_back(Point(0, -1, 0)); // south pole
  
  // "The other ten vertices are at latitude ±arctan(0.5) ≈ ±26.57°. 
  // These ten vertices are at evenly spaced longitudes (36° apart), 
  // alternating between north and south latitudes."
  // See https://en.wikipedia.org/wiki/Regular_icosahedron
  
  const double lat1 =  atan(0.5);
  const double lat2 = -atan(0.5);
  double lon = 0;
  double lat;
  
  for (int i = 0; i < 10; i++) {
    if (i%2)
      lat = lat1;
    else
      lat = lat2;
    
    points.push_back(Point(
      cos(lat) * cos(lon),
      sin(lat),
      cos(lat) * sin(lon)
    ));
    
    lon += M_PI / 5.0;
  }
  
  // 5 vertices are closer to the north pole, while 5 are closer 
  // to the south. First we create the triangles which have either 
  // pole as a vertice.
  // Vertex #2 is closer to the north pole (Vertex #0), so
  // the triangles will go like this:
  // (0, 2, 4) (north), (1, 3, 5) (south), (0, 4, 6) (north), etc.
  for (int i = 2; i < 12; i++) {
    vector<int> index(3);
    
    if (i%2==0) // South pole
      index[0] = 1;
    else
      index[0] = 0;
    
    index[1] = i;
    index[2] = 2 + i % 10;
    
    indices.push_back(index);
  }
  
  // Now we create the triangles which have neither pole as a vertex
  for (int i = 2; i < 12; i++) {
    vector<int> index(3);
    
    index[0] = i;
    index[1] = 2 + (i + 9) % 10;
    index[2] = 2 + i % 10;
    
    indices.push_back(index);
  }
  
  // neighbours of the triangles of the icosahedron
  neighbours = vector<vector<int> >(indices.size(), vector<int>());
  
  int matches;
  for (int i = 0; i < indices.size(); i++) {
    for (int j = i+1; j < indices.size(); j++) {
      matches = 0;
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
          if (indices[i][k] == indices[j][l])
            matches++;
        }
      }
      
      if (matches == 2) {
        neighbours[i].push_back(j);
        neighbours[j].push_back(i);
      }
    }
  }
}

void Icosphere::divide() {
  vector<vector<int> > old_indices = indices;
  vector<vector<int> > old_neighbours = neighbours;
  
  indices = vector<vector<int> >();
  
  // Divides every triangle into four smaller triangles
  // Updates the index vector accordingly
  for (int i = 0 ; i < old_indices.size(); i++) {
    int i1 = old_indices[i][0];
    int i2 = old_indices[i][1];
    int i3 = old_indices[i][2];
    
    Point p1 = (points[i1] + points[i2]) / 2.0;
    Point p2 = (points[i1] + points[i3]) / 2.0;
    Point p3 = (points[i2] + points[i3]) / 2.0;
    
    p1.normalize();
    p2.normalize();
    p3.normalize();
    
    int s = points.size();
    
    vector<int> ind1 = {i1, s, s + 1};
    indices.push_back(ind1);
    
    vector<int> ind2 = {i2, s, s + 2};
    indices.push_back(ind2);
    
    vector<int> ind3 = {i3, s + 1, s + 2};
    indices.push_back(ind3);
    
    // the central triangle is created last
    vector<int> ind4 = {s, s + 1, s + 2};
    indices.push_back(ind4);
    
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
  }
  
  // the center of each triangle is calculated
  // this is needed to find their neighbours 
  vector<Point> centers = vector<Point>(indices.size());
  
  for (int i = 0; i < indices.size(); i++)
    centers[i] = (points[indices[i][0]] + points[indices[i][1]] + points[indices[i][2]]) / 3.0;
  
  // updating the neighbours
  
  neighbours = vector<vector<int> >(indices.size(), vector<int>());
  
  // sets all neighbours to unknown
  for (int i = 0; i < indices.size(); i++)
    for (int j = 0; j < 3; j++)
      neighbours[i].push_back(-1);
  
  // for every triangle in the old (undivided) set
  for (int i = 0; i < old_indices.size(); i++) {
    // the other three new triangles are 
    // the neighbours of the new center triangle
    neighbours[i*4 + 3] = {i*4, i*4 + 1, i*4 + 2};
    
    for (int j = 0; j <3; j++) {
      // the outer three new triangles have
      // the central new triangle as a neighbour
      neighbours[i*4 + j][2] = i*4 + 3;
      
      // the distance from the closest new triangle 
      // in each neighbouring old triangle
      float distances[3] = {100, 100, 100};
      
      // indices of the closest new triangles
      // from each neighbouring old triangle
      int indices_of_closest[3] = {-1, -1, -1};
      
      // for the three old neighbouring triangles
      for (int k = 0; k < 3; k++) {
        // for the three non-central triangles of the old neighbouring triangle
        for (int l = 0; l < 3; l++) {
          // d is the distance between the new triangle 
          // and the new triangle from the old neighbouring triangle
          float d = (centers[i*4 + j] - centers[old_neighbours[i][k]*4 + l]).pyth();
          if (d < distances[k]) {
            distances[k] = d;
            indices_of_closest[k] = old_neighbours[i][k]*4 + l;
          }
        }
      }
      
      // get the two closest indices to the 2 first spaces
      if (distances[2] < distances[0] || distances[2] < distances[1]) {
        if (distances[1] > distances[0])
          indices_of_closest[1] = indices_of_closest[2];
        else
          indices_of_closest[0] = indices_of_closest[2];
      }
      
      // the other two neighbours of the new triangle are 
      // the two closest new triangles from the old neighbouring triangles
      neighbours[i*4 + j][0] = indices_of_closest[0];
      neighbours[i*4 + j][1] = indices_of_closest[1];
    }
  }
}

vector<Tile*> Icosphere::to_tile_set(ShaderManager* shader_manager) {
  vector<Tile*> tiles;
  
  for (int i = 0; i < indices.size(); i++) {
    tiles.push_back(new Tile(
      points[indices[i][0]], 
      points[indices[i][1]], 
      points[indices[i][2]],
      shader_manager
    ));
  }
  
  for (int i = 0; i < neighbours.size(); i++) {
    tiles[i]->set_neighbours(
      tiles[neighbours[i][0]],
      tiles[neighbours[i][1]],
      tiles[neighbours[i][2]]
    );
  }
  
  return tiles;
}

#endif

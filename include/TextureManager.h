#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>

#include "Texture.h"

using namespace std;
using namespace agl;

//TODO: This could be moved to agl2.0
class TextureManager {
  map<string, Texture*> textures;
  
public:
  TextureManager();
  
  Texture* get_texture(string name);
  
  //TODO: this should be bool
  /**
   * @param[in] name Name of the texture, by which it can be retrieved
   * @param[in] filename Name of the file to read the texture from
   */
  void add_texture(string name, string filename);
};

#endif

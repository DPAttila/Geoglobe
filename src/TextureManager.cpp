#ifndef TEXTURE_MANAGER_CPP
#define TEXTURE_MANAGER_CPP

#include <iostream>

#include "TextureManager.h"

TextureManager::TextureManager() {
  
}

Texture* TextureManager::get_texture(string name) {
  
  if (textures[name] == nullptr) cout << "Texture not found!\n" << flush;
  
  return textures[name];
}

void TextureManager::add_texture(string name, string filename) {
  if (textures[name] != nullptr) {
    cout << "Texture " << name << " already exists!\n";
    cout << "Deleting old texture\n" << flush;
    delete textures[name];
  }
  
  Texture* t = new Texture(filename);
  
  textures[name] = t;
}

#endif

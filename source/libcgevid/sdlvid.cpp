#include <cge/cge.hpp>
#include <cge/cgevid.hpp>

#include <string>
#include <SDL2/SDL.h>

using namespace cge;

bool vid::init() {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    reg::put("cge-error-status" , "true");
    reg::put("cge-error-message", std::string("SDL Error : ") + SDL_GetError());
    
    return false;
  }

  return true;
}

vid::window::window() {
  // Do Nothing //
}

vid::window::window(int x,int y,unsigned int w,unsigned int h,const std::string& name) {
  // Call create() and if something goes wrong
  // throw an error in the registry

  if(!create(x, y, w, h, name)) {
    _isopen = false;
    reg::put("cge-error-status" , "true");
    reg::put("cge-error-message", "Failed to create an SDL2 Window");
    
    return;
  }
  
  reg::put(std::string("cge-window-")+name, "true");
  reg::put(std::string("cge-window-")+name+"w",std::to_string(w));
  reg::put(std::string("cge-window-")+name+"h",std::to_string(h));
}

bool vid::window::create(int x,int y,unsigned int w,unsigned int h,const std::string& name) {
  handle = SDL_CreateWindow(name.c_str(), x, y, w, h, SDL_WINDOW_OPENGL);

  _isopen = true;
  
  return handle;
}

void vid::window::close() {
  if(!_isopen) {
    reg::put("reg-warning-status","true");
    reg::put("reg-warning-message","Can not close a window that is not open");

    return;
  }

  SDL_DestroyWindow((SDL_Window*)handle);
}

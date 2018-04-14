#include <cge/reg.hpp>
#include <cge/vid.hpp>

#include <string>
#include <thread>

#include <SDL2/SDL.h>
#include <GL/glew.h>

using namespace cge;

bool __is_initialized = false;

bool vid::init() {
  if(__is_initialized) {
    reg::put("cge-warning-status" , "true");
    reg::put("cge-warning-message", "Cannot re-initialize video");
    
    return false;
  }
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    reg::put("cge-error-status" , "true");
    reg::put("cge-error-message", std::string("SDL Error : ") + SDL_GetError());
    
    return false;
  }

  __is_initialized = true;

  return true;
}

void vid::quit() {
  SDL_Quit();
  
  __is_initialized = false;
}

vid::window::window() {
  // Do Nothing //
}

vid::window::window(int x,int y,unsigned int w,unsigned int h,const std::string& name,const std::string& title) {
  // Call create() and if something goes wrong
  // throw an error in the registry

  if(!create(x, y, w, h, name, title)) {
    _isopen = false;
    reg::put("cge-error-status" , "true");
    reg::put("cge-error-message", "Failed to create an SDL2 Window");
    
    return;
  }
  
  reg::put(std::string("cge-window-")+name, "true");
  reg::put(std::string("cge-window-")+name+"-title" , title);
  reg::put(std::string("cge-window-")+name+"-width" ,std::to_string(w));
  reg::put(std::string("cge-window-")+name+"-height",std::to_string(h));
  reg::put(std::string("cge-window-")+name+"-gl-version" ,reinterpret_cast<const char*>(glGetString(GL_VERSION)));
  reg::put(std::string("cge-window-")+name+"-gl-vendor"  ,reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
  reg::put(std::string("cge-window-")+name+"-gl-renderer",reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
  reg::put(std::string("cge-window-")+name+"-gl-shading" ,reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

bool vid::window::create(int x,int y,unsigned int w,unsigned int h,const std::string& name,const std::string& title) {
  handle = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  gl_handle = new SDL_GLContext(SDL_GL_CreateContext((SDL_Window*)handle));

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    reg::put("cge-error-status" , "true");
    reg::put("cge-error-message", "Failed to initialize GLEW");
    
    return false;
  }
  
  _isopen = true;
  
  return handle;
}

void vid::window::close() {
  if(!_isopen) {
    reg::put("reg-warning-status","true");
    reg::put("reg-warning-message","Can not close a window that is not open");

    return;
  }

  SDL_GL_DeleteContext(*(SDL_GLContext*)gl_handle);
  SDL_DestroyWindow((SDL_Window*)handle);
}

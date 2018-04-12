#include "testing.hpp"

#include <iostream>

#include <SDL/SDL.h>

#include <cge/vid.hpp>
#include <cge/reg.hpp>

using namespace cge;

void test_cge_vid() {
  std::cout<<"\nTesting Video Functions\nInitializing CGE Video\n";

  if(!vid::init()) {
    std::cout<<"VID Error : "<<reg::get("cge-error-message")<<"\n";
    die(__LINE__,"Failed to initialize CGE Video!\n");
  }

  std::cout<<"Opening window\n";
  
  vid::window win(0, 0, 1280, 720, "CGE Test Window");

  SDL_Delay(1000);

  std::cout<<"Closing window\n";
  win.close();
}

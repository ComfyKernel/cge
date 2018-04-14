#include "testing.hpp"

#include <iostream>

#include <SDL/SDL.h>

#include <cge/vid.hpp>
#include <cge/reg.hpp>
#include <cge/log.hpp>

using namespace cge;

void _print_wininfo(const std::string& window) {
  if(reg::get(std::string("cge-window-") + window) != "true") {
    log::logf("Cannot get info for window '%S'\n", window);
    return;
  }

  log::logf("\
-------- Window Info --------\n\
Window : %S\n\
 Title : %&\n\
 Width : %&\n\
Height : %&\n\
---------- GL info ----------\n\
 Version : %&\n\
  Vendor : %&\n\
Renderer : %&\n\
 Shading : %&\n\
-----------------------------\n",
	    window                               ,
	    std::string("cge-window-") + window + "-title" ,
	    std::string("cge-window-") + window + "-width" ,
	    std::string("cge-window-") + window + "-height",
	    std::string("cge-window-") + window + "-gl-version" ,
	    std::string("cge-window-") + window + "-gl-vendor"  ,
	    std::string("cge-window-") + window + "-gl-renderer",
	    std::string("cge-window-") + window + "-gl-shading");
}

void _check_error() {
  if(reg::get("cge-error-status") == "true") {
    log::logf("CGE Error : %*\n", "cge-error-message");
    die(__LINE__,"CGE Error Encountered");
  }
}

void test_cge_vid() {
  log::log("\nTesting Video Functions\nInitializing CGE Video\n");

  if(!vid::init()) {
    log::logf("VID Error : %*\n", "cge-error-message");
    die(__LINE__,"Failed to initialize CGE Video!\n");
  }

  log::log("Opening Window\n");
  
  vid::window win(0, 0, 1280, 720, "test", "CGE Test Window");

  _check_error();

  _print_wininfo("test");

  _check_error();
  
  SDL_Delay(1000);

  log::log("Closing Window\n");
  win.close();

  log::log("Quitting VID\n");
  vid::quit();
}

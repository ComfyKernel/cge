#ifndef COMFYS_GAME_ENGINE_MAIN_HPP
#define COMFYS_GAME_ENGINE_MAIN_HPP

#include <string>
#include <vector>
#include <initializer_list>

enum cge_reg_enums {
  CGE_REG_FAILED=0,
  CGE_REG_ADDED=1,
  CGE_REG_REPLACED=2
};

namespace cge {
  //
  //             CGE Functions
  // init()
  // - puts values in the registry and starts SDL2
  // quit()
  // - quits SDL2 and cleans up

  bool init();
  bool quit();
  
  //
  //             CGE Registry
  // Store strings and take them back out
  //
  // get(const std::string&)
  // - grabs a string from the registry, will return (UNKNOWN) if string not found
  // put(const std::String&, const std::string&)
  // - puts a string in the registry, replaces string if it exists
  // all()
  // - it just grabs everything in a (name:value) format
  // exists()
  // - tests for a string and returns a value
  // format()
  // - formats a string by replacing '*' with registry values
  
  namespace reg {
    const std::string& get(const std::string&);
    unsigned int       put(const std::string&, const std::string&);

    const std::vector<std::string>& all();
    bool exists(const std::string&);

    std::string format(const std::string&,const std::initializer_list<std::string>&);
  }
}

#endif

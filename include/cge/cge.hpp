#ifndef COMFYS_GAME_ENGINE_MAIN_HPP
#define COMFYS_GAME_ENGINE_MAIN_HPP

#include <string>
#include <vector>

enum cge_reg_enums {
  CGE_REG_FAILED=0,
  CGE_REG_ADDED=1,
  CGE_REG_REPLACED=2
};

namespace cge {
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
  //
  
  namespace registry {
    const std::string& get(const std::string&);
    unsigned int       put(const std::string&, const std::string&);

    const std::vector<std::string>& all();
    bool exists(const std::string&);
  }
}

#endif

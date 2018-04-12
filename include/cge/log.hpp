#ifndef COMFYS_GAME_ENGINE_LOG_HPP
#define COMFYS_GAME_ENGINE_LOG_HPP

#include <string>

namespace cge {
  namespace log {
    bool file(const std::string&);
    
    void log (const std::string&);
    void logf(const std::string&,...);
    void logp(const std::string&,unsigned int,unsigned int);

    void close();
  }
};

#endif

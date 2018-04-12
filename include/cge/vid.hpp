#ifndef COMFYS_GAME_ENGINE_VID_HPP
#define COMFYS_GAME_ENGINE_VID_HPP

#include <string>

namespace cge {
  namespace vid {
    bool init();
    bool quit();

    class window {
    protected:
      void* handle;
      bool _isopen;
      
    public:
      window();
      window(int,int,unsigned int,unsigned int,const std::string&);

      bool create(int,int,unsigned int,unsigned int,const std::string&);
      void close ();
      
      int x();
      int y();

      unsigned int w();
      unsigned int h();
    };
  };
};

#endif

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

//#include "sdl_wrapper/Wrapper.hpp"
#include "isometric_engine/MapParser.hpp"
#include "isometric_engine/Drawable.hpp"
#include "isometric_engine/Engine.hpp"

using namespace std;
using namespace sdl_wrapper;
using namespace isometric_engine;

namespace atowers
{
  class Game
  {
    private:
      bool running;
      bool windowed;

      SDL_Event event;

      SDL_Surface *screen;
      Drawable *obj, *obj2;

      Engine *engine;

    public:
      void setup();
      void run();
  };
}

#endif

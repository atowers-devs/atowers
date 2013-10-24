#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "isometric_engine/Drawable.hpp"
#include "isometric_engine/Engine.hpp"
#include "isometric_engine/sdl_wrapper/Wrapper.hpp"

using namespace std;
using namespace sdl_wrapper;
using namespace isometric_engine;

bool checkClick(Engine *eng, Drawable *d, int x, int y);
bool checkClickonEngine(Engine *eng, Drawable *obj, int x, int y);
Drawable* setMovementTarget(Engine* engine);

#endif
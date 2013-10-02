/*
  Starts the game loop and loads the state machine
 */

#include <stdlib.h>

#include "Game.hpp"

using namespace atowers;

void Game::setup()
{
  running = true;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("atowers", NULL);
  screen = SDL_SetVideoMode(800, 640, 32, SDL_HWSURFACE);

  //SDL_RWops *tile_test_rwops = SDL_RWFromFile("res/grasstile4.png", "rb");
  //SDL_Surface *tile_test = IMG_LoadPNG_RW(tile_test_rwops);
  SDL_Surface *obj_test = Wrapper::load_image("res/tank.png");

  obj = new Drawable (obj_test, 60, 40);
  obj->x = 4;
  obj->y = 3;
  obj2 = new Drawable(obj_test, 60, 40);
  obj2->x = 4;
  obj2->y = 2.5;

  FILE* mfile = fopen("res/testmap.isomap", "r");
  MapParser::load_file(mfile);
  MapParser::parse_file();
  fclose(mfile);

  engine = new Engine(screen, 64, MapParser::get_horiz(), MapParser::get_vert(), 800, 640);

  while (MapParser::has_next())
  {
    engine->insert_tile(MapParser::next());
  }

  for (int i = 0; i < MapParser::get_vert(); i++)
  {
    for (int j = 0; j < MapParser::get_horiz(); j++)
    {
      engine->set_tile(j, i, MapParser::get_tile(j, i));
      engine->set_height(j, i, MapParser::get_height(j, i));
    }
  }

  /*
  engine->insert_tile(tile_test);
  tile_test_rwops = SDL_RWFromFile("res/grasstile3.png", "rb");
  tile_test = IMG_LoadPNG_RW(tile_test_rwops);
  engine->insert_tile(tile_test);
  */
}

void Game::run()
{
  while (running)
  {
    SDL_WaitEvent(&event);

    switch (event.type)
    {
      case SDL_KEYDOWN:
        if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "up") == 0)
          obj->y -= 0.3;
        else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "right") == 0)
          obj->x += 0.3;
        else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "down") == 0)
          obj->y += 0.3;
        else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "left") == 0)
          obj->x -= 0.3;
        else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "escape") == 0)
          running = false;
        break;

      case SDL_QUIT:
        running = false;
        break;
    }

    engine->draw(obj2);
    engine->draw(obj);
    engine->draw();

    Wrapper::flip_screen();
  }
}

int main(int argc, char *argv[])
{
  Game game;
  game.setup();
  game.run();

  return 0;
}

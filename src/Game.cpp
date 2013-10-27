/*
  Starts the game loop and loads the state machine
 */

#include <stdlib.h>

#include "Game.hpp"

using namespace atowers;

void Game::setup()
{
  running = true;
  windowed = true;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("atowers", NULL);
  screen = SDL_SetVideoMode(800, 640, 32, SDL_HWSURFACE | SDL_RESIZABLE);

  //SDL_RWops *tile_test_rwops = SDL_RWFromFile("res/grasstile4.png", "rb");
  //SDL_Surface *tile_test = IMG_LoadPNG_RW(tile_test_rwops);
  SDL_Surface *obj_test = Wrapper::load_image((char*)"res/tank.png");

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

}

void Game::run()
{
  while (running)
  {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
      running = false;
      if (!windowed)
      {
      	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_RESIZABLE);
      	windowed = true;
      }
      break;
    }

    Uint8* keystate = SDL_GetKeyState(NULL);

    if (keystate[SDLK_LEFT])
    {
      obj->x -= 0.1;
    }
    
    if (keystate[SDLK_RIGHT])
    {
      obj->x += 0.1;
    }
    
    if (keystate[SDLK_UP])
    {
      obj->y -= 0.1;
    }
    
    if (keystate[SDLK_DOWN]){
      obj->y += 0.1;
    }

    if (keystate[SDLK_F11])
    {
    	if (windowed)
    	{
    		screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);
      		windowed = false;
    	}
    	else
    	{
    		screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_RESIZABLE);
      		windowed = true;
    	}
    }

    if (keystate[SDLK_ESCAPE])
    {
      running = false;
      if (!windowed)
      {
      	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_RESIZABLE);
      	windowed = true;
      }
    }
    
    engine->draw(obj);
    engine->draw(obj2);
    engine->draw();

    Drawable* d = setMovementTarget(engine);
    /*if(checkClickonEngine(engine, obj, x, y)){

      if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1)){
        printf("1 ");
      }
      if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(2)){
        printf("2 ");
      }
      if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(3)){
        printf("3 ");
      }
      fflush(stdout);
    }*/
    if(d!=NULL){
      obj->x = floor(d->x);
      obj->y = floor(d->y);
    }

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

#include "Selection.hpp"

bool checkClick(Engine *eng, Drawable *d, int x, int y){
	float ix = d->x;
	float iy = d->y;
	if(x >= ix && y >= iy && x <= ix + d->width && y <= iy + d->height){
		return Wrapper::get_pixel(d->surface, x - ix, y - iy);
	}
	return false;
}

bool checkClickonEngine(Engine *eng, Drawable *obj, int x, int y){
	Drawable *col = new Drawable(obj->surface, obj->width, obj->height);
	col->x = eng->get_iso_x(obj->x, obj->y);
	col->y = eng->get_iso_y(obj->x, obj->y) + 18;
	//Wrapper::draw_image(col->surface, 1 * col->x, 1 * col->y, col->width, col->height);
	return checkClick(eng, col, x, y);
}


Drawable* setMovementTarget(Engine* engine){
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = 0; i < engine->vert_number; i++) {
		for (int j = 0; j < engine->horiz_number; j++) {
			Drawable *d;
			d = new Drawable(engine->get_tile_surface(i, j), engine->width, 36);
			d->x = i;
			d->y = j;
			if(checkClickonEngine(engine, d, x, y)){
				if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(3)){
					return d;
				}
			}
		}
	}
	return NULL;
}

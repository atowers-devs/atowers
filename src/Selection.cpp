#include "Selection.hpp"

bool checkClick(Engine *eng, Drawable *d, int x, int y){
	//float ix = eng->get_iso_x(d->x, d->y);
	//float iy = eng->get_iso_y(d->x, d->y);
	float ix = d->x;
	float iy = d->y;
	//printf("%f %f %d %d %d %d\n", ix, iy, x, y, d->width, d->height);
	if(x >= ix && y >= iy && x <= ix + d->width && y <= iy + d->height){
		//printf("inside\n");
		return Wrapper::get_pixel(d->surface, x - ix, y - iy);
	}
	return false;
}


#include "Ground.h"

Ground::Ground()
{
	x = 0;
	y = 0;
	position = 0;
	next = nullptr;
	next_ = nullptr;
	ground_color = GYellow;
}

Ground::Ground(int x_, int y_, int posi, Ground * nex, Ground * nex_, GROUND_COLOR gc)
{
	x = x_;
	y = y_;
	position = posi;
	next = nex;
	next_ = nex_;
	ground_color = gc;
}

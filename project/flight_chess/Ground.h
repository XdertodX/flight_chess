#ifndef GROUND_H_
#define GROUND_H_

enum GROUND_COLOR { GYellow, GBlue, GRed, GGreen, GWhite };

class Ground
{
public:

	Ground();
	Ground(int x_, int y_, int posi, Ground * nex, Ground * nex_, GROUND_COLOR gc);

	int x;
	int y;
	int position;
	GROUND_COLOR ground_color;

	Ground *next;
	Ground *next_;
};

#endif
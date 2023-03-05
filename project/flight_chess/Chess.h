#ifndef CHESS_H_
#define CHESS_H_

#include "Ground.h"

enum CHESS_COLOR { CRed, CYellow, CBlue, CGreen };

class Chess
{
public:
	Chess();
	Chess(CHESS_COLOR c, int x, Ground* cg);

	int direction;
	int has_finished;
	int is_off;
	int position;
	CHESS_COLOR chess_color;
	Ground* chess_ground;

	void set_off();
	void move(int x);
};

#endif

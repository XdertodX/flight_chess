#ifndef PLAYER_H_
#define PLAYER_H_

#include "Chess.h"

enum PLAYER_COLOR { PYellow, PBlue, PRed, PGreen };

class Player
{
public:

	Player(PLAYER_COLOR c, bool f);

	int goal_achieved;
	bool is_computer;
	PLAYER_COLOR player_color;
	Chess chess[4];
};

#endif

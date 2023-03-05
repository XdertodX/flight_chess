#include "Player.h"

Player::Player(PLAYER_COLOR c, bool f)
{
	player_color = c;
	is_computer = f;
	goal_achieved = 0;
}

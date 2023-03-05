#include "Chess.h"
#include "Ground.h"

#include <graphics.h>
#include <iostream>

Chess::Chess()
{
	direction = 1;
	chess_color = CHESS_COLOR::CRed;
	has_finished = 0;
	is_off = 0;
	position = 0;
	chess_ground = nullptr;
}

Chess::Chess(CHESS_COLOR c, int x, Ground* cg)
{
	direction = 1;
	chess_color = c;
	is_off = 0;
	has_finished = 0;
	position = cg->position;
	chess_ground = cg;

	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	if (chess_color == CYellow)
		setfillcolor(YELLOW);
	if (chess_color == CBlue)
		setfillcolor(LIGHTBLUE);
	if (chess_color == CRed)
		setfillcolor(LIGHTRED);
	if (chess_color == CGreen)
		setfillcolor(LIGHTGREEN);
	fillcircle(cg->x, cg->y, 10);
}




void Chess::set_off()
{
	is_off = 1;
	chess_ground = chess_ground->next;
}

void Chess::move(int x)
{
	for (int i = 0; i < x; i++)
	{
		// 判断在road_end部分的移动方向
		if (direction == 1 && (chess_ground->position == 205 || chess_ground->position == 211 || chess_ground->position == 217 || chess_ground->position == 223))
			direction = 0;
		if (direction == 0 && (chess_ground->position == 200 || chess_ground->position == 206 || chess_ground->position == 212 || chess_ground->position == 218))
			direction = 1;

		// 判断移动的next
		if (chess_color == CYellow)
		{
			if (chess_ground->position == 0 || direction == 0)
				chess_ground = chess_ground->next_;
			else
				chess_ground = chess_ground->next;
		}
		if (chess_color == CBlue)
		{
			if (chess_ground->position == 13 || direction == 0)
				chess_ground = chess_ground->next_;
			else
				chess_ground = chess_ground->next;
		}
		if (chess_color == CRed)
		{
			if (chess_ground->position == 26 || direction == 0)
				chess_ground = chess_ground->next_;
			else
				chess_ground = chess_ground->next;
		}
		if (chess_color == CGreen)
		{
			if (chess_ground->position == 39 || direction == 0)
				chess_ground = chess_ground->next_;
			else
				chess_ground = chess_ground->next;
		}
	}

	// 判断是否需要跳或飞
	if (chess_color == CYellow && chess_ground->ground_color == GYellow && chess_ground->position != 0)
			chess_ground = chess_ground->next_;
		else if (chess_color == CBlue && chess_ground->ground_color == GBlue && chess_ground->position != 13)
			chess_ground = chess_ground->next_;
		else if (chess_color == CRed && chess_ground->ground_color == GRed && chess_ground->position != 26)
			chess_ground = chess_ground->next_;
		else if (chess_color == CGreen && chess_ground->ground_color == GGreen && chess_ground->position != 39)
			chess_ground = chess_ground->next_;

}
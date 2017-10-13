#pragma once

#include "Graphics.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle(Graphics& in_gfx, Ball& in_ball, const short in_x);
	void MoveBy(short deltaY);
	void MoveAuto(short deltaY);
	Coord GetCoord() const;
	void Draw();
public:
	static constexpr short width = 20;
	static constexpr short height = 200;
private:
	short x;
	short y = Graphics::ScreenHeight/2 - height/2;
	Graphics& gfx;
	Ball& ball;
};


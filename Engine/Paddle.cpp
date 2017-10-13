#include "Paddle.h"


Paddle::Paddle(Graphics& in_gfx, Ball& in_ball, const short in_x)
	:
	gfx(in_gfx),
	ball(in_ball)
{
	x = in_x;
}

void Paddle::MoveBy(short deltaY)
{
	y += deltaY;
	if (y < 0) y = 0;
	if (y + height >= Graphics::ScreenHeight) y = Graphics::ScreenHeight - height;
}

void Paddle::MoveAuto()
{
	//AI motion goes here
}

void Paddle::Draw()
{
	gfx.PutRect(x, y, width, height, 0xFFFFFF);
}

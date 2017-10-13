#include "Paddle.h"
#include "Game.h"


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

void Paddle::MoveAuto(short deltaY)
{
	short yCenter = y + height / 2;
	Coord ballCoord = ball.GetCoord();
	if (abs(ballCoord.y - yCenter) >= 50)
	{
		if (yCenter > ballCoord.y) y -= deltaY;
		else y += deltaY;
	}
	if (y < 0) y = 0;
	if (y + height >= Graphics::ScreenHeight) y = Graphics::ScreenHeight - height;
}

Coord Paddle::GetCoord() const
{
	return {x,y};
}

void Paddle::Draw()
{
	gfx.PutRect(x, y, width, height, 0xFFFFFF);
}

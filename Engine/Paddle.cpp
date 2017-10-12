#include "Paddle.h"

Paddle::Paddle(Graphics& in_gfx, const short in_x)
	:
	gfx(in_gfx)
{
	x = in_x;
}

void Paddle::MoveBy(short deltaY)
{
	y += deltaY;
	if (y < 0) y = 0;
	if (y + height >= Graphics::ScreenHeight) y = Graphics::ScreenHeight - height - 1;
}

void Paddle::Draw()
{
	gfx.PutRect(x, y, width, height, 0xFFFFFF);
}

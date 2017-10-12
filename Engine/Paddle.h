#pragma once

#include "Graphics.h"

class Paddle
{
public:
	Paddle(Graphics& in_gfx, const short in_x);
	void MoveBy(short deltaY);
	void MoveAuto();
	void Draw();
public:
	static constexpr short width = 20;
	static constexpr short height = 200;
private:
	short x;
	short y = Graphics::ScreenHeight/2 - height/2;
	Graphics& gfx;
};


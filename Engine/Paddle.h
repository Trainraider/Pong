#pragma once

#include "Graphics.h"

class Paddle
{
public:
	Paddle(Graphics& in_gfx, const short in_x);
	void MoveBy(short deltaY);
	void Draw();
private:
	static constexpr short width = 20;
	static constexpr short height = 200;
	short x;
	short y = Graphics::ScreenHeight/2 - height/2;
	Graphics& gfx;
public:
	
};


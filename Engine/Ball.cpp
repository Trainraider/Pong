#include "Ball.h"

Ball::Ball(Graphics & gfx)
	:
	gfx(gfx),
	rng(rd()),
	sDist(-4,4)
{
	Respawn();
}

void Ball::Draw()
{
	gfx.PutRect(x, y, dimension, dimension, 0xFFFFFF);
}

void Ball::BounceOffWall()
{
	if (y < 0)
	{
		y = 0; 
		vSpeed = -vSpeed;
	} 
	if (y + dimension >= Graphics::ScreenHeight)
	{
		y = Graphics::ScreenHeight - dimension - 1;
		vSpeed = -vSpeed;
	}
}

void Ball::HitGoal()
{
	if (x < 0 || x + dimension >= Graphics::ScreenWidth)
	{
		Respawn();
	}
}

void Ball::Respawn()
{
	do
	{
		hSpeed = sDist(rng);
		vSpeed = sDist(rng);
	} while (!hSpeed);
	x = Graphics::ScreenWidth / 2 - radius;
	y = Graphics::ScreenHeight / 2 - radius;
}

short Ball::CenterX()
{
	return x + radius;
}

short Ball::CenterY()
{
	return y + radius;
}

void Ball::Move()
{
	x += hSpeed;
	y += vSpeed;
	BounceOffWall();
	HitGoal();
}
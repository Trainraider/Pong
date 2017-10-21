#include "Ball.h"
#include "Paddle.h"

Ball::Ball(Graphics & gfx)
	:
	gfx(gfx),
	rng(rd()),
	sDist(-4.0f,4.0f)
{
	Respawn();
}

Coord Ball::GetCoord() const
{
	return {x,y};
}

void Ball::Draw()
{
	gfx.PutRect((short)x, (short)y, dimension, dimension, 0xFFFFFF);
}

void Ball::Collision(Paddle& paddle, bool leftSideOfScreen)
{
	if (leftSideOfScreen)
	{
		x = paddle.GetCoord().x + paddle.width;
		hSpeed = -1 * (hSpeed - 2);
	}
	else
	{
		x = paddle.GetCoord().x - dimension;
		hSpeed = -1 * (hSpeed + 2);
	}
	//vSpeed = (paddle.GetCoord().y + (Paddle::height / 2) - y)*(8 / Paddle::height);
	float centerY = paddle.GetCoord().y + (Paddle::height / 2);
	float numerator = centerY - y;
	float denomenator = (8.0f / (float)Paddle::height);
	float vSpeedPre = -2.0f * numerator * denomenator;
	vSpeed = vSpeedPre;

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
	} while (abs(hSpeed) < 1.5);
	x = Graphics::ScreenWidth / 2 - radius;
	y = Graphics::ScreenHeight / 2 - radius;
}

float Ball::CenterX()
{
	return x + radius;
}

float Ball::CenterY()
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
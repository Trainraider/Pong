#pragma once
#include "Graphics.h"
#include "Coord.h"
#include <random>
class Paddle;

class Ball
{
public:
	Ball(Graphics& gfx);
	Coord GetCoord() const;
	void Move();
	void Draw();
	void Collision( Paddle& paddle, bool leftSideOfScreen);
public:
	static constexpr short dimension = 20;
private:
	void BounceOffWall();
	void HitGoal();
	void Respawn();
	short CenterX();
	short CenterY();
private:
	Graphics& gfx;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> sDist;
	short x, y;
	short hSpeed, vSpeed;
	static constexpr short radius = dimension / 2;
	

};


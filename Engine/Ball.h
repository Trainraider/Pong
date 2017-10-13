#pragma once
#include "Graphics.h"
#include <random>

class Ball
{
public:
	Ball(Graphics& gfx);
	void Move();
	void Draw();
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
	int hSpeed, vSpeed;
	static constexpr short dimension = 20;
	static constexpr short radius = dimension / 2;
	

};


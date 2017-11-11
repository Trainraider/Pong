#pragma once
#include "Graphics.h"
#include "Coord.h"
#include <random>
#include "GoalInfo.h"
class Paddle;

class Ball
{
public:
	Ball(Graphics& gfx);
	Coord GetCoord() const;
	Coord GetSpeed() const;
	int GetRespawnCount() const;
	void Move();
	GoalInfo HitGoal();
	void Draw();
	bool GetWasHit();
	void Collision( Paddle& paddle, bool leftSideOfScreen);
public:
	static constexpr short dimension = 20;
private:
	void BounceOffWall();
	void Respawn();
	float CenterX();
	float CenterY();
private:
	Graphics& gfx;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> sDist;
	bool wasHit = false;
	int respawnCount = 0;
	float x, y;
	float hSpeed, vSpeed;
	static constexpr short radius = dimension / 2;
	

};


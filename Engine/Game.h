/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include "NeuralNet.h"

struct Net {
	NeuralNet * brain;
	unsigned int fitness = 0;
};

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawNet();
	bool Collision(Ball& ball, Paddle& padd);
	void NetToPaddle(NeuralNet& net, Paddle& pad);
	void NewMatch();
	void NextGen();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	random_device rd;
	mt19937 rng;
	uniform_int_distribution<int> rdmBrain;
	Paddle left;
	Paddle right;
	Ball ball;
	static constexpr int brainCount = 200;
	bool drawScreen = true;
	bool pressedSpace = false;
	bool matchIsNew = true;
	int generation = 0;
	int roundsPerMatch = 3;
	int activeL = 0;
	int activeR = 1;
	Net brains[brainCount];
	/********************************/
};
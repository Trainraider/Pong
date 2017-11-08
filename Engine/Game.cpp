/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	player(gfx, ball, 50),
	ai(gfx, ball, Graphics::ScreenWidth - Paddle::width - 50),
	ball(gfx),
	brain()
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	//if (wnd.kbd.KeyIsPressed('W')) player.MoveBy(-4);
	//if (wnd.kbd.KeyIsPressed('S')) player.MoveBy(4);
	brain.TakeInputs(ball, player);
	switch (brain.Think())
	{
	case UP: player.MoveBy(-4); break;
	case DOWN: player.MoveBy(4); break;
	case NOTHING: break;
	}
	ai.MoveAuto(4);
	ball.Move();
	if (Collision(player.GetCoord(), player.width, player.height, ball.GetCoord(), ball.dimension, ball.dimension))
	{
		ball.Collision(player, true);
	}
	if (Collision(ai.GetCoord(), ai.width, ai.height, ball.GetCoord(), ball.dimension, ball.dimension))
	{
		ball.Collision(ai, false);
	}




}

void Game::DrawNet()
{
	for (int i = 0; i < Graphics::ScreenHeight; i++)
	{
		if (int(i/7.)%2 == 0)
		gfx.PutPixel(Graphics::ScreenWidth / 2, i, 0xFFFFFF);
	}
}

void Game::ComposeFrame()
{
	player.Draw();
	ai.Draw();
	ball.Draw();
	DrawNet();
}

bool Game::Collision(Coord coord0, short width0, short height0, Coord coord1, short width1, short height1)
{
	float right0 = coord0.x + width0;
	float bottom0 = coord0.y + height0;
	float right1 = coord1.x + width1;
	float bottom1 = coord1.y + height1;
	if (coord0.x <= right1 &&
		bottom0 >= coord1.y &&
		coord0.y <= bottom1 &&
		right0 >= coord1.x)
	{
		return true;
	}
	return false;
}
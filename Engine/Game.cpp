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
#include "GoalInfo.h"

Game::Game(MainWindow& wnd)
	:
	rng(rd()),
	rdmBrain(0, brainCount - 1),
	wnd(wnd),
	gfx(wnd),
	left(gfx, ball, 50),
	right(gfx, ball, Graphics::ScreenWidth - Paddle::width - 50),
	ball(gfx)
{
	for (int i = 0; i < brainCount; i++) {
		brains[i].brain = new NeuralNet();
	}
}

void Game::Go()
{
	if (drawScreen){
		gfx.BeginFrame();
		UpdateModel();
		ComposeFrame();
		gfx.EndFrame();
	}
	else
	{
		UpdateModel();
	}
}

void Game::UpdateModel()
{
	//if (wnd.kbd.KeyIsPressed('W')) left.MoveBy(-4);
	//if (wnd.kbd.KeyIsPressed('S')) left.MoveBy(4);
	//right.MoveAuto(4);
	if (wnd.kbd.KeyIsPressed(' ')) {
		if (pressedSpace == false) {
			pressedSpace = true;
			drawScreen = !drawScreen;
		}
	}
	else {
		pressedSpace = false;
	}
	
	brains[activeL].brain->TakeInputs(ball, left, right, false);
	brains[activeR].brain->TakeInputs(ball, right, left, true);
	NetToPaddle(brains[activeL], left);
	NetToPaddle(brains[activeR], right);
	ball.Move();
	GoalInfo goal = ball.HitGoal();
	if (goal.hitGoal && goal.wasHit) {
		if (goal.left) {
			brains[activeR].wins += 1;
			brains[activeL].losses += 1;
		}
		else {
			brains[activeL].wins += 1;
			brains[activeR].losses += 1;
		}
	}
	if (goal.hitGoal && !goal.wasHit) {
		if (goal.left) {
			brains[activeL].losses += 1;
		}
		else {
			brains[activeR].losses += 1;
		}
	}
	if (Collision(ball,left))
	{
		ball.Collision(left, true);
		brains[activeL].hits += 1;
	}
	if (Collision(ball,right))
	{
		ball.Collision(right, false);
		brains[activeR].hits += 1;
	}
	if (ball.GetRespawnCount()%roundsPerMatch == 0
		&& matchIsNew == false) {
		NewMatch();
	}
	if (ball.GetRespawnCount() % roundsPerMatch == 1)
		matchIsNew = false;

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
	left.Draw();
	right.Draw();
	ball.Draw();
	DrawNet();
	brains[activeL].brain->DrawNeuralNet(gfx, 40, 20);
	brains[activeR].brain->DrawNeuralNet(gfx, 460, 20);
}

bool Game::Collision(Ball & ball, Paddle & padd)
{
	float right0 = ball.GetCoord().x + ball.dimension;
	float bottom0 = ball.GetCoord().y + ball.dimension;
	float right1 = padd.GetCoord().x + padd.width;
	float bottom1 = padd.GetCoord().y + padd.height;
	if (ball.GetCoord().x <= right1 &&
		bottom0 >= padd.GetCoord().y &&
		ball.GetCoord().y <= bottom1 &&
		right0 >= padd.GetCoord().x)
	{
		return true;
	}
	return false;

}

void Game::NetToPaddle(Net & net, Paddle & pad)
{
	int output = net.brain->Think();
	switch (output)
	{
	case UP: pad.MoveBy(-4); break;
	case DOWN: pad.MoveBy(4); break;
	case NOTHING: break;
	}
	if (net.lastOutput == -1) {
		net.lastOutput = output;
	}
	else {
		if (net.lastOutput != output) {
			net.disqualified = false;
		}
	}
}

void Game::NewMatch()
{
	matchIsNew = true;
	int winner, loser;
	if (GetFitness(activeL) > GetFitness(activeR)) {
		winner = activeL;
		loser = activeR;
	}
	else {
		winner = activeR;
		loser = activeL;
	}
	if (brains[winner].disqualified)
	{
		brains[winner].brain->Randomize();
		if (brains[loser].disqualified) {
			brains[loser].brain->Randomize();
		}
		ResetBrain(winner);
		ResetBrain(loser);
	}
	else {
		*brains[loser].brain = *brains[winner].brain;
		brains[loser].brain->Mutate();
		activeL += 2;
		activeR += 2;
	}
	if (activeL >= brainCount) {
		activeL = 0;
		activeR = 1;
		NextGen();
	}
	
}

void Game::NextGen()
{
	string fname = "BrainGen" + to_string(generation) + ".nnet";
	FileDump file;
	int bestBrain = 0;
	float bestFitness = 0.0f;
	for (int i = 0; i < brainCount; i++) {
		if (GetFitness(i) > bestFitness && !brains[i].disqualified) {
			bestFitness = GetFitness(i);
			bestBrain = i;
		}
		ResetBrain(i);
	}
	if (generation % 10 == 0)
	{
		file.Create(fname.c_str());
		file.Close();
		brains[bestBrain].brain->OverwriteFile(fname.c_str());
	}
	NeuralNet * store;
	for (int i = 0; i < brainCount; i++) {
		//swap(brains[i].brain, brains[rdmBrain(rng)].brain);
		int num = rdmBrain(rng);
		store = brains[i].brain;
		brains[i].brain = brains[num].brain;
		brains[num].brain = store;
	}
	generation++;
}

void Game::ResetBrain(int i)
{
	brains[i].disqualified = true;
	brains[i].lastOutput = -1;
	brains[i].hits = 0;
	brains[i].wins = 0;
	brains[i].losses = 0;
}

float Game::GetFitness(int i)
{
	return FitnessSigmoid(brains[i].wins) - FitnessSigmoid(brains[i].losses);
	//return FitnessSigmoid(brains[i].hits);
}

float Game::FitnessSigmoid(float x)
{
	return std::tanh(x / 20.0f);
}

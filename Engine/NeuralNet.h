#pragma once
#include <random>
#include "Ball.h"
#include "Paddle.h"
#include "Matrix.h"
#include "Files.h"
#include <sstream>

#define INPUTS 5
#define OUTPUTS 3
#define LAYERS 2

#define UP 0
#define DOWN 1
#define NOTHING 2

class NeuralNet
{
	static constexpr int neurons = 10;
public:
	NeuralNet();
	~NeuralNet();
	void TakeInputs(const Ball& ball, const Paddle& padd);
	int Think();
	void OverwriteFile();
	void LoadFile();
	void DrawNeuralNet(Graphics& gfx, int x, int y);
private:
	float Sigmoid(float x);
	float XLinmoid(float x);
	float YLinmoid(float y);
private:
	std::stringstream fileName;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	std::uniform_real_distribution<float> tiny;
	Matrix<float> * weights[LAYERS + 1];
	Matrix<float> * biases[LAYERS + 1];
	Matrix<float> * activations[LAYERS + 2];


};

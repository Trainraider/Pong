#pragma once
#include <random>
#include "Ball.h"
#include "Paddle.h"
#include "Matrix.h"


#define INPUTS 5
#define OUTPUTS 3
#define LAYERS 5

#define UP 0
#define DOWN 1
#define NOTHING 2

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();
	int Think();
	void TakeInputs(const Ball& ball, const Paddle& padd);
private:
	float Sigmoid(float x);
	float XLinmoid(float x);
	float YLinmoid(float y);
private:
	static constexpr int neurons = 9;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	Matrix<float> * weights[LAYERS + 1];
	Matrix<float> * biases[LAYERS + 1];
	Matrix<float> * activations[LAYERS + 2];


};

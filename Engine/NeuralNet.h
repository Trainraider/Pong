#pragma once
#include <random>
#include "Ball.h"
#include "Paddle.h"
#include "Matrix.h"


#define INPUTS 5
#define OUTPUTS 3
#define LAYERS 2

class NeuralNet
{
public:
	NeuralNet();
private:
	float Sigmoid(float x);
private:
	static constexpr int neurons = 6;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	Matrix<float> * weights[LAYERS + 1];
	Matrix<float> * biases[LAYERS + 1];
	Matrix<float> * activations[LAYERS + 2];

};

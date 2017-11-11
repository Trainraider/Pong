#pragma once
#include <random>
#include "Ball.h"
#include "Paddle.h"
#include "Matrix.h"
#include "Files.h"
#include <sstream>

#define INPUTS 6
#define OUTPUTS 3
#define LAYERS 3

#define UP 0
#define DOWN 1
#define NOTHING 2

class NeuralNet
{
	static constexpr int neurons = 7;
public:
	NeuralNet();
	~NeuralNet();
	void TakeInputs(const Ball& ball, const Paddle& self, const Paddle& other,bool invertX);
	int Think();
	void OverwriteFile(const string& fileName);
	void LoadFile(const string& fileName);
	void DrawNeuralNet(Graphics& gfx, int x, int y);
	void Mutate();
	void Randomize();
	void operator=(NeuralNet& net);
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
	std::uniform_real_distribution<float> chance;
	Matrix<float> * weights[LAYERS + 1];
	Matrix<float> * biases[LAYERS + 1];
	Matrix<float> * activations[LAYERS + 2];


};


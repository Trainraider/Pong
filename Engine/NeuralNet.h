#pragma once
#include <Eigen/Dense>
#include "Ball.h"
#include <random>

class NeuralNet
{
public:
	NeuralNet();
private:
	std::mt19937 rng;
	static constexpr int hiddenLayers = 2;
	static constexpr int NeuronsPerLayer = 6;
};
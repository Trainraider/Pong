#pragma once
#include <Eigen/Dense>
#include <random>
#include "Ball.h"


#define INPUTS 5
#define OUTPUTS 3
#define LAYERS 2

class NeuralNet
{
public:
	NeuralNet();
	static constexpr int NeuronsPerLayer = 6;
private:
	std::random_device rd;
	std::mt19937 rng;
	Eigen::Matrix<float, INPUTS, 1> input;
	Eigen::Matrix<float, OUTPUTS, 1> output;
	Eigen::Matrix<float, NeuronsPerLayer, 1 > layerList[LAYERS];
	Eigen::Matrix<float, NeuronsPerLayer, 1 > layerBiasList[LAYERS];
	Eigen::Matrix<float, NeuronsPerLayer, 1 > outputBias;
	Eigen::Matrix<float, NeuronsPerLayer, NeuronsPerLayer> weightList[LAYERS]; 
	Eigen::Matrix<float, NeuronsPerLayer, INPUTS > inputWeights;
	Eigen::Matrix<float, OUTPUTS, NeuronsPerLayer> outputWeights;
};

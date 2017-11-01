#pragma once
#include <Eigen/Dense>
#include <random>
#include "Ball.h"


#define INPUTS 5
#define OUTPUTS 3
#define LAYERS 2
#define RANDOMIZEMATRIXLIST(matrixList,matrices,rows,cols) \
	for (int i = 0; i < matrices; i++)\
		{\
		for (int j = 0; j < rows; j++)\
			{\
			for (int k = 0; k < cols; k++)\
				{\
				matrixList[i](j, k) = dist(rng);\
				}\
			}\
		}

class NeuralNet
{
public:
	NeuralNet();
	static constexpr int neurons = 6;
	Eigen::Matrix<float, INPUTS, 1> input;
	Eigen::Matrix<float, OUTPUTS, 1> output;
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	Eigen::Matrix<float, neurons, 1 > layerList[LAYERS];
	Eigen::Matrix<float, neurons, 1 > layerBiasList[LAYERS];
	Eigen::Matrix<float, neurons, 1 > outputBias;
	Eigen::Matrix<float, neurons, neurons> weightList[LAYERS]; 
	Eigen::Matrix<float, neurons, INPUTS > inputWeights;
	Eigen::Matrix<float, OUTPUTS, neurons> outputWeights;
};

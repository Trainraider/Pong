#include "NeuralNet.h"
#include "Graphics.h"
#include <cmath>


NeuralNet::NeuralNet()
	:
	rng(rd()),
	dist(-5.0f,5.0f)
{

}

float NeuralNet::Sigmoid(float x)
{
	return std::tanh(x/4)/2 + 0.5f;
}
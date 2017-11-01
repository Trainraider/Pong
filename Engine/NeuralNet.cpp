#include "NeuralNet.h"
using namespace Eigen;

NeuralNet::NeuralNet()
	:
	rng(rd()),
	dist(-5.0f,5.0f)
{
	RANDOMIZEMATRIXLIST(weightList, LAYERS, neurons, neurons)
	RANDOMIZEMATRIXLIST(layerBiasList, LAYERS, neurons, 1)

}

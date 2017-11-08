#include "NeuralNet.h"
#include "Graphics.h"
#include <cmath>


NeuralNet::NeuralNet()
	:
	rng(rd()),
	dist(-5.0f,5.0f)
{
	weights[0] = new Matrix<float>(neurons, INPUTS);
	for (int i = 0; i < LAYERS - 1; i++) {
		weights[i + 1] = new Matrix<float>(neurons,neurons);
	}
	weights[LAYERS] = new Matrix<float>(OUTPUTS, neurons);

	activations[0] = new Matrix<float>(INPUTS, 1);
	for (int i = 0; i < LAYERS; i++)
	{
		activations[i + 1] = new Matrix<float>(neurons, 1);
		biases[i] = new Matrix<float>(neurons, 1);
	}
	activations[LAYERS + 1] = new Matrix<float>(OUTPUTS, 1);
	biases[LAYERS] = new Matrix<float>(OUTPUTS, 1);

	for (int i = 0; i < LAYERS + 1; i++) {
		int size = weights[i]->GetSize();
		for (int j = 0; j < size; j++) {
			(*weights[i])(j) = dist(rng);
		}
		size = biases[i]->GetSize();
		for (int j = 0; j < size; j++) {
			(*biases[i])(j) = dist(rng);
		}
	}
}

NeuralNet::~NeuralNet()
{
	for (int i = 0; i < LAYERS + 1; i++) {
		delete weights[i];
		delete biases[i];
		delete activations[i];
	}
	delete activations[LAYERS + 1];
}

int NeuralNet::Think()
{
	for (int i = 0; i < LAYERS + 1; i++) {
		weights[i]->DotBias(*activations[i], *biases[i], *activations[i + 1]);
		int size = activations[i + 1]->GetSize();
		for (int j = 0; j < size; j++) {
			(*activations[i + 1])(j) = Sigmoid((*activations[i + 1])(j));
		}
	}
	int decision;
	if ((*activations[LAYERS + 1])(0) > (*activations[LAYERS + 1])(1)) {
		if ((*activations[LAYERS + 1])(0) > (*activations[LAYERS + 1])(2)) {
			decision = UP;
		} 
		else {
			decision = DOWN;
		}
	}
	else {
		if ((*activations[LAYERS + 1])(1) > (*activations[LAYERS + 1])(2)) {
			decision = NOTHING;
		}
		else {
			decision = DOWN;
		}
	}
	return decision;
}

void NeuralNet::TakeInputs(const Ball & ball, const Paddle & padd)
{
	float inputs[INPUTS];
	inputs[0] = YLinmoid(padd.GetCoord().y);
	inputs[1] = XLinmoid(ball.GetCoord().x);
	inputs[2] = YLinmoid(ball.GetCoord().y);
	inputs[3] = Sigmoid(ball.GetSpeed().x);
	inputs[4] = Sigmoid(ball.GetSpeed().y);

	*activations[0] = inputs;
}

float NeuralNet::Sigmoid(float x)
{
	return std::tanh(x/4)/2 + 0.5f;
}

float NeuralNet::XLinmoid(float x)
{
	return x/Graphics::ScreenWidth;
}

float NeuralNet::YLinmoid(float y)
{
	return y / Graphics::ScreenHeight;
}

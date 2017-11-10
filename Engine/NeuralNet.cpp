#include "NeuralNet.h"
#include "Coord.h"
#include <cmath>
#include "ColorConversion.h"



NeuralNet::NeuralNet()
	:
	rng(rd()),
	dist(-7.0f,7.0f),
	tiny(-.05,.05)
{
	using namespace std;
	fileName << "brain" << to_string(LAYERS) << "-" << to_string(neurons) << ".nnet";
	//FileDump file;
	//if (!file.Exists(fileName.str().c_str())) {
	//	file.Create(fileName.str().c_str());
	//}

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
			(*biases[i])(j) = dist(rng) / 5.0f;
		}
	}
	//OverwriteFile();
	//LoadFile();
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

void NeuralNet::OverwriteFile()
{
	FileDump file;
	file.Open(fileName.str().c_str());
	for (int i = 0; i < LAYERS + 1; i++) {
		file.DumpArray(weights[i]->data, weights[i]->GetSize());
	}
	for (int i = 0; i < LAYERS + 1; i++) {
		file.DumpArray(biases[i]->data, biases[i]->GetSize());
	}
	file.Close();
}

void NeuralNet::LoadFile()
{
	FileDump file;
	file.Open(fileName.str().c_str());
	for (int i = 0; i < LAYERS + 1; i++) {
		file.FillArray(weights[i]->data, weights[i]->GetSize());
	}
	for (int i = 0; i < LAYERS + 1; i++) {
		file.FillArray(biases[i]->data, biases[i]->GetSize());
	}
	file.Close();
}

void NeuralNet::DrawNeuralNet(Graphics & gfx, int x, int y)
{
	int hD = int(300.0f / (LAYERS + 2));
	int vD;
	int vD2;
	int neuronRadius = 6;
	for (int i = 0; i < LAYERS + 2; i++)
	{
		int size = activations[i]->GetSize();
		int size2;
		if (i < LAYERS + 1)  size2 = activations[i + 1]->GetSize();
		vD = int(200.0f / size);
		if (i < LAYERS + 1) vD2 = int(200.0f / size2);
		for (int j = 0; j < size; j++) {
			unsigned char act = unsigned char(255*((*activations[i])(j)));
			Color col = { act,act,act };
			Coord n1 = { float(hD*i + hD / 2), float(vD*j + vD / 2) };
			if (i < LAYERS + 1) 
				for (int k = 0; k < size2; k++) {
					Coord n2 = { float(hD*(i + 1) + hD / 2), float(vD2*k + vD2 / 2) };
					float weight = (*weights[i])(k, j);
					Color Cweight;
					double h, s, v;
					s = tanh(abs(weight) / 4);
					v = 0.8*((*activations[i])(j)*tanh(abs(weight) / 4)) + .2;
					if (weight > 0) {
						h = 180;
					}
					else {
						h = 0;
					}
					rgb c = hsv2rgb({h, s, v});
					Cweight = {unsigned char(255*c.r),unsigned char(255 * c.g),unsigned char(255 * c.b)};
					gfx.DrawLine((int)n1.x + x, (int)n1.y + y, (int)n2.x + x, (int)n2.y + y, Cweight);
				}
			gfx.DrawCircle(int(n1.x) + x, int(n1.y) + y, neuronRadius, 4, col);
		}
	}
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

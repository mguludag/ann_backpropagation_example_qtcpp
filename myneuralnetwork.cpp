#include "myneuralnetwork.h"

int MyNeuralNetwork::XB = 1;

double MyNeuralNetwork::W11 = -2.11;
double MyNeuralNetwork::W12 = 0.69;
double MyNeuralNetwork::W13 = -2.89;
double MyNeuralNetwork::W21 = 1.83;
double MyNeuralNetwork::W22 = 1.12;
double MyNeuralNetwork::W23 = -1.36;
double MyNeuralNetwork::W31 = 1.49;
double MyNeuralNetwork::W32 = 1.97;

double MyNeuralNetwork::WB1 = -0.24;
double MyNeuralNetwork::WB2 = -2.4;
double MyNeuralNetwork::WB3 = -2.12;

MyNeuralNetwork::MyNeuralNetwork(/*QObject *parent,*/) {}

std::array<double, 8> MyNeuralNetwork::getWeights()
{
    weights = {W11, W12, W13, W21, W22, W23, W31, W32};
    return weights;
}

std::array<int, 4> MyNeuralNetwork::getinOut()
{
    inOut = {X1, X2, X3, Y};
    return inOut;
}

std::array<double, 3> MyNeuralNetwork::getBias()
{
    bias = {WB1, WB2, WB3};
    return bias;
}

double MyNeuralNetwork::getError()
{
    return outErr;
}

std::array<double, 3> MyNeuralNetwork::getF()
{
    F = {Y1, Y2, Y3};
    return F;
}

double MyNeuralNetwork::sigmoid(double net)
{
    return 1 / (1 + /*gcem::*/ exp(-net));
}

void MyNeuralNetwork::activateNeuron(uint8_t neuron)
{
    switch (neuron) {
    case 1:
        N1 = (X1 * W11) + (X2 * W21) + (X3 * W31) + (XB * WB1);
        Y1 = sigmoid(N1);
        break;
    case 2:
        N2 = (X1 * W12) + (X2 * W22) + (X3 * W32) + (XB * WB2);
        Y2 = sigmoid(N2);
        break;
    case 3:
        N3 = (Y1 * W13) + (Y2 * W23) + (XB * WB3);
        Y3 = sigmoid(N3);
        break;
    }
}

void MyNeuralNetwork::backPropagation()
{
    E3 = Y3 * ((1 - Y3) * (Y - Y3));
    WB3 += 1 * E3 * XB;
    W13 += 1 * E3 * Y1;
    W23 += 1 * E3 * Y2;

    E2 = Y2 * ((1 - Y2) * (W23 * E3));
    WB2 += (1 * E2 * XB);
    W12 += (1 * E2 * X1);
    W22 += (1 * E2 * X2);
    W32 += (1 * E2 * X3);

    E1 = Y1 * ((1 - Y1) * (W13 * E3));
    WB1 += (1 * E1 * XB);
    W11 += (1 * E1 * X1);
    W21 += (1 * E1 * X2);
    W31 += (1 * E1 * X3);
}

void MyNeuralNetwork::setinOut(int x1, int x2, int x3, int y)
{
    X1 = x1;
    X2 = x2;
    X3 = x3;
    Y = y;
}

void MyNeuralNetwork::resetWeights()
{
    MyNeuralNetwork::XB = 1;

    MyNeuralNetwork::W11 = -2.11;
    MyNeuralNetwork::W12 = 0.69;
    MyNeuralNetwork::W13 = -2.89;
    MyNeuralNetwork::W21 = 1.83;
    MyNeuralNetwork::W22 = 1.12;
    MyNeuralNetwork::W23 = -1.36;
    MyNeuralNetwork::W31 = 1.49;
    MyNeuralNetwork::W32 = 1.97;

    MyNeuralNetwork::WB1 = -0.24;
    MyNeuralNetwork::WB2 = -2.4;
    MyNeuralNetwork::WB3 = -2.12;
}

void MyNeuralNetwork::calcErrors()
{
    outErr = 0.5 * pow((Y - Y3), 2);
}

void MyNeuralNetwork::test()
{
    activateNeuron(1);
    activateNeuron(2);
    activateNeuron(3);
    calcErrors();
}

void MyNeuralNetwork::run()
{
    activateNeuron(1);
    activateNeuron(2);
    activateNeuron(3);
    calcErrors();
    backPropagation();

}

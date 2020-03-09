#ifndef MYNEURALNETWORK_H
#define MYNEURALNETWORK_H

//#include "gcem.hpp"
#include <cmath>
//#include <tuple>
#include <array>
#include <QDebug>
//#include <QObject>

class MyNeuralNetwork //: public QObject
{
    // Q_OBJECT

    static int XB;
    int X1, X2, X3, Y;
    double E1, E2, E3, N1, N2, N3, Y1, Y2, Y3, outErr;
    static double W11, W12, W13, W21, W22, W23, W31, W32, WB1, WB2, WB3;
    std::array<double, 8> weights;
    std::array<double, 3> bias;
    std::array<double, 3> errors;
    std::array<double, 3> F;
    std::array<int, 4> inOut;

public:
    MyNeuralNetwork(/*QObject *parent = nullptr,*/);
    std::array<double, 8> getWeights();
    std::array<int, 4> getinOut();
    std::array<double, 3> getBias();
    double getError();
    std::array<double, 3> getF();
    double sigmoid(double net);
    void activateNeuron(uint8_t neuron);
    void backPropagation();
    void setinOut(int x1, int x2, int x3, int y);
    void resetWeights();
    void calcErrors();
    void test();
    void run();

    //signals:

    //public slots:
};

#endif // MYNEURALNETWORK_H

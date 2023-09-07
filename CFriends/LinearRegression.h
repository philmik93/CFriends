#pragma once
#include "Include.h"
#include "Perceptron.h"



class LinearRegression : public App
{
public:
    Perceptron<2> perceptron;
    static const int POINT_COUNT = 600;
    static const int POINT_SIZE = 10;
    static const int INPUT_COUNT = 2;
    CVector<double> points[POINT_COUNT];
    int counter;
    double a, b;
public:
    void setup() override;
    void process(double dt);

    double f(double x);
};

#pragma once
#include "Include.h"
#include "LinearRegression.h"

template<int inputCount>
class Perceptron
{
public:
    double weights[inputCount+1];
    double learningRate = 0.0007;

public:

    inline Perceptron<inputCount>()
    {
        for (int i = 0; i < inputCount; i++)
        {
            weights[i] = randf(-1, 1);
        }
    }



    inline double weightedSum(double* inputs)
    {
        double sum = 0;
        for (int i = 0; i < inputCount+1; i++)
        {
            sum += inputs[i] * weights[i];
        }
        return sum;
    }



    inline double activation(double sum)
    {
        return (sum >= 0) ? 1 : -1;
    }



    inline double getGuess(double* inputs)
    {
        return activation(weightedSum(inputs));
    }



    inline double getGuessY(double x)
    {
        return -((weights[0]*x+weights[2])/weights[1]);
    }


    inline void train(double* inputs, double label)
    {
        double error = label - getGuess(inputs);
        for (int i = 0; i < inputCount + 1; i++)
        {
            weights[i] += inputs[i] * error * learningRate;
        }
    }


};

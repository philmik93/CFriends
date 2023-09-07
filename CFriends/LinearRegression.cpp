#include "Include.h"
#include "LinearRegression.h"
#include "Perceptron.h"

/*
int main()
{
	run(new LinearRegression());
}
*/


void LinearRegression::setup()
{
	setSize(800, 600);
	a = randf(-1, 1);
	b = randf(0, 1);
	
	for (int i = 0; i < POINT_COUNT; i++)
	{
		points[i] = CVector<double>(randf(-1, 1), randf(-1, 1), 0);
		if (points[i].get(1) <= f(points[i].get(0))) points[i].set(-1, 2);
		else points[i].set(1, 2);
		
	}
	perceptron = Perceptron<2>();
	counter = 0;
	

	
}

void LinearRegression::process(double dt)
{
	background(150);
	double inputs[3];

	setColor(0,0,255);
	line(0, map(f(-1), -1, 1, 0, getHeight()), getWidth(), map(f(1), -1, 1, 0, getHeight()));

	setColor(0);
	line(0, map(perceptron.getGuessY(-1), -1, 1, 0, getHeight()), getWidth(), map(perceptron.getGuessY(1), -1, 1, 0, getHeight()));

	for (int i = 0; i < POINT_COUNT; i++)
	{
		setColor(0);
		setLineWidth(2);
		drawCircle(map(points[i].get(0), -1, 1, 0, getWidth()), map(points[i].get(1), -1, 1, 0, getHeight()), POINT_SIZE);
		inputs[0] = points[i].get(0);
		inputs[1] = points[i].get(1);
		inputs[2] = 1;
		double guess = perceptron.getGuess(inputs);
		if (guess == points[i].get(2)) setColor(0, 255, 0);
		else setColor(255 ,0 ,0);
		fillCircle(map(points[i].get(0), -1, 1, 0, getWidth()), map(points[i].get(1), -1, 1, 0, getHeight()), POINT_SIZE-1);
	}


	inputs[0] = points[counter].get(0);
	inputs[1] = points[counter].get(1);
	inputs[2] = 1;
	perceptron.train(inputs, points[counter].get(2));
	counter = (counter + 1) % POINT_COUNT;
}


double LinearRegression::f(double x)
{
	return a * x + b;
}


#pragma once
#include "Include.h"
#include "Vehicle.h"


class Flocking : public App
{
public:
	static const int VEHICLE_COUNT = 130;
	Vehicle vehicles[VEHICLE_COUNT];

public:
	inline void setup() override
	{
		setSize(800, 600);
		for (int i = 0; i < VEHICLE_COUNT; i++)
		{
			vehicles[i] = Vehicle(CVector<double>(randf(0, getWidth()), randf(0, getHeight())));
		}
	}



	inline void process(double dt) override
	{
		background(130);

		for (int i = 0; i < VEHICLE_COUNT; i++)
		{
			vehicles[i].applyBehaviors(vehicles);
			vehicles[i].borders();
			vehicles[i].update(dt);
			vehicles[i].display();
		}
	}
};



/*
int main()
{
	run(new Flocking());
}
*/
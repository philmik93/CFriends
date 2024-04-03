#pragma once
#include "Include.h"
#include "Object.h"
#include "Engine.h"






class PhysicsEngine2D : public App
{
	
	int count = 10;
	Engine* engine;


	inline void setup() override
	{
		setSize(800, 600);
		setTitle("Physics");
		engine = new Engine(5);
		
	}


	inline void process(double dt) override
	{
		background(255);
		engine->run(dt);
		
		if (isMousePressed())
		{
			CVector<float> wind({0.1f, 0.0f});
			engine->addForce(wind);
		}
		
	}



};







int main()
{
	run(new PhysicsEngine2D());
}

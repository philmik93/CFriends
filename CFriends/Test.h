#pragma once
#include "Include.h"



class Test : public App
{


public:


	inline void setup() override
	{
		setSize(400, 400);
		


	}


	inline void process(double dt) override
	{
		background(30);
		setColor(200, 0, 0);
		for (int i = 0; i < 1; i++)
			fillCircle(getMouseX(), getMouseY(), 30,30);
	}

};







int main()
{
	run(new Test());
}


 
 /*
 int main()
 {
 	run(new Test());
 }
 */
 


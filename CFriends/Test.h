#pragma once
#include "Include.h"



class Test : public App
{


public:


	inline void setup() override
	{
		setSize(800, 800);
		

	}


	inline void process(double dt) override
	{
		background(30);
		setColor(200, 0, 0);
		drawCircle(100, 100, 30, 30);
	}

};










 
 /*
 int main()
 {
 	run(new Test());
 }
 */


 


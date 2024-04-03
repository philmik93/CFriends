#pragma once
#include "Include.h"



class Test : public App
{


public:
	CTexture* tex;

	inline void setup() override
	{
		//setSize(600,400);
		tex = loadTexture("res/textures/lightning.jpg");
		
	}


	inline void process(double dt) override
	{
		background(30);
		setLineWidth(4);
		setColor(255,255,50);
		setColor(50);
		
		for (int i = 0; i < 500; i++)
		{
			fillCircle(getMouseX() + i, getMouseY()+i, 40, 40);
		}

		
		texture(tex, 20, 20, 100, 100);
	}

};



/*
int main()
{
	run(new Test());
}
*/







 

 
 
 


 


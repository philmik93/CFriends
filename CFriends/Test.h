#pragma once
#include "Include.h"



class Test : public App
{


public:
	CTexture* tex;

	inline void setup() override
	{
		setSize(600,400);
		
	}


	inline void process(double dt) override
	{
		background(30);
		setLineWidth(10);
		setColor(255,255,50);
		setColor(50);
		
		
		line(getWidth()/2,getHeight()/2,getMouseX(),getMouseY());
		drawRect(30,30, 50,50);
		
	}

};




int main()
{
	run(new Test());
}







 

 
 
 


 


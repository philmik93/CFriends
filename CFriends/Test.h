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
		fillRect(100,100, 100,100);
		//drawRect(50,50,50,50);
	}

};




int main()
{
	run(new Test());
}







 

 
 
 


 


#pragma once
#include "Include.h"



class Test : public App
{


public:
	
	OpenGLTexture* texturePtr;

	inline void setup() override
	{
		
		setSize(800, 800);
		setColor(200,200,100);
		fillRect(0,0, 50, 50);
		drawTri(200, 200, 400, 200, 300, 0);
		
		
	}


	inline void process(double dt) override
	{
		
	}

};










 

 
 
 


 


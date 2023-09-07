#pragma once
#include "Include.h"



class Test : public App
{


public:
	
	OpenGLTexture texturew;

	inline void setup() override
	{
		setSize(800, 800);
		texturew = OpenGLTexture("res/textures/neurons.jpg");
	}


	inline void process(double dt) override
	{
		background(30);
		
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		texture(texturew, 0, 0, texturew.getWidth(), texturew.getHeight());
	}

};










 

 
 
 


 


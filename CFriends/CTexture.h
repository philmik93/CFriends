#pragma once
#include "Include.h"


class CTexture
{

public:
	
	inline virtual void bind(unsigned int slot = 0) const = 0;
	inline virtual void unbind() const = 0; 
	inline virtual int getWidth() const = 0;
	inline virtual int getHeight() const = 0;
};

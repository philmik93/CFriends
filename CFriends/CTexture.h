#pragma once
#include "Include.h"


class CTexture
{

public:
	virtual void bind(unsigned int slot = 0) const = 0;
	virtual void unbind() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
};

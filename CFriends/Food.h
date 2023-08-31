#pragma once
#include "Include.h"
#include "Bloob.h"
#include "Bloobs.h"
#include "Population.h"

class Food
{
public:
	static const float INIT_NUTRITION;
	static const float INIT_SIZE;
	float nutrition;
	float size;
	CVector<float> pos;
	

public:
	Food();
	void display();
};

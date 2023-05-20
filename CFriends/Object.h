#pragma once
#include "Include.h"

class Object
{
public:
	CVector<float> pos, vel, acc;
	float size;
	bool dirty;

public:
	Object(float x, float y, float size);
	Object();
	void display();
	void update(double dt);


	bool isOnButton();
	bool isOnLeft();
	bool isOnRight();
	bool isOnTop();
	void addForce(CVector<float>& f);
};


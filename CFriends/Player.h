#include "Include.h"
#pragma once

class Player
{
public:
	CVector<float> pos, vel, moveDir;
	float size;
	float speed;

public:
	Player();
	Player(float size);
	Player(float x, float y, float size);
	Player(float x, float y, float size, float speed);
	void move();
	void update(double dt);
	void display();
};


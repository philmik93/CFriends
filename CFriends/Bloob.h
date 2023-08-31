#pragma once

#include "Include.h"
#include "Bloobs.h"
#include "Population.h"

class Bloob
{
public:
	static const float MAX_LIVETIME;
	static const float MAX_SIZE;
	static const float MIN_SIZE;

	CVector<float> acc, pos, vel, target;
	float lifeTime;
	float size;
	float speed;

public:
	Bloob();
	Bloob(float size);
	void display();
	void update(double dt);
	void eat(int nutrition);
	void applyForce(CVector<float>* force);
	

private:
	void move(CVector<float> *target);
	CVector<float> calcNextTarget();
	bool reachedTarget(CVector<float> *target);



};

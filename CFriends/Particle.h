#pragma once
#include "Include.h"
#include "ParticleSystem.h"
#include "System.h"

class Particle
{
public:
	CVector<float> pos, vel, acc;
	int size;
	float liveTime;


public:
	Particle(float x, float y, int size, int liveTime);
	Particle(const Particle& other);
		
	Particle& operator=(const Particle& other);
	


	void display();
	void update(double dt);
	void addForce(CVector<float> force);


};


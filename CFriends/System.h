#pragma once
#include "Include.h"
#include "Particle.h"
#include "ParticleSystem.h"

class Particle;

class System
{
public:
	std::vector<Particle*>* particles;
	float pLifeTime;
	float particleSize;
	float clock;
	CVector<float> pos;
	int maxParticles;

public:
	System(float x, float y, int maxParticles, float particleSize);
	void run(double dt);
	void display();
	void update(double dt);
	void addForce(CVector<float> force);
};


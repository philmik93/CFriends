#pragma once
#include "Include.h"
#include "System.h"
#include "Particle.h"

class Particle;



class ParticleSystem : public App
{

public:
	
	System* system = nullptr;
	CVector<float>* wind;
	
public:

	void setup() override;


	void process(double dt) override;

};


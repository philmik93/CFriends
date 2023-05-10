#include "Include.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "System.h"

System::System(float x, float y, int maxParticles, float particleSize) : pos(CVector<float>({ x, y })), particleSize(particleSize), pLifeTime(255), clock(100), maxParticles(maxParticles)
{
	particles = new std::vector<Particle*>();
}

void System::run(double dt)
{
	update(dt);
	display();
}

void System::display()
{
	for (int i = particles->size() - 1; i >= 0; i--)
	{
		particles->at(i)->display();
	}
}

void System::update(double dt)
{
	for (int i = particles->size() - 1; i >= 0; i--)
	{
		if (particles->at(i)->liveTime <= 0) particles->erase(particles->begin() + i);
		else particles->at(i)->update(dt);
	}
	clock -= 15 * dt;
	if (clock < 0)
	{
		clock = 100;
		if (maxParticles > particles->size())
		{
			particles->push_back(new Particle(pos.get(0), pos.get(1), particleSize, pLifeTime));
		}
	}

}

void System::addForce(CVector<float> force)
{
	for (Particle* p : *particles)
	{
		p->addForce(force);
	}
}

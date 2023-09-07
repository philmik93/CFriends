#include "Particle.h"
#include "System.h"
#include "ParticleSystem.h"
#include "Include.h"

Particle::Particle(float x, float y, int size, int liveTime) : pos(CVector<float>({x, y})), vel(CVector<float>({ 0.0f, 0.0f })), acc(CVector<float>({ randf(-3,3), randf(-1,0.5) }))
{
	
	this->size = size;
	this->liveTime = liveTime;
}



Particle::Particle(const Particle& other) : pos(other.pos), vel(other.vel), acc(other.acc), size(other.size), liveTime(other.liveTime)
{

}



void Particle::display()
{
	setColor(255, 255, 255,(int)liveTime);
	fillCircle(pos.get(0), pos.get(1), size - 2);
	setLineWidth(2);
	setColor(0, 0, 0, (int)liveTime);
	drawCircle(pos.get(0), pos.get(1), size);
	
}

void Particle::update(double dt)
{

	CVector<float> grav({ 0.0f, 0.05f });
	CVector<float>syncedGrav;
	CVector<float>::mult(&grav, dt, &syncedGrav);
	addForce(syncedGrav);
	vel.add(&acc);
	CVector<float> syncedVel;
	CVector<float>::mult(&vel, dt, &syncedVel);
	pos.add(&syncedVel);
	acc.mult(0.0f);

	liveTime -= 1.5f * dt;



}



void Particle::addForce(CVector<float> force)
{
	acc.add(&force);
}



Particle& Particle::operator=(const Particle& other)
{
	if (this != &other)
	{
		pos = other.pos;
		vel = other.vel;
		acc = other.acc;
		size = other.size;
		liveTime = other.liveTime;
	}
	return *this;
}









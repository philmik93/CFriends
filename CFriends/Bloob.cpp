#include "Include.h"
#include "Bloob.h"
#include "Population.h"
#include "Bloobs.h"

const float Bloob::MAX_LIVETIME = 255;
const float Bloob::MAX_SIZE = 70;
const float Bloob::MIN_SIZE = 3;


Bloob::Bloob() : acc(CVector<float>({ 0,0 })), vel(CVector<float>({ 0,0 })), pos(CVector<float>({ randf(0, getWidth()), randf(0, getHeight()) })), target(calcNextTarget()), lifeTime(MAX_LIVETIME/2), size(randf(MIN_SIZE, MAX_SIZE))
{
	speed = 200.0 / (size*(size/4));
}

Bloob::Bloob(float size) : acc(CVector<float>({ 0,0 })), vel(CVector<float>({ 0,0 })), pos(CVector<float>({ randf(0, getWidth()), randf(0, getHeight()) })), target(calcNextTarget()), lifeTime(MAX_LIVETIME), size(size)
{
	speed = 80.0 / size;
}

void Bloob::display()
{
	setColor(255, 255, 255, lifeTime);
	fillCircle(pos.get(0), pos.get(1), size-1);
	setColor(0, lifeTime);
	drawCircle(pos.get(0), pos.get(1), size);
}

void Bloob::update(double dt)
{
	if (reachedTarget(&target))
	{
		target = calcNextTarget();
	}

	move(&target);
	vel.add(&acc);
	pos.add(&vel);
	acc.mult(0.0);

	lifeTime -= 0.3;
}



void Bloob::move(CVector<float> *target)
{
	CVector<float> moveVec;
	CVector<float>::sub(target, &pos, &moveVec);
	moveVec.setMag(speed);
	vel = moveVec;
}



CVector<float> Bloob::calcNextTarget()
{
	float x = randf(0, getWidth());
	float y = randf(0, getHeight());
	return CVector<float>({x,y});
}




bool Bloob::reachedTarget(CVector<float>* target)
{
	CVector<float> vec;
	CVector<float>::sub(target, &pos, &vec);
	float dist = vec.getMag();
	if (dist <= size) return true;
	else return false;
}




void Bloob::applyForce(CVector<float> *force)
{
	acc.add(force);
}

void Bloob::eat(int nutrition)
{
	lifeTime += nutrition;
}






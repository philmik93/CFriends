#include "Include.h"
#include "Engine.h"

Engine::Engine(int count)
{
	objects = new Object[count];
	this->count = count;
}

void Engine::run(double dt)
{
	display();
	update(dt);
}

void Engine::display()
{
	for (int i = 0; i < count; i++)
	{
		objects[i].display();
	}
}

void Engine::update(double dt)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (checkCollision(objects[i], objects[j]))
			{
				// TODO: collision would be cool
			}
		}
		objects[i].update(dt);
	}
}

bool Engine::checkCollision(Object& obj1, Object& obj2)
{
	float dist = obj1.size / 2 + obj2.size / 2;
	CVector<float> temp;
	CVector<float>::sub(&(obj1.pos), &(obj2.pos), &temp);
	if (temp.getMag() <= dist) return true;
		
	return false;
}


void Engine::addForce(CVector<float>& f)
{
	for (int i = 0; i < count; i++)
	{
		objects[i].addForce(f);
	}
}

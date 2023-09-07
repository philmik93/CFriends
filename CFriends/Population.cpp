#include "Include.h"
#include "Bloob.h"
#include "Bloobs.h"
#include "Population.h"

const int Population::MAX_POPULATION = 300;
const int Population::MAX_FOOD = 300;
const int Population::FOOD_RATE = 30;
const float Population::REPLICATION_PROBABILITY = 0.0001;

Population::Population() : foodTimer(0)
{
	for (int i = 0; i < MAX_POPULATION; i++)
	{
		bloobs.push_back(new Bloob());
	}
}




Population::Population(int pop, int food) : foodTimer(0)
{
	if (pop < MAX_POPULATION)
	{
		for (int i = 0; i < pop; i++)
		{
			bloobs.push_back(new Bloob());
		}
	}
	else
	{
		for (int i = 0; i < MAX_POPULATION; i++)
		{
			bloobs.push_back(new Bloob());
		}
	}

	if (food < MAX_FOOD)
	{
		for (int i = 0; i < food; i++)
		{
			this->food.push_back(new Food());
		}
	}
	else
	{
		for (int i = 0; i < MAX_FOOD; i++)
		{
			this->food.push_back(new Food());
		}
	}
}




Population::~Population()
{
	for (int i = this->food.size() - 1; i >= 0; i--)
	{
		delete this->food.at(i);
	}

	for (int i = this->bloobs.size() - 1; i >= 0; i--)
	{
		delete this->bloobs.at(i);
	}

}


void Population::run(double dt)
{
	display();
	update(dt);
}


void Population::display()
{
	for (Bloob* b : bloobs)
	{
		b->display();
	}

	for (Food* f : food)
	{
		f->display();
	}
}


void Population::update(double dt)
{
	for (int i = bloobs.size()-1; i >= 0; i--)
	{
		Bloob* b = bloobs.at(i);
		if (b->lifeTime <= 0)
		{
			bloobs.erase(bloobs.begin() + i);
			continue;
		}
		b->update(dt);
		
		if (randf(0, 100) <= REPLICATION_PROBABILITY * b->lifeTime) bloobs.push_back(new Bloob(b->size + randf(-1, 1)));

		for (int i = 0; i < food.size(); i++)
		{
			CVector<float> vec;
			CVector<float>::sub(&(b->pos), &(food.at(i)->pos), &vec);
			float dist = vec.getMag();
			if (dist < b->size)
			{
				b->eat(food.at(i)->nutrition);
				food.erase(food.begin()+i);
			}
		}
	}

	if (foodTimer > FOOD_RATE)
	{
		foodTimer = 0;
		food.push_back(new Food());
	}

	foodTimer++;
	
}
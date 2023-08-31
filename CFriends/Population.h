#pragma once
#include "Include.h"
#include "Bloob.h"
#include "Food.h"


class Food;
class Bloob;

class Population
{
public:
	static const int MAX_POPULATION;
	static const int MAX_FOOD;
	static const int FOOD_RATE;
	static const float REPLICATION_PROBABILITY;
	std::vector<Bloob*> bloobs;
	std::vector<Food*> food;
	int foodTimer;

public:
	Population();
	Population(int pop, int food);
	~Population();
	void run(double dt);

private:
	void display();
	void update(double dt);
};

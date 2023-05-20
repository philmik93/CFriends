#pragma once
#include "Include.h"
#include "Object.h"

class Engine
{
public:
	int count;
	Object* objects;

public:
	Engine(int count);
	void run(double dt);
	void addForce(CVector<float>& f);

private:
	void display();
	void update(double dt);
	bool checkCollision(Object& obj1, Object& obj2);
	
};


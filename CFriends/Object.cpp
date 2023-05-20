#include "Include.h"
#include "Object.h"


Object::Object(float x, float y, float size) : pos(CVector<float>({x, y})), vel(CVector<float>({ randf(-6, 6), randf(-1, 1) })), acc(CVector<float>({ 0, 0 })), size(size)
{
	this->dirty = false;
}

Object::Object() : size(randf(20, 40)), pos(CVector<float>({ randf(60 / 2, getWidth() - 60 / 2), randf(60 / 2, getHeight() - 60 / 2) })), vel(CVector<float>({ randf(-6, 6), randf(-1, 1) })), acc(CVector<float>({ 0, 0 }))
{
	this->dirty = false;
}




void Object::display()
{
	setColor(70);
	fillCircle(pos.get(0), pos.get(1), size-1);
	setColor(0);
	setLineWidth(2);
	drawCircle(pos.get(0), pos.get(1), size);

}

void Object::update(double dt)
{
	CVector<float> grav({ 0.0f, 0.08f });

	if (isOnButton())
	{
		vel.set(vel.get(1) * -1, 1);
	}
	else
	{
		acc.add(&grav);
	}

	if (isOnTop())
	{
		vel.set(vel.get(1) * -1, 1);
	}


	if (isOnLeft() || isOnRight() || dirty)
	{
		vel.set(vel.get(0) * -1, 0);
		dirty = false;
	}
	vel.add(&acc);
	pos.add(&vel);

	acc.mult(0.0f);


}

bool Object::isOnButton()
{
	if (pos.get(1) + size / 2 >= getHeight()) return true;
	else return false;
}

bool Object::isOnLeft()
{
	if (pos.get(0) - size / 2 <= 0) return true;
	else return false;
}

bool Object::isOnRight()
{
	if (pos.get(0) + size / 2 >= getWidth()) return true;
	else return false;
}

bool Object::isOnTop()
{
	if (pos.get(1) - size / 2 <= 0) return true;
	else return false;
}



void Object::addForce(CVector<float>& f)
{
	acc.add(&f);
}

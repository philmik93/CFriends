#include "Include.h"
#include "Flocking.h"
#include "Vehicle.h"


Vehicle::Vehicle() : pos(CVector<double>(0, 0)), acc(CVector<double>(0, 0)), r(10), maxSpeed(2.5), maxForce(0.08), sight(60)
{
	vel = CVector<double>(randf(-1, 1), randf(-1, 1));
	vel.setMag(maxSpeed);
}



Vehicle::Vehicle(CVector<double> position) : pos(position), acc(CVector<double>(0,0)), r(10), maxSpeed(2.5), maxForce(0.08), sight(60)
{
	vel = CVector<double>(randf(-1, 1), randf(-1, 1));
	vel.setMag(maxSpeed);
	
}




void Vehicle::display()
{
	CVector<double> xAchse(1, 0);
	double theta = std::acos(vel.dot(&xAchse) / vel.getMag()) / M_PI * 180.0;

	setColor(0);
	drawRect(pos.get(0) - r/2, pos.get(1) - r/2, r);
	setColor(theta, theta / 2, 200);
	fillRect(pos.get(0) - r/2, pos.get(1) - r/2, r);
	
}




void Vehicle::update(double dt)
{
	vel.add(&acc);
	vel.normalize();
	vel = *vel.mult(maxSpeed);
	CVector<double> velSynced;
	pos.add(CVector<double>::mult(&vel, dt, &velSynced));
	acc.mult(0.0);


}





void Vehicle::applyForce(const CVector<double>* force)
{
	acc.add(force);
}




CVector<double> Vehicle::cohesian(const Vehicle* vehicles)
{
	CVector<double> sum(0, 0);
	int count = 0;
	for (int i = 0; i < Flocking::VEHICLE_COUNT; i++)
	{
		CVector<double> vec;
		CVector<double>::sub(&vehicles[i].pos, &pos, &vec);
		float d = vec.getMag();
		if ((d > 0) && (d < sight))
		{
			sum.add(&vehicles[i].pos);
			count++;
		}
	}
	if (count > 0)
	{
		sum.mult(1.0/(double)count);
		return seek(&sum);
	}
	else
	{
		return CVector<double>(0,0);
	}
	
}


CVector<double> Vehicle::align(const Vehicle* vehicles)
{
	CVector<double> sum(0, 0);
	CVector<double> steer(0, 0);
	int count = 0;
	for (int i = 0; i < Flocking::VEHICLE_COUNT; i++)
	{
		CVector<double> vec;
		CVector<double>::sub(&pos, &vehicles[i].pos, &vec);
		float d = vec.getMag();
		if (d > 0 && d < sight)
		{
			sum.add(&vehicles[i].vel);
			count++;
		}
	}

	if (count > 0)
	{
		sum.mult((1.0/(double)count));
		sum.normalize();
		sum.mult(maxSpeed);
		CVector<double>::sub(&sum, &vel, &steer);
		steer.normalize()->mult(maxForce);
	}
	return steer;
}







CVector<double> Vehicle::seperate(const Vehicle* vehicles)
{
	float desiredSeperation = r * 4;
	CVector<double> steer(0,0);
	CVector<double> sum(0, 0);
	int count = 0;

	for (int i = 0; i < Flocking::VEHICLE_COUNT; i++)
	{
		CVector<double> vec;
		CVector<double>::sub(&pos, &vehicles[i].pos, &vec);
		float d = vec.getMag();
		if ((d > 0) && (d < desiredSeperation))
		{
			vec.normalize();
			vec.mult(1.0/(double)d);
			sum.add(&vec);
			count++;
		}
	}

	if (count > 0)
	{
		sum.mult(1.0 / (double)count);
		sum.normalize();
		sum.mult(maxSpeed);
		CVector<double>::sub(&sum, &vel, &steer);
		steer.normalize()->mult(maxForce);
	}
	return steer;

	
}







CVector<double> Vehicle::seek(const CVector<double>* target)
{
	CVector<double> steer;
	CVector<double>desired;
	CVector<double>::sub(target, &pos, &desired);
	float d = desired.getMag();

	if (d < 100)
	{
		float m = map(d, 0, 100, 0, maxSpeed);
		desired.setMag(m);
	}
	else
	{
		desired.setMag(maxSpeed);
	}

	CVector<double>::sub(&desired, &vel, &steer);
	steer.normalize()->mult(maxForce);
	return steer;
}



void Vehicle::applyBehaviors(const Vehicle* vehicles)
{
	CVector<double> seperateForce = seperate(vehicles);
	CVector<double> cohesianForce = cohesian(vehicles);
	CVector<double> alignForce = align(vehicles);
	CVector<double> target(getMouseX(), getMouseY());
	CVector<double> targetForce = seek(&target);
	seperateForce.mult(1);
	cohesianForce.mult(1);
	alignForce.mult(1);

	if (isMousePressed())
	{
		targetForce.mult(1);
	}
	else
	{
		targetForce.mult(0.0);
	}
	applyForce(&seperateForce);
	applyForce(&cohesianForce);
	applyForce(&alignForce);
	applyForce(&targetForce);
}



void Vehicle::borders()
{
	if (pos.get(0) < 0) pos.set(getWidth(),0);
	if (pos.get(0) > getWidth()) pos.set(0, 0);
	if (pos.get(1) < 0) pos.set(getHeight(), 1);
	if (pos.get(1) > getHeight()) pos.set(0, 1);
}

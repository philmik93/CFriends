#pragma once
#include "Include.h"
#include "Flocking.h"

class Vehicle
{
public:
	CVector<double> pos;
	CVector<double> vel;
	CVector<double> acc;
	double maxForce;
	double maxSpeed;
	double sight;
	float r = 5;
	

public:
	Vehicle();
	Vehicle(CVector<double> position);

	CVector<double> seek(const CVector<double>* target);
	CVector<double> align(const Vehicle* vehicles);
	CVector<double> cohesian(const Vehicle* vehicles);
	CVector<double> seperate(const Vehicle* vehicles);
	void display();
	void update(double dt);
	void borders();
	void applyForce(const CVector<double>* force);
	void applyBehaviors(const Vehicle* vehicles);
	
};

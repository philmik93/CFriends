#include "Include.h"
#pragma once
class Field
{
public:
	int field[9][9];


public:
	void init();
	void update(double dt);
	void display();
	void print();

private:
	bool traverse(int pos);
	bool isValueValid(int v, int pos);
	
};


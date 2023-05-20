#pragma once
#include "Include.h"
#include "Field.h"
class Sudoku : public App
{
public:

	Field* field;

	inline void setup() override
	{
		setSize(800, 800);
		setTitle("Sudoku");
		field = new Field();

		field->print();
		field->init();
	}


	inline void process(double dt) override
	{
		field->display();
		
	}

};




/*
int main()
{
	run(new Sudoku());
}
*/


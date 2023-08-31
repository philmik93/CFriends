#pragma once
#include "Include.h"



class Test : public App
{


public:


	inline void setup() override
	{
		setSize(800, 800);
		

	}


	inline void process(double dt) override
	{
		background(30);
		setColor(200, 0, 0);
		drawCircle(100, 100, 30, 30);
	}

};










 
 
 int main()
 {
	 CMatrix<int> m1(3, 3);
	 CMatrix<int> m2(3, 3);
	 m1.randomize(0, 9);
	 m2.randomize(0, 9);

	 m1.print();
	 m2.print();

	 CMatrix<int>::add(m1, m2).print();

	 

 }
 


 


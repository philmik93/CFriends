#include "Bloobs.h"
#include "Include.h"
#include "Population.h"
#include "Bloob.h"

Population *population;


void Bloobs::setup()
{
	setSize(800, 600);
	population = new Population(20, 100);
}

void Bloobs::process(double dt)
{
	background(100);
	population->run(dt);
	
}






/*
int main()
{
	run(new Bloobs());
}
*/

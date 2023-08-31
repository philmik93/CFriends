#include "Include.h"
#include "Bloob.h"
#include "Bloobs.h"
#include "Food.h"
#include "Population.h"

const float Food::INIT_NUTRITION = 50;
const float Food::INIT_SIZE = 3;

Food::Food() : nutrition(INIT_NUTRITION), size(INIT_SIZE), pos(CVector<float>({randf(0, getWidth()), randf(0, getHeight())}))
{
}

void Food::display()
{
	setColor(0,255,0);
	fillCircle(pos.get(0), pos.get(1), size-1);
	setColor(0, 0, 0);
	drawCircle(pos.get(0), pos.get(1), size);
}

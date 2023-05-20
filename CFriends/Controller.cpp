#include "Include.h"
#include "Controller.h"

Controller::Controller(Player* pl) : pl(pl)
{
}

void Controller::handleInput()
{

	pl->moveDir = { 0, 0 };


	if (isKeyPressed('W'))
	{
		CVector<float> vec = { 0, -1 };
		pl->moveDir.add(&vec);
	}
	if (isKeyPressed('A'))
	{
		CVector<float> vec = { -1, 0 };
		pl->moveDir.add(&vec);
	}
	if (isKeyPressed('S'))
	{
		CVector<float> vec = { 0, 1 };
		pl->moveDir.add(&vec);
	}
	if (isKeyPressed('D'))
	{
		CVector<float> vec = { 1, 0 };
		pl->moveDir.add(&vec);
	}
	
}

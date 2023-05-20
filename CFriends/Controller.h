#include "Include.h"
#include "Player.h"
#pragma once
class Controller
{
public:
	Player* pl;

public:
	Controller(Player* pl);
	void handleInput();
};


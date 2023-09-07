#pragma once
#include "Include.h"
#include "Player.h"
#include "Controller.h"



class Minigame : public App
{
	Player* player;
	Controller* controller;

public:
	inline void setup() override
	{
		player = new Player(getWidth()/2, getHeight()/2, 30, 5);
		controller = new Controller(player);

	}


	inline void process(double dt) override
	{
		background(0);
		controller->handleInput();
		player->update(dt);
		player->display();
	}

	

};



/*
int main()
{
	run(new Minigame());
}
*/









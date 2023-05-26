#include "Include.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "System.h"




/*
int main()
{
	run(new ParticleSystem());
}
*/


int main()
{
	run(new ParticleSystem());
}


void ParticleSystem::setup()
{
	setSize(800, 600);
	setTitle("ParticleSystem");

	system = new System(getWidth() / 2, getHeight() / 4, 30, 30);
	wind = new CVector<float>({ 0.05f,0.0f });

}

void ParticleSystem::process(double dt)
{
	background(100, 255);
	system->run(dt);

	system->pos.set(getWidth() / 2, 0);
	system->pos.set(getHeight() / 4, 1);

	if (isMousePressed())
	{	
		CVector<float> mouse = CVector<float>({getMouseX(), getMouseY()});
		wind = CVector<float>::sub(&(system->pos), &mouse);
		wind->setMag(0.05);

		CVector<float>* syncedWind = CVector<float>::mult(wind, dt);
		system->addForce(*syncedWind);
		delete syncedWind;
		
	}

	

	

}

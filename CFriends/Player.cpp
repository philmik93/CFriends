#include "Include.h"
#include "Player.h"


Player::Player() : pos(CVector<float>({ 0.0f,0.0f })), vel(CVector<float>({ 0.0f,0.0f })), moveDir(CVector<float>({ 0.0f,0.0f })), size(30), speed(100.0f)
{
}

Player::Player(float size) : pos(CVector<float>({ 0.0f,0.0f })), vel(CVector<float>({ 0.0f,0.0f })), moveDir(CVector<float>({ 0.0f,0.0f })), size(size), speed(100.0f)
{

}


Player::Player(float x, float y, float size) : pos(CVector<float>({ x,y })), vel(CVector<float>({ 0.0f,0.0f })), moveDir(CVector<float>({ 0.0f,0.0f })), size(size), speed(100.0f)
{

}


Player::Player(float x, float y, float size, float speed) : pos(CVector<float>({ x,y })), vel(CVector<float>({ 0.0f,0.0f })), moveDir(CVector<float>({ 0.0f,0.0f })), size(size), speed(speed)
{

}



void Player::move()
{
	pos.add(CVector<float>::mult(moveDir.normalize(), speed));
}


void Player::update(double dt)
{
	move();
}

void Player::display()
{
	fillCircle(pos.get(0), pos.get(1), size);
}

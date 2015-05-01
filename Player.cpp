/**
AGP Assignment
Player.h
Purpose: Implementation of the player. 
Could be used  for everything which contains the player

@author Marcel Zobus
*/
#include "Player.h"

Player::Player(Model* playermodel)
{
	mPlayerModel = playermodel;

}

Player::~Player()
{

}

std::string Player::GetName()
{
	return "Player";
}

// draws the model
void Player::Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection)
{
	mPlayerModel->Draw(world, view, projection);
}


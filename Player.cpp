#include "Player.h"

Player::Player(Model* playermodel)
{
	mPlayerModel = playermodel;

}

Player::~Player()
{

}

void Player::GetName()
{

}

void Player::Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection)
{
	mPlayerModel->Draw(world, view, projection);
}


/**
AGP Assignment
Player.h
Purpose: Header file for Player.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "AGPSideScroller.h"

class Player : public GameObject
{
public:
	Player(Model* playermodel);
	~Player();
	void Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection);
private:
	Model* mPlayerModel;
};

#endif


/**
AGP Assignment
SceneNode.h
Purpose: Header file for SceneNode.cpp

@author Marcel Zobus
*/

#pragma once
#include "d3d11.h"
#include "math.h"
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENTS
#include <xnamath.h>

#include "Model.h"


class SceneNode
{
public:
	SceneNode();
	~SceneNode();
	void addChildNode(SceneNode *n);
	bool detatchNode(SceneNode *n);
	void execute(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection);
	void SetModel(Model *m);
	void SetXPos(float num);
	void SetYPos(float num);
	void SetZPos(float num);
	void SetXAngle(float num);
	void SetYAngle(float num);
	void SetZAngle(float num);
	void SetScale(float num);
	void SetRotation(float num);
	float GetXPos();
	float GetYPos();
	float GetZPos();
	float GetXAngle();
	float GetYAngle();
	float GetZAngle();
	float GetScale();
	float GetRotation();
	Model* GetModel();
	bool IsObjectHidden();
	void HideObject(bool hide);
private: 
	Model *mModel;
	vector<SceneNode*> mChildren;
	float mX, mY, mZ, mDx, mDz;
	float mXAngle, mZAngle, mYAngle;
	float mScale, mRotation;
	bool mHideObject;
};
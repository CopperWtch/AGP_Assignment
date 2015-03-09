/**
AGP Assignment
SceneNode.cpp
Purpose: SceneNode Object

@author Marcel Zobus
*/

#include "SceneNode.h"

SceneNode::SceneNode()
{
	mModel = NULL;
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
	mXAngle = 0.0f;
	mYAngle = 0.0f;
	mZAngle = 0.0f;
	mScale = 1.0f;
	mRotation = 0.0f;
	mHideObject = false;
}

SceneNode::~SceneNode()
{
	for each (SceneNode* node in mChildren)
	{
		delete node;
	}
	if(mChildren.size() > 0) mChildren.pop_back();
	mChildren.clear();
}

void SceneNode::addChildNode(SceneNode *n)
{
	mChildren.push_back(n);
}
bool SceneNode::detatchNode(SceneNode *n)
{
	//traverse tree to find node to detatch
	for (int i = 0; i < mChildren.size(); i++)
	{
		if (n == mChildren[i])
		{
			mChildren.erase(mChildren.begin() + i);
			return true;
		}
		if (mChildren[i]->detatchNode(n) == true) return true;
	}
	return false; //node not in this tree
}
void SceneNode::execute(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection)
{
	// the local wiorkd matrix will be used to calc the local transformations for this node
	XMMATRIX local_world = XMMatrixIdentity();

	local_world = XMMatrixRotationX(XMConvertToRadians(mXAngle));
	local_world *= XMMatrixRotationY(XMConvertToRadians(mYAngle));
	local_world *= XMMatrixRotationZ(XMConvertToRadians(mZAngle));

	local_world *= XMMatrixScaling(mScale, mScale, mScale);

	local_world *= XMMatrixTranslation(mX, mY, mZ);

	// the local matrix is multiplied y the passed in world matrix that contains the concatenated
	// transformations of all parent nodes so that this nodes transformations are relative to those
	local_world *= *world;

	// only draw if there is a model attached 
	if (!mHideObject && mModel) mModel->Draw(&local_world, view, projection);

	//traverse all child nodes, passing in the concatenated world matrix
	for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren[i]->execute(&local_world, view, projection);
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//	Getter and Setter
//////////////////////////////////////////////////////////////////////////////////////

// mModel
void SceneNode::SetModel(Model *m) 
{
	mModel = m; 
}
Model* SceneNode::GetModel() 
{ 
	return mModel;
}

// mX, mY, mZ
void SceneNode::SetXPos(float num)
{
	mX = num;
}
void SceneNode::SetYPos(float num)
{
	mY = num; 
}
void SceneNode::SetZPos(float num)
{
	mZ = num; 
}
float SceneNode::GetXPos()
{
	return mX;
}
float SceneNode::GetYPos()
{
	return mY;
}
float SceneNode::GetZPos()
{
	return mZ;
}

// mXAngle, mYAngle, mZAngle
void SceneNode::SetXAngle(float num)
{ 
	mXAngle = num;
}
void SceneNode::SetYAngle(float num)
{
	mYAngle = num; 
}
void SceneNode::SetZAngle(float num)
{
	mZAngle = num;
}
float SceneNode::GetXAngle()
{ 
	return mXAngle;
}
float SceneNode::GetYAngle()
{ 
	return mYAngle; 
}
float SceneNode::GetZAngle()
{ 
	return mZAngle; 
}

// mScale
float SceneNode::GetScale()
{ 
	return mScale; 
}
void SceneNode::SetScale(float num)
{
	mScale = num;
}

// mRotation
float SceneNode::GetRotation()
{ 
	return mRotation;
}
void SceneNode::SetRotation(float num)
{
	mRotation = num;
}

// mHideObject
bool SceneNode::IsObjectHidden()
{
	return mHideObject;
}
void SceneNode::HideObject(bool hide)
{
	mHideObject = hide;
}


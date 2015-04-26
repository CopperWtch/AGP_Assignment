/**
AGP Assignment
SceneNode.cpp
Purpose: SceneNode Object

@author Marcel Zobus
*/

#include "SceneNode.h"
#include "Player.h"

SceneNode::SceneNode()
{
	//mModel = NULL;
	gameObject = NULL;
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
	mXAngle = 0.0f;
	mYAngle = 0.0f;
	mZAngle = 0.0f;
	mScaleX = 1.0f;
	mScaleY = 1.0f;
	mScaleZ = 1.0f;
	mRotation = 0.0f;
	mHideObject = false;
}

SceneNode::~SceneNode()
{
	for (int i = mChildren.size() - 1; i >= 0; i--)
	{
		delete mChildren.at(i);
		mChildren.pop_back();
	}
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

	local_world = XMMatrixScaling(mScaleX, mScaleY, mScaleZ);

	local_world *= XMMatrixRotationX(XMConvertToRadians(mXAngle));
	local_world *= XMMatrixRotationY(XMConvertToRadians(mYAngle));
	local_world *= XMMatrixRotationZ(XMConvertToRadians(mZAngle));

	local_world *= XMMatrixTranslation(mX, mY, mZ);
	
	// the local matrix is multiplied y the passed in world matrix that contains the concatenated
	// transformations of all parent nodes so that this nodes transformations are relative to those
	local_world *= *world;

	// only draw if there is a model attached 
	//if (!mHideObject && mModel) mModel->Draw(&local_world, view, projection);
	if (!mHideObject && gameObject)
	{
		Model* model = dynamic_cast<Model*>(gameObject);
		// draw if cast is not null, which means the object is a model
		if (model != nullptr)
		{
			model->Draw(&local_world, view, projection);
		}

		Player* player = dynamic_cast<Player*>(gameObject);
		if (player != nullptr)
		{
		//	local_view *= XMMatrixTranslation(mX, mY, mZ);
			player->Draw(&local_world, view, projection);
		}
	}


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
//void SceneNode::SetModel(Model *m) 
//{
//	mModel = m; 
//}
//Model* SceneNode::GetModel() 
//{ 
//	return mModel;
//}

vector<SceneNode*> SceneNode::GetChildren()
{
	return mChildren;
}

void SceneNode::SetGameObject(GameObject* go)
{
	gameObject = go;
}
GameObject* SceneNode::GetGameObject()
{
	return gameObject;
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
	mScaleX = num;
	mScaleY = num;
	mScaleZ = num;
}
void SceneNode::SetXScale(float num)
{
	mScaleX = num;
}
void SceneNode::SetYScale(float num)
{
	mScaleY = num;
}
void SceneNode::SetZScale(float num)
{
	mScaleZ = num;
}
float SceneNode::GetXScale()
{
	return mScaleX;
}
float SceneNode::GetYScale()
{
	return mScaleY;
}
float SceneNode::GetZScale()
{
	return mScaleZ;
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


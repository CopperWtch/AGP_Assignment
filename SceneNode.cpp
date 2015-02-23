#include "SceneNode.h"

Scene_Node::Scene_Node()
{
	m_p_model = NULL;
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_zangle = 0.0f;
	m_scale = 1.0f;
	m_rotation = 0.0f;
}

void Scene_Node::addChildNode(Scene_Node *n)
{
	m_children.push_back(n);
}
bool Scene_Node::detatchNode(Scene_Node *n)
{
	//traverse tree to find node to detatch
	for (int i = 0; i < m_children.size(); i++)
	{
		if (n == m_children[i])
		{
			m_children.erase(m_children.begin() + i);
			return true;
		}
		if (m_children[i]->detatchNode(n) == true) return true;
	}
	return false; //node not in this tree
}
void Scene_Node::execute(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection)
{
	// the local wiorkd matrix will be used to calc the local transformations for this node
	XMMATRIX local_world = XMMatrixIdentity();

	local_world = XMMatrixRotationX(XMConvertToRadians(m_xangle));
	local_world *= XMMatrixRotationY(XMConvertToRadians(m_yangle));
	local_world *= XMMatrixRotationZ(XMConvertToRadians(m_zangle));

	local_world *= XMMatrixScaling(m_scale, m_scale, m_scale);

	local_world *= XMMatrixTranslation(m_x, m_y, m_z);

	// the local matrix is multiplied y the passed in world matrix that contains the concatenated
	// transformations of all parent nodes so that this nodes transformations are relative to those
	local_world *= *world;

	// only draw if there is a model attached 
	if (m_p_model) m_p_model->Draw(&local_world, view, projection);

	//traverse all child nodes, passing in the concatenated world matrix
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->execute(&local_world, view, projection);
	}
}

void Scene_Node::SetModel(Model *m) { m_p_model = m; }
Model* Scene_Node::GetModel() { return m_p_model; }

void Scene_Node::SetXPos(float num){ m_x = num; }
void Scene_Node::SetYPos(float num){ m_y = num; }
void Scene_Node::SetZPos(float num){ m_z = num; }
void Scene_Node::SetXAngle(float num){ m_xangle = num; }
void Scene_Node::SetYAngle(float num){ m_yangle = num; }
void Scene_Node::SetZAngle(float num){ m_zangle = num; }
void Scene_Node::SetScale(float num){ m_scale = num; }
void Scene_Node::SetRotation(float num){ m_rotation = num; }
float Scene_Node::GetXPos(){ return m_x; }
float Scene_Node::GetYPos(){ return m_y; }
float Scene_Node::GetZPos(){ return m_z; }
float Scene_Node::GetXAngle(){ return m_xangle; }
float Scene_Node::GetYAngle(){ return m_yangle; }
float Scene_Node::GetZAngle(){ return m_zangle; }
float Scene_Node::GetScale(){ return m_scale; }
float Scene_Node::GetRotation(){ return m_rotation; }

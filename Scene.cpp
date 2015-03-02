#include "Scene.h"

Scene::Scene(ID3D11Device *g_pD3DDevice, ID3D11DeviceContext *g_pImmediateContext)
{
	m_pD3DDevice = g_pD3DDevice;
	m_pImmediateContext = g_pImmediateContext;
}

void Scene::Create()
{
	m_root_node = new Scene_Node();
	m_node1 = new Scene_Node();
	m_node2 = new Scene_Node();
	m_node3 = new Scene_Node();
	m_node4 = new Scene_Node();


	mCube = new Model(m_pD3DDevice, m_pImmediateContext);
	//mSphere = new Model(m_pD3DDevice, m_pImmediateContext);

	m_node1->SetModel(mCube);
	m_node2->SetModel(mCube);
	m_node3->SetModel(mCube);
	m_node4->SetModel(mCube);

	m_root_node->addChildNode(m_node1);
	m_node1->addChildNode(m_node2);
	m_node2->addChildNode(m_node3);
	m_node3->addChildNode(m_node4);
	
	m_node2->SetXPos(5);
	m_node3->SetXPos(6);
	m_node4->SetXPos(7);
	m_node3->SetYPos(1);
	m_node4->SetYPos(-1);
	

	//mSphere->SetXPos(5);
	//textrue
	D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice, "assets/crate002.jpg", NULL, NULL, &m_pTexture0, NULL);

	mCube->LoadObjModel("cube.obj", m_pTexture0);
	//mSphere->LoadObjModel("Sphere.obj", m_pTexture0);
}

float degrees = 0;
void Scene::RenderScene(XMMATRIX view, XMMATRIX projection)
{
	// draw model
	m_root_node->SetYAngle(degrees);
	m_root_node->execute(&XMMatrixIdentity(), &view, &projection);
	degrees += 0.01f;
}

Scene_Node* Scene::GetRootNode()
{
	return m_root_node;
}
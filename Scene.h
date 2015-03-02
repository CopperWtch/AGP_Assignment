#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "SceneNode.h"
#include "Model.h"

class Scene
{
public:
	Scene(ID3D11Device *g_pD3DDevice, ID3D11DeviceContext *g_pImmediateContext);
	void Create();
	void RenderScene(XMMATRIX view, XMMATRIX projection);
	Scene_Node* GetRootNode();
private:
	ID3D11Device *m_pD3DDevice;
	ID3D11DeviceContext *m_pImmediateContext;
	ID3D11ShaderResourceView *m_pTexture0;
	Model *mCube;
	Model *mSphere;

	Scene_Node *m_root_node;
	Scene_Node *m_node1;
	Scene_Node *m_node2;
	Scene_Node *m_node3;
	Scene_Node *m_node4;
};
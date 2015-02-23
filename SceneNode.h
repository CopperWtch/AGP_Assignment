#include "d3d11.h"
#include "math.h"
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENTS
#include <xnamath.h>

#include "Model.h"


class Scene_Node
{
	Model *m_p_model;
	vector<Scene_Node*> m_children;
	float m_x, m_y, m_z, m_dx, m_dz;
	float m_xangle, m_zangle, m_yangle;
	float m_scale, m_rotation;

public:
	Scene_Node::Scene_Node();
	void addChildNode(Scene_Node *n);
	bool detatchNode(Scene_Node *n);
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
};
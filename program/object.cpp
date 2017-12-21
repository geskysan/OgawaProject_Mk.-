#include "object.h"
#include "player.h"

CObject::CObject()
{

}

CObject::~CObject()
{

}

HRESULT CObject::Init()
{
	m_bRotMode = false;

	m_RotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

void CObject::Uninit()
{
	Release();
}

void CObject::Update()
{
	if (m_bRotMode)
	{
		m_rot += m_RotMove;
		if (m_rot.x > D3DX_PI)
			m_rot.x -= D3DX_PI * 2;
		if (m_rot.y > D3DX_PI)
			m_rot.y -= D3DX_PI * 2;
		if (m_rot.z > D3DX_PI)
			m_rot.z -= D3DX_PI * 2;

		if (m_rot.x < -D3DX_PI)
			m_rot.x += D3DX_PI * 2;
		if (m_rot.y < -D3DX_PI)
			m_rot.y += D3DX_PI * 2;
		if (m_rot.z < -D3DX_PI)
			m_rot.z += D3DX_PI * 2;
	}
}

void CObject::Draw()
{

}

void CObject::RotationMode(bool bRotMode, D3DXVECTOR3 RotMove)
{
	m_bRotMode = bRotMode;
	m_RotMove = RotMove;
}
#include "3Danim.h"

C3DAnim::C3DAnim()
{

}

C3DAnim::~C3DAnim()
{

}

HRESULT C3DAnim::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 TextureSize, bool bLoop, int iAnimTime, int iDivisionSide, int iDivisionVer, bool bAnimate)
{
	CSceneBillboard::Init(0, pos, rot,TextureSize);
	m_bAnimLoop = bLoop;
	m_iAnimTime = iAnimTime;
	m_bAnimate = bAnimate;
	m_iAnimCurrentTimer = 0;
	m_iAnimPattern = 0;

	m_iTextureDivisionSide = iDivisionSide;
	m_iTextureDivisionVer = iDivisionVer;

	LoadTexture("data/TEXTURE/explosion.png");

	AnimationLoad();

	return S_OK;
}

void C3DAnim::Uninit(void)
{
	CSceneBillboard::Uninit();
}

void C3DAnim::Update(void)
{
	if (m_bAnimate)
	{

		int iTextureDivisionMax = m_iTextureDivisionSide * m_iTextureDivisionVer;

		m_iAnimCurrentTimer++;
		if (m_iAnimCurrentTimer > m_iAnimTime)
		{
			m_iAnimCurrentTimer = 0;
			m_iAnimPattern = (m_iAnimPattern + 1) % iTextureDivisionMax;

			if (m_iAnimPattern == 0 && !m_bAnimLoop)
			{
				//ƒ‹[ƒv‚µ‚Ä‚È‚©‚Á‚½ŽžI—¹‚·‚é
				Uninit();
				return;
			}

			AnimationLoad();

		}
	}
	CSceneBillboard::Update();
}

void C3DAnim::Draw(void)
{
	CSceneBillboard::Draw();
}

void C3DAnim::AnimationLoad()
{

	int iTextureDivisionMax = m_iTextureDivisionSide * m_iTextureDivisionVer;

	VERTEX_BILLBOARD *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float TextureU = 1.0f / ((float)iTextureDivisionMax / m_iTextureDivisionVer) * (float)(m_iAnimPattern % m_iTextureDivisionSide);
	float TextureV = m_iAnimPattern / m_iTextureDivisionSide / (float)m_iTextureDivisionVer;

	pVtx[0].tex = D3DXVECTOR2(TextureU, TextureV);
	pVtx[1].tex = D3DXVECTOR2(TextureU + 1.0f / m_iTextureDivisionSide, TextureV);
	pVtx[2].tex = D3DXVECTOR2(TextureU, TextureV + 1.0f / m_iTextureDivisionVer);
	pVtx[3].tex = D3DXVECTOR2(TextureU + 1.0f / m_iTextureDivisionSide, TextureV + 1.0f / m_iTextureDivisionVer);

	m_pVtxBuff->Unlock();

}

void C3DAnim::SetAnimPattern(int iNumPattern)
{
	m_iAnimPattern = iNumPattern;
	AnimationLoad();
}
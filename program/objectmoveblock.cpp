#include "objectmoveblock.h"
#include "player.h"
#include "debugproc.h"

CObjectMoveBlock::CObjectMoveBlock()
{
	m_iMoveChangeTimeCount = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CObjectMoveBlock::~CObjectMoveBlock()
{

}

HRESULT CObjectMoveBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move, D3DXVECTOR3 ObjSize,MOVE_BLOCK moveType)
{
	CObjectBlock::Init(pos, rot, ObjSize.x, ObjSize.y, ObjSize.z);
	
	m_move = move;
	m_MoveType = moveType;

	return S_OK;
}

void CObjectMoveBlock::Uninit(void)
{
	CObjectBlock::Uninit();
}

void CObjectMoveBlock::Update(void)
{
	CObjectBlock::Update();

	switch (m_MoveType)
	{
	case MOVE_BLOCK_STRAIGHT:
		m_pos += m_move;
		break;
	case MOVE_BLOCK_REPET:
		m_pos += m_move;
		m_iMoveChangeTimeCount++;
		if (m_iMoveChangeTimeCount >= m_iMoveChangeTime)
		{
			m_iMoveChangeTimeCount = 0;
			m_move *= -1.0f;
		}
		break;
	case MOVE_BLOCK_ROTATE:
		m_pos.x = m_RotateCenterPos.x + sinf(m_fAngle)*m_fLength;
		m_pos.y = m_RotateCenterPos.y + cosf(m_fAngle)*m_fLength;
		m_fAngle += m_fRotateSpeed;
		m_move.x = sinf(m_fAngle + D3DX_PI * 0.5f)*m_fLength*m_fRotateSpeed;
		m_move.y = cosf(m_fAngle + D3DX_PI * 0.5f)*m_fLength*m_fRotateSpeed;
		if (m_fAngle > D3DX_PI)
		{
			m_fAngle -= D3DX_PI * 2;
		}
		if (m_fAngle > -D3DX_PI)
		{
			m_fAngle += D3DX_PI * 2;
		}
		break;
	}
}

void CObjectMoveBlock::Draw(void)
{
	CObjectBlock::Draw();
}

void CObjectMoveBlock::Collision(CPlayer *pPlayer)
{
	D3DXVECTOR3 PlayerMin = pPlayer->GetBBMin();
	D3DXVECTOR3 PlayerMax = pPlayer->GetBBMax();

	if (PlayerMin.x < m_BBMax.x && PlayerMax.x > m_BBMin.x &&
		PlayerMin.y < m_BBMax.y && PlayerMax.y > m_BBMin.y &&
		PlayerMin.z < m_BBMax.z && PlayerMax.z > m_BBMin.z)
	{
		float fTop, fBottom, fRight, fLeft;
		fTop = abs(PlayerMin.y - m_BBMax.y);
		fBottom = abs(m_BBMin.y - PlayerMax.y);
		fRight = abs(m_BBMax.x - PlayerMin.x);
		fLeft = abs(PlayerMax.x - m_BBMin.x);

		if (fTop < fBottom && fTop < fLeft && fTop < fRight)
		{
			CDebugProc::Print("ã\n");
			pPlayer->SetCollisionTop(true);
			pPlayer->AddPostion(D3DXVECTOR3(0.0f, fTop, 0.0f));
			pPlayer->AddMove(D3DXVECTOR3(m_move.x ,m_move.y,m_move.z));
		}
		else if (fBottom < fLeft&& fBottom < fRight)
		{
			CDebugProc::Print("‰º\n");
			pPlayer->SetCollisionBottom();
			pPlayer->AddPostion(D3DXVECTOR3(0.0f, -(fBottom+3.0f), 0.0f));
		}
		else if (fLeft < fRight)
		{
			pPlayer->SetCollisionLeft(true);
			pPlayer->AddPostion(D3DXVECTOR3(-fLeft, 0.0f, 0.0f));
		}
		else
		{
			pPlayer->SetCollisionRight(true);
			pPlayer->AddPostion(D3DXVECTOR3(fRight, 0.0f, 0.0f));
		}

		pPlayer->UpdateBB();
	}

}

void CObjectMoveBlock::InitSetStraight(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXVECTOR3 ObjSize)
{
	CObjectBlock::Init(pos, rot, ObjSize.x, ObjSize.y, ObjSize.z);

	m_move = move;
	m_MoveType = MOVE_BLOCK_STRAIGHT;
}

void CObjectMoveBlock::InitSetRotate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 ObjSize, float fAngle, float fRotateSpeed, float fLength)
{
	CObjectBlock::Init(pos, rot, ObjSize.x, ObjSize.y, ObjSize.z);
	m_fAngle = fAngle;
	m_fLength = fLength;
	m_fRotateSpeed = fRotateSpeed;
	m_RotateCenterPos = pos;
	m_MoveType = MOVE_BLOCK_ROTATE;
}

void CObjectMoveBlock::InitSetRepete(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 ObjSize, D3DXVECTOR3 move, int iMoveChangeTime)
{
	CObjectBlock::Init(pos, rot, ObjSize.x, ObjSize.y, ObjSize.z);
	m_move = move;
	m_iMoveChangeTime = iMoveChangeTime;
	m_MoveType = MOVE_BLOCK_REPET;

}
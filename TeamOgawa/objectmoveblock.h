#ifndef _OBJECTMOVEBLOCK_H_
#define _OBJECTMOVEBLOCK_H_

#include "objectblock.h"

class CObjectMoveBlock : public CObjectBlock
{
public:
	typedef enum
	{
		MOVE_BLOCK_NONE = 0,		//ìÆÇ©Ç»Ç¢
		MOVE_BLOCK_STRAIGHT,	//íºêiÇ∑ÇÈ
		MOVE_BLOCK_ROTATE,		//âÒì]Ç∑ÇÈ
		MOVE_BLOCK_REPET,		//îΩïúÇ∑ÇÈ
		MOVE_BLOCK_MAX,
	}MOVE_BLOCK;

	CObjectMoveBlock();
	~CObjectMoveBlock();

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 move, D3DXVECTOR3 ObjSize, MOVE_BLOCK moveType);
	void InitSetStraight(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,D3DXVECTOR3 ObjSize);
	void InitSetRotate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 ObjSize, float fAngle, float fRotateSpeed,float fLength);
	void InitSetRepete(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 ObjSize,D3DXVECTOR3 move,int iMoveChangeTime);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(CPlayer *pPlayer);
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_RotateCenterPos;
	float m_fAngle;
	float m_fLength;
	float m_fRotateSpeed;
	int   m_iMoveChangeTime;
	int   m_iMoveChangeTimeCount;
	MOVE_BLOCK m_MoveType;
};

#endif //_OBJECTMOVEBLOCK_H_
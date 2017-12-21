//�v���C���[�̏���	[player.h]
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene3D.h"

//------------------------------------------------
//�v���C���[�N���X
//------------------------------------------------
class CObjectBlock;
class CPlayer : public CScene3D
{
public:
	CPlayer();
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void KeyControl(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPostion(D3DXVECTOR3 pos) { m_pos = pos; }
	void AddPostion(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	
	D3DXVECTOR3 GetBBMin(void) { return m_BBMin; }
	D3DXVECTOR3 GetBBMax(void) { return m_BBMax; }

	void SetCollisionTop(bool btop);
	void SetCollisionRight(bool bRight);
	void SetCollisionLeft(bool bLeft);
	void SetCollisionBottom();
	void UpdateBB();
	bool CollisionBlock(CObjectBlock *pObject);
	bool GetCollisionTop(void) { return CollisionTop; }
	bool GetDirection() { return m_bDirection; }
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	void AddMove(D3DXVECTOR3 move) { m_AddMove += move; }
private:
	D3DXVECTOR3 m_Move;

	bool m_bJump;
	float m_fJumpPower;
	int m_iJumpTimer;
	bool m_bJumpKey;
	D3DXVECTOR3 JumpPawer;
	D3DXVECTOR3 m_AddMove;
	void JumpControl(void);
	bool m_bDirection;	//�v���C���[�̌����Ă������	�E�cfalse / ���ctrue
	bool CollisionTop;	//���ƐG��Ă��邩�ǂ���
	bool CollisionRight; //�E�ɏ�Q��������ꍇ
	bool CollisionLeft;	 //���ɏ�Q��������ꍇ
	//�o�E���f�B���O�{�b�N�X�p
	D3DXVECTOR3 m_BBMin;
	D3DXVECTOR3 m_BBMax;
};
#endif // !_PLAYER_H_
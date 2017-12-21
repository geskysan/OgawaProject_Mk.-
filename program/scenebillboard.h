//=============================================================================
//
// �r���{�[�h�I�u�W�F�N�g�̏��� [sceneBillboard.h]
// Author : 
//
//=============================================================================
#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W / �@�� / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_BILLBOARD;

//*********************************************************
// Billboard�I�u�W�F�N�g�N���X
//*********************************************************
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = 4, CScene::OBJTYPE objType = CScene::OBJTYPE_BILLBOARD);
	~CSceneBillboard();

	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 textureSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetType(int nType) { m_nType = nType; }

	void SetVtx(float fLength);
	void SetTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3);
	void SetColAlpha(float fAlpha);
	void LoadTexture(const char *pTextureName);
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̊p�x

	int m_nType;							// ���
};

#endif

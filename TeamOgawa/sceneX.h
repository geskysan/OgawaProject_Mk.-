//X�t�@�C���I�u�W�F�N�g�̏���	[sceneX.h]
#ifndef _SCENEX_H_
#define _SCENEX_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//X�t�@�C���I�u�W�F�N�g
//------------------------------------------------
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 3, CScene::OBJTYPE objtype = CScene::OBJTYPE_X);
	~CSceneX();

	static CSceneX *Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void) { return S_OK; }
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

	LPD3DXMESH GetMesh(void) { return m_pMesh; }

	void SetType(int nType) { m_nType = nType; }

	void SetbUse(bool bUse) { m_bUse = bUse; }

	void SetTexture(const char *TextureName);
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;					// �}�e���A�����̑���

	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;					// �̈ʒu
	D3DXVECTOR3 m_rot;					// ���݂̌���
	D3DXVECTOR3 m_scale;				//�g��l
	int m_nType;						// ���
	bool m_bUse;							//�`�悷�邩�ǂ���
	static const char *m_apModelName[];

};

#endif // !_SCENEX_H_
